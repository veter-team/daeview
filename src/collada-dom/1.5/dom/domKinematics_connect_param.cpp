#include <dae.h>
#include <dae/daeDom.h>
#include <dom/domKinematics_connect_param.h>
#include <dae/daeMetaCMPolicy.h>
#include <dae/daeMetaSequence.h>
#include <dae/daeMetaChoice.h>
#include <dae/daeMetaGroup.h>
#include <dae/daeMetaAny.h>
#include <dae/daeMetaElementAttribute.h>

daeElementRef
domKinematics_connect_param::create(DAE& dae)
{
	domKinematics_connect_paramRef ref = new domKinematics_connect_param(dae);
	return ref;
}


daeMetaElement *
domKinematics_connect_param::registerElement(DAE& dae)
{
	daeMetaElement* meta = dae.getMeta(ID());
	if ( meta != NULL ) return meta;

	meta = new daeMetaElement(dae);
	dae.setMeta(ID(), *meta);
	meta->setName( "kinematics_connect_param" );
	meta->registerClass(domKinematics_connect_param::create);


	//	Add attribute: ref
	{
		daeMetaAttribute *ma = new daeMetaAttribute;
		ma->setName( "ref" );
		ma->setType( dae.getAtomicTypes().get("xsToken"));
		ma->setOffset( daeOffsetOf( domKinematics_connect_param , attrRef ));
		ma->setContainer( meta );
		ma->setIsRequired( true );
	
		meta->appendAttribute(ma);
	}

	meta->setElementSize(sizeof(domKinematics_connect_param));
	meta->validate();

	return meta;
}

