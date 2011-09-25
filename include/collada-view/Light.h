#ifndef __LIGHT_H
#define __LIGHT_H

#include <map>
#include "comdefs.h"


struct Light
{
  enum LightType 
    {
      UNKNOWN,
      AMBIENT = 1,
      DIRECTIONAL,
      POINT,
      SPOT	
    };

  Color4f color; /**< The color of the light (all types)*/
  float	falloff_angle; /**< Falloff angle for spot light (spot) */
  float	falloff_exponent; /**< Falloff exponent for spot light (spot) */
  float	constant_attenuation; /**< Constant attenuation factor (point
				and spot)*/
  float linear_attenuation; /**< Linear attenuation factor (point
				 and spot)*/
  float	quadratic_attenuation; /**< Quadratic attenuation factor (point
				 and spot) */
  LightType type;

  Light()
  : color(0.5f, 0.5f, 0.5f, 1.0f),
    falloff_angle(180.0f),
    falloff_exponent(0.0f),
    constant_attenuation(1.0f),
    linear_attenuation(0.0f),
    quadratic_attenuation(0.0f),
    type(POINT)
  {
  }

  struct LightID
  {
    std::string name;
    std::string doc_uri;
    bool operator < (const LightID &rhs) const {return name == rhs.name ? (doc_uri < rhs.doc_uri) : (name < rhs.name);}
  };
  typedef std::map<LightID, Light> LightList;
};


/** 
 * The InstanceLight class holds the information needed to make an
 *  instance of an abstract light.  This maps to the <instance_light>
 *  tag in COLLADA NOTE: This assumes that all light instances that
 *  reference the same CrtLight are sharing the info in that abstract
 *  light, ie: if someone changes the stuff in the CrtLight all the
 *  instances derived from it will change.  We could avoid this by
 *  keeping a copy of CrtLight in the instance.
 */
struct InstanceLight
{
  Light::LightList::key_type abstract_light_ref; /**<< The abstract
						    light where the
						    light parameters
						    are stored */
};

#endif // __LIGHT_H
