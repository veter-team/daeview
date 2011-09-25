#include "deindexer.h"
#include "colladautils.h"
#include <dom/domGeometry.h>
#include <dom/domSkin.h>
#include <dom/domConstants.h>
#include <dom/domP.h>
#include <dae.h>
#include <map>
#include <set>

class SkinInfo
{
public:
	SkinInfo(domSkin::domVertex_weights * thisWeights, domUint inputnumbers);
	~SkinInfo();
	void AppendIndex(domUint i);
	void SetWeightsCount(domUint count) {weights->setCount(count);};
private:
	domUint vcountnumber;
	domUint * vcount;	// numbers of int for each vertices * numbers of inputs
	domUint ** v;		// the numbers
	domSkin::domVertex_weights::domVcountRef weightvcount;
	domSkin::domVertex_weights::domVRef weightv;
	domUint input_numbers;
	domSkin::domVertex_weights * weights;
};

SkinInfo::SkinInfo(domSkin::domVertex_weights * thisWeights, domUint inputnumbers)
{
	input_numbers = inputnumbers;
	weights = thisWeights;
	weightvcount = thisWeights->getVcount();
	weightv = thisWeights->getV();

	domListOfUInts vcountarray = weightvcount->getValue();
	domListOfInts varray = weightv->getValue();
	vcountnumber = vcountarray.getCount();
    domUint vnumber = varray.getCount();
	vcount = new domUint[(size_t) vcountnumber];
	v = new domUint*[(size_t)vcountnumber];
	size_t vindex = 0;
	for (size_t i=0; i<vcountnumber; i++)
	{
		vcount[i] = vcountarray[i];
		v[i] = new domUint[(size_t)(vcount[i] * inputnumbers)];
		for (domUint j=0; j< vcount[i] * inputnumbers; j++)
		{
			v[i][j] = varray[vindex];
			vindex ++;
		}
	}
	assert(vindex == vnumber);
	weightvcount->getValue().clear();
	weightv->getValue().clear();
}

SkinInfo::~SkinInfo()
{
	for (domUint i=0; i<vcountnumber; i++)
	{
		delete v[i];
	}
	delete v;
	delete vcount;
}

void SkinInfo::AppendIndex(domUint i)
{
	weightvcount->getValue().append(vcount[i]);
	for (domUint j=0; j< vcount[i] * input_numbers; j++)
	{
		weightv->getValue().append(v[i][j]);
	}
}

class VertexIndexes;
struct LessVertexIndexes;
typedef std::map<domElement*, domUint> IndexMap;
typedef std::set<VertexIndexes*, LessVertexIndexes> VertexSet;

class VertexIndexes
{
public:
	VertexIndexes();
	~VertexIndexes();
	void SetIndex(domElement * source, domUint index_value);
	IndexMap index_map;
	domUint new_index;
};

VertexIndexes::VertexIndexes()
{
	new_index = 0;
}

VertexIndexes::~VertexIndexes()
{
	index_map.clear();
}

struct LessVertexIndexes
{
	bool operator()(VertexIndexes * s1, VertexIndexes * s2)
	{
		IndexMap::iterator i;
		IndexMap::iterator j;
		for (i=s1->index_map.begin(); i!=s1->index_map.end(); i++)
		{
			for (j=s2->index_map.begin(); j!=s2->index_map.end(); j++)
			{
				if (i->first == j->first)
				{
					if (i->second == j->second)
						continue;
					else 
						return i->second < j->second;
				}
			}
		}
		return false;
	}
};

struct LessInNewIndex
{
	bool operator()(VertexIndexes * s1, VertexIndexes * s2)
	{
		return s1->new_index < s2->new_index;
	}
};


void VertexIndexes::SetIndex(domElement * source, domUint index_value)
{
	IndexMap::iterator i;
	for (i=index_map.begin(); i!=index_map.end(); i++)
	{
		if (i->first == source)
		{
			i->second = index_value;
			return;
		}
	}
	index_map[source] = index_value;
}


void MergeVertex(VertexIndexes * match_vertex, VertexIndexes *vertex)
{
	IndexMap::iterator srciter;
	for(srciter=vertex->index_map.begin(); srciter!=vertex->index_map.end(); srciter++)
	{
		match_vertex->index_map[srciter->first] = srciter->second;
	}
}


void ParseInputAndP(domInputLocalOffset_Array &input_array, domP * p, domPRef &newp, VertexSet & vertexset, domUint & vertexindex, domUint &maxoffset)
{
	std::map<domElement*, domUint> offsetmap;
	// set offsetmap<source_element_ptr, offset_number>
	for (size_t j=0; j<input_array.getCount(); j++)
	{
		xsAnyURI & uri = input_array[j]->getSource();
		uri.resolveElement();
		domElement * element = uri.getElement();
		offsetmap[element] = input_array[j]->getOffset();
		input_array[j]->setOffset(0);			// reset all input's offset to 0 since all inputs use the same vertex index
	}
	domListOfUInts & value = p->getValue();

	for (size_t j=0; j<value.getCount(); j=(size_t) (j+maxoffset+1))
	{
		VertexIndexes* vertex = new VertexIndexes();

		std::map<domElement*, domUint>::iterator iter;
		for (iter=offsetmap.begin(); iter!=offsetmap.end(); iter++)
		{
			vertex->SetIndex(iter->first, value[(size_t) (j+(iter->second))]);
		}
		std::pair<VertexSet::iterator,bool> result = vertexset.insert(vertex);
		if (result.second)
		{	// it is unique, not duplicate in set
//			printf("vertex is unique\n");
			vertex->new_index = vertexindex;
			newp->getValue().append(vertexindex);
			vertexindex++;
		} else
		{	// it is not unique, duplicate found in set
//			printf("vertex is not unique\n"); 
			VertexIndexes * match_vertex = *(result.first);
			newp->getValue().append(match_vertex->new_index);
			MergeVertex(match_vertex, vertex);
		}
	}
}

void ResetSource(domSource * newsource, domUint new_vertex_size)
{
	newsource->getTechnique_common()->getAccessor()->setCount(new_vertex_size);
	domUint stride = newsource->getTechnique_common()->getAccessor()->getStride();

	domFloat_arrayRef newfloat_array = newsource->getFloat_array();
	if (newfloat_array)
	{
		newfloat_array->setCount(new_vertex_size * stride);
		newfloat_array->getValue().setCount((size_t)(new_vertex_size * stride));
	}

	domInt_arrayRef newint_array = newsource->getInt_array();
	if (newint_array)
	{
		newint_array->setCount(new_vertex_size * stride);
		newint_array->getValue().setCount((size_t)(new_vertex_size * stride));
	}

	domName_arrayRef newname_array = newsource->getName_array();
	if (newname_array)
	{
		newname_array->setCount(new_vertex_size * stride);
		newname_array->getValue().setCount((size_t)(new_vertex_size * stride));
	}

	domIDREF_arrayRef newidref_array = newsource->getIDREF_array();
	if (newidref_array)
	{
		newidref_array->setCount(new_vertex_size * stride);
		newidref_array->getValue().setCount((size_t)(new_vertex_size * stride));
	}

	domBool_arrayRef newbool_array = newsource->getBool_array();
	if (newbool_array)
	{
		newbool_array->setCount(new_vertex_size * stride);
		newbool_array->getValue().setCount((size_t)(new_vertex_size * stride));
	}
}

void SetSource(domSource * oldsource, domSource * newsource, domUint oldindex, domUint newindex)
{
	domUint stride = oldsource->getTechnique_common()->getAccessor()->getStride();

	domFloat_arrayRef oldfloat_array = oldsource->getFloat_array();
	if (oldfloat_array)
	{
		domFloat_arrayRef newfloat_array = newsource->getFloat_array();
		for (size_t i=0; i<stride; i++)
		{
			newfloat_array->getValue().set((size_t)(newindex*stride+i), oldfloat_array->getValue()[(size_t)(oldindex*stride+i)]);
		}
	}

	domInt_arrayRef oldint_array = oldsource->getInt_array();
	if (oldint_array)
	{
		domInt_arrayRef newint_array = newsource->getInt_array();
		for (size_t i=0; i<stride; i++)
		{
			newint_array->getValue().set((size_t)(newindex*stride+i), oldint_array->getValue()[(size_t)(oldindex*stride+i)]);
		}
	}

	domName_arrayRef oldname_array = oldsource->getName_array();
	if (oldname_array)
	{
		domName_arrayRef newname_array = newsource->getName_array();
		for (size_t i=0; i<stride; i++)
		{
			newname_array->getValue().set((size_t)newindex, oldname_array->getValue()[(size_t)oldindex]);
		}
	}

	domIDREF_arrayRef oldidref_array = oldsource->getIDREF_array();
	if (oldidref_array)
	{
		domIDREF_arrayRef newidref_array = newsource->getIDREF_array();
		for (size_t i=0; i<stride; i++)
		{
			newidref_array->getValue().set((size_t)newindex, oldidref_array->getValue()[(size_t)oldindex]);
		}
	}

	domBool_arrayRef oldbool_array = oldsource->getBool_array();
	if (oldbool_array)
	{
		domBool_arrayRef newbool_array = newsource->getBool_array();
		for (size_t i=0; i<stride; i++)
		{
			newbool_array->getValue().set((size_t)newindex, oldbool_array->getValue()[(size_t)oldindex]);
		}
	}
}


int 
deindex(DAE *dae)
{
	domInt error = 0;
	std::vector<daeElement*> geometries = dae->getDatabase()->typeLookup(domGeometry::ID());

	for(std::vector<daeElement*>::iterator g = geometries.begin(); g != geometries.end(); ++g)
	{	// for each geometry
    domGeometry *geometry = (domGeometry*)(*g);
		domMesh *mesh = geometry->getMesh();
		if (mesh==NULL) continue;

		VertexSet vertexset;				// the set
		domUint vertexindex = 0;			// the next new index
//		domUint IndexMaxOffset = 0;

		domTriangles_Array & triangles_array = mesh->getTriangles_array();
		for (size_t i=0; i<triangles_array.getCount(); i++)
		{
			domTriangles * triangles = triangles_array[i];
			domInputLocalOffset_Array & input_array = triangles->getInput_array();
			domUint maxoffset = getMaxOffset(input_array);

			domP * p = triangles->getP();
			domPRef newp = (domP*) (domElement*) p->createElement("p");
			ParseInputAndP(input_array, p, newp, vertexset, vertexindex, maxoffset);

			// remove old p and add new p
			triangles->removeChildElement(p);
			triangles->placeElement(newp);
		}

		domTristrips_Array & tristrips_array = mesh->getTristrips_array();
		for (size_t i=0; i<tristrips_array.getCount(); i++)
		{
			domTristrips * tristrips = tristrips_array[i];
			domInputLocalOffset_Array & input_array = tristrips->getInput_array();
			domUint maxoffset = getMaxOffset(input_array);

			domP_Array & p_array = tristrips->getP_array();
			size_t p_array_count = p_array.getCount();
			for (size_t j=0; j<p_array_count; j++)
			{
				domP * p = p_array[0];
				domPRef newp = (domP*) (domElement*) p->createElement("p");
				ParseInputAndP(input_array, p, newp, vertexset, vertexindex, maxoffset);
				// remove old p and add new p
				tristrips->placeElement(newp);
				tristrips->removeChildElement(p);
			}
		}

		domTrifans_Array & trifans_array = mesh->getTrifans_array();
		for (size_t i=0; i<trifans_array.getCount(); i++)
		{
			domTrifans * trifans = trifans_array[i];
			domInputLocalOffset_Array & input_array = trifans->getInput_array();
			domUint maxoffset = getMaxOffset(input_array);

			domP_Array & p_array = trifans->getP_array();
			size_t p_array_count = p_array.getCount();
			for (size_t j=0; j<p_array_count; j++)
			{
				domP * p = p_array[0];
				domPRef newp = (domP*) (domElement*) p->createElement("p");
				ParseInputAndP(input_array, p, newp, vertexset, vertexindex, maxoffset);
				// remove old p and add new p
				trifans->placeElement(newp);
				trifans->removeChildElement(p);
			}
		}

		domPolygons_Array & polygons_array = mesh->getPolygons_array();
		for (size_t i=0; i<polygons_array.getCount(); i++)
		{
			domPolygons * polygons = polygons_array[i];
			domInputLocalOffset_Array & input_array = polygons->getInput_array();
			domUint maxoffset = getMaxOffset(input_array);

			domP_Array & p_array = polygons->getP_array();
			size_t p_array_count = p_array.getCount();
			for (size_t j=0; j<p_array_count; j++)
			{
				domP * p = p_array[0];
				domPRef newp = (domP*) (domElement*) p->createElement("p");
				ParseInputAndP(input_array, p, newp, vertexset, vertexindex, maxoffset);
				// remove old p and add new p
				polygons->placeElement(newp);
				polygons->removeChildElement(p);
			}
		}

		domPolylist_Array & polylist_array = mesh->getPolylist_array();
		for (size_t i=0; i<polylist_array.getCount(); i++)
		{
			domPolylist * polylist = polylist_array[i];
			domInputLocalOffset_Array & input_array = polylist->getInput_array();
			domUint maxoffset = getMaxOffset(input_array);

			domP * p = polylist->getP();
			domPRef newp = (domP*) (domElement*) p->createElement("p");
			ParseInputAndP(input_array, p, newp, vertexset, vertexindex, maxoffset);

			// remove old p and add new p
			polylist->removeChildElement(p);
			polylist->placeElement(newp);
		}

		domLines_Array & lines_array = mesh->getLines_array();
		for (size_t i=0; i<lines_array.getCount(); i++)
		{
			domLines * lines = lines_array[i];
			domInputLocalOffset_Array & input_array = lines->getInput_array();
			domUint maxoffset = getMaxOffset(input_array);

			domP * p = lines->getP();
			domPRef newp = (domP*) (domElement*) p->createElement("p");
			ParseInputAndP(input_array, p, newp, vertexset, vertexindex, maxoffset);

			// remove old p and add new p
			lines->removeChildElement(p);
			lines->placeElement(newp);
		}

		domLinestrips_Array & linestrips_array = mesh->getLinestrips_array();
		for (size_t i=0; i<linestrips_array.getCount(); i++)
		{
			domLinestrips * linestrips = linestrips_array[i];
			domInputLocalOffset_Array & input_array = linestrips->getInput_array();
			domUint maxoffset = getMaxOffset(input_array);

			domP_Array & p_array = linestrips->getP_array();
			size_t p_array_count = p_array.getCount();
			for (size_t j=0; j<p_array_count; j++)
			{
				domP * p = p_array[0];
				domPRef newp = (domP*) (domElement*) p->createElement("p");
				assert(newp);
				ParseInputAndP(input_array, p, newp, vertexset, vertexindex, maxoffset);
				// remove old p and add new p

				linestrips->placeElement(newp);
				linestrips->removeChildElement(p);
			}
		}

		domVertices * vertices = mesh->getVertices();
		if (vertices == 0)
		{
			printf("<vertices> not found int mesh, please run coherencytest\n");
			continue;
		}

		// setup map for new sources
		std::map<domSource*,domSource*> source_map;
		domSource_Array & source_array = mesh->getSource_array();
		domUint source_count = source_array.getCount();
		for(size_t i=0; i<source_count; i++)
		{	//make a map of old source and new duplicat source
			domSource* source = (domSource*) (domElement*) source_array[i];
			domSourceRef newsource = (domSource*) (domElement*) source->clone();
			assert(newsource);
			ResetSource(newsource, vertexindex);
			mesh->placeElement(newsource);
			source_map[source] = newsource;
		}

		// sort vertexset by new_index
		std::set<VertexIndexes*, LessInNewIndex> sortedvertexset;
		VertexSet::iterator setiter;
		for(setiter=vertexset.begin(); setiter!=vertexset.end(); setiter++)
		{
			sortedvertexset.insert((*setiter));
		}

		// rearrange all source data 
		std::set<VertexIndexes*, LessInNewIndex>::iterator sortedsetiter;
		for(sortedsetiter=sortedvertexset.begin(); sortedsetiter!=sortedvertexset.end(); sortedsetiter++)
		{
			VertexIndexes * index = (*sortedsetiter);
			IndexMap::iterator mapiter;
			for(mapiter=index->index_map.begin(); mapiter!=index->index_map.end(); mapiter++)
			{
				domElement * inputsource = mapiter->first;
				if (inputsource == vertices)
				{	// this inputsource is vertices, we need to rearrage all input sources in vertices
//					SetNewSource(index->new_index, 
					domInputLocal_Array & vertices_input_array = vertices->getInput_array();
					for(size_t i=0; i<vertices_input_array.getCount(); i++)
					{
						xsAnyURI & uri = vertices_input_array[i]->getSource();
						uri.resolveElement();
						domSource* source = (domSource*) (domElement*) uri.getElement();
						assert(source_map[source]);
						SetSource(source, source_map[source], mapiter->second, index->new_index);
					}
				} else
				{	// it is not vertices, some other source					
					domSource* source = (domSource*) inputsource;
					assert(source_map[source]);
					SetSource(source, source_map[source], mapiter->second, index->new_index);
				}
			}
		}

		// remove old sources
		std::map<domSource*,domSource*>::iterator iter;
		for(iter=source_map.begin(); iter!=source_map.end(); iter++)
		{
			domSource * source = iter->first;
			mesh->removeChildElement(source);
		}

		// parse skinning
		SkinInfo *skininfo = NULL;
	  std::vector<daeElement*> skins = dae->getDatabase()->typeLookup(domSkin::ID());
  	for(std::vector<daeElement*>::iterator s = skins.begin(); s != skins.end(); ++s)
		{
			domSkin *skin = (domSkin*)(*s);

			xsAnyURI & uri = skin->getSource();
			uri.resolveElement();
			domGeometry * skin_geometry = (domGeometry*) (domElement*) uri.getElement();
			if(geometry == skin_geometry)
			{// found match mesh, process skin
				domSkin::domVertex_weights * weights = skin->getVertex_weights();
				domUint maxoffset = 0;
				domInputLocalOffset_Array &inputarray = weights->getInput_array();
				for (size_t j=0; j< inputarray.getCount(); j++)
				{
					domUint tmpoffset = inputarray[j]->getOffset();
					if (tmpoffset > maxoffset) maxoffset = tmpoffset;
				}
				domUint numbersofinput = maxoffset + 1; // offset is 0 start, not 1 start

				skininfo = new SkinInfo(weights, numbersofinput);
				break;
			}
		}

		if (skininfo==NULL) continue;
		for (sortedsetiter=sortedvertexset.begin();sortedsetiter!=sortedvertexset.end();sortedsetiter++)
		{
			VertexIndexes * vertex_index = *sortedsetiter;
			domUint oldindex = vertex_index->index_map[vertices];
			skininfo->AppendIndex(oldindex);
			delete vertex_index;
		}
		sortedvertexset.clear();
		skininfo->SetWeightsCount(vertexindex);
		delete skininfo;
	}

	// resolve all a the inputs so that they will reference to the new domSource
	std::vector<daeElement*> inputs = dae->getDatabase()->typeLookup(domInputLocal::ID());
  for(std::vector<daeElement*>::iterator in = inputs.begin(); in != inputs.end(); ++in)
	{	// for each geometry
		domInputLocal *inputlocal = (domInputLocal*)(*in);
		inputlocal->getSource().resolveElement();
	}
	std::vector<daeElement*> inputsoff = dae->getDatabase()->typeLookup(domInputLocalOffset::ID());
  for(std::vector<daeElement*>::iterator ino = inputsoff.begin(); ino != inputsoff.end(); ++ino)
	{	// for each geometry
		domInputLocalOffset *inputlocaloffset = (domInputLocalOffset*)(*ino);
		inputlocaloffset->getSource().resolveElement();
	}

	return error;
}
