include(FetchContent)

FetchContent_Declare(mdi
	GIT_REPOSITORY https://github.com/Templarian/MaterialDesign-SVG.git
	GIT_TAG v7.4.47
)
message(STATUS "Downloading icons")
FetchContent_MakeAvailable(mdi)

set(MDI_DIR "${mdi_SOURCE_DIR}/svg")
set(MDI_ICONS
	"checkbox-blank-outline.svg"
	"checkbox-marked.svg"
)

set(OUTPUT "")
string(APPEND OUTPUT
	"#include \"caw/res/icons.h\"\n\n"
	"#include <SDL3/SDL_stdinc.h>\n\n"
	"const char *icon_data(const char *name, size_t *len)\n"
	"{\n"
)

foreach (ICON ${MDI_ICONS})
	string(LENGTH "${ICON}" ICON_LENGTH)
	math(EXPR ICON_LENGTH "${ICON_LENGTH} - 4")
	string(SUBSTRING "${ICON}" 0 "${ICON_LENGTH}" ICON_NAME)

	file(READ "${mdi_SOURCE_DIR}/svg/${ICON}" ICON_DATA)
	string(REPLACE "\"" "\\\"" ICON_DATA "${ICON_DATA}")
	string(LENGTH "${ICON_DATA}" ICON_DATA_LENGTH)

	string(APPEND OUTPUT
		"\t" "if (SDL_strcmp(name, \"${ICON_NAME}\") == 0)" "\n"
		"\t" "{" "\n"
		"\t\t" "*len = ${ICON_DATA_LENGTH};" "\n"
		"\t\t" "return \"${ICON_DATA}\";" "\n"
		"\t" "}" "\n\n"
	)
endforeach ()

string(APPEND OUTPUT
	"\t" "return nullptr;\n"
	"}\n"
)

set(FILENAME "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/bakedicons.c")
file(WRITE "${FILENAME}" "${OUTPUT}")