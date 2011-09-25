#include "Scene.h"
#include <dae.h>
#include <dom/domNode.h>
#include <dom/domGeometry.h>
#include "colladautils.h"


size_t 
SetVertexData(const Offsets &offset, Geometry &geometry, const domListOfUInts &values, size_t i)
{
	size_t index = size_t(values[i*offset.max_offset + offset.position_offset]);
	
  geometry.skin_idx_list.push_back(index);
  /*
  Point3 point(float((*offset.position_floats)[index * 3 + 0]),
               float((*offset.position_floats)[index * 3 + 1]),
               float((*offset.position_floats)[index * 3 + 2]));
  geometry.points.push_back(point);
  */
  geometry.points.push_back(float((*offset.position_floats)[index * 3 + 0]));
  geometry.points.push_back(float((*offset.position_floats)[index * 3 + 1]));
  geometry.points.push_back(float((*offset.position_floats)[index * 3 + 2]));

	if(offset.normal_offset != size_t(-1))
	{
		index = size_t(values[i*offset.max_offset + offset.normal_offset]);
    /*
    Vector3 normal(float((*offset.normal_floats)[index * 3 + 0]),
                   float((*offset.normal_floats)[index * 3 + 1]),
                   float((*offset.normal_floats)[index * 3 + 2]));
    geometry.normals.push_back(normal);
    */
    geometry.normals.push_back(float((*offset.normal_floats)[index * 3 + 0]));
    geometry.normals.push_back(float((*offset.normal_floats)[index * 3 + 1]));
    geometry.normals.push_back(float((*offset.normal_floats)[index * 3 + 2]));
	}

	if(offset.texture1_offset != size_t(-1))
	{
		index = size_t(values[i*offset.max_offset + offset.texture1_offset]);
    /*
    Geometry::TexCoord t(float((*offset.texture1_floats)[index * 2 + 0]),
                         float((*offset.texture1_floats)[index * 2 + 1]));
    geometry.tex_coords[0].push_back(t);
    */
    geometry.tex_coords[0].push_back(float((*offset.texture1_floats)[index * 2 + 0]));
    geometry.tex_coords[0].push_back(float((*offset.texture1_floats)[index * 2 + 1]));
	}

  return geometry.points.size()/3 - 1;
}


void 
BuildPolyList(Geometry &geometry, domPolylist *dom_polylist)
{
	geometry.polygons_list.push_back(Polygons());
  Polygons &polygons = geometry.polygons_list.back();

	const domInputLocalOffset_Array &inputs = dom_polylist->getInput_array();
	const Offsets offsets(inputs);

  const domListOfUInts &vcount_array = dom_polylist->getVcount()->getValue();
	const domPRef p = dom_polylist->getP();

	size_t vertex_start_index = 0;
	for(size_t i = 0; i < vcount_array.getCount(); i++)
	{		
		const size_t vcnt = (size_t)vcount_array[i];
		polygons.index_vector.push_back(PolyGroup::IndexVector());
		PolyGroup::IndexVector &vertices = polygons.index_vector.back();
		vertices.reserve(vcnt);
		for(size_t j = 0; j < vcnt; ++j)
		{
      const size_t idx = SetVertexData(offsets, geometry, p->getValue(), vertex_start_index + j);
			vertices.push_back(idx);
		}
		vertex_start_index += vcnt;
	}
}


void 
BuildPolygons(Geometry &geometry, domPolygons *dom_polygons)
{
	geometry.polygons_list.push_back(Polygons());
  Polygons &polygons = geometry.polygons_list.back();

	const domInputLocalOffset_Array &inputs = dom_polygons->getInput_array();
	const Offsets offsets(inputs);
	
	const domP_Array &p = dom_polygons->getP_array();
	for(size_t i = 0; i < p.getCount(); ++i)
	{
    const domListOfUInts &plist = p[i]->getValue();
		const size_t vcount = plist.getCount() / offsets.max_offset;
    polygons.index_vector.push_back(PolyGroup::IndexVector());
		PolyGroup::IndexVector &vertices = polygons.index_vector.back();
		vertices.reserve(vcount);
		for(size_t j = 0; j < vcount; ++j)
		{
			const size_t idx = SetVertexData(offsets, geometry, plist, j);
      vertices.push_back(idx);
		}
	}
}


void 
BuildTriStrips(Geometry &geometry, domTristrips *dom_tristrips)
{
  geometry.tristrips_list.push_back(TriStrips());
  TriStrips &tristrips = geometry.tristrips_list.back();

  // Prepare data
  const domInputLocalOffset_Array &inputs = dom_tristrips->getInput_array();
  const Offsets offsets(inputs);

  // Set index, they all have the same index since we process 
  // deindexer conditioner
  const domP_Array &p = dom_tristrips->getP_array();
  for(size_t i = 0; i < p.getCount(); ++i)
  {
    const domListOfUInts &plist = p[i]->getValue();
    const size_t vcount = plist.getCount() / offsets.max_offset;
    tristrips.index_vector.push_back(PolyGroup::IndexVector());
    PolyGroup::IndexVector &strips = tristrips.index_vector.back();
    strips.reserve(vcount);
    for(size_t j = 0; j < vcount; ++j)
    {
      const size_t idx = SetVertexData(offsets, geometry, plist, j);
      strips.push_back(idx);
    }
  }
}


void 
BuildTriFans(Geometry &geometry, domTrifans *dom_trifans)
{
  geometry.trifans_list.push_back(TriFans());
  TriFans &trifans = geometry.trifans_list.back();

  // prepare data
  const domInputLocalOffset_Array &inputs = dom_trifans->getInput_array();
  const Offsets offsets(inputs);

  // set index, they all have the same index since we process deindexer conditioner
  const domP_Array &p = dom_trifans->getP_array();
  for(size_t i = 0; i < p.getCount(); ++i)
  {		
    const domListOfUInts &plist = p[i]->getValue();
    const size_t vcount = plist.getCount() / offsets.max_offset;
    trifans.index_vector.push_back(PolyGroup::IndexVector());
    PolyGroup::IndexVector &fans = trifans.index_vector.back();
    fans.reserve(vcount);
    for(size_t j = 0; j < vcount; ++j)
    {
      const size_t idx = SetVertexData(offsets, geometry, plist, j);
      fans.push_back(idx);
    }
  }
}


void 
BuildTriangles(Geometry &geometry, domTriangles *dom_triangles, SceneGraph &scene_graph)
{
  geometry.triangles_list.push_back(Triangles());
  Triangles &triangles = geometry.triangles_list.back();
  
  triangles.material.name = dom_triangles->getMaterial();
  triangles.material.doc_uri = dom_triangles->getDocumentURI()->getURI();

	// prepare data
	const domInputLocalOffset_Array &inputs = dom_triangles->getInput_array();
	const Offsets offsets(inputs);

	// set index, they all have the same index since we process deindexer conditioner
	const domListOfUInts &p = dom_triangles->getP()->getValue();
  triangles.index_vector.push_back(PolyGroup::IndexVector());
	PolyGroup::IndexVector &vertices = triangles.index_vector.back();
  const size_t vcount = size_t(dom_triangles->getCount() * 3);
  vertices.reserve(vcount);
	for(size_t i = 0; i < vcount; ++i)
	{
    const size_t idx = SetVertexData(offsets, geometry, p, i);
		vertices.push_back(idx);
	}
}


void 
BuildLines(Geometry &geometry, domLines *dom_lines)
{
  geometry.triangles_list.push_back(Lines());
  Lines &lines = geometry.lines_list.back();

  // prepare data
  const domInputLocalOffset_Array &inputs = dom_lines->getInput_array();
  const Offsets offsets(inputs);

  // set index, they all have the same index since we process deindexer conditioner
  const domListOfUInts &p = dom_lines->getP()->getValue();

  lines.index_vector.push_back(PolyGroup::IndexVector());
  PolyGroup::IndexVector &vertices = lines.index_vector.back();
  const size_t vcount = size_t(dom_lines->getCount() * 2);
  vertices.reserve(vcount);
  for(size_t i = 0; i < vcount; ++i)
  {
    const size_t idx = SetVertexData(offsets, geometry, p, i);
    vertices.push_back(idx);
  }
}


void 
BuildLineStrips(Geometry &geometry, domLinestrips *dom_linestrips)
{
  geometry.linestrips_list.push_back(Linestrips());
  Linestrips &linestrips = geometry.linestrips_list.back();

	// prepare data
	const domInputLocalOffset_Array &inputs = dom_linestrips->getInput_array();
	const Offsets offsets(inputs);

	const domP_Array &p = dom_linestrips->getP_array();
	for(size_t i=0; i < p.getCount(); ++i)
	{
    const domListOfUInts &plist = p[i]->getValue();
    const size_t vcount = plist.getCount() / offsets.max_offset;
    linestrips.index_vector.push_back(PolyGroup::IndexVector());
    PolyGroup::IndexVector &strips = linestrips.index_vector.back();
    strips.reserve(vcount);
		for(size_t j = 0; j < vcount; ++j)
		{
			const size_t idx = SetVertexData(offsets, geometry, plist, j);
			strips.push_back(idx);
		}
	}
}


void 
ParseGeometry(Geometry &new_geo, domGeometry *dom_geometry, SceneGraph &scene_graph)
{
  size_t i;
  size_t count;
	const domMesh *mesh_element = dom_geometry->getMesh();

	// Not sure if we should get primitives by groups or by whatever comes first, 
  // I think it shouldn't matter, let's confirm later.

  const domPolylist_Array &pla = mesh_element->getPolylist_array();
	count = pla.getCount();
	for(i = 0; i < count; ++i)
		BuildPolyList(new_geo, pla[i]);

	const domPolygons_Array &pa = mesh_element->getPolygons_array();
	count = pa.getCount();
	for(i = 0; i < count; ++i)
		BuildPolygons(new_geo, pa[i]);

	const domTriangles_Array &ta = mesh_element->getTriangles_array();
	count = ta.getCount();
	for(i = 0; i < count; ++i)
		BuildTriangles(new_geo, ta[i], scene_graph);

	const domTristrips_Array &tsa = mesh_element->getTristrips_array();
	count = tsa.getCount();
	for(i = 0; i < count ; ++i)
		BuildTriStrips(new_geo, tsa[i]);

	const domTrifans_Array &tfa = mesh_element->getTrifans_array();
	count = tfa.getCount();
	for(i = 0; i < count ; ++i)
		BuildTriFans(new_geo, tfa[i]);

	const domLines_Array &la = mesh_element->getLines_array();
	count = la.getCount();
	for(i = 0; i < count ; ++i)
		BuildLines(new_geo, la[i]);

	const domLinestrips_Array &lsa = mesh_element->getLinestrips_array();
	count = lsa.getCount();
	for(i = 0; i < count ; ++i)
		BuildLineStrips(new_geo, lsa[i]);
/*
	if (_CrtRender.UsingVBOs())
	{
		for(i = 0; i <newGeo->Groups.size() ; ++i)
			newGeo->Groups[i]->SetVBOs();

		newGeo->VBOIDs[eGeoPoints] = _CrtRender.GenerateVBO();
		_CrtRender.CopyVBOData(GL_ARRAY_BUFFER, newGeo->VBOIDs[eGeoPoints],newGeo->Points, newGeo->vertexcount*3*sizeof(CrtFloat));

		newGeo->VBOIDs[eGeoNormals] = _CrtRender.GenerateVBO();
		_CrtRender.CopyVBOData(GL_ARRAY_BUFFER, newGeo->VBOIDs[eGeoNormals],newGeo->Normals, newGeo->vertexcount*3*sizeof(CrtFloat));

		newGeo->VBOIDs[eGeoTexCoord0] = _CrtRender.GenerateVBO();
		_CrtRender.CopyVBOData(GL_ARRAY_BUFFER, newGeo->VBOIDs[eGeoTexCoord0],newGeo->TexCoords[0], newGeo->vertexcount*2*sizeof(CrtFloat));
	}
*/
}


Geometry::GeometryList::iterator 
Scene::readGeometry(domGeometryRef dom_geometry)
{
  xsID gid = dom_geometry->getId();
	if(gid == NULL) 
    return this->scene_graph.all_geometries.end();

  const Geometry::GeometryID geometry_key = 
    {gid, dom_geometry->getDocumentURI()->getURI()};
  Geometry::GeometryList::iterator geometry = this->scene_graph.all_geometries.find(geometry_key);
	if(geometry != this->scene_graph.all_geometries.end()) // geometry is found
		return geometry;

	this->scene_graph.printStatusMessage(std::string("  add new Geometry ") + gid);

	// See what kind of data is in the geometry (there can be only one)
	domAsset *assetElement = dom_geometry->getAsset();
	domMesh *meshElement = dom_geometry->getMesh();
	domConvex_mesh *convexMeshElement = dom_geometry->getConvex_mesh();
	const domExtra_Array &extraElement = dom_geometry->getExtra_array();
	domSpline *splineElement = dom_geometry->getSpline();

	if(assetElement)
		this->scene_graph.printStatusMessage(std::string("  ") + gid + " has an <asset> which is not supported, skipped it.");
	else if(convexMeshElement)
		this->scene_graph.printStatusMessage(std::string("  ") + gid + " has a <convex_mesh> which is not supported, skipped it.");
	else if(extraElement.getCount())
		this->scene_graph.printStatusMessage(std::string("  ") + gid + " has an <extra> which is not supported, skipped it.");
	else if(splineElement)
		this->scene_graph.printStatusMessage(std::string("  ") + gid + " has a <spline> which is not supported, skipped it.");

	if(meshElement == NULL)
		return this->scene_graph.all_geometries.end();

	// Allocate space for the new geometry object 
  bool inserted;
	tie(geometry, inserted) = this->scene_graph.all_geometries.insert(std::make_pair(geometry_key, Geometry()));
  ParseGeometry(geometry->second, dom_geometry, this->scene_graph);

  return geometry;
}


bool 
Scene::readInstanceGeometry(Node &node, domInstance_geometryRef instance)
{
	// Find the <geometry> the <instance_geometry> is pointing at (there can be only one)
	// by searching the Geometries list in the scene.
	xsAnyURI &urltype = instance->getUrl();
	urltype.resolveElement();
	domElement *element = (domElement*)urltype.getElement();
	if(element == NULL) // this instance geometry is not found skip to the next one
		return false;

	const Geometry::GeometryList::iterator geo = this->readGeometry((domGeometry*)element);
	if(geo == this->scene_graph.all_geometries.end()) // couldn't find from existing pool of geometries
		return false;

  node.instance_geometries.push_back(InstanceGeometry());
	InstanceGeometry &instance_geometry = node.instance_geometries.back();
	instance_geometry.abstract_geometry_ref = geo->first;

	const domBind_material *bindMaterial = instance->getBind_material();
	if(bindMaterial)
	{
		// Get the <technique_common>
		const domBind_material::domTechnique_common *techniqueCommon = bindMaterial->getTechnique_common();
		if(techniqueCommon)
		{
			// Get the <instance_material>s
			const domInstance_material_Array &instanceMaterialArray = techniqueCommon->getInstance_material_array();
			for(size_t j = 0; j < instanceMaterialArray.getCount(); ++j)
			{
        this->readInstanceMaterial(instance_geometry, instanceMaterialArray[j]);
			}
		}
	}

	return true;
}
