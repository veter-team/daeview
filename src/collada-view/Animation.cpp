#include "Animation.h"
#include "Node.h"
#include <algorithm>



bool 
AnimChannel::getSample(float key, 
                       const AnimSource &in, 
                       const AnimSource &out,
                       float *sample_values) const
{
  const AnimSource::FloatArray &source_data = 
    in.source_data;

  if(key < source_data.front() || key > source_data.back())
    return false;

  size_t right_pos;
  AnimSource::FloatArray::const_iterator right_key;
  AnimSource::FloatArray::const_iterator left_key = 
    std::lower_bound(source_data.begin(), source_data.end(), key);
  if(left_key > source_data.begin())
    left_key -= 1;
  size_t left_pos = left_key - source_data.begin();
  if(left_pos >= source_data.size() - 1)
  {
    right_pos = left_pos = source_data.size() - 1;
    right_key = left_key;
  }
  else
  {
    right_key = left_key + 1;
    right_pos = left_pos + 1;
  }

  AnimSource::FloatArray::const_iterator left_val = 
    out.source_data.begin() + left_pos * this->num_element_targets;
  AnimSource::FloatArray::const_iterator right_val = 
    out.source_data.begin() + right_pos * this->num_element_targets;

  // Linear interpolation only for now

  const float k = ((right_key == left_key) ? 1.0f : (key - *left_key) / (*right_key - *left_key));
  for(size_t i = 0; i < this->num_element_targets; ++i)
  {
    const float v1 = *(left_val + i);
    const float v2 = *(right_val + i);
    sample_values[i] = v1 + (v2 - v1) * k;
  }

  return true;
}


void 
AnimateTransformation(LoggerFuncT &printStatusMessage,
                      Transformation &trans, 
                      const float *value, 
                      AnimTarget target)
{
  switch(target)
  {
  // new way 
  case eScaleXAxis:
    trans.transform.setElem(0, 0, value[0]);
  break;

  case eAnimTargetX:
  case eTransXAxis:
    trans.transform.setElem(3, 0, value[0]);
  break; 

  case eScaleYAxis:
    trans.transform.setElem(1, 1, value[0]);
  break;

  case eAnimTargetY:
  case eTransYAxis:
    trans.transform.setElem(3, 1, value[0]);
  break; 

  case eScaleZAxis:
    trans.transform.setElem(2, 2, value[0]);
  break;

  case eAnimTargetZ:
  case eTransZAxis:
    trans.transform.setElem(3, 2, value[0]);
  break; 

  case eRotXAxis:
    trans.transform = Transform3::rotationX(value[0] * DEGREES_TO_RADIANS);
  break; 

  case eRotYAxis:
    trans.transform = Transform3::rotationY(value[0] * DEGREES_TO_RADIANS);
  break;

  case eRotZAxis:
    trans.transform = Transform3::rotationZ(value[0] * DEGREES_TO_RADIANS);
  break; 

  case eAnimTargetAngle:
    // ??? don't know how..... trans.transform = Transform3::rotation(value[0] * DEGREES_TO_RADIANS);
  break; 

  case eTranslate:
    trans.transform.setTranslation(Vector3(value[0], value[1], value[2]));
    break;

  case eScale:
    trans.transform.setElem(0, 0, value[0]);
    trans.transform.setElem(1, 1, value[1]);
    trans.transform.setElem(2, 2, value[2]);
  break;

  case eAnimTargetXYZ:
    /* ??? do not know how yet....
	  Interp(vec.x, &AnimKeySets[c], time );
	  Interp(vec.y, &AnimKeySets[c+1], time );
	  Interp(vec.z, &AnimKeySets[c+2], time );*/
	  break; 

  case eMatrix:
    for(size_t c = 0; c < 4; ++c)
    {
      trans.matrix[c][0] = value[c*4 + 0];
      trans.matrix[c][1] = value[c*4 + 1];
      trans.matrix[c][2] = value[c*4 + 2];
      trans.matrix[c][3] = value[c*4 + 3];
    }
	  //trans.matrix = transpose(trans.matrix);
	  break; 

  default:
	  printStatusMessage("Animation target not found");
	  break; 
  }
}


float 
Animation::getMaxTime() const
{
  float max_time = 0;
  float max_channel_time = 0;

  for(AnimChannelList::const_iterator ch = this->channels.begin();
    ch != this->channels.end(); ++ch)
  {
    const AnimSource &in = this->sources.find(ch->input_source_key)->second;
    const AnimSource::FloatArray &source_data = in.source_data;
    if(source_data.empty())
      max_channel_time = 0;
    else
      max_channel_time = source_data.back();
    if(max_channel_time > max_time)
      max_time = max_channel_time;
  }
  return max_time;
}


void 
Animation::animate(LoggerFuncT &printStatusMessage,
                   Node::NodeMap &all_nodes, 
                   float pos, 
                   NodeIdSet &touched_nodes)
{
  for(AnimChannelList::const_iterator ch = this->channels.begin();
    ch != this->channels.end(); ++ch)
  {
    const AnimSource &in = this->sources.find(ch->input_source_key)->second;
    const AnimSource &out = this->sources.find(ch->output_source_key)->second;
    float value[16];
    if(!ch->getSample(pos, in, out, value))
      continue;
    for(AnimChannel::TargetList::const_iterator t = ch->tranformation_targets.begin();
      t != ch->tranformation_targets.end(); ++t)
    {
      touched_nodes.insert(t->first);
      Node *node = all_nodes.find(t->first.c_str());
      Transformation &tr = node->transformations.at(t->second);
      AnimateTransformation(printStatusMessage, tr, value, ch->target);
    }
  }
}
