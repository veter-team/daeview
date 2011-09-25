#ifndef __RENDERER_H
#define __RENDERER_H

#include "SceneGraph.h"
#include <SDL.h>
#include <SDL_opengl.h>

class DefaultRenderer
{
 public:
  DefaultRenderer(const LoggerFuncT &logger = DefaultLoggerFunc);
  ~DefaultRenderer();

 public:
  void setScene(SceneGraph *sg);
  void setupCamera(int window_width, int window_height);
  void render();

  SceneGraph *scene_graph;

  typedef std::map<Effect::ShaderModelType, GLuint> ShaderMap;
  ShaderMap shaders;

  typedef std::map<Image::ImageID, GLuint> TextureNameMap;
  TextureNameMap texture_names;
  
  struct GeometryBuffers
  {
    GLuint vertexArrayBufferObject;

    GLuint vertex_data_array;
    GLuint normal_data_array;
    GLuint texture_data_array;
    // list of index_data_array id and index_count pairs
    typedef std::vector< std::pair<GLuint, GLuint> > IndexArrays;
    IndexArrays index_data_array;

    /*
    GLuint polygons_vertex_array;
    GLuint polygons_normal_array;
    GLuint polygons_color_array;

    GLuint triangles_vertex_array;
    GLuint triangles_normal_array;
    GLuint triangles_color_array;

    GLuint lines_vertex_array;
    GLuint lines_color_array;

    GLuint linestrips_vertex_array;
    GLuint linestrips_color_array;

    GLuint tristrips_vertex_array;
    GLuint tristrips_normal_array;
    GLuint tristrips_color_array;

    GLuint trifans_vertex_array;
    GLuint trifans_normal_array;
    GLuint trifans_color_array;
    */
    GeometryBuffers() :
      vertexArrayBufferObject(0),
      vertex_data_array(0),
      normal_data_array(0),
      texture_data_array(0),
      index_data_array(0)/*,

      polygons_vertex_array(0),
      polygons_normal_array(0),
      polygons_color_array(0),

      triangles_vertex_array(0),
      triangles_normal_array(0),
      triangles_color_array(0),

      lines_vertex_array(0),
      lines_color_array(0),

      linestrips_vertex_array(0),
      linestrips_color_array(0),

      tristrips_vertex_array(0),
      tristrips_normal_array(0),
      tristrips_color_array(0),

      trifans_vertex_array(0),
      trifans_normal_array(0),
      trifans_color_array(0)*/
    {
    }
  };

  typedef std::map<Geometry::GeometryID, GeometryBuffers> GeometryBuffersList;
  GeometryBuffersList geometry_buffers_list;

  Node *root_node;
  Matrix4 projection_matrix;

 private:
  void cleanupBufferObjects();

  Matrix4 perspective_matrix;
  Node *light_node;
  Light::LightList::const_iterator light_iter;
  LoggerFuncT printStatusMessage;
};

void UpdateLocalMatricies(Node::NodeMap &all_nodes, 
                          const Animation::NodeIdSet &touched_nodes);

#endif // __RENDERER_H
