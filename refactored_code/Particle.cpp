//---------------------------------------------------------------
// Assignment Copyright 2021, Ed Keenan, all rights reserved.
// Refactored by Kevin Endres
//---------------------------------------------------------------

#include "Particle.h"

Particle::Particle()
{
}

Particle::Particle(const float life)
	: next(nullptr), prev(nullptr), life(life), rotation(0.0f), position(Vect4D(0.0f, 0.0f, 0.0f)), velocity(Vect4D(0.0f, 1.0f, 0.0f)), scale(Vect4D(1.0f, 1.0f, 1.0f))
{
}

Particle::Particle(const Particle& R)
	: next(nullptr), prev(nullptr), life(R.life), rotation(R.rotation), position(R.position), velocity(R.velocity), scale(R.scale)
{
}

Particle& Particle::operator= (const Particle& R)
{
	next = nullptr;
	prev = nullptr;
	this->life = R.life;
	this->position = R.position;
	this->velocity = R.velocity;
	this->scale = R.scale;
	this->rotation = R.rotation;
	return *this;
}

Particle::~Particle()
{
	// nothing to do
}

void Particle::Update(const float& time_elapsed)
{
	// serious math below - magic secret sauce
	life += time_elapsed;
	position += velocity * time_elapsed;
	Vect4D z_axis(0.0f, -0.25f, 1.0f);
	position.Cross(z_axis, z_axis);
	z_axis.norm(z_axis);
	z_axis *= life;
	position += z_axis;

	rotation += time_elapsed * 1.005f;
}

const Matrix Particle::particleTransform() const
{
	float rcos = cosf(this->rotation);
	float rsin = sinf(this->rotation);

	float px = this->position.getX() + -0.0f;
	float py = this->position.getY() + -3.0f;
	float pz = this->position.getZ() + -10.0f;

	float sx = this->scale.getX();
	float sy = this->scale.getY();
	float sz = this->scale.getZ();

	return Matrix(
		sx * sx * rcos, sy * sx * (-rsin), 0.0f, 0.0f,
		sx * sy * rsin, sy * sy * rcos, 0.0f, 0.0f,
		0.0f, 0.0f, sz * sz, 0.0f,
		sx * (rcos * px + rsin * py), sy * (-rsin * px + rcos * py),
		sz * pz, 1.0f);
}
// --- End of File ---
