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

void Game::actionPhase(Player& player) {
    while (player.getActions() > 0 && player.hasCardType(CardType::ACTION)) {
        displayPlayerState(player);
        player.displayHand();
        
        std::cout << "Choose an action card to play (0-" << player.getDeck().getHand().size()-1 
                  << ") or -1 to end action phase: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == -1) break;
        
        if (choice >= 0 && choice < static_cast<int>(player.getDeck().getHand().size())) {
            Card& card = player.getDeck().getHand()[choice];
            if (card.getType() == CardType::ACTION) {
                CardEffect effect = card.getEffect();
                player.applyCardEffect(effect);
                
                // Handle attack effects if present
                if (effect.attackEffect.type != AttackType::NONE) {
                    applyAttackEffect(player, effect.attackEffect);
                }
                
                player.addActions(-1);
            } else {
                std::cout << "Selected card is not an action card!" << std::endl;
            }
        }
    }
}

void Game::applyAttackEffect(Player& attacker, const AttackEffect& effect) {
    for (auto& player : players) {
        // Skip the attacking player
        if (&player == &attacker) continue;

        switch (effect.type) {
            case AttackType::DISCARD:
                for (int i = 0; i < effect.value; ++i) {
                    if (!player.getDeck().getHand().empty()) {
                        // Let player choose a card to discard
                        std::cout << player.getName() << ", choose a card to discard:" << std::endl;
                        player.displayHand();
                        int choice;
                        std::cin >> choice;
                        if (choice >= 0 && choice < static_cast<int>(player.getDeck().getHand().size())) {
                            player.getDeck().discard(player.getDeck().getHand()[choice]);
                        }
                    }
                }
                break;

            case AttackType::DRAW:
                player.getDeck().draw(effect.value);
                break;

            case AttackType::GAIN_CURSE:
                if (!supply.isPileEmpty("Curse")) {
                    Card curse = supply.buyCard("Curse");
                    player.getDeck().addCardToDeck(curse);
                }
                break;

            case AttackType::REVEAL_CARDS:
                // Implementation for revealing cards
                break;
            default:
                break;
        }
    }
}

int main(){
    Game dominion;
    dominion.start();
}
