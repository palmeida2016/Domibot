#include "card.hpp"

// Constructor
Card::Card(const std::string& name, Type type, int cost)
    : name(name), type(type), cost(cost), additionalCost(0), 
      numberOfCards(0), modifyCost(false), inSupply(false), 
      hasTrashEffect(false), hasGainEffect(false), trasher(false), 
      specialSetup(false), curseCost(0), costReducer(false) {}

// Destructor
Card::~Card() {}

// Getter and Setter implementations

std::string Card::getName() const {
    return name;
}

void Card::setName(const std::string& name) {
    this->name = name;
}

std::string Card::getSet() const {
    return set;
}

void Card::setSet(const std::string& set) {
    this->set = set;
}

Card::Type Card::getType() const{
    return type;
}

std::vector<std::string> Card::getTypes() const {
    return types;
}

void Card::addType(const std::string& type) {
    types.push_back(type);
}

int Card::getCost() const {
    return cost;
}

void Card::setCost(int cost) {
    this->cost = cost;
}

int Card::getAdditionalCost() const {
    return additionalCost;
}

void Card::setAdditionalCost(int additionalCost) {
    this->additionalCost = additionalCost;
}

int Card::getNumberOfCards() const {
    return numberOfCards;
}

void Card::setNumberOfCards(int numberOfCards) {
    this->numberOfCards = numberOfCards;
}

bool Card::isModifyCost() const {
    return modifyCost;
}

void Card::setModifyCost(bool modifyCost) {
    this->modifyCost = modifyCost;
}

bool Card::isInSupply() const {
    return inSupply;
}

void Card::setInSupply(bool inSupply) {
    this->inSupply = inSupply;
}

bool Card::getHasTrashEffect() const {
    return hasTrashEffect;
}

void Card::setHasTrashEffect(bool hasTrashEffect) {
    this->hasTrashEffect = hasTrashEffect;
}

bool Card::getHasGainEffect() const {
    return hasGainEffect;
}

void Card::setHasGainEffect(bool hasGainEffect) {
    this->hasGainEffect = hasGainEffect;
}

// Implement other getters and setters similarly

// Special functions
void Card::playCard() {
    // Implementation of card's effect when played
}

void Card::onTrashEffect() {
    // Implementation of card's effect when trashed
}

void Card::onGainEffect() {
    // Implementation of card's effect when gained
}
