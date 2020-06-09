set(SOURCES
  KFVertex.cxx
  KFPTrack.cxx
  KFPTrackVector.cxx
  KFPVertex.cxx
  KFParticleDatabase.cxx
  KFParticleBase.cxx
  KFParticleBaseSIMD.cxx
  KFParticle.cxx
  KFParticleSIMD.cxx
  KFPEmcCluster.cxx
  )

string(REPLACE ".cxx" ".h" HEADERS "${SOURCES}")
list(APPEND HEADERS "KFParticleField.h" "KFPSimdAllocator.h" "KFPInputData.h")

add_library(KFParticle STATIC ${SOURCES} G__KFParticle.cxx)

if(ROOT_FOUND)
  ROOT_GENERATE_DICTIONARY(G__KFParticle ${HEADERS} LINKDEF KFParticleLinkDef.h OPTIONS "-DDO_TPCCATRACKER_EFF_PERFORMANCE" "-DNonhomogeneousField" "-DCBM" "-DUSE_TIMERS")
  target_link_libraries(KFParticle ${ROOT_LIBRARIES} ${Vc_LIBRARIES})
endif(ROOT_FOUND)

add_target_property(KFParticle COMPILE_FLAGS "-DDO_TPCCATRACKER_EFF_PERFORMANCE -DNonhomogeneousField -DCBM -DUSE_TIMERS")

set(PCM_FILE_NAME libKFParticle)
install(FILES ${HEADERS} DESTINATION include)

install(TARGETS KFParticle EXPORT KFParticleTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PCM_FILE_NAME}_rdict.pcm"
        DESTINATION
        lib
        OPTIONAL
)
