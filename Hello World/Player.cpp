// Player.cpp
#include "GameAI.h"
#include "Player.h"
#include "raylib.h"
#include "raymath.h"
#include "Globals.h"

Vector2 ClampToBounds(Vector2 pos) {
    pos.x = Clamp(pos.x, WORLD_BOUNDS.x, WORLD_BOUNDS.x + WORLD_BOUNDS.width);
    pos.y = Clamp(pos.y, WORLD_BOUNDS.y, WORLD_BOUNDS.y + WORLD_BOUNDS.height);
    return pos;
}

void InitPlayer(Bot& player) {
    player.position = { 1000.0f, 1000.0f };
    player.speed = 200.0f;
    player.color = BLUE;
    player.score = 0;
    player.alive = true;
}

void UpdatePlayer(Bot& player, float dt) {
    if (player.isRespawning) {
        player.respawnTimer -= dt;
        if (player.respawnTimer <= 0.0f) {
            player.isRespawning = false;
            player.alive = true;
        }
        return;
    }

    Vector2 move = {
        (float)(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
        (float)(IsKeyDown(KEY_S) - IsKeyDown(KEY_W))
    };

    if (Vector2Length(move) > 0.1f)
        move = Vector2Normalize(move);

    player.position = Vector2Add(player.position, Vector2Scale(move, player.speed * dt));
    player.position = ClampToBounds(player.position);
}


void DrawPlayer(const Bot& player) {
    if (!player.alive || player.isRespawning)
        return;

    float radius = ScoreToRadius(player.score);
    DrawCircleV(player.position, radius, player.color);
}



void CheckPelletCollision(Bot& player, std::vector<Pellet>& pellets, PlayerStats& stats) {
    float radius = ScoreToRadius(player.score);
    for (Pellet& p : pellets) {
        if (!p.active) continue;
        float dist = Vector2Distance(player.position, p.position);
        if (dist < radius) {
            p.active = false;
            player.score += 10;
            stats.foodEaten++;
        }
    }
}

void CheckPlayerEatsBots(Bot& player, std::vector<Bot>& bots, PlayerStats& stats) {
    if (!player.alive) return;
    float playerRadius = ScoreToRadius(player.score);
    for (Bot& bot : bots) {
        if (!bot.alive) continue;
        float botRadius = ScoreToRadius(bot.score);
        float distance = Vector2Distance(player.position, bot.position);
        if (playerRadius > botRadius * 1.25f && distance < playerRadius) {
            player.score += bot.score / 2;
            RespawnBot(bot);
            stats.blobsEaten++;
        }
    }
}





