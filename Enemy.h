#pragma once
#include"Character.h"
#include"SpriteAnimation.h"
#include"Rigidbody.h"
#include"Collider.h"
#include"Vector2D.h"
#include"Player.h"

using namespace std;

#define VEL 1.5f

class Enemy : public Character {
public:
	Enemy(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h);

	virtual void Update(float dt);
	virtual void moveToPlayer();
	
private:
	void AnimationState();
	float m_Vision;
	//Player& m_player;
};