#include <iostream>
#include <algorithm>
#include <random>
#include "game.hpp"
#include "file_utils.cpp"

void Game::setupGame() {
    std::string filename = "data/dominion_cards.csv";
    std::vector<std::string> editions = {"Base"};
    allCards = readCardsFromCSV(filename, editions);
    selectKingdomCards();
    // ... set up other game elements ...
}


void Game::selectKingdomCards() {
    std::vector<Card> supplyCards;
    for (const auto& card : allCards) {
        if (card.isInSupply()) {
            supplyCards.push_back(card);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(supplyCards.begin(), supplyCards.end(), g);

    kingdomCards.assign(supplyCards.begin(), supplyCards.begin() + 10);
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

int main() {
    Game dominion;
    dominion.start();
    return 0;
}