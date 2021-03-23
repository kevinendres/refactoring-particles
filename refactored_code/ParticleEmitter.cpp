//---------------------------------------------------------------
// Assignment Copyright 2021, Ed Keenan, all rights reserved.
// Refactored by Kevin Endres
//---------------------------------------------------------------

#include "OpenGLDevice.h"
#include "ParticleEmitter.h"
#include "Settings.h"

PerformanceTimer globalTimer;

ParticleEmitter::ParticleEmitter()
	: last_loop(globalTimer.GetGlobalTime()),
	particleCount(0)
{
	//allocate memory for all Particles
	this->particleBuffer = (Particle *)_aligned_malloc(NUM_PARTICLES * sizeof(Particle), 16);
	this->bufferPtr = this->particleBuffer;
	bufferLimit = bufferPtr + NUM_PARTICLES;
}

ParticleEmitter::~ParticleEmitter()
{
	_aligned_free(particleBuffer);
}

void ParticleEmitter::SpawnParticle()
{
	// create another particle in pre-allocated buffer
	AZUL_PLACEMENT_NEW_BEGIN
#undef new
	Particle* newParticle = new(bufferPtr++) Particle(0.0f);
	AZUL_PLACEMENT_NEW_END
	if (bufferPtr >= bufferLimit) {
		bufferPtr = particleBuffer;
	}

	// apply the variance
	this->addVariance(newParticle->position, newParticle->velocity, newParticle->scale);
}

void ParticleEmitter::update()
{
	// spawn particles as needed
	if (!this->particleCount) {
		for (int i = 0; i < NUM_PARTICLES; ++i)
		{
			// spawn a particle
			this->SpawnParticle();
		}
		this->particleCount = NUM_PARTICLES;
	}
	
	// get current and elapsed time
	float current_time = globalTimer.GetGlobalTime();
	float time_elapsed = current_time - this->last_loop;

	//clear the particle buffer; the particles have exceeded their time limit
	Particle* p = this->particleBuffer;
	if ((p->life > MAX_LIFE))
	{
		// clear the buffer
		memset(this->particleBuffer, 0, NUM_PARTICLES * sizeof(Particle));

		// update the number of particles
		this->particleCount = 0;
	}
	else {
		for (int i = 0; i < particleCount; ++i, ++p)
		{
			// update every particle's position and life
			p->Update(time_elapsed);
		}
	}
	last_loop = current_time;
}
	   
void ParticleEmitter::draw()
{
	for (Particle* it = this->particleBuffer; it < bufferLimit; ++it) {
		// iterate throught the list of particles and create transform matrix
		Matrix tmp = it->particleTransform();

		//draw the particle
		OpenGLDevice::SetTransformMatrixFloat((const float*)&tmp);
	}
}

void ParticleEmitter::addVariance(Vect4D& pos, Vect4D& vel, Vect4D& sc) const
{
	// x - variance
	float *t_pos = reinterpret_cast<float*>(&pos);
	float var = static_cast<float>(rand() % 1000) * 0.001f;
	int sign = rand() % 2;
	if(!sign)
	{
		var *= -1.0f;
	}
	*t_pos++ += var;

	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = rand() % 2;
	if(!sign)
	{
		var *= -1.0f;
	}
	*t_pos++ += var;
	
	// z - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = rand() % 2;
	if(!sign)
	{
		var *= -1.0f;
	}
	*t_pos++ += var;
	
	// x  - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = rand() % 2;
	t_pos = reinterpret_cast<float*>(&vel);
	if(!sign)
	{
		var *= -1.0f;
	}
	*t_pos++ += var;
	
	// y - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = rand() % 2;
	if(!sign)
	{
		var *= -1.0f;
	}
	*t_pos++ += 4.0f * var;
	
	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = rand() % 2;
	if(!sign)
	{
		var *= -1.0f;
	}
	*t_pos++ += 0.4f * var;
	
	// update scale
	var = static_cast<float>(rand() % 1000) * 0.002f;
	sign = rand() % 2;
	if(!sign)
	{
		var *= -1.0f;
	}
	sc *= var;
}

// --- End of File ---
