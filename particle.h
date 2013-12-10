#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <glm/glm.hpp>

class Particle {
public:
    Particle(const glm::vec3& position, const glm::vec3& velocity);
    void update(float dt);

    const glm::vec3& position() const;
    glm::vec3& position();
    const glm::vec3& velocity() const;
    glm::vec3& velocity();

    const float lifetime() const;

private:
    glm::vec3 _position;
    glm::vec3 _velocity;
    float _lifeTime;
};

#endif // __PARTICLE_H__