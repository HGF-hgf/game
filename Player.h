#pragma once
#include"Character.h"
#include"Animation.h"
#include"Rigidbody.h"
#include"Collider.h"
#include"Vector2D.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f

using namespace std;
 
class Player : public Character {
public:
	Player(Properties* props);
	
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);


private:
	bool m_IsJumping;
	bool m_IsGrounded;

	float m_JumpTime; // Time the player leave the ground
	float m_JumpForce; //forcce apply on the player at the jumpoing time
	
	Collider* m_Collider;	
	Animation* m_Animation;
	Rigidbody* m_Rigidbody;
	Vector2D m_LastSafePosition;// to make sure the player doesn't stuck
};