// Player.h
#pragma once
#include <vector>
#include "GameTypes.h"
#include "PelletFocus.h" // if Pellet is declared here

void InitPlayer(Bot& player);
void UpdatePlayer(Bot& player, float dt);
void DrawPlayer(const Bot& player);
void CheckPelletCollision(Bot& player, std::vector<Pellet>& pellets, PlayerStats& stats);
void CheckPlayerEatsBots(Bot& player, std::vector<Bot>& bots, PlayerStats& stats);

