
add_executable(mem_segments mem_segments.c)
add_executable(necho necho.c)
add_executable(display_env display_env.c)
add_executable(modify_env modify_env.c)
add_executable(longjmp longjmp.c)

target_link_libraries(mem_segments lib)
target_link_libraries(necho lib)
target_link_libraries(display_env lib)
target_link_libraries(modify_env lib)
target_link_libraries(longjmp lib)

add_test(
  NAME
    test_io
  COMMAND
    $<TARGET_FILE:mem_segments>
    $<TARGET_FILE:necho>
    $<TARGET_FILE:display_env>
    $<TARGET_FILE:modify_env>
    $<TARGET_FILE:longjmp>
)
