#include "Geode/cocos/cocoa/CCObject.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

class garage : public geode::Modify<garage, GJGarageLayer> {
    public:
        struct Fields {
            ScrollLayer* m_scrollLayer = nullptr;
            Scrollbar* m_scrollBar = nullptr;

            CCSprite* m_cursorCust1 = nullptr;
            CCSprite* m_cursorCust2 = nullptr;

            Ref<AxisLayout> m_layout = nullptr;
        
            CCMenu* m_iconMenu = nullptr;
            CCArray* m_iconArray = nullptr;
        };

        bool init() $override;
        void onSelectTab(CCObject* sender) $override;
        void onPaint(CCObject* sender) $override {
            static_cast<FLAlertLayer*>(CharacterColorPage::create())->show();
        };

        void onIcon(CCObject* sender);
        void onShipFire(CCObject* sender);
        void onAnimation(CCObject* sender);

        // void onMoreIcons(CCObject* sender);

        void onSettings(CCObject* sender) {
            openSettingsPopup(Mod::get());
        };

        void setPlayerIcon(int ID);
        
        void createIconPage();
        void createMenu();
        void refreshCursor();
        void adjustScroll();
};
