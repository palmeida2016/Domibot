#include "card.hpp"

// Constructor
Card::Card(const std::string& name, const std::string& set, Type type, bool isAttack, int cost, int actions, int cards, int discards, int buys, int coins, int trash, int victoryPoints, bool hasPlayEffect)
    : name(name), set(set), type(type), isAttack(isAttack), cost(cost), actions(actions), cards(cards), discards(discards), buys(buys), coins(coins), trash(trash), victoryPoints(victoryPoints), hasPlayEffect(hasPlayEffect){}

// Destructor
Card::~Card() {}

// Getter and Setter implementations

std::string Card::getName() const {
    return name;
}

std::string Card::getSet() const {
    return set;
}

Card::Type Card::getType() const {
    return type;
}

bool Card::getIsAttack() const {
    return isAttack;
}

int Card::getCost() const {
    return cost;
}
int Card::getActions() const {
    return actions;
}
int Card::getCards() const {
    return cards;
}
int Card::getDiscards() const {
    return discards;
}
int Card::getBuys() const {
    return buys;
}
int Card::getCoins() const {
    return coins;
}
int Card::getTrash() const {
    return trash;
}
int Card::getVictoryPoints() const {
    return victoryPoints;
}
bool Card::getHasPlayEffect() const {
    return hasPlayEffect;
}

// Special functions
void Card::playCard() {
    // Implementation of card's effect when played
}
