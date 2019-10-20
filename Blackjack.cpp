#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include"Blackjack.hpp"

using namespace std;

  Blackjack::Blackjack(double funds, int minimum):
  funds_(funds),
  minimum_(minimum)
  {}

  int Blackjack::bet(){
  setBJhand(false);
  int betAmount;
  cout << "** At any point - press Ctrl+C to quit **" << endl;
  cout << "Place your bets! Remember, the minimum in this table is " << getMinimum() << "$." << endl;
  cout << "That means you can bet on " << getMinimum() <<"$, " << getMinimum()*2 << "$, " << getMinimum()*3 << "$ and so on ";
  cout << "[Funds: " <<getFunds() << "]: ";
  cin >> betAmount;
  while (betAmount < getMinimum() && betAmount < 10) {
    cout << "\nYour bet is lower than the minimum! Place a bet of at least " << getMinimum() << "$ please: ";
    cin >> betAmount;
  }
  while (betAmount % getMinimum() != 0) {
    cout << "Your bet must be a multiple of " << getMinimum() << ". please place your bet: ";
    cin >> betAmount;
  }
  while (betAmount > getFunds()) {
    cout << "\nYou don't have enough chips for that bet! please place your bet: ";
    cin >> betAmount;
  }
  return betAmount;
  } //end bet()

  int Blackjack::pullCard() {
    int card = rand() % 13 + 1;
    if (card == 1) {cout << "Ace";}
    else if (card == 11) {cout << "Jack";
    card = 10;}
    else if (card == 12) {cout << "Queen";
    card = 10;}
    else if (card == 13) {cout << "King";
    card = 10;}
    else {cout << card;}

    return card;
  } //end pullCard()

  int Blackjack::playerHand(int bet) {

    bool tenAndAce = false;
    int sumCards;
    setBJhand(tenAndAce);

    cout << "\n\tPlayer has: ";
    int playerCardsArr[21];
    playerCardsArr[0] = pullCard();       //first card
    cout << " and ";
    playerCardsArr[1] = pullCard();      //second card

    if (playerCardsArr[0] == 1) {     //blackjack first card Ace
      if (playerCardsArr[1] == 10) {
        cout << "\nBlackjack!!" <<endl;
        tenAndAce = true;
        setBJhand(tenAndAce); //set tenAndAce=true(player has BJ)
      }
    } //end blackjack first card Ace

    if (playerCardsArr[0] == 10) {    //blackjack second card Ace
      if (playerCardsArr[1] == 1) {
        cout << "\nBlackjack!!" <<endl;
        tenAndAce = true;
        setBJhand(tenAndAce);//set tenAndAce=true(player has BJ)
      }
    } //end blackjack second card Ace

    if (getBJhand() == false){     //Will run only if getBJhand() is false (player doesn't have BJ)

      cout << "\n\tDealer has: ";     //names the dealer's card
      dealerInitial();

      sumCards = playerCardsArr[0] + playerCardsArr[1];   //initial sum of player's first 2cards
      cout << "\nSum of your cards is: " << sumCards;
      if (playerCardsArr[0] == 1 || playerCardsArr[1] == 1) {  //if one of player's cards is ace
        cout << " / " << sumCards+10 << endl;  //show sumCards 11 w/ Ace option
      }
      else {cout << endl;}

      cout << "Would you like to: (H)hit / (S)stand / (D)double Down";
      if (playerCardsArr[0] == playerCardsArr[1]) {cout << " / (P)split: ";} //split option in case of pair
      else {cout << ": ";}

      char action;
      cin >> action;

      //---------------------invalid input
      while (action != 'S' && action != 's' && action != 'H' && action != 'h' && action != 'D'
      && action != 'd' && action != 'P' && action != 'p') {
        cout << "Invalid action. Please choose: (H)hit / (S)stand / (D)double Down";
        if (playerCardsArr[0] == playerCardsArr[1]) {cout << " / (P)split";}
        cin >> action;
      }//end of invalid input

      //---------------------Double down--------------------
      if (action =='D' || action =='d') {
        if (getFunds() < bet*2) { // if insufficient funds for DD
          cout << "You do not have enough chips to double-down. Choose another action:" << endl;
          cout << "(H)hit / (S)stand";
          if (playerCardsArr[0] == playerCardsArr[1]) {cout << " / (P)split";}
          cin >> action;
        } //end of insufficient funds for DD
        else if (getFunds() >= bet*2) {
          bet = bet*2;
          cout << "Double Down! Card is: ";
          playerCardsArr[2] = pullCard();
          sumCards = playerCardsArr[0] + playerCardsArr[1] + playerCardsArr[2];
          if (playerCardsArr[0] == 1 || playerCardsArr[1] == 1 || playerCardsArr[2] == 1) { //if one card is an ace
            if (playerCardsArr[0]+playerCardsArr[1]+playerCardsArr[2] <= 11)  { //if the three cards are <=11
              sumCards = sumCards+10;   //then sumCards will be the higher option with an ace
            }
          }
          cout << "\nSum of your hand is: " << sumCards << endl;
          return sumCards;
        }
      }//--------------------end of Double Down--------------------

      //---------------------Stand--------------------
      if (action == 'S' || action == 's') {
        if (playerCardsArr[0] == 1 || playerCardsArr[1] == 1) //if one of the cards is an ace
          sumCards = sumCards+10;       //sumCards will be the higher option with an ace
        cout << "Player stands on " << sumCards << endl;
        return sumCards;                      //player stands, return sumCards
      }//--------------------end of Stand--------------------

      //---------------------Hit--------------------
      if (action == 'H' || action == 'h') {
        for (int i=3; i < 21; i++) {
          cout << "Hit! Card is: ";
          playerCardsArr[i] = pullCard();
          sumCards += playerCardsArr[i]; //update sum of cards with new card
          cout << "\nSum of your cards is: " << sumCards;
          if (playerCardsArr[0] == 1 || playerCardsArr[1] == 1) {  //if one of player's cards is ace
            if (sumCards <= 11) {                             //and sumCards is <11
              cout << " / " << sumCards+10 << endl;  //show sumCards 11 w/ Ace option
            }
            else {cout << endl;}
          }
          else {cout << endl;}
          if (sumCards > 21) {          //if >21 player busts
            cout << "Player busts!" << endl;
            return sumCards;
          }
          if (sumCards == 21) {         //if 21 player stands
            cout << "Player stands." << endl;
            return sumCards;
          }
          cout << "Press (S)stand, or any other key to hit again: ";
          cin >> action;
          if (action == 's' || action =='S') {
            return sumCards;
          }

        }
      }//--------------------end of Hit--------------------


    } // end of if(!tenAndAce)


  return 0;
  }//end of playerHand()

  void Blackjack::setBJhand(bool hand_of_21){
    hand_of_21_ = hand_of_21;
  }//end of setBJhand()

  bool Blackjack::getBJhand() {
    return hand_of_21_;

  }//end of getBJhand()

  void Blackjack::dealerInitial() {
    int firstCard = pullCard(); //Dealer's first card
    setDealerInitial(firstCard);

  }//end dealerInitial()

  void Blackjack::setDealerInitial(int firstCard) {
    dealer_first_card_ = firstCard;
  }//end setDealerInitial()

  int Blackjack::getDealerInitial() {
    return dealer_first_card_;
  }//end getDealerInitial()

  void Blackjack::setFunds(double funds) {
    funds_ = funds;
  }//end setFunds()

  int Blackjack::getFunds() {
    return funds_;
  }//end getFunds()

  int Blackjack::getMinimum() {
    return minimum_;

  }//end getMinimum()

  int Blackjack::dealerFinal(int sumCards) {
      int dealerSum;
      int dealerArr[21];
      if (getBJhand() == false && sumCards <= 21) {   //dealer doesn't play if player busted or has BJ
        cout << "Dealer's first card is: ";
        if (getDealerInitial() == 1) {
          cout << "Ace" << endl;
        }
        else {cout << getDealerInitial() << endl;}
        dealerArr[0] = getDealerInitial();
        cout << "Dealer's second card is: ";
        dealerArr[1] = pullCard();

        dealerSum = dealerArr[0] + dealerArr[1];
        cout <<  " [SUM: " << dealerSum;
        if (dealerArr[0] == 1 || dealerArr[1] == 1) {  //if one of dealer's cards is ace
          cout << " / " << dealerSum+10 << "]" << endl;  //show dealerSum 11 w/ Ace option
        }
        else {cout << "]" << endl;}
        if (dealerArr[0] == 1 || dealerArr[1] == 1) {
          if (7 < dealerSum && dealerSum < 12) {
            dealerSum = dealerSum+10;
            return dealerSum;
          }
        }
        for (int i=2; i<21; i++) {
          if (dealerSum > 21) {
            cout << "Dealer busts with " << dealerSum << endl;
            return dealerSum;
          }
          else if (dealerSum >= 17) {
            cout << "Dealer stands on " << dealerSum << endl;
            return dealerSum;
          }
          else {
            cout << "Dealer hits! Card is ";
            dealerArr[i] = pullCard();
            dealerSum += dealerArr[i];
            cout << " [SUM: " << dealerSum << "]" << endl;

          }
      }

    }
    return 1;
  } //end of dealerFinal()

  void Blackjack::decision(int dealerSum, int sumCards, int betAmount){
    if (getBJhand() == true) {          //if player has BJ, betAmount =+ *1.5
      cout << "Player wins!" << "\n\n";
      setFunds(getFunds() + (betAmount*1.5));
    }

    else if (getBJhand() == false) {    //if player doesn't have BJ
      if (sumCards > 21) {    //player busted
        cout << "Dealer wins! " << "\n\n";
        setFunds(getFunds()-betAmount);
      }

      else if (dealerSum > 21) {  //dealer busted
        cout << "Player wins! " << "\n\n";
        setFunds(getFunds() + betAmount);
      }

      else if (sumCards > dealerSum) {  //player>dealer, but still under 21
        cout << "Player wins! " << "\n\n";
        setFunds(getFunds() + betAmount);
      }

      else if (dealerSum > sumCards) {  //dealer > player, but still under 21
        cout << "Dealer wins! " << "\n\n";
        setFunds(getFunds() - betAmount);
      }

      else if (sumCards == dealerSum) { //push, nothing happens
        cout << "Push!" << "\n\n";
      }

    } //end of player doesn't have BJ
  } //end of decision()
