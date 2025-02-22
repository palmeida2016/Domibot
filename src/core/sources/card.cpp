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

void Card::play(Player *player, Game &game){
    player->getDeck()->discard(this);
    std::cout << "You've played " << this->getName() << std::endl;
    player->applyCardEffect(this->getEffect());
}

void CellarCard::play(Player *player, Game &game) {
    //Discard any number of cards.
    //+1 Card per card discarded
    Card::play(player, game);
    
    std::cout << "Enter the number of cards you would like to discard: ";
    int numCards = 0;
    std::cin >> numCards;

    if(numCards > 0 && numCards < player->getDeck()->getHand().size()){
        for(int i = 0; i < numCards; i++){
            int choice = 0;
            player->displayHand();
            std::cout << "Choose a card to discard (0-" << player->getDeck()->getHand().size()-1 << "): ";                    
            std::cin >> choice;
            if (choice >= 0 && choice < static_cast<int>(player->getDeck()->getHand().size())) {
                Card *card = player->getDeck()->getHand()[choice];
                player->getDeck()->discard(choice);
            }
        }

        std::cout << "Now drawing " << numCards << " cards!" << std::endl;
        player->getDeck()->draw(numCards);
        
    }
    else{
        std::cout << "Please enter a valid number" << std::endl;
    }
}

void HarbingerCard::play(Player *player, Game &game) {
    //Look through your discard pile
    //You MAY put a card from it onto your deck
    Card::play(player, game);

    std::cout << "Look through your discard pile and select a card you want to put on top of your deck." << std::endl;
    player->displayDiscardPile();

    std::cout << "Do you want to topdeck a card onto your deck? (Y/N)" << std::endl;
    char choice;
    std::cin >> choice;

    if(choice == 'Y'){
        std::cout << "Enter the index of the card to put on top of your draw pile." << std::endl;
        int cardIndex;
        std::cin >> cardIndex;

        if (cardIndex >= 0 && cardIndex < static_cast<int>(player->getDeck()->getDiscardPile().size())) {
            Card *card = player->getDeck()->getDiscardPile()[cardIndex];
            player->getDeck()->removeFromDiscardPile(card);
            player->getDeck()->addCardToDeck(card);
        }
    }
}

void ChapelCard::play(Player *player, Game &game){
    Card::play(player, game);

    //Trash up to 4 cards from your hand
    int numCards = player->getDeck()->getHand().size();
    if(numCards > 4){
        numCards = 4;
    }

    std::cout << "You may trash up to 4 cards from your hand" << std::endl;
    player->displayHand();

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
            if (cardIndex >= 0 && cardIndex < static_cast<int>(player->getDeck()->getDiscardPile().size())) {
                player->getDeck()->trashCardFromHand(cardIndex);
            }
            else{
                std::cout << "Invalid card index!" << std::endl;
            }
        }
        trashCounter++;
    }
}

void LibraryCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "You will draw until you have 7 cards, selecting which action cards to keep." << std::endl;
    int numCards = player->getDeck()->getHand().size();

    while (numCards <= 7){
        Card *card = player->getDeck()->drawOne();
        std::cout << "You drew a " << card->getName() << std::endl;
        if(card->getType() == CardType::ACTION){
            std::cout << "Do you want to keep the " << card->getName() << "?(Y/N)" << std::endl;
            char choice;
            std::cin >> choice;
            if(choice == 'N'){
                player->getDeck()->discard(card);
            }
        }
    }
}

void MoneylenderCard::play(Player *player, Game &game){
    Card::play(player, game);


    if(player->hasCard("Copper")){
        std::cout << "You may trash a copper in your hand for +3 coins" << std::endl;
        player->displayHand();

        std::cout << "Enter the index of the copper you want to trash" << std::endl;
        int cardIndex;
        std::cin >> cardIndex;
        if (cardIndex >= 0 && cardIndex < static_cast<int>(player->getDeck()->getHand().size())) {
            while (player->getDeck()->getHand()[cardIndex]->getName() != "Copper"){
                std::cout << "The index you entered is not a copper card!" << std::endl;
                std::cout << "Enter the index of the copper you want to trash" << std::endl;
                std::cin >> cardIndex;
            }
            player->getDeck()->trashCardFromHand(cardIndex);
            player->addCoins(3);
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
void RemodelCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "You may now trash a card from your hand to gain a card costing 2 more coins than it" << std::endl;
    player->displayHand();
    std::cout << "Enter the index of the card you want to trash: ";
    int cardIndex;
    std::cin >> cardIndex;
    if (cardIndex >= 0 && cardIndex < static_cast<int>(player->getDeck()->getHand().size())) {
        Card *trashCard = player->getDeck()->getHand()[cardIndex];
        int cost = trashCard->getCost();
        player->getDeck()->trashCardFromHand(cardIndex);

        std::cout << "You trashed a " << trashCard->getName() << "! Now you can gain a card that costs up to " << cost + 2 << std::endl;

        // Gain a card that costs at most cost+2
        game.displayPiles();
        std::cout << "Enter the name of the card you want to gain: ";
        std::string cardName;
        std::cin >> cardName;

        Card *card = game.getSupply().buyCard(cardName, cost+2);
        player->getDeck()->addCardToDiscardPile(card);

    }
    else{
        std::cout << "Invalid card index!" << std::endl;
    }
}

void PoacherCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "You must now discard a card per number of empty Supply piles" << std::endl;


    int emptyPileCount = game.getSupply().getNumberOfEmptyPiles();
    std::cout << "There are currently " << emptyPileCount << " empty piles in the supply." << std::endl;

    int discardCount = 0;
    while (discardCount < emptyPileCount){
        player->displayHand();
        std::cout << "Enter the index of the card you want to discard" << std::endl;
        int cardIndex;
        std::cin >> cardIndex;

        if (cardIndex >= 0 && cardIndex < static_cast<int>(player->getDeck()->getHand().size())) {
            player->getDeck()->discard(cardIndex);
        }
        else{
            std::cout << "Invalid card index!" << std::endl;
        }
        discardCount++;
    }
}

void WorkshopCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "You can now gain a card costing up to 4 coins" << std::endl;

    game.displayPiles();
    std::cout << "Enter the name of the card you want to gain: ";
    std::string cardName;
    std::cin >> cardName;

    Card *card = game.getSupply().buyCard(cardName, cost+2);
    std::cout << "You gained a " << cardName << std::endl;
    player->getDeck()->addCardToDiscardPile(card);
}

void VassalCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "You will now discard the top card of your deck. If it is an action card, you may choose to play it." << std::endl;

    Card *card = player->getDeck()->drawOne();
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
            player->getDeck()->discard(card);
        }
    }
    else{
        std::cout << "It wasn't an action, so it is discarded." << std::endl;
        player->getDeck()->discard(card);
    }
}

void ArtisanCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "You can now gain a card costing up to 5 coins, and place a card from your hand onto your deck." << std::endl;

    game.displayPiles();
    std::cout << "Enter the name of the card you want to gain: ";
    std::string cardName;
    std::cin >> cardName;

    Card *card = game.getSupply().buyCard(cardName, 5);
    std::cout << "You gained a " << cardName << std::endl;
    player->getDeck()->addCardToHand(card);

    player->displayHand();
    std::cout << "Enter the index of the card you want to put onto your deck" << std::endl;
    int cardIndex;
    std::cin >> cardIndex;


    std::vector<Card*> playerHand = player->getDeck()->getHand();
    if (cardIndex >= 0 && cardIndex < static_cast<int>(playerHand.size())) {
        Card *card = playerHand[cardIndex];
        player->getDeck()->trashCardFromHand(cardIndex);
        player->getDeck()->addCardToDeck(card);
    }
    else{
        std::cout << "Invalid card index!" << std::endl;
    }
}

void MineCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "You may trash a treasure from your hand and gain a treasure to your hand costing up to 3 more coins than it." << std::endl;


    player->displayHand();
    std::cout << "Enter the index of the treasure card you want to trash: ";
    int cardIndex;
    std::cin >> cardIndex;
    
    if (cardIndex >= 0 && cardIndex < static_cast<int>(player->getDeck()->getHand().size())) {
        Card *trashCard = player->getDeck()->getHand()[cardIndex];
        while (trashCard->getType() != CardType::TREASURE){
            std::cout << "The index you entered is not a treasure card!" << std::endl;
            std::cout << "Enter the index of the treasure card you want to trash: ";
            std::cin >> cardIndex;
            trashCard = player->getDeck()->getHand()[cardIndex];
        }
        int cost = trashCard->getCost();
        player->getDeck()->trashCardFromHand(cardIndex);

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
        player->getDeck()->addCardToHand(card);

    }
    else{
        std::cout << "Invalid card index!" << std::endl;
    }
}

void ThroneRoomCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "You may play an action card from your hand twice this turn." << std::endl;

    if(player->hasCardType(CardType::ACTION)){
        player->displayHand();
        std::cout << "Enter the index of the action card you want to play twice: ";
        int cardIndex;
        std::cin >> cardIndex;
        
        if (cardIndex >= 0 && cardIndex < static_cast<int>(player->getDeck()->getHand().size())) {
            Card *actionCard = player->getDeck()->getHand()[cardIndex];
            while (actionCard->getType() != CardType::ACTION){
                std::cout << "The index you entered is not an action card!" << std::endl;
                std::cout << "Enter the index of the action card you want to play twice: ";
                std::cin >> cardIndex;
                actionCard = player->getDeck()->getHand()[cardIndex];
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

void CouncilRoomCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "Every other play must draw a card." << std::endl;

    std::vector<Player*> players = game.getOtherPlayers(player);

    for (auto& p: players){
        std::cout << p->getName() << " drew a card!" << std::endl;
        p->getDeck()->draw(1);
    }
}

void MilitiaCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "Every other play must discard down to three cards in hand." << std::endl;

    std::vector<Player*> players = game.getOtherPlayers(player);

    for (auto& p: players){
        if(p->hasCard("Moat")){
            std::cout << p->getName() << " - Would you like to reveal your Moat card to avoid this attack? (Y/N): ";
            char moatChoice;
            std::cin >> moatChoice;
            if(moatChoice == 'Y' || moatChoice == 'y'){
                continue;
            }
        }

        std::cout << p->getName() << " - select which cards to discard" << std::endl;
        while(p->getDeck()->getHand().size() > 3){
            p->displayHand();
            std::cout << "Enter the index of the action card you want discard: ";
            int cardIndex;
            std::cin >> cardIndex;

            if (cardIndex >= 0 && cardIndex < static_cast<int>(p->getDeck()->getHand().size())) {
                p->getDeck()->discard(cardIndex);
            }
            else{
                std::cout << "Invalid card index!" << std::endl;
            }
        }
    }
}

void WitchCard::play(Player *player, Game &game){
    Card::play(player, game);

    std::cout << "Every other play must gain a curse." << std::endl;

    std::vector<Player*> players = game.getOtherPlayers(player);

    for (auto& p: players){
        if(p->hasCard("Moat")){
            std::cout << p->getName() << " - Would you like to reveal your Moat card to avoid this attack? (Y/N): ";
            char moatChoice;
            std::cin >> moatChoice;
            if(moatChoice == 'Y' || moatChoice == 'y'){
                continue;
            }
        }
        std::cout << p->getName() << " gained a curse!" << std::endl;
        Card *curse = new CurseCard();
        p->getDeck()->addCardToDiscardPile(curse);
    }
}

void BanditCard::play(Player *player, Game &game){
    Card::play(player, game);

    Card *card = game.getSupply().buyCard("Gold", 6);
    player->getDeck()->addCardToDiscardPile(card);

    std::cout << "You gained a gold. Now each other player must reveal the top two cards of their deck," << std::endl
              << "and trash any treasure that isn't copper" <<std::endl;
    
    std::vector<Player*> players = game.getOtherPlayers(player);

    for (auto& p: players){

        if(p->hasCard("Moat")){
            std::cout << p->getName() << " - Would you like to reveal your Moat card to avoid this attack? (Y/N): ";
            char moatChoice;
            std::cin >> moatChoice;
            if(moatChoice == 'Y' || moatChoice == 'y'){
                continue;
            }
        }

        Card *firstCard = p->getDeck()->drawOne();
        Card *secondCard = p->getDeck()->drawOne();
        
        std::cout << p->getName() << " reveals a " << firstCard->getName() << " and a " << secondCard->getName() << std::endl; 

        bool firstCanTrash = false;
        bool secondCanTrash = false;

        if(firstCard->getType() != CardType::TREASURE || firstCard->getName() == "Copper"){
            p->getDeck()->discard(firstCard);
        }
        else{
            firstCanTrash = true;
        }

        if(secondCard->getType() != CardType::TREASURE || secondCard->getName() == "Copper"){
            p->getDeck()->discard(secondCard);
        }
        else{
            secondCanTrash = true;
        }

        if(firstCanTrash && secondCanTrash){
            int choice = -1;
            while(choice < 0 || choice > 1){
                std::cout << "Pick which card to trash [0-1]" << std::endl;
                std::cout << "Index 0: " << firstCard->getName() << std::endl;
                std::cout << "Index 1: " << secondCard->getName() << std::endl;
                std::cin >> choice;
            }
            if(choice == 0){
                p->getDeck()->trashCardFromHand(firstCard);
            }
            else if(choice == 1){
                p->getDeck()->trashCardFromHand(secondCard);
            }
        }
        else if(firstCanTrash){
            p->getDeck()->trashCardFromHand(firstCard);
        }
        else{
            p->getDeck()->trashCardFromHand(secondCard);
        }
    }
}

void BureaucratCard::play(Player *player, Game &game){
    Card::play(player, game);

    Card *card = game.getSupply().buyCard("Silver", 3);
    player->getDeck()->addCardToDeck(card);

    std::cout << "Each other player must place a Victory card from their hand onto their deck." << std::endl;

    std::vector<Player*> players = game.getOtherPlayers(player);

    for (auto& p: players){
        if(p->hasCardType(CardType::VICTORY)){
            if(p->hasCard("Moat")){
                std::cout << p->getName() << " - Would you like to reveal your Moat card to avoid this attack? (Y/N): ";
                char moatChoice;
                std::cin >> moatChoice;
                if(moatChoice == 'Y' || moatChoice == 'y'){
                    continue;
                }
            }

            std::cout << p->getName() << " - Select a victory card from your hand to place onto your deck." << std::endl;

            p->displayHand();

            std::cout << "Enter the index of a victory card: ";
            int cardIndex;
            std::cin >> cardIndex;

            if (cardIndex >= 0 && cardIndex < static_cast<int>(p->getDeck()->getHand().size())) {
                Card *card = p->getDeck()->getHand()[cardIndex];
                while(card->getType() != CardType::VICTORY){
                    std::cout << "Selected card is not a Victory card." << std::endl;
                    std::cout << "Please select another card: ";
                    std::cin >> cardIndex;

                    card = p->getDeck()->getHand()[cardIndex];
                }
                p->getDeck()->addCardToDeck(card);
            }
            else{
                std::cout << "Invalid card index!" << std::endl;
            }

        }
        else{
            std::cout << p->getName() << " does not have a Victory card!" << std::endl;
        }
    }
}

void SentryCard::play(Player *player, Game &game){
    Card::play(player, game);


    std::cout << "You may look at the top two cards of your deck, and trash/discard/topdeck any of them." << std::endl;

    Card *firstCard = player->getDeck()->drawOne();
    Card *secondCard = player->getDeck()->drawOne();
    Card* cards[] = {firstCard, secondCard};
        
    std::cout << "You have a " << firstCard->getName() << " and a " << secondCard->getName() << std::endl;

    int i = 0;
    int keepCount = 0;
    int keepIndex = 0;
    while(i < 2){
        Card *card = cards[i];
        std::cout << "Would you like to trash, discard, or keep " << card->getName() << " ?" <<std::endl;
        std::cout << "T - Trash the Card" << std::endl;
        std::cout << "D - Discard the Card" << std::endl;
        std::cout << "K - Keep the Card" << std::endl;
        std::cout << "Enter your choice: " <<std::endl;
        char choice;
        std::cin >> choice;

        while(choice != 'T' && choice != 'D' && choice != 'K'){
            std::cout << "Please select one of the three options!" << std::endl;
            std::cout << "Enter your choice: " <<std::endl;
            std::cin >> choice;
        }

        if (choice == 'T'){
            std::cout << "You trashed the " << card->getName();
            player->getDeck()->trashCardFromHand(card);
        }
        else if (choice == 'D'){
            std::cout << "You discarded the " << card->getName();
            player->getDeck()->discard(card);
        }
        else{
            keepIndex = i;
            keepCount++;
        }
        i++;
    }
    if(keepCount == 2){
        std::cout << "You chose to keep both of the cards" << std::endl;
        std::cout << "Would you like to reverse their order?" << std::endl;
        std::cout << "Current Order: " << std::endl;
        std::cout << "Top card: " << firstCard->getName() << std::endl;
        std::cout << "Bottom card: " << secondCard->getName() << std::endl;
        
        std::cout << "Put " << secondCard->getName() << " on top of your draw pile? (Y/N)" << std::endl;
        char choice;
        std::cin >> choice;
        if (choice == 'Y'){
            player->getDeck()->addCardToDeck(firstCard);
            player->getDeck()->addCardToDeck(secondCard);
        }
        else{
            player->getDeck()->addCardToDeck(secondCard);
            player->getDeck()->addCardToDeck(firstCard);
        }
    }
    else{
        player->getDeck()->addCardToDeck(cards[keepIndex]);
    }


}

void MerchantCard::play(Player *player, Game &game) {
    Card::play(player, game);

    std::cout << "The first time you play a Silver this turn you will gain an extra coin." << std::endl;
    player->setMerchantEffect(true);
}

void SilverCard::play(Player *player, Game &game){
    Card::play(player, game);

    // Has Merchant Effect is active
    if (player->getMerchantEffect()){
        player->addCoins(1);
        player->setMerchantEffect(false);
    }
}