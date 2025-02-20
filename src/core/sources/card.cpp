#include "card.hpp"


CardType stringToType(const std::string& typeStr) {
    if (typeStr == "Treasure") return CardType::TREASURE;
    if (typeStr == "Victory") return CardType::VICTORY;
    if (typeStr == "Action") return CardType::ACTION;
    if (typeStr == "Curse") return CardType::CURSE;
    return CardType::TRASH; // Handle unknown types
}

Card::Card(const std::string& name, const std::string& type, int cost, int actions, int cards, int buys, int coins, int victoryPoints){
    CardEffect effect = CardEffect(actions, cards, buys, coins, victoryPoints);
    this->effect = effect;
    this->type = stringToType(type);
    this->cost = cost;
    this->name = name;
}

// AttackCard implementations
AttackCard::AttackCard(const std::string& name, const std::string& type, int cost, int actions, int cards, int buys, int coins, int victoryPoints)
    : Card(name, type, cost, actions, cards, buys, coins, victoryPoints) {
}

class MilitiaCard : public AttackCard {
public:
    MilitiaCard() 
        : AttackCard("Militia", "Action", 4, 0, 0, 0, 2, 0) {
        attackEffect = AttackEffect(AttackType::DISCARD, 2);  // Discard down to 3 cards
    }

    CardEffect getEffect() const {
        CardEffect baseEffect = Card::getEffect();
        return CardEffect(
            baseEffect.actions,
            baseEffect.cards,
            baseEffect.buys,
            baseEffect.coins,
            baseEffect.victoryPoints,
            attackEffect
        );
    }

private:
    AttackEffect attackEffect = AttackEffect(AttackType::DISCARD, 2);;
};