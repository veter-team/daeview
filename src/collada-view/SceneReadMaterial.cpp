#include "Scene.h"
#include <dae.h>
#include <dom/domCOLLADA.h>
#include <dom/domAsset.h>


Material::MaterialList::iterator 
ReadMaterial(LoggerFuncT &printStatusMessage, 
             SceneGraph &scene_graph, 
             domMaterialRef dom_material, 
             const filesystem::path &dir)
{
  xsID gid = dom_material->getId();
	if(gid == NULL) 
    return scene_graph.all_materials.end();

  const Material::MaterialID material_key = 
    {gid, dom_material->getDocumentURI()->getURI()};
  Material::MaterialList::iterator material = scene_graph.all_materials.find(material_key);
	if(material != scene_graph.all_materials.end()) // material is found
		return material;
  
	scene_graph.printStatusMessage(std::string("  add new Material ") + gid);
	
	const domMaterial *material_element = dom_material.cast(); 

	if(!material_element) 
	  return scene_graph.all_materials.end(); 	

	if(!material_element->getInstance_effect())
		return scene_graph.all_materials.end(); 

	domElement *element = (domElement*)material_element->getInstance_effect()->getUrl().getElement(); 
	if(element == NULL)
		return scene_graph.all_materials.end();
		
	// find the effect that the material is refering too 
	Effect::EffectList::const_iterator effect 
    = ReadEffect(printStatusMessage, 
                 &scene_graph, 
                 (domEffect*)element, 
                 dir);
	if(effect != scene_graph.all_effects.end())
	{
    bool inserted;
	  tie(material, inserted) = scene_graph.all_materials.insert(std::make_pair(material_key, Material()));
		material->second.effect = effect->first; 
    scene_graph.printStatusMessage(std::string("  attached effect ") + effect->first.name 
      + " to material " + material_key.name);
		return material;
	} else
	{
		scene_graph.printStatusMessage(std::string("  No effect ") + element->getID() 
      + " for old-style matrial " + dom_material->getId() 
      + " (no problem if there is a cfx version of this material)"); 
		return scene_graph.all_materials.end();
	}
}


bool 
Scene::readMaterialLibrary(domLibrary_materialsRef lib)
{
  filesystem::path dir = this->dae_file_name.string();
  const domMaterial_Array &ma = lib->getMaterial_array();
	for(size_t i = 0; i < ma.getCount(); ++i)
		ReadMaterial(this->scene_graph.printStatusMessage, 
                 this->scene_graph, 
                 ma[i], 
                 dir); 

	return true; 	
}


bool  
Scene::readInstanceMaterial(InstanceGeometry &instance_geometry, domInstance_materialRef dom_instance)
{
	// Make a new InstanceMaterial and add it to the list in newCrtInstanceGeometry
	instance_geometry.material_instances.push_back(InstanceMaterial());
	InstanceMaterial &newimaterial = instance_geometry.material_instances.back();
	newimaterial.symbol = dom_instance->getSymbol();
	newimaterial.target = dom_instance->getTarget().getID();

	// resolve bind target for fx materials
/*	std::map<std::string, cfxMaterial*>::iterator iter;
	for(iter = cfxMaterials.begin(); iter != cfxMaterials.end(); ++iter)
	{
		std::string id = (*iter).first;
		if(id==newCrtInstanceMaterial->target)
		{
			newCrtInstanceMaterial->targetcfxMaterial = (*iter).second;
			break;
		}
	}
*/
	//if(newCrtInstanceMaterial->targetcfxMaterial==NULL)
	{// can't resolve fx materials, try common materials
		domElement *element = dom_instance->getTarget().getElement();
		if(element)
		{
      filesystem::path dir = this->dae_file_name.string();
			Material::MaterialList::iterator material 
        = ReadMaterial(this->scene_graph.printStatusMessage, 
                       this->scene_graph, 
                       (domMaterial*)element, 
                       dir);
			if(material != this->scene_graph.all_materials.end()) // material added or found
			{
				newimaterial.target_material = material->first;				
			} else
			{
				this->scene_graph.printStatusMessage(std::string("  Couldn't find instance Materials for binding: ") + newimaterial.target);
        return false;
			}
		}
	}

	return true;
}
