#pragma once
#include"Character.h"
#include"Collider.h"
#include"Rigidbody.h"
#include"SeqAnimation.h"
#include"Vector2D.h"
#include"INCLUDE.h"



class Enemy : public Character {
public:
	Enemy(Properties* props);
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

private:
	Collider* m_Collider;
	Rigidbody* m_Rigidbody;
	SeqAnimation* m_Animation;
	Vector2D* m_LastSafePosiotion;

};

