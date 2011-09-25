/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domCg_newarray_type.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domCg_newarray_type::create(DAE& dae)
{
	domCg_newarray_typeRef ref = new domCg_newarray_type(dae);
	return ref;
}


daeMetaElement *
domCg_newarray_type::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "cg_newarray_type" );
	meta->registerClass(domCg_newarray_type::create);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaChoice( meta, cm, 0, 0, 0, -1 );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "cg_param_type" );
	mea->setOffset( daeOffsetOf(domCg_newarray_type,elemCg_param_type_array) );
	mea->setElementType( domCg_param_type::registerElement(dae) );
	cm->appendChild( new daeMetaGroup( mea, meta, cm, 0, 1, 1 ) );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "array" );
	mea->setOffset( daeOffsetOf(domCg_newarray_type,elemArray_array) );
	mea->setElementType( domCg_newarray_type::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "usertype" );
	mea->setOffset( daeOffsetOf(domCg_newarray_type,elemUsertype_array) );
	mea->setElementType( domCg_setuser_type::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "connect_param" );
	mea->setOffset( daeOffsetOf(domCg_newarray_type,elemConnect_param_array) );
	mea->setElementType( domCg_connect_param::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 3000 );
	meta->setCMRoot( cm );	
	// Ordered list of sub-elements
	meta->addContents(daeOffsetOf(domCg_newarray_type,_contents));
	meta->addContentsOrder(daeOffsetOf(domCg_newarray_type,_contentsOrder));

	meta->addCMDataArray(daeOffsetOf(domCg_newarray_type,_CMData), 1);
	//	Add attribute: length
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "length" );
		ma->setType( dae.getAtomicTypes().get("xsPositiveInteger"));
		ma->setOffset( daeOffsetOf( domCg_newarray_type , attrLength ));
		ma->setContainer( meta );
		ma->setIsRequired( true );
	
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domCg_newarray_type));
	meta->validate();

	return meta;
}

