#pragma once
#include"Object.h"
#include"Transformation.h"
#include<string>
#include<iostream>
#include<SDL.h>

using namespace std;

struct Properties
{
public:
	Properties(string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		X = x;
		Y = y;
		Flip = flip;
		Width = width;
		Height = height;
		TextureID = textureID;
	}
public:
	string TextureID;
	int Width, Height;
	float X, Y;
	SDL_RendererFlip Flip;
};

class GameObject : public Object
{
public:
	GameObject(Properties* props) 
	:m_TextureID(props->TextureID), m_width(props->Width), m_height(props->Height), m_Flip(props->Flip) {
		m_Transform = new Transform(props->X, props->Y);
	}
	virtual ~GameObject() {}
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

protected:
	Transform* m_Transform;
	int m_width, m_height;
	string m_TextureID;
	SDL_RendererFlip m_Flip;
};
