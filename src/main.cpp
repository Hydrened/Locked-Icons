#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/GameLevelManager.hpp>
#include "utils.hpp"
#include "IconsManager.hpp"

class $modify(LockedIcons, GameLevelManager) {
    // HOOK
    void updateUserScore() {
        if (LockedIcons::isLocked()) {
            lockedUpdate();
        }
        else {
            GameLevelManager::updateUserScore();
        }
    }

    // OTHER
    static bool isLocked() {
        geode::Mod* mod = Mod::get();
        bool locked = mod->getSavedValue<bool>("locked", false);
        bool hasSavedProfile = mod->getSavedValue<bool>("hasSavedProfile", false);

        return locked && hasSavedProfile;
    }

    void lockedUpdate() {
        GameManager* gm = GameManager::get();
        Icons real = IconsManager::getFromGameManager(gm);

        IconsManager::applyToGameManager(gm, IconsManager::load());
        GameLevelManager::updateUserScore();
        IconsManager::applyToGameManager(gm, real);
    }
};

class $modify(LockedIconsProfilePage, ProfilePage) {
    // HOOK
    void loadPageFromUserInfo(GJUserScore* score) {
        ProfilePage::loadPageFromUserInfo(score);

        if (score->isCurrentUser()) {
            initProfile();
        }
    }

    // INIT
    void initProfile() {
        CCMenu* leftMenu = getLeftMenu();
        if (leftMenu == nullptr) {
            return;
        }

        CCMenuItemToggler* toggleBox = getToggleBox();
        bool hasBeenInitialized = (toggleBox != nullptr);

        if (!hasBeenInitialized) {
            toggleBox = initToggleMenu(leftMenu);
        }

        bool isToggled = Mod::get()->getSavedValue<bool>("locked", false);
        toggleBox->toggle(isToggled);
    }

    CCMenuItemToggler* initToggleMenu(CCMenu* menu) {
        CCMenu* toggleMenu = CCMenu::create();
        toggleMenu->setZOrder(100);
        toggleMenu->setID("locked-icons-toggle-menu"_spr);
        toggleMenu->setContentSize({ 30.0f, 33.0f });
        menu->addChild(toggleMenu);

        initToggleLabel(toggleMenu);
        CCMenuItemToggler* toggleBox = initToggleBox(toggleMenu);

        menu->updateLayout();

        return toggleBox;
    }

    void initToggleLabel(CCMenu* menu) {
        CCLabelBMFont* toggleLabel = CCLabelBMFont::create("Lock\nicons", "bigFont.fnt");
        toggleLabel->setID("locked-icons-toggle-label"_spr);
        toggleLabel->setPosition({ 15.0f, 27.0f });
        toggleLabel->setScale(0.2f);
        toggleLabel->setAlignment(kCCTextAlignmentCenter);
        menu->addChild(toggleLabel);
    }

    CCMenuItemToggler* initToggleBox(CCMenu* menu) {
        CCSprite* off = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        CCSprite* on = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        
        CCMenuItemToggler* toggleBox = CCMenuItemToggler::create(off, on, this, menu_selector(LockedIconsProfilePage::onToggleBoxChange));
        toggleBox->setID("locked-icons-toggle-box"_spr);
        toggleBox->setPosition({ 15.0f, 10.0f });
        toggleBox->setScale(0.5f);
        menu->addChild(toggleBox);

        return toggleBox;
    }

    // EVENTS
    void onToggleBoxChange(CCObject* sender) {
        CCMenuItemToggler* toggleBox = static_cast<CCMenuItemToggler*>(sender);
        bool toggleBoxIsOn = !toggleBox->isToggled();

        if (toggleBoxIsOn) {
            onToggleBoxOn();
        }
        else {
            onToggleBoxOff();
        }

        GameLevelManager::get()->updateUserScore();
    }

    void onToggleBoxOn() {
        IconsManager::save(IconsManager::getFromGameManager(GameManager::get()));

        geode::Mod* mod = Mod::get();
        mod->setSavedValue("hasSavedProfile", true);
        mod->setSavedValue("locked", true);
    }

    void onToggleBoxOff() {
        geode::Mod* mod = Mod::get();
        mod->setSavedValue("locked", false);
    }

    // GETTERS
    CCMenu* getLeftMenu() {
        CCNode* leftMenuNode = m_mainLayer->getChildByID("left-menu");
        return typeinfo_cast<CCMenu*>(leftMenuNode);
    }

    CCMenuItemToggler* getToggleBox() {
        CCNode* toggleNode = m_mainLayer->getChildByIDRecursive("locked-icons-toggle-box"_spr);
        return typeinfo_cast<CCMenuItemToggler*>(toggleNode);
    }
};
