aux_source_directory(. SRC_LIST)
add_library(smtp_server SHARED ${SRC_LIST})
target_link_libraries(smtp_server server base64)