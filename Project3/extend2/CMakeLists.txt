set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/extend2/app)

add_executable(encrypt_extend2 ${PROJECT_SOURCE_DIR}/extend2/src/encrypt.cpp)
add_executable(decrypt_extend2 ${PROJECT_SOURCE_DIR}/extend2/src/decrypt.cpp)
