
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <numeric>
using namespace std;
// CIS-7 Course Project Part 2 by Celeste Hernandez Mora
// for CIS-7 on June 7 2023

struct Label {
  const string CARDNAMES[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Q", "K", "J"};
  const string SUITNAMES[4] = {"♣", "♦", "♥", "♠"};
  const int CARDVALUES[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
};

struct Card {
  string cname;
  string csuit;
  int cval;
};

struct Hand {
  vector<string> cNames;
  vector<int> cValues;
  int cTotal;
};

class Deck {
  private:
    Card cards[4][13];
    Label label;
  public:
    Deck();
    Card hand();
};

Deck::Deck() {
  for (int j = 0; j < 4; j++) {
    for (int k = 0; k < 13; k++) {
      cards[j][k].csuit = label.SUITNAMES[j];
      cards[j][k].cname = label.CARDNAMES[k];
      cards[j][k].cval = label.CARDVALUES[k];
    }
  }
}

Card Deck::hand() {
  int randSuit = (rand() % 4);
  int randIndv = (rand() % 13);

  Card cHand = cards[randSuit][randIndv];
  
  return cHand;
}

int sumUp(Hand cv) {
  int oldSum = cv.cTotal;

  for (int k = 0; k < cv.cValues.size(); k++) {
    if (cv.cValues[k] == 1 && oldSum < 12) {
      cv.cValues[k] = 11;
      if (oldSum == 2) {
        cv.cValues[k] -= 5;
      }
    }
  }
  
  cv.cTotal = accumulate(begin(cv.cValues), end(cv.cValues), 0);

  return cv.cTotal;
}

void menu() {
  cout << endl << endl;
  cout << "What would you like to do next?";
  cout << endl;
  cout << "[1] Draw a card" << endl;
  cout << "[2] Stand" << endl;
  cout << "Any button to exit" << endl;
}

int mainmenu() {
  int answ; 

  cout << endl << endl << "-=-=-=-=-=-=-=-=-=-=-" << endl;
  cout << "♣♦♥♠ Blackjack ♣♦♥♠" << endl;
  cout << "Press 1 to play a round; anything else to exit" << endl;
  cout << "-=-=-=-=-=-=-=-=-=-=-" << endl;
  cin >> answ;

  return answ;
}

class Play {
  private: 
    Card icard;
    Hand ihand;
    Deck deck;
    int dCash;
  public:
    Play();
    void addCard();
    int startP();
    int startD();
    int advance();
    int stand(int, int);
    void displayD(bool);
    void beginCheck();
    int outcome(int, int, int);
    int bet(int, int);
};

Play::Play() {
  icard = deck.hand();
  ihand.cValues.push_back(icard.cval);
  ihand.cNames.push_back(icard.cname);
  ihand.cNames.push_back(icard.csuit);
  dCash = 100000;
}

void Play::addCard() {
  icard = deck.hand();
  ihand.cValues.push_back(icard.cval);
  ihand.cNames.push_back(icard.cname);
  ihand.cNames.push_back(icard.csuit);
}

int Play::startP() {
  cout << "Your cards: " << endl;
  addCard();
  
  for (int k = 0; k < ihand.cNames.size(); k++) {
    cout << ihand.cNames[k] << " ";
  }

  ihand.cTotal = ihand.cValues[0] + ihand.cValues[1];
  
  cout << endl << "Your total: " << endl;
  ihand.cTotal = sumUp(ihand);
  cout << ihand.cTotal;
  
  return ihand.cTotal;
}

void Play::displayD(bool show) {
  if (show == 1) {
    cout << endl << endl;
    cout << "Dealer's cards: " << endl;
    for (int k = 0; k < ihand.cNames.size(); k++) 
      cout << ihand.cNames[k] << " ";
      cout << endl;
      cout << "Dealer's total: " << endl;
      cout << ihand.cTotal << endl;
    cout << endl;
  }
  else {
    cout << "Dealer's cards: " << endl;
    cout << ihand.cNames[0] << " " << ihand.cNames[1] << " ???" << endl << endl << endl;
  }
}

int Play::startD() {
  addCard();
  
  ihand.cTotal = ihand.cValues[0] + ihand.cValues[1];
  displayD(0);
  ihand.cTotal = sumUp(ihand);
  
  return ihand.cTotal;
}

int Play::advance() {
  cout << "====================" << endl;
  addCard();
  cout << "You pulled a new card." << endl;
  cout << ihand.cNames[ihand.cNames.size()-2] << " " << ihand.cNames[ihand.cNames.size()-1] << endl;
  cout << "====================" << endl;

  displayD(0);
  
  cout << "Your cards: " << endl;
  for (int k = 0; k < ihand.cNames.size(); k++) {
    cout << ihand.cNames[k] << " ";
  }

  cout << endl << "Your total: " << endl;
  ihand.cTotal = sumUp(ihand);
  cout << ihand.cTotal;
  
  return ihand.cTotal;
}

int Play::stand(int dsum, int psum) {
  cout << "You have chosen to stand." << endl << endl;

  while (dsum <= psum && dsum != 21) {
    addCard();
    dsum = sumUp(ihand);
  }
  ihand.cTotal = dsum;
  
  return ihand.cTotal;
}

int Play::outcome(int pVal, int dVal, int status) {
  cout << endl;
  
  if (pVal == dVal && status == 2) {
    cout << "A tie!";
    return 0;
  }
  else if (dVal > pVal && dVal < 21 && status == 2) {
    cout << "Game over! Your value was lower.";
    return 2;
  }
  else if (pVal == 21 && dVal != 21) {
    cout << "Wow! You hit 21 and won the game!";
    return 1;
  }
  else if (pVal != 21 && dVal == 21) {
    cout << "Game over! Your opponent hit 21.";
    return 2;
  }
  else if (pVal > 21 && dVal < 21) {
    cout << "Game over! You hit above 21.";
    return 2;
  }
  else if (pVal < 21 && dVal > 21) {
    cout << "Wow! Your opponent hit above 21 and you won!";
    return 1;
  }
  else if (pVal == 21 && dVal == 21) {
    cout << "A tie! You both hit 21.";
    return 0;
  }
  else 
    
  return 4;
}

int Play::bet(int end, int pbet) {
  cout << endl << endl;
  switch (end) {
    case 0: cout << "All money remains unchanged!" << endl; return pbet;
    break;
    case 1: cout << "You gained +" << pbet << "!" << endl; return pbet+pbet;
    break;
    case 2: cout << "You lost -" << pbet << "..." << endl; return 0;
    break;
    default: cout << "";
  }
  return -1;
}

int main() {
  srand(time(NULL));
  int psum = 0, dsum = 0;
  int answer = 0;
  Play play, play1, play2;

  answer = mainmenu();
   if (answer != 1)
    return 0;
    
  cout << endl << "=====================" << endl;
  int playerbet = 0;
  cout << endl << endl << "How much would you like to bet? $";
  cin >> playerbet;
  cout << endl << "====================" << endl;
  
  dsum = play1.startD();
  psum = play2.startP();

  int endFlag = play.outcome(psum, dsum, 1);
  
  if (endFlag != 4) {
    play1.displayD(1);
    cout << play.bet(endFlag, playerbet) << " is your total.";
    return 0;
  } 
    
  int response = 0;
  menu();
  cin >> response;
    
  while (response == 1 || response == 2) {
    if (response == 1) {
      psum = play2.advance();
        
    endFlag = play.outcome(psum, dsum, 1);
    if (endFlag != 4) {
      play1.displayD(1);
     cout << play.bet(endFlag, playerbet) << " is your total.";
      return 0;
     }
   }
    if (response == 2) {
      dsum = play1.stand(dsum, psum);

      endFlag = play.outcome(psum, dsum, 2);
      if (endFlag != 4) {
        play1.displayD(1);
        cout << play.bet(endFlag, playerbet) << " is your total.";
        return 0;
     }
   }
   menu();
    cin >> response;
  }
  return 0;
}