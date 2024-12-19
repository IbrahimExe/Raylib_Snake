// Raylib_FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include "raylib.h"

// Some Defines
#define SNAKE_LENGTH   200
#define SQUARE_SIZE    56

// Types and Structures Definition
typedef struct Snake {
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
} Snake;

typedef struct Food {
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
} Food;

typedef struct PowerUp {
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
} PowerUp;

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

static int framesCounter = 0;
static bool gameOver = false;
static bool pause = false;

static Food fruit = { 0 };
static Snake snake[SNAKE_LENGTH] = { 0 };
static Vector2 snakePosition[SNAKE_LENGTH] = { 0 };
static bool allowMove = false;
static Vector2 offset = { 0 };
static int counterTail = 0;

static PowerUp powerUp = { 0 };
static bool bfsActive = false;
static std::queue<Vector2> bfsPath;
static bool reverseAnimation = false;

// BFS Directions
const Vector2 directions[4] = {
    { SQUARE_SIZE, 0 },
    { -SQUARE_SIZE, 0 },
    { 0, SQUARE_SIZE },
    { 0, -SQUARE_SIZE }
};


static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UpdateDrawFrame(void);  // Update and Draw (one frame)
static void ActivateBFS(void);      // Activate BFS and calculate path


int main(void)
{
    InitWindow(screenWidth, screenHeight, "Snake");

    InitGame();

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())  
    {
        UpdateDrawFrame();
    }

    CloseWindow();        
    return 0;
}


// Initialize game variables
void InitGame(void)
{
    framesCounter = 0;
    gameOver = false;
    pause = false;

    counterTail = 1;
    allowMove = false;
    bfsActive = false;
    reverseAnimation = false;

    offset.x = screenWidth % SQUARE_SIZE;
    offset.y = screenHeight % SQUARE_SIZE;

    while (!bfsPath.empty()) bfsPath.pop();

    for (int i = 0; i < SNAKE_LENGTH; i++)
    {
        snake[i].position = Vector2{ offset.x / 2, offset.y / 2 };
        snake[i].size = Vector2{ SQUARE_SIZE, SQUARE_SIZE };
        snake[i].speed = Vector2{ SQUARE_SIZE, 0 };

        if (i == 0) snake[i].color = DARKBLUE;
        else snake[i].color = BLUE;
    }

    for (int i = 0; i < SNAKE_LENGTH; i++)
    {
        snakePosition[i] = Vector2{ 0.0f, 0.0f };
    }

    fruit.size = Vector2{ SQUARE_SIZE, SQUARE_SIZE };
    fruit.color = RED;
    fruit.active = false;

    powerUp.size = Vector2{ SQUARE_SIZE, SQUARE_SIZE };
    powerUp.color = GREEN;
    powerUp.active = false;
}

// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            // Player control
            if (!bfsActive)
            {
                if (IsKeyPressed(KEY_RIGHT) && (snake[0].speed.x == 0) && allowMove)
                {
                    snake[0].speed = Vector2{ SQUARE_SIZE, 0 };
                    allowMove = false;
                }
                if (IsKeyPressed(KEY_LEFT) && (snake[0].speed.x == 0) && allowMove)
                {
                    snake[0].speed = Vector2{ -SQUARE_SIZE, 0 };
                    allowMove = false;
                }
                if (IsKeyPressed(KEY_UP) && (snake[0].speed.y == 0) && allowMove)
                {
                    snake[0].speed = Vector2{ 0, -SQUARE_SIZE };
                    allowMove = false;
                }
                if (IsKeyPressed(KEY_DOWN) && (snake[0].speed.y == 0) && allowMove)
                {
                    snake[0].speed = Vector2{ 0, SQUARE_SIZE };
                    allowMove = false;
                }
            }

            // Snake movement
            for (int i = 0; i < counterTail; i++) snakePosition[i] = snake[i].position;

            if ((framesCounter % 5) == 0)
            {
                if (bfsActive && !bfsPath.empty())
                {
                    Vector2 nextPosition = bfsPath.front();
                    bfsPath.pop();

                    if (reverseAnimation)
                    {
                        for (int i = counterTail - 1; i > 0; i--)
                        {
                            snake[i].position = snake[i - 1].position;
                        }
                        snake[0].position = nextPosition;
                    }
                    else
                    {
                        // Normal BFS animation
                        snake[0].position = nextPosition;
                        for (int i = 1; i < counterTail; i++)
                        {
                            snake[i].position = snakePosition[i - 1];
                        }
                    }

                    if (bfsPath.empty())
                    {
                        bfsActive = false;
                        reverseAnimation = false;
                    }
                }
                else
                {
                    for (int i = 0; i < counterTail; i++)
                    {
                        if (i == 0)
                        {
                            snake[0].position.x += snake[0].speed.x;
                            snake[0].position.y += snake[0].speed.y;
                            allowMove = true;
                        }
                        else snake[i].position = snakePosition[i - 1];
                    }
                }
            }

            // Wall behaviour
            if (((snake[0].position.x) > (screenWidth - offset.x)) ||
                ((snake[0].position.y) > (screenHeight - offset.y)) ||
                (snake[0].position.x < 0) || (snake[0].position.y < 0))
            {
                gameOver = true;
            }

            // Collision with yourself
            if (!bfsActive)
            {
                for (int i = 1; i < counterTail; i++)
                {
                    if ((snake[0].position.x == snake[i].position.x) && (snake[0].position.y == snake[i].position.y)) gameOver = true;
                }
            }

            // Fruit position calculation
            if (!fruit.active)
            {
                fruit.active = true;
                fruit.position = Vector2{ GetRandomValue(0, (screenWidth / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.x / 2, GetRandomValue(0, (screenHeight / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2 };

                for (int i = 0; i < counterTail; i++)
                {
                    while ((fruit.position.x == snake[i].position.x) && (fruit.position.y == snake[i].position.y))
                    {
                        fruit.position = Vector2{ GetRandomValue(0, (screenWidth / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.x / 2, GetRandomValue(0, (screenHeight / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2 };
                        i = 0;
                    }
                }
            }

            // PowerUp position calculation
            if (!powerUp.active && GetRandomValue(0, 1000) < 10)
            {
                powerUp.active = true;
                powerUp.position = Vector2{ GetRandomValue(0, (screenWidth / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.x / 2, GetRandomValue(0, (screenHeight / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2 };
            }

            // Collision with Fruit
            if ((snake[0].position.x < (fruit.position.x + fruit.size.x) && (snake[0].position.x + snake[0].size.x) > fruit.position.x) &&
                (snake[0].position.y < (fruit.position.y + fruit.size.y) && (snake[0].position.y + snake[0].size.y) > fruit.position.y))
            {
                snake[counterTail].position = snakePosition[counterTail - 1];
                counterTail += 1;
                fruit.active = false;
            }

            // Collision with PowerUp
            if ((snake[0].position.x < (powerUp.position.x + powerUp.size.x) && (snake[0].position.x + snake[0].size.x) > powerUp.position.x) &&
                (snake[0].position.y < (powerUp.position.y + powerUp.size.y) && (snake[0].position.y + snake[0].size.y) > powerUp.position.y))
            {
                powerUp.active = false;
                reverseAnimation = true;
                ActivateBFS();
            }

            framesCounter++;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (!gameOver)
    {
        // Draw grid lines
        for (int i = 0; i < screenWidth / SQUARE_SIZE + 1; i++)
        {
            DrawLineV(Vector2{ SQUARE_SIZE * i + offset.x / 2, offset.y / 2 },
                Vector2{ SQUARE_SIZE * i + offset.x / 2, screenHeight - offset.y / 2 }, LIGHTGRAY);
        }

        for (int i = 0; i < screenHeight / SQUARE_SIZE + 1; i++)
        {
            DrawLineV(Vector2{ offset.x / 2, SQUARE_SIZE * i + offset.y / 2 },
                Vector2{ screenWidth - offset.x / 2, SQUARE_SIZE * i + offset.y / 2 }, LIGHTGRAY);
        }

        // Draw snake
        for (int i = 0; i < counterTail; i++) DrawRectangleV(snake[i].position, snake[i].size, snake[i].color);

        // Draw fruit to pick
        DrawRectangleV(fruit.position, fruit.size, fruit.color);

        // Draw power-up
        if (powerUp.active) DrawRectangleV(powerUp.position, powerUp.size, powerUp.color);

        if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
    }
    else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

    EndDrawing();
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

// Activate BFS and calculate path
void ActivateBFS(void)
{
    bfsActive = true;

    std::queue<Vector2> queue;
    std::vector<std::vector<bool>> visited(screenWidth / SQUARE_SIZE, std::vector<bool>(screenHeight / SQUARE_SIZE, false));
    std::vector<std::vector<Vector2>> parent(screenWidth / SQUARE_SIZE, std::vector<Vector2>(screenHeight / SQUARE_SIZE, { -1, -1 }));

    Vector2 start = snake[0].position;
    Vector2 goal = fruit.position;

    queue.push(start);
    visited[start.x / SQUARE_SIZE][start.y / SQUARE_SIZE] = true;

    bool found = false;

    while (!queue.empty() && !found)
    {
        Vector2 current = queue.front();
        queue.pop();

        for (Vector2 dir : directions)
        {
            Vector2 neighbor = { current.x + dir.x, current.y + dir.y };

            int nx = neighbor.x / SQUARE_SIZE;
            int ny = neighbor.y / SQUARE_SIZE;

            if (nx >= 0 && ny >= 0 && nx < (screenWidth / SQUARE_SIZE) && ny < (screenHeight / SQUARE_SIZE) && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                parent[nx][ny] = current;
                queue.push(neighbor);

                if (neighbor.x == goal.x && neighbor.y == goal.y)
                {
                    found = true;
                    break;
                }
            }
        }
    }

    if (found)
    {
        Vector2 step = goal;
        while (step.x != start.x || step.y != start.y)
        {
            bfsPath.push(step);
            step = parent[step.x / SQUARE_SIZE][step.y / SQUARE_SIZE];
        }
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
