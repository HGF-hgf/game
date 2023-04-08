#include"Player.h"
#include"Texture.h"
#include"INCLUDE.h"
#include"Input.h"
#include"Engine.h"
#include"Factory.h"
#include"CollisionHandler.h"
#include"Camera.h"

static Registrar<Player> registrar("player");

Player::Player(Properties* props) :Character(props) {
	
	m_IsRunning = false;
	m_IsJumping = false;
	m_IsFalling = false;
	m_IsGrounded = false;
	m_IsAttacking = false;
	m_IsCrouching = false;
	
	m_Flip = SDL_FLIP_NONE;
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_AttackTime = ATTACK_TIME;

	m_Collider = new Collider();
//	m_Collider->SetBuffer(-60, -20, 0, 0);

	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(3.0f);

	m_Animation = new SpriteAnimation();
	m_Animation->SetProps(m_TextureID, 1, 6, 100);
}

void Player::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_width, m_height, 1, 1, m_Flip);
	//m_Collider->Draw();
}

void Player::Update(float dt) {
	
	m_IsCrouching = false;
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

	//move on X axis
	m_Rigidbody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_Rigidbody->Position().X;
	m_Collider->Set(m_Transform->X + 48, m_Transform->Y + 44, 30, 52);
	 
	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
		m_Transform->X = m_LastSafePosition.X;
		
	//move on Y axis
	m_Rigidbody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_Rigidbody->Position().Y;
	m_Collider->Set(m_Transform->X + 48 , m_Transform->Y + 44, 30, 52);//+44 +32 30 63
	//std::cout << m_Collider->Get().y << '\n';
	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else {
		m_IsGrounded = false;
	}
	
	
	m_Origin->X = m_Transform->X + m_width / 2;
	m_Origin->Y = m_Transform->Y + m_height / 2;

	AnimationState();
	m_Animation->Update(dt);
}

void Player::AnimationState() {
//idle
	m_Animation->SetProps("player_idle", 1, 6, 100);

//run
	if(m_IsRunning && !m_IsJumping)
	m_Animation->SetProps("player_run", 1, 4, 100);

//jump
	if(m_IsJumping)
	m_Animation->SetProps("player_jump", 1, 3, 250);

//falling
	if (m_IsFalling)
		m_Animation->SetProps("player_fall", 1, 3, 450);
//attacking

}

void Player::Clean() {
	Texture::Getinstance()->Drop(m_TextureID);
}