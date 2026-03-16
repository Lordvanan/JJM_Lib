cmake_minimum_required(VERSION 3.0.0)

add_library(JJM_Lib)

target_sources(JJM_Lib
	PRIVATE
		JJM_App.cpp
		JJM_Time.cpp
		JJM_Main.cpp
		JJM_Files.cpp

	PUBLIC
		FILE_SET myHeaders
		TYPE HEADERS
		BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
		FILES
			JJM_App.h
			JJM_Time.h
			JJM_Files.h
			JJM_List.h
)

target_include_directories(JJM_Lib
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)