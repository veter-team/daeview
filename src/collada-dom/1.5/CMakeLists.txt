project(collada-dom-1.5)

SET(LIBOBJREADER_VERSION 0.1+devel)
SET(PROJECT_NAME collada-dom-1.5)

find_package(ZLIB REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(Boost REQUIRED)

add_definitions(-DPCRE_STATIC -DDOM_INCLUDE_LIBXML)

include_directories(${LIBXML2_INCLUDE_DIR}
                    ${ZLIB_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/../../minizip
                    ${PROJECT_SOURCE_DIR}/../../../include/collada-dom 
                    ${PROJECT_SOURCE_DIR}/../../../include/collada-dom/1.5
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

add_library(collada-dom-1.5
            ${DAE}
            ${MODULES}
            dom/domAccessor.cpp
            dom/domAnimation.cpp
            dom/domAnimation_clip.cpp
            dom/domArticulated_system.cpp
            dom/domAsset.cpp
            dom/domAxis.cpp
            dom/domAxis_constraint.cpp
            dom/domBind_joint_axis.cpp
            dom/domBind_kinematics_model.cpp
            dom/domBind_material.cpp
            dom/domBool_array.cpp
            dom/domBox.cpp
            dom/domBrep.cpp
            dom/domCamera.cpp
            dom/domCapsule.cpp
            dom/domCg_array.cpp
            dom/domCg_newparam.cpp
            dom/domCg_param.cpp
            dom/domCg_pass.cpp
            dom/domCg_setparam.cpp
            dom/domCg_user.cpp
            dom/domChannel.cpp
            dom/domCircle.cpp
            dom/domCOLLADA.cpp
            dom/domCommon_bool_or_param.cpp
            dom/domCommon_float2_or_param.cpp
            dom/domCommon_float_or_param.cpp
            dom/domCommon_int_or_param.cpp
            dom/domCommon_param.cpp
            dom/domCommon_sidref_or_param.cpp
            dom/domCone.cpp
            dom/domConstants.cpp
            dom/domController.cpp
            dom/domConvex_mesh.cpp
            dom/domCurve.cpp
            dom/domCurves.cpp
            dom/domCylinder.cpp
            dom/domEdges.cpp
            dom/domEffect.cpp
            dom/domEllipse.cpp
            dom/domEllipsoid.cpp
            dom/domExtra.cpp
            dom/domFaces.cpp
            dom/domFloat_array.cpp
            dom/domForce_field.cpp
            dom/domFormula.cpp
            dom/domFormula_newparam.cpp
            dom/domFormula_setparam.cpp
            dom/domFormula_technique.cpp
            dom/domFx_annotate.cpp
            dom/domFx_clearcolor.cpp
            dom/domFx_cleardepth.cpp
            dom/domFx_clearstencil.cpp
            dom/domFx_code.cpp
            dom/domFx_colortarget.cpp
            dom/domFx_common_color_or_texture.cpp
            dom/domFx_common_float_or_param.cpp
            dom/domFx_common_newparam.cpp
            dom/domFx_common_transparent.cpp
            dom/domFx_depthtarget.cpp
            dom/domFx_include.cpp
            dom/domFx_newparam.cpp
            dom/domFx_profile.cpp
            dom/domFx_rendertarget.cpp
            dom/domFx_sampler.cpp
            dom/domFx_sampler1D.cpp
            dom/domFx_sampler2D.cpp
            dom/domFx_sampler3D.cpp
            dom/domFx_samplerCUBE.cpp
            dom/domFx_samplerDEPTH.cpp
            dom/domFx_samplerRECT.cpp
            dom/domFx_sampler_states.cpp
            dom/domFx_setparam.cpp
            dom/domFx_sources.cpp
            dom/domFx_stenciltarget.cpp
            dom/domFx_target.cpp
            dom/domGeometry.cpp
            dom/domGles2_newparam.cpp
            dom/domGles2_pass.cpp
            dom/domGles2_pipeline_settings.cpp
            dom/domGles2_program.cpp
            dom/domGles2_shader.cpp
            dom/domGles2_value.cpp
            dom/domGles_newparam.cpp
            dom/domGles_param.cpp
            dom/domGles_pipeline_settings.cpp
            dom/domGles_sampler.cpp
            dom/domGles_sampler_states.cpp
            dom/domGles_texcombiner_argument_alpha.cpp
            dom/domGles_texcombiner_argument_rgb.cpp
            dom/domGles_texcombiner_command.cpp
            dom/domGles_texcombiner_command_alpha.cpp
            dom/domGles_texcombiner_command_rgb.cpp
            dom/domGles_texenv_command.cpp
            dom/domGles_texture_constant.cpp
            dom/domGles_texture_pipeline.cpp
            dom/domGlsl_array.cpp
            dom/domGlsl_newparam.cpp
            dom/domGlsl_program.cpp
            dom/domGlsl_shader.cpp
            dom/domGlsl_value.cpp
            dom/domGl_pipeline_settings.cpp
            dom/domHyperbola.cpp
            dom/domIdref_array.cpp
            dom/domImage.cpp
            dom/domImage_mips.cpp
            dom/domImage_source.cpp
            dom/domInput_global.cpp
            dom/domInput_local.cpp
            dom/domInput_local_offset.cpp
            dom/domInstance_articulated_system.cpp
            dom/domInstance_camera.cpp
            dom/domInstance_controller.cpp
            dom/domInstance_effect.cpp
            dom/domInstance_force_field.cpp
            dom/domInstance_formula.cpp
            dom/domInstance_geometry.cpp
            dom/domInstance_image.cpp
            dom/domInstance_joint.cpp
            dom/domInstance_kinematics_model.cpp
            dom/domInstance_kinematics_scene.cpp
            dom/domInstance_light.cpp
            dom/domInstance_material.cpp
            dom/domInstance_node.cpp
            dom/domInstance_physics_material.cpp
            dom/domInstance_physics_model.cpp
            dom/domInstance_rigid_body.cpp
            dom/domInstance_rigid_constraint.cpp
            dom/domInstance_with_extra.cpp
            dom/domInt_array.cpp
            dom/domJoint.cpp
            dom/domJoint_limits.cpp
            dom/domKinematics.cpp
            dom/domKinematics_axis_info.cpp
            dom/domKinematics_bind.cpp
            dom/domKinematics_connect_param.cpp
            dom/domKinematics_frame.cpp
            dom/domKinematics_index.cpp
            dom/domKinematics_limits.cpp
            dom/domKinematics_model.cpp
            dom/domKinematics_model_technique.cpp
            dom/domKinematics_newparam.cpp
            dom/domKinematics_param.cpp
            dom/domKinematics_scene.cpp
            dom/domKinematics_setparam.cpp
            dom/domKinematics_technique.cpp
            dom/domLibrary_animations.cpp
            dom/domLibrary_animation_clips.cpp
            dom/domLibrary_articulated_systems.cpp
            dom/domLibrary_cameras.cpp
            dom/domLibrary_controllers.cpp
            dom/domLibrary_effects.cpp
            dom/domLibrary_force_fields.cpp
            dom/domLibrary_formulas.cpp
            dom/domLibrary_geometries.cpp
            dom/domLibrary_images.cpp
            dom/domLibrary_joints.cpp
            dom/domLibrary_kinematics_models.cpp
            dom/domLibrary_kinematics_scenes.cpp
            dom/domLibrary_lights.cpp
            dom/domLibrary_materials.cpp
            dom/domLibrary_nodes.cpp
            dom/domLibrary_physics_materials.cpp
            dom/domLibrary_physics_models.cpp
            dom/domLibrary_physics_scenes.cpp
            dom/domLibrary_visual_scenes.cpp
            dom/domLight.cpp
            dom/domLimits_sub.cpp
            dom/domLine.cpp
            dom/domLines.cpp
            dom/domLinestrips.cpp
            dom/domLink.cpp
            dom/domLookat.cpp
            dom/domMaterial.cpp
            dom/domMatrix.cpp
            dom/domMesh.cpp
            dom/domMinmax.cpp
            dom/domMorph.cpp
            dom/domMotion.cpp
            dom/domMotion_axis_info.cpp
            dom/domMotion_effector_info.cpp
            dom/domMotion_technique.cpp
            dom/domName_array.cpp
            dom/domNode.cpp
            dom/domNurbs.cpp
            dom/domNurbs_surface.cpp
            dom/domOrient.cpp
            dom/domOrigin.cpp
            dom/domP.cpp
            dom/domParabola.cpp
            dom/domParam.cpp
            dom/domPcurves.cpp
            dom/domPhysics_material.cpp
            dom/domPhysics_model.cpp
            dom/domPhysics_scene.cpp
            dom/domPlane.cpp
            dom/domPolygons.cpp
            dom/domPolylist.cpp
            dom/domProfile_bridge.cpp
            dom/domProfile_cg.cpp
            dom/domProfile_common.cpp
            dom/domProfile_gles.cpp
            dom/domProfile_gles2.cpp
            dom/domProfile_glsl.cpp
            dom/domRigid_body.cpp
            dom/domRigid_constraint.cpp
            dom/domRotate.cpp
            dom/domSampler.cpp
            dom/domScale.cpp
            dom/domShells.cpp
            dom/domSidref_array.cpp
            dom/domSkew.cpp
            dom/domSkin.cpp
            dom/domSolids.cpp
            dom/domSource.cpp
            dom/domSphere.cpp
            dom/domSpline.cpp
            dom/domSurface.cpp
            dom/domSurfaces.cpp
            dom/domSurface_curves.cpp
            dom/domSwept_surface.cpp
            dom/domTargetable_float.cpp
            dom/domTargetable_float3.cpp
            dom/domTargetable_float4.cpp
            dom/domTechnique.cpp
            dom/domToken_array.cpp
            dom/domTorus.cpp
            dom/domTranslate.cpp
            dom/domTriangles.cpp
            dom/domTrifans.cpp
            dom/domTristrips.cpp
            dom/domTypes.cpp
            dom/domVertices.cpp
            dom/domVisual_scene.cpp
            dom/domWires.cpp
            )

target_link_libraries(collada-dom-1.5
                      pcre
                      pcrecpp
                      ${LIBXML2_LIBRARIES}
                      ${ZLIB_LIBRARIES})

install(TARGETS collada-dom-1.5
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

FILE(GLOB files "${PROJECT_SOURCE_DIR}/../include/collada-dom-1.5/*.h")
INSTALL(FILES ${files} DESTINATION include/collada-dom-1.5)
