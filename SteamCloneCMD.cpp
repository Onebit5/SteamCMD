#include "User.h"
#include "Game.h"
#include "Utils.h"
#include "ANSIColors.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <conio.h>

std::vector<User> users;
std::vector<Game> games;
User* currentUser = nullptr;

std::string getHiddenPassword() {
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r') { 
        if (ch == '\b') { 
            if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}

void createAccount() {
    std::string username, password;
    ConsoleColors::setColor(ConsoleColors::BOLD);
    ConsoleColors::setColor(ConsoleColors::MAGENTA);
    std::cout << "\n=== Create Account ===\n";
    ConsoleColors::resetColor();
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    password = getHiddenPassword();
    users.push_back(User(username, password));
    saveUsers(users, "D:/Work/SteamCloneCMD/SteamCloneCMD/x64/Debug/data/users.txt");
    ConsoleColors::setColor(ConsoleColors::GREEN);
    std::cout << "Account created successfully!\n";
    ConsoleColors::resetColor();
}

void login() {
    std::string username, password;
    ConsoleColors::setColor(ConsoleColors::BOLD);
    ConsoleColors::setColor(ConsoleColors::MAGENTA);
    std::cout << "\n=== Login ===\n";
    ConsoleColors::resetColor();
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    password = getHiddenPassword();
    for (auto& user : users) {
        if (user.getUsername() == username && user.checkPassword(password)) {
            currentUser = &user;
            ConsoleColors::setColor(ConsoleColors::GREEN);
            std::cout << "Login successful!\n";
            ConsoleColors::resetColor();
            return;
        }
    }
    ConsoleColors::setColor(ConsoleColors::RED);
    std::cout << "Invalid username or password\n";
    ConsoleColors::resetColor();
}

void activateGame() {
    if (currentUser == nullptr) {
        ConsoleColors::setColor(ConsoleColors::RED);
        std::cout << "You need to log in first\n";
        ConsoleColors::resetColor();
        return;
    }
    std::string gameKey;
    ConsoleColors::setColor(ConsoleColors::BOLD);
    ConsoleColors::setColor(ConsoleColors::MAGENTA);
    std::cout << "\n=== Activate Game ===\n";
    ConsoleColors::resetColor();
    std::cout << "Game Key: ";
    std::cin >> gameKey;
    for (const auto& game : games) {
        if (game.getKey() == gameKey) {
            char confirm;
            std::cout << "The game " << game.getName() << " will be activated.\n";
            std::cout << "Do you want to activate this game? (Y/N): ";
            std::cin >> confirm;
            if (confirm == 'Y' || confirm == 'y') {
                currentUser->addGame(gameKey);
                ConsoleColors::setColor(ConsoleColors::GREEN);
                std::cout << "Game activated: " << game.getName() << "\n";
                ConsoleColors::resetColor();
                saveUsers(users, "D:/Work/SteamCloneCMD/SteamCloneCMD/x64/Debug/data/users.txt");
            }
            else {
                ConsoleColors::setColor(ConsoleColors::YELLOW);
                std::cout << "Activation cancelled\n";
                ConsoleColors::resetColor();
            }
            return;
        }
    }
    ConsoleColors::setColor(ConsoleColors::RED);
    std::cout << "Invalid game key\n";
    ConsoleColors::resetColor();
}

void viewLibrary() {
    if (currentUser == nullptr) {
        ConsoleColors::setColor(ConsoleColors::RED);
        std::cout << "You need to log in first\n";
        ConsoleColors::resetColor();
        return;
    }
    ConsoleColors::setColor(ConsoleColors::BOLD);
    ConsoleColors::setColor(ConsoleColors::MAGENTA);
    std::cout << "\n=== Game Library ===\n";
    ConsoleColors::resetColor();
    for (const auto& gameKey : currentUser->getGames()) {
        for (const auto& game : games) {
            if (game.getKey() == gameKey) {
                std::cout << "- " << game.getName();
                if (currentUser->isGameInstalled(gameKey)) {
                    ConsoleColors::setColor(ConsoleColors::GREEN);
                    std::cout << " [INSTALLED]";
                    ConsoleColors::resetColor();
                }
                else {
                    ConsoleColors::setColor(ConsoleColors::RED);
                    std::cout << " [NOT INSTALLED]";
                    ConsoleColors::resetColor();
                }
                std::cout << "\n";
            }
        }
    }
}

void showProgressBar(int duration) {
    const int width = 50;
    for (int i = 0; i <= duration; ++i) {
        std::cout << "[";
        int pos = (i * width) / duration;
        for (int j = 0; j < width; ++j) {
            if (j < pos) std::cout << "=";
            else if (j == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int((i * 100) / duration) << " %";
        std::cout << " (" << i << "s/" << duration << "s)";
        std::cout << "\r";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::endl;
}

void downloadGame() {
    if (currentUser == nullptr) {
        ConsoleColors::setColor(ConsoleColors::RED);
        std::cout << "You need to log in first\n";
        ConsoleColors::resetColor();
        return;
    }
    std::string gameName;
    ConsoleColors::setColor(ConsoleColors::BOLD);
    ConsoleColors::setColor(ConsoleColors::MAGENTA);
    std::cout << "\n=== Download Game ===\n";
    ConsoleColors::resetColor();
    std::cout << "Game Name: ";
    std::cin >> gameName;

    for (const auto& game : games) {
        if (game.getName() == gameName) {
            bool alreadyDownloaded = false;
            for (const auto& key : currentUser->getGames()) {
                if (key == game.getKey()) {
                    ConsoleColors::setColor(ConsoleColors::BLUE);
                    std::cout << "Downloading " << gameName << "...\n";
                    ConsoleColors::resetColor();
                    showProgressBar(game.getDownloadDuration());
                    currentUser->installGame(game.getKey());
                    saveUsers(users, "D:/Work/SteamCloneCMD/SteamCloneCMD/x64/Debug/data/users.txt");
                    ConsoleColors::setColor(ConsoleColors::GREEN);
                    std::cout << "Game downloaded and installed!\n";
                    ConsoleColors::resetColor();
                    alreadyDownloaded = true;
                    break;
                }
            }
            if (alreadyDownloaded) {
                ConsoleColors::setColor(ConsoleColors::RED);
                std::cout << "Game not found in the library.\n";
                ConsoleColors::resetColor();
                return;
            }
        }
    }
    std::cout << "Game not found in the library.\n";
}

void runGame() {
    if (currentUser == nullptr) {
        ConsoleColors::setColor(ConsoleColors::RED);
        std::cout << "You need to log in first\n";
        ConsoleColors::resetColor();
        return;
    }
    std::string gameName;
    ConsoleColors::setColor(ConsoleColors::BOLD);
    ConsoleColors::setColor(ConsoleColors::MAGENTA);
    std::cout << "\n=== Run Game ===\n";
    ConsoleColors::resetColor();
    std::cout << "Game Name: ";
    std::cin >> gameName;

    bool gameFound = false;
    for (const auto& gameKey : currentUser->getGames()) {
        for (const auto& game : games) {
            if (game.getKey() == gameKey && game.getName() == gameName) {
                gameFound = true;
                if (!currentUser->isGameInstalled(gameKey)) {
                    ConsoleColors::setColor(ConsoleColors::RED);
                    std::cout << "Game is not installed. Please install the game first.\n";
                    ConsoleColors::resetColor();
                    return;
                }
                ConsoleColors::setColor(ConsoleColors::BLUE);
                std::cout << "Running " << gameName << "...\n";
                ConsoleColors::resetColor();
                std::this_thread::sleep_for(std::chrono::seconds(2));
                ConsoleColors::setColor(ConsoleColors::GREEN);
                std::cout << "Game " << gameName << " is now running.\n";
                ConsoleColors::resetColor();
                return;
            }
        }
    }
    if (!gameFound) {
        ConsoleColors::setColor(ConsoleColors::RED);
        std::cout << "Game not found in your library.\n";
        ConsoleColors::resetColor();
    }
}

void uninstallGame() {
    if (currentUser == nullptr) {
        ConsoleColors::setColor(ConsoleColors::RED);
        std::cout << "You need to log in first\n";
        ConsoleColors::resetColor();
        return;
    }
    std::string gameName;
    ConsoleColors::setColor(ConsoleColors::BOLD);
    ConsoleColors::setColor(ConsoleColors::MAGENTA);
    std::cout << "\n=== Uninstall Game ===\n";
    ConsoleColors::resetColor();
    std::cout << "Game Name: ";
    std::cin >> gameName;

    for (const auto& game : games) {
        if (game.getName() == gameName) {
            if (!currentUser->isGameInstalled(game.getKey())) {
                ConsoleColors::setColor(ConsoleColors::YELLOW);
                std::cout << "Game is not installed.\n";
                ConsoleColors::resetColor();
                return;
            }
            ConsoleColors::setColor(ConsoleColors::BLUE);
            std::cout << "Uninstalling " << gameName << "...\n";
            ConsoleColors::resetColor();
            showProgressBar(game.getUninstallDuration());
            currentUser->uninstallGame(game.getKey());
            saveUsers(users, "D:/Work/SteamCloneCMD/SteamCloneCMD/x64/Debug/data/users.txt");
            ConsoleColors::setColor(ConsoleColors::GREEN);
            std::cout << "Game uninstalled.\n";
            ConsoleColors::resetColor();
            return;
        }
    }
    ConsoleColors::setColor(ConsoleColors::RED);
    std::cout << "Game not found in your library.\n";
    ConsoleColors::resetColor();
}

int main() {
    users = loadUsers("D:/Work/SteamCloneCMD/SteamCloneCMD/x64/Debug/data/users.txt");
    games = loadGames("D:/Work/SteamCloneCMD/SteamCloneCMD/x64/Debug/data/games.txt");

    int option;
    do {
        ConsoleColors::setColor(ConsoleColors::BOLD);
        ConsoleColors::setColor(ConsoleColors::CYAN);
        std::cout << "\n=== Main Menu ===\n";
        ConsoleColors::resetColor();
        std::cout << "1. Create Account\n2. Login\n3. Activate Game Key\n4. View Library\n5. Download Game\n6. Uninstall Game\n7. Run Game\n8. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> option;
        switch (option) {
        case 1: createAccount(); break;
        case 2: login(); break;
        case 3: activateGame(); break;
        case 4: viewLibrary(); break;
        case 5: downloadGame(); break;
        case 6: uninstallGame(); break;
        case 7: runGame(); break;
        case 8:
            saveUsers(users, "D:/Work/SteamCloneCMD/SteamCloneCMD/x64/Debug/data/users.txt");
            ConsoleColors::setColor(ConsoleColors::GREEN);
            std::cout << "Goodbye!\n";
            ConsoleColors::resetColor();
            break;
        default:
            ConsoleColors::setColor(ConsoleColors::RED);
            std::cout << "Invalid choice\n";
            ConsoleColors::resetColor();
        }
    } while (option != 8);

    return 0;
}
