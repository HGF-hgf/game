#include"Enemy.h"
#include"Texture.h"
#include"INCLUDE.h"
#include"Input.h"
#include"Engine.h"
//#include"Factory.h"
#include"CollisionHandler.h"
#include"Camera.h"

Enemy::Enemy(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h) :Character(props, Row, FrameCount, AnimationSpeed, x, y, w, h) {

	/*m_IsRunning = false;
	m_IsJumping = false;
	m_IsFalling = false;
	m_IsGrounded = false;
	m_IsAttacking = false;
	m_IsDead = false;*/



}


void Enemy::Update(float dt) {

	Character::Update(dt);
	AnimationState();
	m_Animation->Update(dt);
	
}

void Enemy::AnimationState() {
	//idle
	m_Animation->SetProps("Enemy_idle", 1, 4, 170);

	
}
