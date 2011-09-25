/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domCg_surface_type.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domCg_surface_type::create(DAE& dae)
{
	domCg_surface_typeRef ref = new domCg_surface_type(dae);
	return ref;
}


daeMetaElement *
domCg_surface_type::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "cg_surface_type" );
	meta->registerClass(domCg_surface_type::create);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( meta, cm, 0, 0, 1 );
	mea->setName( "fx_surface_init_common" );
	mea->setOffset( daeOffsetOf(domCg_surface_type,elemFx_surface_init_common) );
	mea->setElementType( domFx_surface_init_common::registerElement(dae) );
	cm->appendChild( new daeMetaGroup( mea, meta, cm, 0, 0, 1 ) );

	mea = new daeMetaElementAttribute( meta, cm, 1, 0, 1 );
	mea->setName( "format" );
	mea->setOffset( daeOffsetOf(domCg_surface_type,elemFormat) );
	mea->setElementType( domFormat::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 2, 0, 1 );
	mea->setName( "format_hint" );
	mea->setOffset( daeOffsetOf(domCg_surface_type,elemFormat_hint) );
	mea->setElementType( domFx_surface_format_hint_common::registerElement(dae) );
	cm->appendChild( mea );

	cm = new daeMetaChoice( meta, cm, 0, 3, 0, 1 );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "size" );
	mea->setOffset( daeOffsetOf(domCg_surface_type,elemSize) );
	mea->setElementType( domSize::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "viewport_ratio" );
	mea->setOffset( daeOffsetOf(domCg_surface_type,elemViewport_ratio) );
	mea->setElementType( domViewport_ratio::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 0 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();

	mea = new daeMetaElementAttribute( meta, cm, 4, 0, 1 );
	mea->setName( "mip_levels" );
	mea->setOffset( daeOffsetOf(domCg_surface_type,elemMip_levels) );
	mea->setElementType( domMip_levels::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 5, 0, 1 );
	mea->setName( "mipmap_generate" );
	mea->setOffset( daeOffsetOf(domCg_surface_type,elemMipmap_generate) );
	mea->setElementType( domMipmap_generate::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 6, 0, -1 );
	mea->setName( "extra" );
	mea->setOffset( daeOffsetOf(domCg_surface_type,elemExtra_array) );
	mea->setElementType( domExtra::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 6 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();

	cm = new daeMetaSequence( meta, cm, 7, 1, 1 );

	mea = new daeMetaElementAttribute( meta, cm, 0, 0, 1 );
	mea->setName( "generator" );
	mea->setOffset( daeOffsetOf(domCg_surface_type,elemGenerator) );
	mea->setElementType( domGenerator::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 0 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();

	cm->setMaxOrdinal( 7 );
	meta->setCMRoot( cm );	
	// Ordered list of sub-elements
	meta->addContents(daeOffsetOf(domCg_surface_type,_contents));
	meta->addContentsOrder(daeOffsetOf(domCg_surface_type,_contentsOrder));

	meta->addCMDataArray(daeOffsetOf(domCg_surface_type,_CMData), 1);
	//	Add attribute: type
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "type" );
		ma->setType( dae.getAtomicTypes().get("Fx_surface_type_enum"));
		ma->setOffset( daeOffsetOf( domCg_surface_type , attrType ));
		ma->setContainer( meta );
		ma->setIsRequired( true );
	
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domCg_surface_type));
	meta->validate();

	return meta;
}

daeElementRef
domCg_surface_type::domGenerator::create(DAE& dae)
{
	domCg_surface_type::domGeneratorRef ref = new domCg_surface_type::domGenerator(dae);
	return ref;
}


daeMetaElement *
domCg_surface_type::domGenerator::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "generator" );
	meta->registerClass(domCg_surface_type::domGenerator::create);

	meta->setIsInnerClass( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 0, -1 );
	mea->setName( "annotate" );
	mea->setOffset( daeOffsetOf(domCg_surface_type::domGenerator,elemAnnotate_array) );
	mea->setElementType( domFx_annotate_common::registerElement(dae) );
	cm->appendChild( mea );

	cm = new daeMetaChoice( meta, cm, 0, 1, 1, -1 );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "code" );
	mea->setOffset( daeOffsetOf(domCg_surface_type::domGenerator,elemCode_array) );
	mea->setElementType( domFx_code_profile::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "include" );
	mea->setOffset( daeOffsetOf(domCg_surface_type::domGenerator,elemInclude_array) );
	mea->setElementType( domFx_include_common::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 0 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();

	mea = new daeMetaElementAttribute( meta, cm, 3002, 1, 1 );
	mea->setName( "name" );
	mea->setOffset( daeOffsetOf(domCg_surface_type::domGenerator,elemName) );
	mea->setElementType( domCg_surface_type::domGenerator::domName::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 3003, 0, -1 );
	mea->setName( "setparam" );
	mea->setOffset( daeOffsetOf(domCg_surface_type::domGenerator,elemSetparam_array) );
	mea->setElementType( domCg_setparam_simple::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 3003 );
	meta->setCMRoot( cm );	
	// Ordered list of sub-elements
	meta->addContents(daeOffsetOf(domCg_surface_type::domGenerator,_contents));
	meta->addContentsOrder(daeOffsetOf(domCg_surface_type::domGenerator,_contentsOrder));

	meta->addCMDataArray(daeOffsetOf(domCg_surface_type::domGenerator,_CMData), 1);
	meta->setElementSize(sizeof(domCg_surface_type::domGenerator));
	meta->validate();

	return meta;
}

daeElementRef
domCg_surface_type::domGenerator::domName::create(DAE& dae)
{
	domCg_surface_type::domGenerator::domNameRef ref = new domCg_surface_type::domGenerator::domName(dae);
	return ref;
}


daeMetaElement *
domCg_surface_type::domGenerator::domName::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "name" );
	meta->registerClass(domCg_surface_type::domGenerator::domName::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("xsNCName"));
		ma->setOffset( daeOffsetOf( domCg_surface_type::domGenerator::domName , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	//	Add attribute: source
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "source" );
		ma->setType( dae.getAtomicTypes().get("xsNCName"));
		ma->setOffset( daeOffsetOf( domCg_surface_type::domGenerator::domName , attrSource ));
		ma->setContainer( meta );
		ma->setIsRequired( false );
	
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domCg_surface_type::domGenerator::domName));
	meta->validate();

	return meta;
}

