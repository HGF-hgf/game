#include "CollisionHandler.h"
#include"Engine.h"
#include <iostream>

using namespace std;

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
	m_CollisionLayer = (Tile*)Engine::Getinstance()->GetMap()->GetLayers().front();
	m_CollisionTilemap = m_CollisionLayer->GetTilemap();
}

bool CollisionHandler::checkCollision(SDL_Rect a, SDL_Rect b) {
	bool x_overLaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overLaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
	return (x_overLaps && y_overLaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a) {
	int tileSize = 32;
	int RowCount = 1000;
	int ColCount = 1920;

	int left_tile = a.x / tileSize;
	int right_tile = (a.x + a.w) / tileSize;

	int top_tile = a.y / tileSize;
	int bottom_tile = (a.y + a.h) / tileSize;

	if (left_tile < 0) left_tile = 0;
	if (right_tile > ColCount) right_tile = ColCount;

	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > RowCount) bottom_tile = RowCount;

	for (int i = left_tile; i <= right_tile; ++i) {
		for (int j = top_tile; j <= bottom_tile; ++j) {
			if (m_CollisionTilemap[j][i] > 0) {
				//std::cout << m_CollisionTilemap[j][i] << '\n';
				return true;
			}
		}
	}
	return false;
}

int CollisionHandler::checkTileID(SDL_Rect a) {
	int tileSize = 32;
	int RowCount = 1000;
	int ColCount = 1920;

	int left_tile = a.x / tileSize;
	int right_tile = (a.x + a.w) / tileSize;

	int top_tile = a.y / tileSize;
	int bottom_tile = (a.y + a.h) / tileSize;

	if (left_tile < 0) left_tile = 0;
	if (right_tile > ColCount) right_tile = ColCount;

	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > RowCount) bottom_tile = RowCount;

	for (int i = left_tile; i <= right_tile; ++i) {
		for (int j = top_tile; j <= bottom_tile; ++j) {
			if (m_CollisionTilemap[j][i] > 0) {
				return m_CollisionTilemap[j][i];
			}
		}
	}
	
}
