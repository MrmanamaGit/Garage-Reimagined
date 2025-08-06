// hello ;)

#include <Geode/Geode.hpp>

using namespace geode::prelude;

$execute {
    listenForSettingChanges("icon-colours", +[](bool value) {
        log::info("farts: {}", value);
    });
}