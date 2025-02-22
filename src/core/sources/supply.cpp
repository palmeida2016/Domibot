#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "card.hpp"
#include "supply.hpp"
#include <iostream>

Supply::Supply(const std::vector<Card*>& kingdomCards, const std::vector<Card*>& supplyCards, const int numberOfPlayers) {
    initializeSupply(kingdomCards, supplyCards, numberOfPlayers);
}

// Retrieve a card from the supply
Card* Supply::getCard(const std::string& name){
    if (supplyPiles.find(name) != supplyPiles.end() && !supplyPiles.at(name).empty()) {
        return supplyPiles.at(name).back();
    }
    // Return a default Card or handle the error case
    return new CellarCard();
}

// Remove a card from the supply
void Supply::removeCard(const std::string& name) {
    if (supplyPiles.find(name) != supplyPiles.end() && !supplyPiles[name].empty()) {
        supplyPiles[name].pop_back();
    } else {
        throw std::runtime_error("Cannot remove card: " + name);
    }
}

// Check if a specific card pile is empty
bool Supply::isPileEmpty(const std::string& name) const {
    return ((supplyPiles.find(name) == supplyPiles.end()) || (supplyPiles.at(name).empty()));
}

int Supply::getNumberOfEmptyPiles() {
    int emptyCount = 0;

    for (const auto& pile : supplyPiles) {
        const std::string& cardName = pile.first;
        
        if (isPileEmpty(cardName)) {
            emptyCount++;
        }
    }

    return emptyCount;
}

// Check if the game is over based on empty piles
bool Supply::isGameOver() const {
    return isPileEmpty("Province") || emptyPileCount() >= 3;
    // return false;
}

void Supply::initializeSupply(std::vector<Card*> kingdomCards, std::vector<Card*> supplyCards, int numberOfPlayers) {
    
    // Add basic cards to the supply
    for(auto& card : supplyCards){
        int numCards = 0;
        if (card->getType() == CardType::TREASURE){
            if(card->getName() == "Copper"){
                numCards = 60 - (7 * numberOfPlayers);
            }
            else if (card->getName() == "Silver")
            {
                numCards = 40;
            }
            else{
                numCards = 30;
            }
        }
        else if (card->getType() == CardType::VICTORY){
            if(numberOfPlayers == 2){
                numCards = 8;
            }
            else{
                numCards = 12;
            }
        }
        else{
            numCards = 10 * (numberOfPlayers - 1);
        }
        supplyPiles[card->getName()] = std::vector<Card*>(numCards, card);
    }

    // Shuffle the Kingdom cards
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(kingdomCards.begin(), kingdomCards.end(), g);

    // Select the first 10 Kingdom cards and add them to the supply
    for (size_t i = 0; i < 10 && i < kingdomCards.size(); ++i) {
        const auto& card = kingdomCards[i];
        supplyPiles[card->getName()] = std::vector<Card*>(10, card);
    }
}

// Count the number of empty piles
int Supply::emptyPileCount() const {
    int count = 0;
    for (const auto& pair : supplyPiles) {
        if (pair.second.empty()) {
            ++count;
        }
    }
    return count;
}

std::unordered_map<std::string, std::vector<Card*>> Supply::getSupplyPiles(){
    return supplyPiles;
}


bool Supply::canBuyCard(const std::string& cardName, int coins){
    Card *card = getCard(cardName);
    
    return card->getName() != "" && !isPileEmpty(cardName) && coins >= card->getCost();
}

Card* Supply::buyCard(const std::string& cardName, int coins) {
    if (canBuyCard(cardName, coins)) {
        removeCard(cardName);
        return getCard(cardName);
    }
    else{
        std::cout << "Cannot buy card!" << std::endl;
    }

    throw std::runtime_error("Cannot buy card: " + cardName);
}