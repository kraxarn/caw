set(MAPLE_FONT_VERSION "v7.8")
set(MAPLE_FONT_HASH "9f51399c8f59fc6ae9dded1d4cad53b2430d5915ef66cbac54cde05b4ab3edf0")

if (CMAKE_VERSION VERSION_LESS "3.24.0")
	FetchContent_Declare(maple_font
		URL "https://github.com/subframe7536/maple-font/releases/download/${MAPLE_FONT_VERSION}/MapleMonoNL-TTF.zip"
	)
else ()
	FetchContent_Declare(maple_font
		URL "https://github.com/subframe7536/maple-font/releases/download/${MAPLE_FONT_VERSION}/MapleMonoNL-TTF.zip"
		URL_HASH "SHA256=${MAPLE_FONT_HASH}"
		DOWNLOAD_EXTRACT_TIMESTAMP true
	)
endif ()

message(STATUS "Downloading fonts")
FetchContent_MakeAvailable(maple_font)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	MAPLE_MONO_NL_REGULAR_TTF="${maple_font_SOURCE_DIR}/MapleMonoNL-Regular.ttf"
)