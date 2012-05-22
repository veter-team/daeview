#ifndef __POLYGROUPS_H
#define __POLYGROUPS_H

#include <vector>
#include "Material.h"


struct PolyGroup
{
  typedef std::vector<unsigned int> IndexVector;
  typedef std::vector<IndexVector> PolyIndexVector;

  PolyIndexVector index_vector;
  Material::MaterialList::key_type material;
};

typedef PolyGroup Polygons;
typedef PolyGroup Triangles;
typedef PolyGroup Lines;
typedef PolyGroup Linestrips;
typedef PolyGroup TriStrips;
typedef PolyGroup TriFans;


#endif // __POLYGROUPS_H
