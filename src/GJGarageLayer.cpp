#include "classes.hpp"

bool garage::init() {
    if (!GJGarageLayer::init()) return false;

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto scrollSize = CCSize{winSize.width / 2, winSize.height};
    auto f = m_fields.self();

	m_rightArrow->setPositionX(winSize.width + 25);
    m_leftArrow->setPositionX(-50);
    this->getChildByID("select-background")->setVisible(false);
	this->getChildByID("tap-more-hint")->setVisible(false);
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
    categoryMenu->setLayout(AxisLayout::create(Axis::Column)->setAxisReverse(true));

    categoryMenu->setPosition(winSize.width / 2.84, winSize.height / 2);
    categoryMenu->setContentWidth(0);
    categoryMenu->setContentHeight(400);
    categoryMenu->setScale(0.75f);

    categoryMenu->updateLayout();

	/*
		shop button
	*/

	auto shards = this->getChildByID("shards-menu");
    this->getChildByID("top-left-menu")->setVisible(false);

    auto shopBtnSprite = CCSprite::create("shopBtnSprite.png"_spr);
    shopBtnSprite->setScale(0.85f);
    auto shopBtn = CCMenuItemSpriteExtra::create(
        shopBtnSprite, 
		this,
        menu_selector(GJGarageLayer::onShop)
    );

    shards->addChild(shopBtn);
    shopBtn->setID("shop-button"_spr);

    // Fix Button layout
    shards->setPosition(40, 90);
	shards->setContentHeight(135);
    shards->updateLayout();

    auto shardsBG = CCScale9Sprite::create("square02_001.png");
    shardsBG->setContentSize({60,210});
    shardsBG->setScale(0.7f);
    shardsBG->setPosition(shards->getPosition());
    shardsBG->setOpacity(75);
    this->addChild(shardsBG);
    shardsBG->setID("other-BG");

	/*
		Player Stage
	*/

    m_playerObject->setPosition({categoryMenu->getPositionX() / 2, 200});
    this->getChildByID("floor-line")->setPosition(categoryMenu->getPositionX() / 2, 175);
	this->getChildByID("floor-line")->setScaleX(0.35f);

    if (auto greyUsernameLock = getChildByID("username-lock")) {

		greyUsernameLock->setPosition(categoryMenu->getPositionX() / 2, 265);

	} else if (auto nameHint = this->getChildByID("username-hint")) {

		nameHint->setPosition({0,0});

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

    auto gridLayout = AxisLayout::create();
    gridLayout->setGrowCrossAxis(true);
    gridLayout->setGap(7.5);

    auto mainLayer = CCLayer::create();
    mainLayer->setPosition(winSize.width / 2, winSize.height / 2);
    mainLayer->ignoreAnchorPointForPosition(false);

    f->m_scrollLayer = ScrollLayer::create({scrollSize.width + 20, scrollSize.height - 10});
    f->m_scrollLayer->ignoreAnchorPointForPosition(false);
    f->m_scrollLayer->setPosition({winSize.width - (winSize.width / 3), winSize.height / 2});
    f->m_scrollLayer->m_contentLayer->setAnchorPoint({0.5,1});

    f->m_scrollBar = Scrollbar::create(f->m_scrollLayer);
    f->m_scrollBar->setPosition({winSize.width - (winSize.width / 35), winSize.height / 2});

    auto BG = CCScale9Sprite::create("square02_001.png");
    BG->setPosition(f->m_scrollLayer->getPosition());
    BG->setContentSize(f->m_scrollLayer->getContentSize() + CCSize{10,0});
    BG->setOpacity(75);
    mainLayer->addChild(BG);

    f->m_iconMenu = CCMenu::create();
    f->m_iconMenu->setLayout(gridLayout);
    f->m_iconMenu->setAnchorPoint({0.5, 1});
    f->m_iconMenu->setContentSize({f->m_scrollLayer->getContentWidth() - 10, 0});
    f->m_iconMenu->setID("icon-menu");

    createIconPage(); // sets up page
    ADD_TO_SCROLL(f->m_iconMenu);

    f->m_breakline = CCLayerColor::create({0, 0, 0, 100}, f->m_scrollLayer->m_contentLayer->getContentWidth(), 1);
    ADD_TO_SCROLL(f->m_breakline);
    f->m_breakline->setID("breakline");

    if (f->MORE_ICONS_ENABLED) {

        f->m_moreIconsMenu = CCMenu::create();
        f->m_moreIconsMenu->setAnchorPoint({0.5,1});
        f->m_moreIconsMenu->setLayout(gridLayout);
        f->m_moreIconsMenu->setContentSize({f->m_scrollLayer->getContentWidth() - 10, 0});
        f->m_moreIconsMenu->setID("more-icons");
    
        setupMoreIcons(); // sets up more icons
        ADD_TO_SCROLL(f->m_moreIconsMenu);

    }

    // UI change when Separate dual icons are enabled
    if (f->SEPARATE_DUAL_ENABLED) {
        m_playerObject->setPosition({60,195.5});
        auto p2 = this->getChildByID("player2-icon");
        p2->setPosition(120,195.5f);
        m_playerObject->setScale(1.3f);
        p2->setScale(1.3f);

        auto playerBtnMenu = this->getChildByID("player-buttons-menu");

        auto p1Btn = static_cast<CCMenuItemSpriteExtra*>(playerBtnMenu->getChildByID("player1-button"));
        p1Btn->setPosition(m_playerObject->getPosition());
        p1Btn->setTarget(this, menu_selector(garage::on2pSwitch));

        auto p2Btn = static_cast<CCMenuItemSpriteExtra*>(playerBtnMenu->getChildByID("player2-button"));
        p2Btn->setPosition(p2->getPosition());
        p2Btn->setTarget(this, menu_selector(garage::on2pSwitch));

        auto switch2pIcnBtn = static_cast<CCMenuItemSpriteExtra*>(shards->getChildByID("swap-2p-button"));
        switch2pIcnBtn->setTarget(this, menu_selector(garage::swapPlayerIcons));

        this->getChildByID("arrow-1")->setPosition(25.5f,195.5f);
        this->getChildByID("arrow-2")->setPosition(155.5f,195.5f);
    }

    adjustScroll();

    this->addChild(mainLayer);
    mainLayer->addChild(f->m_scrollLayer);
    mainLayer->addChild(f->m_scrollBar);
    
    mainLayer->setID("content"_spr);

    this->schedule(schedule_selector(garage::hideOverlaps),0,kCCRepeatForever,0);

    return true;
}

void garage::onSelectTab(CCObject* sender) {
    auto toggler = static_cast<CCMenuItemToggler*>(sender);
    auto icontype = toggler ? toggler->getTag() : -1;
    auto separateDual = Loader::get()->getLoadedMod("weebify.separate_dual_icons");

    auto f = m_fields.self();

    auto prev = static_cast<CCMenuItemToggler*>(toggler->getParent()->getChildByTag(as<int>(m_iconType)));
    prev->toggle(false);
    prev->setEnabled(true);

    m_iconType = as<IconType>(icontype);

    if (f->SEPARATE_DUAL_ENABLED) {
        separateDual->setSavedValue("lastmode", icontype);
        separateDual->setSavedValue("lasttype", icontype);
    }
    
    toggler->toggle(true);
    toggler->setEnabled(false);

    if (f->MORE_ICONS_ENABLED) setupMoreIcons(); // sets up more icons
    createIconPage(); // Changes page
    adjustScroll();
}