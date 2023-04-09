#pragma once
#include"Character.h"
#include"SpriteAnimation.h"
#include"Rigidbody.h"
#include"Collider.h"
#include"Vector2D.h"

#define JUMP_TIME 2.0f
#define JUMP_FORCE 7.0f

#define RUN_FORCE 3.0f
#define ATTACK_TIME 20.0f

using namespace std;
 
class Player : public Character {
public:
	Player(Properties* props);
	
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);


private:
	void AnimationState();
 
	bool m_IsJumping;
	bool m_IsGrounded;
	bool m_IsRunning;
	bool m_IsFalling;
	bool m_IsAttacking;
	bool m_IsCrouching;

	float m_JumpTime; // Time the player leave the ground
	float m_JumpForce; //forcce apply on the player at the jumpoing time
	float m_AttackTime;

	Collider* m_Collider;	
	SpriteAnimation* m_Animation;
	Rigidbody* m_Rigidbody;
	Vector2D m_LastSafePosition;// to make sure the player doesn't stuck
};