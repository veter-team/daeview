project(daeviewer)

SET(COCKPIT_VERSION 0.1+devel)
SET(PROJECT_NAME daeviewer)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_definitions(-DGLEW_STATIC)

include_directories(${PROJECT_SOURCE_DIR}/../../include/collada-dom 
                    ${PROJECT_SOURCE_DIR}/../../include/collada-dom/1.4
                    ${PROJECT_SOURCE_DIR}/../../include
                    ${bullet-physics_SOURCE_DIR}/src
                    ${Boost_INCLUDE_DIRS}
                    ${SDL_INCLUDE_DIR})

link_directories(${collada-view_BINARY_DIR})

if(NOT WIN32)
  SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wall")
endif(NOT WIN32)

SET(CPPFILES 
    TxtAreaPainter.cpp
    PrintStatusMsg.cpp
    SetStatusMsgCmd.cpp
    main.cpp)

SET(HEADERS
    AbstractCommand.h
    TxtAreaPainter.h)

SET(LIBRARIES
    collada-view
    ${OPENGL_LIBRARIES}
    ${SDL_LIBRARY})

if(WIN32)
  add_executable(daeviewer 
                 WIN32
                 ${CPPFILES}
                 ${HEADERS})
  target_link_libraries(daeviewer
                        ${LIBRARIES})
else(WIN32)
  add_executable(daeviewer
                 ${CPPFILES}
                 ${HEADERS})
  target_link_libraries(daeviewer
                        ${LIBRARIES}
                        ${Boost_LIBRARIES})
endif(WIN32) 

