#include "particle.h"

Particle::Particle(const glm::vec3& position, const glm::vec3& velocity)
    : _position(position)
    , _velocity(velocity)
    , _lifeTime(0.f)
{}

void Particle::update(float dt) {
    _lifeTime += dt;
    _position += _velocity * dt;
}

const glm::vec3& Particle::position() const {
    return _position;
}

glm::vec3& Particle::position() {
    return _position;
}

const glm::vec3& Particle::velocity() const {
    return _velocity;
}

glm::vec3& Particle::velocity() {
    return _velocity;
}

const float Particle::lifetime() const {
    return _lifeTime;
}
