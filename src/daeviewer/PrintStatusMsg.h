/* Copyright (c) 2010 Andrey Nechypurenko
   See the file LICENSE for copying permission. 
*/

#ifndef __PRINTSTATUSMSG_H
#define __PRINTSTATUSMSG_H

#include <string>

class TxtAreaPainter;

void printStatusMessage(const std::string &msg, TxtAreaPainter *painter);
void printStatusMessage1(const std::string &msg);


#endif // __PRINTSTATUSMSG_H
