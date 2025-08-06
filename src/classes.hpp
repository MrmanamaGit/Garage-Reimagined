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
            const bool SEPARATE_DUAL_ENABLED = Loader::get()->isModLoaded("weebify.separate_dual_icons");
            ScrollLayer* m_scrollLayer = nullptr;
            Scrollbar* m_scrollBar = nullptr;

            CCLayerColor* m_breakline = nullptr; // shhh, no questions

            CCSprite* m_cursorCust1 = nullptr;
            CCSprite* m_cursorCust2 = nullptr;
            CCSprite* m_cursorMoreIcons = nullptr;

            CCMenu* m_moreIconsMenu = nullptr;
            CCMenu* m_iconMenu = nullptr;
        };

        static void onModify(ModifyBase<ModifyDerive<garage, GJGarageLayer>>& self) {
            (void)self.setHookPriorityBefore("GJGarageLayer::init","weebify.separate_dual_icons");
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
        void hideOverlaps(float dt);

        // compat
        void setupMoreIcons();
        void onCustomIcon(CCObject* sender);

        std::string iconTypeToStr(IconType type) {
            switch (type) {
                case IconType::Cube: return "cube";
                case IconType::Ship: return "ship";
                case IconType::Ball: return "roll";
                case IconType::Ufo: return "bird";
                case IconType::Wave: return "dart";
                case IconType::Robot: return "robot";
                case IconType::Spider: return "spider";
                case IconType::Swing: return "swing";
                case IconType::Jetpack: return "jetpack";
                case IconType::DeathEffect: return "death";
                case IconType::Special: return "trail";
                case IconType::ShipFire: return "shiptrail";
                default: return nullptr;
            }
        };

        void on2pSwitch(CCObject*); // when clicking the icons
        void swapPlayerIcons(CCObject*); // when clicking the button is the shards menu

        // UI
        void refreshCursor();
        void adjustScroll();

};

class moreIconInfoPopup : public geode::Popup<IconInfo*> {
    protected:
        bool setup(IconInfo* icon) $override {
            setTitle(icon->name);
            setContentSize(CCDirector::sharedDirector()->getWinSize());

            setCloseButtonSpr(ButtonSprite::create("OK"));
            m_closeBtn->setPosition(150, 27.5);

            auto displayIcn = GJItemIcon::createBrowserItem(UnlockType::Cube, 0);
            MoreIcons::updateSimplePlayer(displayIcn->getChildByType<SimplePlayer*>(0), icon->name, icon->type);
            displayIcn->setScale(1.25f);
            displayIcn->setPosition({150, 170});
            m_mainLayer->addChild(displayIcn);

            auto descBG = CCScale9Sprite::create("square02_001.png");
            descBG->setContentSize({260,90});
            descBG->setPosition(150, 95);
            descBG->setOpacity(75);
            auto desc = TextArea::create(fmt::format("This <cg>{}</c> is added by the <cl>More Icons</c> mod.", ItemInfoPopup::nameForUnlockType(0, GameManager::get()->iconTypeToUnlockType(icon->type))), "bigFont.fnt", 1, 600.0f, { 0.5f, 1.0f }, 42.0f, false);
            desc->setScale(0.4f);
            desc->setPosition({150, 100});

            m_mainLayer->addChild(descBG);
            m_mainLayer->addChild(desc);

            return true;
        }
    public:
        static moreIconInfoPopup* create(IconInfo* icon) {
            auto ret = new moreIconInfoPopup();
            if (ret && ret->initAnchored(300.0f, 230.0f, icon)) {
                ret->autorelease();
                return ret;
            }

            delete ret;
            return nullptr;
        }
};