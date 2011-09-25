/* Copyright (c) 2010 Andrey Nechypurenko
   See the file LICENSE for copying permission. 
*/

#ifndef __SETSTATUSMSGCMD_H
#define __SETSTATUSMSGCMD_H

#include "AbstractCommand.h"
#include <string>

class TxtAreaPainter;


class SetStatusMsgCmd : public AbstractCommand
{
 public:
  SetStatusMsgCmd(TxtAreaPainter *p, const std::string &msg);

 public:
  virtual void execute();

 private:
  TxtAreaPainter *painter;
  std::string message;
};

#endif // __SETSTATUSMSGCMD_H
