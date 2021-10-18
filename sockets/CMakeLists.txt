add_library(sockets
INTERFACE
)

target_sources(
  sockets INTERFACE us_xfr.h
)

add_executable(us_xfr_sv us_xfr_sv.c)
add_executable(us_xfr_cl us_xfr_cl.c)

set(LIBS lib sockets)

target_link_libraries(us_xfr_sv ${LIBS})
target_link_libraries(us_xfr_cl ${LIBS})

add_test(
  NAME
    test_io
  COMMAND
    $<TARGET_FILE:us_xfr_sv>
    $<TARGET_FILE:us_xfr_cl>
)
