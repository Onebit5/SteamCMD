#pragma once

#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
public:
    User(const std::string& username, const std::string& password);

    std::string getUsername() const;
    bool checkPassword(const std::string& password) const;

    void addGame(const std::string& gameKey);
    const std::vector<std::string>& getGames() const;

    void installGame(const std::string& gameKey);
    bool isGameInstalled(const std::string& gameKey) const;
    void uninstallGame(const std::string& gameKey);

    std::string toString() const;
    static User fromString(const std::string& userString);

private:
    std::string username;
    std::string password;
    std::vector<std::string> games;
    std::vector<std::string> installedGames;
};

#endif // USER_H
