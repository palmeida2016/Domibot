#include "game.hpp"
#include <algorithm>
#include <iostream>

// Constructor
Game::Game() : supply({}, {}, 0) {
}

// Destructor
Game::~Game() {
}

// Start the game
void Game::start() {
    setupGame();
    for (auto& player : players){
        player->getDeck()->draw(5);
    }
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
        Player *p = new Player("Player " + std::to_string(i+1));
        players.push_back(p);
    }

    CardFactory& factory = CardFactory::getInstance();

    std::vector<Card*> kingdomCards = factory.createAllKingdomCards();
    std::vector<Card*> supplyCards = factory.createSupplyCards();

    supply = Supply(kingdomCards, supplyCards, numPlayers); // Initialize the supply 
}

void Game::displayPiles(const std::vector<CardType>& types){
    std::cout << "----------------- Supply ---------------" << std::endl;
    std::cout << "|    Card    |    Cost    |    Amount    |" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    for (auto& type: types){
        for (auto& pile : supply.getSupplyPiles()){
            if(pile.second[1]->getType() == type){
                const size_t numSpaces = (16 - pile.first.length());
                const std::string separator = std::string(numSpaces, ' ');
                std::cout << "    " << pile.first <<  separator << pile.second[1]->getCost() << "          " << pile.second.size() << std::endl;
            }
        }
    }
}

void displayPlayerState(Player& player){
    std::cout << "Actions: " << player.getActions() << " | Buys: " << player.getBuys() << " | Coins: " << player.getCoins() << std::endl;
}

// Play a single turn for a player
void Game::playTurn(Player* player) {  
    player->startTurn();
  
    bool turnCompleted = false;
    bool endedTurn = false;

    do{
        std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
        std::cout << "Player's turn: " << player->getName() << std::endl << std::endl;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "Options: " << std::endl;
        std::cout << "S - Print Supply Cards" << std::endl;
        std::cout << "H - Print Hand Cards" << std::endl;
        std::cout << "B - Buy a card" << std::endl;
        std::cout << "P - Play a card" << std::endl;
        std::cout << "E - END TURN" << std::endl;

        char playerInput;
        std::cin >> playerInput;
        std::cout << "\033[2J\033[1;1H";

        if (playerInput == 'S'){
            displayPiles();
        }
        else if(playerInput == 'H'){
            player->displayHand();
        }
        else if(playerInput == 'B'){
            buyStep(player);
        }
        else if(playerInput == 'P'){
            actionStep(player);
        }
        else if(playerInput == 'E'){
            endedTurn = true;
        }
        else{
            std::cout << "Please enter an option from provided list." << std::endl;
        }
        turnCompleted = (endedTurn) || (player->getBuys() <= 0 && player->getActions() <= 0);
    } while(!turnCompleted);

    player->endTurn();
    player->getDeck()->draw(5);
}

// Check if the game end conditions are met
bool Game::checkEndConditions() {
    return supply.isGameOver(); // Example end condition; adjust based on your rules
}

std::vector<Player*> Game::getOtherPlayers(Player *player) {
    std::vector<Player*> playerList;
    for (auto& p: this->players){
        if (p->getName() != player->getName()){
            playerList.push_back(p);
        }
    }
    return playerList;
}

// Determine and announce the winner
void Game::determineWinner() {
    Player* winner = players[0];
    for (auto& player : players) {
        if (player->calculateScore() > winner->calculateScore()) {
            winner = player;
            std::cout << "The winner is: " << winner->getName() << " with a score of: " << winner->calculateScore() << std::endl;

        }
        else if(player->calculateScore() == winner->calculateScore()){
            std::cout << "Both players tied with a score of: " << player->calculateScore() << std::endl;
        }
    }
}

void Game::buyStep(Player* player) {
    displayPlayerState(*player);
    if (player->getBuys() > 0) {
        if(player->getCoins() > 0){  
            displayPiles();

            std::cout << "Enter the name of the card you want to purchase (or enter -1 to go back): ";
            
            std::string cardName;
            std::cin >> cardName;
            
            if (cardName == "-1") return;
            
            Card *boughtCard = supply.buyCard(cardName, player->getCoins());
            player->getDeck()->addCardToDiscardPile(boughtCard);

        }
        else{
            std::cout << "You have no coins remaining this turn!" << std::endl;
        }
    }
    else{
        std::cout << "You have no buys remaining for this turn!" << std::endl;
    }
}

void Game::actionStep(Player* player) {
    while (player->hasCardType(CardType::TREASURE) || (player->getActions() > 0 && player->hasCardType(CardType::ACTION))) {
        displayPlayerState(*player);
        player->displayHand();
        
        std::cout << "Choose a card to play (0-" << player->getDeck()->getHand().size()-1 
                  << ") or -1 to go back: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == -1) break;
        
        if (choice >= 0 && choice < static_cast<int>(player->getDeck()->getHand().size())) {
            Card *card = player->getDeck()->getHand().at(choice);
            if (card->getType() == CardType::ACTION || card->getType() == CardType::TREASURE) {

                card->play(player, *this);
                if(card->getType() == CardType::ACTION){
                    player->addActions(-1);
                }
            } else {
                std::cout << "Selected card is not playable!" << std::endl;
            }
        }
    }
}

int main(){
    Game dominion;
    dominion.start();
}
