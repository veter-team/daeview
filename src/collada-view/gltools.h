#ifndef __GLTOOLS_H
#define __GLTOOLS_H

#include <GL/glew.h>			// OpenGL Extension "autoloader"

// There are conflicting definitions in SDL_opengl.h
// with glew.h. So prefere glew.h.
#define GL_SGIX_fragment_lighting

#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <vector>

#include "comdefs.h"


typedef std::vector<std::string> ErrorMessages;

GLuint 
CreateTexture(SDL_Surface *surface, GLfloat *texcoord, bool should_flip);

/**
 * Get the OpenGL version number
 */
void 
GetOpenGLVersion(GLint &nMajor, GLint &nMinor);

/**
 * Check for any GL errors that may affect rendering
 * Check the framebuffer, the shader, and general errors
 */
ErrorMessages 
CheckErrors(GLuint progName);

enum SHADER_ATTRIBUTE
{
  ATTRIBUTE_VERTEX = 0, ATTRIBUTE_COLOR, ATTRIBUTE_NORMAL, 
  ATTRIBUTE_TEXTURE0, ATTRIBUTE_TEXTURE1, ATTRIBUTE_TEXTURE2, ATTRIBUTE_TEXTURE3, 
  ATTRIBUTE_LAST
};

/**
 * Load a pair of shaders, compile, and link together. Specify the complete
 * source code text for each shader. Note, there is no support for
 * just loading say a vertex program... you have to do both.
 */
GLuint 
LoadShaderPairSrcWithAttributes(LoggerFuncT &printStatusMessage, 
                                const char *szVertexSrc, 
                                const char *szFragmentSrc, 
                                ...);

#endif // __GLTOOLS_H
