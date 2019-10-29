set(SOURCES
  KFParticleTest.cxx
  )

string(REPLACE ".cxx" ".h" HEADERS "${SOURCES}")
# message(STATUS ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/KFParticle ${CMAKE_SOURCE_DIR}/KFParticleTest)

add_library(KFParticleTest SHARED ${SOURCES} G__KFParticleTest.cxx)
        
if(ROOT_FOUND)
  ROOT_GENERATE_DICTIONARY(G__KFParticleTest ${HEADERS} LINKDEF KFParticleTestLinkDef.h)        
  target_link_libraries(KFParticleTest ${ROOT_LIBRARIES} KFParticleMain)
endif(ROOT_FOUND)  

install(TARGETS KFParticleTest EXPORT KFParticleTargets
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

set(PCM_FILE_NAME libKFParticleTest)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PCM_FILE_NAME}_rdict.pcm"
        DESTINATION
        lib
        OPTIONAL
)
