#include "triangulation.h"
#include "colladautils.h"
#include <iostream>
#include <dae.h>
#include <dom/domGeometry.h>
#include <dom/domMesh.h>
#include <dom/domPolygons.h>
#include <dom/domPolylist.h>



void 
createTrianglesFromPolylist(domMesh *thisMesh, domPolylist *thisPolylist)
{
  // Create a new <triangles> inside the mesh that has the same
  // material as the <polylist>
  domTriangles *thisTriangles = 
    (domTriangles*)thisMesh->createAndPlace("triangles");
  //thisTriangles->setCount( 0 );
  size_t triangles = 0;
  thisTriangles->setMaterial(thisPolylist->getMaterial());
  domP *p_triangles = (domP*)thisTriangles->createAndPlace("p");

  // Give the new <triangles> the same <dae> and <parameters> as the
  // old <polylist>
  for(size_t i=0; i < thisPolylist->getInput_array().getCount(); i++)
    thisTriangles->placeElement(thisPolylist->getInput_array()[i]->clone());

  // Get the number of inputs and primitives for the polygons array
  size_t numberOfInputs = getMaxOffset(thisPolylist->getInput_array()) + 1;
  size_t numberOfPrimitives = thisPolylist->getVcount()->getValue().getCount();

  size_t offset = 0;

  // Triangulate all the primitives, this generates all the triangles
  // in a single <p> element
  for(size_t j = 0; j < numberOfPrimitives; j++)
    {	
      size_t triangleCount = 
        (size_t)thisPolylist->getVcount()->getValue()[j] - 2;
      // Write out the primitives as triangles, just fan using the
      // first element as the base
      size_t idx = numberOfInputs;
      for(size_t k = 0; k < triangleCount; k++)
      {
        // First vertex
        for(size_t l = 0; l < numberOfInputs; l++)
	        p_triangles->getValue().append(thisPolylist->getP()->getValue()[offset + l]);
        // Second vertex
        for(size_t l = 0; l < numberOfInputs; l++)
	        p_triangles->getValue().append(thisPolylist->getP()->getValue()[offset + idx + l]);
        // Third vertex
        idx += numberOfInputs;
        for(size_t l = 0; l < numberOfInputs; l++)
	        p_triangles->getValue().append(thisPolylist->getP()->getValue()[offset + idx + l]);
        //thisTriangles->setCount(thisTriangles->getCount()+1);
        triangles++;
      }
      offset += (size_t)thisPolylist->getVcount()->getValue()[j] * numberOfInputs;
    }
  thisTriangles->setCount(triangles);
}


void 
createTrianglesFromPolygons(domMesh *thisMesh, domPolygons *thisPolygons)
{
  // Create a new <triangles> inside the mesh that has the same
  // material as the <polygons>
  domTriangles *thisTriangles = 
    (domTriangles*)thisMesh->createAndPlace("triangles");
  thisTriangles->setCount(0);
  thisTriangles->setMaterial(thisPolygons->getMaterial());
  domP *p_triangles = (domP*)thisTriangles->createAndPlace("p");

  // Give the new <triangles> the same <_dae> and <parameters> as the
  // old <polygons>
  for(size_t i = 0; i < thisPolygons->getInput_array().getCount(); i++)
    thisTriangles->placeElement(thisPolygons->getInput_array()[i]->clone());

  // Get the number of inputs and primitives for the polygons array
  size_t numberOfInputs = getMaxOffset(thisPolygons->getInput_array()) + 1;
  size_t numberOfPrimitives = thisPolygons->getP_array().getCount();

  // Triangulate all the primitives, this generates all the triangles
  // in a single <p> element
  for(size_t j = 0; j < numberOfPrimitives; j++)
    {
      // Check the polygons for consistancy (some exported files have
      // had the wrong number of indices)
      domP *thisPrimitive = thisPolygons->getP_array()[j];
      size_t elementCount = thisPrimitive->getValue().getCount();
      if((elementCount % numberOfInputs) != 0)
        {
          std::cerr << "Primitive " << j 
          << " has an element count " << elementCount 
          << " not divisible by the number of inputs " 
          << numberOfInputs << "\n";
        }
      else
        {
          size_t triangleCount = (elementCount / numberOfInputs) - 2;
          // Write out the primitives as triangles, just fan using the
          // first element as the base
          size_t idx = numberOfInputs;
          for(size_t k = 0; k < triangleCount; k++)
            {
              // First vertex
              for(size_t l = 0; l < numberOfInputs; l++)
                p_triangles->getValue().append(thisPrimitive->getValue()[l]);
              // Second vertex
              for(size_t l = 0; l < numberOfInputs; l++)
                p_triangles->getValue().append(thisPrimitive->getValue()[idx + l]);
              // Third vertex
              idx += numberOfInputs;
              for(size_t l = 0; l < numberOfInputs; l++)
                p_triangles->getValue().append(thisPrimitive->getValue()[idx + l]);
              thisTriangles->setCount(thisTriangles->getCount()+1);
            }
        }
    }
}


int
triangulate(DAE * dae)
{
  int error = 0;

  // How many geometry elements are there?
  size_t geometryElementCount = 
  dae->getDatabase()->getElementCount(NULL, "geometry");
  std::cout << "There are " << geometryElementCount 
            << " geometry elements in this file\n"; 

  for(size_t currentGeometry = 0; currentGeometry < geometryElementCount; currentGeometry++)
    {
      // Find the next geometry element
      domGeometry *thisGeometry;
      //error = dae->getDatabase()->getElement((daeElement**)&thisGeometry,currentGeometry, NULL, "geometry");
      daeElement *element = 0;
      error = dae->getDatabase()->getElement(&element, 
					     currentGeometry, 
					     NULL, 
					     "geometry");
      thisGeometry = (domGeometry*)element;

      // Get the mesh out of the geometry
      domMesh *thisMesh = thisGeometry->getMesh();

      if(thisMesh == NULL)
        continue;

      // Loop over all the polygon elements
      size_t polygons_count = thisMesh->getPolygons_array().getCount();
      for(size_t currentPolygons = 0; currentPolygons < polygons_count; currentPolygons++)
        {
          // Get the polygons out of the mesh
          // Always get index 0 because every pass through this loop
          // deletes the <polygons> element as it finishes with it
          domPolygons *thisPolygons = 
          thisMesh->getPolygons_array()[currentPolygons];  
          createTrianglesFromPolygons(thisMesh, thisPolygons);
          // Remove the polygons from the mesh
          //thisMesh->removeChildElement(thisPolygons);
        }
      while(thisMesh->getPolygons_array().getCount() > 0)
        {
          domPolygons *thisPolygons = thisMesh->getPolygons_array().get(0);  
          // Remove the polygons from the mesh
          thisMesh->removeChildElement(thisPolygons);
        }
      size_t polylistElementCount = thisMesh->getPolylist_array().getCount();
      std::cout << "There are " << polylistElementCount 
                << " polylist elements in this file\n"; 
      for(size_t currentPolylist = 0; currentPolylist < polylistElementCount; currentPolylist++)
        {
          // Get the polylist out of the mesh
          // Always get index 0 because every pass through this loop
          // deletes the <polygons> element as it finishes with it
          domPolylist *thisPolylist = 
          thisMesh->getPolylist_array()[currentPolylist];  
          createTrianglesFromPolylist(thisMesh, thisPolylist);
          // Remove the polylist from the mesh
          //thisMesh->removeChildElement(thisPolylist);
        }
      while(thisMesh->getPolylist_array().getCount() > 0)
        {
          domPolylist *thisPolylist = thisMesh->getPolylist_array().get(0);  
          // Remove the polylist from the mesh
          thisMesh->removeChildElement(thisPolylist);
        }
    }
  return error;
}
