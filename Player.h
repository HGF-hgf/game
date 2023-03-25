#pragma once
#include"Character.h"
#include"Animation.h"
#include"Rigidbody.h"
using namespace std;
 
class Player : public Character {
public:
	Player(Properties* props);
	
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	//int m_Row, m_Frame, m_Framecount, m_animationSpeed;
	Animation* m_Animation;
	Rigidbody* m_Rigidbody;
};