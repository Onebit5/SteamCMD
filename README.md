# SteamCMD Documentation
## Table of Contents

  * Overview
  * Project Structure
  * Class Descriptions
     * User Class
     * Game Class
  * Utility Functions
  * Main Program Flow
     * Creating an Account
     * Logging In
     * Activating a Game Key
     * Viewing the Game Library
     * Downloading a Game
     * Uninstalling a Game
     * Running a Game
  * Building and Running the Project

## Overview

SteamCMD is a command-line based application that simulates the basic functionalities of the Steam client. It allows users to create accounts, log in, activate game keys, view their game library, download games, uninstall games, and run games.
### Project Structure

The project is organized into several files, each serving a specific purpose:

  * User.h/User.cpp: Define and implement the User class.
  * Game.h/Game.cpp: Define and implement the Game class.
  * Utils.h/Utils.cpp: Provide utility functions for saving/loading data and other operations.
  * ANSIColors.h: Define ANSI color codes for console output.
  * SteamCMD.cpp: Contains the main program logic and user interaction flow.
  * data/: Directory containing user and game data files.

### Class Descriptions
#### User Class

The User class represents a user in the SteamCMD application.
#### Properties

  * username: Stores the username of the user.
  * password: Stores the user's password.
  * games: A list of game keys that the user owns.
  * installedGames: A list of game keys that are installed.

#### Methods

  1. Constructor: Initializes a user with a username and password.
  2. Get Username: Returns the username.
  3. Check Password: Verifies if the provided password matches the user's password.
  4. Add Game: Adds a game key to the user's library.
  5. Get Games: Returns the list of game keys owned by the user.
  6. Is Game Installed: Checks if a game is installed.
  7. Install Game: Marks a game as installed.
  8. Uninstall Game: Marks a game as uninstalled.

#### Game Class

The Game class represents a game in the SteamCMD application.
####Properties

  * key: The unique key of the game.
  * name: The name of the game.
  * downloadDuration: The time it takes to download the game (in seconds).

#### Methods

  1. Constructor: Initializes a game with a key, name, and download duration.
  2. Get Key: Returns the game key.
  3. Get Name: Returns the game name.
  4. Get Download Duration: Returns the download duration.

#### Utility Functions

Utility functions are provided to handle operations such as saving and loading user data and converting between strings and bytes.
Key Functions

  * String to Bytes: Converts a string to a byte vector.
  * Bytes to String: Converts a byte vector to a string.
  * Save Users: Saves the user data to a file.
  * Load Users: Loads user data from a file.

## Main Program Flow

The main program handles user interactions and invokes appropriate methods from the User and Game classes based on user input.
* Creating an Account

  1. Prompts the user to enter a username and password.
  2. Creates a new User object with the provided credentials.
  3. Saves the new user to the user data file.
  4. Displays a success message.

* Logging In

  1. Prompts the user to enter a username and password.
  2. Searches for a user with matching credentials.
  3. If found, sets the current user to the logged-in user and displays a success message.
  4. If not found, displays an error message.

* Activating a Game Key

   1. Ensures the user is logged in.
   2. Prompts the user to enter a game key.
   3. Searches for the game with the provided key.
   4. If found, confirms the activation with the user.
   5. Adds the game to the user's library and saves the user data.
   6. Displays appropriate messages based on the activation status.

* Viewing the Game Library

   1. Ensures the user is logged in.
   2. Displays the list of games in the user's library.
   3. Indicates whether each game is installed or not.

* Downloading a Game

   1. Ensures the user is logged in.
   2. Prompts the user to enter the game name.
   3. Searches for the game in the user's library.
   4. If found, displays a progress bar simulating the download.
   5. Marks the game as installed and saves the user data.
   6. Displays appropriate messages based on the download status.

* Uninstalling a Game

    1. Ensures the user is logged in.
    2. Prompts the user to enter the game name.
    3. Searches for the game in the user's library.
    4. If found and installed, displays a progress bar simulating the uninstallation.
    5. Marks the game as uninstalled and saves the user data.
    6. Displays appropriate messages based on the uninstallation status.

* Running a Game

    1. Ensures the user is logged in.
    2. Prompts the user to enter the game name.
    3. Searches for the game in the user's library.
    4. If found and installed, simulates running the game.
    5. Displays appropriate messages based on the game run status.

## Building and Running the Project

  * Build the Project: Use a C++ compiler to compile the source files.
  * Run the Executable: Execute the compiled program from the command line.
  * Interact with the Program: Follow the prompts to create accounts, log in, manage the game library, and perform other actions.




