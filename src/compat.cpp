#include "garage/garageLayer.hpp"

// randomize icons incompats:
// doesnt switch tabs but a different page button is selected
// listbuttonbar shows  up along with the navdot menus (vanilla and more icons mod)
// cursor doesnt refresh

void garage::setupMoreIcons() {
    auto f = m_fields.self();
    auto gm = GameManager::get();
    auto custIcons = MoreIcons::getIcons();

    auto layout = AxisLayout::create();
    layout->setGrowCrossAxis(true);
    layout->setGap(7.5);

    f->m_moreIconsMenu->removeAllChildrenWithCleanup(true);

    for (auto icon : custIcons) {
        if (icon->type == m_iconType) {
            auto iconSpr = GJItemIcon::createBrowserItem(gm->iconTypeToUnlockType(m_iconType), 1);
            auto simplePlayer = iconSpr->getChildByType<SimplePlayer*>(0);
            iconSpr->setScale(f->ICON_SIZE);

            MoreIcons::updateSimplePlayer(simplePlayer, icon->name, icon->type);
            if (Mod::get()->getSettingValue<bool>("icon-colours")) simplePlayer->setColors(gm->colorForIdx(gm->getPlayerColor()), gm->colorForIdx(gm->getPlayerColor2()));

            auto btn = CCMenuItemSpriteExtra::create(
                iconSpr,
                this,
                menu_selector(garage::onCustomIcon)
            );

            btn->setID(icon->name);
            f->m_moreIconsMenu->addChild(btn);
        }
    }
    
    this->scheduleOnce(schedule_selector(garage::hideNodes), 0.1); // if you know another way, tell me, please

    f->m_moreIconsMenu->updateLayout();
}

void garage::hideNodes() {
    if (auto node = this->getChildByID("hiimjustin000.more_icons/icon-selection-bar")) node->setVisible(false);
    if (auto node = this->getChildByID("hiimjustin000.more_icons/navdot-menu")) node->setVisible(false);

    m_cursor1->setPosition({0,0});
}

void garage::onCustomIcon(CCObject* sender) {
    auto item = static_cast<CCMenuItemSpriteExtra*>(sender);
    int itemID = item ? item->getTag() : -1;
    auto gm = GameManager::get();

    auto f = m_fields.self();

    if (MoreIcons::activeIcon(m_iconType) == item->getID()) showUnlockPopup(1, gm->iconTypeToUnlockType(m_iconType));

    MoreIcons::setIcon(item->getID(), m_iconType);
    setPlayerIcon(-1);
    f->m_cursorMoreIcons->setPosition(item->getPosition());
    f->m_cursorMoreIcons->setVisible(true);
    f->m_cursorCust1->setVisible(false);

    MoreIcons::updateSimplePlayer(m_playerObject, m_iconType, Loader::get()->isModLoaded("weebify.separate_dual_icons"));
}