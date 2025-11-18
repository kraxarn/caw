#include "shiny/internal/element.h"

#include "clay.h"

#include <SDL3/SDL_stdinc.h>

void shiny_element_open(const char *element_id)
{
	const Clay_String str = {
		.isStaticallyAllocated = true,
		.length = SDL_strlen(element_id),
		.chars = element_id
	};
	Clay__OpenElementWithId(CLAY_SID(str));
}

void shiny_element_configure(const Clay_ElementDeclaration *declaration)
{
	Clay__ConfigureOpenElementPtr(declaration);
}

void shiny_element_close()
{
	Clay__CloseElement();
}
