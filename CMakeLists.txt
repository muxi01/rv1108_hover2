project(RK1108_CVR)
cmake_minimum_required(VERSION 2.8.12)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

add_subdirectory(app/wlan_service)
add_subdirectory(external/librkipc)
add_subdirectory(external/libion)
add_subdirectory(external/io)
