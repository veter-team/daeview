#ifndef __SHADERS_H
#define __SHADERS_H

#include <utility>


typedef std::pair<const char*, const char*> VPFPShaderProg;

// Flat shader
extern VPFPShaderProg flatShader;

// Point light, diffuse lighting only
extern VPFPShaderProg pointLightDiff;

// ADS Gouraud shading
extern VPFPShaderProg ADSGouraud;

// ADS Phong shading
extern VPFPShaderProg ADSPhong;

extern VPFPShaderProg texturePointLightDiff;

#endif // __SHADERS_H
