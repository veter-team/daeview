project(collada-view)

SET(COCKPIT_VERSION 0.1+devel)
SET(PROJECT_NAME collada-view)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(OpenGL REQUIRED)
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS filesystem system)


add_definitions(-DPCRE_STATIC -DDOM_INCLUDE_LIBXML -DGLEW_STATIC)

SET(COLLADA_VIEW_INCDIR ${PROJECT_SOURCE_DIR}/../../include/collada-view)

include_directories(${PROJECT_SOURCE_DIR}/../../include/collada-dom 
                    ${PROJECT_SOURCE_DIR}/../../include/collada-dom/1.4
                    ${COLLADA_VIEW_INCDIR}
                    ${PROJECT_SOURCE_DIR}/../../include
                    ${bullet-physics_SOURCE_DIR}/src
                    ${Boost_INCLUDE_DIRS}
                    ${SDL_INCLUDE_DIR}
                    ${SDLIMAGE_INCLUDE_DIR})

link_directories(${collada-dom-1.4_BINARY_DIR})

if(NOT WIN32)
  SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wall")
endif(NOT WIN32)

SET(CPPFILES 
    glew.c
    colladautils.cpp
    comdefs.cpp
    gltools.cpp
    deindexer.cpp
    triangulation.cpp
    Node.cpp
    Camera.cpp
    Animation.cpp
    SceneReadAnimation.cpp
    SceneReadEffect.cpp
    SceneReadMaterial.cpp
    SceneReadImage.cpp
    SceneReadNodeTransforms.cpp
    SceneReadGeometry.cpp
    SceneReadLight.cpp
    SceneReadCamera.cpp
    Scene.cpp
    Shaders.cpp
    NodePainter.cpp
    DefaultRenderer.cpp
    SceneGraph.cpp)

SET(HEADERS
    ${COLLADA_VIEW_INCDIR}/Animation.h
    ${COLLADA_VIEW_INCDIR}/Light.h
    ${COLLADA_VIEW_INCDIR}/Camera.h
    ${COLLADA_VIEW_INCDIR}/comdefs.h
    ${COLLADA_VIEW_INCDIR}/PolyGroups.h
    ${COLLADA_VIEW_INCDIR}/Texture.h
    ${COLLADA_VIEW_INCDIR}/Material.h
    ${COLLADA_VIEW_INCDIR}/Geometry.h
    ${COLLADA_VIEW_INCDIR}/Node.h
    ${COLLADA_VIEW_INCDIR}/Scene.h
    ${COLLADA_VIEW_INCDIR}/NodePainter.h
    ${COLLADA_VIEW_INCDIR}/DefaultRenderer.h
    ${COLLADA_VIEW_INCDIR}/SceneGraph.h
    colladautils.h
    deindexer.h
    gltools.h
    Shaders.h
    triangulation.h)

SET(LIBRARIES
    collada-dom-1.4
    LinearMath
    ${OPENGL_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY})

add_library(collada-view 
            ${CPPFILES}
            ${HEADERS})

if(WIN32)
  target_link_libraries(collada-view
                        ${LIBRARIES})
else(WIN32)
  target_link_libraries(collada-view
                        ${LIBRARIES}
                        ${Boost_LIBRARIES})
endif(WIN32) 

install(TARGETS collada-view
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

FILE(GLOB files "${PROJECT_SOURCE_DIR}/../include/collada-view/*.h")
INSTALL(FILES ${files} DESTINATION include/collada-view)
