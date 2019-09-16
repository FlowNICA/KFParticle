# Install script for directory: /home/user/cbmdir/kfpf/KFParticle

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleBase.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticle.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFVertex.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFPartEfficiencies.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFMCParticle.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticleTest/KFParticleTest.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleTopoReconstructor.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticlePVReconstructor.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFPVertex.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFPTrack.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleFinder.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleSIMD.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleBaseSIMD.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleDef.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFPSimdAllocator.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFPTrackVector.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFPEmcCluster.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleField.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFPTrackVector.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleDatabase.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFTopoPerformance.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFParticlePerformanceBase.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFMCCounter.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFPVEfficiencies.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFMCVertex.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFMCTrack.h"
    "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFPartMatch.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE OPTIONAL FILES "/home/user/cbmdir/kfpf/KFParticle/build/libKFParticle_rdict.pcm")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/home/user/cbmdir/kfpf/KFParticle/build/libKFParticle.rootmap")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKFParticle.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKFParticle.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKFParticle.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/user/cbmdir/kfpf/KFParticle/build/libKFParticle.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKFParticle.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKFParticle.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKFParticle.so"
         OLD_RPATH "/home/user/Root6/build/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKFParticle.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/user/cbmdir/kfpf/KFParticle/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
