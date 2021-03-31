cmake_minimum_required(VERSION 2.6)

project(APP_HMI_Persistence_Wrapper)

include_directories(BEFORE SYSTEM ${CMAKE_SOURCE_DIR}/v1/com/harman/persistenceWrapperTypes ${CMAKE_SOURCE_DIR}/v1)
include_directories(./src)
include_directories(${CMAKE_SYSROOT}/usr/include/CommonAPI-3.1)
include_directories(${CMAKE_SYSROOT}/usr/include/capimsgconverter)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread -std=c++11")

OPTION(USE_INSTALLED_COMMONAPI "Set to OFF to use the local (build tree) version of CommonAPI" ON)
message(STATUS "USE_INSTALLED_COMMONAPI is set to value: ${USE_INSTALLED_COMMONAPI}")
if ("${USE_INSTALLED_COMMONAPI}" STREQUAL "ON")
endif()

message(STATUS "CommonAPI_CONSIDERED_CONFIGS: ${CommonAPI_CONSIDERED_CONFIGS}")
message(STATUS "COMMONAPI_INCLUDE_DIRS: ${COMMONAPI_INCLUDE_DIRS}")

include_directories(
${COMMONAPI_INCLUDE_DIRS}
)

link_directories(
${COMMONAPI_LIBDIR}

)

#LINK_DIRECTORIES(${src-gen})


ADD_EXECUTABLE(APP_HMI 
			${CMAKE_SOURCE_DIR}/APP_HMIMain.cpp 
			${CMAKE_SOURCE_DIR}/APP_HMIPersWrapperImpl.cpp) 

target_link_libraries(APP_HMI -lpersistence_client_library -ldl -Wl,--no-undefined,--as-needed CommonAPI capimsgconverter rt)


