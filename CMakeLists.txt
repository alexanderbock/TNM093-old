##################################################################################################
#                                                                                                #
# TNM090 Particle System                                                                         #
#                                                                                                #
# Copyright (c) 2013 Alexander Bock                                                              #
#                                                                                                #
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software  #
# and associated documentation files (the "Software"), to deal in the Software without           #
# restriction, including without limitation the rights to use, copy, modify, merge, publish,     #
# distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the  #
# Software is furnished to do so, subject to the following conditions:                           #
#                                                                                                #
# The above copyright notice and this permission notice shall be included in all copies or       #
# substantial portions of the Software.                                                          #
#                                                                                                #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING  #
# BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND     #
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   #
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, #
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.        #
#                                                                                                #
##################################################################################################

####################
# General settings #
####################
# We want to use the C++11 standard and GCC requires with flag
project(ParticleSimulator)
cmake_minimum_required(VERSION 2.8)
if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

if (APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif ()

set(GHOUL_ROOT_DIR "${PROJECT_SOURCE_DIR}/ghoul")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${GHOUL_ROOT_DIR}/ext)

################
# Source files #
################
# Set all the sources that we will need in this project
set(ParticleSimulator_Simulator_SOURCES
    # Add your new source (.cpp) files here
)

set(ParticleSimulator_Simulator_HEADERS
    # add your new header (.h) files here
)

# Then the main source and the GUI sources
set(ParticleSimulator_GUI_SOURCES main.cpp gui.cpp renderer.cpp)
set(ParticleSimulator_GUI_HEADERS gui.h renderer.h)

################
# Dependencies #
################
# Ghoul
add_definitions(-DGHL_DEBUG)
set(GHOUL_USE_DYNAMIC_GLEW ON)
set(GHOUL_ROOT_DIR "${PROJECT_SOURCE_DIR}/ghoul")
include_directories("${GHOUL_ROOT_DIR}/include")
add_subdirectory(${GHOUL_ROOT_DIR})
set(DEPENDENT_LIBS ${DEPENDENT_LIBS} Ghoul)

# Include then openGL Mathematics library
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

include_directories("${GHOUL_ROOT_DIR}/ext/glew/include")
#add_definitions(-DGLEW_STATIC)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
set(DEPENDENT_LIBS ${DEPENDENT_LIBS} ${GLEW_LIBRARY})

# Include Qt 
set(QT_USE_QTOPENGL TRUE)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
# Wrap the headers to autogenerate the qt metaobject files
qt4_wrap_cpp(ParticleSimulator_GUI_HEADERS_MOC ${ParticleSimulator_GUI_HEADERS})
set(DEPENDENT_LIBS ${DEPENDENT_LIBS} ${QT_LIBRARIES} ${OPENGL_LIBRARIES})

##############
# Executable #
##############
# Create the Particle Simulator exectuable
add_executable(ParticleSimulator
    ${ParticleSimulator_GUI_SOURCES}
    ${ParticleSimulator_GUI_HEADERS}
    ${ParticleSimulator_GUI_HEADERS_MOC}
    ${ParticleSimulator_Simulator_SOURCES}
    ${ParticleSimulator_Simulator_HEADERS}
)
target_link_libraries(ParticleSimulator ${DEPENDENT_LIBS})
#message("${DEPENDENT_LIBS}")

# On Windows, we want to automatically copy all the necessary dll files into the build directory
if (WIN32)
    add_custom_command(
        TARGET ParticleSimulator 
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GHOUL_ROOT_DIR}/ext/glew/lib/glew32.dll" "$<TARGET_FILE_DIR:ParticleSimulator>"
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GHOUL_ROOT_DIR}/ext/glew/lib/glew32mx.dll" "$<TARGET_FILE_DIR:ParticleSimulator>"
    )
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        # 32 bit
        add_custom_command(
            TARGET ParticleSimulator 
            POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GHOUL_ROOT_DIR}/ext/il/lib/win32/DevIL.dll" "$<TARGET_FILE_DIR:ParticleSimulator>"
            POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GHOUL_ROOT_DIR}/ext/il/lib/win32/ILU.dll" "$<TARGET_FILE_DIR:ParticleSimulator>"
            POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GHOUL_ROOT_DIR}/ext/il/lib/win32/ILUT.dll" "$<TARGET_FILE_DIR:ParticleSimulator>"
        )
    else ()
        # 64 bit
        add_custom_command(
            TARGET ParticleSimulator 
            POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GHOUL_ROOT_DIR}/ext/il/lib/win64/DevIL.dll" "$<TARGET_FILE_DIR:ParticleSimulator>"
            POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GHOUL_ROOT_DIR}/ext/il/lib/win64/ILU.dll" "$<TARGET_FILE_DIR:ParticleSimulator>"
            POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GHOUL_ROOT_DIR}/ext/il/lib/win64/ILUT.dll" "$<TARGET_FILE_DIR:ParticleSimulator>"
        )
    endif ()
endif ()
