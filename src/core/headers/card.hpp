#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>


class Card {
public:
    enum class Type { TREASURE, VICTORY, ACTION, CURSE, TRASH };

    // Constructor
    Card(const std::string& name, const std::string& set, Type type, bool isAttack, int cost, int actions, int cards, int discards, int buys, int coins, int trash, int victoryPoints, bool hasPlayEffect);
    Card();
    // Destructor
    ~Card();

    std::string getName() const;
    std::string getSet() const;
    Type getType() const;
    bool getIsAttack() const;
    int getCost() const;
    int getActions() const;
    int getCards() const;
    int getDiscards() const;
    int getBuys() const;
    int getCoins() const;
    int getTrash() const;
    int getVictoryPoints() const;
    bool getHasPlayEffect() const;

    // Special functions
    void playCard();
    
    // Define the equality operator
    bool operator==(const Card& other) const {
        return name == other.name;  // Compare the attributes you care about
    }

private:
    std::string name;
    Type type;
    bool isAttack;
    int cost;
    int actions;
    int cards;
    int discards;
    int buys;
    int coins;
    int trash;
    int victoryPoints;
    bool hasPlayEffect;

    std::string set;
    std::vector<std::string> types;
};

#endif
