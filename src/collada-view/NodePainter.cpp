#include "gltools.h"
#include "NodePainter.h"
#include "DefaultRenderer.h"


NodePainter::NodePainter(DefaultRenderer *r)
  : renderer(r)
{
}


void 
NodePainter::paint(const Node &node, const Vector3 &light_pos, const Light &light) const
{
  //const Matrix4 &m = this->renderer->root_node->local_to_world_matrix;
  const Matrix4 &m = node.local_to_world_matrix;
  GLfloat mvMatrix[16];
  for(size_t c = 0; c < 4; ++c)
  {
    const Vector4 &col = m.getCol(c);
    for(size_t r = 0; r < 4; ++r)
      mvMatrix[c*4+r] = col[r];
  }

  const Matrix4 &p = this->renderer->projection_matrix;
  GLfloat pMatrix[16];
  for(size_t c = 0; c < 4; ++c)
  {
    const Vector4 &col = p.getCol(c);
    for(size_t r = 0; r < 4; ++r)
      pMatrix[c*4+r] = col[r];
  }

  // Set up the uniforms
  // Just the modelview and the color
  GLuint shader_prog = 0;
  GLint loc = 0;
  
  for(Node::InstanceGeometries::const_iterator i = node.instance_geometries.begin(); 
    i != node.instance_geometries.end(); ++i)
  {
    const DefaultRenderer::GeometryBuffers &gb = this->renderer->geometry_buffers_list.find(i->abstract_geometry_ref)->second;

    // Prepare buffers for drawing
#ifndef OPENGL_ES
    glBindVertexArray(gb.vertexArrayBufferObject);
#else
    // Vertex data
    glBindBuffer(GL_ARRAY_BUFFER, gb.vertex_data_array);
    glEnableVertexAttribArray(ATTRIBUTE_VERTEX);
    glVertexAttribPointer(ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
    // Normal data
    glBindBuffer(GL_ARRAY_BUFFER, gb.normal_data_array);
    glEnableVertexAttribArray(ATTRIBUTE_NORMAL);
    glVertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, gb.texture_data_array);
    glEnableVertexAttribArray(ATTRIBUTE_TEXTURE0);
    glVertexAttribPointer(ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
#endif

    Geometry::GeometryList::const_iterator gi = this->renderer->scene_graph->all_geometries.find(i->abstract_geometry_ref);
    const Geometry &geometry = gi->second;
    Geometry::TrianglesList::const_iterator ti = geometry.triangles_list.begin();
    static const float default_color[4] = {0.99f, 0.5f, 0.5f, 1.0f};
    for(DefaultRenderer::GeometryBuffers::IndexArrays::const_iterator a = gb.index_data_array.begin();
      a != gb.index_data_array.end(); ++a)
    {
      // Setup material
      //
      // I think this place could be optimized to prevent hash table lookup for each draw.
      if(!ti->material.name.empty())
      {
        Material::MaterialList::const_iterator m = this->renderer->scene_graph->all_materials.find(ti->material);
        if(m == this->renderer->scene_graph->all_materials.end())
        {
          for(InstanceGeometry::MaterialInstances::const_iterator mi = i->material_instances.begin();
            mi != i->material_instances.end(); ++mi)
          {
            if(ti->material.name == mi->symbol)
            {
              m = this->renderer->scene_graph->all_materials.find(mi->target_material);
              break;
            }
          }
        }

        if(m == this->renderer->scene_graph->all_materials.end())
        {
          shader_prog = this->renderer->shaders.find(Effect::Constant)->second;
          glUseProgram(shader_prog);
          loc = glGetUniformLocation(shader_prog, "vColor");
          glUniform4fv(loc, 1, default_color);
        }
        else
        {
          const Material &material = m->second;
          const Effect &effect = this->renderer->scene_graph->all_effects.find(material.effect)->second;
          if(!this->renderer->texture_names.empty() && !effect.textures.empty())
          {
            DefaultRenderer::TextureNameMap::const_iterator tex = this->renderer->texture_names.find(effect.textures.front());
            if(tex != this->renderer->texture_names.end())
            {
              glBindTexture(GL_TEXTURE_2D, tex->second);
              shader_prog = this->renderer->shaders.find(Effect::Texture)->second;
              glUseProgram(shader_prog);
              loc = glGetUniformLocation(shader_prog, "vColor");
              glUniform4fv(loc, 1, effect.diffuse.rgba);
            }
            else
            {
              glBindTexture(GL_TEXTURE_2D, 0);
              shader_prog = this->renderer->shaders.find(Effect::Constant)->second;
              glUseProgram(shader_prog);
              loc = glGetUniformLocation(shader_prog, "vColor");
              glUniform4fv(loc, 1, effect.diffuse.rgba);
            }
          }
          else
          {
            glBindTexture(GL_TEXTURE_2D, 0);
            shader_prog = this->renderer->shaders.find(effect.shader_model)->second;
            glUseProgram(shader_prog);
            loc = glGetUniformLocation(shader_prog, "ambientColor");
            glUniform4fv(loc, 1, effect.ambient.rgba);
            loc = glGetUniformLocation(shader_prog, "specularColor");
            glUniform4fv(loc, 1, effect.specular.rgba);
            loc = glGetUniformLocation(shader_prog, "shininess");
            glUniform1f(loc, effect.shininess);
            loc = glGetUniformLocation(shader_prog, "diffuseColor");
            glUniform4fv(loc, 1, effect.diffuse.rgba);
          }
        }
      }
      else
      {
        shader_prog = this->renderer->shaders.find(Effect::Constant)->second;
        glUseProgram(shader_prog);
        loc = glGetUniformLocation(shader_prog, "vColor");
        glUniform4fv(loc, 1, default_color);
      }

      // Set up the uniforms
      loc = glGetUniformLocation(shader_prog, "mvMatrix");
      glUniformMatrix4fv(loc, 1, GL_FALSE, mvMatrix);

      loc = glGetUniformLocation(shader_prog, "pMatrix");
      glUniformMatrix4fv(loc, 1, GL_FALSE, pMatrix);

      loc = glGetUniformLocation(shader_prog, "vLightPos");
      //float light_pos[3] = {light_pos[0], light_pos[1], light_pos[2]};
#if defined (BT_USE_SSE) && defined (_WIN32)
      glUniform3fv(loc, 1, (GLfloat*)&(light_pos.get128()));
#else
      glUniform3fv(loc, 1, (GLfloat*)&light_pos);
#endif
      // only one line source is currently supported
      loc = glGetUniformLocation(shader_prog, "lightColor");
      glUniform4fv(loc, 1, light.color.rgba);

      loc = glGetUniformLocation(shader_prog, "fConstantAttenuation");
      glUniform1f(loc, light.constant_attenuation);
  
      loc = glGetUniformLocation(shader_prog, "fLinearAttenuation");
      glUniform1f(loc, light.linear_attenuation);

      loc = glGetUniformLocation(shader_prog, "fQuadraticAttenuation");
      glUniform1f(loc, light.quadratic_attenuation);

      // Indexes
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a->first);
      // Draw
      glDrawElements(GL_TRIANGLES, a->second, GL_UNSIGNED_INT, 0);

      ++ti;
    }
    // Unbind to anybody
#ifndef OPENGL_ES
    glBindVertexArray(0);
#else
    glDisableVertexAttribArray(ATTRIBUTE_VERTEX);
    glDisableVertexAttribArray(ATTRIBUTE_NORMAL);
    glDisableVertexAttribArray(ATTRIBUTE_TEXTURE0);
#endif
  }
}
