// GameTypes.h
#pragma once
#include "raylib.h"

// Game object definitions
struct Bot {
    Vector2 position;
    float speed;
    Color color;
    int score;
    bool alive;

    // Add for respawning
    bool isRespawning = false;
    float respawnTimer = 0.0f;
};

struct Pellet {
    Vector2 position;
    bool active = true;
};

struct PlayerStats {
    int foodEaten;
    int blobsEaten;
    float timeAlive;
    int highestScore;
    float leaderboardTime;
    int bestRank;
};

// Utility functions
float Distance(Vector2 a, Vector2 b);
float ScoreToRadius(int score);
