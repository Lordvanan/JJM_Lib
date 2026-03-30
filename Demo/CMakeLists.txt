cmake_minimum_required(VERSION 3.23.3)
project(Demo VERSION 1.0 LANGUAGES CXX C)

add_subdirectory(../ JJM_Lib_build)

add_executable(Demo)
target_sources(Demo PRIVATE main.cpp utils.cpp)

target_link_libraries(Demo PUBLIC JJM_Lib)
target_compile_definitions(JJM_Lib PUBLIC USE_JJM_CONTEXT=1)