project(DPP_TEST)

set(DPP_TEST_SRC_FILES
  dsp_test.cc
)

add_executable(dpp_test ${DPP_TEST_SRC_FILES})

target_include_directories(dpp_test
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(dpp_test ion)

install(TARGETS dpp_test DESTINATION bin)