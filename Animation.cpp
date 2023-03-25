#include "Animation.h"
#include"Texture.h"

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight) {
	Texture::Getinstance()->DrawFrame(m_textureID, x, y, spriteWidth, spriteHeight, m_spriteRow, m_spriteFrame, m_Flip);
}

void Animation::Update() {
	m_spriteFrame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;
}

void Animation::SetProps(string textureID, int spriteRow, int FrameCount, int animationSpeed, SDL_RendererFlip flip) {
	m_textureID = textureID;
	m_spriteRow = spriteRow;
	m_FrameCount = FrameCount;
	m_AnimationSpeed = animationSpeed;
	m_Flip = flip;
}


