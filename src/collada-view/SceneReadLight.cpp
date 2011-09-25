#include <dae.h>
#include <dom/domCOLLADA.h>
#include <dom/domAsset.h>
#include "Scene.h"
#include "Light.h"


Light::LightList::iterator 
ReadLight(LoggerFuncT &printStatusMessage, 
          SceneGraph &scene_graph, 
          domLightRef dom_light)
{
  const xsID gid = dom_light->getId();
  if(gid == NULL)
    return scene_graph.all_lights.end();

  const Light::LightID light_key = 
    {gid, dom_light->getDocumentURI()->getURI()};
  Light::LightList::iterator light = scene_graph.all_lights.find(light_key);
	if(light != scene_graph.all_lights.end()) // light is found
		return light;

	printStatusMessage(std::string("  add new Light ") + gid);

  if(dom_light.cast() == NULL)
    return scene_graph.all_lights.end();

  // Get the common technique for this light
  domLight::domTechnique_common *commonTechnique = dom_light->getTechnique_common();
  if(commonTechnique == NULL) 
    return scene_graph.all_lights.end();

  bool inserted;
  tie(light, inserted) = scene_graph.all_lights.insert(std::make_pair(light_key, Light()));
  Light &new_light = light->second;

  // Only one of these light types can be present
  domLight::domTechnique_common::domAmbient		*ambientElement		= commonTechnique->getAmbient();
  domLight::domTechnique_common::domDirectional	*directionalElement	= commonTechnique->getDirectional();
  domLight::domTechnique_common::domPoint			*pointElement		= commonTechnique->getPoint();
  domLight::domTechnique_common::domSpot			*spotElement		= commonTechnique->getSpot();
  
  if(ambientElement)
  {
    new_light.type = Light::AMBIENT;
    domFloat3 &color = ambientElement->getColor()->getValue();
    new_light.color = Color4f((float)(color[0]), (float)(color[1]), (float)(color[2]), 1.0f);
  }
  else if(directionalElement)
  {
    new_light.type = Light::DIRECTIONAL;
    domFloat3 &color = directionalElement->getColor()->getValue();
    new_light.color = Color4f((float)(color[0]), (float)(color[1]), (float)(color[2]), 1.0f);
  }
  else if(pointElement)
  {
    new_light.type = Light::POINT;
    domFloat3 &color = pointElement->getColor()->getValue();
    new_light.color = Color4f((float)(color[0]), (float)(color[1]), (float)(color[2]), 1.0f);
    if(pointElement->getConstant_attenuation()) 
      new_light.constant_attenuation = (float)(pointElement->getConstant_attenuation()->getValue());
    if(pointElement->getLinear_attenuation()) 
      new_light.linear_attenuation = (float)(pointElement->getLinear_attenuation()->getValue());
    if(pointElement->getQuadratic_attenuation()) 
      new_light.quadratic_attenuation = (float)(pointElement->getQuadratic_attenuation()->getValue());
  }
  else if(spotElement)
	{
    new_light.type = Light::SPOT;
    domFloat3 &color = spotElement->getColor()->getValue();
    new_light.color = Color4f((float)(color[0]), (float)(color[1]), (float)(color[2]), 1.0f);
    if(spotElement->getConstant_attenuation())
      new_light.constant_attenuation = (float)(spotElement->getConstant_attenuation()->getValue());
    if(spotElement->getLinear_attenuation())
      new_light.linear_attenuation = (float)(spotElement->getLinear_attenuation()->getValue());
    if(spotElement->getQuadratic_attenuation())
      new_light.quadratic_attenuation	= (float)(spotElement->getQuadratic_attenuation()->getValue());
    if(spotElement->getFalloff_angle())
      new_light.falloff_angle = (float)(spotElement->getFalloff_angle()->getValue());
    if (spotElement->getFalloff_exponent())
      new_light.falloff_exponent = (float)(spotElement->getFalloff_exponent()->getValue());
	}

  return light;
}


bool 
Scene::readInstanceLight(Node &node, domInstance_lightRef instance)
{
  const xsAnyURI &urltype = instance->getUrl();
  domElement *element = (domElement*)urltype.getElement();
  if(element == NULL) // this instance light is not found skip to the next one
    {
      this->scene_graph.printStatusMessage(std::string("    can not find referenced light: ") + urltype.getURI());
      return false;
    }

	const Light::LightList::iterator light 
    = ReadLight(this->scene_graph.printStatusMessage, 
                this->scene_graph, 
                (domLight*)element);
	if(light == this->scene_graph.all_lights.end()) // couldn't find from existing pool of geometries
		return false;

  InstanceLight instance_light;
  instance_light.abstract_light_ref = light->first;

  node.instance_lights.push_back(instance_light);
	return true;
}
