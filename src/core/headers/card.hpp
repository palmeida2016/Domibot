#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>


class Card {
public:
    enum class Type { TREASURE, VICTORY, ACTION, CURSE, TRASH };

    // Constructor
    Card(const std::string& name, Type type, int cost);

    // Destructor
    ~Card();

    // Getters and Setters
    std::string getName() const;
    void setName(const std::string& name);

    Type getType() const;

    std::string getSet() const;
    void setSet(const std::string& set);

    std::vector<std::string> getTypes() const;
    void addType(const std::string& type);

    int getCost() const;
    void setCost(int cost);

    int getAdditionalCost() const;
    void setAdditionalCost(int additionalCost);

    int getNumberOfCards() const;
    void setNumberOfCards(int numberOfCards);

    bool isModifyCost() const;
    void setModifyCost(bool modifyCost);

    bool isInSupply() const;
    void setInSupply(bool inSupply);

    bool getHasTrashEffect() const;
    void setHasTrashEffect(bool hasTrashEffect);

    bool getHasGainEffect() const;
    void setHasGainEffect(bool hasGainEffect);

    // Special functions
    void playCard();
    void onTrashEffect();
    void onGainEffect();
    
    // Define the equality operator
    bool operator==(const Card& other) const {
        return name == other.name;  // Compare the attributes you care about
    }

private:
    std::string name;
    Type type;
    int cost;
    int additionalCost;
    int numberOfCards;
    bool modifyCost;
    bool inSupply;
    bool hasTrashEffect;
    bool hasGainEffect;
    bool trasher;
    bool specialSetup;
    int curseCost;
    bool costReducer;
    std::string set;
    std::vector<std::string> types;
};

#endif
