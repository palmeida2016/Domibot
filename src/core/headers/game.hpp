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
    void actionPhase(Player* player);
    void playTreasure(Player* player);
    void buyPhase(Player* player);

    std::vector<Player*> getOtherPlayers(Player *player);
    Supply getSupply() {return supply;};
    void displayPiles(const std::vector<CardType>& types = {CardType::TREASURE, CardType::VICTORY, CardType::CURSE, CardType::ACTION});

private:
    std::vector<Player*> players;
    Supply supply;
    void playTurn(Player* player);
    bool checkEndConditions();
};

#endif