cmake_minimum_required(VERSION 3.28)
project(Aurelia VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
option(AURELIA_BUILD_TESTS "Build unit tests" ON)
option(AURELIA_BUILD_EXAMPLES "Build examples" ON)
option(AURELIA_ENABLE_SANITIZERS "Enable address/UB sanitizers" OFF)
option(AURELIA_ENABLE_LLVM "Enable LLVM/MLIR backend" OFF)
option(AURELIA_ENABLE_CUDA "Enable CUDA backend" OFF)

# Compiler flags
add_compile_options(-Wall -Wextra -Wpedantic)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Werror)
endif()

if(AURELIA_ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

# Find dependencies
find_package(LLVM 17 QUIET)
find_package(MLIR 17 QUIET)

if(LLVM_FOUND AND MLIR_FOUND AND AURELIA_ENABLE_LLVM)
    message(STATUS "LLVM/MLIR found: ${LLVM_VERSION}")
    add_definitions(-DAURELIA_HAS_LLVM)
    
    include_directories(${LLVM_INCLUDE_DIRS})
    include_directories(${MLIR_INCLUDE_DIRS})
    link_directories(${LLVM_LIBRARY_DIRS})
else()
    message(WARNING "LLVM/MLIR not found or disabled. Building frontend only.")
endif()

if(AURELIA_ENABLE_CUDA)
    find_package(CUDAToolkit 12.0 QUIET)
    if(CUDAToolkit_FOUND)
        message(STATUS "CUDA found: ${CUDAToolkit_VERSION}")
        add_definitions(-DAURELIA_HAS_CUDA)
    endif()
endif()

# Aurelia Runtime Library
add_library(aurelia_runtime STATIC
    src/runtime/tensor.cpp
    src/runtime/memory_pool.cpp
    src/runtime/stream.cpp
    src/runtime/error.cpp
)

target_include_directories(aurelia_runtime PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Aurelia Compiler Frontend
add_library(aurelia_frontend STATIC
    src/lexer/token.cpp
    src/lexer/lexer.cpp
    src/parser/ast.cpp
    src/parser/parser.cpp
    src/typechecker/types.cpp
    src/typechecker/type_checker.cpp
    src/typechecker/shape_solver.cpp
)

target_link_libraries(aurelia_frontend PRIVATE aurelia_runtime)
target_include_directories(aurelia_frontend PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Main compiler executable
add_executable(aulc
    src/main.cpp
)

target_link_libraries(aulc PRIVATE aurelia_frontend aurelia_runtime)

if(LLVM_FOUND AND AURELIA_ENABLE_LLVM)
    target_link_libraries(aulc PRIVATE 
        LLVMSupport
        LLVMCore
        MLIRIR
        MLIRParser
    )
endif()

# REPL (Interactive interpreter)
add_executable(aurelia_repl
    tools/repl.cpp
)

target_link_libraries(aurelia_repl PRIVATE aurelia_frontend aurelia_runtime)

# Examples
if(AURELIA_BUILD_EXAMPLES)
    add_executable(example_hello examples/hello.cpp)
    target_link_libraries(example_hello PRIVATE aurelia_runtime)
    
    add_executable(example_tensor examples/tensor_ops.cpp)
    target_link_libraries(example_tensor PRIVATE aurelia_runtime)
endif()

# Tests
if(AURELIA_BUILD_TESTS)
    enable_testing()
    
    add_executable(test_lexer tests/unit/test_lexer.cpp)
    target_link_libraries(test_lexer PRIVATE aurelia_frontend)
    add_test(NAME lexer_tests COMMAND test_lexer)
    
    add_executable(test_parser tests/unit/test_parser.cpp)
    target_link_libraries(test_parser PRIVATE aurelia_frontend)
    add_test(NAME parser_tests COMMAND test_parser)
    
    add_executable(test_typechecker tests/unit/test_typechecker.cpp)
    target_link_libraries(test_typechecker PRIVATE aurelia_frontend)
    add_test(NAME typechecker_tests COMMAND test_typechecker)
    
    add_executable(test_tensor tests/unit/test_tensor.cpp)
    target_link_libraries(test_tensor PRIVATE aurelia_runtime)
    add_test(NAME tensor_tests COMMAND test_tensor)
endif()

# Installation
install(TARGETS aulc aurelia_runtime aurelia_frontend
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/aurelia
    DESTINATION include
)

# Print configuration summary
message(STATUS "")
message(STATUS "Aurelia Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Tests: ${AURELIA_BUILD_TESTS}")
message(STATUS "  Build Examples: ${AURELIA_BUILD_EXAMPLES}")
message(STATUS "  Sanitizers: ${AURELIA_ENABLE_SANITIZERS}")
message(STATUS "  LLVM Backend: ${AURELIA_ENABLE_LLVM}")
message(STATUS "  CUDA Backend: ${AURELIA_ENABLE_CUDA}")
message(STATUS "")
