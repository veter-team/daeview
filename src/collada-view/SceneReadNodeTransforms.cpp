#include "Scene.h"
#include <dae.h>
#include <dom/domNode.h>
#include "colladautils.h"

#ifndef WIN32
#define _stricmp strcasecmp
#endif


Transformation::TransformType 
GetTransformType(const char *type_name)
{
  // Return a enum for the type of transform, things that are not transforms like <instance_
  // are returned as eCrtTFormUnknown and will be handled by other code.
  if(_stricmp(type_name, "rotate") == 0)
    return Transformation::Rotate;
  else if(_stricmp(type_name, "translate") == 0)
    return Transformation::Translate;
  else if(_stricmp(type_name, "matrix") == 0) 
    return Transformation::Matrix;
  else if(_stricmp(type_name, "scale") == 0) 
    return Transformation::Scale;
  else if(_stricmp(type_name, "lookat") == 0) 
    return Transformation::LookAt;
  else if(_stricmp(type_name, "skew") == 0) 
    return Transformation::Skew;
  else 
    return Transformation::Unknown;
}


bool 
Scene::readNodeTranforms(Node &node, 
                         const Node &parent, 
                         domNodeRef dom_node)
{
  // load the node transformations as they are to be able to 
  // handle any matrix stack configurations independant of the tools 
  daeElementRefArray contents = dom_node->getContents();
  for(size_t i = 0; i < contents.getCount(); i++)
    {
      // get the component type
      const char *type_name = contents[i]->getTypeName(); 
      Transformation::TransformType type = GetTransformType(type_name); 
      // set the type of the transform and switch on it 
      Transformation trans;
      trans.type = type;
      switch(type)
	    {
	    case Transformation::Rotate:
	      {
	        // Load rotation
	        domRotateRef rotateArray = (domRotate*)(domElement*)contents[i];
	        assert(rotateArray->getValue().getCount() == 4); 
          domFloat4 &rarray = rotateArray->getValue();
          // Get the rotation axis 
          Vector3 rot_axis(float(rarray.get(0)), float(rarray.get(1)), float(rarray.get(2)));
          // Store rotation
          // Sid will be used to bind to an animation later 
          trans.sid = CheckString(rotateArray->getSid());
          trans.transform = Transform3::rotation(float(rarray.get(3)) * DEGREES_TO_RADIANS, rot_axis);
          node.local_matrix *= trans.transform;
          node.transformations.push_back(trans);
	      }
	      break;

	    case Transformation::Translate:
	      {
	        // Load translation
	        domTranslateRef translateArray = (domTranslate *)(domElement*)contents[i];
	        assert(translateArray->getValue().getCount() == 3); 
			    domFloat3 &tarray = translateArray->getValue();
	        // Get the transation data 
	        Vector3 t(float(tarray.get(0)), float(tarray.get(1)), float(tarray.get(2)));
          // Store transformation
          trans.sid = CheckString(translateArray->getSid());
          trans.transform = Transform3::translation(t);
          node.local_matrix *= trans.transform;
          node.transformations.push_back(trans);
	      }
	      break;

	    case Transformation::Scale:
	      {
	        // Load scale 
	        domScaleRef scaleArray = (domScale*)(domElement*)contents[i];
	        assert(scaleArray->getValue().getCount() == 3); 
			    domFloat3 &sarray = scaleArray->getValue();
 	        // Get the scale data 
	        Vector3 s(float(sarray.get(0)), float(sarray.get(1)), float(sarray.get(2)));
          // Store transformation
          trans.sid = CheckString(scaleArray->getSid());
          trans.transform = Transform3::scale(s);
          node.local_matrix *= trans.transform;
          node.transformations.push_back(trans);
	      }
	      break;

	    case Transformation::LookAt:
	      {
	        // Load transformation
	        domLookatRef lookatArray = (domLookat*)(domElement*)contents[i];
	        assert(lookatArray->getValue().getCount() == 9);
	        // Get the lookat data 
          domFloat3x3 lkatarray = lookatArray->getValue();
          const Point3 eyePos(float(lkatarray.get(0)), float(lkatarray.get(1)), float(lkatarray.get(2)));
          const Point3 lookAtPos(float(lkatarray.get(3)), float(lkatarray.get(4)), float(lkatarray.get(5)));
          const Vector3 upVec(float(lkatarray.get(6)), float(lkatarray.get(7)), float(lkatarray.get(8)));
          // Store transformation
          trans.matrix = Matrix4::lookAt(eyePos, lookAtPos, upVec);
          trans.sid = CheckString(lookatArray->getSid());
          node.local_matrix *= trans.matrix;
          node.transformations.push_back(trans);	
        }
	      break;

	    case Transformation::Matrix:
	      {
	        // beware, RT is row major, collada spec is column major
	        domMatrixRef matrixArray = (domMatrix*)(domElement*)contents[i];
          assert(matrixArray->getValue().getCount() == 16);
          domFloat4x4 marray = matrixArray->getValue();
          // Get the data
	        for(size_t c = 0; c < 4; ++c)
          {
	          trans.matrix[c][0] = float(marray.get(c*4 + 0));
	          trans.matrix[c][1] = float(marray.get(c*4 + 1));
	          trans.matrix[c][2] = float(marray.get(c*4 + 2));
	          trans.matrix[c][3] = float(marray.get(c*4 + 3));
          }
          // Store transformation
          trans.sid = CheckString(matrixArray->getSid());
          node.local_matrix *= trans.matrix;
          node.transformations.push_back(trans);		
	      }
	      break;

	    case Transformation::Skew:
	      this->scene_graph.printStatusMessage("Skew transforms not supported yet");
	      continue;

	    case Transformation::Unknown:
	      // If it's not a transform, it's an instance or something else 
        // that will be handled later.
	      continue; 
	    }

      int transform_idx = node.transformations.size() - 1;
      for(Animation::AnimationList::iterator a = this->scene_graph.all_animations.begin();
        a != this->scene_graph.all_animations.end(); ++a) 
      {
        Animation &anim = a->second;
        for(Animation::AnimChannelList::iterator ch = anim.channels.begin(); 
          ch != anim.channels.end(); ++ch)
        {
          std::string node_id = CheckString(dom_node->getId());
          if(ch->target_id_str == node_id 
            && ch->target_sid_str == trans.sid)
          {
            ch->tranformation_targets.push_back(std::make_pair(node_id, transform_idx));
          }
        }
      }

    }	

  return true; 
}
