#include"Enemy.h"
#include"Texture.h"
#include"INCLUDE.h"
#include"Input.h"
#include"Engine.h"

//#include"Factory.h"
#include"CollisionHandler.h"
#include"Camera.h"

Enemy::Enemy(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h) :Character(props, Row, FrameCount, AnimationSpeed, x, y, w, h) {
	
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_AttackTime = ATTACK_TIME;

}


void Enemy::Update(float dt) {
	
	/*if (m_IsAttacking && m_AttackTime > 0) {
		m_AttackTime -= dt;
	}
	else {
		m_IsAttacking = false;
		m_AttackTime = ATTACK_TIME;
	}*/

	//cout << m_Vision << endl;
	moveToPlayer();
	Character::Update(dt);
	
	AnimationState();
	m_Animation->Update(dt);
	
}

void Enemy::AnimationState() {
	//idle
	m_Animation->SetProps("Enemy_idle", 1, 4, 170);
	//run 
	if (m_IsRunning && !m_IsAttacking)
		m_Animation->SetProps("Enemy_run", 1, 4, 150);
	//attack
	if (m_IsAttacking)
		m_Animation->SetProps("Enemy_attack", 1, 4, 100);
}

void Enemy::moveToPlayer() {

	m_IsRunning = false;
	m_IsAttacking = false;
	m_Rigidbody->UnsetForce();

	m_Vision = Engine::Getinstance()->Getplayer()->GetX() - GetX();
	if (m_Vision <= 500 && m_Vision > 100) {
		m_Rigidbody->ApplyForceX(FORWARD * VEL);
		m_Flip = SDL_FLIP_NONE;
		m_IsRunning = true;
	}

	if (m_Vision >= -500 && m_Vision < -40) {
		m_Rigidbody->ApplyForceX(BACKWARD * VEL);
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_IsRunning = true;
	}

	if (m_Vision >= -40 && m_Vision < 0) {
		m_IsAttacking = true;
		m_Rigidbody->UnsetForce();
	}

	if (m_Vision <= 100 && m_Vision > 0) {
		m_IsAttacking = true;
		m_Rigidbody->UnsetForce();
	}
}
