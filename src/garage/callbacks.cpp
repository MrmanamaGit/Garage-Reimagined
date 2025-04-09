#include "garageLayer.hpp"

void garage::onIcon(CCObject* sender) {
    auto item = static_cast<CCMenuItemSpriteExtra*>(sender);
    int itemID = item ? item->getTag() : -1;
    auto gm = GameManager::get();

    if (item && itemID != -1 && gm->isIconUnlocked(itemID, m_iconType) && itemID != gm->activeIconForType(m_iconType)) {

        if (m_fields->MORE_ICONS_ENABLED) MoreIcons::setIcon("", m_iconType); // reset custom icon
        setPlayerIcon(itemID);
        if (m_iconType != IconType::Special && m_iconType != IconType::DeathEffect) m_playerObject->updatePlayerFrame(gm->activeIconForType(m_iconType), m_iconType);
        refreshCursor();

    } else if (item && itemID != -1 || itemID == gm->activeIconForType(m_iconType)) {

        showUnlockPopup(itemID, gm->iconTypeToUnlockType(m_iconType));

    } else {

        log::error("Couldn't find icon or iconID!");

    }
}

void garage::onShipFire(CCObject* sender) {
    auto item = static_cast<CCMenuItemSpriteExtra*>(sender);
    int itemID = item ? item->getTag() : -1;
    auto gm = GameManager::get();

    if (item && itemID != -1 && gm->isIconUnlocked(itemID, IconType::ShipFire) && itemID != gm->activeIconForType(IconType::ShipFire)) {

        gm->setPlayerShipStreak(itemID);
        refreshCursor();

    } else if (item && itemID != -1 || itemID == gm->activeIconForType(IconType::ShipFire)) {

        showUnlockPopup(itemID, gm->iconTypeToUnlockType(IconType::ShipFire));

    } else {

        log::error("Couldn't find ship fire icon or iconID!");

    }
}

void garage::onAnimation(CCObject* sender) {
    auto item = static_cast<CCMenuItemSpriteExtra*>(sender);
    int itemID = item ? item->getTag() : -1;
    auto gm = GameManager::get();
    auto gsm = GameStatsManager::get();

    if (item && itemID != -1 && gm->isIconUnlocked(itemID, gm->unlockTypeToIconType(as<int>(UnlockType::GJItem)))) {

        gsm->toggleEnableItem(UnlockType::GJItem, itemID, !gsm->isItemEnabled(UnlockType::GJItem,itemID));
        item->getChildByType<GJItemIcon*>(0)->toggleEnabledState(gsm->isItemEnabled(UnlockType::GJItem,itemID));

    } else if (item && itemID != -1 || itemID == gm->activeIconForType(IconType::ShipFire)) {

        showUnlockPopup(itemID, UnlockType::GJItem);

    } else {

        log::error("Couldn't find animation icon or iconID!");

    }
}

void garage::setPlayerIcon(int ID) {
    auto gm = GameManager::get();

    switch (m_iconType) {
        case IconType::Cube:
            gm->setPlayerFrame(ID);
            break;
        case IconType::Ship:
            gm->setPlayerShip(ID);
            break;
        case IconType::Ball:
            gm->setPlayerBall(ID);
            break;
        case IconType::Ufo:
            gm->setPlayerBird(ID);
            break;
        case IconType::Wave:
            gm->setPlayerDart(ID);
            break;
        case IconType::Robot:
            gm->setPlayerRobot(ID);
            break;
        case IconType::Spider:
            gm->setPlayerSpider(ID);
            break;
        case IconType::Swing:
            gm->setPlayerSwing(ID);
            break;
        case IconType::Jetpack:
            gm->setPlayerJetpack(ID);
            break;
        case IconType::DeathEffect:
            gm->setPlayerDeathEffect(ID);
            break;
        case IconType::Special:
            gm->setPlayerStreak(ID);
            break;
    
    default:
        log::error("Couldn't set player icon!");
        break;
    }
}