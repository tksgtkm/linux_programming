add_library(sockets
INTERFACE
)

target_sources(
  sockets INTERFACE
  us_xfr.h
  ud_ucase.h
  read_line.h
  read_line.c
  i6d_ucase.h
  is_seqnum.h
  inet_sockets.h
  inet_sockets.c
  id_echo.h
)

add_executable(us_xfr_sv us_xfr_sv.c)
add_executable(us_xfr_cl us_xfr_cl.c)
add_executable(ud_ucase_sv ud_ucase_sv.c)
add_executable(ud_ucase_cl ud_ucase_cl.c)
add_executable(i6d_ucase_sv i6d_ucase_sv.c)
add_executable(i6d_ucase_cl i6d_ucase_cl.c)
add_executable(is_seqnum_sv is_seqnum_sv.c)
add_executable(is_seqnum_cl is_seqnum_cl.c)
add_executable(t_gethostbyname t_gethostbyname.c)
add_executable(id_echo_sv id_echo_sv.c)
add_executable(id_echo_cl id_echo_cl.c)

set(LIBS lib daemons sockets)

target_link_libraries(us_xfr_sv ${LIBS})
target_link_libraries(us_xfr_cl ${LIBS})
target_link_libraries(ud_ucase_sv ${LIBS})
target_link_libraries(ud_ucase_cl ${LIBS})
target_link_libraries(i6d_ucase_sv ${LIBS})
target_link_libraries(i6d_ucase_cl ${LIBS})
target_link_libraries(is_seqnum_sv ${LIBS})
target_link_libraries(is_seqnum_cl ${LIBS})
target_link_libraries(t_gethostbyname ${LIBS})
target_link_libraries(id_echo_sv ${LIBS})
target_link_libraries(id_echo_cl ${LIBS})

add_test(
  NAME
    test_io
  COMMAND
    $<TARGET_FILE:us_xfr_sv>
    $<TARGET_FILE:us_xfr_cl>
    $<TARGET_FILE:ud_ucase_sv>
    $<TARGET_FILE:ud_ucase_cl>
    $<TARGET_FILE:i6d_ucase_sv>
    $<TARGET_FILE:i6d_ucase_cl>
    $<TARGET_FILE:is_seqnum_sv>
    $<TARGET_FILE:is_seqnum_cl>
    $<TARGET_FILE:t_gethostbyname>
    $<TARGET_FILE:id_echo_sv>
    $<TARGET_FILE:id_echo_cl>
)
