#ifndef STANDARDSDL2_H
#define STANDARDSDL2_H

#if MSVC
    #include <GL/glew.h>

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_opengl.h>

	#include <windows.h>
#elif NX
    #include <SDL2/SDL.h>

    #include <GLES2/gl2.h>
    #include <SDL2/SDL_opengl.h>
    #include <GLES2/gl2ext.h>
#else
    #if USING_FRAMEWORK
        #include <SDL.h>
        #include <gl.h>
        #include <SDL_opengl.h>
        #include <glu.h>
    #else
        #include <SDL2/SDL.h>
        #include <GL/gl.h>
        #include <SDL2/SDL_opengl.h>
        #include <GL/glu.h>
    #endif
#endif

#undef min
#undef max

#include <zlib.h>

#if NX
    #include <switch.h>
#endif

#include <vorbis/vorbisfile.h>

typedef uint32_t uint;

#endif // STANDARDSDL2_H
