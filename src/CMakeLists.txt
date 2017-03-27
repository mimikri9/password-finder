project(passwordFinder C CXX)

find_package(Threads)
add_subdirectory(crypto)

set(SOURCES
    ${PROJECT_NAME}.cpp
    inputDataHandler.cpp
    keyGen.cpp
    supportFunc.cpp
    worker.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries (${PROJECT_NAME} 
                       crypto-static
                       ${CMAKE_THREAD_LIBS_INIT}
                       )


