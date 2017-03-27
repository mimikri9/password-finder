#project(passFndTests)

find_package(Threads)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)

include(ExternalProject)

ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")


add_executable(${PROJECT_NAME}
    keyGen.cpp
    inputDataHandler.cpp
    supportFunc.cpp
    worker.cpp
    crypto.cpp
    )

target_link_libraries(${PROJECT_NAME}
    libgtest
    libgmock
    crypto-static
    ${CMAKE_THREAD_LIBS_INIT}
    )

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME} --gtest_output=xml:${CMAKE_BINARY_DIR}/reports/
    )


