#include "game.hpp"
#include "file_utils.hpp"
#include <algorithm>
#include <iostream>
#include <random>

// Constructor
Game::Game() : supply({}) {
}

// Destructor
Game::~Game() {
}

// Start the game
void Game::start() {
    setupGame();
    while (!checkEndConditions()) {
        for (auto& player : players) {
            playTurn(player);
            if (checkEndConditions()) {
                break; // Exit if game end conditions are met during a turn
            }
        }
    }
    determineWinner();
}

void Game::setupGame() {
    int numPlayers;
    std::cout << "Enter the number of players (2-4): ";
    std::cin >> numPlayers;
    // Initialize the players
    for (int i = 1; i < (numPlayers); i++){
        const Player p = Player("Player " + std::to_string(i));
        players.push_back(p);
    }

    // Initialize the supply with kingdom cards
    std::string filename = "data/dominion_cards.csv";
    std::vector<std::string> kingdom_card_editions = {"Dominion 1st Edition"};
    std::vector<std::string> base_supply_editions = {"Base"};

    std::vector<Card> kingdomCards = FileUtils::readCardsFromCSV(filename, kingdom_card_editions); // Assuming this function reads the cards

    supply = Supply(kingdomCards); // Initialize the supply with kingdom cards

    // Example: Set up other game components, such as dealing initial cards to players
    for (auto& player : players) {
        // Example: give each player a starting deck
        player.initializeStartingDeck(); // Implement this function in the Player class
    }

    // Additional setup logic...
}

// Play a single turn for a player
void Game::playTurn(Player& player) {
    std::cout << "Player's turn: " << player.getName() << std::endl;
    // Example: Execute player's actions, buys, and end of turn processing
    // player.takeTurn(); // Implement this function in the Player class
}

// Check if the game end conditions are met
bool Game::checkEndConditions() {
    return supply.isGameOver(); // Example end condition; adjust based on your rules
}

// Determine and announce the winner
void Game::determineWinner() {
    // Example: Find the player with the highest score
    Player* winner = &players[0];
    for (auto& player : players) {
        if (player.getScore() > winner->getScore()) { // Implement getScore() in the Player class
            winner = &player;
            std::cout << "The winner is: " << winner->getName() << " with a score of: " << winner->getScore() << std::endl;

        }
        else if(player.getScore() == winner->getScore()){
            std::cout << "Both players tied with a score of: " << player.getScore() << std::endl;
        }
    }
}

int main(){
    Game dominion;
    dominion.start();
}
