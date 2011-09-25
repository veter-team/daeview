/* Copyright (c) 2010 Andrey Nechypurenko
   See the file LICENSE for copying permission. 
*/

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <dae.h>
#include <dom/domCOLLADA.h>
#include <dom/domAsset.h>
#include "Texture.h"
#include "Scene.h"
#include "triangulation.h"
#include "deindexer.h"
#include "colladautils.h"


Scene::Scene() 
  : collada(NULL), 
    up_axis(UPAXISTYPE_Y_UP)
{
}


Scene::~Scene()
{
  this->scene_graph.all_animations.clear();

  if(this->collada)
    delete(this->collada);
}


void 
Scene::load(const filesystem::path &file)
{
  size_t i;
  std::string message;

  if(!filesystem::exists(file))
    throw std::runtime_error(std::string("File does not exists:") + file.string());

  this->collada = new DAE;

  message = "Start loading COLLADA DOM from ";
  message += file.string();
  this->scene_graph.printStatusMessage(message); 
  this->dae_file_name = file;

  // load with full path 
  domCOLLADA *dom = this->collada->open(file.string());
  if(!dom)
    {
      delete this->collada;	
      throw std::runtime_error(std::string("Error loading the COLLADA file ") 
			  + file.string() 
			  + ". Make sure it is COLLADA 1.4 or greater");
    }

  this->scene_graph.printStatusMessage("Begin conditioning");

  //if(kmzcleanup(this->collada, true))
  //  std::cout << "  kmzcleanup complete\n";
  int res = 0;

  this->scene_graph.printStatusMessage("  triangulating");
  res = triangulate(this->collada);
	if(res)
  {
    std::ostringstream os;
    os << "  triangulation returns error " << res << std::ends;
    this->scene_graph.printStatusMessage(os.str());
  }
  else
    this->scene_graph.printStatusMessage(std::string("  triangulation complete"));
/*
  this->scene_graph.printStatusMessage(std::string("  deindexing"));
  res = deindex(this->collada);
	if(res)
  {
    std::ostringstream os;
    os << "  deindexer returns error " << res << std::ends;
    this->scene_graph.printStatusMessage(os.str());
  }
  else
    this->scene_graph.printStatusMessage(std::string("  deindexing complete"));
*/
  this->scene_graph.printStatusMessage(std::string("Finish conditioning."));

  // Need to get the asset tag which will determine what vector x y or z is up.  Typically y or z. 
  domAssetRef asset = dom->getAsset();
  this->scene_graph.printStatusMessage(std::string("File information:"));
  const domAsset::domContributor_Array &contributors = asset->getContributor_array();
  for(i = 0; i < contributors.getCount(); ++i)
  {
    domAsset::domContributorRef c = contributors.get(i);
    this->scene_graph.printStatusMessage(std::string("  author:") + c->getAuthor()->getCharData());
    this->scene_graph.printStatusMessage(std::string("  authoring tool:") + c->getAuthoring_tool()->getCharData());
  }
  if(asset->getCreated())
    this->scene_graph.printStatusMessage(std::string("  created: ") + asset->getCreated()->getCharData());
  if(asset->getModified())
    this->scene_graph.printStatusMessage(std::string("  modified: ") + asset->getModified()->getCharData());
  if(asset->getUnit())
  {
    std::ostringstream os;
    os << "  units: " << asset->getUnit()->getMeter() << " meter (" << asset->getUnit()->getAttribute("name") << ")";
    os << std::ends;
    this->scene_graph.printStatusMessage(os.str());
  }
  if(asset->getUp_axis())
    {
      domAsset::domUp_axis *up = dom->getAsset()->getUp_axis();
      if(up)
        this->up_axis = up->getValue();
      switch(this->up_axis)
        {
        case UPAXISTYPE_X_UP:
          this->scene_graph.printStatusMessage(std::string("  X axis is UP axis.")); 
          break; 

        case UPAXISTYPE_Y_UP:
          this->scene_graph.printStatusMessage(std::string("  Y axis is UP axis.")); 
          break;

        case UPAXISTYPE_Z_UP:
          this->scene_graph.printStatusMessage(std::string("  Z axis is UP axis.")); 
          break; 

        default:
          break; 
        }
  	}

  this->scene_graph.printStatusMessage("Building libraries");
 	
  // Load the image for the default texture.

  const Image::ImageID image_key = {"default", ""};
  bool inserted;
  Image::ImageList::iterator img_iter;
  tie(img_iter, inserted) = this->scene_graph.all_images.insert(std::make_pair(image_key, Image()));

  Image &img = img_iter->second;
  img.image = IMG_Load("default.tga");
  if(!img.image)
  {
    scene_graph.all_images.erase(image_key);
    this->scene_graph.printStatusMessage("Can not load default.tga for the default texture.");
  }

  this->scene_graph.printStatusMessage("  Load image libraries");
  const domLibrary_images_Array &ia = dom->getLibrary_images_array();
	for(i = 0; i < ia.getCount(); ++i)
		this->readImageLibrary(ia[i]);

  this->scene_graph.printStatusMessage("  Load effect libraries");
  const domLibrary_effects_Array &ea = dom->getLibrary_effects_array();
	for(i = 0; i < ea.getCount(); i++)
		this->readEffectLibrary(ea[i]);

  this->scene_graph.printStatusMessage("  Load material libraries");
  const domLibrary_materials_Array &ma = dom->getLibrary_materials_array();
	for(i = 0; i < ma.getCount(); i++)
		this->readMaterialLibrary(ma[i]);

  this->scene_graph.printStatusMessage("  Load animation libraries");
  const domLibrary_animations_Array &aa = dom->getLibrary_animations_array();
	for(i = 0; i < aa.getCount(); i++)
		this->readAnimationLibrary(aa[i]);

	// Find the scene we want
	domCOLLADA::domSceneRef domScene = dom->getScene();
	daeElement* defaultScene = NULL;
	if (domScene)
		if (domScene->getInstance_visual_scene())
			if (domScene->getInstance_visual_scene())
				defaultScene = domScene->getInstance_visual_scene()->getUrl().getElement();
	if(defaultScene)
		this->readScene((domVisual_scene*)defaultScene);

	// If no lights were loaded, we need to make one so the scene won't be totally black
	if(this->scene_graph.all_lights.empty())
	{
		// new Light  
		this->scene_graph.printStatusMessage("Scene: no lights were loaded. Creating a default light");
    const Light::LightID light_key = 
      {"no_light_in_scene_default_light", dom->getDocumentURI()->getURI()};
    bool inserted;
    Light::LightList::iterator light;
    tie(light, inserted) = scene_graph.all_lights.insert(std::make_pair(light_key, Light()));
    Light &default_light = light->second;
		default_light.type = Light::DIRECTIONAL;
		default_light.color = Color4f(1, 1, 1, 1);

		// new Node
		this->scene_graph.printStatusMessage("Scene: no instance_light found creating a node with an instance");
    this->scene_graph.insertNode(this->scene_graph.root,
                                 "no_light_in_scene_default_node",
                                 "no_light_in_scene_default_node",
                                 "NONE");
    // Read node transformations
    Node &current_node = *this->scene_graph.all_nodes.find("no_light_in_scene_default_node");

    current_node.transformations.push_back(Transformation());
    Transformation &transform = 
      current_node.transformations.at(current_node.transformations.size() - 1);
		transform.type = Transformation::Translate; 
		const Vector3 trans(-40.0, 40.0, 0.0);
    transform.transform = Transform3::translation(trans);

		// new InstanceLight
    InstanceLight instance_light;
    instance_light.abstract_light_ref = light->first;
    current_node.instance_lights.push_back(instance_light);
    this->scene_graph.light_nodes.push_back("no_light_in_scene_default_node"); 
  }

  if(!this->scene_graph.all_cameras.empty())
  {
    // Search for the first camera node
    Node::NodeMap &all_nodes = this->scene_graph.all_nodes;
    for(int n = 0; n < all_nodes.size(); ++n)
    {
      Node *node = all_nodes.getAtIndex(n);
      if(node->instance_cameras.size() > 0)
      {
        this->scene_graph.active_camera_info = std::make_pair(node, &(node->instance_cameras[0]));
        break;
      }
    }
  }
  else
	{
		this->scene_graph.printStatusMessage( "Scene: create a default camera and it is the first camera to use");
		// new Camera
    const Camera::CameraID camera_key = 
      {"no_camera_in_scene_default_camera", dom->getDocumentURI()->getURI()};

	  // Make the camera
    bool inserted;
    Camera::CameraList::iterator camera;
    tie(camera, inserted) = this->scene_graph.all_cameras.insert(std::make_pair(camera_key, Camera()));
    Camera &default_camera = camera->second;
    default_camera.Xfov = 45.0f;
    default_camera.Yfov = 45.0f;

		this->scene_graph.printStatusMessage( "Scene: creating a node with an instance of default camera");
		// new Node
    this->scene_graph.insertNode(this->scene_graph.root,
                                 "no_camera_in_scene_default_node",
                                 "no_camera_in_scene_default_node",
                                 "NONE");
    // Read node transformations
    Node &current_node = *this->scene_graph.all_nodes.find("no_camera_in_scene_default_node");

    // Calculate approximate bounding box for the model
    Vector3 max(0,0,0);
    Vector3 min(0,0,0);
    for(Geometry::GeometryList::const_iterator g = this->scene_graph.all_geometries.begin();
      g != this->scene_graph.all_geometries.end(); ++g)
    {
      // Points are stored as x/y/z tripples within this array
      for(Geometry::PointList::const_iterator p = g->second.points.begin();
        p != g->second.points.end(); ++p)
      {
        float f = *p;
        // X
        if(*p > max.getX())
          max.setX(*p);
        else if(*p < min.getX())
          min.setX(*p);
        // Y
        ++p;
        f = *p;
        if(*p > max.getY())
          max.setY(*p);
        else if(*p < min.getY())
          min.setY(*p);
        // Z
        ++p;
        f = *p;
        if(*p > max.getZ())
          max.setZ(*p);
        else if(*p < min.getZ())
          min.setZ(*p);
      }
    }

    default_camera.ZNear = 1.0f;
		default_camera.ZFar = 1000.0f;

    current_node.transformations.push_back(Transformation());
    Transformation &transform = 
      current_node.transformations.at(current_node.transformations.size() - 1);
    transform.type = Transformation::LookAt;
    const Point3 eyePos(max.getX() * 0.5f, max.getY() * 0.5f, max.getZ() * 0.5f);
    const Point3 lookAtPos(min.getX(), min.getY(), min.getZ());
    Vector3 upVec;
    upVec.setY(0);
		if(this->up_axis == UPAXISTYPE_Z_UP)
    {
      upVec.setX(0);
      upVec.setZ(1.0f);
    }
		else if(this->up_axis == UPAXISTYPE_X_UP)
    {
      upVec.setX(1.0f);
      upVec.setZ(0);
    }
    // Store transformation
    transform.matrix = inverse(Matrix4::lookAt(eyePos, lookAtPos, upVec));
    current_node.local_matrix *= transform.matrix;

    // new InstanceCamera
    InstanceCamera instance_camera;
    instance_camera.abstract_camera_ref = camera->first;
    current_node.instance_cameras.push_back(instance_camera);
    this->scene_graph.active_camera_info = std::make_pair(&current_node,
      &(current_node.instance_cameras.at(current_node.instance_cameras.size() - 1)));
	}

  this->scene_graph.printStatusMessage(std::string("COLLADA_DOM runtime database initialized from ") + file.filename());
}


SceneGraph::Vertex 
Scene::readNode(const domNodeRef node, SceneGraph::Vertex &parent)
{
  // just to experiment with fonts
  bool is_font_node = false;
  size_type pos = std::string(node->getId()).find(SceneGraph::font_name);
  if(pos != std::string::npos)
    is_font_node = true;

  SceneGraph::IdVertexMap::iterator findnode = this->scene_graph.id_vertex_map.find(node->getId());
  if(findnode != this->scene_graph.id_vertex_map.end())
    return findnode->second;

  this->scene_graph.printStatusMessage(std::string("  reading scene node ") + node->getID());
  size_t i;
  // Insert new node and connect to parent
  SceneGraph::NodeInfo new_node_info = {node->getId(), CheckString(node->getSid())};
  this->scene_graph.insertNode(parent,
                               CheckString(node->getName()),
                               node->getId(),
                               CheckString(node->getSid()));
  SceneGraph::node_id_map_t node_id_map = get(SceneGraph::node_info_t(), this->scene_graph.node_graph);
  // Read node transformations
  const SceneGraph::NodeInfo &parent_node_info = node_id_map[parent];
  const Node *parent_node = this->scene_graph.all_nodes.find(parent_node_info.id.c_str());
  Node &current_node = *this->scene_graph.all_nodes.find(new_node_info.id.c_str());
  current_node.is_font_node = is_font_node;
  SceneGraph::Vertex node_vertex = this->scene_graph.id_vertex_map.find(new_node_info.id)->second;

  this->readNodeTranforms(current_node, *parent_node, node);

  // Process Instance Geometries
  const domInstance_geometry_Array &geom_instances = node->getInstance_geometry_array();
	for(i = 0; i < geom_instances.getCount(); ++i)
		this->readInstanceGeometry(current_node, geom_instances[i]);

  // Process Instance Lights 
  const domInstance_light_Array &lia = node->getInstance_light_array();
	for(i = 0; i < lia.getCount(); ++i)
		this->readInstanceLight(current_node, lia[i]);
  if(!current_node.instance_lights.empty())
    this->scene_graph.light_nodes.push_back(new_node_info.id);

  // Process Instance Cameras 
  const domInstance_camera_Array &ica  = node->getInstance_camera_array();
	for(i = 0; i < ica.getCount(); ++i)
    this->readInstanceCamera(current_node, ica[i]);

  // Read in each child and recursively it's children 
  const domNode_Array &nodes = node->getNode_array();
  for(i = 0; i < nodes.getCount(); i++)
    this->readNode(nodes[i], node_vertex);

  // Read children <instance_nodes>, can be 0 or more
  const domInstance_node_Array &instance_nodes = node->getInstance_node_array();
  for(i = 0; i < instance_nodes.getCount(); i++)
  {
    domInstance_node *instance_node = instance_nodes[i];
    domNode *urlnode = (domNode*)(domElement*)instance_node->getUrl().getElement();
    if(urlnode)
      this->readNode(urlnode, node_vertex);
  }

  return node_vertex;
}


void 
Scene::readScene(domVisual_sceneRef scene)
{
  const std::string scene_name = CheckString(scene->getName());
  std::ostringstream os;
  os << "Reading Collada scene '" << scene_name << "'";
  os << std::ends;
	this->scene_graph.printStatusMessage(os.str()); 	

  bool inserted;
  SceneGraph::IdVertexMap::iterator pos;
  SceneGraph::node_id_map_t node_id = get(SceneGraph::node_info_t(), this->scene_graph.node_graph);
  tie(pos, inserted) = this->scene_graph.id_vertex_map.insert(std::make_pair(scene->getId(), SceneGraph::Vertex()));
  if(inserted)
  {
    this->scene_graph.root = add_vertex(this->scene_graph.node_graph);
    node_id[this->scene_graph.root].id = scene->getId();
    node_id[this->scene_graph.root].sid = "";
    pos->second = this->scene_graph.root;
    this->scene_graph.all_nodes.insert(scene->getID(), Node());
    this->scene_graph.all_nodes.find(scene->getID())->name = scene_name;
  } else
    this->scene_graph.root = pos->second;

	// recurse through the scene, read and add nodes 
  const domNode_Array &nodes = scene->getNode_array();
	for(size_t i = 0; i < nodes.getCount(); ++i)
	{
		this->readNode(nodes.get(i), this->scene_graph.root);
	}

  // calculate bounding boxes for font elements
  for(int j = 0; j < this->scene_graph.all_nodes.size(); ++j)
  {
    Node *n = this->scene_graph.all_nodes.getAtIndex(j);
    if(n->is_font_node)
      n->calcBoundingBox(this->scene_graph.all_geometries);
  }
}
