#pragma once

#include"Layer.h"
#include<vector>

using namespace std;

class Map {
public:
	void Render() {
		for (unsigned int i = 0; i < m_MapLayer.size();i++)
			m_MapLayer[i]->Render();
	}
	void Update() {
		for (unsigned int i = 0; i < m_MapLayer.size();i++)
			m_MapLayer[i]->Update();
	}
	vector<Layer*> GetMapLayer() { return m_MapLayer; }
private:
	friend class MapParser;
	vector<Layer*> m_MapLayer;
};