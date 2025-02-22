#include "file_utils.hpp"
#include <vector>
#include <unordered_set>

std::vector<Card*> FileUtils::readCardsFromCSV(const std::string& filename, const std::string& editionName){
    std::vector<Card*> cards;
    // std::cout << "Reading from csv: " << filename << std::endl;
    csv::CSVReader reader(filename);

    std::string cardName;
    std::string setName;
    std::string type;
    bool isAttack;
    int cost;
    int actions;
    int drawCards;
    int discards;
    int buys;
    int coins;
    int trash;
    int victoryPoints;
    bool hasPlayEffect;

    for (auto& row: reader) {
        setName = row["Set"].get<std::string>();
        if (setName == editionName) {
            cardName = row["Card Name"].get<std::string>();
            type = row["Type"].get<std::string>();
            cost = row["Cost"].get<int>();
            actions = row["Actions"].get<int>();
            drawCards = row["Cards"].get<int>();
            buys = row["Buys"].get<int>();
            coins = row["Coins"].get<int>();
            victoryPoints = row["VP"].get<int>();
            if(cardName == "Cellar"){
                CellarCard *newCard = new CellarCard();
                cards.push_back(newCard);
            }
            else{
                Card *newCard = new Card(cardName, type, cost, actions, drawCards, buys, coins, victoryPoints);
                cards.push_back(newCard);
            }
        }
    }
    return cards;
}