#ifndef __GEOMETRY_H
#define __GEOMETRY_H

#include <map>
#include <string>
#include <vector>
#include <LinearMath/btAlignedObjectArray.h>
#include <vectormath/vmInclude.h>
#include "Material.h"
#include "PolyGroups.h"

using namespace Vectormath::Aos;

// It probably should not be hardcoded but 
// queried at startup
#define MAX_TEX_COORDS 8

struct Geometry
{
	typedef std::vector<float> PointList;
	typedef std::vector<float> Vector3List;
  //typedef std::pair<float, float> TexCoord;
  //typedef std::vector<TexCoord> TexCoordList;
  typedef std::vector<float> TexCoordList;
  typedef std::vector<size_t> SkinIdxList;

  PointList points;
	Vector3List normals;
//	Vec3f *Tangents;
//	Color4f *Colors; 
	TexCoordList tex_coords[MAX_TEX_COORDS];
//	Weight *Weights;
  // We need this because we deindex the vertices. it store the original index.
  // We need the original index to access the right skin index 
	SkinIdxList	skin_idx_list;

  typedef std::vector<Polygons> PolygonsList;
  typedef std::vector<Triangles> TrianglesList;
  typedef std::vector<Lines> LinesList;
  typedef std::vector<Linestrips> LinestripsList;
  typedef std::vector<TriStrips> TriStripsList;
  typedef std::vector<TriFans> TriFansList;

  PolygonsList polygons_list;
  TrianglesList triangles_list;
  LinesList lines_list;
  LinestripsList linestrips_list;
  TriStripsList tristrips_list;
  TriFansList trifans_list;

  struct GeometryID
  {
    std::string name;
    std::string doc_uri;
    bool operator < (const GeometryID &rhs) const {return name == rhs.name ? (doc_uri < rhs.doc_uri) : (name < rhs.name);}
  };
  typedef std::map<GeometryID, Geometry> GeometryList;
};


struct InstanceGeometry
{
  typedef std::vector <InstanceMaterial> MaterialInstances;
  MaterialInstances material_instances; /**< list of material
					   instances in the
					   <technique_common> */ 
  Geometry::GeometryList::key_type abstract_geometry_ref; /**< The
				 abstract geometry where the original
				 data is stored */ 
};


#endif // __GEOMETRY_H
