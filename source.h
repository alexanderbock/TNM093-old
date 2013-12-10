#ifndef __SOURCE_H__
#define __SOURCE_H__

#include <glm/glm.hpp>
#include "particle.h"
#include <random>
#include <vector>

class Source {
public:
    virtual std::vector<Particle*> createParticles(float dt) = 0;
};

class ExplosionSource : public Source {
public:
    ExplosionSource(const glm::vec3& position, const float spawnRate);
    std::vector<Particle*> createParticles(float dt) ;

private:
    const glm::vec3 _position;
    const float _reciSpawnRate;
    float _runningTime;

    std::default_random_engine _generator;
    std::uniform_real_distribution<float> _distribution;
};

class ConeSource : public Source {
public:
    ConeSource(const glm::vec3& position, const float spawnRate, const glm::vec3& direction, const float openingAngle);
    std::vector<Particle*> createParticles(float dt);

private:
    const glm::vec3 _position;
    const float _reciSpawnRate;
    const glm::vec3 _direction;
    const float _openingAngle;
    float _runningTime;

    std::default_random_engine _generator;
    std::uniform_real_distribution<float> _distributionAngle;
    std::uniform_real_distribution<float> _distributionRadius;
};

#endif // __SOURCE_H__ 