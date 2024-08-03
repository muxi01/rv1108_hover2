project(io)

set(IO_SRC_FILES
    io.c
)

add_executable(io ${IO_SRC_FILES})

install(TARGETS io DESTINATION sbin)
