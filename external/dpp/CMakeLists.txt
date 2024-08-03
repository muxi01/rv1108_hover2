project(DPP)

add_library(dpp SHARED IMPORTED GLOBAL)
set_target_properties(dpp
  PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/out/lib/libdpp.so
)
set_target_properties(dpp
  PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/out/inc
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/out/lib/libdpp.so DESTINATION lib)

add_subdirectory(test)