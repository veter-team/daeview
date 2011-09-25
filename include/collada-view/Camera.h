#ifndef __CAMERA_H
#define __CAMERA_H

#include <map>
#include <string>
#include <vectormath/vmInclude.h>

using namespace Vectormath::Aos;

/**
 * The AbstractCamera class holds the parameters for a camera taken
 * from a <camera> inside a <library_cameras>.  These parameters are
 * then used to instantiate an <instance_camera> in a node.
 * Currently, the instance_cameras reference this data so if you
 * change it here all the related instance_cameras will change too.
 * This should probably be changed so each <instance_camera> has a
 * copy of the <camera> data, this would allow the parameters of
 * individual <instance_camera> to change.
 */
struct Camera
{
  float Xfov;   /**< X field of view for perspective camera */
  float Yfov;   /**< Y field of view for perspective camera */ 
  float aspect; /**< Aspect Ratio for perspective camera */
  float ZNear;  /**< Z clip near for perspective camera */
  float ZFar;   /**< Z clip far for perspective camera */

  float Xmag;   /**< X magnification for an orthographic camera */
  float Ymag;   /**< Y magnification for an orthographic camera */
		
  Camera();

  struct CameraID
  {
    std::string name;
    std::string doc_uri;
    bool operator < (const CameraID &rhs) const {return name == rhs.name ? (doc_uri < rhs.doc_uri) : (name < rhs.name);}
  };
  typedef std::map<CameraID, Camera> CameraList;
};


/** 
 * The InstanceCamera struct holds the information needed to make
 * an instance of an abstract camera.  This maps to the
 * <instance_camera> tag in COLLADA NOTE: This assumes that all
 * camera instances that reference the same CrtCamera are sharing the
 * info in that abstract camera, ie: if someone changes the stuff in
 * the CrtCamera all the instances derived from it will change.  We
 * could avoid this by keeping a copy of CrtCamera in the instance.
 */
struct InstanceCamera
{
  InstanceCamera();

  Camera::CameraList::key_type abstract_camera_ref; /**<< The abstract camera
				where the cam parameters are stored*/

};


#endif // __CAMERA_H
