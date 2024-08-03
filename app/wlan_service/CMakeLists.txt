project(WLAN_SERVICE)

set(WLAN_SERVICE_SRC_FILES
  main.cc
  src/wlan_service.cc
  src/console.cc
)

add_subdirectory(test)

add_executable(wlan_service ${WLAN_SERVICE_SRC_FILES})

target_link_libraries(wlan_service rkipc)

target_include_directories(wlan_service
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

install(TARGETS wlan_service DESTINATION bin)