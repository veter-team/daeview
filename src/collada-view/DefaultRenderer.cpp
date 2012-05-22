#include <stdexcept>
#include <sstream>
#include <boost/graph/depth_first_search.hpp>
#include <list>
#include "gltools.h"
#include "DefaultRenderer.h"
#include "NodePainter.h"
#include "Shaders.h"


class lwmatrix_update_visitor : public default_dfs_visitor
{
 public:
  lwmatrix_update_visitor(SceneGraph *sg) 
    : scene_graph(sg),
      node_id_map(get(SceneGraph::node_info_t(), scene_graph->node_graph))
  {
  }


  ~lwmatrix_update_visitor()
  {
    assert(this->parent_stack.empty());
  }
  

  template<typename Vertex, typename Graph> 
  void discover_vertex(Vertex u, const Graph & g)
  {
    SceneGraph::NodeInfo &n = this->node_id_map[u];

    Node *node = this->scene_graph->all_nodes.find(n.id.c_str());
    assert(node);
    Node *parent = NULL;
    if(!this->parent_stack.empty())
    {
      parent = this->scene_graph->all_nodes.find(this->parent_stack.back().c_str());
      assert(parent);
    }

    if(parent)
      node->local_to_world_matrix = parent->local_to_world_matrix * node->local_matrix;
    else
      node->local_to_world_matrix = node->local_matrix;

    node->inverse_local_to_world_matrix = inverse(node->local_to_world_matrix);
    node->inverse_transpose_local_to_world_matrix = transpose(node->inverse_local_to_world_matrix);

    this->parent_stack.push_back(n.id);
  }
  

  template<typename Vertex, typename Graph>
  void finish_vertex(Vertex u, const Graph & g)
  {
    this->parent_stack.pop_back();
  }

private:
  SceneGraph *scene_graph;
  typedef property_map<SceneGraph::NodeGraph, SceneGraph::node_info_t>::type node_id_map_t;
  node_id_map_t node_id_map;
  typedef std::list<std::string> IdStack;
  IdStack parent_stack;
};


void 
BuildLWMatrix(SceneGraph *scene_graph)
{
  lwmatrix_update_visitor vis(scene_graph);
  depth_first_search(scene_graph->node_graph, visitor(vis));
}


DefaultRenderer::DefaultRenderer(const LoggerFuncT &logger)
  : scene_graph(NULL),
  root_node(NULL), 
  projection_matrix(Matrix4::identity()),
  perspective_matrix(Matrix4::identity()),
  light_node(NULL),
  printStatusMessage(logger)
{
  GLint vMajor = 0;
  GLint vMinor = 0;
  GetOpenGLVersion(vMajor, vMinor);
  std::ostringstream os;
  os << "Running with OpenGL version " << vMajor << "." << vMinor;
  os << std::ends;
  this->printStatusMessage(os.str());

  GLuint shader_prog = 
    LoadShaderPairSrcWithAttributes(this->printStatusMessage,
                                    pointLightDiff.first, 
                                    pointLightDiff.second, 
                                    2, 
                                    ATTRIBUTE_VERTEX, "vVertex", 
                                    ATTRIBUTE_NORMAL, "vNormal");

  ErrorMessages errors = CheckErrors(shader_prog);
  
  for(ErrorMessages::const_iterator error_iter = errors.begin(); error_iter != errors.end(); ++error_iter)
    this->printStatusMessage(*error_iter);

  if(shader_prog == 0)
    throw std::runtime_error("Error loading shaders. See output for more details.");

  this->shaders.insert(std::make_pair(Effect::Constant, shader_prog));

  shader_prog = 
    LoadShaderPairSrcWithAttributes(this->printStatusMessage,
                                    ADSGouraud.first, 
                                    ADSGouraud.second, 
                                    2, 
                                    ATTRIBUTE_VERTEX, "vVertex", 
                                    ATTRIBUTE_NORMAL, "vNormal");

  errors = CheckErrors(shader_prog);
  
  for(ErrorMessages::const_iterator error_iter = errors.begin(); error_iter != errors.end(); ++error_iter)
    this->printStatusMessage(*error_iter);

  if(shader_prog == 0)
    throw std::runtime_error("Error loading shaders. See output for more details.");

  this->shaders.insert(std::make_pair(Effect::Lambert, shader_prog));

  shader_prog = 
    LoadShaderPairSrcWithAttributes(this->printStatusMessage,
                                    ADSPhong.first, 
                                    ADSPhong.second, 
                                    2, 
                                    ATTRIBUTE_VERTEX, "vVertex", 
                                    ATTRIBUTE_NORMAL, "vNormal");

  errors = CheckErrors(shader_prog);
  
  for(ErrorMessages::const_iterator error_iter = errors.begin(); error_iter != errors.end(); ++error_iter)
    this->printStatusMessage(*error_iter);

  if(shader_prog == 0)
    throw std::runtime_error("Error loading shaders. See output for more details.");

  this->shaders.insert(std::make_pair(Effect::Phong, shader_prog));
  this->shaders.insert(std::make_pair(Effect::Blinn, shader_prog));

  shader_prog = 
    LoadShaderPairSrcWithAttributes(this->printStatusMessage,
                                    texturePointLightDiff.first, 
                                    texturePointLightDiff.second, 
                                    3,
                                    ATTRIBUTE_VERTEX, "vVertex", 
                                    ATTRIBUTE_NORMAL, "vNormal", 
                                    ATTRIBUTE_TEXTURE0, "vTexCoord0");

  errors = CheckErrors(shader_prog);
  
  for(ErrorMessages::const_iterator error_iter = errors.begin(); error_iter != errors.end(); ++error_iter)
    this->printStatusMessage(*error_iter);
  
  if(shader_prog == 0)
    throw std::runtime_error("Error loading shaders. See output for more details.");

  this->shaders.insert(std::make_pair(Effect::Texture, shader_prog));

  this->printStatusMessage("Shaders loaded and initialized");
}


void 
DefaultRenderer::cleanupBufferObjects()
{
  // Vertex buffer objects
  for(GeometryBuffersList::const_iterator i = this->geometry_buffers_list.begin();
    i != this->geometry_buffers_list.end(); ++i)
  {
    const GeometryBuffers &gb = i->second;

    glDeleteBuffers(1, &(gb.vertex_data_array));
    glDeleteBuffers(1, &(gb.normal_data_array));
    glDeleteBuffers(1, &(gb.texture_data_array));
    for(GeometryBuffers::IndexArrays::const_iterator i = gb.index_data_array.begin();
      i != gb.index_data_array.end(); ++i)
      glDeleteBuffers(1, &(i->first));
    /*
    glDeleteBuffers(1, &(gb.polygons_vertex_array));
    glDeleteBuffers(1, &(gb.polygons_normal_array));
    glDeleteBuffers(1, &(gb.polygons_color_array));

    glDeleteBuffers(1, &(gb.triangles_vertex_array));
    glDeleteBuffers(1, &(gb.triangles_normal_array));
    glDeleteBuffers(1, &(gb.triangles_color_array));

    glDeleteBuffers(1, &(gb.lines_vertex_array));
    glDeleteBuffers(1, &(gb.lines_color_array));

    glDeleteBuffers(1, &(gb.linestrips_vertex_array));
    glDeleteBuffers(1, &(gb.linestrips_color_array));

    glDeleteBuffers(1, &(gb.tristrips_vertex_array));
    glDeleteBuffers(1, &(gb.tristrips_normal_array));
    glDeleteBuffers(1, &(gb.tristrips_color_array));

    glDeleteBuffers(1, &(gb.trifans_vertex_array));
    glDeleteBuffers(1, &(gb.trifans_normal_array));
    glDeleteBuffers(1, &(gb.trifans_color_array));
    */
#ifndef OPENGL_ES
    glDeleteVertexArrays(1, &(gb.vertexArrayBufferObject));
#endif
  }
  this->geometry_buffers_list.clear();

  for(TextureNameMap::const_iterator tn = this->texture_names.begin();
    tn != this->texture_names.end(); ++tn)
  {
    glDeleteTextures(1, &(tn->second));
  }
  this->texture_names.clear();
}


DefaultRenderer::~DefaultRenderer()
{
  this->cleanupBufferObjects();
}


void 
DefaultRenderer::setScene(SceneGraph *sg)
{
  this->cleanupBufferObjects();

  this->scene_graph = sg;

  // Build local-to-world and related matricies
  BuildLWMatrix(this->scene_graph);

  SceneGraph::node_id_map_t node_id_map(get(SceneGraph::node_info_t(), this->scene_graph->node_graph));
  const SceneGraph::NodeInfo &n = node_id_map[this->scene_graph->root];
  this->root_node = this->scene_graph->all_nodes.find(n.id.c_str());
  assert(this->root_node);

  // Walk through all geometry objects and build corresponding GL buffer objects
  for(Geometry::GeometryList::const_iterator i = this->scene_graph->all_geometries.begin();
    i != this->scene_graph->all_geometries.end(); ++i)
  {
    const Geometry::GeometryID &gid = i->first;
    const Geometry &g = i->second;
    GeometryBuffers gb;

#ifndef OPENGL_ES
    // Create the master vertex array object
    glGenVertexArrays(1, &(gb.vertexArrayBufferObject));
    glBindVertexArray(gb.vertexArrayBufferObject);
#endif

    // Copy data to video memory
    if(!g.points.empty())
    {// Vertex data
      glGenBuffers(1, &(gb.vertex_data_array));
      glBindBuffer(GL_ARRAY_BUFFER, gb.vertex_data_array);
      glEnableVertexAttribArray(ATTRIBUTE_VERTEX);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * g.points.size(), &(g.points[0]), GL_STATIC_DRAW);
      glVertexAttribPointer(ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if(!g.normals.empty())
    {// Normal data
      glGenBuffers(1, &(gb.normal_data_array));
      glBindBuffer(GL_ARRAY_BUFFER, gb.normal_data_array);
      glEnableVertexAttribArray(ATTRIBUTE_NORMAL);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * g.normals.size(), &(g.normals[0]), GL_STATIC_DRAW);
      glVertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if(!g.tex_coords[0].empty())
    {// Texture coordinates
      glGenBuffers(1, &(gb.texture_data_array));
      glBindBuffer(GL_ARRAY_BUFFER, gb.texture_data_array);
      glEnableVertexAttribArray(ATTRIBUTE_TEXTURE0);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * g.tex_coords[0].size(), &(g.tex_coords[0][0]), GL_STATIC_DRAW);
      glVertexAttribPointer(ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    // Indexes
    for(Geometry::TrianglesList::const_iterator t = g.triangles_list.begin(); t != g.triangles_list.end(); ++t)
    {
      GLuint index_data_array;
      glGenBuffers(1, &index_data_array);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_data_array);
      const PolyGroup::IndexVector &iv = t->index_vector.front();
      if(!iv.empty())
      {
        GLuint index_count = iv.size();
        gb.index_data_array.push_back(std::make_pair(index_data_array, index_count));
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PolyGroup::IndexVector::value_type) * index_count, &(iv[0]), GL_STATIC_DRAW);
      }
      else
        glDeleteBuffers(1, &index_data_array);
    }

    // Done
#ifndef OPENGL_ES
    glBindVertexArray(0);
#endif
    this->geometry_buffers_list.insert(std::make_pair(gid, gb));
  }

  // Create textures for all effects
  for(Effect::EffectList::const_iterator e = this->scene_graph->all_effects.begin();
    e != this->scene_graph->all_effects.end(); ++e)
  {
    const Effect &effect = e->second;
    for(Effect::ImageIDList::const_iterator id = effect.textures.begin();
      id != effect.textures.end(); ++id)
    {
      const Image::ImageID &img_id = *id;
      Image::ImageList::iterator img = this->scene_graph->all_images.find(img_id);
      if(img != this->scene_graph->all_images.end())
      {
        GLuint texid = CreateTexture(img->second.image, NULL, img->second.should_flip);
        this->texture_names.insert(std::make_pair(img_id, texid));
      }
    }
  }

  // Get light information.
  // Only one light source is currently supported.
  this->light_node = this->scene_graph->all_nodes.find(this->scene_graph->light_nodes.front().c_str());
  assert(light_node);
  this->light_iter = this->scene_graph->all_lights.find(light_node->instance_lights.front().abstract_light_ref);
  assert(this->light_iter != this->scene_graph->all_lights.end());
}


void 
DefaultRenderer::setupCamera(int window_width, int window_height)
{
  if(this->scene_graph == NULL)
    return;

  Node *node;
  InstanceCamera *inst;
  tie(node, inst) = this->scene_graph->active_camera_info;
	if(inst == NULL || node == NULL)
    return;

	// Recalculate the aspect in case the window size has changed.

  Camera::CameraList::const_iterator ac = this->scene_graph->all_cameras.find(inst->abstract_camera_ref);
  assert(ac != this->scene_graph->all_cameras.end());
  const Camera &abstract_camera = ac->second;

	float aspect;
	if(window_width > 0 && window_height > 0)
  {
		// If the window size is set, make the aspect ratio match it
		aspect = (float)window_width / (float)window_height;
    glViewport(0, 0, window_width, window_height); 
  }
	else if(abstract_camera.aspect > 0.0)
		// No window size set, use the aspect ratio from the camera
		aspect = abstract_camera.aspect;
	else // Otherwise default to 16 by 9 (HDTV)
		aspect = 16.0f / 9.0f;

  this->perspective_matrix = Matrix4::perspective(abstract_camera.Xfov, aspect, abstract_camera.ZNear, abstract_camera.ZFar);
}


void 
UpdateLocalMatricies(Node::NodeMap &all_nodes, const Animation::NodeIdSet &touched_nodes)
{
  // Update local matricies
  for(Animation::NodeIdSet::const_iterator n = touched_nodes.begin();
    n != touched_nodes.end(); ++n)
  {
    Node *node = all_nodes.find(n->c_str());
    node->local_matrix = Matrix4::identity();
    for(int i = 0; i < node->transformations.size(); ++i)
    {
      switch(node->transformations[i].type)
      {
      case Transformation::Rotate:
      case Transformation::Translate:
      case Transformation::Scale:
        node->local_matrix *= node->transformations[i].transform;
        break;

      case Transformation::Matrix:
      case Transformation::LookAt:
        node->local_matrix *= node->transformations[i].matrix;
        break;

      case Transformation::Skew:
      case Transformation::Unknown:
        break;
      }
    }
  }
}


void 
DefaultRenderer::render()
{
  if(this->scene_graph == NULL)
    return;
  /*
  static float time = 0.0f;
  time += 0.1f;
  Animation::NodeIdSet touched_nodes;
  for(Animation::AnimationList::iterator a = this->scene_graph->all_animations.begin();
    a != this->scene_graph->all_animations.end(); ++a)
  {
    a->second.animate(this->scene_graph->printStatusMessage,
                      this->scene_graph->all_nodes, 
                      time, 
                      touched_nodes);
  }
  if(touched_nodes.empty())
    time = 0.0f;
  else
    UpdateLocalMatricies(this->scene_graph->all_nodes, touched_nodes);
  */
  Node *camera_node = this->scene_graph->active_camera_info.first;

  //static Vector3 v;
  //v[0] = 0.2f;
  //v[1] += 0.1f;
  //v[2] += -0.02f;

  // Reuild local-to-world and related matricies
  BuildLWMatrix(this->scene_graph);
  this->projection_matrix = this->perspective_matrix * camera_node->inverse_local_to_world_matrix;
  //this->projection_matrix *= Transform3::rotationZYX(v);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  NodePainter node_painter(this);

  for(int i = 0; i < this->scene_graph->all_nodes.size(); ++i)
  {
    Node *node = this->scene_graph->all_nodes.getAtIndex(i);
    if(!node->is_font_node)
      node_painter.paint(*node, 
                         this->light_node->local_to_world_matrix.getTranslation(),
                         this->light_iter->second);
  }

  static const char *hello_world = "Hello, World!";
  Vector3 t(-1.0f, 1.0f, 3.0f);
  Transform3 text_transform = Transform3::translation(t);
  char buff[8];
  for(const char *c = hello_world; *c; ++c)
  {
    sprintf(buff, "%i", int(*c));
    Node *node = this->scene_graph->all_nodes.find((SceneGraph::font_name + buff).c_str());
    if(node)
    {
      Matrix4 l2w = node->local_to_world_matrix;
      node->local_to_world_matrix *= text_transform;
      node_painter.paint(*node, 
                         this->light_node->local_to_world_matrix.getTranslation(),
                         this->light_iter->second);
      node->local_to_world_matrix = l2w;
      t.setX(t.getX() + (node->bbox_max.getX() - node->bbox_min.getX()) * 1.1f);
      text_transform = Transform3::translation(t);
    }
  }
}
