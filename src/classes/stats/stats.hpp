#include <Geode/Geode.hpp>

using namespace geode::prelude;

// this is unused for now

enum class statType {
    stars = 6,
    secret = 8,
    user = 12,
    diamond = 13,
    demonKey = 21,
    orbs = 22,
    moons = 28,
    // add more later
};

class stats {
    public:
        static CCMenuItemSpriteExtra* createStatBtn(statType stat);
        static std::string getSpriteStrForType(statType type);

        // void onStat(CCObject* sender);
};