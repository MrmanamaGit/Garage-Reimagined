#include "stats.hpp"

// This is currently unused

CCMenuItemSpriteExtra* stats::createStatBtn(statType stat) {
    auto gsm = GameStatsManager::get();
    auto statStr = std::to_string(as<int>(stat));

    auto statVal = gsm->getStat(statStr.c_str());
    auto statSpr = CCSprite::createWithSpriteFrameName(getSpriteStrForType(stat).c_str());

    auto main = CCMenu::create();
    main->setLayout(AxisLayout::create());
    auto label = CCLabelBMFont::create(std::to_string(statVal).c_str(), "bigFont.fnt");

    main->setContentWidth(label->getContentWidth() + statSpr->getContentWidth());

    main->addChild(label);
    main->addChild(statSpr);
    main->updateLayout();

    main->setScale(0.5f);

    auto btn = CCMenuItemSpriteExtra::create(
        main,
        main,
        nullptr
    );

    btn->setTag(1);

    return btn;
};

std::string stats::getSpriteStrForType(statType type) {

    switch (type) {

        case statType::stars:
            return "GJ_starsIcon_001.png";

        case statType::secret:
            return "GJ_coinsIcon_001.png";

        case statType::user:
            return "GJ_coinsIcon2_001.png";

        case statType::moons:
            return "GJ_moonsIcon_001.png";

        case statType::diamond:
            return "GJ_diamondsIcon_001.png";

        case statType::orbs:
            return "currencyOrbIcon_001.png";

        case statType::demonKey:
            return "GJ_bigKey_001.png";
    
        default:
            return nullptr;

    }
}

/*
void stats::onStat(CCObject* sender) {
    int statType = sender->getTag();

    log::info("id: {}", statType);

    auto glm = GameLevelManager::get();

    auto levels = glm->getCompletedLevels(true);

    auto level = static_cast<GJGameLevel*>(levels->objectAtIndex(1));
    level->m_difficulty;
    level->

    GJDifficulty::

    log::info("levels: {}", levels);

    switch (statType) {
        case 6:
            StarInfoPopup::create(251,533,53,4,124,241,24,142,1241,true)->show();
            log::info("stars");
            break;
        case 28:
            StarInfoPopup::createFromString("02")->show();
            log::info("moons");
            break;
    
        default:
            log::info("Invalid statType or no stats to show!");
            break;
    }
}

*/
