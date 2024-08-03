project(WLAN_SERVICE)

set(RK_IPC_SRC_FILES
  src/socket_client.cc
  src/socket_server.cc
)

add_library(rkipc ${RK_IPC_SRC_FILES})

target_include_directories(rkipc
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(TARGETS rkipc DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/librkipc)
