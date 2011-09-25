/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domFx_samplerDEPTH_common.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domFx_samplerDEPTH_common::create(DAE& dae)
{
	domFx_samplerDEPTH_commonRef ref = new domFx_samplerDEPTH_common(dae);
	return ref;
}


daeMetaElement *
domFx_samplerDEPTH_common::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "fx_samplerDEPTH_common" );
	meta->registerClass(domFx_samplerDEPTH_common::create);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "source" );
	mea->setOffset( daeOffsetOf(domFx_samplerDEPTH_common,elemSource) );
	mea->setElementType( domFx_samplerDEPTH_common::domSource::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 1, 0, 1 );
	mea->setName( "wrap_s" );
	mea->setOffset( daeOffsetOf(domFx_samplerDEPTH_common,elemWrap_s) );
	mea->setElementType( domFx_samplerDEPTH_common::domWrap_s::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 2, 0, 1 );
	mea->setName( "wrap_t" );
	mea->setOffset( daeOffsetOf(domFx_samplerDEPTH_common,elemWrap_t) );
	mea->setElementType( domFx_samplerDEPTH_common::domWrap_t::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 3, 0, 1 );
	mea->setName( "minfilter" );
	mea->setOffset( daeOffsetOf(domFx_samplerDEPTH_common,elemMinfilter) );
	mea->setElementType( domFx_samplerDEPTH_common::domMinfilter::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 4, 0, 1 );
	mea->setName( "magfilter" );
	mea->setOffset( daeOffsetOf(domFx_samplerDEPTH_common,elemMagfilter) );
	mea->setElementType( domFx_samplerDEPTH_common::domMagfilter::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementArrayAttribute( meta, cm, 5, 0, -1 );
	mea->setName( "extra" );
	mea->setOffset( daeOffsetOf(domFx_samplerDEPTH_common,elemExtra_array) );
	mea->setElementType( domExtra::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 5 );
	meta->setCMRoot( cm );	

	meta->setElementSize(sizeof(domFx_samplerDEPTH_common));
	meta->validate();

	return meta;
}

daeElementRef
domFx_samplerDEPTH_common::domSource::create(DAE& dae)
{
	domFx_samplerDEPTH_common::domSourceRef ref = new domFx_samplerDEPTH_common::domSource(dae);
	return ref;
}


daeMetaElement *
domFx_samplerDEPTH_common::domSource::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "source" );
	meta->registerClass(domFx_samplerDEPTH_common::domSource::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("xsNCName"));
		ma->setOffset( daeOffsetOf( domFx_samplerDEPTH_common::domSource , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domFx_samplerDEPTH_common::domSource));
	meta->validate();

	return meta;
}

daeElementRef
domFx_samplerDEPTH_common::domWrap_s::create(DAE& dae)
{
	domFx_samplerDEPTH_common::domWrap_sRef ref = new domFx_samplerDEPTH_common::domWrap_s(dae);
	return ref;
}


daeMetaElement *
domFx_samplerDEPTH_common::domWrap_s::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "wrap_s" );
	meta->registerClass(domFx_samplerDEPTH_common::domWrap_s::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Fx_sampler_wrap_common"));
		ma->setOffset( daeOffsetOf( domFx_samplerDEPTH_common::domWrap_s , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domFx_samplerDEPTH_common::domWrap_s));
	meta->validate();

	return meta;
}

daeElementRef
domFx_samplerDEPTH_common::domWrap_t::create(DAE& dae)
{
	domFx_samplerDEPTH_common::domWrap_tRef ref = new domFx_samplerDEPTH_common::domWrap_t(dae);
	return ref;
}


daeMetaElement *
domFx_samplerDEPTH_common::domWrap_t::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "wrap_t" );
	meta->registerClass(domFx_samplerDEPTH_common::domWrap_t::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Fx_sampler_wrap_common"));
		ma->setOffset( daeOffsetOf( domFx_samplerDEPTH_common::domWrap_t , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domFx_samplerDEPTH_common::domWrap_t));
	meta->validate();

	return meta;
}

daeElementRef
domFx_samplerDEPTH_common::domMinfilter::create(DAE& dae)
{
	domFx_samplerDEPTH_common::domMinfilterRef ref = new domFx_samplerDEPTH_common::domMinfilter(dae);
	return ref;
}


daeMetaElement *
domFx_samplerDEPTH_common::domMinfilter::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "minfilter" );
	meta->registerClass(domFx_samplerDEPTH_common::domMinfilter::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Fx_sampler_filter_common"));
		ma->setOffset( daeOffsetOf( domFx_samplerDEPTH_common::domMinfilter , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domFx_samplerDEPTH_common::domMinfilter));
	meta->validate();

	return meta;
}

daeElementRef
domFx_samplerDEPTH_common::domMagfilter::create(DAE& dae)
{
	domFx_samplerDEPTH_common::domMagfilterRef ref = new domFx_samplerDEPTH_common::domMagfilter(dae);
	return ref;
}


daeMetaElement *
domFx_samplerDEPTH_common::domMagfilter::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "magfilter" );
	meta->registerClass(domFx_samplerDEPTH_common::domMagfilter::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Fx_sampler_filter_common"));
		ma->setOffset( daeOffsetOf( domFx_samplerDEPTH_common::domMagfilter , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domFx_samplerDEPTH_common::domMagfilter));
	meta->validate();

	return meta;
}

