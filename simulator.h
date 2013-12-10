#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include "particle.h"
#include "source.h"
#include "effect.h"
#include <vector>

class Simulator {
public:
    Simulator(float particleLifetime);

    void update(float dt);

    void addSource(Source* source);
    void addEffect(Effect* effect);

    void removeAll();

    void getParticlePositions(std::vector<glm::vec3>& particleData) const;

private:
    const float _maxParticleLifetime;
    std::vector<Particle*> _particles;
    std::vector<Effect*> _effects;
    std::vector<Source*> _sources;
};

#endif // __SIMULATOR_H__

