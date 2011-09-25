#include "gltools.h"


//Flip flags
#define FLIP_VERTICAL   1
#define FLIP_HORIZONTAL 2


/**
 * Quick utility function for texture creation 
 */
static size_t power_of_two(size_t input)
{
  size_t value = 1;
  while(value < input)
    value <<= 1;
  return value;
}


/**
 * A 32 bit RGBA pixel.
 */
typedef struct tagColorRGBA {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} tColorRGBA;

/** 
Function is copy/pasted from SDL_gfx.

Internal 32 bit Zoomer with optional anti-aliasing by bilinear interpolation.

Zooms 32 bit RGBA/ABGR 'src' surface to 'dst' surface.
Assumes src and dst surfaces are of 32 bit depth.
Assumes dst surface was allocated with the correct dimensions.

\param src The surface to zoom (input).
\param dst The zoomed surface (output).
\param flipx Flag indicating if the image should be horizontally flipped.
\param flipy Flag indicating if the image should be vertically flipped.
\param smooth Antialiasing flag; set to SMOOTHING_ON to enable.

\return 0 for success or -1 for error.
*/
int 
ZoomSurfaceRGBA(SDL_Surface * src, SDL_Surface * dst, int flipx, int flipy, int smooth)
{
	int x, y, sx, sy, *sax, *say, *csax, *csay, csx, csy, ex, ey, t1, t2, sstep, lx, ly;
	tColorRGBA *c00, *c01, *c10, *c11, *cswap;
	tColorRGBA *sp, *csp, *dp;
	int dgap;

	/*
	* Variable setup 
	*/
	if (smooth) {
		/*
		* For interpolation: assume source dimension is one pixel 
		* smaller to avoid overflow on right and bottom edge.     
		*/
		sx = (int) (65536.0 * (float) (src->w - 1) / (float) dst->w);
		sy = (int) (65536.0 * (float) (src->h - 1) / (float) dst->h);
	} else {
		sx = (int) (65536.0 * (float) src->w / (float) dst->w);
		sy = (int) (65536.0 * (float) src->h / (float) dst->h);
	}

	/*
	* Allocate memory for row increments 
	*/
	if ((sax = (int *) malloc((dst->w + 1) * sizeof(Uint32))) == NULL) {
		return (-1);
	}
	if ((say = (int *) malloc((dst->h + 1) * sizeof(Uint32))) == NULL) {
		free(sax);
		return (-1);
	}

	/*
	* Precalculate row increments 
	*/
	sp = csp = (tColorRGBA *) src->pixels;
	dp = (tColorRGBA *) dst->pixels;

	if (flipx) csp += (src->w-1);
	if (flipy) csp += ((src->pitch/4)*(src->h-1));

	csx = 0;
	csax = sax;
	for (x = 0; x <= dst->w; x++) {
		*csax = csx;
		csax++;
		csx &= 0xffff;
		csx += sx;
	}
	csy = 0;
	csay = say;
	for (y = 0; y <= dst->h; y++) {
		*csay = csy;
		csay++;
		csy &= 0xffff;
		csy += sy;
	}

	dgap = dst->pitch - dst->w * 4;

	/*
	* Switch between interpolating and non-interpolating code 
	*/
	if (smooth) {

		/*
		* Interpolating Zoom 
		*/

		/*
		* Scan destination 
		*/
		csay = say;
		ly = 0;
		for (y = 0; y < dst->h; y++) {
			/*
			* Setup color source pointers 
			*/
			c00 = csp;
			c01 = csp;
			c01++;	    
			c10 = csp;
			c10 += src->pitch/4;
			c11 = c10;
			c11++;
			if (flipx) {
				cswap = c00; c00=c01; c01=cswap;
				cswap = c10; c10=c11; c11=cswap;
			}
			if (flipy) {
				cswap = c00; c00=c10; c10=cswap;
				cswap = c01; c01=c11; c11=cswap;
			}

			csax = sax;
			lx = 0;
			for (x = 0; x < dst->w; x++) {
				/*
				* Draw and interpolate colors 
				*/
				ex = (*csax & 0xffff);
				ey = (*csay & 0xffff);
				t1 = ((((c01->r - c00->r) * ex) >> 16) + c00->r) & 0xff;
				t2 = ((((c11->r - c10->r) * ex) >> 16) + c10->r) & 0xff;
				dp->r = (((t2 - t1) * ey) >> 16) + t1;
				t1 = ((((c01->g - c00->g) * ex) >> 16) + c00->g) & 0xff;
				t2 = ((((c11->g - c10->g) * ex) >> 16) + c10->g) & 0xff;
				dp->g = (((t2 - t1) * ey) >> 16) + t1;
				t1 = ((((c01->b - c00->b) * ex) >> 16) + c00->b) & 0xff;
				t2 = ((((c11->b - c10->b) * ex) >> 16) + c10->b) & 0xff;
				dp->b = (((t2 - t1) * ey) >> 16) + t1;
				t1 = ((((c01->a - c00->a) * ex) >> 16) + c00->a) & 0xff;
				t2 = ((((c11->a - c10->a) * ex) >> 16) + c10->a) & 0xff;
				dp->a = (((t2 - t1) * ey) >> 16) + t1;
				/*
				* Advance source pointers 
				*/
				csax++;
				if (*csax > 0)
				{
					sstep = (*csax >> 16);
					lx += sstep;
					if (flipx) sstep = -sstep;
					if (lx <= src->w)
					{
						c00 += sstep;
						c01 += sstep;
						c10 += sstep;
						c11 += sstep;
					}
				}

				/*
				* Advance destination pointer 
				*/
				dp++;
			}

			/*
			* Advance source pointer 
			*/
			csay++;
			if (*csay > 0)
			{
				sstep = (*csay >> 16);
				ly += sstep;				
				if (flipy) sstep = -sstep;
				if (ly < src->h)
				{
					csp += (sstep * (src->pitch/4));
				}
			}

			/*
			* Advance destination pointers 
			*/
			dp = (tColorRGBA *) ((Uint8 *) dp + dgap);
		}
	} else {

		/*
		* Non-Interpolating Zoom 
		*/
		csay = say;
		for (y = 0; y < dst->h; y++) {
			sp = csp;
			csax = sax;
			for (x = 0; x < dst->w; x++) {
				/*
				* Draw 
				*/
				*dp = *sp;
				/*
				* Advance source pointers 
				*/
				csax++;
				if (*csax > 0)
				{
					sstep = (*csax >> 16);
					if (flipx) sstep = -sstep;
					sp += sstep;
				}
				/*
				* Advance destination pointer 
				*/
				dp++;
			}
			/*
			* Advance source pointer 
			*/
			csay++;
			if (*csay > 0)
			{
				sstep = (*csay >> 16) * (src->pitch/4);
				if (flipy) sstep = -sstep;
				csp += sstep;
			}

			/*
			* Advance destination pointers 
			*/
			dp = (tColorRGBA *) ((Uint8 *) dp + dgap);
		}
	}

	/*
	* Remove temp arrays 
	*/
	free(sax);
	free(say);

	return (0);
}


GLuint  
CreateTexture(SDL_Surface *surface, GLfloat *texcoord, bool should_flip)
{
  GLuint texture;
  int w, h;
  SDL_Surface *image;
  SDL_Rect area;
  Uint32 saved_flags;
  Uint8  saved_alpha;

  /* Use the surface width and height expanded to powers of 2 */
  w = power_of_two(surface->w);
  h = power_of_two(surface->h);
  if(texcoord)
    {
      texcoord[0] = 0.0f;			/* Min X */
      texcoord[1] = 0.0f;			/* Min Y */
      texcoord[2] = (GLfloat)surface->w / w;	/* Max X */
      texcoord[3] = (GLfloat)surface->h / h;	/* Max Y */
    }
  image = SDL_CreateRGBSurface(
			       SDL_SWSURFACE,
			       w, h,
			       32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN // OpenGL RGBA masks
			       0x000000FF, 
			       0x0000FF00, 
			       0x00FF0000, 
			       0xFF000000
#else
			       0xFF000000,
			       0x00FF0000, 
			       0x0000FF00, 
			       0x000000FF
#endif
			       );
  if(image == NULL)
    return 0;

  /* Save the alpha blending attributes */
  saved_flags = surface->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
  saved_alpha = surface->format->alpha;
  if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
    SDL_SetAlpha(surface, 0, SDL_ALPHA_TRANSPARENT);

  /* Copy the surface into the GL texture image */
  SDL_Surface *t = 
    SDL_CreateRGBSurface(SDL_SWSURFACE, 
                         surface->w, surface->h, 
                         image->format->BitsPerPixel, 
                         image->format->Rmask, 
                         image->format->Gmask, 
                         image->format->Bmask, 
                         image->format->Amask);
  if(t == NULL)
    return 0;

  area.x = 0;
  area.y = 0;
  area.w = surface->w;
  area.h = surface->h;
  SDL_BlitSurface(surface, &area, t, &area);

  // If source image size has power of 2 then no scaling
  // will be done. Surface will be flipped if requested.
  bool smooth = (w != surface->w || h != surface->h);
  ZoomSurfaceRGBA(t, image, false, should_flip, smooth);

  SDL_FreeSurface(t);

  /* Restore the alpha blending attributes */
  if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
    SDL_SetAlpha(surface, saved_flags, saved_alpha);

  /* Create an OpenGL texture for the image */
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  /*for(int y = 0; y < h; ++y)
  {
    for(int x = 0; x < w; ++x)
      (((tagColorRGBA*)(image->pixels)) + y * w + x)->a = 0;
  }*/
  glTexImage2D(GL_TEXTURE_2D,
	       0,
	       GL_RGBA,
	       w, h,
	       0,
	       GL_RGBA,
	       GL_UNSIGNED_BYTE,
	       image->pixels);

  GLenum error = glGetError();
  if(error != GL_NO_ERROR)
  {
    glDeleteTextures(1, &texture);
    texture = 0;
  }

  SDL_FreeSurface(image); /* No longer needed */

  return texture; 
}


/**
 * Get the OpenGL version number
 */
void 
GetOpenGLVersion(GLint &nMajor, GLint &nMinor)
{
#ifndef OPENGL_ES       
  glGetIntegerv(GL_MAJOR_VERSION, &nMajor);
  glGetIntegerv(GL_MINOR_VERSION, &nMinor);
#else
  const char *szVersionString = (const char *)glGetString(GL_VERSION);
  if(szVersionString == NULL)
  {
  nMajor = 0;
  nMinor = 0;
  return;
  }
    
  // Get major version number. This stops at the first non numeric character
  nMajor = atoi(szVersionString);
    
  // Get minor version number. Start past the first ".", atoi terminates on first non numeric char.
  nMinor = atoi(strstr(szVersionString, ".")+1);
#endif
}


/**
 * Check for any GL errors that may affect rendering
 * Check the framebuffer, the shader, and general errors
 */
ErrorMessages 
CheckErrors(GLuint progName)
{
  ErrorMessages errors;
  GLenum error = glGetError();
		
  if(error != GL_NO_ERROR)
    errors.push_back("A GL Error has occured");

#ifndef OPENGL_ES
  GLenum fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

  if(fboStatus != GL_FRAMEBUFFER_COMPLETE)
  {
    errors.push_back("The framebuffer is not complete - ");
    switch(fboStatus)
	  {
	  case GL_FRAMEBUFFER_UNDEFINED:
	    // Oops, no window exists?
	    errors.push_back("  GL_FRAMEBUFFER_UNDEFINED");
	    break;
	  case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
	    // Check the status of each attachment
	    errors.push_back("  GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
	    break;
	  case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
	    // Attach at least one buffer to the FBO
	    errors.push_back("  GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
	    break;
	  case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
	    // Check that all attachments enabled via
	    // glDrawBuffers exist in FBO
	    errors.push_back("  GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
	    break;
	  case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
	    // Check that the buffer specified via
	    // glReadBuffer exists in FBO
	    errors.push_back("  GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
	    break;
	  case GL_FRAMEBUFFER_UNSUPPORTED:
	    // Reconsider formats used for attached buffers
	    errors.push_back("  GL_FRAMEBUFFER_UNSUPPORTED");
	    break;
	  case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
	    // Make sure the number of samples for each 
	    // attachment is the same 
	    errors.push_back("  GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
	    break; 
	  case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
	    // Make sure the number of layers for each 
	    // attachment is the same 
	    errors.push_back("  GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
	    break;
	  }
  }

#endif

  if(progName != 0)
    {
      glValidateProgram(progName);
      int iIsProgValid = 0;
      glGetProgramiv(progName, GL_VALIDATE_STATUS, &iIsProgValid);
      if(iIsProgValid == 0)
        errors.push_back("The current program is not valid");
    }
  return errors;
}


/**
 * Load the shader from the source text
 */
void 
LoadShaderSrc(const char *szShaderSrc, GLuint shader)
{
  GLchar *fsStringPtr[1];
  fsStringPtr[0] = (GLchar*)szShaderSrc;
  glShaderSource(shader, 1, (const GLchar**)fsStringPtr, NULL);
}


GLuint 
LoadShaderPairSrcWithAttributes(LoggerFuncT &printStatusMessage, const char *szVertexSrc, 
				const char *szFragmentSrc, 
				...)
{
  char info_log_buff[1024 * 4];
  // Temporary Shader objects
  GLuint hVertexShader;
  GLuint hFragmentShader; 
  GLuint hReturn = 0;   
  GLint testVal;
	
  // Create shader objects
  hVertexShader = glCreateShader(GL_VERTEX_SHADER);
  hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
  // Load them. 
  LoadShaderSrc(szVertexSrc, hVertexShader);
  LoadShaderSrc(szFragmentSrc, hFragmentShader);
   
  // Compile them
  glCompileShader(hVertexShader);
  glGetShaderInfoLog(hVertexShader, sizeof(info_log_buff) - 1, NULL, info_log_buff);
  printStatusMessage("Vertex shader compilation log:");
  printStatusMessage(info_log_buff);

  glCompileShader(hFragmentShader);
  glGetShaderInfoLog(hFragmentShader, sizeof(info_log_buff) - 1, NULL, info_log_buff);
  printStatusMessage("Fragmet shader compilation log:");
  printStatusMessage(info_log_buff);

  // Check for errors
  glGetShaderiv(hVertexShader, GL_COMPILE_STATUS, &testVal);
  if(testVal == GL_FALSE)
    {
      glDeleteShader(hVertexShader);
      glDeleteShader(hFragmentShader);
      return (GLuint)NULL;
    }
    
  glGetShaderiv(hFragmentShader, GL_COMPILE_STATUS, &testVal);
  if(testVal == GL_FALSE)
    {
      glDeleteShader(hVertexShader);
      glDeleteShader(hFragmentShader);
      return (GLuint)NULL;
    }
    
  // Link them - assuming it works...
  hReturn = glCreateProgram();
  glAttachShader(hReturn, hVertexShader);
  glAttachShader(hReturn, hFragmentShader);

  // List of attributes
  va_list attributeList;
  va_start(attributeList, szFragmentSrc);

  char *szNextArg;
  int iArgCount = va_arg(attributeList, int);	// Number of attributes
  for(int i = 0; i < iArgCount; i++)
    {
      int index = va_arg(attributeList, int);
      szNextArg = va_arg(attributeList, char*);
      glBindAttribLocation(hReturn, index, szNextArg);
    }
  va_end(attributeList);


  glLinkProgram(hReturn);
	
  // These are no longer needed
  glDeleteShader(hVertexShader);
  glDeleteShader(hFragmentShader);  
    
  // Make sure link worked too
  glGetProgramiv(hReturn, GL_LINK_STATUS, &testVal);
  if(testVal == GL_FALSE)
    {
      glDeleteProgram(hReturn);
      return (GLuint)NULL;
    }
    
  return hReturn;  
}   
