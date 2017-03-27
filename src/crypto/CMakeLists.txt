project(crypto-static C CXX)

set(CRYPTO_SOURCES
    des.cpp
    des3.cpp
    sha256.cpp
    md5.cpp
   )

add_library(${PROJECT_NAME} STATIC 
            ${CRYPTO_SOURCES}
           )