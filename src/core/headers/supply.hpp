#ifndef SUPPLY_HPP
#define SUPPLY_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include "card.hpp"

class Supply {
public:
    Supply(const std::vector<Card>& kingdomCards, const std::vector<Card>& supplyCards, const int numberOfPlayers);

    Card getCard(const std::string& name);
    void removeCard(const std::string& name);
    bool isPileEmpty(const std::string& name) const;
    bool isGameOver() const;

    bool canBuyCard(const std::string& cardName, int coins);
    Card buyCard(const std::string& cardName);

    std::unordered_map<std::string, std::vector<Card>> getSupplyPiles();
    std::unordered_map<std::string, std::vector<Card>> getKingdomPiles();

private:
    std::unordered_map<std::string, std::vector<Card>> supplyPiles;
    std::unordered_map<std::string, std::vector<Card>> kingdomPiles;

    void initializeSupply(std::vector<Card> kingdomCards, std::vector<Card> supplyCards, int numberOfPlayers);
    int emptyPileCount() const;
};

#endif
