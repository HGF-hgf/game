#pragma once
#include"Point.h"
#include"Vector2D.h"
#include<SDL.h>
#include"Engine.h"

using namespace std;

class Camera {
public:
	
	void Update(float dt);

	inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();}
	inline SDL_Rect GetViewBox() { return m_ViewBox; }
	inline Vector2D GetPosition() { return m_Position; }
	inline void SetTarget(Point* target) { m_Target = target; }

private:

	Camera() {m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; }

	SDL_Rect m_ViewBox;
	Point* m_Target;
	Vector2D m_Position;
	static Camera* s_Instance;
};