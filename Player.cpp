#include"Player.h"
#include"Texture.h"
#include"INCLUDE.h"
#include"Input.h"
#include"Engine.h"
//#include"Factory.h"
#include"CollisionHandler.h"
#include"Camera.h"

//static Registrar<Player> registrar("player");

Player::Player(Properties* props, float Row, float FrameCount, float AnimationSpeed, float x, float y, float w, float h) : Character(props, Row, FrameCount, AnimationSpeed, x, y, w, h) {
	
	//m_RunForce = RUN_FORCE;
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_AttackTime = ATTACK_TIME;
}

void Player::Update(float dt) {

	m_IsRunning = false;
	m_Rigidbody->UnsetForce();
	
	//RUN FORWARD
	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking) {
		m_Rigidbody->ApplyForceX(FORWARD * RUN_FORCE);
		m_Flip = SDL_FLIP_NONE;
		m_IsRunning = true;
	}

	//RUN BACKWARD
	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking) {
		m_Rigidbody->ApplyForceX(BACKWARD * RUN_FORCE);
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_IsRunning = true;
	}

	//ATTACK
	/*if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)) {
		m_Rigidbody->UnsetForce();
		m_IsAttacking = true;
	}*/
	
	
	//JUMP
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded) {
		m_IsJumping = true;
		m_IsGrounded = false;
		m_Rigidbody->ApplyForceY(UPWARD * m_JumpForce);	
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0) {
		m_JumpTime -= dt;
		m_Rigidbody->ApplyForceY(UPWARD * m_JumpForce);
	}
	else
	{
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}
	
	//FALL
	if (m_Rigidbody->Velocity().Y > 0 && !m_IsGrounded) {
		m_IsFalling = true;
	}
	else{
		m_IsFalling = false;
	}

	//ATTACK TIMER 
	if (m_IsAttacking && m_AttackTime > 0) {
		m_AttackTime -= dt;
	}
	else {
		m_IsAttacking = false;
		m_AttackTime = ATTACK_TIME;
	}

	Character::Update(dt);
	
	AnimationState();
	m_Animation->Update(dt);
}

void Player::AnimationState() {
//idle
	m_Animation->SetProps("player_idle", 1, 6, 100);

//run
	if(m_IsRunning && !m_IsJumping)
	m_Animation->SetProps("player_run", 1, 4, 150);

//jump
	if(m_IsJumping)
	m_Animation->SetProps("player_jump", 1, 3, 250);

//falling
	if (m_IsFalling)
		m_Animation->SetProps("player_fall", 1, 3, 450);
//dead
	if (m_IsDead)
		cout << "Game Over" << endl;

}

