#include"Player.h"
#include"Texture.h"
#include"Input.h"
#include<SDL.h>

using namespace std;

Player::Player(Properties* props) :Character(props) {
	m_Rigidbody = new Rigidbody();
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 1, 6, 100);
}

void Player::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_width, m_height);

}

void Player::Update(float dt) {

	m_Animation->SetProps("player", 1, 4, 100);
	m_Rigidbody->UnsetForce();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		m_Rigidbody->ApplyForceX(5*FORWARD);
		m_Animation->SetProps("player_run", 1, 4, 100);
	}
	
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		m_Rigidbody->ApplyForceX(5*BACKWARD);
		m_Animation->SetProps("player_run", 1, 4, 100, SDL_FLIP_HORIZONTAL);
	}
	m_Rigidbody->Update(0.8);
	
	m_Transform->TransformX( m_Rigidbody->Position().X);
	//m_Transform->TransformY( m_Rigidbody->Position().Y);
	m_Animation->Update();
}

void Player::Clean() {
	Texture::Getinstance()->Clean();
}