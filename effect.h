#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "particle.h"
#include <glm/glm.hpp>
#include <vector>

class Effect {
public:
    virtual void applyToParticles(std::vector<Particle*>& particles, float dt) = 0;
};

class GravityEffect : public Effect {
public:
    GravityEffect(const glm::vec3& position, const float strength);
    void applyToParticles(std::vector<Particle*>& particles, float dt) override;

private:
    const glm::vec3 _position;
    const float _strength;
};

class WindEffect : public Effect {
public:
    WindEffect(const glm::vec3& direction, const float strength);
    void applyToParticles(std::vector<Particle*>& particles, float dt) override;

private:
    const glm::vec3 _direction;
    const float _strength;
};



#endif __EFFECT_H__
