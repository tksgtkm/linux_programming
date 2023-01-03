
add_library(lib
  SHARED
    error_functions.h
    get_num.h
    api_hdr.h
    error_functions.c
    get_num.c)

# add_executable(error_functions error_functions.c)
#
# add_executable(get_num get_num.c)

# target_link_libraries(error_functions lib)
# target_link_libraries(get_num lib)

target_sources(lib
  PRIVATE
    error_functions.c
    get_num.c
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/error_functions.h
    ${CMAKE_CURRENT_LIST_DIR}/get_num.h
    ${CMAKE_CURRENT_LIST_DIR}/api_hdr.h
)

target_include_directories(lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(lib)
