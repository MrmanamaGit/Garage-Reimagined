#include "garageLayer.hpp"

bool garage::init() {
    if (!GJGarageLayer::init()) return false;

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto scrollSize = CCSize{winSize.width / 2, winSize.height};
    auto f = m_fields.self();

    m_cursor1->setPosition({0,0});
    m_cursor1->setZOrder(0);
    m_cursor2->setPosition({0,0});
    m_cursor2->setZOrder(0);

	m_rightArrow->setVisible(false);
    m_leftArrow->setVisible(false);
    this->getChildByID("select-background")->setVisible(false);
	this->getChildByID("tap-more-hint")->setVisible(false);
	this->getChildByID("navdot-menu")->setPositionY(-25);
	this->getChildByID("bottom-right-corner")->setVisible(false);

	auto back = this->getChildByID("back-menu");
	auto settingSpr = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
	settingSpr->setScale(0.8f);

	auto settings = CCMenuItemSpriteExtra::create(
		settingSpr,
		this,
		menu_selector(garage::onSettings)
	);

	settings->setID("settings"_spr);

	back->addChild(settings);
	back->updateLayout();

		/*
			Category Menu
		*/

	auto categoryMenu = this->getChildByID("category-menu");
    categoryMenu->setLayout(AxisLayout::create(Axis::Column)
        ->setAxisReverse(true)
    );

	/*
    auto moreIconsBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"),
        this,
        menu_selector(garage::onMoreIcons)
    );

    moreIconsBtn->setTag(1000); // id for more icons
    categoryMenu->addChild(moreIconsBtn);

    if (Loader::get()->isModLoaded("hiimjustin000.more_icons")) {
        moreIconsBtn->setVisible(true);
    } else {
        moreIconsBtn->setVisible(false);
    }
 	*/

    categoryMenu->setPosition(winSize.width / 2.84, winSize.height / 2);
    categoryMenu->setContentWidth(0);
    categoryMenu->setContentHeight(400);
    categoryMenu->setScale(0.75f);

    categoryMenu->updateLayout();

		/*
			shop button
		*/

	auto otherMenu = this->getChildByID("shards-menu");
        
    this->getChildByID("top-left-menu")->setVisible(false);

    auto shopBtnSprite = CCSprite::create("shopBtnSprite.png"_spr);
    shopBtnSprite->setScale(0.9f);

    auto shopBtn = CCMenuItemSpriteExtra::create(
        shopBtnSprite, 
		this,
        menu_selector(GJGarageLayer::onShop)
    );

    otherMenu->addChild(shopBtn);
    shopBtn->setID("shop-button"_spr);

    // Fix Button layout
    otherMenu->setPosition(40, 90);
	otherMenu->setContentHeight(135);
    otherMenu->updateLayout();

		/*
			Player Stage
		*/

    m_playerObject->setPosition({categoryMenu->getPositionX() / 2, 200});
    this->getChildByID("floor-line")->setPosition(categoryMenu->getPositionX() / 2, 175);
	this->getChildByID("floor-line")->setScaleX(0.35f);

    if (auto greyUsernameLock = getChildByID("username-lock")) {

		greyUsernameLock->setPosition(categoryMenu->getPositionX() / 2, 265);

	} else if (auto nameHint = this->getChildByID("username-hint")) {

		nameHint->setPosition({});

	}

    m_usernameInput->setPosition(categoryMenu->getPositionX() / 2, 240);
	m_usernameInput->ignoreAnchorPointForPosition(false);
	m_usernameInput->getChildByType<CCLabelBMFont*>(0)->setPosition(m_usernameInput->getContentSize() / 2);
    m_usernameInput->setScale(0.8f);

		/*
			Stats
		*/

	this->getChildByID("stars-icon")->setPosition(150, 145);
	this->getChildByID("stars-label")->setPosition(140, 145);
	
	this->getChildByID("moons-icon")->setPosition(150, 130);
	this->getChildByID("moons-label")->setPosition(140, 130);

	this->getChildByID("coins-icon")->setPosition(150, 115);
	this->getChildByID("coins-label")->setPosition(140, 115);

	this->getChildByID("user-coins-icon")->setPosition(150, 100);
	this->getChildByID("user-coins-label")->setPosition(140, 100);

	this->getChildByID("orbs-icon")->setPosition(150, 85);
	this->getChildByID("orbs-label")->setPosition(140, 85);

	this->getChildByID("diamonds-icon")->setPosition(150, 70);
	this->getChildByID("diamonds-label")->setPosition(140, 70);

	this->getChildByID("diamond-shards-icon")->setPosition(150, 55);
	this->getChildByID("diamond-shards-label")->setPosition(140, 55);

    f->m_layout = AxisLayout::create();
    f->m_layout->setGrowCrossAxis(true);
    f->m_layout->setGap(7.5);

    auto mainLayer = CCLayer::create();
    mainLayer->setPosition(winSize.width / 2, winSize.height / 2);
    mainLayer->ignoreAnchorPointForPosition(false);

    f->m_scrollLayer = ScrollLayer::create({scrollSize.width + 20, scrollSize.height - 10});
    f->m_scrollLayer->ignoreAnchorPointForPosition(false);
    f->m_scrollLayer->setPosition({winSize.width - (winSize.width / 3), winSize.height / 2});
    f->m_scrollLayer->m_contentLayer->setAnchorPoint({0.5,0});

    f->m_scrollBar = Scrollbar::create(f->m_scrollLayer);
    f->m_scrollBar->setPosition({winSize.width - (winSize.width / 35), winSize.height / 2});

    createIconPage(); // sets up page

    auto background = CCScale9Sprite::create("square02_001.png");
    background->setPosition(f->m_scrollLayer->getPosition());
    background->setContentSize(f->m_scrollLayer->getContentSize() + CCSize{10,0});
    background->setOpacity(75);
    mainLayer->addChild(background);

    m_playerObject->updatePlayerFrame(GameManager::get()->activeIconForType(IconType::Cube), IconType::Cube);
    m_iconSelection->setVisible(false);

    this->addChild(mainLayer);
    mainLayer->addChild(f->m_scrollLayer);
    mainLayer->addChild(f->m_scrollBar);
    
    mainLayer->setID("content"_spr);

    return true;
}

void garage::onSelectTab(CCObject* sender) {
    auto toggler = static_cast<CCMenuItemToggler*>(sender);
    auto icontype = toggler ? toggler->getTag() : -1;

    auto prev = static_cast<CCMenuItemToggler*>(toggler->getParent()->getChildByTag(as<int>(m_iconType)));
    prev->toggle(false);
    prev->setEnabled(true);

    m_iconType = as<IconType>(icontype);

    toggler->toggle(true);
    toggler->setEnabled(false);

    createIconPage(); // Changes page
}

void garage::onIcon(CCObject* sender) {
    auto item = static_cast<CCMenuItemSpriteExtra*>(sender);
    int itemID = item ? item->getTag() : -1;
    auto gm = GameManager::get();

    if (item && itemID != -1 && gm->isIconUnlocked(itemID, m_iconType) && itemID != gm->activeIconForType(m_iconType)) {

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

void garage::createIconPage() {
    auto gm = GameManager::get();
    auto f = m_fields.self();

    if (!f->m_iconArray) f->m_iconArray = CCArray::create();

    f->m_iconArray->removeAllObjects();
    f->m_iconArray->retain();

    auto lockSpr = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
    lockSpr->setScale(0.7f);
    lockSpr->setPosition({5, 10});

    for (int i = 1; i < gm->countForType(m_iconType) + 1; i++) {

        auto icon = GJItemIcon::createBrowserItem(gm->iconTypeToUnlockType(m_iconType), i);
        icon->setScale(0.6f); // changes sprite scale

        /*
            Icons display with player colour settings
        */

        if (auto simplePlayer = icon->getChildByType<SimplePlayer*>(0)) {

            if (Mod::get()->getSettingValue<bool>("icon-colours")) {

                simplePlayer->setColors(gm->colorForIdx(gm->getPlayerColor()), gm->colorForIdx(gm->getPlayerColor2()));

            }

        }
            

        // adds a lock next to icons that are locked
        if (!gm->isIconUnlocked(i, m_iconType)) {

            icon->setOpacity(75);
            icon->addChild(lockSpr);

        }

        auto btn = CCMenuItemSpriteExtra::create(
            icon,
            this,
            menu_selector(garage::onIcon)
        );

        btn->setTag(i);
        f->m_iconArray->addObject(btn);

    }

    if (m_iconType == IconType::Special) {

        auto ship = CCMenu::create();
        auto items = CCMenu::create();

        // Shipfires
        for (int i = 1; i < gm->countForType(IconType::ShipFire) + 1; i++) {

            auto icon = GJItemIcon::createBrowserItem(UnlockType::ShipFire, i);
            icon->setScale(0.6f);

            // adds a lock next to icons that are locked
            if (!gm->isIconUnlocked(i, IconType::ShipFire)) {

                icon->setOpacity(75);
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
            icon->setScale(0.6f);

            // adds a lock next to icons that are locked
            if (!gm->isIconUnlocked(i, IconType::Item)) {

                icon->setOpacity(75);
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

        ship->setLayout(f->m_layout);
        items->setLayout(f->m_layout);
        ship->updateLayout();
        items->updateLayout();

        // Based on iconType
        ship->setTag(101);
        items->setTag(100);

        f->m_iconArray->addObject(ship);
        f->m_iconArray->addObject(items);

    }
    
    // refreshes icon menu
    if (f->m_iconMenu) f->m_iconMenu->removeFromParentAndCleanup(true);

    createMenu();
    adjustScroll();
    refreshCursor();
}

void garage::createMenu() {
    auto f = m_fields.self();

    f->m_iconMenu = CCMenu::createWithArray(f->m_iconArray);
    f->m_iconMenu->setLayout(f->m_layout);

    f->m_iconMenu->setPosition(145,0);

    f->m_iconMenu->setContentSize({f->m_scrollLayer->getContentWidth() - 10, f->m_iconMenu->getContentHeight()});

    f->m_scrollLayer->m_contentLayer->addChild(f->m_iconMenu);
}

void garage::refreshCursor() {
    auto f = m_fields.self();
    auto gm = GameManager::get();

    int currentIcon = gm->activeIconForType(m_iconType);

    if (!f->m_iconMenu->getChildByID("cursor-1")) {

        f->m_cursorCust1 = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
        f->m_cursorCust2 = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
        f->m_cursorCust1->setScale(0.65f);
        f->m_cursorCust2->setScale(0.65f);
        f->m_cursorCust1->setID("cursor-1");
        f->m_cursorCust2->setID("cursor-2");
        f->m_cursorCust2->setVisible(false);
        f->m_iconMenu->addChild(f->m_cursorCust1, 10000);

    }

    this->m_cursor1->setPosition({0,0});
    this->m_cursor1->setZOrder(0);
    this->m_cursor2->setPosition({0,0});
    this->m_cursor2->setZOrder(0);

    if (auto target = f->m_iconMenu->getChildByTag(currentIcon)) {

        f->m_cursorCust1->setPosition(target->getPosition());

        if (m_iconType == IconType::Special) {
            auto secondaryTarget = f->m_iconMenu->getChildByTag(101)->getChildByTag(gm->activeIconForType(IconType::ShipFire));

            f->m_iconMenu->getChildByTag(101)->addChild(f->m_cursorCust2, 10000);

            f->m_cursorCust2->setPosition(secondaryTarget->getPosition());
            f->m_cursorCust2->setVisible(true);
        }

    } else {

        log::error("couldn't find active icon!");

    }
}

void garage::adjustScroll() {
    auto f = m_fields.self();

    f->m_iconMenu->updateLayout();

    if (f->m_iconMenu->getContentHeight() >= 310) {

        f->m_scrollLayer->m_contentLayer->setContentHeight(f->m_iconMenu->getContentHeight() + 20);
        f->m_iconMenu->setPosition(f->m_scrollLayer->m_contentLayer->getContentSize() / 2);

    } else {

        f->m_scrollLayer->m_contentLayer->setContentHeight(310);
        f->m_iconMenu->setPosition(f->m_scrollLayer->m_contentLayer->getContentSize() / 2);

    }

    f->m_scrollLayer->scrollToTop();
}
