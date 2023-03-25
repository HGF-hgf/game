#pragma once
#include<iostream>
#include<SDL.h>

using namespace std;

class Object {
public:
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;
};
