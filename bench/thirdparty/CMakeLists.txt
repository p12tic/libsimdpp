cmake_minimum_required(VERSION 2.8.0)

#Adapted from https://github.com/dream3d/Dream3DSdkBuild/blob/master/Boost.cmake
message("Create ExternalProject google benchmark has thirdpartie lib")

include(ExternalProject)
# clone approach
find_package(git QUIET)
ExternalProject_Add(googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG master
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}
  #--Configure step-------------
	CMAKE_ARGS
		 -DBUILD_TESTING:BOOL=OFF
		 -DBENCHMARK_ENABLE_TESTING:BOOL=OFF
		 -DBENCHMARK_ENABLE_LTO:BOOL=OFF
		 -DCMAKE_BUILD_TYPE=Release
	#--Build step-----------------
  UPDATE_COMMAND "" # Skip annoying updates for every build
	#--Install step-----------------
	INSTALL_COMMAND ""
  ) 

ExternalProject_Get_Property(googlebenchmark TMP_DIR STAMP_DIR DOWNLOAD_DIR SOURCE_DIR BINARY_DIR INSTALL_DIR)
message("Build googlebenchmark src ${SOURCE_DIR} in ${BINARY_DIR}")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(GOOGLE_BENCHMARK_INCLUDE_DIRS "${SOURCE_DIR}/include")
set(GOOGLE_BENCHMARK_INCLUDE_DIRS ${GOOGLE_BENCHMARK_INCLUDE_DIRS}    PARENT_SCOPE)
set(GOOGLE_BENCHMARK googlebenchmark PARENT_SCOPE)
set_target_properties (googlebenchmark PROPERTIES FOLDER bench)
add_library(benchmark STATIC IMPORTED GLOBAL) #MARK AS IMPORTED AND GLOBAL SCOPE
set_target_properties (benchmark PROPERTIES FOLDER bench)
if(WIN32)
set_target_properties(benchmark PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/src/Release/benchmark.lib)
else()
set_target_properties(benchmark PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/src/libbenchmark.a)
endif()
