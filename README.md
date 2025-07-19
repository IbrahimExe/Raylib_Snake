# A Snake clone created using Raylib & the BFS Algorithm!
### Hello! Here is a basic re-creation of the Snake game built in C++ using the Raylib library!

The game is the same one you know and love!

However, this one has an implementation of a special power-up to help you be the longest snake of all!

This was a Project done for my VGP230 2D Games Programming class.

### The game makes use of the Depth First Search Algorithm to incorporate a pathfinding method to create a power-up that guides the player to the next fruit automatically!

![Snake_Intro](https://github.com/user-attachments/assets/12fb0ce5-6b1a-48ef-89ea-d45f66537719)


 ## **Features**

  - **Player Movement:** The game includes very basic movements, such as not being able to go back on yourself!

  - **Grid-Based System and Speed:**
  - - The game world is divided into a grid, where each cell corresponds to a fixed square size, the snakes' movement is also mapped to this, moving square by square at a specified frame rate to control general speed.
  - - The snake and all other objects (fruit, power-ups) move and interact based on this grid structure and take up an entire grid square.

  - **BFS Pathfinding:**
  - - When a power-up is collected, the snake activates BFS pathfinding to autonomously reach the next fruit.
  - - BFS ensures the shortest path is calculated using a queue and visited nodes.
  - - The pathfinding is implemented to navigate the grid, avoiding walls and the snake's own body.
   
 ## Technical Details
- **Grid System:**

   The game divides the screen into a grid of cells, with each cell having a fixed size defined by SQUARE_SIZE.
   Objects like the snake, fruit, and power-ups are positioned at the centre of these grid cells for consistent movement and collision detection.
   Movement updates the snake’s position by moving it to adjacent cells, ensuring precise alignment with the grid.

- **BFS Pathfinding Algorithm:**

    - Algorithm Overview:
        The BFS algorithm is triggered when the snake collects a power-up.
        The snake's head is treated as the starting point, and the fruit's position is the goal.
        BFS uses a queue to explore neighbouring cells in all directions until the fruit is reached.
        A parent map is used to trace the shortest path back to the starting point.

    - Implementation:
        Grid cells are marked as visited during traversal to avoid reprocessing.
        Once the path is found, it is stored in a queue (bfsPath), which the snake follows step by step.
        Collision checks ensure that walls and the snake's body are avoided during pathfinding.

## Educational Takeaways:
- This project has further improved my overall familiarity with the Raylib library, and its power in not only the rendering of the game but its included functions as well that all help improve programming for games like these!

- Moreover, the introduction to and attempt at the implementation of a pathfinding algorithm was challenging, but fun to do, allowing me to see why they are so important not only in games but in other applications as well!

## Educational Takeaways:
- Although implemented, it's not perfect, therefore in terms of improvements, I hope to make it smoother to the point where the player is able to understand that they've moved to the fruit better.

- Animation improvements through the change of color or speed when the power-up is picked up would help as well.

- A major issue I wasnt able to fix was that when the snake collects the power-up, and has to go through it's own body to get to the next fruit, it dissapears and ends the game, I belive this it to do with the checking of where the snakes body is vs where it will be.

- Other improvements I wanted to make was to make the code Modular and spereate the BFS into its own header and .cpp files in order to make it more organised and better.

- Maybe even implement another algorithm, such as A* to improve the power-up. 

- Perhaps even re-create this simple game and expand it in a game engine such as Unity! 
