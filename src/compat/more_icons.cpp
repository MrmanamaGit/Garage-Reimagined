#include "../classes.hpp"

void garage::setupMoreIcons() {
    auto gm = GameManager::get();
    auto custIcons = MoreIcons::getIcons();
    int i = 0;

    auto f = m_fields.self();

    auto layout = AxisLayout::create();
    layout->setGrowCrossAxis(true);
    layout->setGap(7.5);

    f->m_moreIconsMenu->removeAllChildrenWithCleanup(true);
    f->m_moreIconsMenu->setContentHeight(0);

    for (auto icon : custIcons) {
        if (icon->type == m_iconType) {
            auto iconSpr = GJItemIcon::createBrowserItem(gm->iconTypeToUnlockType(m_iconType), 1);
            auto simplePlayer = iconSpr->getChildByType<SimplePlayer*>(0);
            iconSpr->setScale(f->ICON_SIZE);

            MoreIcons::updateSimplePlayer(simplePlayer, icon->name, icon->type);
            if (Mod::get()->getSettingValue<bool>("icon-colours") && icon->type != IconType::Special) simplePlayer->setColors(gm->colorForIdx(gm->getPlayerColor()), gm->colorForIdx(gm->getPlayerColor2()));

            auto btn = CCMenuItemSpriteExtra::create(
                iconSpr,
                this,
                menu_selector(garage::onCustomIcon)
            );

            btn->setID(icon->name);
            f->m_moreIconsMenu->addChild(btn);
        }
    }
}

void garage::onCustomIcon(CCObject* sender) {
    auto item = static_cast<CCMenuItemSpriteExtra*>(sender);
    auto gm = GameManager::get();

    auto separateDual = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    bool is2p = separateDual ? separateDual->getSavedValue<bool>("2pselected") : false;
    auto f = m_fields.self();

    if (MoreIcons::activeIcon(m_iconType, is2p) == item->getID()) {
        moreIconInfoPopup::create(MoreIcons::getIcon(item->getID(), m_iconType))->show();
    } else {
        MoreIcons::setIcon(item->getID(), m_iconType, separateDual ? separateDual->getSavedValue<bool>("2pselected") : false);
        refreshCursor();
    }
}