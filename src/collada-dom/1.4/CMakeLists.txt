project(collada-dom-1.4)

SET(LIBOBJREADER_VERSION 0.1+devel)
SET(PROJECT_NAME collada-dom-1.4)

find_package(ZLIB REQUIRED)
find_package(LibXml2 REQUIRED)
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS system)

add_definitions(-DPCRE_STATIC -DDOM_INCLUDE_LIBXML)

include_directories(${LIBXML2_INCLUDE_DIR}
                    ${ZLIB_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/../../minizip
                    ${PROJECT_SOURCE_DIR}/../../../include/collada-dom 
                    ${PROJECT_SOURCE_DIR}/../../../include/collada-dom/1.4
                    ${Boost_INCLUDE_DIRS})

INCLUDE(${PROJECT_SOURCE_DIR}/../dae/CMakeLists.txt)
INCLUDE(${PROJECT_SOURCE_DIR}/../modules/CMakeLists.txt)

SET(DAE_TMP)
foreach(l IN LISTS DAE)
  list(APPEND DAE_TMP ${PROJECT_SOURCE_DIR}/../dae/${l})
endforeach()
SET(DAE "${DAE_TMP}")
UNSET(DAE_TMP)

SET(MODULES_TMP)
foreach(l IN LISTS MODULES)
  list(APPEND MODULES_TMP ${PROJECT_SOURCE_DIR}/../modules/${l})
endforeach()
SET(MODULES "${MODULES_TMP}")
UNSET(MODULES_TMP)

add_library(collada-dom-1.4
            ${DAE}
            ${MODULES}
            ${PROJECT_SOURCE_DIR}/../../minizip/unzip.c
            ${PROJECT_SOURCE_DIR}/../../minizip/ioapi.c
            dom/domAccessor.cpp
            dom/domAnimation.cpp
            dom/domAnimation_clip.cpp
            dom/domAsset.cpp
            dom/domBind_material.cpp
            dom/domBool_array.cpp
            dom/domBox.cpp
            dom/domCamera.cpp
            dom/domCapsule.cpp
            dom/domCg_connect_param.cpp
            dom/domCg_newarray_type.cpp
            dom/domCg_newparam.cpp
            dom/domCg_param_type.cpp
            dom/domCg_sampler1D.cpp
            dom/domCg_sampler2D.cpp
            dom/domCg_sampler3D.cpp
            dom/domCg_samplerCUBE.cpp
            dom/domCg_samplerDEPTH.cpp
            dom/domCg_samplerRECT.cpp
            dom/domCg_setarray_type.cpp
            dom/domCg_setparam.cpp
            dom/domCg_setparam_simple.cpp
            dom/domCg_setuser_type.cpp
            dom/domCg_surface_type.cpp
            dom/domChannel.cpp
            dom/domCOLLADA.cpp
            dom/domCommon_color_or_texture_type.cpp
            dom/domCommon_float_or_param_type.cpp
            dom/domCommon_newparam_type.cpp
            dom/domCommon_transparent_type.cpp
            dom/domConstants.cpp
            dom/domController.cpp
            dom/domConvex_mesh.cpp
            dom/domCylinder.cpp
            dom/domEffect.cpp
            dom/domEllipsoid.cpp
            dom/domExtra.cpp
            dom/domFloat_array.cpp
            dom/domForce_field.cpp
            dom/domFx_annotate_common.cpp
            dom/domFx_annotate_type_common.cpp
            dom/domFx_basic_type_common.cpp
            dom/domFx_clearcolor_common.cpp
            dom/domFx_cleardepth_common.cpp
            dom/domFx_clearstencil_common.cpp
            dom/domFx_code_profile.cpp
            dom/domFx_colortarget_common.cpp
            dom/domFx_depthtarget_common.cpp
            dom/domFx_include_common.cpp
            dom/domFx_newparam_common.cpp
            dom/domFx_profile_abstract.cpp
            dom/domFx_sampler1D_common.cpp
            dom/domFx_sampler2D_common.cpp
            dom/domFx_sampler3D_common.cpp
            dom/domFx_samplerCUBE_common.cpp
            dom/domFx_samplerDEPTH_common.cpp
            dom/domFx_samplerRECT_common.cpp
            dom/domFx_stenciltarget_common.cpp
            dom/domFx_surface_common.cpp
            dom/domFx_surface_format_hint_common.cpp
            dom/domFx_surface_init_common.cpp
            dom/domFx_surface_init_cube_common.cpp
            dom/domFx_surface_init_from_common.cpp
            dom/domFx_surface_init_planar_common.cpp
            dom/domFx_surface_init_volume_common.cpp
            dom/domGeometry.cpp
            dom/domGles_basic_type_common.cpp
            dom/domGles_newparam.cpp
            dom/domGles_pipeline_settings.cpp
            dom/domGles_sampler_state.cpp
            dom/domGles_texcombiner_argumentAlpha_type.cpp
            dom/domGles_texcombiner_argumentRGB_type.cpp
            dom/domGles_texcombiner_commandAlpha_type.cpp
            dom/domGles_texcombiner_commandRGB_type.cpp
            dom/domGles_texcombiner_command_type.cpp
            dom/domGles_texenv_command_type.cpp
            dom/domGles_texture_constant_type.cpp
            dom/domGles_texture_pipeline.cpp
            dom/domGles_texture_unit.cpp
            dom/domGlsl_newarray_type.cpp
            dom/domGlsl_newparam.cpp
            dom/domGlsl_param_type.cpp
            dom/domGlsl_setarray_type.cpp
            dom/domGlsl_setparam.cpp
            dom/domGlsl_setparam_simple.cpp
            dom/domGlsl_surface_type.cpp
            dom/domGl_hook_abstract.cpp
            dom/domGl_pipeline_settings.cpp
            dom/domGl_sampler1D.cpp
            dom/domGl_sampler2D.cpp
            dom/domGl_sampler3D.cpp
            dom/domGl_samplerCUBE.cpp
            dom/domGl_samplerDEPTH.cpp
            dom/domGl_samplerRECT.cpp
            dom/domIDREF_array.cpp
            dom/domImage.cpp
            dom/domInputGlobal.cpp
            dom/domInputLocal.cpp
            dom/domInputLocalOffset.cpp
            dom/domInstanceWithExtra.cpp
            dom/domInstance_camera.cpp
            dom/domInstance_controller.cpp
            dom/domInstance_effect.cpp
            dom/domInstance_force_field.cpp
            dom/domInstance_geometry.cpp
            dom/domInstance_light.cpp
            dom/domInstance_material.cpp
            dom/domInstance_node.cpp
            dom/domInstance_physics_material.cpp
            dom/domInstance_physics_model.cpp
            dom/domInstance_rigid_body.cpp
            dom/domInstance_rigid_constraint.cpp
            dom/domInt_array.cpp
            dom/domLibrary_animations.cpp
            dom/domLibrary_animation_clips.cpp
            dom/domLibrary_cameras.cpp
            dom/domLibrary_controllers.cpp
            dom/domLibrary_effects.cpp
            dom/domLibrary_force_fields.cpp
            dom/domLibrary_geometries.cpp
            dom/domLibrary_images.cpp
            dom/domLibrary_lights.cpp
            dom/domLibrary_materials.cpp
            dom/domLibrary_nodes.cpp
            dom/domLibrary_physics_materials.cpp
            dom/domLibrary_physics_models.cpp
            dom/domLibrary_physics_scenes.cpp
            dom/domLibrary_visual_scenes.cpp
            dom/domLight.cpp
            dom/domLines.cpp
            dom/domLinestrips.cpp
            dom/domLookat.cpp
            dom/domMaterial.cpp
            dom/domMatrix.cpp
            dom/domMesh.cpp
            dom/domMorph.cpp
            dom/domName_array.cpp
            dom/domNode.cpp
            dom/domP.cpp
            dom/domParam.cpp
            dom/domPhysics_material.cpp
            dom/domPhysics_model.cpp
            dom/domPhysics_scene.cpp
            dom/domPlane.cpp
            dom/domPolygons.cpp
            dom/domPolylist.cpp
            dom/domProfile_CG.cpp
            dom/domProfile_COMMON.cpp
            dom/domProfile_GLES.cpp
            dom/domProfile_GLSL.cpp
            dom/domRigid_body.cpp
            dom/domRigid_constraint.cpp
            dom/domRotate.cpp
            dom/domSampler.cpp
            dom/domScale.cpp
            dom/domSkew.cpp
            dom/domSkin.cpp
            dom/domSource.cpp
            dom/domSphere.cpp
            dom/domSpline.cpp
            dom/domTapered_capsule.cpp
            dom/domTapered_cylinder.cpp
            dom/domTargetableFloat.cpp
            dom/domTargetableFloat3.cpp
            dom/domTechnique.cpp
            dom/domTranslate.cpp
            dom/domTriangles.cpp
            dom/domTrifans.cpp
            dom/domTristrips.cpp
            dom/domTypes.cpp
            dom/domVertices.cpp
            dom/domVisual_scene.cpp
            )

SET(LIBRARIES
	${LIBXML2_LIBRARIES}
	${ZLIB_LIBRARIES}
	${Boost_LIBRARIES})

IF(WIN32 AND MSVC)
  target_link_libraries(collada-dom-1.4
                        ${LIBRARIES} debug pcred debug pcrecppd
                        optimized pcre optimized pcrecpp)
ELSE()
  target_link_libraries(collada-dom-1.4
                        ${LIBRARIES} pcre pcrecpp)
ENDIF()

install(TARGETS collada-dom-1.4
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

FILE(GLOB files "${PROJECT_SOURCE_DIR}/../include/collada-dom-1.4/*.h")
INSTALL(FILES ${files} DESTINATION include/collada-dom-1.4)

