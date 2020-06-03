set(SOURCES
  KFMCParticle.cxx
  KFMCVertex.cxx
  KFPartEfficiences.cxx
  KFParticlePerformanceBase.cxx
  KFTopoPerformance.cxx
  KFPHistogram/KFPHistogramSet.cxx
  )

string(REPLACE ".cxx" ".h" HEADERS "${SOURCES}")
list(APPEND HEADERS "KFMCCounter.h" "KFMCTrack.h" "KFPartMatch.h" "KFPVEfficiencies" "KFPHistogram/KFPHistogram.h" "KFPHistogram/KFPHistogram1D.h")
# message(STATUS ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/KFParticle ${CMAKE_SOURCE_DIR}/KFParticlePerformance)

add_library(KFParticlePerformance SHARED ${SOURCES} G__KFParticlePerformance.cxx)
        
if(ROOT_FOUND)
  ROOT_GENERATE_DICTIONARY(G__KFParticlePerformance ${HEADERS} LINKDEF KFParticlePerformanceLinkDef.h)        
  target_link_libraries(KFParticlePerformance ${ROOT_LIBRARIES} KFParticleMain)
endif(ROOT_FOUND)  

install(TARGETS KFParticlePerformance EXPORT KFParticleTargets
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

set(PCM_FILE_NAME libKFParticlePerformance)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PCM_FILE_NAME}_rdict.pcm"
        DESTINATION
        lib
        OPTIONAL
)
