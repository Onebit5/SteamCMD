#include "game.h"

Game::Game(const std::string& key, const std::string& name, int downloadDuration, int uninstallDuration)
    : key(key), name(name), downloadDuration(downloadDuration), uninstallDuration(uninstallDuration) {}

std::string Game::getKey() const {
    return key;
}

std::string Game::getName() const {
    return name;
}

int Game::getDownloadDuration() const {
    return downloadDuration;
}

int Game::getUninstallDuration() const {
    return uninstallDuration;
}
