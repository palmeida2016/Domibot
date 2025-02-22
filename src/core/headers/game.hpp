#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include "player.hpp"
#include "supply.hpp"
#include "card_factory.hpp"

class Game {
public:
    Game();
    ~Game();
    void start();
    void setupGame();
    void determineWinner();
    void actionStep(Player* player);
    void buyStep(Player* player);

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