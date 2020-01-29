set(SOURCES
#   KFParticleTopoReconstructor.cxx
  KFVertex.cxx
  KFPTrack.cxx
  KFPTrackVector.cxx
  KFPVertex.cxx
#   KFParticlePVReconstructor.cxx
  KFParticleDatabase.cxx
  KFParticleBase.cxx
  KFParticleBaseSIMD.cxx
  KFParticle.cxx
  KFParticleSIMD.cxx
#   KFParticleFinder.cxx
  KFPEmcCluster.cxx
  MFMap.cxx
#   MFHistos.cxx
  )

set (HEADERS
  KFParticleBase.h
  KFParticle.h
  KFVertex.h
  MFMap.h
  )

add_library(KFParticle SHARED ${SOURCES} G__KFParticle.cxx)
        
if(ROOT_FOUND)
  ROOT_GENERATE_DICTIONARY(G__KFParticle ${HEADERS} LINKDEF KFParticleLinkDef.h OPTIONS "-DDO_TPCCATRACKER_EFF_PERFORMANCE" "-DNonhomogeneousField" "-DCBM" "-DUSE_TIMERS")
  target_link_libraries(KFParticle ${ROOT_LIBRARIES} ${Vc_LIBRARIES})
endif(ROOT_FOUND)

add_target_property(KFParticle COMPILE_FLAGS "-DDO_TPCCATRACKER_EFF_PERFORMANCE -DNonhomogeneousField -DCBM -DUSE_TIMERS")

Set(NODICT_HEADERS
#   KFParticleTopoReconstructor.h
#   KFParticlePVReconstructor.h
  KFPVertex.h
  KFPTrack.h
#   KFParticleFinder.h
  KFParticleSIMD.h
  KFParticleBaseSIMD.h
  KFParticleDef.h
  KFPSimdAllocator.h
  KFPTrackVector.h
  KFPEmcCluster.h
  KFParticleField.h
  KFPTrackVector.h
  KFParticleDatabase.h
  KFPInputData.h
#   MFHistos.h
)

set(PCM_FILE_NAME libKFParticle)
install(FILES ${HEADERS} ${NODICT_HEADERS} DESTINATION include)
#install(FILES ${CMAKE_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}KFParticle.rootmap DESTINATION lib)

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
