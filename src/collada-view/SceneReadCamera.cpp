#include <dae.h>
#include <dom/domCOLLADA.h>
#include <dom/domAsset.h>
#include "Scene.h"
#include "Camera.h"


Camera::CameraList::iterator 
ReadCamera(LoggerFuncT &printStatusMessage, 
           Camera::CameraList &all_cameras, 
           domCameraRef dom_camera)
{
  const xsID gid = dom_camera->getId();
  if(gid == NULL)
    return all_cameras.end();

  const Camera::CameraID camera_key = 
    {gid, dom_camera->getDocumentURI()->getURI()};
  Camera::CameraList::iterator camera = all_cameras.find(camera_key);
	if(camera != all_cameras.end()) // camera is found
		return camera;

	printStatusMessage(std::string("  add new Camera ") + gid);

  domCamera *camera_element = dom_camera.cast();
  if(camera_element == NULL)
    return all_cameras.end();

	// Make the camera
  bool inserted;
  tie(camera, inserted) = all_cameras.insert(std::make_pair(camera_key, Camera()));
  Camera &new_cam = camera->second;

	// Get the optics
	domCamera::domOptics *cameraOptics = camera_element->getOptics();
	
	// Get the optics common profile technique
	domCamera::domOptics::domTechnique_common *cameraCommonTechnique = cameraOptics->getTechnique_common();
		
	// Get the get the perspective and orthographic common profiles (if they exist)
	domCamera::domOptics::domTechnique_common::domPerspective *camera_perspective = cameraCommonTechnique->getPerspective();
	domCamera::domOptics::domTechnique_common::domOrthographic *camera_orthographic = cameraCommonTechnique->getOrthographic();
		
	// Setup camera parameters, note we have to check if a parameter is there before doing getValue
	// Parameters not in the COLLADA data will be left at the CrtCamera defaults
	if(camera_perspective)
	{
		if(camera_perspective->getXfov())
			new_cam.Xfov = (float)(camera_perspective->getXfov()->getValue()) * DEGREES_TO_RADIANS;
		if(camera_perspective->getYfov())
      new_cam.Yfov = (float)(camera_perspective->getYfov()->getValue()) * DEGREES_TO_RADIANS;
		if(camera_perspective->getAspect_ratio())
			new_cam.aspect = (float)(camera_perspective->getAspect_ratio()->getValue());
		if(camera_perspective->getZnear())
			new_cam.ZNear = (float)(camera_perspective->getZnear()->getValue());
		if(camera_perspective->getZfar())
			new_cam.ZFar = (float)(camera_perspective->getZfar()->getValue());
		// force Znear to be >= 1.0 to avoid rendering problems
		if(new_cam.ZNear < 1.0f)
			new_cam.ZNear = 1.0f;
    // If only xfov specified, try to calculate yfov using aspect
    if(new_cam.Xfov == 0.0f)
    {
      if(new_cam.Yfov != 0.0f && new_cam.aspect != 0.0f)
        new_cam.Xfov = new_cam.Yfov * new_cam.aspect;
      else
        new_cam.Xfov = (new_cam.Yfov == 0.0f ? 36.0f : new_cam.Yfov);
    }
	} else if(camera_orthographic)
	{
		// Setup orthographic camera
		printStatusMessage("Support for orthograph cameras incomplete, this camera will probably look odd");
		if(camera_orthographic->getXmag())
			new_cam.Xmag = (float)(camera_orthographic->getXmag()->getValue());
		if(camera_orthographic->getYmag())
			new_cam.Ymag = (float)(camera_orthographic->getYmag()->getValue());
		if(camera_orthographic->getAspect_ratio())
			new_cam.aspect = (float)(camera_orthographic->getAspect_ratio()->getValue());
		if(camera_orthographic->getZnear())
			new_cam.ZNear = (float)(camera_orthographic->getZnear()->getValue());
		if(camera_orthographic->getZfar())
			new_cam.ZFar = (float)(camera_orthographic->getZfar()->getValue());
		// !!!GAC force Znear to be >= 1.0 to avoid rendering problems
		if(new_cam.ZNear < 1.0f)
			new_cam.ZNear = 1.0f;
	}

  return camera;
}


bool 
Scene::readInstanceCamera(Node &node, domInstance_cameraRef instance)
{
	const xsAnyURI &urltype = instance->getUrl();
	domElement *element = (domElement*)urltype.getElement();
	if (element==NULL) // this camera instance is not found skip to the next one
	{
		this->scene_graph.printStatusMessage(std::string("    can not find referenced camera: ") + urltype.getURI());
		return false;
	}

	const Camera::CameraList::iterator camera 
    = ReadCamera(this->scene_graph.printStatusMessage,
                 this->scene_graph.all_cameras, 
                 (domCamera*)element);
	if(camera  == this->scene_graph.all_cameras.end()) // couldn't find from existing pool
		return false;

  InstanceCamera instance_camera;
  instance_camera.abstract_camera_ref = camera->first;
  node.instance_cameras.push_back(instance_camera);

  Transformation t;
  t.type = Transformation::LookAt;
  Point3 eyePos(node.local_matrix.getTranslation());
  Point3 lookAtPos(0,0,0);
  Vector3 upVec(0,0,0);
	if(this->up_axis == UPAXISTYPE_Z_UP)
  {
    lookAtPos = Point3(node.local_matrix.getTranslation().yAxis());
    upVec.setZ(1.0f);
  }
	else if(this->up_axis == UPAXISTYPE_X_UP)
  {
    lookAtPos = Point3(node.local_matrix.getTranslation().zAxis());
    upVec.setX(1.0f);
  }

  t.matrix = inverse(Matrix4::lookAt(eyePos, lookAtPos, upVec));
  node.local_matrix = t.matrix;
  node.transformations.push_back(t);

  return true;
}
