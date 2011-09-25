#include "SceneGraph.h"

std::string SceneGraph::font_name = "Font1_";


SceneGraph::SceneGraph() 
  : active_camera_info(std::make_pair((Node*)NULL, (InstanceCamera*)NULL)),
  printStatusMessage(DefaultLoggerFunc)
{
}


bool  
SceneGraph::insertNode(SceneGraph::Vertex &parent,
                       const std::string &new_node_name,
                       const char *new_node_id,
                       const char *new_node_sid)
{
  bool inserted = false;
  SceneGraph::Vertex node_vertex;
  SceneGraph::IdVertexMap::iterator pos;
  typedef property_map<SceneGraph::NodeGraph, SceneGraph::node_info_t>::type node_id_map_t;
  node_id_map_t node_id_map = get(SceneGraph::node_info_t(), this->node_graph);

  // insert new node
  tie(pos, inserted) = this->id_vertex_map.insert(std::make_pair(new_node_id, SceneGraph::Vertex()));
  if(inserted)
  {
    node_vertex = add_vertex(this->node_graph);
    SceneGraph::NodeInfo &n = node_id_map[node_vertex];
    n.id = new_node_id;
    n.sid = new_node_sid;
    pos->second = node_vertex;
    this->all_nodes.insert(new_node_id, Node());
    this->all_nodes.find(new_node_id)->name = new_node_name;
  } else
    node_vertex = pos->second;
  
  // Connect to parent
  graph_traits<SceneGraph::NodeGraph>::edge_descriptor e;
  tie(e, inserted) = add_edge(parent, node_vertex, this->node_graph);
  
  return inserted;
}
