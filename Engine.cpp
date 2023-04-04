#include<iostream>
#include<SDL.h>
#include"Engine.h"
#include"Texture.h"
#include"Transformation.h" 
#include"Player.h"
#include"Input.h"
#include"Timer.h"
#include"MapParser.h"
#include"Camera.h"

using namespace std;

Engine* Engine::s_Instance = nullptr;
Player* player = nullptr;
bool Engine::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG) != 0) {
		SDL_Log("FAILED TO INITIALIZE SDL\n", SDL_GetError());
		return false;
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_PNG) != 0) {
		SDL_Log("FAILED TO INITIALIZE SDL\n", SDL_GetError());
		return false;
	}
	
	SDL_WindowFlags  window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	m_Window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
	if (m_Window == nullptr) {
		SDL_Log("FAILED TO CREATE WINDOW\n", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		SDL_Log("FAILED TO CREATE RENDERER\n", SDL_GetError());
		return false;
	}

	if (!MapParser::GetInstance()->Load()) {
		cout<<"Failed to load map\n";
		return false;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("Level1");

	Texture::Getinstance()->LoadTexture("player", "texture/s.png");
	Texture::Getinstance()->LoadTexture("player_run", "texture/r.png");
	Texture::Getinstance()->LoadTexture("player_jump", "texture/jump.png");

	player = new Player(new Properties("player", 100, 200, 128, 128));
	

	Camera::GetInstance()->SetTarget(player->GetOrigin());
	return m_isRunning = true;
}


void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 164, 218, 254, 255);
	SDL_RenderClear(m_Renderer);

	//	Texture::Getinstance()->Draw("12", 0, 0, 720, 767);
	m_LevelMap->Render();
	player->Draw();
	SDL_RenderPresent(m_Renderer);
}

void Engine::Update() {
	float dt = Timer::Getinstance()->GetDeltaTime();
	player->Update(dt);
	m_LevelMap->Update();
	Camera::GetInstance()->Update(dt);
}



void Engine::Events() {
	Input::GetInstance()->HandIn();
}

void Engine::Clean() {
	Texture::Getinstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();

}

void Engine::Quit() {
	m_isRunning = false;
}