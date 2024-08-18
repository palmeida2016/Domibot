#ifndef SUPPLY_HPP
#define SUPPLY_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include "card.hpp"

class Supply {
public:
    Supply(const std::vector<Card>& kingdomCards);

    Card getCard(const std::string& name);
    void removeCard(const std::string& name);
    bool isPileEmpty(const std::string& name) const;
    bool isGameOver() const;

private:
    std::unordered_map<std::string, std::vector<Card>> piles;

    void initializeSupply(const std::vector<Card>& kingdomCards);
    int emptyPileCount() const;
};

#endif
