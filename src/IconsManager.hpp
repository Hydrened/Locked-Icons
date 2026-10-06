#pragma once
#include <Geode/Geode.hpp>
#include "utils.hpp"

using namespace geode::prelude;

class IconsManager {
public:
    static Icons getFromGameManager(GameManager* gm);
    static void applyToGameManager(GameManager* gm, Icons const& p);
    
    static void save(Icons const& p);
    static Icons load();
};
