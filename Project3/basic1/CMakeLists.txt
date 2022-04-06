set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/basic1/app)

add_executable(encrypt_basic1 ${PROJECT_SOURCE_DIR}/basic1/src/encrypt.cpp)
add_executable(decrypt_basic1 ${PROJECT_SOURCE_DIR}/basic1/src/decrypt.cpp)
