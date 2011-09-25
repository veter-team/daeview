#ifndef __COMDEFS_H
#define __COMDEFS_H

#include <boost/function.hpp>


#define DEGREES_TO_RADIANS 0.017453292f

struct Color3f
{
  float rgba[4];
  
  Color3f();
  Color3f(float cr, float cg, float cb);
  Color3f(const Color3f &c);
  Color3f &operator = (const Color3f &rhs);
};


struct Color4f : public Color3f
{
  Color4f();
  Color4f(float cr, float cg, float cb, float ca = 0);
  Color4f(const Color4f &c);
  Color4f &operator = (const Color4f &rhs);
};

typedef boost::function<void (const std::string &msg)> LoggerFuncT;

void DefaultLoggerFunc(const std::string &msg);

#endif // __COMDEFS_H
