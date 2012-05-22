#include "Scene.h"
#include <map>
#include <dae.h>
#include <dom/domCOLLADA.h>
#include <dom/domAsset.h>
#include <dom/domProfile_COMMON.h>
#include <dom/domCommon_color_or_texture_type.h>
#include "SceneGraph.h"


typedef std::map<std::string, domCommon_newparam_type*> NewParamMap;

struct ShaderElements
{
	ShaderElements() 
  : emission(NULL), ambient(NULL), diffuse(NULL), specular(NULL), 
    shininess(NULL), reflective(NULL), reflectivity(NULL), 
    transparent(NULL), transarency(NULL), index_of_refaction(NULL) {}

  domCommon_color_or_texture_type *emission;
	domCommon_color_or_texture_type *ambient;
	domCommon_color_or_texture_type *diffuse;
	domCommon_color_or_texture_type *specular;
	domCommon_float_or_param_type *shininess;

	domCommon_color_or_texture_type *reflective;
	domCommon_float_or_param_type *reflectivity;
	domCommon_color_or_texture_type_complexType *transparent;
	domCommon_float_or_param_type *transarency;
	domCommon_float_or_param_type *index_of_refaction;
}; 


float 
ReadFloatOrParamType(domCommon_float_or_param_typeRef float_or_param)
{
	if(float_or_param->getFloat())
	{
		return (float)float_or_param->getFloat()->getValue();
	}
	return 0;
}


Color4f 
ReadColorOrTextureType(domCommon_color_or_texture_type_complexType *color_or_texture)
{
	if(color_or_texture->getColor())
	{
		domFx_color_common &color = color_or_texture->getColor()->getValue();
		return Color4f((float)color[0], (float)color[1], (float)color[2], (float)color[3]);
	}
	return Color4f();
}


void 
ReadConstant(Effect &effect, ShaderElements &shader, domProfile_COMMON::domTechnique::domConstant *constant)
{
	shader.emission = constant->getEmission();
	if(shader.emission)
		effect.emission = ReadColorOrTextureType(shader.emission);
	
  shader.reflective = constant->getReflective();
	if(shader.reflective)
		effect.reflective = ReadColorOrTextureType(shader.reflective);

	shader.reflectivity = constant->getReflectivity();
	if(shader.reflectivity)
		effect.reflectivity = ReadFloatOrParamType(shader.reflectivity);

	shader.transparent = constant->getTransparent();
	if(shader.transparent)
		effect.transparent = ReadColorOrTextureType(shader.transparent);

	shader.transarency = constant->getTransparency();
	if(shader.transarency)
		effect.transparency = ReadFloatOrParamType(shader.transarency);

	shader.index_of_refaction = constant->getIndex_of_refraction();
	if(shader.index_of_refaction)
		effect.refractive_index = ReadFloatOrParamType(shader.index_of_refaction);
}


void 
ReadLambert(Effect &effect, ShaderElements &shader, domProfile_COMMON::domTechnique::domLambert *lambert)
{
	shader.emission = lambert->getEmission();
	if(shader.emission)
		effect.emission = ReadColorOrTextureType(shader.emission);

	shader.ambient = lambert->getAmbient();
	if(shader.ambient )
		effect.ambient = ReadColorOrTextureType(shader.ambient);

	shader.diffuse = lambert->getDiffuse();
	if(shader.diffuse)
		effect.diffuse = ReadColorOrTextureType(shader.diffuse);

	shader.reflective = lambert->getReflective();
	if(shader.reflective)
		effect.reflective = ReadColorOrTextureType(shader.reflective);

	shader.reflectivity = lambert->getReflectivity();
	if(shader.reflectivity)
		effect.reflectivity = ReadFloatOrParamType(shader.reflectivity);

	shader.transparent = lambert->getTransparent();
	if(shader.transparent)
		effect.transparent = ReadColorOrTextureType(shader.transparent);

	shader.transarency = lambert->getTransparency();
	if(shader.transarency)
		effect.transparency = ReadFloatOrParamType(shader.transarency);

	shader.index_of_refaction = lambert->getIndex_of_refraction();
	if(shader.index_of_refaction)
		effect.refractive_index = ReadFloatOrParamType(shader.index_of_refaction);

}


void 
ReadPhong(Effect &effect, ShaderElements &shader, domProfile_COMMON::domTechnique::domPhong *phong)
{
	shader.emission = phong->getEmission();
	if(shader.emission)
		effect.emission = ReadColorOrTextureType(shader.emission);

	shader.ambient = phong->getAmbient();
	if(shader.ambient )
		effect.ambient = ReadColorOrTextureType(shader.ambient);

	shader.diffuse = phong->getDiffuse();
	if(shader.diffuse)
		effect.diffuse = ReadColorOrTextureType(shader.diffuse);

	shader.specular = phong->getSpecular();
	if(shader.specular)
		effect.specular = ReadColorOrTextureType(shader.specular);

	shader.shininess = phong->getShininess();
	if(shader.shininess)
		effect.shininess = ReadFloatOrParamType(shader.shininess);

	shader.reflective = phong->getReflective();
	if(shader.reflective)
		effect.reflective = ReadColorOrTextureType(shader.reflective);

	shader.reflectivity = phong->getReflectivity();
	if(shader.reflectivity)
		effect.reflectivity = ReadFloatOrParamType(shader.reflectivity);

	shader.transparent = phong->getTransparent();
	if(shader.transparent)
		effect.transparent = ReadColorOrTextureType(shader.transparent);

	shader.transarency = phong->getTransparency();
	if(shader.transarency)
		effect.transparency = ReadFloatOrParamType(shader.transarency);

	shader.index_of_refaction = phong->getIndex_of_refraction();
	if(shader.index_of_refaction)
		effect.refractive_index = ReadFloatOrParamType(shader.index_of_refaction);
}


void 
ReadBlinn(Effect &effect, ShaderElements &shader, domProfile_COMMON::domTechnique::domBlinn *blinn)
{
	shader.emission = blinn->getEmission();
	if(shader.emission)
		effect.emission = ReadColorOrTextureType(shader.emission);

	shader.ambient = blinn->getAmbient();
	if(shader.ambient)
		effect.ambient = ReadColorOrTextureType(shader.ambient);

	shader.diffuse = blinn->getDiffuse();
	if(shader.diffuse)
		effect.diffuse = ReadColorOrTextureType(shader.diffuse);

	shader.specular = blinn->getSpecular();
	if(shader.specular)
		effect.specular = ReadColorOrTextureType(shader.specular);

	shader.shininess = blinn->getShininess();
	if(shader.shininess)
		effect.shininess = ReadFloatOrParamType(shader.shininess);

	shader.reflective = blinn->getReflective();
	if(shader.reflective)
		effect.reflective = ReadColorOrTextureType(shader.reflective);

	shader.reflectivity = blinn->getReflectivity();
	if(shader.reflectivity)
		effect.reflectivity = ReadFloatOrParamType(shader.reflectivity);

	shader.transparent = blinn->getTransparent();
	if(shader.transparent)
		effect.transparent = ReadColorOrTextureType(shader.transparent);

	shader.transarency = blinn->getTransparency();
	if(shader.transarency)
		effect.transparency = ReadFloatOrParamType(shader.transarency);

	shader.index_of_refaction = blinn->getIndex_of_refraction();
	if(shader.index_of_refaction)
		effect.refractive_index = ReadFloatOrParamType(shader.index_of_refaction);
}


// Get diffuse texture name
Image::ImageList::iterator 
GetTextureFromShader(LoggerFuncT &printStatusMessage, 
                     Image::ImageList &all_images, 
                     const NewParamMap &new_params, 
                     domCommon_color_or_texture_type *shader,
                     const filesystem::path &dir)
{
	if(shader == NULL)
    return all_images.end();
	domCommon_color_or_texture_type::domTexture *texture_element = shader->getTexture();
	if(texture_element == NULL)
    return all_images.end();

	std::string sampler2D_SID = texture_element->getTexture();
  NewParamMap::const_iterator i = new_params.find(sampler2D_SID);
	if(i == new_params.end())
	{
		xsIDREF idref(sampler2D_SID.c_str());
		idref.setContainer(shader);
		idref.resolveElement();
		domImage *image_element = (domImage*)(domElement*)idref.getElement();
		return ReadImage(printStatusMessage, all_images, image_element, dir);
	}
	std::string surface_SID = i->second->getSampler2D()->getSource()->getValue();

  i = new_params.find(surface_SID);
	if (i == new_params.end() 
    || i->second->getSurface()->getFx_surface_init_common() == NULL)
		return all_images.end();

	xsIDREF& idRef = i->second->getSurface()->getFx_surface_init_common()->getInit_from_array()[0]->getValue();
	idRef.resolveElement();
	domImage *image_element = (domImage*)(domElement*)idRef.getElement();;
	return ReadImage(printStatusMessage, all_images, image_element, dir);
}


Effect::EffectList::iterator
ReadEffect(LoggerFuncT &printStatusMessage, 
           SceneGraph *scene_graph, 
           domEffectRef dom_effect, 
           const filesystem::path &dir)
{
  size_t i;

  xsID gid = dom_effect->getId();
	if(gid == NULL) 
    return scene_graph->all_effects.end();

  const Effect::EffectID effect_key = 
    {gid, dom_effect->getDocumentURI()->getURI()};
  Effect::EffectList::iterator effect = scene_graph->all_effects.find(effect_key);
	if(effect != scene_graph->all_effects.end()) // effect is found
		return effect;

	printStatusMessage(std::string("  add new Effect ") + gid);

	// Get a pointer to the effect element
	const domEffect *effect_element = dom_effect.cast(); 

	if(!effect_element)
    return scene_graph->all_effects.end();

  bool inserted;
	tie(effect, inserted) = scene_graph->all_effects.insert(std::make_pair(effect_key, Effect()));

  const domImage_Array &ia = effect_element->getImage_array();
	for(size_t i = 0; i < ia.getCount(); ++i)
  {
		Image::ImageList::iterator img = ReadImage(printStatusMessage, scene_graph->all_images, ia[i], dir);
    if(img != scene_graph->all_images.end())
      effect->second.textures.push_back(img->first);
  }
		
	// How many profiles are there
  const domFx_profile_abstract_Array &fp = effect_element->getFx_profile_abstract_array();
	size_t numProfiles = fp.getCount(); 

	// Scan the profiles to find the profile_COMMON
	for(size_t p = 0; p < numProfiles;  ++p)
	{
		std::string type_name = fp[p]->getTypeName(); 
			
		if(type_name == "profile_COMMON")
		{
			// Found the common profile, get the technique from it as well
			domProfile_COMMON *common = (domProfile_COMMON*)(domFx_profile_abstract*)fp[p]; 

			// Get all images in profile_COMMON
      const domImage_Array &cia = common->getImage_array();
			for(i = 0; i < cia.getCount(); ++i)
				ReadImage(printStatusMessage, scene_graph->all_images, cia[i], dir);

			// Get all images in profile_COMMON
			domProfile_COMMON::domTechnique *technique = common->getTechnique(); 
			if(technique == NULL)
				break; 

      const domImage_Array &tia = technique->getImage_array();
			for(i = 0; i < tia.getCount(); ++i)
				ReadImage(printStatusMessage, scene_graph->all_images, tia[i], dir);

			// This support is really basic, since the shader models don't descend from a common type
			// we have to handle each one individually.  There can only be one in the technique.
			// All of them assume the texture is in the diffuse component for now.

			ShaderElements shader;
			domProfile_COMMON::domTechnique::domConstant *constant = technique->getConstant();
			if(constant)
      {
				ReadConstant(effect->second, shader, constant);
        effect->second.shader_model = Effect::Constant;
      }
			domProfile_COMMON::domTechnique::domLambert *lambert = technique->getLambert();
			if(lambert)
      {
				ReadLambert(effect->second, shader, lambert);
        effect->second.shader_model = Effect::Lambert;
      }
			domProfile_COMMON::domTechnique::domPhong *phong = technique->getPhong();
			if(phong)
      {
				ReadPhong(effect->second, shader, phong);
        effect->second.shader_model = Effect::Phong;
      }
			domProfile_COMMON::domTechnique::domBlinn *blinn = technique->getBlinn();
			if(blinn)
      {
				ReadBlinn(effect->second, shader, blinn);
        effect->second.shader_model = Effect::Blinn;
      }

			const domCommon_newparam_type_Array &newparam_array = common->getNewparam_array();
			NewParamMap new_params;
			for(size_t i=0; i < newparam_array.getCount(); i++)
				new_params.insert(std::make_pair(newparam_array[i]->getSid(), newparam_array[i]));
				
			// TODO: take only the texture from diffuse for now
			Image::ImageList::iterator image;
			image = GetTextureFromShader(printStatusMessage, 
                                   scene_graph->all_images, 
                                   new_params, 
                                   shader.diffuse, 
                                   dir);
			if(image != scene_graph->all_images.end())
				effect->second.textures.push_back(image->first);
/*					image = GetTextureFromShader(NewParams, shader.emission);
			if (image)
				newEffect->Textures.push_back(image);
			image = GetTextureFromShader(NewParams, shader.ambient);
			if (image)
				newEffect->Textures.push_back(image);
			image = GetTextureFromShader(NewParams, shader.specular);
			if (image)
				newEffect->Textures.push_back(image);
			image = GetTextureFromShader(NewParams, shader.reflective);
			if (image)
				newEffect->Textures.push_back(image);
			image = GetTextureFromShader(NewParams, shader.transparent);
			if (image)
				newEffect->Textures.push_back(image);
*/				
      if(!effect->second.textures.empty())
        effect->second.shader_model = Effect::Texture;

			// Handle an effect with no texture
			return effect; 	
		} else {
    	printStatusMessage(std::string("   ") + type_name + " is not supported");
      return scene_graph->all_effects.end();
		}
  }
  return effect;
}


bool 
Scene::readEffectLibrary(domLibrary_effectsRef lib)
{
  filesystem::path dir = this->dae_file_name.string();
  const domEffect_Array &ea = lib->getEffect_array();
  for(size_t i = 0; i < ea.getCount(); ++i)
    {
      ReadEffect(this->scene_graph.printStatusMessage,
		 &(this->scene_graph), 
		 ea[i], 
		 dir); 
    }

  return true;
}
