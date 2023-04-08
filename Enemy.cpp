#include"Enemy.h"
#include"Camera.h"
#include"Input.h"
#include"Factory.h"
#include"CollisionHandler.h"
#include"INCLUDE.h"

static Registrar<Enemy> registrar("enemy");

Enemy::Enemy(Properties* props) : Character(props) {
	m_Rigidbody = new Rigidbody;
	m_Rigidbody->SetGravity(3.0f);

	m_Collider = new Collider();

	m_Animation = new SeqAnimation;
//	m_Animation->Parse("texture/animation.aml");
	//m_Animation->SetCurrentSeq("");

}

void Enemy::Draw() {
	m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 1, 1, m_Flip);
}

void Enemy::Update(float dt) {

//	Xaxis
	m_Rigidbody->Update(dt);
	m_LastSafePosiotion->X = m_Transform->X;
	m_Transform->X += m_Rigidbody->Position().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 64);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosiotion->X;
	}

	//Yaxis
	m_Rigidbody->Update(dt);
	m_LastSafePosiotion->Y = m_Transform->Y;
	m_Transform->Y += m_Rigidbody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 64);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosiotion->Y;
	}

	m_Animation->Update(dt);

	if (m_Animation->IsEnded()) {
		m_Animation->SetRepeat(true);
	//	m_Animation->SetCurrentSeq("enemy_idle");
	}

}

void Enemy::Clean() {

}