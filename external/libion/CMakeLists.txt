project(ION)

add_library(ion SHARED IMPORTED GLOBAL)
set_target_properties(ion
  PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/out/lib/libion.so
)
set_target_properties(ion
  PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/out/inc
)

add_custom_target(libion DEPENDS ion)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/out/lib/libion.so DESTINATION lib)
install(DIRECTORY out/inc/ DESTINATION include)
