#pragma once


#include"INCLUDE.h"
#include"GameObject.h"
#include"Map.h"
#include"Player.h"
#include"Bullet.h"
//#include"GameState.h"

using namespace std;

#define SCREEN_WIDTH 1280 //1536
#define SCREEN_HEIGHT 720//816

#define ROW 40
#define COLUMN 100

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

	void addCharacter(GameObject* object);
	void removeCharacter(GameObject* object);

	//void PopState();// pause the game but not quit
	//void PushState(GameState* current);//when you don't want to destroy the current state but still want to add smt in and drove it on the screen
	//void ChangeState(GameState* target);//changing the state
	Player* Getplayer() { return player; };
	inline Map* GetMap() { return m_LevelMap; }
	inline bool isRunning() { return m_isRunning; };
	inline SDL_Renderer* GetRenderer() { return m_Renderer; };
	std::unordered_map<int, GameObject*> m_GameObjects;
private:
	
	Engine() {}
	bool m_isRunning;
	float SetBotPos();
	Map* m_LevelMap;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	static Engine* s_Instance;
	//vector<GameState*> m_State;
	
	Player* player;
};

