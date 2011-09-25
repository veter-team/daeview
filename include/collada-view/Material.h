#ifndef __MATERIAL_H
#define __MATERIAL_H

#include <map>
#include <vector>
#include "Texture.h"
#include "comdefs.h"


struct SceneGraph;


struct Effect
{
  enum ShaderModelType
  {
    Constant = 0,
    Lambert = 1,
    Phong = 2,
    Blinn = 3,
    Texture = 4,
    Undefined
  };

  ShaderModelType shader_model;

	Color4f emission;
	Color4f ambient;
	Color4f diffuse;
	Color4f specular;
	float shininess;
	float transparency;

	Color4f reflective;
	Color4f transparent;
	Color4f absorption;
	float reflectivity;
	float refractive_index;
	
  typedef std::vector<Image::ImageID> ImageIDList;
	ImageIDList textures;

  Effect()
    : shader_model(Undefined),
      emission(0, 0, 0, 0),
	    ambient(0, 0, 0, 0),
	    diffuse(0, 0, 0, 0),
	    specular(0, 0, 0, 0),
      shininess(40.0f),
		  transparency(1.0f),
	    reflective(0, 0, 0),
	    transparent(0, 0, 0),
	    absorption(0, 0, 0),
		  reflectivity(0),
		  refractive_index(0)
	{
	} 

  struct EffectID
  {
    std::string name;
    std::string doc_uri;
    bool operator < (const EffectID &rhs) const {return name == rhs.name ? (doc_uri < rhs.doc_uri) : (name < rhs.name);}
  };
  typedef std::map<EffectID, Effect> EffectList;
};

Effect::EffectList::iterator ReadEffect(LoggerFuncT &printStatusMessage, 
                                        SceneGraph *scene_graph, 
                                        domEffectRef dom_effect, 
                                        const filesystem::path &dir);


struct Material
{
  Effect::EffectList::key_type effect;

  struct MaterialID
  {
    std::string name;
    std::string doc_uri;
    bool operator < (const MaterialID &rhs) const {return name == rhs.name ? (doc_uri < rhs.doc_uri) : (name < rhs.name);}
  };
  typedef std::map<MaterialID, Material> MaterialList;
};


struct InstanceMaterial
{
  std::string symbol;
  std::string target;
  Material::MaterialList::key_type target_material;
};

#endif // __MATERIAL_H
