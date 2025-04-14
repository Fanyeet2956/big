//PelletFocus.h
#pragma once
#include "GameTypes.h"
#include <vector>

void InitPellets(std::vector<Pellet>& pellets, int count);
void DrawPellets(const std::vector<Pellet>& pellets);
void RecycleOrSpawnPellets(std::vector<Pellet>& pellets, float dt);

