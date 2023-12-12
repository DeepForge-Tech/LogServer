cmake_minimum_required(VERSION 3.21)
project(Server)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_CXX_STANDARD 20)
include (GNUInstallDirs)
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_FIND_LIBRARY_SUFFIXES .a .so .dylib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/lib)

# jsoncpp
FetchContent_Declare(jsoncpp
  GIT_REPOSITORY https://github.com/DeepForge-Technology/jsoncpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(jsoncpp)

# SQLite 3
FetchContent_Declare(SQLite
  GIT_REPOSITORY https://github.com/DeepForge-Technology/SQLite.git
  GIT_TAG master
)
FetchContent_MakeAvailable(SQLite)

include_directories("./src/include")
set(SOURCE_FILES
    ./src/Server/Server.cpp
    ./src/Server/DatabaseConnect.cpp
    ./src/Server/DatabaseConnect.hpp
)
add_executable(Server ${SOURCE_FILES})
add_subdirectory(./src/Client/)
if (WIN32)
  set(LIBRARIES
    urlmon
    jsoncpp_static
    ws2_32
    SQLite
    winmm
  )
elseif(APPLE)
  set(LIBRARIES
    jsoncpp_static
    SQLite
  )
elseif(UNIX)
  set(LIBRARIES
    jsoncpp_static
    SQLite
  )
endif()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS}-DCURL_STATICLIB -static-libgcc -static-libstdc++ -Bstatic")
target_link_libraries(Server 
  PRIVATE  
  ${LIBRARIES}
) 