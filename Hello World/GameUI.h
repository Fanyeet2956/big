//gameUI.h
#pragma once

#include "GameTypes.h"
#include <vector>

float Distance(Vector2 a, Vector2 b);
float ScoreToRadius(int score);
void DrawGrid(Vector2 cameraOffset, float zoom);
bool DrawLeaderboard(const std::vector<Bot>& bots, const Bot* player, bool showLeaderboard, const PlayerStats* stats);
void DrawRespawnStats(const PlayerStats& stats);