#include "player.hpp"
#include <iostream>
#include <vector> 

Player::Player(std::string name) : name(name), actions(1), buys(1), coins(0) {
    // Initialize the player's deck with starting cards
    initializeStartingDeck();
}

void Player::initializeStartingDeck() {
    for (int i = 0; i < 7; ++i) {
        deck.addCardToDeck(Card("Copper", Card::Type::TREASURE, 0));
    }
    for (int i = 0; i < 3; ++i) {
        deck.addCardToDeck(Card("Estate", Card::Type::VICTORY, 2));
    }
    deck.shuffle();
}

void Player::startTurn() {
    actions = 1;
    buys = 1;
    coins = 0;

    deck.draw(5);
}

bool Player::hasActionCards(){
    for (const auto& card: deck.getHand()){
        if (card.getType() == Card::Type::ACTION) {
            return true;
        }
    }
    return false;
}

void Player::playCard(int cardIndex) {
    // Play a card from hand
    Card card = deck.getHand()[cardIndex];
    // TODO: Implement card effects

    // After playing, remove from hand and discard
    deck.discard(card);
}

void Player::buyCard(Card card) {
    // Ensure player has enough coins and buys
    if (coins >= card.getCost() && buys > 0) {
        deck.addCardToDeck(card);
        --buys;
        coins -= card.getCost();
    }
}

void Player::endTurn() {
    // Discard remaining hand
    for (auto& card : deck.getHand()) {
        deck.discard(card);
    }
}

int Player::getActions() { return actions; }
int Player::getBuys() { return buys; }
int Player::getCoins() { return coins; }
std::string Player::getName() { return name; }

void Player::addCoins(int amount) { coins += amount; }
void Player::addActions(int amount) { actions += amount; }
void Player::addBuys(int amount) { buys += amount; }

int getVP(Card card){
    int output = 0;
    if(card.getName() == "Estate"){
        output = 1;
    }
    else if(card.getName() == "Duc"){
        output = 3;
    }
    else if (card.getName() == "Province"){
        output = 6;
    }
    return output;
}

int Player::getScore() {
    int score = 0;
    for (const auto& card : deck.getDrawPile()) {
        if (card.getType() == Card::Type::VICTORY) {
            score += getVP(card);
        }
    }
    for (const auto& card : deck.getDiscardPile()) {
        if (card.getType() == Card::Type::VICTORY) {
            score += getVP(card);
        }
    }
    // Optionally, add hand cards to score calculation
    // for (const auto& card : deck.getHand()) {
    //     if (card.getType() == Type::VICTORY) {
    //         score += card.getVictoryPoints();
    //     }
    // }
    return score;
}

Deck& Player::getDeck() {
    return deck;
}

void Player::displayHand(){
    for(int i = 0; i < deck.getHand().size(); i++){
        std::cout << deck.getHand()[i].getName() << ", ";
    }
}