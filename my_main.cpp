/**************************************************************************************************
 *                                                                                                *
 * TNM090 Particle System                                                                         *
 *                                                                                                *
 * Copyright (c) 2013 Alexander Bock                                                              *
 *                                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software  *
 * and associated documentation files (the "Software"), to deal in the Software without           *
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,     *
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the  *
 * Software is furnished to do so, subject to the following conditions:                           *
 *                                                                                                *
 * The above copyright notice and this permission notice shall be included in all copies or       *
 * substantial portions of the Software.                                                          *
 *                                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING  *
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND     *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.        *
 *                                                                                                *
 *************************************************************************************************/

#include <GL/glew.h>

#include <QApplication>
#include <QWidget>
#include <glm/gtc/constants.hpp>
#include <random>
#include "ghoul/logmanager"

#include "simulator.h"
#include "source.h"
#include "effect.h"
#include "gui.h"

Simulator _simulator(10.f);
std::vector<glm::vec3> _particleData;

std::default_random_engine _generator;
std::uniform_real_distribution<float> _distributionPosition(-1.f, 1.f);
std::uniform_real_distribution<float> _distributionAngle(0.f, glm::pi<float>());

void addNewSource(SourceType source, const glm::vec3& pos, float value) {
    switch (source) {
    case SourceType::Point:
        _simulator.addSource(new ExplosionSource(pos, 1000 * value));
        LINFOC("ApplicationHandler", "Point Source button pressed. (" << pos.x << "," << pos.y << "," << pos.z << ") [" << value << "]");
        break;
    case SourceType::Cone:
        _simulator.addSource(new ConeSource(
            pos,            // Position
            1000 * value,   // Spawnrate
            glm::vec3(0,0,1), glm::radians(90.f)
            //glm::vec3(_distributionPosition(_generator), _distributionPosition(_generator), _distributionPosition(_generator)),    // Direction
            //_distributionAngle(_generator)    // Opening angle
            )); 
        LINFOC("ApplicationHandler", "Cone Source button pressed. (" << pos.x << "," << pos.y << "," << pos.z << ") [" << value << "]");
        break;
    default:
        LFATALC("ApplicationHandler", "Missing case in source handler");
    }
}

void addNewEffect(EffectType effect, const glm::vec3& pos, float value) {
    switch (effect) {
        case EffectType::Gravity:
            _simulator.addEffect(new GravityEffect(pos, value * 100));
            LINFOC("ApplicationHandler", "Gravity Effect button pressed. (" << pos.x << "," << pos.y << "," << pos.z << ") [" << value << "]");
            break;
        case EffectType::Wind:
            _simulator.addEffect(new WindEffect(pos, value * 10));
            LINFOC("ApplicationHandler", "Wind Effects button pressed. (" << pos.x << "," << pos.y << "," << pos.z << ") [" << value << "]");
            break;
        default:
            LFATALC("ApplicationHandler", "Missing case in effect handler");
    }
}

void update(float deltaT) {
    _simulator.update(deltaT);
    _simulator.getParticlePositions(_particleData);
}

void removeAll() {
    _simulator.removeAll();
}

int main(int argc, char** argv) {
    ghoul::logging::LogManager::init(ghoul::logging::LogManager::LogLevelInfo);
    LogMgr.addLog(new ghoul::logging::ConsoleLog);

    QApplication app(argc, argv);

    GUI gui;
    gui.setData(&_particleData);
    gui.setCallbacks(addNewSource, addNewEffect, update, removeAll);
    gui.show();

    return app.exec();
}
