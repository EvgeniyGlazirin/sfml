add_executable(ws2.1 main.cpp)

target_include_directories(ws2.1 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(ws2.1 PUBLIC cxx_std_17)
target_compile_definitions(ws2.1 PRIVATE SFML_STATIC)

target_link_libraries(ws2.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})