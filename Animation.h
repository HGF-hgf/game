#pragma once
#include<SDL.h>
#include<string>
using namespace std;


class Animation {
public:
	Animation(){}
	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight);
	void SetProps(string textureID, int spriteRow, int FrameCount, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	int m_spriteRow, m_spriteFrame;
	int m_AnimationSpeed, m_FrameCount;
	string m_textureID;
	SDL_RendererFlip m_Flip;
};