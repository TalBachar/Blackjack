#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Blackjack.hpp"

using namespace std;

int main(){
  srand(time(0));     //random cards every time
  int minimum;
  cout << "\tThis program will teach you Basic Strategy for Blackjack! " << endl;

  //choose a minimum
  cout << "Minimum options are: 10$, 25$, or 50$. \nPlease choose minimum: ";
  cin >> minimum;
  while ((minimum != 10) && (minimum!= 25) && (minimum != 50)) {
    cout << "Please choose amount: 10$, 25$, or 50$" << endl;
    cin >> minimum;
  }
  cout << "\nMinimum bet for this table is: " << minimum << "$" << endl;

  cout << "Great! Now select how many chips you'd like to buy: ";
  //enter buy-in
  double funds;
  cin >> funds;
  while (funds < minimum) {
      cout << "You cannot buy-in with less than the minimum bet for this table!" << endl;
      cout << "Please enter the amount of your buy-in: " << endl;
      cin >> funds;
  }
  cout << "\nWe are good to go! Good luck! \n" << endl;

  Blackjack b(funds, minimum);


  for (int i=0; i<5; i++) {
    if (b.getFunds() == 0) {
      cout << "You do not have enogh money to play. Good bye!" << endl;
      break;
    }

    int bet;
    bet = bet;
    b.bet(bet);

    /**
     @param betAmount
     @return: sumCards sum of the player's cards
     **/
    int sumCards = b.playerHand(b.getBetAmount());

    /**
     @return: dealerSum sum of the dealer's cards
     **/
    int dealerSum = b.dealerFinal(sumCards);

    /**
     @param dealerSum, sumCards, betAmount
     @post adjust funds according to outcome of the game
     **/
    b.decision(dealerSum, sumCards);


  } //end 5 games

  return 0;
}
