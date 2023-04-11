#pragma once


#include"INCLUDE.h"
#include"GameObject.h"
#include"Map.h"
//#include"GameState.h"

using namespace std;

#define SCREEN_WIDTH 1280 //1536
#define SCREEN_HEIGHT 720//816

class Engine{
public:
	static Engine* Getinstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}
	
	bool Init();
	void Clean();

	void Quit();
	void Update();
	void Render();
	void Events();

	//void PopState();// pause the game but not quit
	//void PushState(GameState* current);//when you don't want to destroy the current state but still want to add smt in and drove it on the screen
	//void ChangeState(GameState* target);//changing the state
	
	inline Map* GetMap() { return m_LevelMap; }
	inline bool isRunning() { return m_isRunning; };
	inline SDL_Renderer* GetRenderer() { return m_Renderer; };
private:
	Engine() {}
	bool m_isRunning;
	
	Map* m_LevelMap;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	static Engine* s_Instance;
	//vector<GameState*> m_State;
	vector<GameObject*>m_GameObjects;
	
};

