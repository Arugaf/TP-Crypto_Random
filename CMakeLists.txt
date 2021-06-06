cmake_minimum_required(VERSION 3.20)
project(TP_Crypto_Random)

set(CMAKE_CXX_STANDARD 17)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

add_executable(TP_Crypto_Random main.cpp)

target_link_libraries(TP_Crypto_Random OpenSSL::Crypto)