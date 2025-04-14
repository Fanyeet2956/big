//PelletFocus.cpp
#include "PelletFocus.h"
#include "Globals.h"
#include "raylib.h"
#include "raymath.h"

float pelletSpawnTimer = 0.0f;
const float PELLET_SPAWN_INTERVAL = 1.0f;
const int MAX_PELLETS = 200;

void InitPellets(std::vector<Pellet>& pellets, int count) {
    pellets.clear();
    for (int i = 0; i < count; ++i) {
        Pellet p;
        p.position = {
            (float)GetRandomValue(WORLD_BOUNDS.x, WORLD_BOUNDS.x + WORLD_BOUNDS.width),
            (float)GetRandomValue(WORLD_BOUNDS.y, WORLD_BOUNDS.y + WORLD_BOUNDS.height)
        };
        p.active = true;
        pellets.push_back(p);
    }
}


void DrawPellets(const std::vector<Pellet>& pellets) {
    for (const Pellet& p : pellets) {
        if (p.active)
            DrawCircleV(p.position, 5.0f, ORANGE);
    }
}



void RecycleOrSpawnPellets(std::vector<Pellet>& pellets, float dt) {
    static float timeAccumulator = 0.0f;
    timeAccumulator += dt;

    if (timeAccumulator >= 1.0f) {
        timeAccumulator = 0.0f;

        // Try to recycle
        for (Pellet& p : pellets) {
            if (!p.active && GetRandomValue(0, 1) == 0) {
                p.position = {
                    (float)GetRandomValue((int)WORLD_BOUNDS.x, (int)(WORLD_BOUNDS.x + WORLD_BOUNDS.width)),
                    (float)GetRandomValue((int)WORLD_BOUNDS.y, (int)(WORLD_BOUNDS.y + WORLD_BOUNDS.height))
                };
                p.active = true;
                return;
            }
        }

        // If no inactive pellets, create a new one
        Pellet newPellet = {
            {
                (float)GetRandomValue((int)WORLD_BOUNDS.x, (int)(WORLD_BOUNDS.x + WORLD_BOUNDS.width)),
                (float)GetRandomValue((int)WORLD_BOUNDS.y, (int)(WORLD_BOUNDS.y + WORLD_BOUNDS.height))
            },
            true
        };
        pellets.push_back(newPellet);
    }
}
