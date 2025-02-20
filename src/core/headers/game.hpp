#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include "player.hpp"
#include "supply.hpp"

class Game {
public:
    Game();
    ~Game();
    void start();
    void setupGame();
    void determineWinner();
    void actionPhase(Player& player);
    void applyAttackEffect(Player& attacker, const AttackEffect& effect);
    void playTreasure(Player& player);
    void buyPhase(Player& player);

private:
    std::vector<Player> players;
    Supply supply;
    void playTurn(Player& player);
    bool checkEndConditions();
};

#endif