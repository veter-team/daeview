#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domInstance_controller.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domInstance_controller::create(DAE& dae)
{
	domInstance_controllerRef ref = new domInstance_controller(dae);
	ref->attrUrl.setContainer( (domInstance_controller*)ref );
	return ref;
}


daeMetaElement *
domInstance_controller::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "instance_controller" );
	meta->registerClass(domInstance_controller::create);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 0, -1 );
	mea->setName( "skeleton" );
	mea->setOffset( daeOffsetOf(domInstance_controller,elemSkeleton_array) );
	mea->setElementType( domInstance_controller::domSkeleton::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 1, 0, 1 );
	mea->setName( "bind_material" );
	mea->setOffset( daeOffsetOf(domInstance_controller,elemBind_material) );
	mea->setElementType( domBind_material::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 2, 0, -1 );
	mea->setName( "extra" );
	mea->setOffset( daeOffsetOf(domInstance_controller,elemExtra_array) );
	mea->setElementType( domExtra::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 2 );
	meta->setCMRoot( cm );	

	//	Add attribute: url
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "url" );
		ma->setType( dae.getAtomicTypes().get("xsAnyURI"));
		ma->setOffset( daeOffsetOf( domInstance_controller , attrUrl ));
		ma->setContainer( meta );
		ma->setIsRequired( true );
	
		meta->appendAttribute(ma);
	}

	//	Add attribute: sid
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "sid" );
		ma->setType( dae.getAtomicTypes().get("Sid"));
		ma->setOffset( daeOffsetOf( domInstance_controller , attrSid ));
		ma->setContainer( meta );
	
		meta->appendAttribute(ma);
	}

	//	Add attribute: name
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "name" );
		ma->setType( dae.getAtomicTypes().get("xsToken"));
		ma->setOffset( daeOffsetOf( domInstance_controller , attrName ));
		ma->setContainer( meta );
	
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domInstance_controller));
	meta->validate();

	return meta;
}

daeElementRef
domInstance_controller::domSkeleton::create(DAE& dae)
{
	domInstance_controller::domSkeletonRef ref = new domInstance_controller::domSkeleton(dae);
	ref->_value.setContainer( (domInstance_controller::domSkeleton*)ref );
	return ref;
}


daeMetaElement *
domInstance_controller::domSkeleton::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "skeleton" );
	meta->registerClass(domInstance_controller::domSkeleton::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("xsAnyURI"));
		ma->setOffset( daeOffsetOf( domInstance_controller::domSkeleton , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domInstance_controller::domSkeleton));
	meta->validate();

	return meta;
}

