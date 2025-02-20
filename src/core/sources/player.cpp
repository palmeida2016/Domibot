#include "player.hpp"
#include <iostream>
#include <vector> 

Player::Player(std::string name) : name(name), actions(1), buys(1), coins(0) {
    // Initialize the player's deck with starting cards
    this->points = 0;
    initializeStartingDeck();
}

void Player::initializeStartingDeck() {
    for (int i = 0; i < 7; ++i) {
        deck.addCardToDeck(Card("Copper", "Treasure", 0, 0, 0, 0, 1, 0));
    }
    for (int i = 0; i < 3; ++i) {
        deck.addCardToDeck(Card("Estate", "Victory", 2, 0, 0, 0, 0, 1));
        this->addVictoryPoints(1);
    }
    deck.shuffle();
}

void Player::startTurn() {
    this->actions = 1;
    this->buys = 1;
    this->coins = 0;

    this->deck.draw(5);
}

bool Player::hasCardType(CardType type){
    for (const auto& card: this->deck.getHand()){
        if (card.getType() == type) {
            return true;
        }
    }
    return false;
}

void Player::applyCardEffect(const CardEffect& effect) {
    this->actions += effect.actions;
    this->coins += effect.coins;
    this->buys += effect.buys;
    if (effect.cards > 0) {
        this->deck.draw(effect.cards);
    }
}

void Player::playCard(size_t cardIndex) {
    if (cardIndex >= deck.getHand().size() || cardIndex < 0) {
        throw std::out_of_range("Invalid card index");
    }

    Card& card = deck.getHand()[cardIndex];
    
    // Apply the card's effect
    CardEffect effect = card.getEffect();
    applyCardEffect(effect);

    if(effect.attackEffect.type != AttackType::NONE){
        std::cout << "Playing attack card: " << card.getName() << std::endl;
    }

    // Move card to discard pile
    deck.discard(card);
}

void Player::buyCard(Card card) {
    // Ensure player has enough coins and buys
    if (this->coins >= card.getCost() && this->buys > 0) {
        this->deck.addCardToDeck(card);
        --buys;
        this->coins -= card.getCost();
    }
}

void Player::endTurn() {
    // Discard remaining hand
    for (auto& card : this->deck.getHand()) {
        deck.discard(card);
    }
}

void Player::displayHand(){
    std::cout << "------------------------"<< std::endl;
    std::cout << "Your Hand: " << std::endl;
    for(int i = 0; i < deck.getHand().size(); i++){
        std::cout << "Index " << i << ": " << deck.getHand()[i].getName() << std::endl;
    }
    std::cout << "------------------------"<< std::endl;
    std::cout << std::endl;
}