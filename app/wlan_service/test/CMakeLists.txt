project(WLAN_SERVICE_TEST)

set(WLAN_SERVICE_TEST_SRC_FILES
  wlan_service_test.cc
)

add_executable(wlan_service_test ${WLAN_SERVICE_TEST_SRC_FILES})

target_link_libraries(wlan_service_test rkipc)

install(TARGETS wlan_service_test DESTINATION bin)