#include "deck.hpp"
#include <algorithm>
#include <random>

void Deck::shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(drawPile.begin(), drawPile.end(), g);
}

void Deck::draw(int numCards) {
    for (int i = 0; i < numCards; ++i) {
        if (drawPile.empty()) {
            reshuffleDiscardPile();
        }
        if (!drawPile.empty()) {
            hand.push_back(drawPile.back());
            drawPile.pop_back();
        }
    }
}

Card* Deck::drawOne(){
    Card *card;
    if (drawPile.empty()) {
        reshuffleDiscardPile();
    }
    if (!drawPile.empty()) {
        card = drawPile.back();
        hand.push_back(card);
        drawPile.pop_back();
    }
    return card;
}

void Deck::discard(Card *card) {
    for (size_t i = 0; i < hand.size(); i++) {
        if (hand.at(i)->getName() == card->getName()) {
            hand.erase(hand.begin() + i);
            discardPile.push_back(card);
            return;
        }
    }
}

void Deck::discard(int cardIndex) {
    Card *card = hand[cardIndex];
    hand.erase(hand.begin() + cardIndex);
    discardPile.push_back(card);
}

void Deck::addCardToDeck(Card *card) {
    drawPile.push_back(card);
}
void Deck::addCardToDiscardPile(Card *card){
    discardPile.push_back(card);
}

void Deck::addCardToHand(Card *card){
    hand.push_back(card);
}

void Deck::trashCardFromHand(Card *card){
    for (size_t i = 0; i < hand.size(); i++) {
        if (hand.at(i)->getName() == card->getName()) {
            hand.erase(hand.begin() + i);
            return;
        }
    }
}

void Deck::trashCardFromHand(int cardIndex){
    hand.erase(hand.begin() + cardIndex);
}

void Deck::removeFromDiscardPile(Card *card) {
    for (size_t i = 0; i < discardPile.size(); i++) {
        if (discardPile.at(i)->getName() == card->getName()) {
            discardPile.erase(discardPile.begin() + i);
            return;
        }
    }
}

std::vector<Card*> Deck::getHand() const {
    return hand;
}

std::vector<Card*> Deck::getDrawPile() const {
    return drawPile;
}

std::vector<Card*> Deck::getDiscardPile() const {
    return discardPile;
}

void Deck::reshuffleDiscardPile() {
    drawPile = discardPile;
    discardPile.clear();
    shuffle();
}