#pragma once

#ifndef GAME_H
#define GAME_H

#include <string>

class Game {
public:
    Game(const std::string& key, const std::string& name, int downloadDuration, int uninstallDuration);

    std::string getKey() const;
    std::string getName() const;
    int getDownloadDuration() const;
    int getUninstallDuration() const;

private:
    std::string key;
    std::string name;
    int downloadDuration;
    int uninstallDuration;
};

#endif // GAME_H
