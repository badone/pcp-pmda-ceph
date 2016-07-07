cmake_minimum_required(VERSION 2.6)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(PMDA_NAME "ceph")

project(pmda${PMDA_NAME})

#add_subdirectory(pcp-pmda-cpp)
include_directories ("${PROJECT_SOURCE_DIR}/pcp-pmda-cpp/include")

# Add a pmdaceph target.
add_executable(
    ${PROJECT_NAME}
    ${PROJECT_NAME}.cpp
    cephpmda.cpp
    cephpmda.h
    cephmetricsource.h
)

# Add PCP libraries to the build.
target_link_libraries(${PROJECT_NAME} pcp pcp_pmda)

# Add boost libraries
find_package(Boost COMPONENTS program_options system filesystem REQUIRED)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Enable (and stop on) compiler warnings.
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-Wall   HAVE_WALL)
check_cxx_compiler_flag(-Werror HAVE_WERROR)
check_cxx_compiler_flag(-Wextra HAVE_WEXTRA)
if (HAVE_WALL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()
if (HAVE_WERROR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()
if (HAVE_WEXTRA)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif()
