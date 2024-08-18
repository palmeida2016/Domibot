#include <iostream>
#include <algorithm>
#include <random>
#include "game.hpp"
#include "file_utils.cpp"

Game::Game() {}

// Destructor
Game::~Game(){}

void Game::setupGame() {
    std::string filename = "../data/dominion_cards.csv";
    std::vector<std::string> editions = {"Dominion 1st Edition", "Base"};
    allCards = readCardsFromCSV(filename, editions);
    selectKingdomCards();
    // ... set up other game elements ...
}


void Game::selectKingdomCards() {
    // Check if there are enough cards in supply
    if (allCards.size() < 10) {
        std::cerr << "Error: Not enough cards in set to select 10 kingdom cards." << std::endl;
        return;  // Early exit to avoid out-of-bounds access
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allCards.begin(), allCards.end(), g);

    kingdomCards.assign(allCards.begin(), allCards.begin() + 10);
}


void displayKingdomCards(const std::vector<Card>& kingdomCards){
    for (int i = 0; i < kingdomCards.size(); i++)
    {
        std::cout << kingdomCards[i].getName() << std::endl;
    }
}

void Game::start() {
    // std::string edition;
    // std::cout << "Enter the Dominion edition you want to play: ";
    // std::cin >> edition;
    
    setupGame();
    std::cout << "The kingdom cards in this game are: " << std::endl;
    displayKingdomCards(kingdomCards);
    // // Main game loop
    // while (!isGameOver()) {
    //     playTurn();
    //     switchToNextPlayer();
    // }
    
    // announceWinner();
}

int main(int argc, char** argv){
    Game dominion;
    dominion.start();
    return 0;
}