#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

#include <Geode/modify/GJGarageLayer.hpp>
class $modify(other, GJGarageLayer) {
	bool init() {
		if(!GJGarageLayer::init()) return false;

		auto winSize = CCDirector::sharedDirector()->getWinSize();

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
			menu_selector(other::onSettings)
		);

		settings->setID("settings"_spr);

		back->addChild(settings);
		back->updateLayout();

		/*
			Category Menu
		*/

		auto categoryMenu = this->getChildByID("category-menu");

        auto categoryLayout = AxisLayout::create(Axis::Column);
        categoryLayout->setAxisReverse(true);

        categoryMenu->setLayout(categoryLayout);

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

		return true;
	}

	void onSettings(CCObject*) {
		openSettingsPopup(Mod::get());
	}
};