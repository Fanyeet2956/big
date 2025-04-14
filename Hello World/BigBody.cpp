// BigBody.cpp
#include "Player.h"
#include "raylib.h"
#include "raymath.h"
#include "Globals.h"
#include "GameUI.h"
#include "GameAI.h"
#include "CameraController.h"
#include "PelletFocus.h"
#include <vector>

void HandlePlayerInput(Bot& player, float dt) {
    Vector2 move = {
        (float)(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
        (float)(IsKeyDown(KEY_S) - IsKeyDown(KEY_W))
    };

    if (Vector2Length(move) > 0.1f)
        player.position = Vector2Add(player.position,
            Vector2Scale(Vector2Normalize(move), player.speed * dt));
}

void DrawStartOverlay() {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.6f));
    DrawText("Press ENTER to Start", SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2 - 20, 30, DARKGRAY);
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Big Body Game");
    SetTargetFPS(60);

    Bot player = { { 1000, 1000 }, 200.0f, BLUE, 0, true };
    PlayerStats stats = {};
    std::vector<Bot> bots;
    std::vector<Pellet> pellets;
    bool gameStarted = false;
    float zoom = 1.0f;

    SpawnBots(bots, 10);
    InitPellets(pellets, 100);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        UpdateBots(bots, pellets, dt);

        if (gameStarted) {
            HandlePlayerInput(player, dt);
            CheckPelletCollision(player, pellets, stats);
            RecycleOrSpawnPellets(pellets, dt);

            CheckPlayerEatsBots(player, bots, stats);
            CheckBotsEatPlayer(bots, player);
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            gameStarted = true;
        }
        // Update timeAlive only when the player is alive
        if (player.alive) {
            stats.timeAlive += dt;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Camera2D cam = CreateCamera(player.position, zoom);
        BeginMode2D(cam);

        DrawGrid(player.position, zoom);
        DrawPellets(pellets);
        DrawBots(bots);
        if (gameStarted) DrawPlayer(player);

        EndMode2D();

        DrawLeaderboard(bots, &player, true, &stats);
        if (!gameStarted) DrawStartOverlay();
        if (!player.alive && player.isRespawning) DrawRespawnStats(stats);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

