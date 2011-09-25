#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domAccessor.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domAccessor::create(DAE& dae)
{
	domAccessorRef ref = new domAccessor(dae);
	ref->attrSource.setContainer( (domAccessor*)ref );
	return ref;
}


daeMetaElement *
domAccessor::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "accessor" );
	meta->registerClass(domAccessor::create);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 0, -1 );
	mea->setName( "param" );
	mea->setOffset( daeOffsetOf(domAccessor,elemParam_array) );
	mea->setElementType( domParam::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 0 );
	meta->setCMRoot( cm );	

	//	Add attribute: count
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "count" );
		ma->setType( dae.getAtomicTypes().get("Uint"));
		ma->setOffset( daeOffsetOf( domAccessor , attrCount ));
		ma->setContainer( meta );
		ma->setIsRequired( true );
	
		meta->appendAttribute(ma);
	}

	//	Add attribute: offset
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "offset" );
		ma->setType( dae.getAtomicTypes().get("Uint"));
		ma->setOffset( daeOffsetOf( domAccessor , attrOffset ));
		ma->setContainer( meta );
		ma->setDefaultString( "0");
	
		meta->appendAttribute(ma);
	}

	//	Add attribute: source
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "source" );
		ma->setType( dae.getAtomicTypes().get("xsAnyURI"));
		ma->setOffset( daeOffsetOf( domAccessor , attrSource ));
		ma->setContainer( meta );
		ma->setIsRequired( true );
	
		meta->appendAttribute(ma);
	}

	//	Add attribute: stride
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "stride" );
		ma->setType( dae.getAtomicTypes().get("Uint"));
		ma->setOffset( daeOffsetOf( domAccessor , attrStride ));
		ma->setContainer( meta );
		ma->setDefaultString( "1");
	
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domAccessor));
	meta->validate();

	return meta;
}

