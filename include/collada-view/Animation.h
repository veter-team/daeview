#ifndef __ANIMATION_H
#define __ANIMATION_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "Node.h"


struct AnimSource
{
  typedef std::vector<float> FloatArray;
  FloatArray source_data;

  typedef std::string AnimSourceID;
  typedef std::map<AnimSourceID, AnimSource> AnimSourceList;
};


struct AnimSampler
{
  // Semantic to source map
  typedef std::map<std::string, AnimSource::AnimSourceID> SourceList;
  SourceList inputs;

  typedef std::map<std::string, AnimSampler> AnimSamplerList;
};


enum AnimTarget
{
  eAnimTargetX,
  eAnimTargetY,
  eAnimTargetZ,
  eAnimTargetXYZ, 
  eAnimTargetAngle,

  eTargetUnknown, 

  eRotXAxis,
  eRotYAxis,
  eRotZAxis,
  eRotate, 

  eScaleXAxis,
  eScaleYAxis,
  eScaleZAxis,
  eScale,

  eTransXAxis,
  eTransYAxis,
  eTransZAxis, 
  eTranslate, 

  eSource,
  eMatrix
};


class Transformation;

struct AnimChannel
{
  AnimSampler::AnimSamplerList::key_type sampler_key;
  AnimSource::AnimSourceList::key_type input_source_key;
  AnimSource::AnimSourceList::key_type output_source_key;

	std::string target_id_str;
	std::string target_sid_str;	
	std::string target_member_str;	

  AnimTarget target;
  size_t num_element_targets;

  typedef std::pair<std::string, int> NodeTransformPair;
  typedef std::vector<NodeTransformPair> TargetList;
  TargetList tranformation_targets;

  bool getSample(float key, const AnimSource &in, const AnimSource &out, float *sample_values) const;
};


struct Animation
{
  Animation() :
	  has_rotation(false),
	  has_translation(false), 
	  has_scale(false),
	  has_source(false),
	  has_matrix(false),
    num_anim_channels(0) {}

	bool has_rotation;
	bool has_translation; 
	bool has_scale;
	bool has_source;
	bool has_matrix;

  size_t num_anim_channels; // multipule elements can be targeted by one channel

  AnimSource::AnimSourceList sources;
  AnimSampler::AnimSamplerList samplers;
  
  typedef std::vector<AnimChannel> AnimChannelList;
  AnimChannelList channels;

  struct AnimationID
  {
    std::string name;
    std::string doc_uri;
    bool operator < (const AnimationID &rhs) const {return name == rhs.name ? (doc_uri < rhs.doc_uri) : (name < rhs.name);}
  };
  typedef std::map<AnimationID, Animation> AnimationList;

  typedef std::set<std::string> NodeIdSet;

  float getMaxTime() const;
  void animate(LoggerFuncT &printStatusMessage, Node::NodeMap &all_nodes, float pos, NodeIdSet &touched_nodes);
};


#endif // __ANIMATION_H
