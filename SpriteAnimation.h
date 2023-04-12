#pragma once
#include"Animation.h"
#include<SDL.h>
#include<string>

class SpriteAnimation : public Animation
{
public:
	SpriteAnimation(bool repeat = true);

	virtual void Update(float dt);
	void Draw(float x, float y, int spriteWidth, int spriteHeight,float Xscale, float yScale, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SetProps(string textureID, int spriteRow, int FrameCount, int animationSpeed);

private:
	int m_AnimationSpeed;//toc do hien thi cua cac animation
	int m_spriteRow;//so hang
	int m_FrameCount;//dem so frame can ve
	string m_textureID;//ten cua doi tuong can ve
};

