#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include "card.hpp"

class Deck {
public:
    void shuffle();
    void draw(int numCards);
    void discard(Card card);
    void addCardToDeck(Card card);

    std::vector<Card> getDrawPile() const;
    std::vector<Card> getDiscardPile() const;
    std::vector<Card> getHand() const;

private:
    std::vector<Card> drawPile;
    std::vector<Card> discardPile;
    std::vector<Card> hand;
    void reshuffleDiscardPile();
};


#endif