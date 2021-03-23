//---------------------------------------------------------------
// Assignment Copyright 2021, Ed Keenan, all rights reserved.
// Refactored by Kevin Endres
//---------------------------------------------------------------

#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"
#include "Matrix.h"

class Particle : Align16
{
public:
	friend class ParticleEmitter;
	friend class Matrix;
	
	Particle();	
	Particle(const float);	
	Particle(const Particle&);
	Particle& operator= (const Particle&);
	~Particle();

	void Update(const float& time_elapsed);
	const Matrix particleTransform() const;

private:
	Particle *next;
	Particle *prev;

	float	life;
	float	rotation;
	Vect4D	position;
	Vect4D	velocity;
	Vect4D	scale;
};

#endif 

// --- End of File ---
