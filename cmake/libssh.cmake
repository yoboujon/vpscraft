cmake_minimum_required(VERSION 3.11)
include(FetchContent)

set(WITH_ZLIB OFF CACHE BOOL "Build with ZLIB support")
set(WITH_PCAP OFF CACHE BOOL "Compile with Pcap generation support")
set(WITH_EXAMPLES OFF CACHE BOOL "Build examples")
set(WITH_NACL OFF CACHE BOOL "Build with libnacl (curve25519)")
FetchContent_Declare(
  libssh
  GIT_REPOSITORY https://git.libssh.org/projects/libssh.git
  GIT_TAG        libssh-0.11.3
)
FetchContent_GetProperties(libssh)
if (NOT libssh_POPULATED)
  set(FETCHCONTENT_QUIET NO)
  FetchContent_MakeAvailable(libssh)
endif()
set(LIBSSH_INCLUDE_DIRS "${libssh_SOURCE_DIR}/include")
