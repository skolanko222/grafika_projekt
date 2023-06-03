# cmake - grafika
cmake_minimum_required(VERSION 3.4)
project (main)

set(wxWidgets_ROOT_DIR "C:/wxWidgets-3.2.2.1")
set(wxWidgets_LIB_DIR "C:/wxWidgets-3.2.2.1/lib/gcc_lib")

#find_package(SFML REQUIRED COMPONENTS audio graphics window system)
find_package(wxWidgets REQUIRED COMPONENTS net core base)


# prevent for in-source building
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

add_definitions(-DPROJECTPATH=\"${PROJECT_SOURCE_DIR}\")

set(CMAKE_BUILD_TYPE Debug) #Release
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDES})

include(${wxWidgets_USE_FILE})

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp ${SOURCES})
#target_link_options(${PROJECT_NAME} PUBLIC -lsfml-system -lsfml-graphics -lsfml-window)
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

