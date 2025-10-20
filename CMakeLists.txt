ORPHAN BLOCK Bitcoin: CMake Build System Configuration
File: CMakeLists.txt

This file defines the build process for the ORPHd node software, including all
source files, header paths, and required C++ standards.
cmake_minimum_required(VERSION 3.10)
project(ORPHAN_BLOCK_Bitcoin CXX)
Enforce modern C++ standard for development
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
--- Define Source Files (All Implementation .cpp files) ---
NOTE: Header files (.h) are included implicitly by the compiler.
set(ORPH_SOURCES
src/main.cpp
# Core Structures
src/block.cpp
src/transaction.cpp

# Consensus and Economics
src/consensus/ghostdag.cpp
src/consensus/rewards.cpp

# Networking
src/net/p2p_message.cpp
src/net/network_service.cpp

# Cryptography
src/crypto/sha256.cpp

)
--- Create the Executable Target ---
Creates the final executable file named 'ORPHd'
add_executable(ORPHd ${ORPH_SOURCES})
--- Define Header Search Paths ---
Tells the compiler where to look for .h files (like block.h or ghostdag.h)
target_include_directories(ORPHd PRIVATE
src/
src/consensus
src/net
src/crypto
)
--- Required External Libraries (Placeholders for Phase 2) ---
When linking external libraries, you will uncomment and use these placeholders.
target_link_libraries(ORPHd PRIVATE
# Placeholder: Linking RocksDB for the database layer
RocksDB::RocksDB
# Placeholder: Linking Boost::ASIO or similar for socket handling
Boost::asio
)
