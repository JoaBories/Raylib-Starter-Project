#include "raylib.h"
#include <iostream>
#include <vector>

#include "Ball.h"
#include "Player.h"
#include "SceneManager.h"

using namespace std;

int leftScore = 0;
int rightScore = 0;

float unitY = CONSTS::SCREEN::SIZE_X / 40;
float unitX = CONSTS::SCREEN::SIZE_Y / 70;

Vector2 playableAreaSize = { 70*unitX, 40 * unitY };
Vector2 playableAreaPos = { 0, 0 };

Color leftColor = RED;
Color rightColor = BLUE;

SceneManager sceneManager = SceneManager();

Texture backgroundText;
Texture netText;

Font ft1;
Font ft2;

Music music;

Player leftPaddle = Player({ unitX * 2, unitY * 14 }, { unitX * 2, unitY * 10 }, 10, playableAreaPos, playableAreaSize, KEY_W, KEY_S, leftColor);
Player rightPaddle = Player({ unitX * 66, unitY * 14 }, { unitX * 2, unitY * 10 }, 10, playableAreaPos, playableAreaSize, KEY_UP, KEY_DOWN, rightColor);
Ball ball = Ball(playableAreaSize, playableAreaPos, &leftPaddle, &rightPaddle);

void Init();
void Update();
void Draw();
void UpdateDraw();
void DeInit();

void ResetTerrain(float dir);
Texture LoadTextureFromSource(const char *source);

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
    InitWindow(CONSTS::SCREEN::SIZE_X, CONSTS::SCREEN::SIZE_Y, "COOL PONG");
    InitAudioDevice();
    SetTargetFPS(60);

    music = LoadMusicStream("resources/sound/celeste_music.mp3");

    PlayMusicStream(music);

    ft1 = LoadFont("resources/fonts/pixantiqua.png");
    ft2 = LoadFont("resources/fonts/jupiter_crash.png");

    backgroundText = LoadTextureFromSource("resources/img/summit_begin.png");
    netText = LoadTextureFromSource("resources/img/net.png");

}

void Update()
{
    UpdateMusicStream(music);

    switch (sceneManager.GetCurrentScene())
    {
    case Scenes::Menu:
        if(IsKeyPressed(KEY_ENTER))
        {
            sceneManager.SetCurrentScene(Scenes::TwoPlayer);
            UnloadTexture(backgroundText);
            backgroundText = LoadTextureFromSource("resources/img/core.png");
            leftScore = 0;
            rightScore = 0;

            leftPaddle = Player({ unitX * 2, unitY * 14 }, { unitX * 2, unitY * 10 }, 10, playableAreaPos, playableAreaSize, KEY_W, KEY_S, leftColor);
            rightPaddle = Player({ unitX * 66, unitY * 14 }, { unitX * 2, unitY * 10 }, 10, playableAreaPos, playableAreaSize, KEY_UP, KEY_DOWN, rightColor);
            ball = Ball(playableAreaSize, playableAreaPos, &leftPaddle, &rightPaddle);
        }
        break;

    case Scenes::TwoPlayer:
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

        if (leftScore == CONSTS::GAME::POINT_TO_WIN || rightScore == CONSTS::GAME::POINT_TO_WIN)
        {
            sceneManager.SetCurrentScene(Scenes::Score);
            UnloadTexture(backgroundText);
            backgroundText = LoadTextureFromSource("resources/img/summit_end.png");
        }
        break;

    case Scenes::Score : 
        if (IsKeyPressed(KEY_ENTER))
        {
            sceneManager.SetCurrentScene(Scenes::Menu);
            UnloadTexture(backgroundText);
            backgroundText = LoadTextureFromSource("resources/img/summit_begin.png");
        }
        break;
    }
}

void Draw()
{
    DrawTextureEx(backgroundText, { 0, 0 }, 0, 1, WHITE);

    switch (sceneManager.GetCurrentScene())
    {
    case Scenes::Menu:
        DrawTextEx(ft1, "Cool Pong", { 19 * unitX, 15 * unitY }, 7 * unitX, unitX, DARKGRAY);
        DrawTextEx(ft1, "Press [Enter]", { 25 * unitX, 25 * unitY }, 2 * unitX, unitX, DARKGRAY);
        break;

    case Scenes::TwoPlayer:
        DrawTextureEx(netText, { 34 * unitX, 0 }, 0, 1, GRAY);

        ball.Draw();
        leftPaddle.Draw();
        rightPaddle.Draw();

        DrawTextEx(ft2, TextFormat("%i", leftScore), { 30 * unitX, 2 * unitY }, 10 * unitX, 0, leftColor);
        DrawTextEx(ft2, TextFormat("%i", rightScore), { 37 * unitX, 2 * unitY }, 10 * unitX, 0, rightColor);
        break;

    case Scenes::Score:

        if (leftScore == CONSTS::GAME::POINT_TO_WIN)
        {
            DrawTextEx(ft1, "Left  Win", { 19 * unitX, 15 * unitY }, 7 * unitX, unitX, leftColor);
            DrawTextEx(ft1, "Press [Enter]", { 25 * unitX, 25 * unitY }, 2 * unitX, unitX, leftColor);
        }
        else
        {
            DrawTextEx(ft1, "Right Win", { 19 * unitX, 15 * unitY }, 7 * unitX, unitX, rightColor);
            DrawTextEx(ft1, "Press [Enter]", { 25 * unitX, 25 * unitY }, 2 * unitX, unitX, rightColor);
        }

        break;

    }
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
    UnloadFont(ft1);
    UnloadFont(ft2);

    UnloadTexture(backgroundText);
    UnloadTexture(netText);
    UnloadMusicStream(music);

    CloseWindow();

    CloseAudioDevice();
}

void ResetTerrain(float dir)
{
    ball.Reset(dir);
}

Texture LoadTextureFromSource(const char *source)
{
    Image img = LoadImage(source);
    Texture text = LoadTextureFromImage(img);

    UnloadImage(img);

    return text;
}
