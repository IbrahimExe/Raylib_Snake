# Raylib 2D - Game Programming Final Project!
### Hello! Here is a basic re-creation of the Snake game built in C++ using the Raylib library!

The game is the same one you know and love!

However, this one has an implementation of a special power-up to help you be the longest snake of all! 

### The game makes use of the Depth First Search Algorithm to !

 ## **Features**

  - **Player Movement:** Left & Right movements with a very basic and simple gravity implementation to create a jump!

![Animation](https://github.com/user-attachments/assets/593cae00-ca5a-465a-958e-5e057d5bb520)

  - **Object-Oriented Programming (OOP):** The game is designed with classes for Player, Platform, Enemy & Item. Each class is in its own file for modularity, making the code manageable and extendable.

  - **Game States:** The game also includes different states (Start, Playing & GameOver) to handle transitions between menus and gameplay.

  - **Collision Detection:** Raylib's simple 2D collision detection is used to detect interactions between the player and other game objects (Such as the platforms or coin) *as well as* for menu collisions between the mouse and buttons!

![Collisions Respawn](https://github.com/user-attachments/assets/ea082087-5930-42c6-aed4-2c3cbfdfba19)

## **Using Raylib**

- I use raylib to initialize the game window and UI handle input.

![StartMenu](https://github.com/user-attachments/assets/cba4dfd1-2be4-4c6e-a9a7-c6911951e754)

- Render and Draw all game objects, including the player, platforms, enemies and items as simple polygonal shapes.

![GamePlay](https://github.com/user-attachments/assets/18d7831a-d919-4aaf-9581-7dcd6e63295b)

- Detect collisions and update positions based on player input and gravity.

- Manage & set frame updates, game state transitions, and User Interface elements.

## **Learing Take-Aways & Future Improvements**

- This project has given me a great understanding of Raylib and how to use other libraries in general, but an even bigger understanding as to how game engines operate and how modularisation is extremley important in even simple games.

- I hope to perhaps revisit this game in order to add more levels with more platform configurations.

- Introduce additional obstacles and perhpas even power-ups.

- Maybe even re-create this simple game and expand it in a game engine such as Unity! 



