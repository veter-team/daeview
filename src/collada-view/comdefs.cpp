#include "comdefs.h"
#include <memory.h>
#include <iostream>


Color3f::Color3f()
{
  memset(this->rgba, 0, sizeof(this->rgba));
}


Color3f::Color3f(float cr, float cg, float cb)
{
  this->rgba[0] = cr;
  this->rgba[1] = cg;
  this->rgba[2] = cb;
  this->rgba[3] = 0;
}


Color3f::Color3f(const Color3f &c)
{
  memcpy(this->rgba, c.rgba, sizeof(this->rgba));
}


Color3f &
Color3f::operator = (const Color3f &rhs)
{
  memcpy(this->rgba, rhs.rgba, sizeof(this->rgba));
  return *this;
}


Color4f::Color4f() : Color3f()
{
  rgba[3] = 0;
}


Color4f::Color4f(float cr, float cg, float cb, float ca) : Color3f(cr, cg, cb)
{
  this->rgba[3] = ca;
}


Color4f::Color4f(const Color4f &c) : Color3f(c)
{
  this->rgba[3] = c.rgba[3];
}


Color4f &
Color4f::operator = (const Color4f &rhs)
{
  Color3f::operator=(rhs);
  return *this;
}


void 
DefaultLoggerFunc(const std::string &msg)
{
  std::cout << msg << std::endl;
}

