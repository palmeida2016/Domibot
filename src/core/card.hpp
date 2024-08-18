#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

class Card {
public:
    // Constructor and destructor
    Card();
    ~Card();
    
    // Attributes based on Dominion cards dataset
    std::string getName() const;
    void setName(const std::string& name);

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
    void playCard(); // Implement the card's effect when played
    void onTrashEffect(); // Implement the card's effect when trashed
    void onGainEffect(); // Implement the card's effect when gained

private:
    std::string name;
    std::string set;
    std::vector<std::string> types; // Can hold multiple types
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
    std::string associatedToken;
    std::string associatedToken2;
    std::string associatedMat;
    std::vector<std::string> calledCards;
};

#endif // CARD_H