#include "colladautils.h"

#ifndef WIN32
#define _stricmp strcasecmp
#endif


Offsets::Offsets(const domInputLocalOffset_Array &inputs)
  : max_offset(0),
    position_offset(-1),
    normal_offset(-1),
    texture1_offset(-1),
    position_floats(NULL),
    normal_floats(NULL),
    texture1_floats(NULL)
{
  size_t i;
  // inputs with offsets
  for(i = 0; i < inputs.getCount(); ++i)
  {
    size_t thisoffset = (size_t)inputs[i]->getOffset();
    if(max_offset < thisoffset)
      ++max_offset;

    domSource *source = (domSource*)(domElement*)inputs[i]->getSource().getElement();
    if(_stricmp("VERTEX", inputs[i]->getSemantic()) == 0)
    {
      position_offset = thisoffset;
    } else if(_stricmp("NORMAL", inputs[i]->getSemantic()) == 0)
    {
      normal_offset = thisoffset;
      normal_floats = & source->getFloat_array()->getValue();
    } else if(_stricmp("TEXCOORD", inputs[i]->getSemantic()) == 0)
    {
      texture1_offset = thisoffset;
      texture1_floats = & source->getFloat_array()->getValue();
    }
  }
  ++max_offset;

  // inputs without offsets in vertices
  domMesh *mesh = (domMesh*)inputs[0]->getParentElement()->getParentElement();
  domVertices *vertices = mesh->getVertices();
  domInputLocal_Array &vertices_inputs = vertices->getInput_array();
  for(i = 0; i < vertices_inputs.getCount(); ++i)
  {
    domSource *source = (domSource*)(domElement*)vertices_inputs[i]->getSource().getElement();
    if(_stricmp("POSITION", vertices_inputs[i]->getSemantic()) == 0)
    {
      position_floats = & source->getFloat_array()->getValue();
    } else if(_stricmp("NORMAL", vertices_inputs[i]->getSemantic()) == 0)
    {
      normal_floats = & source->getFloat_array()->getValue();
      normal_offset = position_offset;
    } else if(_stricmp("TEXCOORD", vertices_inputs[i]->getSemantic()) == 0)
    {
      texture1_floats = & source->getFloat_array()->getValue();
      texture1_offset = position_offset;
    }
  }
}


const char *
CheckString(const char *s)
{
  return (s == NULL ? "" : s);
}


size_t 
getMaxOffset(const domInputLocalOffset_Array &input_array)
{
	size_t maxOffset = 0;
	for(size_t i = 0; i < input_array.getCount(); i++)
		if(input_array[i]->getOffset() > maxOffset)
			maxOffset = (size_t)(input_array[i]->getOffset());
	return maxOffset;
} 
