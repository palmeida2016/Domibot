#include "card.hpp"
#include <iostream>

CardType stringToType(const std::string& typeStr) {
    if (typeStr == "Treasure") {
        return CardType::TREASURE;
    }
    if (typeStr == "Victory") {
        return CardType::VICTORY;
    }
    if (typeStr == "Action") {
        return CardType::ACTION;
    }
    if (typeStr == "Curse") {
        return CardType::CURSE;
    }
    return CardType::TRASH; // Handle unknown types
}

Card::Card(const std::string& name, const std::string& type, int cost, int actions, int cards, int buys, int coins, int victoryPoints){
    CardEffect effect = CardEffect(actions, cards, buys, coins, victoryPoints);
    this->effect = effect;
    this->type = stringToType(type);
    this->cost = cost;
    this->name = name;
}


// Special Card Implementations
#include "player.hpp"
void CellarCard::play(Player &player) {
    //Discard any number of cards.
    //+1 Card per card discarded
    player.getDeck().discard(this);
    std::cout << "You've played Cellar" << std::endl;
    std::cout << "Enter the number of cards you would like to discard: ";
    int numCards = 0;
    std::cin >> numCards;

    if(numCards > 0 && numCards < player.getDeck().getHand().size()){
        for(int i = 0; i < numCards; i++){
            int choice = 0;
            player.displayHand();
            std::cout << "Choose a card to discard (0-" << player.getDeck().getHand().size()-1 << "): ";                    
            std::cin >> choice;
            if (choice >= 0 && choice < static_cast<int>(player.getDeck().getHand().size())) {
                Card *card = player.getDeck().getHand()[choice];
                player.getDeck().discard(choice);
            }
        }

        std::cout << "Now drawing " << numCards << " cards!" << std::endl;
        player.getDeck().draw(numCards);
        
    }
    else{
        std::cout << "Please enter a valid number" << std::endl;
    }
}

void HarbingerCard::play(Player &player) {
    //Look through your discard pile
    //You MAY put a card from it onto your deck
    std::cout << "You've played Harbinger" << std::endl;
    std::cout << "Look through your discard pile and select a card you want to put on top of your deck." << std::endl;
    player.displayDiscardPile();

    std::cout << "Do you want to topdeck a card onto your deck? (Y/N)" << std::endl;
    char choice;
    std::cin >> choice;

    if(choice == 'Y'){
        std::cout << "Enter the index of the card to put on top of your draw pile." << std::endl;
        int cardIndex;
        std::cin >> cardIndex;

        if (cardIndex >= 0 && cardIndex < static_cast<int>(player.getDeck().getDiscardPile().size())) {
            Card *card = player.getDeck().getDiscardPile()[cardIndex];
            player.getDeck().removeFromDiscardPile(card);
            player.getDeck().addCardToDeck(card);
        }
    }
}

void ChapelCard::play(Player &player){
    //Trash up to 4 cards from your hand
    int numCards = player.getDeck().getHand().size();
    if(numCards > 4){
        numCards = 4;
    }

    std::cout << "You've played Chapel" << std::endl;
    std::cout << "You may trash up to 4 cards from your hand" << std::endl;
    player.displayHand();

    int trashCounter = 0;

    while(trashCounter < numCards) {
        std::cout << "Do you want to trash a card? (Y/N)" << std::endl;
        char choice;
        std::cin >> choice;
        if(choice != 'Y'){
            break;
        }
        else{
            std::cout << "Enter the index of the card to trash." << std::endl;
            int cardIndex;
            std::cin >> cardIndex;
            if (cardIndex >= 0 && cardIndex < static_cast<int>(player.getDeck().getDiscardPile().size())) {
                player.getDeck().trashCardFromHand(cardIndex);
            }
            else{
                std::cout << "Invalid card index!" << std::endl;
            }
        }
        trashCounter++;
    }
}

void LibraryCard::play(Player &player){
    
    std::cout << "You've played Library" << std::endl;
    std::cout << "You will draw until you have 7 cards, selecting which action cards to keep." << std::endl;
    int numCards = player.getDeck().getHand().size();

    while (numCards <= 7){
        Card *card = player.getDeck().drawOne();
        std::cout << "You drew a " << card->getName() << std::endl;
        if(card->getType() == CardType::ACTION){
            std::cout << "Do you want to keep the " << card->getName() << "?(Y/N)" << std::endl;
            char choice;
            std::cin >> choice;
            if(choice == 'N'){
                player.getDeck().discard(card);
            }
        }
    }
}