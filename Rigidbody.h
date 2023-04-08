#pragma once
#include<SDL.h>
#include"Vector2D.h"
using namespace std;

#define UNI_MASS 1.0f
#define GRAVITY 9.0f

#define FORWARD 1
#define BACKWARD -1


#define UPWARD -1
#define DOWNWARD 1


class Rigidbody {
public:
	Rigidbody() {
		m_Mass = UNI_MASS;
		m_Gravity = GRAVITY;
	}
	// SET GRAVITY AND MASS
	inline void SetMass(float mass) { m_Mass = mass; }
	inline void SetGravity(float gravity) { m_Gravity = gravity; }

	//FORCE
	inline void ApplayForce(Vector2D force) { m_Force = force; }
	inline void ApplyForceX(float Fx) { m_Force.X = Fx; }
	inline void ApplyForceY(float Fy) { m_Force.Y = Fy; }
	inline void UnsetForce() { m_Force = Vector2D(0, 0); }

	//FRICTION
	inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
	inline void UnsetFriction() { m_Friction = Vector2D(0, 0); }

	//Getter
	inline float GetMass() { return m_Mass; }
	inline Vector2D Position() { return m_Position; }
	inline Vector2D Velocity() { return m_Velocity; }
	inline Vector2D Accelaration() { return m_Accelaration; }

	//UPDATE METHOD
	void Update(float dt) {
		m_Accelaration.X = (m_Force.X + m_Friction.X) / m_Mass;
		m_Accelaration.Y = m_Gravity + m_Force.Y / m_Mass;
		m_Velocity = m_Accelaration;
		m_Position = m_Velocity;
	}

private:
	float m_Mass;
	float m_Gravity;

	Vector2D m_Force;
	Vector2D m_Friction;
	Vector2D m_Position;
	Vector2D m_Velocity;
	Vector2D m_Accelaration;
};