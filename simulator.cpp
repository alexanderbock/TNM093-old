#include "simulator.h"

Simulator::Simulator(float particleLifetime)
    : _maxParticleLifetime(particleLifetime)
    , _particles()
    , _effects()
    , _sources()
{}

void Simulator::update(float dt) {
    for (auto effectIt = _effects.begin(); effectIt != _effects.end(); ++effectIt)
        (*effectIt)->applyToParticles(_particles, dt);

    for (auto sourceIt = _sources.begin(); sourceIt != _sources.end(); ++sourceIt) {
        const std::vector<Particle*>& particles = (*sourceIt)->createParticles(dt);
        _particles.insert(_particles.end(), particles.begin(), particles.end());
    }

    for (size_t i = 0; i < _particles.size(); ++i) {
        _particles[i]->update(dt);
        if (_particles[i]->lifetime() > _maxParticleLifetime) {
            delete _particles[i];
            _particles.erase(_particles.begin() + i);
            ++i;
        }
    }
}

void Simulator::addSource(Source* source) {
    _sources.push_back(source);
}

void Simulator::addEffect(Effect* effect) {
    _effects.push_back(effect);
}

void Simulator::getParticlePositions(std::vector<glm::vec3>& particleData) const {
    particleData.resize(_particles.size());
    for (size_t i = 0; i < _particles.size(); ++i)
        particleData[i] = _particles[i]->position();
}

void Simulator::removeAll() {
    for (size_t i = 0; i < _sources.size(); ++i)
        delete _sources[i];
    _sources.clear();

    for (size_t i = 0; i < _effects.size(); ++i)
        delete _effects[i];
    _effects.clear();

    for (size_t i = 0; i < _particles.size(); ++i)
        delete _particles[i];
    _particles.clear();
}

