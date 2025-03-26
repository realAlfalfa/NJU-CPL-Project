cmake_minimum_required(VERSION 3.27)
project(Final C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-fcommon)

include_directories(include)
add_subdirectory(src)

target_link_libraries(Final PRIVATE
        mingw32
        SDL2main
        SDL2
        SDL2_image
        SDL2_mixer
        SDL2_ttf
)
