#include "raylib.h"
#include <iostream>
#include <vector>

#include "Ball.h"
#include "Player.h"

using namespace std;

int leftScore = 0;
int rightScore = 0;

int width = 1280;
int height = 720;

float unitY = height / 40;
float unitX = width / 70;

int topRectangleHeight = 2*unitY;

Vector2 playableAreaSize = { 70*unitX, 36 * unitY };
Vector2 playableAreaPos = { 0, 2*unitY };

Color leftColor = RED;
Color rightColor = BLUE;

Font ft;

Player leftPaddle = Player({ unitX * 2, unitY * 14 }, { unitX * 2, unitY * 10 }, 10, playableAreaPos, playableAreaSize, KEY_W, KEY_S, leftColor);
Player rightPaddle = Player({ unitX * 66, unitY * 14 }, { unitX * 2, unitY * 10 }, 10, playableAreaPos, playableAreaSize, KEY_UP, KEY_DOWN, rightColor);

Ball ball = Ball( unitY, 10, playableAreaSize, playableAreaPos, &leftPaddle, &rightPaddle);

void Init();
void Update();
void Draw();
void UpdateDraw();
void DeInit();

void ResetTerrain(float dir);

int main() {   
    
    Init();

    while (!WindowShouldClose()) {  
   
        UpdateDraw();
        
    }

    DeInit();

    return 0;
}

void Init()
{
    InitWindow(width, height, "");
    SetTargetFPS(60);

    ft = LoadFont("resources/fonts/jupiter_crash.png");
}

void Update()
{
    ball.Update();
    leftPaddle.Update();
    rightPaddle.Update();

    if (ball.isOnBorder(true))
    {
        rightScore++;
        ResetTerrain(1.0f);
    }
    else if (ball.isOnBorder(false))
    {
        leftScore++;
        ResetTerrain(-1.0f);
    }

    if (leftScore == 9 || rightScore == 9)
    {
        DeInit();
    }
}

void Draw()
{
    DrawRectangle(unitX * 34, 0, unitX * 2, height, GRAY);

    ball.Draw();
    leftPaddle.Draw();
    rightPaddle.Draw();

    DrawRectangle(0, 0, width, topRectangleHeight, DARKGRAY);
    DrawRectangle(0, height - topRectangleHeight, width, topRectangleHeight, DARKGRAY);
    DrawTextEx(ft, TextFormat("%i", leftScore), { 30 * unitX, 2 * unitY }, 10 * unitX, 0, leftColor);
    DrawTextEx(ft, TextFormat("%i", rightScore), { 37 * unitX, 2 * unitY }, 10 * unitX, 0, rightColor);
}

void UpdateDraw()
{
    Update();

    BeginDrawing();
    ClearBackground(BLACK);

    Draw();

    EndDrawing();
}

void DeInit()
{
    UnloadFont(ft);
    CloseWindow();
}

void ResetTerrain(float dir)
{
    ball.Reset(dir);
}
