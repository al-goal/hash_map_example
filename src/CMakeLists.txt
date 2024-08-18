add_library(
    hash_map_parse
    process_inputs.cpp
    word_extractor.cpp
)

add_executable(
  hash_map_example
  main.cpp
)

target_link_libraries(
    hash_map_parse
    curl
)

target_link_libraries(
    hash_map_example
    hash_map_parse
)
