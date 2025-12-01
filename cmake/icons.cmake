
# TODO: This is way more complicated than it's worth xd
# (Let's just call it temporary until nest is done)

set(OUTPUT_VAR "#include <SDL3/SDL_stdinc.h>\n")
set(OUTPUT_FUN "const void *icon_data(const char *name, int *size)")
string(APPEND OUTPUT_FUN "\n" "{" "\n")

file(GLOB ICON_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/res/icons/*.qoi")

foreach (ICON_PATH ${ICON_PATHS})
	get_filename_component(ICON_NAME "${ICON_PATH}" NAME_WE)
	string(REPLACE "-" "_" ICON_VAR "${ICON_NAME}")
	string(TOUPPER "${ICON_VAR}" ICON_DEFINE)
	string(APPEND ICON_DEFINE "_QOI")

	target_compile_definitions(${PROJECT_NAME} PRIVATE
		${ICON_DEFINE}="${ICON_PATH}"
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