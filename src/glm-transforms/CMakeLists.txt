#http://stackoverflow.com/questions/28395833/using-sdl2-with-cmake

cmake_minimum_required (VERSION 2.6)
project (glm-tests)

include_directories(../../include /usr/local/include/SDL2)


#target_include_directories(transforms01 ${SDL2_INCLUDE_DIR})
#target_link_libraries(transforms01 ${SDL2_LIBRARY})

set( LIBS libSDL2.dylib )
#link_directories(/Users/behollis/SDL2_build)
link_directories(/usr/local/lib)

add_executable(transforms01 transforms01.cxx)
target_link_libraries(transforms01 ${LIBS})
