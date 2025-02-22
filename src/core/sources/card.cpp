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
#include "game.hpp"
void CellarCard::play(Player &player, Game &game) {
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

void HarbingerCard::play(Player &player, Game &game) {
    //Look through your discard pile
    //You MAY put a card from it onto your deck
    player.getDeck().discard(this);

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

void ChapelCard::play(Player &player, Game &game){
    player.getDeck().discard(this);

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

void LibraryCard::play(Player &player, Game &game){
    player.getDeck().discard(this);


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

void MoneylenderCard::play(Player &player, Game &game){
    player.getDeck().discard(this);

    std::cout << "You've played Moneylender" << std::endl;

    if(player.hasCard("Copper")){
        std::cout << "You may trash a copper in your hand for +3 coins" << std::endl;
        player.displayHand();

        std::cout << "Enter the index of the copper you want to trash" << std::endl;
        int cardIndex;
        std::cin >> cardIndex;
        if (cardIndex >= 0 && cardIndex < static_cast<int>(player.getDeck().getHand().size())) {
            while (player.getDeck().getHand()[cardIndex]->getName() != "Copper"){
                std::cout << "The index you entered is not a copper card!" << std::endl;
                std::cout << "Enter the index of the copper you want to trash" << std::endl;
                std::cin >> cardIndex;
            }
            player.getDeck().trashCardFromHand(cardIndex);
            player.addCoins(3);
        }
        else{
            std::cout << "Invalid card index!" << std::endl;
        }
    }
    else{
        std::cout << "You don't have a copper in hand! Moneylender does nothing" << std::endl;
    }

}


// NEEDS GAME REFERENCE
void RemodelCard::play(Player &player, Game &game){
    player.getDeck().discard(this);

    std::cout << "You've played Remodel" << std::endl;
    std::cout << "You may now trash a card from your hand to gain a card costing 2 more coins than it" << std::endl;
    player.displayHand();
    std::cout << "Enter the index of the card you want to trash: ";
    int cardIndex;
    std::cin >> cardIndex;
    if (cardIndex >= 0 && cardIndex < static_cast<int>(player.getDeck().getHand().size())) {
        Card *trashCard = player.getDeck().getHand()[cardIndex];
        int cost = trashCard->getCost();
        player.getDeck().trashCardFromHand(cardIndex);

        std::cout << "You trashed a " << trashCard->getName() << "! Now you can gain a card that costs up to " << cost + 2 << std::endl;

        // Gain a card that costs at most cost+2
        game.displayPiles();
        std::cout << "Enter the name of the card you want to gain: ";
        std::string cardName;
        std::cin >> cardName;

        Card *card = game.getSupply().buyCard(cardName, cost+2);
        player.getDeck().addCardToDiscardPile(card);

    }
    else{
        std::cout << "Invalid card index!" << std::endl;
    }
}

void PoacherCard::play(Player &player, Game &game){
    player.getDeck().discard(this);

    std::cout << "You've played Poacher" << std::endl;
    std::cout << "You must now discard a card per number of empty Supply piles" << std::endl;


    int emptyPileCount = game.getSupply().getNumberOfEmptyPiles();
    std::cout << "There are currently " << emptyPileCount << " empty piles in the supply." << std::endl;

    int discardCount = 0;
    while (discardCount < emptyPileCount){
        player.displayHand();
        std::cout << "Enter the index of the card you want to discard" << std::endl;
        int cardIndex;
        std::cin >> cardIndex;

        if (cardIndex >= 0 && cardIndex < static_cast<int>(player.getDeck().getHand().size())) {
            player.getDeck().discard(cardIndex);
        }
        else{
            std::cout << "Invalid card index!" << std::endl;
        }
        discardCount++;
    }
}

void WorkshopCard::play(Player &player, Game &game){
    player.getDeck().discard(this);

    std::cout << "You've played Workshop" << std::endl;
    std::cout << "You can now gain a card costing up to 4 coins" << std::endl;

    game.displayPiles();
    std::cout << "Enter the name of the card you want to gain: ";
    std::string cardName;
    std::cin >> cardName;

    Card *card = game.getSupply().buyCard(cardName, cost+2);
    std::cout << "You gained a " << cardName << std::endl;
    player.getDeck().addCardToDiscardPile(card);
}

void VassalCard::play(Player &player, Game &game){
    player.getDeck().discard(this);

    std::cout << "You've played Vassal" << std::endl;
    std::cout << "You will now discard the top card of your deck. If it is an action card, you may choose to play it." << std::endl;

    Card *card = player.getDeck().drawOne();
    std::cout << "You drew a " << card->getName() << std::endl;

    if(card->getType() == CardType::ACTION){
        std::cout << "Would you like to play it? (Y/N): ";
        char choice;
        std::cin >> choice;
        if(choice == 'Y'){
            card->play(player, game);
        }
        else{
            std::cout << "You did not play it, so it is discarded." << std::endl;
            player.getDeck().discard(card);
        }
    }
    else{
        std::cout << "It wasn't an action, so it is discarded." << std::endl;
        player.getDeck().discard(card);
    }
}

void ArtisanCard::play(Player &player, Game &game){
    player.getDeck().discard(this);

    std::cout << "You've played Artisan" << std::endl;
    std::cout << "You can now gain a card costing up to 5 coins, and place a card from your hand onto your deck." << std::endl;

    game.displayPiles();
    std::cout << "Enter the name of the card you want to gain: ";
    std::string cardName;
    std::cin >> cardName;

    Card *card = game.getSupply().buyCard(cardName, 5);
    std::cout << "You gained a " << cardName << std::endl;
    player.getDeck().addCardToHand(card);

    player.displayHand();
    std::cout << "Enter the index of the card you want to put onto your deck" << std::endl;
    int cardIndex;
    std::cin >> cardIndex;


    std::vector<Card*> playerHand = player.getDeck().getHand();
    if (cardIndex >= 0 && cardIndex < static_cast<int>(playerHand.size())) {
        Card *card = playerHand[cardIndex];
        player.getDeck().trashCardFromHand(cardIndex);
        player.getDeck().addCardToDeck(card);
    }
    else{
        std::cout << "Invalid card index!" << std::endl;
    }
}

void MineCard::play(Player &player, Game &game){
    player.getDeck().discard(this);

    std::cout << "You've played Mine" << std::endl;
    std::cout << "You may trash a treasure from your hand and gain a treasure to your hand costing up to 3 more coins than it." << std::endl;


    player.displayHand();
    std::cout << "Enter the index of the treasure card you want to trash: ";
    int cardIndex;
    std::cin >> cardIndex;
    
    if (cardIndex >= 0 && cardIndex < static_cast<int>(player.getDeck().getHand().size())) {
        Card *trashCard = player.getDeck().getHand()[cardIndex];
        while (trashCard->getType() != CardType::TREASURE){
            std::cout << "The index you entered is not a treasure card!" << std::endl;
            std::cout << "Enter the index of the treasure card you want to trash: ";
            std::cin >> cardIndex;
            trashCard = player.getDeck().getHand()[cardIndex];
        }
        int cost = trashCard->getCost();
        player.getDeck().trashCardFromHand(cardIndex);

        std::cout << "You trashed a " << trashCard->getName() << "! Now you can gain a treasure card that costs up to " << cost + 3 << std::endl;

        // Gain a card that costs at most cost+2
        const std::vector<CardType>& types = {CardType::TREASURE};
        game.displayPiles(types);
        std::cout << "Enter the name of the card you want to gain: ";
        std::string cardName;
        std::cin >> cardName;


        Card *card = game.getSupply().getCard(cardName);
        while(card->getType() != CardType::TREASURE){
            std::cout << "The card name you entered is not a treasure card!" << std::endl;
            std::cout << "Enter the name of the card you want to gain: ";
            std::cin >> cardName;
            card = game.getSupply().getCard(cardName);
        }

        game.getSupply().buyCard(cardName, cost+3);
        player.getDeck().addCardToHand(card);

    }
    else{
        std::cout << "Invalid card index!" << std::endl;
    }
}

void ThroneRoomCard::play(Player &player, Game &game){
    player.getDeck().discard(this);

    std::cout << "You've played Throne Room" << std::endl;
    std::cout << "You may play an action card from your hand twice this turn." << std::endl;

    if(player.hasCardType(CardType::ACTION)){
        player.displayHand();
        std::cout << "Enter the index of the action card you want to play twice: ";
        int cardIndex;
        std::cin >> cardIndex;
        
        if (cardIndex >= 0 && cardIndex < static_cast<int>(player.getDeck().getHand().size())) {
            Card *actionCard = player.getDeck().getHand()[cardIndex];
            while (actionCard->getType() != CardType::ACTION){
                std::cout << "The index you entered is not an action card!" << std::endl;
                std::cout << "Enter the index of the action card you want to play twice: ";
                std::cin >> cardIndex;
                actionCard = player.getDeck().getHand()[cardIndex];
            }
            for(int i = 0; i < 2; i++){
                actionCard->play(player, game);
            }
        }
        else{
            std::cout << "Invalid card index!" << std::endl;
        }
    }
    else{
        std::cout << "You don't have any action cards. Throne Room does nothing!" << std::endl;
    }

}