include_directories(${CPosix_SOURCE_DIR}/lib/include)

# Tables

add_library(tables_lib SHARED
    table/hash_table.c
)
set_target_properties(tables_lib PROPERTIES LINKER_LANGUAGE C)

# LinkedLists

add_library(linked_list_lib SHARED
    linked_lists/doubly_linked.c
    linked_lists/queue.c
    linked_lists/stack.c
)
set_target_properties(linked_list_lib PROPERTIES LINKER_LANGUAGE C)

# Server

add_library(web_server_lib SHARED
    networking/web_server/content.c
    networking/web_server/handle.c
    networking/web_server/manager.c
    networking/web_server/responses.c
    networking/web_server/socket.c
)
set_target_properties(web_server_lib PROPERTIES LINKER_LANGUAGE C)

# Searching

add_library(search_lib SHARED
    searching/binary_search.c
)
set_target_properties(search_lib PROPERTIES LINKER_LANGUAGE C)

# Sorting

add_library(sorting_lib SHARED
    sorting/bubble_sort.c
    sorting/quick_sort.c
)
set_target_properties(sorting_lib PROPERTIES LINKER_LANGUAGE C)
