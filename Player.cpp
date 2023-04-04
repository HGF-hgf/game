#include"Player.h"
#include"Texture.h"
#include"Input.h"
#include<SDL.h>
#include"Camera.h"
#include"CollisionHandler.h"
#include"Collider.h"

using namespace std;

Player::Player(Properties* props) :Character(props) {
	/*m_IsJumping = false;
	m_IsGrounded = false;
	*/

	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;

	m_Collider = new Collider();
	m_Collider->SetBuffer(-60, -20, 0, 0);

	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(3.0f);

	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 1, 6, 100);
}

void Player::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_width, m_height);
	
	/*Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::Getinstance()->GetRenderer(), &box);*/
}

void Player::Update(float dt) {
	
	m_Rigidbody->UnsetForce();
	m_Animation->SetProps("player", 1, 4, 100);
	m_Rigidbody->UnsetForce();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
			m_Rigidbody->ApplyForceX(5 * BACKWARD);
			m_Animation->SetProps("player_run", 1, 4, 100, SDL_FLIP_HORIZONTAL);
	}


	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		m_Rigidbody->ApplyForceX(5*FORWARD);
		m_Animation->SetProps("player_run", 1, 4, 100);
	}
	
	
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
	//m_Rigidbody->Update(dt);
	//move on X axis
	m_Rigidbody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_Rigidbody->Position().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
		m_Transform->X = m_LastSafePosition.X;
		
	//move on Y axis
	m_Rigidbody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_Rigidbody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else {
		m_IsGrounded = false;
	}

	if (m_IsJumping || m_IsGrounded){
		m_Animation->SetProps("player_jump", 1, 4, 150);
	}
	m_Origin->X = m_Transform->X + m_width / 2;
	m_Origin->Y = m_Transform->Y + m_height / 2;
	m_Animation->Update();
}

void Player::Clean() {
	Texture::Getinstance()->Drop(m_TextureID);
}