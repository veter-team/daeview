/* Copyright (c) 2010 Andrey Nechypurenko
   See the file LICENSE for copying permission. 
*/

#ifndef __SCENE_H
#define __SCENE_H

#include <dom/domElements.h>
#include <boost/filesystem.hpp>
#include "SceneGraph.h"
using namespace boost;

class DAE;

class Scene
{
 public:
  Scene();
  virtual ~Scene();

 public:
  void load(const filesystem::path &file);
  domUpAxisType getUpAxis() const {return this->up_axis;}
  SceneGraph *getSceneGraph() {return &(this->scene_graph);}

 private:
  bool readNodeTranforms(Node &node, const Node &parent, domNodeRef dom_node);
  bool readImageLibrary(domLibrary_imagesRef lib);
  Geometry::GeometryList::iterator readGeometry(domGeometryRef dom_geometry);
  bool readInstanceGeometry(Node &node, domInstance_geometryRef instance);
  bool readInstanceLight(Node &node, domInstance_lightRef instance);
  bool readInstanceCamera(Node &node, domInstance_cameraRef instance);
  bool readEffectLibrary(domLibrary_effectsRef lib);
  bool readMaterialLibrary(domLibrary_materialsRef lib);
  bool readInstanceMaterial(InstanceGeometry &instance_geometry, domInstance_materialRef dom_instance);
  bool readAnimationLibrary(domLibrary_animationsRef lib);
  SceneGraph::Vertex readNode(domNodeRef node, SceneGraph::Vertex &parent);
  void readScene(domVisual_sceneRef scene);

 private:
  filesystem::path dae_file_name;
  DAE *collada;
  domUpAxisType up_axis;
  SceneGraph scene_graph;
};


#endif // __SCENE_H
