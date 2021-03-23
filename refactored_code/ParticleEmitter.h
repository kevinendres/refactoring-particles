//---------------------------------------------------------------
// Assignment Copyright 2021, Ed Keenan, all rights reserved.
// Refactored by Kevin Endres
//---------------------------------------------------------------

#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Matrix.h"
#include "Vect4D.h"
#include "Particle.h"


class ParticleEmitter : Align16
{
public:
	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter&) = delete;
	ParticleEmitter& operator= (const ParticleEmitter&) = delete;
	~ParticleEmitter();
	
	void SpawnParticle();
	void update();
	void draw();

	void addVariance(Vect4D& pos, Vect4D& vel, Vect4D& sc) const;

private:

	float	last_loop;
	int		particleCount;

	Particle* particleBuffer;
	Particle* bufferPtr;
	Particle* bufferLimit;
};


#endif 

// --- End of File ---
