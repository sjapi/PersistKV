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

# WAL tests
add_executable(wal_test
	wal_test.cpp
)

target_link_libraries(wal_test PRIVATE persist_kv)

add_test(NAME WAL COMMAND wal_test)
