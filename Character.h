#pragma once
#include"GameObject.h"
#include<string>

using namespace std;
class Character : public GameObject {
public:
	Character(Properties* props) : GameObject(props) {}
		
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

protected:
	string m_Name;
 };