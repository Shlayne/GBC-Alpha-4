#include <stdlib.h>
#include <string.h>

#define STBI_MALLOC(sz)                     static_cast<void*>(::operator new(sz))
#define STBI_REALLOC(p, newsz)              static_assert(false)
#define STBI_FREE(p)                        ::operator delete(p)

auto stbi_realloc_sized_impl(void* p, size_t oldSize, size_t newSize) -> void*
{
	if (!p)
		p = STBI_MALLOC(newSize);
	else if (oldSize < newSize)
	{
		void* newp{STBI_MALLOC(newSize)};
		memcpy(newp, p, oldSize);
		STBI_FREE(p);
		p = newp;
	}
	return p;
}
#define STBI_REALLOC_SIZED(p, oldsz, newsz) stbi_realloc_sized_impl((p), (oldsz), (newsz))

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
