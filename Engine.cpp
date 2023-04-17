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
#include"Bullet.h"

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

	player = new Player(new Properties("player", 100, 300, 128, 128), 1, 6, 150, -48, -44, -30, -52);
	addCharacter(player);
	
	for (int i = 0; i < 6;++i) {
		Enemy* enemy = new Enemy(new Properties("enemy", /*rand() % (1280 - 640 + 1) +*/ 300 + i*350, 640-93-35 /*+ rand() % (573 - 320 + 1) + 320*/, 192, 192), 1, 4, 150, -68, -34, -50, -93);
		addCharacter(enemy);
	}

	Camera::GetInstance()->SetTarget(player->GetOrigin());
	return m_isRunning = true;
}


void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 164, 218, 254, 255);
	SDL_RenderClear(m_Renderer);

	Texture::Getinstance()->Draw("bg", 0, 0, 1920, 1080, 1, 0.9, 0.3);

	m_LevelMap->Render();

	for (auto& it : m_GameObjects) {
		int id = it.first;
		GameObject* object = it.second;
		object->Draw();
	}

	SDL_RenderPresent(m_Renderer);
}

void Engine::Update() {

	for (auto& it1 : m_GameObjects) {
		Character* ch1 = (Character*) it1.second;

		for (auto& it2 : m_GameObjects) {
			Character* ch2 = (Character*) it2.second;
			
			if (ch1 != ch2 && CollisionHandler::GetInstance()->checkCollision(ch1->GetBox(), ch2->GetBox()))
			{
				ch1->OnCollide(ch2);
			}
		}
	}

	float dt = Timer::Getinstance()->GetDeltaTime();
	for (auto& it: m_GameObjects) {
		int id = it.first;
		GameObject* object = it.second;
		object->Update(dt);
	}

	m_LevelMap->Update();
	Camera::GetInstance()->Update(dt);

	std::vector<int> m_removedIds;

	for (auto& it : m_GameObjects) {
		int id = it.first;
		GameObject* object = it.second;
		Character* character = (Character*)object;
		
		if (character->IsDead())
			m_removedIds.push_back(character->GetId());
	}

	for (auto& id : m_removedIds)
		removeCharacter(m_GameObjects[id]);
}



void Engine::Events() {
	Input::GetInstance()->HandIn();
}

void Engine::addCharacter(GameObject* object)
{
	m_GameObjects[object->GetId()] = object;
}

void Engine::removeCharacter(GameObject* object)
{
	m_GameObjects.erase(object->GetId());
	delete object;
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

//float Engine::SetBotPos() {
//
//}
