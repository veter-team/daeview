#include <dae.h>
#include <dom/domCOLLADA.h>
#include <dom/domAsset.h>
#include "Scene.h"
#include "Animation.h"

#ifndef WIN32
#define _stricmp strcasecmp
#endif


bool 
ReadAnimationSource(LoggerFuncT &printStatusMessage, 
                    Animation &animation, 
                    domSourceRef dom_source)
{
  if(dom_source == NULL)
    return false;
  xsID gid = dom_source->getId();
	if(gid == NULL) 
    return false;

  AnimSource::AnimSourceList::iterator src_iter = animation.sources.find(gid);
	if(src_iter != animation.sources.end()) // animation is found
		return true;

  bool inserted;
  tie(src_iter, inserted) = animation.sources.insert(std::make_pair(gid, AnimSource()));
  
  AnimSource &source = src_iter->second;

	// Copy over the float array data if any 
	if(dom_source->getFloat_array()) // for float array
	{
		const daeDoubleArray &floatArray = dom_source->getFloat_array()->getValue();
    source.source_data.reserve(floatArray.getCount());
		
		// copy the array data 
		for(size_t i = 0; i < floatArray.getCount(); ++i)
			source.source_data.push_back((float)floatArray[i]);
	}
  else
  {
    printStatusMessage(std::string("Animation source ") + gid + " has empty data array or unsupported");
    return false;
  }

	return true;
}


bool 
ReadAnimationSampler(Animation &animation, domSamplerRef dom_sampler)
{
	if(dom_sampler == NULL) 
    return false;
  xsID gid = dom_sampler->getID();
	if(gid == NULL) 
    return false;

  AnimSampler::AnimSamplerList::iterator sampler_iter = animation.samplers.find(gid);
	if(sampler_iter != animation.samplers.end()) // animation is found
		return true;

  bool inserted;
  tie(sampler_iter, inserted) = animation.samplers.insert(std::make_pair(gid, AnimSampler()));
  
  AnimSampler &sampler = sampler_iter->second;

	const domInputLocal_Array &input_array = dom_sampler->getInput_array();
	for(size_t i = 0; i < input_array.getCount(); ++i)
	{
		domSource *source = (domSource*) (domElement*) input_array[i]->getSource().getElement();
    assert(source);
    AnimSource::AnimSourceList::const_iterator si = animation.sources.find(source->getID());
    if(si != animation.sources.end())
		  sampler.inputs.insert(std::make_pair(input_array[i]->getSemantic(), source->getID()));
	}

  return true;
}


bool 
ReadAnimationChannel(LoggerFuncT &printStatusMessage, 
                     Animation &animation, 
                     domChannelRef dom_channel)
{
	if(dom_channel == NULL)
    return false;

  animation.channels.push_back(AnimChannel());
  AnimChannel &new_channel = animation.channels.back();

	domSampler *sampler = (domSampler*)(domElement*)dom_channel->getSource().getElement();
	new_channel.sampler_key = sampler->getID();
	const AnimSampler &anim_sampler = animation.samplers.find(sampler->getID())->second;

	new_channel.input_source_key = anim_sampler.inputs.find("INPUT")->second;
	new_channel.output_source_key = anim_sampler.inputs.find("OUTPUT")->second;

	const std::string target = dom_channel->getTarget();
	// parse target
	// get a pointer to the target element
  size_t id_sep_pos = target.find('/');
  if(id_sep_pos == std::string::npos)
    if((id_sep_pos = target.find('(')) == std::string::npos)
      id_sep_pos = target.find('.');

	// get a pointer to the final element 
  size_t sid_sep_pos = target.find('.');
  if(sid_sep_pos == std::string::npos)
    if((sid_sep_pos = target.find('(')) == std::string::npos)
      sid_sep_pos = target.length();

  if(id_sep_pos != std::string::npos)
    new_channel.target_id_str = target.substr(0, id_sep_pos);
	if(id_sep_pos != std::string::npos 
     && id_sep_pos != std::string::npos 
     && sid_sep_pos > id_sep_pos)
    new_channel.target_sid_str = target.substr(id_sep_pos + 1, sid_sep_pos - id_sep_pos - 1); 
	if(sid_sep_pos != std::string::npos 
    && sid_sep_pos != target.length())
    new_channel.target_member_str = target.substr(sid_sep_pos + 1); 
/*
	const CrtChar * id_sep = CrtFindStr( target, "/");
	if (id_sep == NULL)	id_sep = CrtFindStr( target, "(");
	if (id_sep == NULL)	id_sep = CrtFindStr( target, ".");

	// get a pointer to the final element 
	const CrtChar * sid_sep = CrtFindStr( target, "." );	// search for '.'
	if (sid_sep == NULL) sid_sep = CrtFindStr( target, "(" );		// search for '('
	if (sid_sep == NULL) sid_sep = target + CrtLen(target);			// nothing else matches, then there is no member
	
	if (id_sep != NULL) CrtNCpy(new_channel->TargetIDStr, target, (CrtInt) (id_sep - target)); 
	if (id_sep != NULL && id_sep !=NULL && sid_sep>id_sep) CrtNCpy(new_channel->TargetSIDStr, id_sep+1, (CrtInt) (sid_sep - id_sep - 1)); 
	if (sid_sep!=NULL && (*sid_sep)!='\0') CrtCpy(new_channel->TargetMemberStr, sid_sep+1); 
*/
	// resolve target
	daeElement *element = NULL;
	daeElement *rootnode = dom_channel->getDocument()->getDomRoot();
	daeSIDResolver sidresolver(rootnode, target.c_str());
	element = sidresolver.getElement();
	if(element == NULL)
	{
		printStatusMessage(std::string("Animation target '") + target + "' can not be solved");
		animation.channels.pop_back();
		return false;
	}

	// set channel info
	COLLADA_TYPE::TypeEnum type = element->getElementType();
	switch(type)
	{
	case COLLADA_TYPE::TRANSLATE:
		animation.has_translation = true;
		new_channel.target = eTranslate;
		new_channel.num_element_targets = 3; 
		break;

	case COLLADA_TYPE::ROTATE:
		animation.has_rotation = true;
		new_channel.target = eRotate;
		new_channel.num_element_targets = 4; 
		break;

	case COLLADA_TYPE::SCALE:
		animation.has_scale = true;
		new_channel.target = eScale;
		new_channel.num_element_targets = 3; 
		break;

	case COLLADA_TYPE::SOURCE:
		animation.has_source = true;
		new_channel.target = eSource;
		new_channel.num_element_targets = 1; 
		break;

	case COLLADA_TYPE::MATRIX:
		animation.has_matrix = true;
		new_channel.target = eMatrix;
		new_channel.num_element_targets = 16; 
		break;

	default:
		printStatusMessage(std::string("Animation target '") + target + "' is not supported");
		animation.channels.pop_back();
		return false;
	}

	// parse member
	if(!new_channel.target_member_str.empty())
	{
		const char *target_member = new_channel.target_member_str.c_str();
		if(_stricmp(target_member, "AXIS" ) == 0 ||
			 _stricmp(target_member, "ANGLE" ) == 0)
		{
			domRotate *rotate = (domRotate*)element;
			if(rotate->getValue()[0] == 1)
			{	// rotate x axis
				animation.has_rotation = true;
				new_channel.target = eRotXAxis;
				new_channel.num_element_targets = 1; 
			} else if (rotate->getValue()[1] == 1) 
			{	// rotate y axis
				animation.has_rotation = true;
				new_channel.target = eRotYAxis;
				new_channel.num_element_targets = 1; 
			} else if (rotate->getValue()[2] == 1) 
			{	// rotate y axis
				animation.has_rotation = true;
				new_channel.target = eRotZAxis;
				new_channel.num_element_targets = 1; 
			}
		}
		else if(!_stricmp(target_member, "X"))
		{
			new_channel.target = eAnimTargetX; 
			new_channel.num_element_targets = 1; 
		}
		else if(!_stricmp(target_member, "Y"))
		{
			new_channel.target = eAnimTargetY;
			new_channel.num_element_targets = 1;
		}
		else if(!_stricmp(target_member, "Z"))
		{
			new_channel.target = eAnimTargetZ;
			new_channel.num_element_targets = 1;
		}
		else if((*target_member) >= '0' && (*target_member) <= '9')
		{
			new_channel.target = eSource;
			new_channel.num_element_targets = 1;
		}
		else
		{
			new_channel.target = eAnimTargetXYZ;
			new_channel.num_element_targets = 3;
		}
	}
	animation.num_anim_channels = new_channel.num_element_targets;
	return true;
}


Animation::AnimationList::iterator   
ReadAnimation(LoggerFuncT &printStatusMessage, 
              Animation::AnimationList &all_animations, 
              domAnimationRef dom_animation)
{
  size_t i;
  xsID gid = dom_animation->getId();
	if(gid == NULL) 
    return all_animations.end();

  const Animation::AnimationID animation_key = 
    {gid, dom_animation->getDocumentURI()->getURI()};
  Animation::AnimationList::iterator anim_iter = all_animations.find(animation_key);
	if(anim_iter != all_animations.end()) // animation is found
		return anim_iter;
  
  printStatusMessage(std::string("  add new Animation ") + gid);

  bool inserted;
  tie(anim_iter, inserted) = all_animations.insert(std::make_pair(animation_key, Animation()));
  
  Animation &animation = anim_iter->second;
  // get the number of sources 
  const domSource_Array &source_array = dom_animation->getSource_array();
  for(i = 0; i < source_array.getCount(); ++i)
	  ReadAnimationSource(printStatusMessage, animation, source_array[i]);

  const domSampler_Array &sampler_array = dom_animation->getSampler_array();
  for(i = 0; i < sampler_array.getCount(); ++i)
	  ReadAnimationSampler(animation, sampler_array[i]);

  const domChannel_Array &channel_array = dom_animation->getChannel_array();
  for(i = 0; i < channel_array.getCount(); ++i)
	  ReadAnimationChannel(printStatusMessage, animation, channel_array[i]);

  if(animation.channels.empty())
  //if(!animation.channels.empty())
	//  animation.generateKeys(); 
  //else
  {
	  printStatusMessage("No Channel found in this animation");
	  all_animations.erase(anim_iter);
	  return all_animations.end();
  }

  return anim_iter;
}


bool
Scene::readAnimationLibrary(domLibrary_animationsRef lib)
{
	this->scene_graph.printStatusMessage(" Reading Animation Library");	
  const domAnimation_Array &aa = lib->getAnimation_array();
	for(size_t i = 0; i < aa.getCount(); ++i)
		ReadAnimation(this->scene_graph.printStatusMessage, 
                  this->scene_graph.all_animations, 
                  aa[i]);

	return true; 	
}
