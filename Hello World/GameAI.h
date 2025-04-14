// GameAI.h
#pragma once
#include "GameTypes.h"
#include <vector>

void SpawnBots(std::vector<Bot>& bots, int count);
void UpdateBots(std::vector<Bot>& bots, std::vector<Pellet>& pellets, float dt);
void DrawBots(const std::vector<Bot>& bots);
void RespawnBot(Bot& bot);
void CheckBotsEatPlayer(std::vector<Bot>& bots, Bot& player);

