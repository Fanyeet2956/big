// GameAI.cpp
#include "PelletFocus.h"
#include "Globals.h"
#include "GameAI.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdlib>
#include <ctime>




void UpdateBots(std::vector<Bot>& bots, std::vector<Pellet>& pellets, float dt) {
    for (Bot& bot : bots) {
        if (!bot.alive) continue;

        // Find closest pellet
        float minDist = 1e9f;
        Pellet* closest = nullptr;
        for (Pellet& p : pellets) {
            if (!p.active) continue;
            float dist = Distance(bot.position, p.position);
            if (dist < minDist) {
                minDist = dist;
                closest = &p;
            }
        }

        // Move toward the closest pellet
        if (closest) {
            Vector2 dir = Vector2Subtract(closest->position, bot.position);
            dir = Vector2Normalize(dir);
            bot.position = Vector2Add(bot.position, Vector2Scale(dir, bot.speed * dt));

            // Eat if close
            if (minDist < 20.0f) {
                closest->active = false;
                bot.score += 10;
            }
        }
    }
}

void DrawBots(const std::vector<Bot>& bots) {
    for (const Bot& bot : bots) {
        if (!bot.alive) continue;
        float radius = ScoreToRadius(bot.score);
        DrawCircleV(bot.position, radius, bot.color);
    }
}



void SpawnBots(std::vector<Bot>& bots, int count) {
    bots.clear();
    for (int i = 0; i < count; ++i) {
        Bot bot;
        bot.position = {
            static_cast<float>(rand() % WORLD_WIDTH),
            static_cast<float>(rand() % WORLD_HEIGHT)
        };
        bot.speed = 100.0f + static_cast<float>(rand() % 50); // Random speed
        bot.color = Color{
            static_cast<unsigned char>(rand() % 256),
            static_cast<unsigned char>(rand() % 256),
            static_cast<unsigned char>(rand() % 256),
            255
        };
        bot.score = 0;
        bot.alive = true;

        bots.push_back(bot);
    }
}

void CheckBotsEatPlayer(std::vector<Bot>& bots, Bot& player) {
    if (!player.alive || player.isRespawning) return;

    float playerRadius = ScoreToRadius(player.score);

    for (Bot& bot : bots) {
        if (!bot.alive) continue;

        float botRadius = ScoreToRadius(bot.score);
        float distance = Vector2Distance(bot.position, player.position);

        if (botRadius > playerRadius * 1.25f && distance < botRadius) {
            bot.score += player.score / 2;

            // Start respawn process
            player.alive = false;
            player.isRespawning = true;
            player.respawnTimer = 3.0f; // 3 seconds delay
            player.score = 0;
            player.position = { WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f }; // safe spot
        }
    }
}


void RespawnBot(Bot& bot) {
    bot.position = {
        static_cast<float>(GetRandomValue(0, WORLD_WIDTH)),
        static_cast<float>(GetRandomValue(0, WORLD_HEIGHT))
    };
    bot.speed = 100.0f + static_cast<float>(rand() % 50);
    bot.color = Color{
        static_cast<unsigned char>(rand() % 256),
        static_cast<unsigned char>(rand() % 256),
        static_cast<unsigned char>(rand() % 256),
        255
    };
    bot.score = 0;
    bot.alive = true;
}
