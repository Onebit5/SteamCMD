#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "user.h"
#include "game.h"
#include <vector>
#include <string>

std::vector<User> loadUsers(const std::string& filepath);
void saveUsers(const std::vector<User>& users, const std::string& filepath);
std::vector<Game> loadGames(const std::string& filepath);

#endif // UTILS_H
