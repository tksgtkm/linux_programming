add_library(daemons
  STATIC
    become_daemon.h
    become_daemon.c
)

# add_executable(error_functions error_functions.c)
#
# add_executable(get_num get_num.c)

# target_link_libraries(error_functions lib)
# target_link_libraries(get_num lib)

target_sources(daemons
  PRIVATE
    become_daemon.c
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/become_daemon.h
)

target_include_directories(daemons
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(daemons lib)
