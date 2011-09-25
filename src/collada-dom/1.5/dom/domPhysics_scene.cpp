#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domPhysics_scene.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domPhysics_scene::create(DAE& dae)
{
	domPhysics_sceneRef ref = new domPhysics_scene(dae);
	return ref;
}


daeMetaElement *
domPhysics_scene::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "physics_scene" );
	meta->registerClass(domPhysics_scene::create);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( meta, cm, 0, 0, 1 );
	mea->setName( "asset" );
	mea->setOffset( daeOffsetOf(domPhysics_scene,elemAsset) );
	mea->setElementType( domAsset::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 1, 0, -1 );
	mea->setName( "instance_force_field" );
	mea->setOffset( daeOffsetOf(domPhysics_scene,elemInstance_force_field_array) );
	mea->setElementType( domInstance_force_field::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 2, 0, -1 );
	mea->setName( "instance_physics_model" );
	mea->setOffset( daeOffsetOf(domPhysics_scene,elemInstance_physics_model_array) );
	mea->setElementType( domInstance_physics_model::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 3, 1, 1 );
	mea->setName( "technique_common" );
	mea->setOffset( daeOffsetOf(domPhysics_scene,elemTechnique_common) );
	mea->setElementType( domPhysics_scene::domTechnique_common::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 4, 0, -1 );
	mea->setName( "technique" );
	mea->setOffset( daeOffsetOf(domPhysics_scene,elemTechnique_array) );
	mea->setElementType( domTechnique::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 5, 0, -1 );
	mea->setName( "extra" );
	mea->setOffset( daeOffsetOf(domPhysics_scene,elemExtra_array) );
	mea->setElementType( domExtra::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 5 );
	meta->setCMRoot( cm );	

	//	Add attribute: id
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "id" );
		ma->setType( dae.getAtomicTypes().get("xsID"));
		ma->setOffset( daeOffsetOf( domPhysics_scene , attrId ));
		ma->setContainer( meta );
	
		meta->appendAttribute(ma);
	}

	//	Add attribute: name
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "name" );
		ma->setType( dae.getAtomicTypes().get("xsToken"));
		ma->setOffset( daeOffsetOf( domPhysics_scene , attrName ));
		ma->setContainer( meta );
	
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domPhysics_scene));
	meta->validate();

	return meta;
}

daeElementRef
domPhysics_scene::domTechnique_common::create(DAE& dae)
{
	domPhysics_scene::domTechnique_commonRef ref = new domPhysics_scene::domTechnique_common(dae);
	return ref;
}


daeMetaElement *
domPhysics_scene::domTechnique_common::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "technique_common" );
	meta->registerClass(domPhysics_scene::domTechnique_common::create);

	meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( meta, cm, 0, 0, 1 );
	mea->setName( "gravity" );
	mea->setOffset( daeOffsetOf(domPhysics_scene::domTechnique_common,elemGravity) );
	mea->setElementType( domTargetable_float3::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 1, 0, 1 );
	mea->setName( "time_step" );
	mea->setOffset( daeOffsetOf(domPhysics_scene::domTechnique_common,elemTime_step) );
	mea->setElementType( domTargetable_float::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 1 );
	meta->setCMRoot( cm );	

	meta->setElementSize(sizeof(domPhysics_scene::domTechnique_common));
	meta->validate();

	return meta;
}

