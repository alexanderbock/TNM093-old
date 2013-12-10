#include "effect.h"

using glm::vec3;

GravityEffect::GravityEffect(const vec3& position, const float strength)
    : _position(position)
    , _strength(strength)
{}

void GravityEffect::applyToParticles(std::vector<Particle*>& particles, float dt) {
    for (auto it = particles.begin(); it != particles.end(); ++it) {
        Particle* currentParticle = *it;

        const float distance = glm::distance(currentParticle->position(), _position);

        if (distance > 2.f) {
            glm::vec3 acceleration = (glm::normalize(_position - currentParticle->position()) * _strength) / (distance * distance);

            currentParticle->velocity() += acceleration * dt;
        }
    }
}

WindEffect::WindEffect(const vec3& direction, const float strength)
    : _direction(direction)
    , _strength(strength)
{}

void WindEffect::applyToParticles(std::vector<Particle*>& particles, float dt) {
    for (auto it = particles.begin(); it != particles.end(); ++it) {
        Particle* currentParticle = *it;
        const glm::vec3 acceleration = _direction * _strength;
        currentParticle->velocity() += acceleration * dt;
    }
}