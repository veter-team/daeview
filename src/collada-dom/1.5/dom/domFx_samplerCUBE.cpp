#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domFx_samplerCUBE.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domFx_samplerCUBE::create(DAE& dae)
{
	domFx_samplerCUBERef ref = new domFx_samplerCUBE(dae);
	return ref;
}


daeMetaElement *
domFx_samplerCUBE::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "fx_samplerCUBE" );
	meta->registerClass(domFx_samplerCUBE::create);

	daeMetaCMPolicy *cm = NULL;
	daeMetaElementAttribute *mea = NULL;
	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	cm = new daeMetaSequence( meta, cm, 0, 1, 1 );

	mea = new daeMetaElementAttribute( meta, cm, 0, 0, 1 );
	mea->setName( "instance_image" );
	mea->setOffset( daeOffsetOf(domFx_samplerCUBE,elemInstance_image) );
	mea->setElementType( domInstance_image::registerElement(dae) );
	cm->appendChild( mea );

	mea = new daeMetaElementAttribute( meta, cm, 1, 1, 1 );
	mea->setName( "fx_sampler_states" );
	mea->setOffset( daeOffsetOf(domFx_samplerCUBE,elemFx_sampler_states) );
	mea->setElementType( domFx_sampler_states::registerElement(dae) );
	cm->appendChild( new daeMetaGroup( mea, meta, cm, 1, 1, 1 ) );

	cm->setMaxOrdinal( 1 );
	cm->getParent()->appendChild( cm );
	cm = cm->getParent();

	cm->setMaxOrdinal( 1 );
	meta->setCMRoot( cm );	

	meta->setElementSize(sizeof(domFx_samplerCUBE));
	meta->validate();

	return meta;
}

