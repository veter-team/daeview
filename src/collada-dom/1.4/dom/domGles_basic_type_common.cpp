/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domGles_basic_type_common.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domGles_basic_type_common::create(DAE& dae)
{
	domGles_basic_type_commonRef ref = new domGles_basic_type_common(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "gles_basic_type_common" );
	meta->registerClass(domGles_basic_type_common::create);

	meta->setIsTransparent( true );
	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaChoice( meta, cm, 0, 0, 1, 1 );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "bool" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemBool) );
	mea->setElementType( domGles_basic_type_common::domBool::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "bool2" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemBool2) );
	mea->setElementType( domGles_basic_type_common::domBool2::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "bool3" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemBool3) );
	mea->setElementType( domGles_basic_type_common::domBool3::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "bool4" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemBool4) );
	mea->setElementType( domGles_basic_type_common::domBool4::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "int" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemInt) );
	mea->setElementType( domGles_basic_type_common::domInt::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "int2" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemInt2) );
	mea->setElementType( domGles_basic_type_common::domInt2::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "int3" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemInt3) );
	mea->setElementType( domGles_basic_type_common::domInt3::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "int4" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemInt4) );
	mea->setElementType( domGles_basic_type_common::domInt4::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat) );
	mea->setElementType( domGles_basic_type_common::domFloat::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float2" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat2) );
	mea->setElementType( domGles_basic_type_common::domFloat2::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float3" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat3) );
	mea->setElementType( domGles_basic_type_common::domFloat3::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float4" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat4) );
	mea->setElementType( domGles_basic_type_common::domFloat4::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float1x1" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat1x1) );
	mea->setElementType( domGles_basic_type_common::domFloat1x1::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float1x2" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat1x2) );
	mea->setElementType( domGles_basic_type_common::domFloat1x2::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float1x3" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat1x3) );
	mea->setElementType( domGles_basic_type_common::domFloat1x3::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float1x4" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat1x4) );
	mea->setElementType( domGles_basic_type_common::domFloat1x4::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float2x1" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat2x1) );
	mea->setElementType( domGles_basic_type_common::domFloat2x1::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float2x2" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat2x2) );
	mea->setElementType( domGles_basic_type_common::domFloat2x2::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float2x3" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat2x3) );
	mea->setElementType( domGles_basic_type_common::domFloat2x3::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float2x4" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat2x4) );
	mea->setElementType( domGles_basic_type_common::domFloat2x4::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float3x1" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat3x1) );
	mea->setElementType( domGles_basic_type_common::domFloat3x1::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float3x2" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat3x2) );
	mea->setElementType( domGles_basic_type_common::domFloat3x2::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float3x3" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat3x3) );
	mea->setElementType( domGles_basic_type_common::domFloat3x3::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float3x4" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat3x4) );
	mea->setElementType( domGles_basic_type_common::domFloat3x4::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float4x1" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat4x1) );
	mea->setElementType( domGles_basic_type_common::domFloat4x1::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float4x2" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat4x2) );
	mea->setElementType( domGles_basic_type_common::domFloat4x2::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float4x3" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat4x3) );
	mea->setElementType( domGles_basic_type_common::domFloat4x3::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "float4x4" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemFloat4x4) );
	mea->setElementType( domGles_basic_type_common::domFloat4x4::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "surface" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemSurface) );
	mea->setElementType( domFx_surface_common::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "texture_pipeline" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemTexture_pipeline) );
	mea->setElementType( domGles_texture_pipeline::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "sampler_state" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemSampler_state) );
	mea->setElementType( domGles_sampler_state::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "texture_unit" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemTexture_unit) );
	mea->setElementType( domGles_texture_unit::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 0, 1, 1 );
	mea->setName( "enum" );
	mea->setOffset( daeOffsetOf(domGles_basic_type_common,elemEnum) );
	mea->setElementType( domGles_basic_type_common::domEnum::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 0 );
	meta->setCMRoot( cm );	
	// Ordered list of sub-elements
	meta->addContents(daeOffsetOf(domGles_basic_type_common,_contents));
	meta->addContentsOrder(daeOffsetOf(domGles_basic_type_common,_contentsOrder));

	meta->addCMDataArray(daeOffsetOf(domGles_basic_type_common,_CMData), 1);
	meta->setElementSize(sizeof(domGles_basic_type_common));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domBool::create(DAE& dae)
{
	domGles_basic_type_common::domBoolRef ref = new domGles_basic_type_common::domBool(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domBool::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "bool" );
	meta->registerClass(domGles_basic_type_common::domBool::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Bool"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domBool , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domBool));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domBool2::create(DAE& dae)
{
	domGles_basic_type_common::domBool2Ref ref = new domGles_basic_type_common::domBool2(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domBool2::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "bool2" );
	meta->registerClass(domGles_basic_type_common::domBool2::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Bool2"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domBool2 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domBool2));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domBool3::create(DAE& dae)
{
	domGles_basic_type_common::domBool3Ref ref = new domGles_basic_type_common::domBool3(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domBool3::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "bool3" );
	meta->registerClass(domGles_basic_type_common::domBool3::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Bool3"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domBool3 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domBool3));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domBool4::create(DAE& dae)
{
	domGles_basic_type_common::domBool4Ref ref = new domGles_basic_type_common::domBool4(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domBool4::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "bool4" );
	meta->registerClass(domGles_basic_type_common::domBool4::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Bool4"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domBool4 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domBool4));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domInt::create(DAE& dae)
{
	domGles_basic_type_common::domIntRef ref = new domGles_basic_type_common::domInt(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domInt::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "int" );
	meta->registerClass(domGles_basic_type_common::domInt::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Int"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domInt , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domInt));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domInt2::create(DAE& dae)
{
	domGles_basic_type_common::domInt2Ref ref = new domGles_basic_type_common::domInt2(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domInt2::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "int2" );
	meta->registerClass(domGles_basic_type_common::domInt2::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Int2"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domInt2 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domInt2));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domInt3::create(DAE& dae)
{
	domGles_basic_type_common::domInt3Ref ref = new domGles_basic_type_common::domInt3(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domInt3::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "int3" );
	meta->registerClass(domGles_basic_type_common::domInt3::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Int3"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domInt3 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domInt3));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domInt4::create(DAE& dae)
{
	domGles_basic_type_common::domInt4Ref ref = new domGles_basic_type_common::domInt4(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domInt4::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "int4" );
	meta->registerClass(domGles_basic_type_common::domInt4::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Int4"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domInt4 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domInt4));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat::create(DAE& dae)
{
	domGles_basic_type_common::domFloatRef ref = new domGles_basic_type_common::domFloat(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float" );
	meta->registerClass(domGles_basic_type_common::domFloat::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat2::create(DAE& dae)
{
	domGles_basic_type_common::domFloat2Ref ref = new domGles_basic_type_common::domFloat2(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat2::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float2" );
	meta->registerClass(domGles_basic_type_common::domFloat2::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float2"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat2 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat2));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat3::create(DAE& dae)
{
	domGles_basic_type_common::domFloat3Ref ref = new domGles_basic_type_common::domFloat3(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat3::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float3" );
	meta->registerClass(domGles_basic_type_common::domFloat3::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float3"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat3 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat3));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat4::create(DAE& dae)
{
	domGles_basic_type_common::domFloat4Ref ref = new domGles_basic_type_common::domFloat4(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat4::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float4" );
	meta->registerClass(domGles_basic_type_common::domFloat4::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float4"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat4 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat4));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat1x1::create(DAE& dae)
{
	domGles_basic_type_common::domFloat1x1Ref ref = new domGles_basic_type_common::domFloat1x1(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat1x1::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float1x1" );
	meta->registerClass(domGles_basic_type_common::domFloat1x1::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat1x1 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat1x1));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat1x2::create(DAE& dae)
{
	domGles_basic_type_common::domFloat1x2Ref ref = new domGles_basic_type_common::domFloat1x2(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat1x2::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float1x2" );
	meta->registerClass(domGles_basic_type_common::domFloat1x2::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float2"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat1x2 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat1x2));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat1x3::create(DAE& dae)
{
	domGles_basic_type_common::domFloat1x3Ref ref = new domGles_basic_type_common::domFloat1x3(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat1x3::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float1x3" );
	meta->registerClass(domGles_basic_type_common::domFloat1x3::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float3"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat1x3 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat1x3));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat1x4::create(DAE& dae)
{
	domGles_basic_type_common::domFloat1x4Ref ref = new domGles_basic_type_common::domFloat1x4(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat1x4::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float1x4" );
	meta->registerClass(domGles_basic_type_common::domFloat1x4::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float4"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat1x4 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat1x4));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat2x1::create(DAE& dae)
{
	domGles_basic_type_common::domFloat2x1Ref ref = new domGles_basic_type_common::domFloat2x1(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat2x1::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float2x1" );
	meta->registerClass(domGles_basic_type_common::domFloat2x1::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float2"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat2x1 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat2x1));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat2x2::create(DAE& dae)
{
	domGles_basic_type_common::domFloat2x2Ref ref = new domGles_basic_type_common::domFloat2x2(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat2x2::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float2x2" );
	meta->registerClass(domGles_basic_type_common::domFloat2x2::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float2x2"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat2x2 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat2x2));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat2x3::create(DAE& dae)
{
	domGles_basic_type_common::domFloat2x3Ref ref = new domGles_basic_type_common::domFloat2x3(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat2x3::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float2x3" );
	meta->registerClass(domGles_basic_type_common::domFloat2x3::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float2x3"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat2x3 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat2x3));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat2x4::create(DAE& dae)
{
	domGles_basic_type_common::domFloat2x4Ref ref = new domGles_basic_type_common::domFloat2x4(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat2x4::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float2x4" );
	meta->registerClass(domGles_basic_type_common::domFloat2x4::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float2x4"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat2x4 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat2x4));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat3x1::create(DAE& dae)
{
	domGles_basic_type_common::domFloat3x1Ref ref = new domGles_basic_type_common::domFloat3x1(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat3x1::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float3x1" );
	meta->registerClass(domGles_basic_type_common::domFloat3x1::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float3"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat3x1 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat3x1));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat3x2::create(DAE& dae)
{
	domGles_basic_type_common::domFloat3x2Ref ref = new domGles_basic_type_common::domFloat3x2(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat3x2::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float3x2" );
	meta->registerClass(domGles_basic_type_common::domFloat3x2::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float3x2"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat3x2 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat3x2));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat3x3::create(DAE& dae)
{
	domGles_basic_type_common::domFloat3x3Ref ref = new domGles_basic_type_common::domFloat3x3(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat3x3::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float3x3" );
	meta->registerClass(domGles_basic_type_common::domFloat3x3::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float3x3"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat3x3 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat3x3));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat3x4::create(DAE& dae)
{
	domGles_basic_type_common::domFloat3x4Ref ref = new domGles_basic_type_common::domFloat3x4(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat3x4::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float3x4" );
	meta->registerClass(domGles_basic_type_common::domFloat3x4::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float3x4"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat3x4 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat3x4));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat4x1::create(DAE& dae)
{
	domGles_basic_type_common::domFloat4x1Ref ref = new domGles_basic_type_common::domFloat4x1(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat4x1::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float4x1" );
	meta->registerClass(domGles_basic_type_common::domFloat4x1::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float4"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat4x1 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat4x1));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat4x2::create(DAE& dae)
{
	domGles_basic_type_common::domFloat4x2Ref ref = new domGles_basic_type_common::domFloat4x2(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat4x2::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float4x2" );
	meta->registerClass(domGles_basic_type_common::domFloat4x2::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float4x2"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat4x2 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat4x2));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat4x3::create(DAE& dae)
{
	domGles_basic_type_common::domFloat4x3Ref ref = new domGles_basic_type_common::domFloat4x3(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat4x3::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float4x3" );
	meta->registerClass(domGles_basic_type_common::domFloat4x3::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float4x3"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat4x3 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat4x3));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domFloat4x4::create(DAE& dae)
{
	domGles_basic_type_common::domFloat4x4Ref ref = new domGles_basic_type_common::domFloat4x4(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domFloat4x4::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "float4x4" );
	meta->registerClass(domGles_basic_type_common::domFloat4x4::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaArrayAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Float4x4"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domFloat4x4 , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domFloat4x4));
	meta->validate();

	return meta;
}

daeElementRef
domGles_basic_type_common::domEnum::create(DAE& dae)
{
	domGles_basic_type_common::domEnumRef ref = new domGles_basic_type_common::domEnum(dae);
	return ref;
}


daeMetaElement *
domGles_basic_type_common::domEnum::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "enum" );
	meta->registerClass(domGles_basic_type_common::domEnum::create);

	meta->setIsInnerClass( true );
	//	Add attribute: _value
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "_value" );
		ma->setType( dae.getAtomicTypes().get("Gles_enumeration"));
		ma->setOffset( daeOffsetOf( domGles_basic_type_common::domEnum , _value ));
		ma->setContainer( meta );
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domGles_basic_type_common::domEnum));
	meta->validate();

	return meta;
}

