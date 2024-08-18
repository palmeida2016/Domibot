#include <vector>
#include <string>
#include "card.hpp"
#include "supply.hpp"
// Constructor that initializes the supply with the given Kingdom cards
Supply::Supply(const std::vector<Card>& kingdomCards) {
    initializeSupply(kingdomCards);
}

// Retrieve a card from the supply
Card Supply::getCard(const std::string& name) {
    if (piles.find(name) != piles.end() && !piles[name].empty()) {
        return piles[name].back();
    }
    // Return a default Card or handle the error case
    return Card("", Card::Type::ACTION, 0); // Example default Card
}

// Remove a card from the supply (e.g., after a player buys it)
void Supply::removeCard(const std::string& name) {
    if (piles.find(name) != piles.end() && !piles[name].empty()) {
        piles[name].pop_back();
    }
}

// Check if a specific card pile is empty
bool Supply::isPileEmpty(const std::string& name) const {
    return piles.find(name) == piles.end() || piles.at(name).empty();
}

// Check if the game is over based on empty piles
bool Supply::isGameOver() const {
    return isPileEmpty("Province") || emptyPileCount() >= 3;
}

// Initialize the supply with standard and Kingdom cards
void Supply::initializeSupply(const std::vector<Card>& kingdomCards) {
    // Add basic cards to the supply
    piles["Copper"] = std::vector<Card>(60, Card("Copper", Card::Type::TREASURE, 0));
    piles["Silver"] = std::vector<Card>(40, Card("Silver", Card::Type::TREASURE, 3));
    piles["Gold"] = std::vector<Card>(30, Card("Gold", Card::Type::TREASURE, 6));
    piles["Estate"] = std::vector<Card>(8, Card("Estate", Card::Type::VICTORY, 1));
    piles["Duchy"] = std::vector<Card>(8, Card("Duchy", Card::Type::VICTORY, 3));
    piles["Province"] = std::vector<Card>(8, Card("Province", Card::Type::VICTORY, 6));
    piles["Curse"] = std::vector<Card>(10, Card("Curse", Card::Type::CURSE, -1));

    // Add Kingdom cards to the supply
    for (const auto& card : kingdomCards) {
        piles[card.getName()] = std::vector<Card>(10, card); // Example count
    }
}

// Count the number of empty piles
int Supply::emptyPileCount() const {
    int count = 0;
    for (const auto& pair : piles) {
        if (pair.second.empty()) {
            ++count;
        }
    }
    return count;
}
