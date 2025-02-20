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

void Deck::discard(Card card) {
    for (size_t i = 0; i < hand.size(); i++) {
        if (hand[i].getName() == card.getName()) {
            hand.erase(hand.begin() + i);
            discardPile.push_back(card);
            return;
        }
    }
}

void Deck::addCardToDeck(Card card) {
    drawPile.push_back(card);
}

std::vector<Card> Deck::getHand() const {
    return hand;
}

std::vector<Card> Deck::getDrawPile() const {
    return drawPile;
}

std::vector<Card> Deck::getDiscardPile() const {
    return discardPile;
}

void Deck::reshuffleDiscardPile() {
    drawPile = discardPile;
    discardPile.clear();
    shuffle();
}