/*****************************************************************************************
 *                                                                                       *
 * TNM094 Particle System                                                                *
 *                                                                                       *
 * Copyright (c) 2014 Alexander Bock                                                     *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 *                                                                                       *
 ****************************************************************************************/

#include <QApplication>
#include <ghoul/filesystem/filesystem>
#include <ghoul/logging/logging>
#include <ghoul/systemcapabilities/systemcapabilities>

#include "gui.h"

void initialize();

using namespace ghoul::filesystem;
using namespace ghoul::logging;
using namespace ghoul::systemcapabilities;

namespace {
    const std::string _loggerCat = "ParticleSystem";

    // This vector should contain the positions of the particles at the end of the update callback
    std::vector<glm::vec3> _particleData;
}

void addNewSource(SourceType source, const glm::vec3& pos, float value) {
    switch (source) {
    case SourceType::Point:
        LINFO("Point Source button pressed. (" << pos.x << "," << pos.y << "," << pos.z << ") [" << value << "]");
        break;
    case SourceType::Cone:
        LINFO("Cone Source button pressed. (" << pos.x << "," << pos.y << "," << pos.z << ") [" << value << "]");
        break;
    default:
        LFATAL("Missing case in source handler");
    }
}

void addNewEffect(EffectType effect, const glm::vec3& pos, float value) {
    switch (effect) {
        case EffectType::Gravity:
            LINFO("Gravity Effect button pressed. (" << pos.x << "," << pos.y << "," << pos.z << ") [" << value << "]");
            break;
        case EffectType::Wind:
            LINFO("Wind Effects button pressed. (" << pos.x << "," << pos.y << "," << pos.z << ") [" << value << "]");
            break;
        default:
            LFATAL("Missing case in effect handler");
    }
}

// This method is called an undefined number of times per second. 'deltaT' is the time in
// seconds that has passed since the last call.
void update(float deltaT) {
    
}

void removeAll() {
    LINFO("Remove all button pressed");
}

int main(int argc, char** argv) {
    // Sets up the necessary backend
    initialize();

    // Create the Qt application that handles the main run-loop
    QApplication app(argc, argv);

    // Create the GUI widget (containing the rendering window)
    GUI gui;
    // Make the GUI and renderer aware of the data we have
    gui.setData(&_particleData);
    // Register the callbacks which are called during the lifetime of the application
    gui.setCallbacks(addNewSource, addNewEffect, update, removeAll);
    // Show the GUI (will generate the OpenGL context)    
    gui.show();

    // Detect and log all capabilities to the console for debug purposes
    SysCap.detectCapabilities();
    SysCap.logCapabilities();

    //
    // Create and enable your simulator code here
    //



    // Tell the gui+renderer to start the rendering loop
    gui.startRendering();
    // Pass control of the run-loop to the Qt application
    return app.exec();
}

void initialize() {
    // Initialize LogManager to print error messages to the console
    LogManager::initialize(LogManager::LogLevel::Info);
    LogMgr.addLog(new ConsoleLog);

    // Initialize the FileSystem to dynamically determine paths
    FileSystem::initialize();
#ifdef _WIN32
    FileSys.registerPathToken("${ASSETS}", "../assets/");
#else
    FileSys.registerPathToken("${ASSETS}", "assets/");
#endif

    // Initialize SystemCapabilities to detect the active hardware setup
    SystemCapabilities::initialize();
    SysCap.addComponent(new CPUCapabilitiesComponent);
}
