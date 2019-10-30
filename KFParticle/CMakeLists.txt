set(SOURCES
  KFParticle.cxx
  KFParticleBase.cxx
  KFParticleBaseSIMD.cxx
  KFParticleDatabase.cxx
  KFParticleFinder.cxx
  KFParticlePVReconstructor.cxx
  KFParticleSIMD.cxx
  KFParticleTopoReconstructor.cxx
  KFPEmcCluster.cxx
  KFPTrack.cxx
  KFPTrackVector.cxx
  KFPVertex.cxx
  KFVertex.cxx
  )

string(REPLACE ".cxx" ".h" HEADERS "${SOURCES}")
list(APPEND HEADERS "KFParticleDef.h" "KFParticleField.h" "KFPInputData.h" "KFPSimdAllocator")

add_library(KFParticleMain SHARED ${SOURCES} G__KFParticleMain.cxx)
        
if(ROOT_FOUND)
  ROOT_GENERATE_DICTIONARY(G__KFParticleMain ${HEADERS} LINKDEF KFParticleMainLinkDef.h)        
  target_link_libraries(KFParticleMain ${ROOT_LIBRARIES})
endif(ROOT_FOUND)  



install(TARGETS KFParticleMain EXPORT KFParticleTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include/KFPF
        )

install(
        FILES
        ${HEADERS}
        DESTINATION
        include/KFPF
        COMPONENT
        Devel
)

set(PCM_FILE_NAME libKFParticleMain)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PCM_FILE_NAME}_rdict.pcm"
        DESTINATION
        lib
        OPTIONAL
)
