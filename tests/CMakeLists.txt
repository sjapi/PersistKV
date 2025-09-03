# PersistKV tests
add_executable(persist_kv_test
	persist_kv_test.cpp
)

target_link_libraries(persist_kv_test PRIVATE persist_kv)

add_test(NAME PersistKV COMMAND persist_kv_test)

# PersistKVSerializer tests
add_executable(serializer_test
	serializer_test.cpp
)

target_link_libraries(serializer_test PRIVATE persist_kv)

add_test(NAME Serializer COMMAND serializer_test)
