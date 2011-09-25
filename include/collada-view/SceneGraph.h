#ifndef __SCENEGRAPH_H
#define __SCENEGRAPH_H

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <map>
#include "Node.h"
#include "NodePainter.h"
#include "Animation.h"


using namespace boost;
using namespace Vectormath::Aos;


struct SceneGraph
{
  //struct node_painter_t {typedef vertex_property_tag kind;};

  struct node_info_t {typedef vertex_property_tag kind;};
  struct NodeInfo
  {
    std::string id;
    std::string sid;
  };
  //typedef property<node_painter_t, NodePainter> NodePainterProperty;
  typedef property<node_info_t, NodeInfo/*, NodePainterProperty*/> NodeKeyProperty;
  typedef adjacency_list<vecS, vecS, directedS, NodeKeyProperty> NodeGraph;
  typedef property_map<SceneGraph::NodeGraph, SceneGraph::node_info_t>::type node_id_map_t;
  //typedef property_map<SceneGraph::NodeGraph, SceneGraph::node_painter_t>::type node_painter_map_t;
  typedef graph_traits<NodeGraph>::vertex_descriptor Vertex;
  typedef std::map<std::string, Vertex> IdVertexMap;
  typedef std::vector<std::string> LightNodeRefList;

  NodeGraph node_graph;
  Vertex root;
  Node::NodeMap all_nodes;
  IdVertexMap id_vertex_map;
  Image::ImageList all_images;
  Effect::EffectList all_effects;
  Material::MaterialList all_materials;
  Geometry::GeometryList all_geometries;
  Light::LightList all_lights;
  LightNodeRefList light_nodes;
  Camera::CameraList all_cameras;
  Animation::AnimationList all_animations;
  std::pair<Node*, InstanceCamera*> active_camera_info;
  
  static std::string font_name;

  SceneGraph();
  
  bool insertNode(SceneGraph::Vertex &parent,
                  const std::string &new_node_name,
                  const char *new_node_id,
                  const char *new_node_sid);
  
  LoggerFuncT printStatusMessage;
};


#endif // __SCENEGRAPH_H
