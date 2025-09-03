add_library(persist_kv STATIC
	PersistKV.cpp
	PersistKV.h
	Serializer.h
	utils.cpp
	utils.h
)

target_include_directories(persist_kv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
