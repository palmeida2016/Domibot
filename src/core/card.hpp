#include <string>
#ifndef CARD_H
#define CARD_H

namespace Card{

class Card {
    public:
        // Constructors
        Card();

        // Access functions
        std::string getName(); 
        int getCost();
        int getType();

    private:
        std::string name;
        int cost;
        int type;

};

}
#endif