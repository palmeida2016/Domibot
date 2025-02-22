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
    void play(Player *player, Game &game);

protected:
    std::string name;
    CardType type;
    CardEffect effect;
    int cost;
};

class CellarCard : public Card {
    public:
        CellarCard() : Card("Cellar", "Action", 2, 1, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class HarbingerCard : public Card {
    public:
        HarbingerCard() : Card("Harbinger", "Action", 3, 1, 1, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class ChapelCard : public Card {
    public:
        ChapelCard() : Card("Chapel", "Action", 2, 0, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class LibraryCard : public Card {
    public:
        LibraryCard() : Card("Library", "Action", 5, 0, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};
class MoneylenderCard : public Card {
    public:
        MoneylenderCard() : Card("Moneylender", "Action", 4, 0, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class RemodelCard : public Card {
    public:
        RemodelCard() : Card("Remodel", "Action", 4, 0, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class PoacherCard : public Card {
    public:
        PoacherCard() : Card("Poacher", "Action", 4, 1, 1, 0, 1, 0){};
        void play(Player *player, Game &game);
};

class WorkshopCard : public Card {
    public:
        WorkshopCard() : Card("Workshop", "Action", 3, 0, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class VassalCard : public Card {
    public:
        VassalCard() : Card("Vassal", "Action", 3, 0, 0, 0, 2, 0){};
        void play(Player *player, Game &game);
};

class ArtisanCard : public Card {
    public:
        ArtisanCard() : Card("Artisan", "Action", 6, 0, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class MineCard : public Card {
    public:
        MineCard() : Card("Mine", "Action", 5, 0, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class ThroneRoomCard : public Card {
    public:
        ThroneRoomCard() : Card("Throne Room", "Action", 4, 0, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class CouncilRoomCard : public Card {
    public:
        CouncilRoomCard() : Card("Council Room", "Action", 5, 0, 4, 1, 0, 0){};
        void play(Player *player, Game &game);
};

class MilitiaCard : public Card {
    public:
        MilitiaCard() : Card("Militia", "Action", 4, 0, 0, 0, 2, 0){};
        void play(Player *player, Game &game);
};

class WitchCard : public Card {
    public:
        WitchCard() : Card("Witch", "Action", 5, 0, 2, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class BanditCard : public Card {
    public:
        BanditCard() : Card("Bandit", "Action", 5, 0, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class BureaucratCard : public Card {
    public:
        BureaucratCard() : Card("Bureaucrat", "Action", 4, 0, 0, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class SentryCard : public Card {
    public:
        SentryCard() : Card("Sentry", "Action", 5, 1, 1, 0, 0, 0){};
        void play(Player *player, Game &game);
};

class MerchantCard : public Card {
    public:
        MerchantCard() : Card("Merchant", "Action", 3, 1, 1, 0, 0, 0){};
        void play(Player *player, Game &game);
};
class CopperCard : public Card {
    public:
        CopperCard() : Card("Copper", "Treasure", 0, 0, 0, 0, 1, 0){};
        void play(Player *player, Game &game) {Card::play(player, game);};
};
class SilverCard : public Card {
    public:
        SilverCard() : Card("Silver", "Treasure", 3, 0, 0, 0, 2, 0){};
        void play(Player *player, Game &game);
};

class GoldCard : public Card {
    public:
        GoldCard() : Card("Gold", "Treasure", 6, 0, 0, 0, 3, 0){};
        void play(Player *player, Game &game) {Card::play(player, game);};
};

class EstateCard : public Card {
    public:
        EstateCard() : Card("Estate", "Victory", 2, 0, 0, 0, 0, 1){};
        void play(Player *player, Game &game) {return;};
};

class DuchyCard : public Card {
    public:
        DuchyCard() : Card("Duchy", "Victory", 5, 0, 0, 0, 0, 3){};
        void play(Player *player, Game &game) {return;};
};

class ProvinceCard : public Card {
    public:
        ProvinceCard() : Card("Province", "Victory", 8, 0, 0, 0, 0, 6){};
        void play(Player *player, Game &game) {return;};
};

class CurseCard : public Card {
    public:
        CurseCard() : Card("Curse", "Curse", 0, 0, 0, 0, 0, -1){};
        void play(Player *player, Game &game) {return;};
};

class FestivalCard : public Card {
    public:
        FestivalCard() : Card("Festival", "Action", 5, 2, 0, 1, 2, 0){};
        void play(Player *player, Game &game) {Card::play(player, game);};
};

class LaboratoryCard : public Card {
    public:
        LaboratoryCard() : Card("Laboratory", "Action", 5, 1, 2, 0, 0, 0){};
        void play(Player *player, Game &game) {Card::play(player, game);};
};

class MarketCard : public Card {
    public:
        MarketCard() : Card("Market", "Action", 5, 1, 1, 1, 1, 0){};
        void play(Player *player, Game &game) {Card::play(player, game);};
};

class SmithyCard : public Card {
    public:
        SmithyCard() : Card("Smithy", "Action", 4, 0, 3, 0, 0, 0){};
        void play(Player *player, Game &game) {Card::play(player, game);};
};

class VillageCard : public Card {
    public:
        VillageCard() : Card("Village", "Action", 3, 2, 1, 0, 0, 0){};
        void play(Player *player, Game &game) {Card::play(player, game);};
};

#endif