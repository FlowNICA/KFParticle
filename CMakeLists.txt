cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

project(KFParticleLibrary)
set(PROJECT_VERSION 1.0)
include(ExternalProject)

# by default build optimized code with debug symbols
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RELWITHDEBINFO)
endif ()

# in DEBUG mode make verbose Makefile
if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif ()

# set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -g -DDEBUG -D__DEBUG -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -DDEBUG -D__DEBUG -Wall")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -ftree-vectorize -ffast-math -DNODEBUG")
message(STATUS "Using CXX flags for ${CMAKE_BUILD_TYPE}: ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

macro(add_target_property _target _prop _value)
  get_target_property(_oldprop "${_target}" ${_prop})
  if(NOT _oldprop)
    set_target_properties("${_target}" PROPERTIES ${_prop} "${_value}")
  else(NOT _oldprop)
    set_target_properties("${_target}" PROPERTIES ${_prop} "${_oldprop} ${_value}")
  endif(NOT _oldprop)
endmacro(add_target_property)

if (CMAKE_VERSION VERSION_LESS "3.1")
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
endif ()
else ()
  set (CMAKE_CXX_STANDARD 11)
endif ()

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS} ${ROOTSYS})

# set(FIXTARGET FALSE CACHE BOOL "Compile for collider geometry.")
set(FIXTARGET TRUE CACHE BOOL "Compile for fix target geometry.")

find_package(ROOT REQUIRED COMPONENTS Core Hist Matrix Physics EG Gpad Graf Graf3d RIO MathCore)
find_package(Vc QUIET)

if(Vc_FOUND)
  Message("Vc found")
Else()
  Message("Vc is not found. It will be installed as external package")
  set(EXTERNAL_DIR ${CMAKE_BINARY_DIR}/external)
  set(EXTERNAL_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/external)
  include(cmake_modules/Vc.cmake)
EndIf()

if (ROOT_FOUND)
  message(STATUS "Using ROOT: ${ROOT_VERSION} <${ROOT_CONFIG}>")
  include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS})
  include(${ROOT_USE_FILE})
endif (ROOT_FOUND)

include(${ROOT_USE_FILE})
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
Include_Directories( ${CMAKE_SOURCE_DIR} ${Vc_INCLUDE_DIR} ${INCLUDE_DIRECTORIES} KFParticle)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE OFF)

add_subdirectory(KFParticle)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
       "${CMAKE_CURRENT_BINARY_DIR}/KFParticleMain/KFParticleConfigVersion.cmake"
       VERSION ${PROJECT_VERSION}
       COMPATIBILITY AnyNewerVersion
)

export(EXPORT KFParticleTargets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/KFParticleMain/KFParticleTargets.cmake")

message(STATUS "KFParticleTargets: ${KFParticleTargets}")

set(ConfigPackageLocation lib/cmake/KFParticle)

set(KFParticle_INCLUDE_DIR "include")
set(KFParticle_LIBRARY_DIR "lib")

configure_package_config_file(
       KFParticleConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/KFParticleMain/KFParticleConfig.cmake
       INSTALL_DESTINATION ${ConfigPackageLocation}
       PATH_VARS KFParticle_INCLUDE_DIR KFParticle_LIBRARY_DIR
)

install(EXPORT KFParticleTargets
       FILE
       KFParticleTargets.cmake
       DESTINATION
       ${ConfigPackageLocation}
       )

install(FILES
       "${CMAKE_CURRENT_BINARY_DIR}/KFParticleMain/KFParticleConfig.cmake"
       "${CMAKE_CURRENT_BINARY_DIR}/KFParticleMain/KFParticleConfigVersion.cmake"
       DESTINATION
       ${ConfigPackageLocation}
       COMPONENT
       Devel
       )

# install(FILES ${HEADERS} ${NODICT_HEADERS} DESTINATION include)
# install(FILES ${CMAKE_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}KFParticle_rdict.pcm DESTINATION lib OPTIONAL)
# install(FILES ${CMAKE_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}KFParticle.rootmap DESTINATION lib)
# install(TARGETS KFParticle DESTINATION lib)
