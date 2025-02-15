#include "file_utils.hpp"
#include <vector>
#include <unordered_set>

Card::Type stringToType(const std::string& typeStr) {
    if (typeStr == "Treasure") return Card::Type::TREASURE;
    if (typeStr == "Victory") return Card::Type::VICTORY;
    if (typeStr == "Action") return Card::Type::ACTION;
    if (typeStr == "Curse") return Card::Type::CURSE;
    return Card::Type::TRASH; // Handle unknown types
}

// std::vector<Card> FileUtils::readCardsFromCSV(const std::string& filename, const std::vector<std::string>& editions){
//     std::vector<Card> cards;
//     std::ifstream file(filename);
//     std::string line;
    
//     // Create a set of editions for faster lookup
//     std::unordered_set<std::string> editionSet(editions.begin(), editions.end());
//     // Skip the header line
//     std::getline(file, line);
    
//     while (std::getline(file, line)) {
//         std::istringstream iss(line);
//         std::string token;
        
//         // Read each token and set the corresponding Card attribute
//         std::getline(iss, token, ',');
//         const std::string name = token;
        
//         // Read the set (edition) of the card
//         std::getline(iss, token, ',');
//         const std::string set = token;

        
//         // Check if the card's set is in the desired editions
//         if (editionSet.find(set) != editionSet.end()) {
//             std::getline(iss, token, ',');
//             const std::string string_type = token;
//             const Card::Type type = stringToType(string_type);

//             std::getline(iss, token, ',');
//             std::getline(iss, token, ',');
//             std::getline(iss, token, ',');
//             std::getline(iss, token, ',');
//             const int cost = stoi(token);

//             Card card(name, type, cost);
//             cards.push_back(card);
//         }
//     }
    
//     return cards;
// }
std::vector<Card> FileUtils::readCardsFromCSV(const std::string& filename, const std::string& editionName){
    std::vector<Card> cards;
    std::cout << "Reading from csv: " << filename << std::endl;
    csv::CSVReader reader(filename);

    std::string cardName;
    std::string setName;
    Card::Type type;
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
            type = stringToType(row["Type"].get<std::string>());
            isAttack = row["Attack"].get<bool>();
            cost = row["Cost"].get<int>();
            actions = row["Actions"].get<int>();
            drawCards = row["Cards"].get<int>();
            discards = row["Discards"].get<int>();
            buys = row["Buys"].get<int>();
            coins = row["Coins"].get<int>();
            trash = row["Trash"].get<int>();
            victoryPoints = row["VP"].get<int>();
            hasPlayEffect = row["Has Play Effect"].get<bool>();

            Card newCard(cardName, setName, type, isAttack, cost, actions, drawCards, discards, buys, coins, trash, victoryPoints, hasPlayEffect);
            cards.push_back(newCard);
        }
    }
    return cards;
}