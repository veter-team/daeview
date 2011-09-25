/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domGles_texcombiner_command_type.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domGles_texcombiner_command_type::create(DAE& dae)
{
	domGles_texcombiner_command_typeRef ref = new domGles_texcombiner_command_type(dae);
	return ref;
}


daeMetaElement *
domGles_texcombiner_command_type::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "gles_texcombiner_command_type" );
	meta->registerClass(domGles_texcombiner_command_type::create);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( meta, cm, 0, 0, 1 );
	mea->setName( "constant" );
	mea->setOffset( daeOffsetOf(domGles_texcombiner_command_type,elemConstant) );
	mea->setElementType( domGles_texture_constant_type::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 1, 0, 1 );
	mea->setName( "RGB" );
	mea->setOffset( daeOffsetOf(domGles_texcombiner_command_type,elemRGB) );
	mea->setElementType( domGles_texcombiner_commandRGB_type::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 2, 0, 1 );
	mea->setName( "alpha" );
	mea->setOffset( daeOffsetOf(domGles_texcombiner_command_type,elemAlpha) );
	mea->setElementType( domGles_texcombiner_commandAlpha_type::registerElement(dae) );
	cm->appendChild( mea );

	cm->setMaxOrdinal( 2 );
	meta->setCMRoot( cm );	

	meta->setElementSize(sizeof(domGles_texcombiner_command_type));
	meta->validate();

	return meta;
}

