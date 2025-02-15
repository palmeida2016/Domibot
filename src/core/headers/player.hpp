#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "deck.hpp"
#include "card.hpp"

class Player {
public:
    Player(std::string name);

    void initializeStartingDeck();
    void startTurn();
    void playCard(int cardIndex);
    void buyCard(Card card);
    void endTurn();

    void displayHand();
    bool hasActionCards();

    // Getters and Setters
    int getActions();
    int getBuys();
    int getCoins();
    std::string getName();

    int getScore();
    Deck& getDeck();

    void addCoins(int amount);
    void addActions(int amount);
    void addBuys(int amount);

private:
    std::string name;
    Deck deck;
    int actions;
    int buys;
    int coins;
};


#endif