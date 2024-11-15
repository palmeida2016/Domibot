// In a file named FileUtils.h
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <vector>
#include <string>
#include "card.hpp"

namespace FileUtils {
    std::vector<Card> readCardsFromCSV(const std::string& filename, const std::vector<std::string>& editions);
}

#endif