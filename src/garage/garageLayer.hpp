#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>

#include <hiimjustin000.more_icons/include/MoreIcons.hpp>

using namespace geode::prelude;

#define ADD_TO_SCROLL(...) f->m_scrollLayer->m_contentLayer->addChild(__VA_ARGS__)

class garage : public geode::Modify<garage, GJGarageLayer> {
    public:
        struct Fields {
            const float ICON_SIZE = 0.6f;
            const int LOCK_OPACITY = 70;
            const int PADDING = 15;

            const bool MORE_ICONS_ENABLED = Loader::get()->isModLoaded("hiimjustin000.more_icons");

            ScrollLayer* m_scrollLayer = nullptr;
            Scrollbar* m_scrollBar = nullptr;

            CCLayerColor* m_breakline = nullptr; // shhh, no questions

            CCSprite* m_cursorCust1 = nullptr;
            CCSprite* m_cursorCust2 = nullptr;
            CCSprite* m_cursorMoreIcons = nullptr;

            CCMenu* m_moreIconsMenu = nullptr;
            CCMenu* m_iconMenu = nullptr;
        };

        
        // Overrided funcs
        bool init() $override;
        void onSelectTab(CCObject* sender) $override;
        void onPaint(CCObject* sender) $override {
            static_cast<FLAlertLayer*>(CharacterColorPage::create())->show();
        };

        // Callbacks
        void onIcon(CCObject* sender);
        void onShipFire(CCObject* sender);
        void onAnimation(CCObject* sender);
        void onSettings(CCObject* sender) {
            openSettingsPopup(Mod::get());
        };

        void setPlayerIcon(int ID); 
        
        void createIconPage();

        // compat
        void setupMoreIcons();
        void onCustomIcon(CCObject* sender);
        void hideNodes();

        // UI
        void refreshCursor();
        void adjustScroll();
};