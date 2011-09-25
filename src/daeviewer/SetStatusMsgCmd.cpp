/* Copyright (c) 2010 Andrey Nechypurenko
   See the file LICENSE for copying permission. 
*/

#include "SetStatusMsgCmd.h"
#include "TxtAreaPainter.h"


SetStatusMsgCmd::SetStatusMsgCmd(TxtAreaPainter *p, const std::string &msg)
  : painter(p),
    message(msg)
{
}


void 
SetStatusMsgCmd::execute()
{
  if(painter)
    painter->addString(this->message);
}
