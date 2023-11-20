#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(int _numParticles)
{
	numParticles = _numParticles;	// Set the number of particles

	// Allocate memory for positions, velocities, colors, and lifetimes.
	positions = new float[numParticles * 3];
	velocities = new float[numParticles * 3];
	colors = new float[numParticles * 4];
	lifeTimes = new float[numParticles];


	for (int i = 0; i < numParticles; i++) {
		// Initialize the life times
		lifeTimes[i] = maxLifeTime - maxLifeTime * i / numParticles;

		// initialize velocities to a random value within the velocity range
		velocities[i * 3 + 0] = getRandomValue(minSpeedX, maxSpeedX);	// x
		velocities[i * 3 + 1] = getRandomValue(minSpeedY, maxSpeedY);	// y
		velocities[i * 3 + 2] = getRandomValue(minSpeedZ, maxSpeedZ);	// z

		// initialize positions at the origin
		positions[i * 3 + 0] = 0.0f;	// x
		positions[i * 3 + 1] = 0.0f;	// y
		positions[i * 3 + 2] = 0.0f;	// z

		// initialize colors as solid blue
		colors[i * 4 + 0] = 0.0f;	// red
		colors[i * 4 + 1] = 0.0f;	// green
		colors[i * 4 + 2] = 1.0f;	// blue
		colors[i * 4 + 3] = 1.0f;	// alpha

	}
}

void ParticleSystem::update(float deltaTime)
{
	for (int i = 0; i < numParticles; i++) {

		// Update lifetime, velocity, position, and color.

		lifeTimes[i] += deltaTime;

		// velocity
		// x and z velocities should remain the same
		// alter y velocity based on gravity
		velocities[i * 3 + 1] += acceleration[1] * deltaTime;

		// incremement position based on velocity
		positions[i * 3 + 0] += velocities[i * 3 + 0] * deltaTime;
		positions[i * 3 + 1] += velocities[i * 3 + 1] * deltaTime;
		positions[i * 3 + 2] += velocities[i * 3 + 2] * deltaTime;

		// color gradually fades
		// only decrement alpha indices
		colors[i * 4 + 3] = 1 - (lifeTimes[i] / maxLifeTime);


		// Reset particle states (positions, velocities, colors, and lifetimes) when the lifetime reaches the maxLifeTime

		if (lifeTimes[i] >= maxLifeTime)
		{
			// reset lifetimes
			lifeTimes[i] = 0.0f;

			// reset velocities
			velocities[i * 3 + 0] = getRandomValue(minSpeedX, maxSpeedX);	// x
			velocities[i * 3 + 1] = getRandomValue(minSpeedY, maxSpeedY);	// y
			velocities[i * 3 + 2] = getRandomValue(minSpeedZ, maxSpeedZ);	// z

			// reset positions to the origin
			positions[i * 3 + 0] = 0.0f;	// x
			positions[i * 3 + 1] = 0.0f;	// y
			positions[i * 3 + 2] = 0.0f;	// z

			// reset alpha to 1
			colors[i * 4 + 3] = 1.0f;	// alpha
		}
	}
}

void ParticleSystem::draw()
{
	// vertex array mode drawing
	glPointSize(3.0f);

	// Enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, positions);

	// Enable color arrays
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colors);

	glDrawArrays(GL_POINTS, 0, numParticles);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void ParticleSystem::prepareBufObjects()
{
	// generate position buffer object
	glGenBuffers(1, &pos_id);

	// bind VBO in order to use
	glBindBuffer(GL_ARRAY_BUFFER, pos_id);

	// upload data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numParticles * 3, positions, GL_STATIC_DRAW);

	// clean up 
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// generate color buffer object
	glGenBuffers(1, &col_id);
	glBindBuffer(GL_ARRAY_BUFFER, col_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numParticles * 4, colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

float ParticleSystem::getRandomValue(float min_value, float max_value)
{
	return min_value + (std::rand()) / (RAND_MAX / (max_value - min_value));;
}
