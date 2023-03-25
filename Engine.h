#pragma once


#include<SDL.h>
#include<SDL_image.h>
#include"Map.h"

#define SCREEN_WIDTH = 960
#define SCREEN_HEIGHT = 720
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
	
	inline bool isRunning() { return m_isRunning; };
	inline SDL_Renderer* GetRenderer() { return m_Renderer; };
private:
	Engine() {}
	bool m_isRunning;
	
	Map* m_LevelMap;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	static Engine* s_Instance;
};

