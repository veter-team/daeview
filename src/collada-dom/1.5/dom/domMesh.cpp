#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domMesh.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domMesh::create(DAE& dae)
{
	domMeshRef ref = new domMesh(dae);
	return ref;
}


daeMetaElement *
domMesh::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "mesh" );
	meta->registerClass(domMesh::create);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, -1 );
	mea->setName( "source" );
	mea->setOffset( daeOffsetOf(domMesh,elemSource_array) );
	mea->setElementType( domSource::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 1, 1, 1 );
	mea->setName( "vertices" );
	mea->setOffset( daeOffsetOf(domMesh,elemVertices) );
	mea->setElementType( domVertices::registerElement(dae) );
	cm->appendChild( mea );

	cm = new daeMetaChoice( meta, cm, 0, 2, 0, -1 );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "lines" );
	mea->setOffset( daeOffsetOf(domMesh,elemLines_array) );
	mea->setElementType( domLines::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "linestrips" );
	mea->setOffset( daeOffsetOf(domMesh,elemLinestrips_array) );
	mea->setElementType( domLinestrips::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "polygons" );
	mea->setOffset( daeOffsetOf(domMesh,elemPolygons_array) );
	mea->setElementType( domPolygons::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "polylist" );
	mea->setOffset( daeOffsetOf(domMesh,elemPolylist_array) );
	mea->setElementType( domPolylist::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "triangles" );
	mea->setOffset( daeOffsetOf(domMesh,elemTriangles_array) );
	mea->setElementType( domTriangles::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "trifans" );
	mea->setOffset( daeOffsetOf(domMesh,elemTrifans_array) );
	mea->setElementType( domTrifans::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "tristrips" );
	mea->setOffset( daeOffsetOf(domMesh,elemTristrips_array) );
	mea->setElementType( domTristrips::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 0 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();

	mea = new daeMetaElementArrayAttribute( meta, cm, 3003, 0, -1 );
	mea->setName( "extra" );
	mea->setOffset( daeOffsetOf(domMesh,elemExtra_array) );
	mea->setElementType( domExtra::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 3003 );
	meta->setCMRoot( cm );	
	// Ordered list of sub-elements
	meta->addContents(daeOffsetOf(domMesh,_contents));
	meta->addContentsOrder(daeOffsetOf(domMesh,_contentsOrder));

	meta->addCMDataArray(daeOffsetOf(domMesh,_CMData), 1);
	meta->setElementSize(sizeof(domMesh));
	meta->validate();

	return meta;
}

