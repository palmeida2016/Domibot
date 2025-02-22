#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
// #include "card.hpp"
#include "deck.hpp"
#include "card_effect.hpp"

class Player {
public:
    Player(std::string name);

    void initializeStartingDeck();
    void startTurn();
    void applyCardEffect(const CardEffect& effect);
    void buyCard(Card *card);
    void endTurn();

    void displayHand();
    void displayDiscardPile();
    bool hasCardType(CardType type);
    bool hasCard(std::string cardName);
    int calculateScore();

    // Getters and Setters
    int getActions() { return actions; }
    int getBuys() { return buys; }
    int getCoins() { return coins; }
    std::string getName() { return name; }
    Deck* getDeck() { return deck; }
    bool getMerchantEffect() { return hasMerchantEffect; }
    void setMerchantEffect(bool value) {this->hasMerchantEffect = value;}

    void addCoins(int amount) { coins += amount; }
    void addActions(int amount) { actions += amount; }
    void addBuys(int amount) { buys += amount; }


private:
    std::string name;
    Deck* deck;
    int actions;
    int buys;
    int coins;
    bool hasMerchantEffect;
};


#endif