cmake_minimum_required(VERSION 3.26)

project(argus-retina VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(argus_retina_engine STATIC
    src/retina_engine.cpp
)

target_include_directories(argus_retina_engine
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(argus_retina_engine PUBLIC cxx_std_23)

if(MSVC)
    target_compile_options(argus_retina_engine PRIVATE /W4 /permissive-)
else()
    target_compile_options(argus_retina_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(BUILD_TESTING)
    add_executable(argus_retina_contract_test
        tests/retina_contract_test.cpp
    )

    target_link_libraries(argus_retina_contract_test
        PRIVATE
            argus_retina_engine
    )

    target_compile_features(argus_retina_contract_test PRIVATE cxx_std_23)

    if(MSVC)
        target_compile_options(argus_retina_contract_test PRIVATE /W4 /permissive-)
    else()
        target_compile_options(argus_retina_contract_test PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    add_test(NAME argus_retina_contract_test COMMAND argus_retina_contract_test)
endif()
