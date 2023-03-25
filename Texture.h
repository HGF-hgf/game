#pragma once
#include<string>
#include<SDL.h>
#include<map>

using namespace std;

class Texture {
public:
	static Texture* Getinstance() {return s_Instance = (s_Instance != nullptr) ? s_Instance : new Texture(); }

	bool LoadTexture(string id, string filename);
	void Drop(string id);
	void Clean();

	void DrawTile(string p_id, int p_tilesize, int p_x, int p_y, int p_row, int p_frame, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
	void DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	Texture() {}
	map<string, SDL_Texture*> m_TextureMap;
	static Texture* s_Instance;
};