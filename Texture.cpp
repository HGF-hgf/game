#include "Texture.h"
#include"Engine.h"
#include"Camera.h"
#include<string>
#include<map>
#include<SDL.h>
#include<SDL_image.h>
using namespace std;

Texture* Texture::s_Instance = nullptr;

bool Texture::LoadTexture(string id, string filename) {
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr) {
		SDL_Log("FAILED TO LOAD TEXTURE\n", filename.c_str(), SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::Getinstance()->GetRenderer(), surface);
	if (texture == nullptr) {
		SDL_Log("FAILED TO CREATE TEXTURE FROM SURFACE\n", SDL_GetError());
		return false;
	}

	m_TextureMap[id] = texture;

	return true;
}

void Texture::Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { 0, 0, width, height };
	Vector2D cam = Camera::GetInstance()->GetPosition() * 0.5;
	SDL_Rect dstRect = { x - cam.X,y - cam.Y,width,height };
	SDL_RenderCopyEx(Engine::Getinstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);

}

void Texture::DrawTile(string p_id, int p_tilesize, int p_x, int p_y, int p_row, int p_frame, SDL_RendererFlip p_flip)
{
	SDL_Rect srcRect = { p_tilesize * p_frame, p_tilesize* p_row, p_tilesize, p_tilesize };
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect dstRect = { p_x - cam.X, p_y - cam.Y , p_tilesize, p_tilesize };
	
	
	SDL_RenderCopyEx(Engine::Getinstance()->GetRenderer(), m_TextureMap[p_id], &srcRect, &dstRect, 0, nullptr, p_flip);
}

void Texture::DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { width * frame, height * (row - 1), width,height };
	
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect dstRect = { x - cam.X,y - cam.Y,width,height };
	SDL_RenderCopyEx(Engine::Getinstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}
void Texture::Drop(string id) {
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);
}

void Texture::Clean() {
	map<string, SDL_Texture*>::iterator it;
	for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
		SDL_DestroyTexture(it->second);

	m_TextureMap.clear();
	//SDL_Log("Texture map cleaned");
}