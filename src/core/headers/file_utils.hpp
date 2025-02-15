#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <vector>
#include <string>
#include "card.hpp"
#include "csv.hpp"

namespace FileUtils {
    std::vector<Card> readCardsFromCSV(const std::string& filename, const std::string& editionName);
}

#endif