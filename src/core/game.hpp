#include <string>
#include <vector>
#include "card.hpp"

class Game {
public:
    Game();
    void start();
    void setupGame();
    void selectKingdomCards();
    // ... other game methods ...

private:
    std::vector<Card> allCards;
    std::vector<Card> kingdomCards;
    // ... other game state variables ...
};