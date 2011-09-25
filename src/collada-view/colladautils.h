#ifndef __COLLADAUTILS_H
#define __COLLADAUTILS_H

#include <dom/domGeometry.h>

struct Offsets
{
	Offsets(const domInputLocalOffset_Array &inputs);

	size_t max_offset;
	size_t position_offset;
	size_t normal_offset;
	size_t texture1_offset;

	domListOfFloats *position_floats;
	domListOfFloats *normal_floats;
	domListOfFloats *texture1_floats;
};


const char *CheckString(const char *s);
size_t getMaxOffset(const domInputLocalOffset_Array &input_array);

#endif // __COLLADAUTILS_H
