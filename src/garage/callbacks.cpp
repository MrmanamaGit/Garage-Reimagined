#include "../classes.hpp"

void garage::onIcon(CCObject* sender) {
    auto item = static_cast<CCMenuItemSpriteExtra*>(sender);
    int itemID = item ? item->getTag() : -1;
    auto gm = GameManager::get();
    auto f = m_fields.self();

    auto separateDual = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    bool is2p = separateDual ? separateDual->getSavedValue<bool>("2pselected") : false;

    if (gm->isIconUnlocked(itemID, m_iconType)) {

        if (MoreIcons::activeIcon(m_iconType, is2p) == "") {
            if (!is2p && itemID == gm->activeIconForType(m_iconType)) { // checks if the icon that was clicked on should display the unlock popup if player 1 has it already selected

                showUnlockPopup(itemID, gm->iconTypeToUnlockType(m_iconType));
                return;

            } else if (is2p && itemID == separateDual->getSavedValue<int>(iconTypeToStr(m_iconType))) { // the same, but with player 2

                showUnlockPopup(itemID, gm->iconTypeToUnlockType(m_iconType));
                return;

            }
        }

        if (f->MORE_ICONS_ENABLED) { // clears moreIcons saved icon

            MoreIcons::setIcon("", m_iconType, is2p); // reset custom icon

        }

        if (f->SEPARATE_DUAL_ENABLED && is2p) { // if separate dual icons is enabled and icon selection is on player 2, then set the selected icon to player 2
            
            separateDual->setSavedValue(iconTypeToStr(m_iconType), itemID);

        } else { // just sets player 1 icon if above if condition isnt met

            setPlayerIcon(itemID);

        }

    } else  { // shows the unlock popup if the icon isnt unlocked

        showUnlockPopup(itemID, gm->iconTypeToUnlockType(m_iconType));

    }

    refreshCursor();
}

void garage::onShipFire(CCObject* sender) {
    auto item = static_cast<CCMenuItemSpriteExtra*>(sender);
    int itemID = item ? item->getTag() : -1;
    auto gm = GameManager::get();
    auto f = m_fields.self();

    auto separateDual = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    bool is2p = separateDual ? separateDual->getSavedValue<bool>("2pselected") : false;

    if (gm->isIconUnlocked(itemID, IconType::ShipFire)) {

        if (MoreIcons::activeIcon(IconType::ShipFire, is2p) == "") {
            if (!is2p && itemID == gm->activeIconForType(IconType::ShipFire)) { // checks if the shipFire that was clicked on should display the unlock popup if player 1 has it already selected

                showUnlockPopup(itemID, gm->iconTypeToUnlockType(IconType::ShipFire));
                return;

            } else if (is2p && itemID == separateDual->getSavedValue<int>(iconTypeToStr(IconType::ShipFire))) { // the same, but with player 2

                showUnlockPopup(itemID, gm->iconTypeToUnlockType(IconType::ShipFire));
                return;

            }
        }

        if (f->MORE_ICONS_ENABLED) { // clears moreIcons saved icon

            MoreIcons::setIcon("", IconType::ShipFire, is2p); // reset custom icon

        }

        if (f->SEPARATE_DUAL_ENABLED && is2p) { // if separate dual icons is enabled and icon selection is on player 2, then set the selected shipFire to player 2
            
            separateDual->setSavedValue(iconTypeToStr(IconType::ShipFire), itemID);

        } else { // just sets player 1 shipFire if above if condition isnt met

            gm->setPlayerShipStreak(itemID);

        }

    } else  { // shows the unlock popup if the icon isnt unlocked

        showUnlockPopup(itemID, gm->iconTypeToUnlockType(IconType::ShipFire));

    }

    refreshCursor();
}

void garage::onAnimation(CCObject* sender) {
    auto item = static_cast<CCMenuItemSpriteExtra*>(sender);
    int itemID = item ? item->getTag() : -1;
    auto gm = GameManager::get();
    auto gsm = GameStatsManager::get();
    auto f = m_fields.self();

    // enables animation if the animation is set to a valid ID and if its also unlocked
    if (item && itemID != -1 && gm->isIconUnlocked(itemID, gm->unlockTypeToIconType(static_cast<int>(UnlockType::GJItem)))) {

        gsm->toggleEnableItem(UnlockType::GJItem, itemID, !gsm->isItemEnabled(UnlockType::GJItem,itemID));
        item->getChildByType<GJItemIcon*>(0)->toggleEnabledState(gsm->isItemEnabled(UnlockType::GJItem,itemID));

    } else {

        showUnlockPopup(itemID, UnlockType::GJItem); // shows unlock popup if animation is locked

    }

    refreshCursor();
}

void garage::setPlayerIcon(int ID) { // basically an easier way for me to set the player 1 icon :)
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
        case IconType::Special: // only player trails
            gm->setPlayerStreak(ID);
            break;
    
    default:
        log::error("Couldn't set player icon!");
        break;
    }
}