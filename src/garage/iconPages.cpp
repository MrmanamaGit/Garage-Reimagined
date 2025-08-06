#include "../classes.hpp"
#include "hiimjustin000.more_icons/include/MoreIcons.hpp"

void garage::createIconPage() {
    auto gm = GameManager::get();
    auto f = m_fields.self();

    auto layout = AxisLayout::create();
    layout->setGrowCrossAxis(true);
    layout->setGap(7.5);

    f->m_iconMenu->removeAllChildrenWithCleanup(true);

    auto lockSpr = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
    lockSpr->setScale(0.7f);
    lockSpr->setPosition({5, 10});

    for (int i = 1; i < gm->countForType(m_iconType) + 1; i++) {

        auto icon = GJItemIcon::createBrowserItem(gm->iconTypeToUnlockType(m_iconType), i);
        icon->setScale(f->ICON_SIZE); // changes sprite scale

        /*
            Display icons with player colour settings
        */

        if (auto simplePlayer = icon->getChildByType<SimplePlayer*>(0)) {

            simplePlayer->setTag(0);

            if (Mod::get()->getSettingValue<bool>("icon-colours")) {

                simplePlayer->setColors(gm->colorForIdx(gm->getPlayerColor()), gm->colorForIdx(gm->getPlayerColor2()));

            }

        }

        // adds a lock next to icons that are locked
        if (!gm->isIconUnlocked(i, m_iconType)) {

            icon->setOpacity(f->LOCK_OPACITY);
            icon->addChild(lockSpr);

        }

        auto btn = CCMenuItemSpriteExtra::create(
            icon,
            this,
            menu_selector(garage::onIcon)
        );

        btn->setTag(i);
        f->m_iconMenu->addChild(btn);

    }

    if (m_iconType == IconType::Special) {

        auto ship = CCMenu::create();
        auto items = CCMenu::create();

        // Shipfires
        for (int i = 1; i < gm->countForType(IconType::ShipFire) + 1; i++) {

            auto icon = GJItemIcon::createBrowserItem(UnlockType::ShipFire, i);
            icon->setScale(f->ICON_SIZE);

            // adds a lock next to icons that are locked
            if (!gm->isIconUnlocked(i, IconType::ShipFire)) {

                icon->setOpacity(f->LOCK_OPACITY);
                icon->addChild(lockSpr);

            }

            auto btn = CCMenuItemSpriteExtra::create(
                icon,
                this,
                menu_selector(garage::onShipFire)
            );

            ship->addChild(btn, 10, i);

        }

        // Animations
        for (int i = 18; i < 21; i++) {
            
            auto icon = GJItemIcon::createBrowserItem(UnlockType::GJItem, i);
            icon->setScale(f->ICON_SIZE);

            // adds a lock next to icons that are locked
            if (!gm->isIconUnlocked(i, IconType::Item)) {

                icon->setOpacity(f->LOCK_OPACITY);
                icon->addChild(lockSpr);

            }

            icon->toggleEnabledState(GameStatsManager::get()->isItemEnabled(UnlockType::GJItem, i));

            auto btn = CCMenuItemSpriteExtra::create(
                icon,
                this,
                menu_selector(garage::onAnimation) // onToggleItem doesnt seem to work??
            );

            items->addChild(btn, 10, i);

        }

        ship->setContentWidth(f->m_scrollLayer->m_contentLayer->getContentWidth());
        items->setContentWidth(f->m_scrollLayer->m_contentLayer->getContentWidth());

        ship->setLayout(layout);
        items->setLayout(layout);
        ship->updateLayout();
        items->updateLayout();

        // Set tag based on iconType
        ship->setTag(101);
        items->setTag(100);

        f->m_iconMenu->addChild(ship);
        f->m_iconMenu->addChild(items);

    }
}

void garage::refreshCursor() {
    auto f = m_fields.self();
    auto gm = GameManager::get();

    auto separateDual = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    bool is2p = separateDual ? separateDual->getSavedValue<bool>("2pselected") : false;

    // readds the cursors if they arent already added to their menus
    if (!f->m_iconMenu->getChildByID("cursor-1")) {

        f->m_cursorCust1 = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
        f->m_cursorCust1->setScale(0.65f);
        f->m_cursorCust1->setID("cursor-1");

        f->m_cursorCust2 = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
        f->m_cursorCust2->setScale(0.65f);
        f->m_cursorCust2->setID("cursor-2");
        
        f->m_iconMenu->addChild(f->m_cursorCust1, 10000);
        if (m_iconType == IconType::Special) {
            f->m_iconMenu->getChildByTag(101)->addChild(f->m_cursorCust2, 10000);
            f->m_cursorCust2->setVisible(false); // will be set visible when special icon is selected
        }

        if (f->MORE_ICONS_ENABLED) {
            f->m_cursorMoreIcons = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
            f->m_cursorMoreIcons->setScale(0.65f);
            f->m_cursorMoreIcons->setID("cursor-more-icons");

            f->m_moreIconsMenu->addChild(f->m_cursorMoreIcons, 10000);
        }
    }

    if (f->SEPARATE_DUAL_ENABLED && is2p) {
        f->m_cursorCust1->setColor({255,255,0});

        f->m_cursorCust1->setPosition(f->m_iconMenu->getChildByTag(separateDual->getSavedValue<int>(iconTypeToStr(m_iconType)))->getPosition());
        f->m_cursorCust1->setVisible(true);

        if (f->MORE_ICONS_ENABLED) {
            f->m_cursorMoreIcons->setVisible(false);

            if (MoreIcons::activeIcon(m_iconType, true) != "") {
                f->m_cursorMoreIcons->setColor({255,255,0});
                f->m_cursorMoreIcons->setPosition(f->m_moreIconsMenu->getChildByID(MoreIcons::activeIcon(m_iconType, true))->getPosition());
                f->m_cursorMoreIcons->setVisible(true);
                f->m_cursorCust1->setVisible(false);
            }

        }

        if (m_iconType == IconType::Special) {
            f->m_cursorCust2->setColor({255,255,0});

            f->m_cursorCust2->setPosition(f->m_iconMenu->getChildByTag(101)->getChildByTag(separateDual->getSavedValue<int>("shiptrail"))->getPosition());
            f->m_cursorCust2->setVisible(true);
        }

    } else { // if separateDual isnt active or a vanilla or moreIcon icon was selected
        int activeIconID = gm->activeIconForType(m_iconType);
        f->m_cursorCust1->setPosition(f->m_iconMenu->getChildByTag(activeIconID)->getPosition());
        f->m_cursorCust1->setVisible(true);

        f->m_cursorCust1->setColor({0,255,255});

        if (f->MORE_ICONS_ENABLED) {
            f->m_cursorMoreIcons->setVisible(false);

            if (MoreIcons::activeIcon(m_iconType) != "") {
                f->m_cursorMoreIcons->setColor({0,255,255});
                f->m_cursorMoreIcons->setPosition(f->m_moreIconsMenu->getChildByID(MoreIcons::activeIcon(m_iconType))->getPosition());
                f->m_cursorMoreIcons->setVisible(true);
                f->m_cursorCust1->setVisible(false);
            }
        }

        if (m_iconType == IconType::Special) {
            f->m_cursorCust2->setColor({0,255,255});

            f->m_cursorCust2->setPosition(f->m_iconMenu->getChildByTag(101)->getChildByTag(gm->activeIconForType(IconType::ShipFire))->getPosition());
            f->m_cursorCust2->setVisible(true);
        }
    }

    // refreshes p1 and p2 icons on any change
    if (m_iconType != IconType::DeathEffect && m_iconType != IconType::Special) {
        if (f->MORE_ICONS_ENABLED) {
            if (MoreIcons::activeIcon(m_iconType) != "") {
                MoreIcons::updateSimplePlayer(m_playerObject, MoreIcons::activeIcon(m_iconType), m_iconType);
            } else {
                m_playerObject->updatePlayerFrame(gm->activeIconForType(m_iconType), m_iconType);
            }

            if (f->SEPARATE_DUAL_ENABLED) {
                if (MoreIcons::activeIcon(m_iconType, true) != "") {
                    MoreIcons::updateSimplePlayer(static_cast<SimplePlayer*>(this->getChildByID("player2-icon")), MoreIcons::activeIcon(m_iconType, true), m_iconType);
                } else {
                    static_cast<SimplePlayer*>(this->getChildByID("player2-icon"))->updatePlayerFrame(separateDual->getSavedValue<int>(iconTypeToStr(m_iconType)), m_iconType);
                }
            }
        } else {
            m_playerObject->updatePlayerFrame(gm->activeIconForType(m_iconType), m_iconType);

            if (f->SEPARATE_DUAL_ENABLED) {
                static_cast<SimplePlayer*>(this->getChildByID("player2-icon"))->updatePlayerFrame(separateDual->getSavedValue<int>(iconTypeToStr(m_iconType)), m_iconType);
            }
        }
    }

    m_playerObject->setColors(gm->colorForIdx(gm->getPlayerColor()), gm->colorForIdx(gm->getPlayerColor2()));
    if (f->SEPARATE_DUAL_ENABLED) static_cast<SimplePlayer*>(this->getChildByID("player2-icon"))->setColors(gm->colorForIdx(separateDual->getSavedValue<int>("color1")), gm->colorForIdx(separateDual->getSavedValue<int>("color2")));
}

void garage::adjustScroll() {
    auto f = m_fields.self();
    float moreIconMenuHeight = 0.0f;

    f->m_iconMenu->updateLayout();

    if (f->MORE_ICONS_ENABLED) {
        f->m_moreIconsMenu->updateLayout();
        moreIconMenuHeight = f->m_moreIconsMenu->getContentHeight();
    }

    if (f->m_iconMenu->getContentHeight() + moreIconMenuHeight >= 310) {

        f->m_scrollLayer->m_contentLayer->setContentHeight(f->m_iconMenu->getContentHeight() + moreIconMenuHeight + f->PADDING * 3);

        f->m_iconMenu->setPosition({f->m_scrollLayer->m_contentLayer->getContentWidth() / 2, f->m_scrollLayer->m_contentLayer->getContentHeight() - f->PADDING});
        f->m_iconMenu->setAnchorPoint({0.5, 1});

    } else {

        f->m_scrollLayer->m_contentLayer->setContentHeight(310);
        f->m_iconMenu->setPosition({f->m_scrollLayer->m_contentLayer->getContentWidth() / 2, f->m_scrollLayer->m_contentLayer->getContentHeight() - f->m_iconMenu->getContentHeight() / 2 - f->PADDING});
        f->m_iconMenu->setAnchorPoint({0.5, 0.5});

    }

    f->m_breakline->setPositionY((f->m_scrollLayer->m_contentLayer->getContentHeight() - f->m_iconMenu->getContentHeight()) - (f->PADDING * 1.5));
    if (f->MORE_ICONS_ENABLED) f->m_moreIconsMenu->setPosition({f->m_scrollLayer->m_contentLayer->getContentWidth() / 2, f->m_breakline->getPositionY() - f->PADDING});

    f->m_scrollLayer->scrollToTop();
    
    refreshCursor();
}