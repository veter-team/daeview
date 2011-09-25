cmake_minimum_required(VERSION 2.8)
PROJECT(daeview)


if(WIN32)
  include_directories(/usr/include)
  link_directories(/usr/lib)
endif(WIN32)

add_subdirectory(src/collada-dom/1.4)
#add_subdirectory(src/collada-dom/1.5)
add_subdirectory(src/bullet)
add_subdirectory(src/collada-view)
add_subdirectory(src/daeviewer)

add_dependencies(collada-view collada-dom-1.4)
#add_dependencies(collada-view collada-dom-1.5)
add_dependencies(daeviewer collada-view)
