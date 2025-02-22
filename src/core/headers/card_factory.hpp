// card_factory.hpp
#ifndef CARD_FACTORY_HPP
#define CARD_FACTORY_HPP

#include "card.hpp"
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <random>

class CardFactory {
public:
    static CardFactory& getInstance() {
        static CardFactory instance;
        return instance;
    }

    // Get basic supply cards (Copper, Silver, Gold, Estate, Duchy, Province, Curse)
    std::vector<Card*> createSupplyCards() const {
        std::vector<Card*> cards;
        for (const auto& cardName : supplyCardNames) {
            cards.push_back(createCard(cardName));
        }
        return cards;
    }

    // Get all available kingdom cards
    std::vector<Card*> createAllKingdomCards() const {
        std::vector<Card*> cards;
        for (const auto& cardName : kingdomCardNames) {
            cards.push_back(createCard(cardName));
        }
        return cards;
    }
    
    // Create a single card by name
    Card* createCard(const std::string& cardName) const {
        auto it = creators.find(cardName);
        if (it != creators.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    CardFactory() {
        // Register supply cards
        registerCard<CopperCard>("Copper", CardType::TREASURE, true);
        registerCard<SilverCard>("Silver", CardType::TREASURE, true);
        registerCard<GoldCard>("Gold", CardType::TREASURE, true);
        registerCard<EstateCard>("Estate", CardType::VICTORY, true);
        registerCard<DuchyCard>("Duchy", CardType::VICTORY, true);
        registerCard<ProvinceCard>("Province", CardType::VICTORY, true);
        registerCard<CurseCard>("Curse", CardType::CURSE, true);

        // Register kingdom cards
        registerCard<CellarCard>("Cellar", CardType::ACTION, false);
        registerCard<HarbingerCard>("Harbinger", CardType::ACTION, false);
        registerCard<ChapelCard>("Chapel", CardType::ACTION, false);
        registerCard<LibraryCard>("Library", CardType::ACTION, false);
        registerCard<MoneylenderCard>("Moneylender", CardType::ACTION, false);
        registerCard<RemodelCard>("Remodel", CardType::ACTION, false);
        registerCard<PoacherCard>("Poacher", CardType::ACTION, false);
        registerCard<WorkshopCard>("Workshop", CardType::ACTION, false);
        registerCard<VassalCard>("Vassal", CardType::ACTION, false);
        registerCard<ArtisanCard>("Artisan", CardType::ACTION, false);
        registerCard<MineCard>("Mine", CardType::ACTION, false);
        registerCard<ThroneRoomCard>("Throne Room", CardType::ACTION, false);
        registerCard<CouncilRoomCard>("Council Room", CardType::ACTION, false);
        registerCard<MilitiaCard>("Militia", CardType::ACTION, false);
        registerCard<WitchCard>("Witch", CardType::ACTION, false);
        registerCard<BanditCard>("Bandit", CardType::ACTION, false);
        registerCard<BureaucratCard>("Bureaucrat", CardType::ACTION, false);
        registerCard<SentryCard>("Sentry", CardType::ACTION, false);
        registerCard<MerchantCard>("Merchant", CardType::ACTION, false);
        registerCard<FestivalCard>("Festival", CardType::ACTION, false);
        registerCard<LaboratoryCard>("Laboratory", CardType::ACTION, false);
        registerCard<MarketCard>("Market", CardType::ACTION, false);
        registerCard<SmithyCard>("Smithy", CardType::ACTION, false);
        registerCard<VillageCard>("Village", CardType::ACTION, false);
    }

    CardFactory(const CardFactory&) = delete;
    CardFactory& operator=(const CardFactory&) = delete;

    template<typename T>
    void registerCard(const std::string& name, CardType type, bool isSupplyCard) {
        creators[name] = []() { return new T(); };
        cardTypes[name] = type;
        
        if (isSupplyCard) {
            supplyCardNames.insert(name);
        } else {
            kingdomCardNames.insert(name);
        }
    }

    std::unordered_map<std::string, std::function<Card*()>> creators;
    std::unordered_map<std::string, CardType> cardTypes;
    std::unordered_set<std::string> supplyCardNames;
    std::unordered_set<std::string> kingdomCardNames;
};

#endif