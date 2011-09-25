#include "Scene.h"
#include <dae.h>
#include <dom/domCOLLADA.h>
#include <dom/domAsset.h>

#ifndef WIN32
#define _stricmp strcasecmp
#endif


Image::ImageList::iterator 
ReadImage(LoggerFuncT &printStatusMessage, 
          Image::ImageList &all_images, 
          domImageRef dom_image, 
          const filesystem::path &dir)
{
  xsID gid = dom_image->getId();
	if(gid == NULL) 
    return all_images.end();

  const Image::ImageID image_key = 
    {gid, dom_image->getDocumentURI()->getURI()};
  Image::ImageList::iterator image = all_images.find(image_key);
	if(image != all_images.end()) // image is found
		return image;
  
	printStatusMessage(std::string("  add new Image ") + gid);

	const domImage *image_element = dom_image.cast();
	if(!image_element)
    return all_images.end();

	// load the actual image passing in the current file name 
	// to first look relative to the current <file>_Textures
	// for the textures 
	const filesystem::path file_name(cdom::uriToNativePath(
		image_element->getInit_from()->getValue().str()));
  std::string full_path_name;
  if(!file_name.root_path().empty())
    full_path_name = file_name.string();
  else
    full_path_name = dir.string() + file_name.string();
	const filesystem::path full_path(full_path_name);

  bool inserted;
  Image::ImageList::iterator img_iter;
  tie(img_iter, inserted) = all_images.insert(std::make_pair(image_key, Image()));
  Image &img = img_iter->second;
  img.image = IMG_Load(full_path.native_file_string().c_str());
  std::string ext = full_path.extension();
  if(_stricmp(ext.c_str(), ".bmp") == 0
    || _stricmp(ext.c_str(), ".jpg") == 0
    || _stricmp(ext.c_str(), ".png") == 0)
    img.should_flip = true;
  else
    img.should_flip = false;

  if(!img.image)
  {
    all_images.erase(image_key);
    printStatusMessage(std::string("  can not load image from ") + full_path.native_file_string());
    return all_images.end();
  }

  return img_iter;
}


bool 
Scene::readImageLibrary(domLibrary_imagesRef lib)
{
  filesystem::path dir = this->dae_file_name.parent_path();
  const domImage_Array &ia = lib->getImage_array();
  for(size_t i = 0; i < ia.getCount(); ++i)
    ReadImage(this->scene_graph.printStatusMessage, this->scene_graph.all_images, ia[i], dir); 

  return true; 	 
}
