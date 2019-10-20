#include <iostream>

#ifndef BLACKJACK_H
#define BLACKJACK_H

class Blackjack {

  public:
    Blackjack(double funds, int minimum);  //parameterized constructor

    void bet(int bet);
    int getBetAmount();
    void setBetAmount(int bet);
    int pullCard();
    void dealerInitial();
    void setDealerInitial(int firstCard);
    int getDealerInitial();
    void setFunds(double funds);
    int getFunds();
    int getMinimum();
    int playerHand(int bet);
    void setBJhand(bool hand_of_21);
    bool getBJhand();
    int dealerFinal(int sumCards);
    void decision(int dealerSum, int sumCards);

  private:
    int funds_;
    int minimum_;
    int dealer_first_card_;
    bool hand_of_21_;
    int bet_amount_;
};



#endif
