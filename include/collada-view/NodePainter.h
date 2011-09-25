#ifndef __NODEPAINTER_H
#define __NODEPAINTER_H

#include "Node.h"


class DefaultRenderer;

class NodePainter
{
 public:
  NodePainter(DefaultRenderer *r);

 public:
  void paint(const Node &node, const Vector3 &light_pos, const Light &light) const;

 private:
   DefaultRenderer *renderer;
};


#endif // __NODEPAINTER_H
