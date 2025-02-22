#include "player.hpp"
#include <iostream>
#include <vector> 

Player::Player(std::string name) : name(name), actions(1), buys(1), coins(0) {
    this->deck = new Deck();
    this->hasMerchantEffect = false;

    // Initialize the player's deck with starting cards
    initializeStartingDeck();
}

void Player::initializeStartingDeck() {
    for (int i = 0; i < 7; ++i) {
        Card *newCard = new Card("Copper", "Treasure", 0, 0, 0, 0, 1, 0);
        deck->addCardToDeck(newCard);
    }
    for (int i = 0; i < 3; ++i) {
        // Card *newCard = new Card("Estate", "Victory", 2, 0, 0, 0, 0, 1);
        MilitiaCard *newCard = new MilitiaCard();

        deck->addCardToDeck(newCard);

    }
    // WorkshopCard *newCard = new WorkshopCard();
    // deck.addCardToDeck(newCard);
    deck->shuffle();
}

void Player::startTurn() {
    this->actions = 1;
    this->buys = 1;
    this->coins = 0;
    this->hasMerchantEffect = false;
}

bool Player::hasCardType(CardType type){
    for (const auto& card: this->deck->getHand()){
        if (card->getType() == type) {
            return true;
        }
    }
    return false;
}
bool Player::hasCard(std::string cardName){
    for (const auto& card: this->deck->getHand()){
        if (card->getName() == cardName) {
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
        this->deck->draw(effect.cards);
    }
}


void Player::buyCard(Card *card) {
    // Ensure player has enough coins and buys
    if (this->coins >= card->getCost() && this->buys > 0) {
        this->deck->addCardToDeck(card);
        --buys;
        this->coins -= card->getCost();
    }
}

void Player::endTurn() {
    // Discard remaining hand
    for (auto& card : this->deck->getHand()) {
        deck->discard(card);
    }
    this->hasMerchantEffect = false;
}

int Player::calculateScore(){
    int score = 0;

    std::vector<Card*> discardPile = this->getDeck()->getDiscardPile();
    std::vector<Card*> drawPile = this->getDeck()->getDrawPile();
    std::vector<Card*> hand = this->getDeck()->getHand();
    std::vector<std::vector<Card*>> allPiles = {discardPile, drawPile, hand};

    for (std::vector<Card*> pile : allPiles) {
        for (Card *card: pile){
            if (card->getType() == CardType::VICTORY || card->getType() == CardType::CURSE){
                if(card->getName() == "Gardens"){
                    int totalCards = discardPile.size() + drawPile.size() + hand.size();
                    score += totalCards / 10;
                }
                else{
                    score += card->getEffect().victoryPoints;
                }
            }
        }
    }


    return score;
}

void Player::displayHand(){
    std::cout << "------------------------"<< std::endl;
    std::cout << "Your Hand: " << std::endl;
    for(int i = 0; i < deck->getHand().size(); i++){
        std::cout << "Index " << i << ": " << deck->getHand()[i]->getName() << std::endl;
    }
    std::cout << "------------------------"<< std::endl;
    std::cout << std::endl;
}

void Player::displayDiscardPile(){
    std::cout << "------------------------"<< std::endl;
    std::cout << "Your Discard Pile: " << std::endl;
    for(int i = 0; i < deck->getDiscardPile().size(); i++){
        std::cout << "Index " << i << ": " << deck->getDiscardPile()[i]->getName() << std::endl;
    }
    std::cout << "------------------------"<< std::endl;
    std::cout << std::endl;
}