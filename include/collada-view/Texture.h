#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <SDL_image.h>
#include <map>
#include <dom/domAsset.h>
#include <boost/filesystem.hpp>
#include "comdefs.h"

using namespace boost;


struct Image
{
  Image() : image(NULL), should_flip(false) {}

  SDL_Surface *image;
  bool should_flip;

  struct ImageID
  {
    std::string name;
    std::string doc_uri;
    bool operator < (const ImageID &rhs) const {return name == rhs.name ? (doc_uri < rhs.doc_uri) : (name < rhs.name);}
  };
  typedef std::map<ImageID, Image> ImageList;
};

Image::ImageList::iterator ReadImage(LoggerFuncT &printStatusMessage, 
                                     Image::ImageList &all_images, 
                                     domImageRef dom_image, 
                                     const filesystem::path &dir);


#endif // __TEXTURE_H
