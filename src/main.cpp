//
// Created by theoa on 26/08/2026.
//

#include <stdio.h>
#include <string.h>
#include <tgmath.h>
#include <stdlib.h>
#include <vector>
#include "raylib.h"

// Simulation width and height
constexpr int WIDTH  = 1100;
constexpr int HEIGHT = 800;

constexpr int waveSpeed = 100;

// Max radius for sound waves. If they exceed that they are not drawn
constexpr int soundWaveMaxRadius = 1064;

// Struct for the moving car
struct Car
{
    int posX = WIDTH/2;
    int posY = HEIGHT/3;
    int radius = 6;
    Color color = WHITE;
};

Car car;


// Struct for sound wave info
struct SoundWave
{
    int centerX = car.posX;
    int centerY = car.posY;
    int radius = car.radius - 1;
    Color color = RED;
};



void drawCar()
{
    DrawCircle(car.posX, car.posY, car.radius, car.color);
}


// Updates every wave in the waves vector by increasing its radius. Also draws it in the end
void updateWaves(std::vector<SoundWave>& waves, float dt)
{
    for (auto& soundWave : waves)
    {
        if (soundWave.radius < soundWaveMaxRadius)
        {
            soundWave.radius += waveSpeed * dt;
            DrawCircleLines(soundWave.centerX, soundWave.centerY, soundWave.radius, soundWave.color);
        }
    }
}


int main()
{

    std::vector<SoundWave> soundWaves;

    InitWindow(WIDTH, HEIGHT, "Doppler Effect Simulation");

    SetTargetFPS(60);

    int waveSpawnTimer = 0;

    while (!WindowShouldClose())
    {
        // Arrow keys to move the car
        if (IsKeyDown(KEY_RIGHT)) car.posX++;
        if (IsKeyDown(KEY_LEFT)) car.posX--;
        if (IsKeyDown(KEY_UP)) car.posY--;
        if (IsKeyDown(KEY_DOWN)) car.posY++;

        waveSpawnTimer++;

        if ((waveSpawnTimer % 15) == 0)
        {
            waveSpawnTimer = 0;
            SoundWave newWave;
            soundWaves.emplace_back(newWave);
        }

        BeginDrawing();

        float dt = GetFrameTime();
        updateWaves(soundWaves, dt);
        drawCar();
        ClearBackground(BLACK);

        EndDrawing();
    }

    return 0;
}