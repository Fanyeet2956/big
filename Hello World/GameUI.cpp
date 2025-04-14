// GameUI.cpp
#include "Globals.h"
#include "GameUI.h"
#include "raymath.h"
#include <string>
#include <algorithm>
#include <cmath>



float Distance(Vector2 a, Vector2 b) {
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float ScoreToRadius(int score) {
    return 15.0f + sqrtf((float)score) * 2.0f;
}

void DrawGrid(Vector2 cameraOffset, float zoom) {
    const int gridSize = 40;
    Color gridColor = { 200, 200, 200, 40 };

    for (int x = 0; x < WORLD_WIDTH; x += gridSize) {
        DrawLineEx(
            { (x - cameraOffset.x) * zoom, -cameraOffset.y * zoom },
            { (x - cameraOffset.x) * zoom, (WORLD_HEIGHT - cameraOffset.y) * zoom },
            1.0f, gridColor
        );
    }

    for (int y = 0; y < WORLD_HEIGHT; y += gridSize) {
        DrawLineEx(
            { -cameraOffset.x * zoom, (y - cameraOffset.y) * zoom },
            { (WORLD_WIDTH - cameraOffset.x) * zoom, (y - cameraOffset.y) * zoom },
            1.0f, gridColor
        );
    }
}

bool DrawLeaderboard(const std::vector<Bot>& bots, const Bot* player, bool showLeaderboard, const PlayerStats* stats) {
    if (!showLeaderboard) return false;

    DrawRectangle(SCREEN_WIDTH - 170, 10, 160, 230, Fade(LIGHTGRAY, 0.6f));
    DrawText("Leaderboard", SCREEN_WIDTH - 160, 20, 20, DARKGRAY);
    DrawText("Press ` to close", SCREEN_WIDTH - 160, 40, 16, GRAY);

    std::vector<Bot> allBots;
    for (const auto& bot : bots) {
        if (bot.alive)
            allBots.push_back(bot);
    }
    if (player && player->alive)
        allBots.push_back(*player);

    std::sort(allBots.begin(), allBots.end(), [](const Bot& a, const Bot& b) {
        return a.score > b.score;
        });

    for (int i = 0; i < 5 && i < allBots.size(); ++i) {
        std::string label = (player && fabsf(Distance(allBots[i].position, player->position)) < 1.0f) ? "You" : "Bot";
        DrawText(TextFormat("%d. %s #%d (%d)", i + 1, label.c_str(), i + 1, allBots[i].score),
            SCREEN_WIDTH - 160, 70 + i * 20, 16, allBots[i].color);
    }



    return true;
}
void DrawRespawnStats(const PlayerStats& stats) {
    const int fontSize = 24;
    const int spacing = 40;
    const int startY = SCREEN_HEIGHT / 2 - (3 * spacing);

    std::string lines[6] = {
        "Food Eaten: " + std::to_string(stats.foodEaten),
        "Blobs Eaten: " + std::to_string(stats.blobsEaten),
        "Time Alive: " + std::to_string((int)stats.timeAlive) + "s",
        "Highest Score: " + std::to_string(stats.highestScore),
        "Time on Leaderboard: " + std::to_string((int)stats.leaderboardTime) + "s",
        "Best Rank: " + std::to_string(stats.bestRank)
    };

    for (int i = 0; i < 6; ++i) {
        int width = MeasureText(lines[i].c_str(), fontSize);
        DrawText(lines[i].c_str(), SCREEN_WIDTH / 2 - width / 2, startY + i * spacing, fontSize, DARKGRAY);
    }

    DrawText("Respawning...", SCREEN_WIDTH / 2 - 80, startY - 50, fontSize + 4, RED);
}