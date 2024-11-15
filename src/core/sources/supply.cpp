#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "card.hpp"
#include "supply.hpp"
// Constructor that initializes the supply with the given Kingdom cards
Supply::Supply(const std::vector<Card>& kingdomCards) {
    initializeSupply(kingdomCards);
}

// Retrieve a card from the supply
Card Supply::getCard(const std::string& name){
    if (kingdomPiles.find(name) != kingdomPiles.end() && !kingdomPiles.at(name).empty()) {
        return kingdomPiles.at(name).back();
    }
    if (supplyPiles.find(name) != supplyPiles.end() && !supplyPiles.at(name).empty()) {
        return supplyPiles.at(name).back();
    }
    // Return a default Card or handle the error case
    return Card("", Card::Type::ACTION, 0);
}

// Remove a card from the supply
void Supply::removeCard(const std::string& name) {
    if (kingdomPiles.find(name) != kingdomPiles.end() && !kingdomPiles[name].empty()) {
        kingdomPiles[name].pop_back();
    } else if (supplyPiles.find(name) != supplyPiles.end() && !supplyPiles[name].empty()) {
        supplyPiles[name].pop_back();
    } else {
        throw std::runtime_error("Cannot remove card: " + name);
    }
}

// Check if a specific card pile is empty
bool Supply::isPileEmpty(const std::string& name) const {
    return ((supplyPiles.find(name) == supplyPiles.end()) && (kingdomPiles.find(name) == kingdomPiles.end())) || (supplyPiles.at(name).empty() && kingdomPiles.at(name).empty());
}

// Check if the game is over based on empty piles
bool Supply::isGameOver() const {
    return isPileEmpty("Province") || emptyPileCount() >= 3;
}

void Supply::initializeSupply(std::vector<Card> kingdom) {
    // Add basic cards to the supply
    supplyPiles["Copper"] = std::vector<Card>(60, Card("Copper", Card::Type::TREASURE, 0));
    supplyPiles["Silver"] = std::vector<Card>(40, Card("Silver", Card::Type::TREASURE, 3));
    supplyPiles["Gold"] = std::vector<Card>(30, Card("Gold", Card::Type::TREASURE, 6));
    supplyPiles["Estate"] = std::vector<Card>(8, Card("Estate", Card::Type::VICTORY, 1));
    supplyPiles["Duchy"] = std::vector<Card>(8, Card("Duchy", Card::Type::VICTORY, 3));
    supplyPiles["Province"] = std::vector<Card>(8, Card("Province", Card::Type::VICTORY, 6));
    supplyPiles["Curse"] = std::vector<Card>(10, Card("Curse", Card::Type::CURSE, -1));


    // Shuffle the Kingdom cards
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(kingdom.begin(), kingdom.end(), g);

    // Select the first 10 Kingdom cards and add them to the supply
    for (size_t i = 0; i < 10 && i < kingdom.size(); ++i) {
        const auto& card = kingdom[i];
        kingdomPiles[card.getName()] = std::vector<Card>(10, card);
    }
}

// Count the number of empty piles
int Supply::emptyPileCount() const {
    int count = 0;
    for (const auto& pair : kingdomPiles) {
        if (pair.second.empty()) {
            ++count;
        }
    }
    return count;
}

std::unordered_map<std::string, std::vector<Card>> Supply::getSupplyPiles(){
    return supplyPiles;
}

std::unordered_map<std::string, std::vector<Card>> Supply::getKingdomPiles(){
    return kingdomPiles;
}


bool Supply::canBuyCard(const std::string& cardName, int coins){
    Card card = getCard(cardName);
    // Check if the card exists (not a default card) and the player has enough coins
    return card.getName() != "" && coins >= card.getCost();
}

Card Supply::buyCard(const std::string& cardName) {
    Card card = getCard(cardName);
    if (card.getName() != "") {
        removeCard(cardName);
        return card;
    }
    // If we get here, the card couldn't be bought
    throw std::runtime_error("Cannot buy card: " + cardName);
}