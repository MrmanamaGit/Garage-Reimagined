#include "../classes.hpp"
#include "Geode/Enums.hpp"
#include "hiimjustin000.more_icons/include/MoreIcons.hpp"

void garage::on2pSwitch(CCObject*) {
    auto f = m_fields.self();
    auto gm = GameManager::get();
    auto separateDual = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    separateDual->setSavedValue("2pselected", !separateDual->getSavedValue<bool>("2pselected"));

    bool is2p = separateDual->getSavedValue<bool>("2pselected");

    if (is2p) {

        this->getChildByID("arrow-1")->setVisible(false);
        this->getChildByID("arrow-2")->setVisible(true);
        
    } else {

        this->getChildByID("arrow-1")->setVisible(true);
        this->getChildByID("arrow-2")->setVisible(false);

    }

    refreshCursor();
}

void garage::swapPlayerIcons(CCObject*) {
    auto gm = GameManager::get();
    auto separateDual = Loader::get()->getLoadedMod("weebify.separate_dual_icons");

    int cube = gm->getPlayerFrame();
    int ship = gm->getPlayerShip();
    int ball = gm->getPlayerBall();
    int ufo = gm->getPlayerBird();
    int wave = gm->getPlayerDart();
    int robot = gm->getPlayerRobot();
    int spider = gm->getPlayerSpider();
    int jp = gm->getPlayerJetpack();
    int swing = gm->getPlayerSwing();
    int de = gm->getPlayerDeathEffect();
    int sf = gm->getPlayerShipFire();
    int trail = gm->getPlayerStreak();

    int cubeDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::Cube));
    int shipDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::Ship));
    int ballDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::Ball));
    int ufoDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::Ufo));
    int waveDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::Wave));
    int robotDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::Robot));
    int spiderDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::Spider));
    int jpDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::Jetpack));
    int swingDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::Swing));
    int deDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::DeathEffect));
    int sfDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::ShipFire));
    int trailDual = separateDual->getSavedValue<int>(iconTypeToStr(IconType::Special));

    gm->setPlayerFrame(cubeDual);
    gm->setPlayerShip(shipDual);
    gm->setPlayerBall(ballDual);
    gm->setPlayerBird(ufoDual);
    gm->setPlayerDart(waveDual);
    gm->setPlayerRobot(robotDual);
    gm->setPlayerSpider(spiderDual);
    gm->setPlayerJetpack(jpDual);
    gm->setPlayerSwing(swingDual);
    gm->setPlayerDeathEffect(deDual);
    gm->setPlayerShipStreak(sfDual);
    gm->setPlayerStreak(trailDual);

    separateDual->setSavedValue(iconTypeToStr(IconType::Cube), cube);
    separateDual->setSavedValue(iconTypeToStr(IconType::Ship), ship);
    separateDual->setSavedValue(iconTypeToStr(IconType::Ball), ball);
    separateDual->setSavedValue(iconTypeToStr(IconType::Ufo), ufo);
    separateDual->setSavedValue(iconTypeToStr(IconType::Wave), wave);
    separateDual->setSavedValue(iconTypeToStr(IconType::Robot), robot);
    separateDual->setSavedValue(iconTypeToStr(IconType::Spider), spider);
    separateDual->setSavedValue(iconTypeToStr(IconType::Jetpack), jp);
    separateDual->setSavedValue(iconTypeToStr(IconType::Swing), swing);
    separateDual->setSavedValue(iconTypeToStr(IconType::DeathEffect), de);
    separateDual->setSavedValue(iconTypeToStr(IconType::ShipFire), sf);
    separateDual->setSavedValue(iconTypeToStr(IconType::Special), trail);

    if (m_fields->MORE_ICONS_ENABLED) {

        auto cube = MoreIcons::activeIcon(IconType::Cube);
        auto ship = MoreIcons::activeIcon(IconType::Ship);
        auto ball = MoreIcons::activeIcon(IconType::Ball);
        auto ufo = MoreIcons::activeIcon(IconType::Ufo);
        auto wave = MoreIcons::activeIcon(IconType::Wave);
        auto robot = MoreIcons::activeIcon(IconType::Robot);
        auto spider = MoreIcons::activeIcon(IconType::Spider);
        auto jp = MoreIcons::activeIcon(IconType::Jetpack);
        auto swing = MoreIcons::activeIcon(IconType::Swing);
        auto de = MoreIcons::activeIcon(IconType::DeathEffect);
        auto sf = MoreIcons::activeIcon(IconType::ShipFire);
        auto trail = MoreIcons::activeIcon(IconType::Special);

        auto cubeDual = MoreIcons::activeIcon(IconType::Cube, true);
        auto shipDual = MoreIcons::activeIcon(IconType::Ship, true);
        auto ballDual = MoreIcons::activeIcon(IconType::Ball, true);
        auto ufoDual = MoreIcons::activeIcon(IconType::Ufo, true);
        auto waveDual = MoreIcons::activeIcon(IconType::Wave, true);
        auto robotDual = MoreIcons::activeIcon(IconType::Robot, true);
        auto spiderDual = MoreIcons::activeIcon(IconType::Spider, true);
        auto jpDual = MoreIcons::activeIcon(IconType::Jetpack, true);
        auto swingDual = MoreIcons::activeIcon(IconType::Swing, true);
        auto deDual = MoreIcons::activeIcon(IconType::DeathEffect, true);
        auto sfDual = MoreIcons::activeIcon(IconType::ShipFire, true);
        auto trailDual = MoreIcons::activeIcon(IconType::Special, true);

        MoreIcons::setIcon(cube, IconType::Cube, true);
        MoreIcons::setIcon(ship, IconType::Ship, true);
        MoreIcons::setIcon(ball, IconType::Ball, true);
        MoreIcons::setIcon(ufo, IconType::Ufo, true);
        MoreIcons::setIcon(wave, IconType::Wave, true);
        MoreIcons::setIcon(robot, IconType::Robot, true);
        MoreIcons::setIcon(spider, IconType::Spider, true);
        MoreIcons::setIcon(jp, IconType::Jetpack, true);
        MoreIcons::setIcon(swing, IconType::Swing, true);
        MoreIcons::setIcon(de, IconType::DeathEffect, true);
        MoreIcons::setIcon(sf, IconType::ShipFire, true);
        MoreIcons::setIcon(trail, IconType::Special, true);

        MoreIcons::setIcon(cubeDual, IconType::Cube);
        MoreIcons::setIcon(shipDual, IconType::Ship);
        MoreIcons::setIcon(ballDual, IconType::Ball);
        MoreIcons::setIcon(ufoDual, IconType::Ufo);
        MoreIcons::setIcon(waveDual, IconType::Wave);
        MoreIcons::setIcon(robotDual, IconType::Robot);
        MoreIcons::setIcon(spiderDual, IconType::Spider);
        MoreIcons::setIcon(jpDual, IconType::Jetpack);
        MoreIcons::setIcon(swingDual, IconType::Swing);
        MoreIcons::setIcon(deDual, IconType::DeathEffect);
        MoreIcons::setIcon(sfDual, IconType::ShipFire);
        MoreIcons::setIcon(trailDual, IconType::Special);

    }

    int colour1 = gm->getPlayerColor();
    int colour2 = gm->getPlayerColor2();
    int colour1Dual = separateDual->getSavedValue<int>("color1");
    int colour2Dual = separateDual->getSavedValue<int>("color2");

    gm->setPlayerColor(colour1Dual);
    gm->setPlayerColor2(colour2Dual);
    separateDual->setSavedValue("color1", colour1);
    separateDual->setSavedValue("color2", colour2);

    refreshCursor();
}