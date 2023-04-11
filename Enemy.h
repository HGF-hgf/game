#pragma once
#include"Character.h"
#include"SpriteAnimation.h"
#include"Rigidbody.h"
#include"Collider.h"
#include"Vector2D.h"

using namespace std;

class Enemy : public Character {
public:
	Enemy(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h);

	virtual void Update(float dt);

private:
	void AnimationState();


	float m_Vision;
	
};