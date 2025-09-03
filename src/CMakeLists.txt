add_library(persist_kv STATIC
	PersistKV.cpp
	PersistKV.h
)

target_include_directories(persist_kv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
