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

# TODO: This is way more complicated than it's worth xd
# (Let's just call it temporary until nest is done)

set(OUTPUT_VAR "#include <SDL3/SDL_stdinc.h>\n")
set(OUTPUT_FUN "const void *icon_data(const char *name, int *size)")
string(APPEND OUTPUT_FUN "\n" "{" "\n")

foreach (ICON ${MDI_ICONS})
	string(LENGTH "${ICON}" ICON_LENGTH)
	math(EXPR ICON_LENGTH "${ICON_LENGTH} - 4")
	string(SUBSTRING "${ICON}" 0 "${ICON_LENGTH}" ICON_NAME)
	string(REPLACE "-" "_" ICON_VAR "${ICON_NAME}")
	string(TOUPPER "${ICON_VAR}" ICON_DEFINE)
	string(APPEND ICON_DEFINE "_QOI")

	set(SOURCE "${MDI_DIR}/${ICON_NAME}.svg")
	set(TARGET "${MDI_DIR}/${ICON_NAME}.qoi")
	execute_process(COMMAND
		magick
		-background transparent
		"${SOURCE}"
		-fill "#fbf5ef" -colorize 100
		"${TARGET}"
	)

	target_compile_definitions(${PROJECT_NAME} PRIVATE
		${ICON_DEFINE}="${TARGET}"
	)

	string(APPEND OUTPUT_VAR
		"\n" "constexpr Uint8 ${ICON_VAR}[] = {\n"
		"#embed ${ICON_DEFINE}\n"
		"};" "\n"
	)

	string(APPEND OUTPUT_FUN
		"\t" "if (SDL_strcmp(name, \"${ICON_NAME}\") == 0)" "\n"
		"\t" "{" "\n"
		"\t\t" "*size = sizeof(${ICON_VAR});" "\n"
		"\t\t" "return (void*) ${ICON_VAR};" "\n"
		"\t" "}" "\n\n"
	)
endforeach ()

string(APPEND OUTPUT_FUN
	"\t" "return nullptr;\n"
	"}\n"
)

set(FILENAME "${CMAKE_CURRENT_SOURCE_DIR}/src/res/bakedicons.c")
file(WRITE "${FILENAME}" "${OUTPUT_VAR}" "\n" "${OUTPUT_FUN}")