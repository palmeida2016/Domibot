#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <iostream>
#include "card_effect.hpp"
class Player;
class Game;

enum class CardType { TREASURE, VICTORY, ACTION, CURSE, TRASH };

class Card {
public:
    Card(const std::string& name, const std::string& type, int cost, int actions, int cards, int buys, int coins, int victoryPoints);
    ~Card() = default;
    
    CardEffect getEffect() const { return effect; };
    CardType getType() const { return type; };
    std::string getName() const { return name; }
    int getCost() const { return cost; }
    virtual void play(Player &player, Game &game){return;};

protected:
    std::string name;
    CardType type;
    CardEffect effect;
    int cost;
};

class ActionCard : public Card {
    public:
        ActionCard(const std::string& name, const std::string& type, int cost, int actions, int cards, int buys, int coins, int victoryPoints) : 
            Card(name, type, cost, actions, cards, buys, coins, victoryPoints){};
};

class CellarCard : public Card {
    public:
        CellarCard() : Card("Cellar", "Action", 2, 1, 0, 0, 0, 0){};
        void play(Player &player, Game &game) override;
};

class HarbingerCard : public Card {
    public:
        HarbingerCard() : Card("Harbinger", "Action", 3, 1, 1, 0, 0, 0){};
        void play(Player &player, Game &game) override;
};

class ChapelCard : public Card {
    public:
        ChapelCard() : Card("Chapel", "Action", 2, 0, 0, 0, 0, 0){};
        void play(Player &player, Game &game) override;
};

class LibraryCard : public Card {
    public:
        LibraryCard() : Card("Library", "Action", 5, 0, 0, 0, 0, 0){};
        void play(Player &player, Game &game) override;
};
class MoneylenderCard : public Card {
    public:
        MoneylenderCard() : Card("Moneylender", "Action", 4, 0, 0, 0, 0, 0){};
        void play(Player &player, Game &game) override;
};

class RemodelCard : public Card {
    public:
        RemodelCard() : Card("Remodel", "Action", 4, 0, 0, 0, 0, 0){};
        void play(Player &player, Game &game) override;
};

class PoacherCard : public Card {
    public:
        PoacherCard() : Card("Poacher", "Action", 4, 1, 1, 0, 1, 0){};
        void play(Player &player, Game &game) override;
};

class WorkshopCard : public Card {
    public:
        WorkshopCard() : Card("Workshop", "Action", 3, 0, 0, 0, 0, 0){};
        void play(Player &player, Game &game);
};

class VassalCard : public Card {
    public:
        VassalCard() : Card("Vassal", "Action", 3, 0, 0, 0, 2, 0){};
        void play(Player &player, Game &game);
};

class ArtisanCard : public Card {
    public:
        ArtisanCard() : Card("Artisan", "Action", 6, 0, 0, 0, 0, 0){};
        void play(Player &player, Game &game);
};

class MineCard : public Card {
    public:
        MineCard() : Card("Mine", "Action", 5, 0, 0, 0, 0, 0){};
        void play(Player &player, Game &game);
};

class ThroneRoomCard : public Card {
    public:
        ThroneRoomCard() : Card("Throne Room", "Action", 4, 0, 0, 0, 0, 0){};
        void play(Player &player, Game &game);
};
// class AttackCard : public Card {
// public:
//     AttackCard(const std::string& name, const std::string& type, int cost, int actions, int cards, int buys, int coins, int victoryPoints);
//     void play();
// };

#endif