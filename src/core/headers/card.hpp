#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <iostream>
#include "card_effect.hpp"

enum class CardType { TREASURE, VICTORY, ACTION, CURSE, TRASH };

class Card {
public:
    Card(const std::string& name, const std::string& type, int cost, int actions, int cards, int buys, int coins, int victoryPoints);
    ~Card() = default;
    
    CardEffect getEffect() const { return effect; };

    CardType getType() const { return type; };
    std::string getName() const { return name; }
    int getCost() const { return cost; }

protected:
    std::string name;
    CardType type;
    CardEffect effect;
    int cost;
};

class AttackCard : public Card {
public:
    AttackCard(const std::string& name, const std::string& type, int cost, int actions, int cards, int buys, int coins, int victoryPoints);
    void play();
};

#endif