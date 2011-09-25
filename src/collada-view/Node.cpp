#include "Node.h"


Node::Node()
  : local_matrix(Matrix4::identity()),
  bbox_max(0,0,0),
  bbox_min(0,0,0)
{
}


void 
Node::calcBoundingBox(const Geometry::GeometryList &gl)
{
  this->bbox_max = Vector3(0,0,0);
  this->bbox_min = Vector3(0,0,0);

  for(InstanceGeometries::const_iterator g = this->instance_geometries.begin();
    g != this->instance_geometries.end(); ++g)
  {
    Geometry::GeometryList::const_iterator ag = gl.find(g->abstract_geometry_ref);
    if(ag == gl.end())
      continue;
    // Points are stored as x/y/z tripples within this array
    for(Geometry::PointList::const_iterator p = ag->second.points.begin();
      p != ag->second.points.end(); ++p)
    {
      float f = *p;
      // X
      if(*p > this->bbox_max.getX())
        this->bbox_max.setX(*p);
      else if(*p < this->bbox_min.getX())
        this->bbox_min.setX(*p);
      // Y
      ++p;
      f = *p;
      if(*p > this->bbox_max.getY())
        this->bbox_max.setY(*p);
      else if(*p < this->bbox_min.getY())
        this->bbox_min.setY(*p);
      // Z
      ++p;
      f = *p;
      if(*p > this->bbox_max.getZ())
        this->bbox_max.setZ(*p);
      else if(*p < this->bbox_min.getZ())
        this->bbox_min.setZ(*p);
    }
  }
}
