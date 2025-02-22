#ifndef CARD_EFFECT_HPP
#define CARD_EFFECT_HPP

class CardEffect {
public:
    CardEffect(int actions = 0, 
              int cards = 0, 
              int buys = 0, 
              int coins = 0, 
              int victoryPoints = 0)
        : actions(actions), cards(cards), buys(buys), coins(coins), 
          victoryPoints(victoryPoints) {}

    int actions;
    int cards;
    int buys;
    int coins;
    int victoryPoints;
};

#endif 