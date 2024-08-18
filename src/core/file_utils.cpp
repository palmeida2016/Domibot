#include "file_utils.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>


std::vector<Card> readCardsFromCSV(const std::string& filename, const std::vector<std::string>& editions) {
    std::vector<Card> cards;
    std::ifstream file(filename);
    std::string line;
    
    // Create a set of editions for faster lookup
    std::unordered_set<std::string> editionSet(editions.begin(), editions.end());
    
    // Skip the header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        Card card;
        
        // Read each token and set the corresponding Card attribute
        std::getline(iss, token, ',');
        card.setName(token);
        
        // Read the set (edition) of the card
        std::getline(iss, token, ',');
        card.setSet(token);
        
        // Check if the card's set is in the desired editions
        if (editionSet.find(token) != editionSet.end()) {
            // ... set other attributes ...
            
            // Only add the card if its edition is in the desired editions
            cards.push_back(card);
        }
    }
    
    return cards;
}