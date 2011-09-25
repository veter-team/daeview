#include "PrintStatusMsg.h"
#include "SetStatusMsgCmd.h"
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include <iostream>
#include <SDL.h>


void 
printStatusMessage(const std::string &msg, TxtAreaPainter *painter)
{
#ifdef WIN32
  OutputDebugString(msg.c_str());
  OutputDebugString("\n");
#endif

  std::cout << msg << std::endl;

  SetStatusMsgCmd *cmd = new SetStatusMsgCmd(painter, msg);

  // Trigger repaint
  SDL_Event event;
  event.type = SDL_USEREVENT;
  event.user.code = 1;
  event.user.data1 = cmd;
  event.user.data2 = 0;
  SDL_PushEvent(&event);  
}

void 
printStatusMessage1(const std::string &msg)
{
  printStatusMessage(msg, NULL);
}
