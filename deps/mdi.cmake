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

foreach (ICON IN LISTS MDI_ICONS)
	string(LENGTH "${ICON}" ICON_LENGTH)
	math(EXPR ICON_LENGTH "${ICON_LENGTH} - 4")
	string(SUBSTRING "${ICON}" 0 "${ICON_LENGTH}" ICON_DEFINE)
	string(REPLACE "-" "_" ICON_DEFINE "${ICON_DEFINE}")
	string(TOUPPER "${ICON_DEFINE}" ICON_DEFINE)
	target_compile_definitions(${PROJECT_NAME} PRIVATE
		"IC_${ICON_DEFINE}=\"${mdi_SOURCE_DIR}/svg/${ICON}\""
	)
endforeach ()