set(MAPLE_FONT_VERSION "v7.8")
set(MAPLE_FONT_HASH "9f51399c8f59fc6ae9dded1d4cad53b2430d5915ef66cbac54cde05b4ab3edf0")

FetchContent_Declare(maple_font
	URL "https://github.com/subframe7536/maple-font/releases/download/${MAPLE_FONT_VERSION}/MapleMonoNL-TTF.zip"
	URL_HASH "SHA256=${MAPLE_FONT_HASH}"
	DOWNLOAD_EXTRACT_TIMESTAMP true
)

message(STATUS "Downloading fonts")
FetchContent_MakeAvailable(maple_font)

execute_process(COMMAND
	xxd --include
	--name "maple_mono_nl_regular_ttf"
	"${maple_font_SOURCE_DIR}/MapleMonoNL-Regular.ttf"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/caw/res/maplemononlregular.h"
	RESULT_VARIABLE xxd_result
)