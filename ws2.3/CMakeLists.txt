add_executable(ws2.3 main.cpp)

target_include_directories(ws2.3 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(ws2.3 PUBLIC cxx_std_17)
target_compile_definitions(ws2.3 PRIVATE SFML_STATIC)

target_link_libraries(ws2.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})