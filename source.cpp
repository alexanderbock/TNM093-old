#include "source.h"


ExplosionSource::ExplosionSource(const glm::vec3& position, const float spawnRate)
    : _position(position)
    , _reciSpawnRate(1.f / spawnRate)
    , _runningTime(0.f)
    , _distribution(-0.01f, 0.01f)
{}

std::vector<Particle*> ExplosionSource::createParticles(float dt) {
    _runningTime += dt;

    std::vector<Particle*> result;
    while (_runningTime >= _reciSpawnRate) {
        glm::vec3 velocity(_distribution(_generator), _distribution(_generator), _distribution(_generator));
        velocity = glm::normalize(velocity);

        Particle* particle = new Particle(_position, velocity);
        result.push_back(particle);

        _runningTime -= _reciSpawnRate;
    }
    return result;
}

ConeSource::ConeSource(const glm::vec3& position, const float spawnRate, const glm::vec3& direction, const float openingAngle)
    : _position(position)
    , _reciSpawnRate(1.f / spawnRate)
    , _direction(direction)
    , _openingAngle(openingAngle)
    , _runningTime(0.f)
    , _distributionAngle(-_openingAngle/2.f, _openingAngle/2.f)
{}

std::vector<Particle*> ConeSource::createParticles(float dt) {
    _runningTime += dt;

    std::vector<Particle*> result;
    while (_runningTime >= _reciSpawnRate) {
        // Determine the random numbers in spherical coordinates
        const float radius = _distributionRadius(_generator);
        const float phi = 2 * _distributionAngle(_generator);
        const float theta = _distributionAngle(_generator);

        // Transform into Cartesian coordinates
        const float x = radius * glm::sin(theta) * glm::cos(phi);
        const float y = radius * glm::sin(theta) * glm::sin(phi);
        const float z = radius * glm::cos(theta);

        glm::vec3 velocity(x, y, z);

        Particle* particle = new Particle(_position, velocity);
        result.push_back(particle);

        _runningTime -= _reciSpawnRate;
    }
    return result;
}
