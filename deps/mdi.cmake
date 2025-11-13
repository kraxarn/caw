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

set(FILENAME "${CMAKE_CURRENT_SOURCE_DIR}/include/caw/res/icons.h")
set(OUTPUT "#pragma once\n")

foreach (ICON ${MDI_ICONS})
	string(LENGTH "${ICON}" ICON_LENGTH)
	math(EXPR ICON_LENGTH "${ICON_LENGTH} - 4")
	string(SUBSTRING "${ICON}" 0 "${ICON_LENGTH}" ICON_NAME)
	string(REPLACE "-" "_" ICON_NAME "${ICON_NAME}")
	file(READ "${mdi_SOURCE_DIR}/svg/${ICON}" ICON_DATA)
	string(LENGTH "${ICON_DATA}" ICON_DATA_LENGTH)
	string(REPLACE "\"" "\\\"" ICON_DATA "${ICON_DATA}")
	string(APPEND OUTPUT "\n" "const char *${ICON_NAME} = \"${ICON_DATA}\";" "\n")
	string(APPEND OUTPUT "constexpr size_t ${ICON_NAME}_len = ${ICON_DATA_LENGTH};" "\n")
endforeach ()

file(WRITE "${FILENAME}" "${OUTPUT}")