#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include "card.hpp"
#include "supply.hpp"
#include "player.hpp"

class Game {
public:
    Game();
    ~Game();
    void start();
    void setupGame();
    void determineWinner();
    void actionPhase(Player& player);
    void playTreasure(Player& player);
    void buyPhase(Player& player);
    // void selectKingdomCards();
    // ... other game methods ...

private:
    std::vector<Player> players;
    Supply supply;
    void playTurn(Player& player);
    bool checkEndConditions();
};

#endif