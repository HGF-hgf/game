#include"INCLUDE.h"
#include"Engine.h"
#include"GameObject.h"
#include"Texture.h"
#include"Input.h"
#include"Player.h"
#include"Timer.h"
#include"MapParser.h"
#include"Camera.h"
#include"Enemy.h"

using namespace std;

Engine* Engine::s_Instance = nullptr;
//Player* player = nullptr;
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
	m_Window = SDL_CreateWindow("GAME V1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
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

	Texture::Getinstance()->ParseTexture("textures.tml");

	/*Texture::Getinstance()->LoadTexture("player_idle", "texture/idle.png");
	Texture::Getinstance()->LoadTexture("player_run", "texture/run.png");*/
	/*Texture::Getinstance()->LoadTexture("player_jump", "texture/jump.png");
	Texture::Getinstance()->LoadTexture("player_fall", "texture/fall.png");
	
	*/
	//Texture::Getinstance()->LoadTexture("bg", "texture/bg2.jpg");
	/*Properties* props = new Properties("player_idle", 100, 100, 128, 128);
	GameObject* player = Factory::Getinstance()->CreateObject("player", props);*/
	player = new Player(new Properties("player", 100 , 300, 128, 128), 1, 6, 150, -48, -44, -30, -52);
	m_GameObjects.push_back(player);
	
	for (int i = 0; i < 1;++i) {
		Enemy* enemy = new Enemy(new Properties("enemy", 800 /* i * (rand() % (5 + 2 - 1) + 2)*/, 240, 192, 192), 1, 4, 150, -68, -34, -50, -93);
		m_GameObjects.push_back(enemy);
	}
	
	Camera::GetInstance()->SetTarget(player->GetOrigin());
	return m_isRunning = true;
}


void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 164, 218, 254, 255);
	SDL_RenderClear(m_Renderer);

	Texture::Getinstance()->Draw("bg", 0, 0, 1920, 1080, 1, 0.9, 0.3);

	m_LevelMap->Render();

	for (unsigned int i = 0;i != m_GameObjects.size();i++) {
		m_GameObjects[i]->Draw();
	}

	
	SDL_RenderPresent(m_Renderer);
}

void Engine::Update() {
	float dt = Timer::Getinstance()->GetDeltaTime();
	for (unsigned int i = 0;i != m_GameObjects.size();i++) {
		m_GameObjects[i]->Update(dt);
	}
	m_LevelMap->Update();
	Camera::GetInstance()->Update(dt);

}



void Engine::Events() {
	Input::GetInstance()->HandIn();
}

void Engine::Clean() {

	for (unsigned int i = 0;i != m_GameObjects.size();i++) {
		m_GameObjects[i]->Clean();
	}
	Texture::Getinstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();

}

void Engine::Quit() {
	m_isRunning = false;
}
