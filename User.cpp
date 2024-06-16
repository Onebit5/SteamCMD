#include "User.h"
#include <sstream>
#include <algorithm>

User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}

std::string User::getUsername() const {
    return username;
}

bool User::checkPassword(const std::string& password) const {
    return this->password == password;
}

void User::addGame(const std::string& gameKey) {
    games.push_back(gameKey);
}

const std::vector<std::string>& User::getGames() const {
    return games;
}

void User::installGame(const std::string& gameKey) {
    if (std::find(installedGames.begin(), installedGames.end(), gameKey) == installedGames.end()) {
        installedGames.push_back(gameKey);
    }
}

bool User::isGameInstalled(const std::string& gameKey) const {
    return std::find(installedGames.begin(), installedGames.end(), gameKey) != installedGames.end();
}

void User::uninstallGame(const std::string& gameKey) {
    installedGames.erase(std::remove(installedGames.begin(), installedGames.end(), gameKey), installedGames.end());
}

std::string User::toString() const {
    std::ostringstream oss;
    oss << username << " " << password;
    for (const auto& game : games) {
        oss << " " << game;
    }
    oss << " | ";
    for (const auto& game : installedGames) {
        oss << " " << game;
    }
    return oss.str();
}

User User::fromString(const std::string& userString) {
    std::istringstream iss(userString);
    std::string username, password;
    iss >> username >> password;
    User user(username, password);

    std::string segment;
    bool readingInstalledGames = false;
    while (iss >> segment) {
        if (segment == "|") {
            readingInstalledGames = true;
        }
        else if (readingInstalledGames) {
            user.installedGames.push_back(segment);
        }
        else {
            user.games.push_back(segment);
        }
    }

    return user;
}