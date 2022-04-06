set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/extend1/app)

add_executable(encrypt_extend1 ${PROJECT_SOURCE_DIR}/extend1/src/encrypt.cpp)
add_executable(decrypt_extend1 ${PROJECT_SOURCE_DIR}/extend1/src/decrypt.cpp)
