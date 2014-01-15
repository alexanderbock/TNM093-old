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
 
#version 400 core

in vec3 position;
out vec4 fragColor;

uniform vec3 _lightPosition;
uniform vec3 _cameraPosition;

const vec3 _ambientColor = vec3(0.4, 0.4, 0.4);
const vec3 _diffuseColor = vec3(0.5);
const vec3 _specularColor = vec3(0.6);
const float _shininess = 5.0;

uniform sampler2D _texture;

void main() {
    vec4 textureData = texture(_texture, gl_PointCoord.xy);
    
    vec3 N = textureData.xyz;
    vec3 L = _lightPosition - position;
    vec3 V = normalize(_cameraPosition - position);
    
    float d = length(L);
    L /= d;
    
    vec3 shadedColor = vec3(1.0, 0.0, 0.0) * textureData.rgb;
    vec3 ka = shadedColor;
    vec3 kd = shadedColor;
    vec3 ks = vec3(1.0);
    
    // Ambient term
    shadedColor += ka * _ambientColor;
    
    // Diffuse term
    float NdotL = max(dot(N, L), 0.0);
    shadedColor += kd * _diffuseColor * NdotL;

    // Specular term
    vec3 H = normalize(V + L);
    float NdotH = pow(max(dot(N, H), 0.0), _shininess);
    shadedColor += ks * _specularColor * NdotH;
    
    fragColor = vec4(1.0, 0.0, 0.0, 1.0) * textureData;
    fragColor.rgb *= shadedColor;
}