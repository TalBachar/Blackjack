#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Blackjack.hpp"

using namespace std;
/***

//  PlayerHand(betAmount, funds, minimum);
int PlayerHand(int bet, int funds) {
  cout << "Player has: ";
  //first card
  int playerCardsArr[21];
  playerCardsArr[1] = rand() % 13 + 1;
  if (playerCardsArr[1] == 1) {cout << "Ace";}
  else if (playerCardsArr[1] == 11) {cout << "Jack";}
  else if (playerCardsArr[1] == 12) {cout << "Queen";}
  else if (playerCardsArr[1] == 13) {cout << "King";}
  else {cout << playerCardsArr[1];}
  cout << " and ";
  //second card
  playerCardsArr[2] = rand() % 13 + 1;
  if (playerCardsArr[2] == 1) {cout << "Ace" << endl;}
  else if (playerCardsArr[2] == 11) {cout << "Jack" << endl;}
  else if (playerCardsArr[2] == 12) {cout << "Queen" << endl;}
  else if (playerCardsArr[2] == 13) {cout << "King" << endl;}
  else {cout << playerCardsArr[2] << endl;}

  if (playerCardsArr[2] == 1) { //blackjack first card Ace
    if (10 <= playerCardsArr[1]) {
      cout << "Blackjack!!" <<endl;
      return 150;                    //if player has blackjack, return 150
    }
  } //end blackjack first card Ace
  if (playerCardsArr[1] == 1) { //blackjack second card Ace
    if (10 <= playerCardsArr[2]) {
      cout << "Blackjack!!" <<endl;
      return 150;                    //if player has blackjack, return 150
    }
  } //end blackjack second card Ace

  //Dealer();

//PLAYER ACTIONS *******************

  int sumCards =playerCardsArr[1] + playerCardsArr[2];
  cout << "Sum of your cards is " << sumCards << endl;
  cout << "Would you like to: (H)hit / (S)stand / (D)double Down";
  if (playerCardsArr[1] == playerCardsArr[2]) {cout << " / (P)split";}
  cout << "\n";

  char action;
  cin >> action;
  while (action != 'S' && action != 's' && action != 'H' && action != 'h' && action != 'D' && action != 'd'
  && action != 'P' && action != 'p') {
    cout << "Invalid action. Please choose: (H)hit / (S)stand / (D)double Down";
    if (playerCardsArr[1] == playerCardsArr[2]) {cout << " / (P)split";}
    cin >> action;
  }

  if (action == 'S' || action == 's') {
    cout << "Player stands on " << sumCards;
    return sumCards;                      //player stands, return sum of cards
  }
  if (action =='D' || action =='d') {
    if ()

  }

  return 1;

**************************************************/
 //end playerHand
/*
void Dealer (){
  cout << "Dealer has: ";
  int dealerCard = rand() % 13 + 1;
  if (dealerCard == 1) {cout << "Ace";}
  else if (dealerCard == 11) {cout << "Jack";}
  else if (dealerCard == 12) {cout << "Queen";}
  else if (dealerCard == 13) {cout << "King";}
  else {cout << dealerCard;}

/////////////////////////  MUST CONTINUE DEALRS HAND ///////////////////////////

}


int bet(int funds,int min){
  int betAmount;
  cout << "Place your bets! Remember, the minimum in this table is " << min << "$" << endl;
  cin >> betAmount;
  while (betAmount < min) {
    cout << "Your bet is lower than the minimum! Place a bet of at least " << min << "$ please: " << endl;
    cin >> betAmount;
  }
  return betAmount;
}

*/
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


  for (int i=0; i<1000; i++) {  //a thousand games
    if (b.getFunds() == 0) {
      cout << "You do not have enogh money to play. Good bye!" << endl;
      break;
    }
    int betAmount = b.bet();

    /**
     @param betAmount
     @return: sumCards sum of the player's cards
     **/
    int sumCards = b.playerHand(betAmount);

    /**
     @return: dealerSum sum of the dealer's cards
     **/
    int dealerSum = b.dealerFinal(sumCards);

    /**
     @param dealerSum, sumCards, betAmount
     @post adjust funds according to outcome of the game
     **/
    b.decision(dealerSum, sumCards, betAmount);


  } //end 1000 games

  return 0;
}
