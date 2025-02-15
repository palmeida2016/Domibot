#include "game.hpp"
#include "file_utils.hpp"
#include <algorithm>
#include <iostream>
#include <random>

// Constructor
Game::Game() : supply({}, {}, 0) {
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
    for (int i = 0; i < (numPlayers); i++){
        const Player p = Player("Player " + std::to_string(i+1));
        players.push_back(p);
    }

    std::string filename = "../data/dominion_cards_updated.csv";
    std::string kingdom_card_edition = "Base";
    std::string supply_edition = "Common";

    std::vector<Card> kingdomCards = FileUtils::readCardsFromCSV(filename, kingdom_card_edition);
    std::vector<Card> supplyCards = FileUtils::readCardsFromCSV(filename, supply_edition);

    supply = Supply(kingdomCards, supplyCards, numPlayers); // Initialize the supply 

    for (auto& player : players) {
        player.initializeStartingDeck();
    }
}

void displayPiles(const std::unordered_map<std::string, std::vector<Card>> p){
    std::cout << "    Card    |    Amount    |    Cost    |" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    for (auto& pile : p){
        const size_t numSpaces = (16 - pile.first.length());
        const std::string separator = std::string(numSpaces, ' ');
        std::cout << "    " << pile.first <<  separator << pile.second.size() << "          " << pile.second[1].getCost() << std::endl;
    }
}

void displayPlayerState(Player& player){
    std::cout << "Actions: " << player.getActions() << " | Buys: " << player.getBuys() << " | Coins: " << player.getCoins() << std::endl;
}

void Game::playTreasure(Player& player){
    while (player.hasCardType(Card::Type::TREASURE)) {
        displayPlayerState(player);
        player.displayHand();

        char choice;
        std::cout << "Do you want to play a treasure card? (Y/N): ";
        std::cin >> choice;

        if (toupper(choice) == 'Y') {
            std::cout << "Enter the index of the treasure card you want to play: ";
            int cardIndex;
            std::cin >> cardIndex;

            if (cardIndex >= 0 && cardIndex < player.getDeck().getHand().size()) {
                Card& chosenCard = player.getDeck().getHand()[cardIndex];
                if (chosenCard.getType() == Card::Type::TREASURE) {
                    player.playCard(cardIndex);
                } else {
                    std::cout << "That's not a treasure card. Please choose a treasure card." << std::endl;
                }
            } else {
                std::cout << "Invalid card index. Please try again." << std::endl;
            }
        } else {
            break;
        }
    }
}

void Game::actionPhase(Player& player){
    while (player.getActions() > 0 && player.hasCardType(Card::Type::ACTION)) {
        displayPlayerState(player);
        player.displayHand();

        char actionChoice;
        std::cout << "Do you want to play an action card? (Y/N): ";
        std::cin >> actionChoice;

        if (toupper(actionChoice) == 'Y') {
            std::cout << "Enter the index of the action card you want to play: ";
            int cardIndex;
            std::cin >> cardIndex;

            if (cardIndex >= 0 && cardIndex < player.getDeck().getHand().size()) {
                Card& chosenCard = player.getDeck().getHand()[cardIndex];
                if (chosenCard.getType() == Card::Type::ACTION) {
                    player.playCard(cardIndex);
                } else {
                    std::cout << "That's not an action card. Please choose an action card." << std::endl;
                }
            } else {
                std::cout << "Invalid card index. Please try again." << std::endl;
            }
        } else {
            break; // End action phase
        }
    }
}

void Game::buyPhase(Player& player){
    while (player.getBuys() > 0) {
        displayPlayerState(player);

        char buyChoice;
        std::cout << "Do you want to buy a card? (Y/N): ";
        std::cin >> buyChoice;

        if (toupper(buyChoice) == 'Y') {
            std::cout << "Enter the name of the card you want to buy: ";
            std::string cardName;
            std::cin >> cardName;

            if (supply.canBuyCard(cardName, player.getCoins())) {
                Card boughtCard = supply.buyCard(cardName);
                player.buyCard(boughtCard);
                std::cout << "You bought a " << cardName << "!" << std::endl;
            } else {
                std::cout << "You can't buy that card. Please try again." << std::endl;
            }
        } else {
            break; // End buy phase
        }
    }
}

// Play a single turn for a player
void Game::playTurn(Player& player) {

    player.startTurn();
    
    bool turnCompleted = false;
    bool actionCompleted = false;
    bool buysCompleted = false;
    bool endedTurn = false;

    do{
        std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
        std::cout << "Player's turn: " << player.getName() << std::endl << std::endl;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "Options: " << std::endl;
        std::cout << "S - Print Supply Cards" << std::endl;
        std::cout << "K - Print Kingdom Cards" << std::endl;
        std::cout << "H - Print Hand Cards" << std::endl;
        std::cout << "B - Buy cards" << std::endl;
        std::cout << "T - Play treasure cards" << std::endl;
        std::cout << "A - Play action cards" << std::endl;
        std::cout << "E - END TURN" << std::endl;

        char playerInput;
        std::cin >> playerInput;
        std::cout << "\033[2J\033[1;1H";

        if (playerInput == 'S'){
            displayPiles(supply.getSupplyPiles());
        }
        else if (playerInput == 'K'){
            displayPiles(supply.getKingdomPiles());
        }
        else if(playerInput == 'H'){
            player.displayHand();
        }
        else if(playerInput == 'B'){
            buyPhase(player);
            buysCompleted = true;
        }
        else if(playerInput == 'T'){
            playTreasure(player);
        }
        else if(playerInput == 'A'){
            actionPhase(player);
            actionCompleted = true;
        }
        else if(playerInput == 'E'){
            endedTurn = true;
        }
        else{
            std::cout << "Please enter an option from provided list." << std::endl;
        }
        turnCompleted = (endedTurn) || (buysCompleted && actionCompleted) || (player.getDeck().getHand().size() <= 0);
    } while(!turnCompleted);

    player.endTurn();
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
