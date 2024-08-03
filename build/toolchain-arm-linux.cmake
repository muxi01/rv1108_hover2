# this one is important
SET(CMAKE_SYSTEM_NAME Generic)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   $ENV{CVR_SDK_ROOT}/prebuilts/toolschain/usr/bin/arm-linux-gcc)
SET(CMAKE_CXX_COMPILER $ENV{CVR_SDK_ROOT}/prebuilts/toolschain/usr/bin/arm-linux-g++)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH  $ENV{CVR_SDK_ROOT}/prebuilts/toolschain/usr $ENV{CVR_SDK_ROOT}/out/system)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)