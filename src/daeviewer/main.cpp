/* Copyright (c) 2010 Andrey Nechypurenko
   See the file LICENSE for copying permission. 
*/

#include <GL/glew.h>			// OpenGL Extension "autoloader"

// There are conflicting definitions in SDL_opengl.h
// with glew.h. So prefere glew.h.
#define GL_SGIX_fragment_lighting

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <stdexcept>

#include <collada-view/Scene.h>
#include <collada-view/DefaultRenderer.h>
#include "AbstractCommand.h"
#include "PrintStatusMsg.h"

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  1000
#define SCREEN_HEIGHT 800
#define SCREEN_BPP     16


void 
myInitGL(void)     // Create Some Everyday Functions
{
  glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
  glClearDepth(1.0f);									// Depth Buffer Setup
  glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
  glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do

  glEnable(GL_TEXTURE_2D);            // Enable Texture Mapping
  //glEnable(GL_TEXTURE_RECTANGLE_ARB); // Enable Texture Mapping

  glEnable(GL_MULTISAMPLE);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glCullFace(GL_BACK);
} 


void 
drawScene(DefaultRenderer *renderer)   // Create The Display Function
{
  renderer->render();
  SDL_GL_SwapBuffers(); // Swap the buffers to not be left with a clear screen
}


// The Reshape Function (the viewport)
void 
resizeWindow(DefaultRenderer *renderer, int w, int h)
{
  renderer->setupCamera(w, h);
}


void 
sendUserEvent()
{
  SDL_Event event;
  event.user.type = SDL_USEREVENT;
  event.user.code = 0;
  SDL_PushEvent(&event);
}


/* function to handle key press events */
void 
handleKeyPress(SDL_keysym *keysym, bool *done)
{
  switch(keysym->sym)
    {
    case SDLK_ESCAPE:
      /* Quit the application */
      *done = true;
      break;

    case SDLK_a:
      break;

    case SDLK_d:
      break;

    case SDLK_w:
      break;

    case SDLK_s:
      break;

    default:
      break;
    }

  return;
}


/* function to handle key release events */
void 
handleKeyRelease(SDL_keysym *keysym)
{
  switch(keysym->sym)
    {

    case SDLK_a:
    case SDLK_d:
      break;

    case SDLK_w:
    case SDLK_s:
      break;

    default:
      break;
    }
}


void 
executeCommand(AbstractCommand *cmd)
{
  cmd->execute();
  if(cmd->shouldDelete())
    delete cmd;
}


int  
mainLoop(DefaultRenderer *renderer, int video_flags, SDL_Surface **surface, bool *done)
{
  /* used to collect events */
  SDL_Event event;

  drawScene(renderer);

  /* wait for events */
  while(!(*done))
    {
      /* handle the events in the queue */
      while(!(*done) && SDL_WaitEvent(&event))
        {
          switch(event.type)
            {
            case SDL_VIDEORESIZE:
              /* handle resize event */
              resizeWindow(renderer, event.resize.w, event.resize.h);
              break;

            case SDL_KEYDOWN:
              /* handle key presses */
              handleKeyPress(&event.key.keysym, done);
              drawScene(renderer);
              break;

            case SDL_KEYUP:
              /* handle key releases */
              handleKeyRelease(&event.key.keysym);
              break;

            case SDL_USEREVENT:
              if(event.user.code && event.user.data1)
              {
                executeCommand((AbstractCommand*)event.user.data1);
              }
              //drawScene(renderer);
              break;

            case SDL_QUIT:
              /* handle quit requests */
              *done = true;
              break;

            default:
              drawScene(renderer);
              break;
            }

        }
    }

  /* clean ourselves up and exit */
  SDL_Quit();

  return 0;
}


int 
main(int argc, char *argv[])
{
  int res = 0;
  Scene scene;
  SDL_Surface *surface;
  int video_flags; // Flags to pass to SDL_SetVideoMode
  const SDL_VideoInfo *videoInfo; // this holds some info about our display
  bool done = false;

  if(argc < 2)
    {
      printf("Usage: connectors <obj_file_name>\n");
      return -1;
    }

  /* initialize SDL */
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER) < 0)
    {
      fprintf(stderr, 
              "Video initialization failed: %s\n",
              SDL_GetError());
      SDL_Quit();
      return -2;
    }

  /* Fetch the video info */
  videoInfo = SDL_GetVideoInfo();

  if(!videoInfo)
    {
      fprintf(stderr, 
              "Video query failed: %s\n",
              SDL_GetError( ) );
      SDL_Quit();
      return -3;
    }

  /* the flags to pass to SDL_SetVideoMode */
  video_flags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
  video_flags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
  video_flags |= SDL_HWPALETTE;       /* Store the palette in hardware */
  video_flags |= SDL_RESIZABLE;       /* Enable window resizing */

  /* Sets up OpenGL double buffering */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  // Enable multisampling
  /*
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  */
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  /* get a SDL surface */
  surface = SDL_SetVideoMode(SCREEN_WIDTH, 
                             SCREEN_HEIGHT, 
                             SCREEN_BPP,
                             video_flags);

  /* Verify there is a surface */
  if(!surface)
    {
      fprintf(stderr,
              "Video mode set failed: %s\n",
              SDL_GetError());
      SDL_Quit();
      return -3;
    }

  SDL_WM_SetCaption("Collada viewer", "Collada viewer");

 	

  SDL_version compile_version;
  const SDL_version *link_version = IMG_Linked_Version();
  SDL_IMAGE_VERSION(&compile_version);
  printf("compiled with SDL_image version: %d.%d.%d\n", 
          compile_version.major,
          compile_version.minor,
          compile_version.patch);
  printf("running with SDL_image version: %d.%d.%d\n", 
          link_version->major,
          link_version->minor,
          link_version->patch);

  // load support for the JPG, PNG and TIFF image formats
  const int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
  int initted = IMG_Init(flags);
  if((initted & flags) != flags) {
      fprintf(stderr, "IMG_Init: Failed to init required jpg, png and tiff support!\n");
      fprintf(stderr, "IMG_Init: %s\n", IMG_GetError());
      return -4;
  }

  GLenum err = glewInit();
  if(GLEW_OK != err)
  {
    fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
    return -5;
  }

  /* initialize OpenGL */
  myInitGL(); 
  
  if(argc != 2)
    {
      fprintf(stderr, "Usage: collada-viewer <dae_file_name>\n");
      return 1;
    }

  try
    {
      scene.getSceneGraph()->printStatusMessage = printStatusMessage1;
      scene.load(argv[1]);
      DefaultRenderer renderer(printStatusMessage1);
      renderer.setScene(scene.getSceneGraph());
      /* resize the initial window */
      resizeWindow(&renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
      res = mainLoop(&renderer, video_flags, &surface, &done);
    }
  catch(const std::exception &ex)
    {
      printStatusMessage(ex.what(), NULL);
      res = 101;
    }

  // unload the dynamically loaded image libraries
  IMG_Quit();

  return res;
}
