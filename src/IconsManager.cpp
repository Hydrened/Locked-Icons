#include "IconsManager.hpp"

Icons IconsManager::getFromGameManager(GameManager* gm) {
    return {
        gm->m_playerFrame, gm->m_playerShip, gm->m_playerBall,
        gm->m_playerBird, gm->m_playerDart, gm->m_playerRobot,
        gm->m_playerSpider, gm->m_playerSwing, gm->m_playerJetpack,
        gm->m_playerStreak, gm->m_playerDeathEffect,
        gm->m_playerColor, gm->m_playerColor2, gm->m_playerGlowColor,
        gm->m_playerGlow,
        gm->m_playerIconType
    };
}

void IconsManager::applyToGameManager(GameManager* gm, Icons const& p) {
    gm->m_playerFrame = p.frame;
    gm->m_playerShip = p.ship;
    gm->m_playerBall = p.ball;
    gm->m_playerBird = p.ufo;
    gm->m_playerDart = p.wave;
    gm->m_playerRobot = p.robot;
    gm->m_playerSpider = p.spider;
    gm->m_playerSwing = p.swing;
    gm->m_playerJetpack = p.jetpack;
    gm->m_playerStreak = p.streak;
    gm->m_playerDeathEffect = p.explosion;
    gm->m_playerColor = p.color1;
    gm->m_playerColor2 = p.color2;
    gm->m_playerGlowColor = p.color3;
    gm->m_playerGlow = p.glow;
    gm->m_playerIconType = p.iconType;
}

void IconsManager::save(Icons const& p) {
    geode::Mod* mod = Mod::get();
    mod->setSavedValue("frame", p.frame);
    mod->setSavedValue("ship", p.ship);
    mod->setSavedValue("ball", p.ball);
    mod->setSavedValue("ufo", p.ufo);
    mod->setSavedValue("wave", p.wave);
    mod->setSavedValue("robot", p.robot);
    mod->setSavedValue("spider", p.spider);
    mod->setSavedValue("swing", p.swing);
    mod->setSavedValue("jetpack", p.jetpack);
    mod->setSavedValue("streak", p.streak);
    mod->setSavedValue("explosion", p.explosion);
    mod->setSavedValue("color1", p.color1);
    mod->setSavedValue("color2", p.color2);
    mod->setSavedValue("color3", p.color3);
    mod->setSavedValue("glow", p.glow);
    mod->setSavedValue("iconType", static_cast<int>(p.iconType));
}

Icons IconsManager::load() {
    geode::Mod* mod = Mod::get();
    return {
        mod->getSavedValue<int>("frame"), mod->getSavedValue<int>("ship"),
        mod->getSavedValue<int>("ball"), mod->getSavedValue<int>("ufo"),
        mod->getSavedValue<int>("wave"), mod->getSavedValue<int>("robot"),
        mod->getSavedValue<int>("spider"), mod->getSavedValue<int>("swing"),
        mod->getSavedValue<int>("jetpack"), mod->getSavedValue<int>("streak"),
        mod->getSavedValue<int>("explosion"),
        mod->getSavedValue<int>("color1"), mod->getSavedValue<int>("color2"),
        mod->getSavedValue<int>("color3"),
        mod->getSavedValue<bool>("glow"),
        static_cast<IconType>(mod->getSavedValue<int>("iconType"))
    };
}
