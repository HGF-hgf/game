#include "SpriteAnimation.h"
#include "Texture.h"

SpriteAnimation::SpriteAnimation(bool repeat): Animation(repeat){}

void SpriteAnimation::Draw(float x, float y, int spriteWidth, int spriteHeight,float xScale, float yScale, SDL_RendererFlip flip) {
	Texture::Getinstance()->DrawFrame(m_textureID, x, y, spriteWidth, spriteHeight, m_spriteRow, m_CurrentFrame, flip);
}

void SpriteAnimation::Update(float dt) {
	m_CurrentFrame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;
}

void SpriteAnimation::SetProps(string textureID, int spriteRow, int FrameCount, int animationSpeed) {
	m_textureID = textureID;
	m_spriteRow = spriteRow;
	m_FrameCount = FrameCount;
	m_AnimationSpeed = animationSpeed;
}


