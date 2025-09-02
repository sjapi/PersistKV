add_executable(persist_kv_test
	persist_kv_test.cpp
)

target_link_libraries(persist_kv_test PRIVATE persist_kv)

add_test(NAME PersistKV COMMAND persist_kv_test)
