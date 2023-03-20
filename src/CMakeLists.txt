add_subdirectory(fifteen_lib)

add_executable(fifteen main.cpp)

target_include_directories(fifteen PUBLIC fifteen_lib)

target_link_libraries(fifteen PRIVATE fifteen_lib)
