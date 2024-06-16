#include "Utils.h"
#include <fstream>
#include <sstream>

std::vector<User> loadUsers(const std::string& filepath) {
    std::vector<User> users;
    std::ifstream file(filepath);
    std::string line;

    while (std::getline(file, line)) {
        users.push_back(User::fromString(line));
    }

    return users;
}

void saveUsers(const std::vector<User>& users, const std::string& filepath) {
    std::ofstream file(filepath);

    for (const auto& user : users) {
        file << user.toString() << std::endl;
    }
}

std::vector<Game> loadGames(const std::string& filepath) {
    std::vector<Game> games;
    std::ifstream file(filepath);
    std::string line, key, name;
    int downloadDuration, uninstallDuration;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> key >> name >> downloadDuration >> uninstallDuration) {
            games.push_back(Game(key, name, downloadDuration, uninstallDuration));
        }
    }

    return games;
}

void saveGames(const std::vector<Game>& games, const std::string& filepath) {
    std::ofstream file(filepath);

    for (const auto& game : games) {
        file << game.getKey() << " " << game.getName() << " " << game.getDownloadDuration() << " " << game.getUninstallDuration() << std::endl;
    }
}
