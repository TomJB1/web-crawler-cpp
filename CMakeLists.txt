cmake_minimum_required(VERSION 3.10)
project(Crawler)
add_executable(Crawler crawler.cpp)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG da40186618909b1a7363d4e4495aa899c6e0eb75) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)
target_link_libraries(Crawler PRIVATE cpr::cpr)