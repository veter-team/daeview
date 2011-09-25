#ifndef __NODE_H
#define __NODE_H

#include <vector>
#include <LinearMath/btAlignedObjectArray.h>
#include <vectormath/vmInclude.h>
#include <LinearMath/btHashMap.h>
#include "Geometry.h"
#include "Light.h"
#include "Camera.h"


using namespace Vectormath::Aos;


struct Transformation
{
  Transformation() : type(Unknown) {}

  enum TransformType {
    Rotate, Translate, Matrix, Scale, LookAt, Skew, Unknown
  };

  TransformType type;
  std::string sid;
  Matrix4 matrix;
  Transform3 transform;
};


struct Node
{
  std::string name;

	Matrix4 local_matrix; /**< Matrix version of just the transforms in this node */
	Matrix4 local_to_world_matrix; /**< Full local to world matrix for this node */
	Matrix4 inverse_local_to_world_matrix;
	Matrix4 inverse_transpose_local_to_world_matrix;

  // Decide to use Boolet's btAlignedObjectArray instead of std::vector
  // because of MSVC's stl issue with alligned elements
  typedef btAlignedObjectArray<Transformation> TransformList;
  typedef std::vector<InstanceGeometry> InstanceGeometries;
  typedef std::vector<InstanceLight> InstanceLights;
  typedef btAlignedObjectArray<InstanceCamera> InstanceCameras;
  //typedef std::vector <InstanceController *> InstanceControllers;
  
  typedef btHashMap<btHashString, Node> NodeMap;

  TransformList transformations;
  InstanceGeometries instance_geometries;
  InstanceLights instance_lights;
  InstanceCameras instance_cameras;
  //InstanceControllerd instance_controllers;
  bool is_font_node;
  Vector3 bbox_max;
  Vector3 bbox_min;

  Node();
  
  void calcBoundingBox(const Geometry::GeometryList &gl);
};


#endif // __NODE_H
