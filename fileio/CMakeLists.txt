
add_executable(copy copy.c)
add_executable(seek_io seek_io.c)
add_executable(large_file large_file.c)
add_executable(atomic_append atomic_append.c)
add_executable(multi_descriptors multi_descriptors.c)
add_executable(t_readv t_readv.c)
add_executable(t_truncate t_truncate.c)

target_link_libraries(copy lib)
target_link_libraries(seek_io lib)
target_link_libraries(large_file lib)
target_link_libraries(atomic_append lib)
target_link_libraries(multi_descriptors lib)
target_link_libraries(t_readv lib)
target_link_libraries(t_truncate lib)

add_test(
  NAME
    test_io
  COMMAND
    $<TARGET_FILE:copy>
    $<TARGET_FILE:seek_io>
    $<TARGET_FILE:large_file>
    $<TARGET_FILE:atomic_append>
    $<TARGET_FILE:multi_descriptors>
    $<TARGET_FILE:t_readv>
    $<TARGET_FILE:t_truncate>
)
