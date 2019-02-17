#if INTERFACE
#include <Engine/IGraphics.h>

class IGLGraphics : public IGraphics {
public:
    SDL_GLContext Context;

    GLint LocUseTexture;
    GLint LocPosition;
    GLint LocTexCoord;
    GLint LocNormals;
    GLint LocColor;

    GLint LocTexture;
    GLint LocPalette;
    GLint LocPaletteAlt;

    GLint LocTranslate;
    GLint LocRotate;
    GLint LocScale;

    GLint LocWaterLine;

    GLint LocFilterPR;
    GLint LocFilterBW;
    GLint LocFilterFade;

    GLint LocFade;
    GLint LocFadeToWhite;

    GLuint programID;

    GLuint rectBufferID;

    ISprite* TextSprite;
    ISprite* LastSprite = NULL;

    float ColorBlendR = 1.0f;
    float ColorBlendG = 1.0f;
    float ColorBlendB = 1.0f;

    GLint defaultFBO;
    GLuint renderedTexture;
    GLuint renderedTextureQuality;
    GLuint framebufferScreen;
    GLuint framebufferScreenQuality;

    int RetinaMult = 1; ///
};
#endif

#include <Engine/IGLGraphics.h>

struct VertexData {
    GLfloat X;
    GLfloat Y;
    GLfloat Z;
    GLfloat U;
    GLfloat V;
    GLfloat R;
    GLfloat G;
    GLfloat B;
    GLfloat A;
};

#if ANDROID
#define GL_BGRA GL_RGBA
#endif

int                         Quality = 1;
uint32_t*                   ColorFlipArray = NULL;
int*                        backupframebuffers = NULL;
int                         backupframebuffercount = 0;
int                         backupframebufferindex = 0;

vector<ISprite*>            MakeTextureList;
vector<ISprite*>            MakeFrameBufferSpList;
vector<void*>               MakeFrameBufferIDList;
vector<vector<VertexData>>  MakeFrameBufferRawList;
vector<int*>                MakeFrameBufferRaPtrList;

vector<VertexData>          RawVertArray;

PUBLIC IGLGraphics::IGLGraphics(IApp* app) {
    App = app;

    Deform = (int8_t*)calloc(App->HEIGHT, 1);

    Clip[0] = -1;

    for (int i = 0; i < 0x100; i++)
        DivTable[i] = i / 3;


    backupframebuffers = (int*)calloc(0x200, sizeof(int*));
    backupframebuffercount = 0;
    backupframebufferindex = 0;
}

PUBLIC void IGLGraphics::Init() {

}

PUBLIC void IGLGraphics::SetDisplay(int DesiredWidth, int DesiredHeight, int IsSharp) {
    if (IsSharp)
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    else
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    ColorFlipArray = (uint32_t*)calloc(256, 4);

    int ww, wh;
    if (!Window) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

        Window = SDL_CreateWindow("Sonic 3'Mixed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            DesiredWidth, DesiredHeight,
            SDL_WINDOW_SHOWN
            #if ANDROID | IOS
            | SDL_WINDOW_BORDERLESS
            | SDL_WINDOW_FULLSCREEN
            #endif
            | SDL_WINDOW_ALLOW_HIGHDPI
            | SDL_WINDOW_OPENGL);
        if (!Window) {
            IApp::Print(2, "Could not create window!: %s", SDL_GetError());
            assert(Window);
        }
		
        const char* pxFmt = "UNKNOWN";
        switch (SDL_PIXELORDER(SDL_GetWindowPixelFormat(Window))) {
            case SDL_ARRAYORDER_NONE:
                pxFmt = "SDL_ARRAYORDER_NONE"; break;
            case SDL_ARRAYORDER_RGB:
                pxFmt = "SDL_ARRAYORDER_RGB"; break;
            case SDL_ARRAYORDER_RGBA:
                pxFmt = "SDL_ARRAYORDER_RGBA"; break;
            case SDL_ARRAYORDER_ARGB:
                pxFmt = "SDL_ARRAYORDER_ARGB"; break;
            case SDL_ARRAYORDER_BGR:
                pxFmt = "SDL_ARRAYORDER_BGR"; break;
            case SDL_ARRAYORDER_BGRA:
                pxFmt = "SDL_ARRAYORDER_BGRA"; break;
            case SDL_ARRAYORDER_ABGR:
                pxFmt = "SDL_ARRAYORDER_ABGR"; break;
        }
        IApp::Print(3, "PixelFormat: %s", pxFmt);

        Context = SDL_GL_CreateContext(Window);
        // Set VSYNC
        if (SDL_GL_SetSwapInterval(1) < 0) {

        }

        int w, h;
        SDL_GL_GetDrawableSize(Window, &w, &h);
        SDL_GetWindowSize(Window, &ww, &wh);
        if (h > wh)
            RetinaMult = 2;

        if (IApp::Platform == Platforms::Android)
            App->WIDTH = App->HEIGHT * w / h;

        IApp::Print(0, "Retina Mult: %f", (double)h / wh);
        IApp::Print(0, "RetinaMult: %d", RetinaMult);
        IApp::Print(0, "Render Size: %d x %d", w, h);
        IApp::Print(0, "Window Size: %d x %d", ww, wh);

        if (IApp::Platform == Platforms::iOS)
            Quality = 4;
        else if (IApp::Platform == Platforms::Android)
            Quality = 3;

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);

        IApp::Print(3, "Default FBO: %d", defaultFBO);
        int r, g, b, a;
        SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &r);
        SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &g);
        SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &b);
        SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &a);

        IApp::Print(1, "Red size: %d, Green size: %d, Blue size: %d, Alpha size: %d", r, g, b, a);




        int max;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
        IApp::Print(-1, "Max Texture Size: %d", max);



        if (Quality > 1)
            glGenTextures(2, &renderedTexture);
        else
            glGenTextures(1, &renderedTexture);
        glBindTexture(GL_TEXTURE_2D, renderedTexture);
		if (IsSharp || Quality > 1) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, App->WIDTH, App->HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        if (Quality > 1) {
            glBindTexture(GL_TEXTURE_2D, renderedTexture + 1);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, App->WIDTH * Quality, App->HEIGHT * Quality, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        CheckGLError(__LINE__);


		int iiii = 0;

        if (Quality > 1)
            glGenFramebuffers(2, &framebufferScreen);
        else
            glGenFramebuffers(1, &framebufferScreen);

        for (; iiii < Quality && iiii < 2; iiii++) {
            glBindFramebuffer(GL_FRAMEBUFFER, framebufferScreen + iiii); CheckGLError(__LINE__);

            #if MSVC
                glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture + iiii, 0);
            #elif MACOSX
                glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture + iiii, 0);
            #else
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture + iiii, 0);
            #endif

            GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER); CheckGLError(__LINE__);
            switch (e) {
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                    IApp::Print(2, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                    IApp::Print(2, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
                    break;
                case GL_FRAMEBUFFER_UNSUPPORTED:
                    IApp::Print(2, "GL_FRAMEBUFFER_UNSUPPORTED");
                    break;
                case GL_FRAMEBUFFER_COMPLETE:
                    IApp::Print(0, "GL_FRAMEBUFFER_COMPLETE");
                    break;
                default:
                    break;
            }
        }


        if (IApp::Platform != Platforms::iOS && IApp::Platform != Platforms::Android) {
            // GLuint renderBuffer;
            // glGenRenderbuffers(1, &renderBuffer);
            // glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
            // glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, App->WIDTH, App->HEIGHT);
            // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer);
            // CheckGLError(__LINE__);
        }


        // GLuint depthRenderBuffer;
        // glGenRenderbuffers(1, &depthRenderBuffer);
        // glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
        // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, App->WIDTH, App->HEIGHT);
        // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);

        glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
        CheckGLError(__LINE__);





        glViewport(0.0, 0.0, App->WIDTH, App->HEIGHT);
        CheckGLError(__LINE__);

        glClearColor(0.f, 0.f, 0.f, 1.f);

        char strangeLine1[50];
        char strangeLine2[50];
        sprintf(strangeLine1, "        vec4(2.0 / %d.0,  0.0, 0.0, 0.0),", App->WIDTH);
        sprintf(strangeLine2, "        vec4(0.0, -2.0 / %d.0, 0.0, 0.0),", App->HEIGHT);

        const GLchar* vertexShaderSource[] = {
            #if NX | IOS
            "precision mediump float;",
            #endif
            #if !NX | NX
            "attribute vec3    i_position;",
            "attribute vec2    i_uv;",
            "attribute vec3    i_normals;",
            // "attribute vec4    i_color;",
            "varying vec3      o_position;",
            "varying vec2      o_uv;",
            "varying vec3      o_normals;",
            // "varying vec4      o_color;",
            #else
            "in vec3           i_position;",
            "in vec2           i_uv;",
            "in vec3           i_normals;",
            // "in vec4           i_color;",
            "out vec3          o_position;",
            "out vec2          o_uv;",
            "out vec3          o_normals;",
            // "out vec4          o_color;",
            #endif

            "uniform vec3      u_translate;",
            "uniform vec3      u_rotate;",
            "uniform vec3      u_scale;",

            "uniform float     u_screenWidth;",
            "uniform float     u_screenHeight;",

            "mat3 scale(vec3 v) {",
            "    return mat3(",
            "        vec3(v.x, 0.0, 0.0),",
            "        vec3(0.0, v.y, 0.0),",
            "        vec3(0.0, 0.0, v.z)",
            "    );",
            "}",

            "mat4 translate(vec3 v) {",
            "    return mat4(",
            "        vec4(1.0, 0.0, 0.0, 0.0),",
            "        vec4(0.0, 1.0, 0.0, 0.0),",
            "        vec4(0.0, 0.0, 1.0, 0.0),",
            "        vec4(v.x, v.y, v.z, 1.0)",
            "    );",
            "}",

            "mat4 rotate(vec3 v) {",
            "    v = v * 3.1415926535897932384626433832795 / 128.0;",
            "    mat4 pr = mat4(",
            "        vec4(1.0,       0.0,      0.0, 0.0),",
            "        vec4(0.0,  cos(v.x), sin(v.x), 0.0),",
            "        vec4(0.0, -sin(v.x), cos(v.x), 0.0),",
            "        vec4(0.0,       0.0,      0.0, 1.0)",
            "    );",
            "    pr *= mat4(",
            "        vec4( cos(v.y), 0.0, -sin(v.y), 0.0),",
            "        vec4(0.0,       1.0, 0.0,      0.0),",
            "        vec4( sin(v.y), 0.0,  cos(v.y), 0.0),",
            "        vec4(0.0,      0.0, 0.0,       1.0)",
            "    );",
            "    pr *= mat4(",
            "        vec4(cos(v.z), sin(v.z), 0.0, 0.0),",
            "        vec4(-sin(v.z), cos(v.z), 0.0, 0.0),",
            "        vec4(0.0, 0.0, 1.0, 0.0),",
            "        vec4(0.0, 0.0, 0.0, 1.0)",
            "    );",
            "    return pr;"
            "}",

            "mat3 rotate3(vec3 v) {",
            "    v = v * 3.1415926535897932384626433832795 / 128.0;",
            "    mat3 pr = mat3(",
            "        vec3(1.0,       0.0,      0.0),",
            "        vec3(0.0,  cos(v.x), -sin(v.x)),",
            "        vec3(0.0,  sin(v.x),  cos(v.x))",
            "    );",
            "    pr *= mat3(",
            "        vec3( cos(v.y), 0.0,  sin(v.y)),",
            "        vec3(0.0,       1.0,  0.0     ),",
            "        vec3(-sin(v.y), 0.0,  cos(v.y))",
            "    );",
            "    pr *= mat3(",
            "        vec3( cos(v.z), -sin(v.z), 0.0),",
            "        vec3( sin(v.z),  cos(v.z), 0.0),",
            "        vec3(0.0, 0.0, 1.0)",
            "    );",
            "    return pr;"
            "}",

            "void main() {",
            "    mat4 projection = mat4(",
            strangeLine1,
            strangeLine2,
            "        vec4(0.0, 0.0, -2.0 / 64.0, 0.0),",
            "        vec4(-1.0, 1.0, 1.0, 1.0)",
            "   );",

            "    gl_Position = projection",
            // "        * rotate(u_rotate)",
            "        * translate(u_translate)",
            "        * vec4(i_position * scale(u_scale) * rotate3(u_rotate), 1.0);",

            "    o_position = i_position;",
            "    o_uv = i_uv;",
            "    o_normals = i_normals * rotate3(u_rotate);",
            // "    o_color = i_color;",
            "}",
        };
        const GLchar* fragmentShaderSource[] = {
            #if NX | IOS
            "precision mediump float;",
            #endif
            "varying vec3      o_position;",
            "varying vec2      o_uv;",
            "varying vec3      o_normals;",
            // "varying vec4      o_color;",

            // "out vec3          o_position;",
            // "out vec2          o_uv;",
            // "out vec4          o_color;",

            "uniform bool      u_filterPR;",
            "uniform bool      u_filterBW;",
            "uniform bool      u_filterFade;",

            "uniform float     u_fade;",
            "uniform bool      u_fadeToWhite;",

            "uniform int       u_useTexture;",
            "uniform sampler2D u_texture;",
            "uniform sampler2D u_palette;",
            "uniform sampler2D u_paletteAlt;",
            "uniform vec4      u_color;",

            "uniform float     u_waterLine;",

            "void main() {",
            "    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);",
            "    if (u_useTexture == 1) {",
            "        vec4 index = texture2D(u_texture, o_uv);",

            "        if (gl_FragCoord.y > u_waterLine)",
            "            color = texture2D(u_palette, vec2(index.a, 0.0));",
            "        else",
            "            color = texture2D(u_paletteAlt, vec2(index.a, 0.0));",

            "        if (color.xyz == vec3(1.0, 0.0, 1.0)) discard;",

            // "        color = vec4(1.0, 0.7, 0.2, 1.0);",
            "    }",
            "    else if (u_useTexture == 2) {",
            "        color = texture2D(u_texture, o_uv);",
            "    }",
            "    else if (u_useTexture == 3) {",
            "        vec3 lightdir = vec3(0.0, -1.0, 0.0);",
            "        vec3 normals = normalize(o_normals);",
            "        float intensity = max(0.0, dot(lightdir, normals));",
            "        color = u_color;",
            "        if (intensity < 0.35)",
            "            color = vec4(color.rgb * (intensity + 0.5), color.a);",
            "        else",
            "            color = vec4(mix(color.rgb, vec3(1.0), (intensity - 0.5) * 2.0), color.a);", // 2.0 is too bright on GL

            "        color = color / u_color;",
            "    }",

            "    color = color * u_color;",

            "    if (u_filterBW)",
            "        color = vec4(vec3((color.r + color.g + color.b) / 3.0), color.a);",

            "    if (u_filterFade) {",
            "        float r = 0.0;",
            "        float g = 0.0;",
            "        float b = 0.0;",
            "        r = color.r - u_fade;"
            "        g = color.g;"
            "        if (r < 0.0) {"
            "            g += r;"
            "            r = 0.0;"
            "        }"
            "        b = color.b;"
            "        if (g < 0.0) {"
            "            b = max(0.0, color.b + g);"
            "            g = 0.0;"
            "        }"
            "        color = vec4(r, g, b, color.a);",
            "    }",

            // "    if (u_filterFade)",
            // "        color = vec4(color.rgb * (3.0 - u_fade) / 3.0, color.a);",

            "    gl_FragColor = color;",
            "}",
        };

        //*



        GLint compiled = GL_FALSE;
        programID = glCreateProgram();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, sizeof(vertexShaderSource) / sizeof(GLchar*), vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE) {
            IApp::Print(2, "Unable to compile vertex shader %d!", vertexShader);
            CheckShaderError(vertexShader);
            CheckGLError(__LINE__);
            return;
        }



        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, sizeof(fragmentShaderSource) / sizeof(GLchar*), fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE) {
            IApp::Print(2, "Unable to compile fragment shader %d!", fragmentShader);
            CheckShaderError(fragmentShader);
            CheckGLError(__LINE__);
            return;
        }



        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);



        glBindAttribLocation(programID, 0, "i_position");
        glBindAttribLocation(programID, 1, "i_uv");
        glBindAttribLocation(programID, 2, "i_normals");

        CheckGLError(__LINE__);

        glLinkProgram(programID);
        CheckGLError(__LINE__);

        GLint isLinked = GL_FALSE;
        glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked != GL_TRUE) {
            CheckProgramError(programID);
        }

        glUseProgram(programID);
        CheckGLError(__LINE__);

        //*
        LocUseTexture = glGetUniformLocation(programID, "u_useTexture");
        LocPosition = glGetAttribLocation(programID, "i_position");
        LocTexCoord = glGetAttribLocation(programID, "i_uv");
        LocNormals = glGetAttribLocation(programID, "i_normals");

        LocTexture = glGetUniformLocation(programID, "u_texture");
        LocPalette = glGetUniformLocation(programID, "u_palette");
        LocPaletteAlt = glGetUniformLocation(programID, "u_paletteAlt");

        LocFilterPR = glGetUniformLocation(programID, "u_filterPR");
        LocFilterBW = glGetUniformLocation(programID, "u_filterBW");
        LocFilterFade = glGetUniformLocation(programID, "u_filterFade");

        LocFade = glGetUniformLocation(programID, "u_fade");
        LocFadeToWhite = glGetUniformLocation(programID, "u_fadeToWhite");

        LocTranslate = glGetUniformLocation(programID, "u_translate");
        LocRotate = glGetUniformLocation(programID, "u_rotate");
        LocScale = glGetUniformLocation(programID, "u_scale");
        LocColor = glGetUniformLocation(programID, "u_color");

        LocWaterLine = glGetUniformLocation(programID, "u_waterLine");

        CheckGLError(__LINE__);

        glEnableVertexAttribArray(LocPosition);
        glEnableVertexAttribArray(LocTexCoord);
        // glEnableVertexAttribArray(LocColor);
        // glEnableVertexAttribArray(LocNormals);




        IApp::Print(0, "%s: %d", "LocUseTexture", LocUseTexture);
        IApp::Print(0, "%s: %d", "LocPosition", LocPosition);
        IApp::Print(0, "%s: %d", "LocTexCoord", LocTexCoord);
        IApp::Print(0, "%s: %d", "LocNormals", LocNormals);
        IApp::Print(0, "%s: %d", "LocColor", LocColor);
        IApp::Print(0, "%s: %d", "LocTexture", LocTexture);

        vector<VertexData> v;
        v.push_back(VertexData { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 });
        v.push_back(VertexData { 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0 });
        v.push_back(VertexData { 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 });
        v.push_back(VertexData { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 });
        v.push_back(VertexData { 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 });
        v.push_back(VertexData { 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0 });

        glGenBuffers(1, &rectBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, rectBufferID);
        glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(VertexData), v.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        TextSprite = new ISprite("Sprites/Debug/Objects.gif", App);
        TextSprite->LoadAnimation("Sprites/Debug/Text.bin");
        //*/
    }
    else {
        SDL_SetWindowSize(Window, DesiredWidth, DesiredHeight);
        SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_GetWindowSize(Window, &ww, &wh);
    }

    WindowWidth = ww;
    WindowHeight = wh;
    //*/
}

PUBLIC bool IGLGraphics::CheckGLError(int line) {
    const char* errstr = NULL;
    GLenum error = glGetError();
    switch (error) {
        case GL_NO_ERROR: errstr = "no error"; break;
        case GL_INVALID_ENUM: errstr = "invalid enumerant"; break;
        case GL_INVALID_VALUE: errstr = "invalid value"; break;
        case GL_INVALID_OPERATION: errstr = "invalid operation"; break;

        #if GL_STACK_OVERFLOW
            case GL_STACK_OVERFLOW: errstr = "stack overflow"; break;
            case GL_STACK_UNDERFLOW: errstr = "stack underflow"; break;
            case GL_TABLE_TOO_LARGE: errstr = "table too large"; break;
        #endif

        case GL_OUT_OF_MEMORY: errstr = "out of memory"; break;

        #ifdef GL_EXT_framebuffer_object
            case GL_INVALID_FRAMEBUFFER_OPERATION_EXT: errstr = "invalid framebuffer operation"; break;
        #endif

        #if GLU_H
            case GLU_INVALID_ENUM: errstr = "invalid enumerant"; break;
            case GLU_INVALID_VALUE: errstr = "invalid value"; break;
            case GLU_OUT_OF_MEMORY: errstr = "out of memory"; break;
            case GLU_INCOMPATIBLE_GL_VERSION: errstr = "incompatible gl version"; break;
            // case GLU_INVALID_OPERATION: errstr = "invalid operation"; break;
        #endif

        default:
            errstr = "idk";
            break;
    }
    if (error != GL_NO_ERROR) {
        IApp::Print(2, "OpenGL error on line %d: %s", line, errstr);
        return true;
    }
    return false;
}
PUBLIC bool IGLGraphics::CheckShaderError(GLuint shader) {
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    //Get info string length
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char* infoLog = new char[ maxLength ];

    //Get info log
    glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
        //Print Log
        IApp::Print(2, "%s", infoLog);
    }

    //Deallocate string
    delete[] infoLog;
    return false;
}
PUBLIC bool IGLGraphics::CheckProgramError(GLuint prog) {
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    //Get info string length
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char* infoLog = new char[ maxLength ];

    //Get info log
    glGetProgramInfoLog(prog, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
        //Print Log
        IApp::Print(2, "%s", infoLog);
    }

    //Deallocate string
    delete[] infoLog;
    return false;
}

PUBLIC void IGLGraphics::Present() {
    glBindBuffer(GL_ARRAY_BUFFER, rectBufferID);
    if (Quality > 1) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferScreen + 1);
        glViewport(0.0, 0.0, App->WIDTH * Quality, App->HEIGHT * Quality); // * 2 for retina display
        glUniform3f(LocTranslate, 0.0f, App->HEIGHT, 0.0f);
        glUniform3f(LocRotate, 0.0f, 0.0f, 0.0f);
        glUniform3f(LocScale, App->WIDTH, -App->HEIGHT, 0.0f);
        glUniform4f(LocColor, 1.0f, 1.0f, 1.0f, 1.0f);

        glUniform1i(LocUseTexture, 2);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderedTexture);
        glUniform1i(LocTexture, 0);

        glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
        glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glViewport(0.0, 0.0, WindowWidth * RetinaMult, WindowHeight * RetinaMult);
    glUniform3f(LocTranslate, 0.0f, App->HEIGHT, 0.0f);
    glUniform3f(LocRotate, 0.0f, 0.0f, 0.0f);
    glUniform3f(LocScale, App->WIDTH, -App->HEIGHT, 0.0f);
    glUniform4f(LocColor, 1.0f, 1.0f, 1.0f, 1.0f);

    glUniform1i(LocUseTexture, 2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderedTexture + (Quality > 1));
    glUniform1i(LocTexture, 0);

    glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
    glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    SDL_GL_SwapWindow(Window);
    LastSprite = NULL;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferScreen);
    glViewport(0.0, 0.0, App->WIDTH, App->HEIGHT);

    MakeAllTexturesAndFrameBuffers();

    backupframebufferindex = 0;


    // SDL_GL_SwapWindow(Window);
    //
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glUseProgram(programID);
    // glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    // glViewport(0.0, 0.0, WindowWidth * RetinaMult, WindowHeight * RetinaMult);
}
PUBLIC void IGLGraphics::Cleanup() {
    glDeleteBuffers(1, &rectBufferID);

    glDisableVertexAttribArray(LocPosition);
    glDisableVertexAttribArray(LocTexCoord);
    // glDisableVertexAttribArray(LocColor);
}

PUBLIC void IGLGraphics::MakeTexture(ISprite* sprite) {
    if (!sprite) return;

    MakeTextureList.push_back(sprite);
}
PUBLIC void IGLGraphics::MakeAllTexturesAndFrameBuffers() {
    for (int i = 0; i < MakeTextureList.size(); i++) {
        ISprite* sprite = MakeTextureList[i];

        glGenTextures(1, &sprite->TextureID);
        glBindTexture(GL_TEXTURE_2D, sprite->TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, sprite->Width, sprite->Height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, sprite->Data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glGenTextures(1, &sprite->PaletteID);
        glBindTexture(GL_TEXTURE_2D, sprite->PaletteID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);

        glGenTextures(1, &sprite->PaletteAltID);
        glBindTexture(GL_TEXTURE_2D, sprite->PaletteAltID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);

        UpdatePalette(sprite);
    }
    MakeTextureList.clear();

    for (int i = 0; i < MakeFrameBufferIDList.size(); i++) {
        ISprite* sprite = MakeFrameBufferSpList[i];
        ISprite::AnimFrame* f = (ISprite::AnimFrame*)MakeFrameBufferIDList[i];

        float u0_x = float((uint32_t)f->X) / sprite->Width;
        float u0_y = float((uint32_t)f->Y) / sprite->Height;
        float u1_x = float((uint32_t)f->X + f->W) / sprite->Width;
        float u1_y = float((uint32_t)f->Y + f->H) / sprite->Height;

        float p0_x = f->OffX;
        float p0_y = f->OffY;
        float p1_x = p0_x + f->W;
        float p1_y = p0_y + f->H;

        vector<VertexData> v;
        v.push_back(VertexData { float(p0_x), float(p0_y), 0.0, u0_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
        v.push_back(VertexData { float(p1_x), float(p0_y), 0.0, u1_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
        v.push_back(VertexData { float(p1_x), float(p1_y), 0.0, u1_x, u1_y, 1.0, 1.0, 1.0, 1.0 });

        v.push_back(VertexData { float(p0_x), float(p0_y), 0.0, u0_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
        v.push_back(VertexData { float(p1_x), float(p1_y), 0.0, u1_x, u1_y, 1.0, 1.0, 1.0, 1.0 });
        v.push_back(VertexData { float(p0_x), float(p1_y), 0.0, u0_x, u1_y, 1.0, 1.0, 1.0, 1.0 });

        glGenBuffers(1, &f->BufferID);
        glBindBuffer(GL_ARRAY_BUFFER, f->BufferID);
        glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(VertexData), v.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    MakeFrameBufferSpList.clear();
    MakeFrameBufferIDList.clear();

    for (int i = 0; i < MakeFrameBufferRawList.size(); i++) {
        GLuint buffID;
        glGenBuffers(1, &buffID);
        glBindBuffer(GL_ARRAY_BUFFER, buffID);
        glBufferData(GL_ARRAY_BUFFER, MakeFrameBufferRawList[i].size() * sizeof(VertexData), MakeFrameBufferRawList[i].data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        *MakeFrameBufferRaPtrList[i] = (int)buffID;
    }
    MakeFrameBufferRaPtrList.clear();
    MakeFrameBufferRawList.clear();
}
PUBLIC void IGLGraphics::UpdatePalette(ISprite* sprite) {
    if (!sprite->TextureID) return;

    if (sprite->LinkedSprite)
        sprite = sprite->LinkedSprite;

    glBindTexture(GL_TEXTURE_2D, sprite->PaletteID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 1, GL_BGRA, GL_UNSIGNED_BYTE, sprite->Palette);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, sprite->PaletteAltID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 1, GL_BGRA, GL_UNSIGNED_BYTE, sprite->PaletteAlt);
    glBindTexture(GL_TEXTURE_2D, 0);
}
PUBLIC int  IGLGraphics::MakeFrameBufferID(ISprite* sprite, void* fv) {
    if (!fv) return -1;

    // ISprite::AnimFrame* f = (ISprite::AnimFrame*)fv;

    MakeFrameBufferSpList.push_back(sprite);
    MakeFrameBufferIDList.push_back(fv);

    return 0;
    // float u0_x = float((uint32_t)f->X) / sprite->Width;
    // float u0_y = float((uint32_t)f->Y) / sprite->Height;
    // float u1_x = float((uint32_t)f->X + f->W) / sprite->Width;
    // float u1_y = float((uint32_t)f->Y + f->H) / sprite->Height;
    //
    // float p0_x = f->OffX;
    // float p0_y = f->OffY;
    // float p1_x = p0_x + f->W;
    // float p1_y = p0_y + f->H;
    //
    // vector<VertexData> v;
    // v.push_back(VertexData { float(p0_x), float(p0_y), 0.0, u0_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
    // v.push_back(VertexData { float(p1_x), float(p0_y), 0.0, u1_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
    // v.push_back(VertexData { float(p1_x), float(p1_y), 0.0, u1_x, u1_y, 1.0, 1.0, 1.0, 1.0 });
    //
    // v.push_back(VertexData { float(p0_x), float(p0_y), 0.0, u0_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
    // v.push_back(VertexData { float(p1_x), float(p1_y), 0.0, u1_x, u1_y, 1.0, 1.0, 1.0, 1.0 });
    // v.push_back(VertexData { float(p0_x), float(p1_y), 0.0, u0_x, u1_y, 1.0, 1.0, 1.0, 1.0 });
    //
    // glGenBuffers(1, &f->BufferID);
    // glBindBuffer(GL_ARRAY_BUFFER, f->BufferID);
    // glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(VertexData), v.data(), GL_STATIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // return f->BufferID;
}
PUBLIC int  IGLGraphics::MakeFrameBufferID(ISprite* sprite, void* where, int X, int Y, int W, int H, int OffX, int OffY, int flip) {
    float u0_x = float(X) / sprite->Width;
    float u0_y = float(Y) / sprite->Height;
    float u1_x = float(X + W) / sprite->Width;
    float u1_y = float(Y + H) / sprite->Height;

    float temp;
    if (flip & IE_FLIPX) {
        temp = u0_x;
        u0_x = u1_x;
        u1_x = temp;
    }
    if (flip & IE_FLIPY) {
        temp = u0_y;
        u0_y = u1_y;
        u1_y = temp;
    }

    float p0_x = OffX;
    float p0_y = OffY;
    float p1_x = p0_x + abs(W);
    float p1_y = p0_y + abs(H);

    vector<VertexData> v;
    v.push_back(VertexData { float(p0_x), float(p0_y), 0.0, u0_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
    v.push_back(VertexData { float(p1_x), float(p0_y), 0.0, u1_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
    v.push_back(VertexData { float(p1_x), float(p1_y), 0.0, u1_x, u1_y, 1.0, 1.0, 1.0, 1.0 });

    v.push_back(VertexData { float(p0_x), float(p0_y), 0.0, u0_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
    v.push_back(VertexData { float(p1_x), float(p1_y), 0.0, u1_x, u1_y, 1.0, 1.0, 1.0, 1.0 });
    v.push_back(VertexData { float(p0_x), float(p1_y), 0.0, u0_x, u1_y, 1.0, 1.0, 1.0, 1.0 });

    MakeFrameBufferRaPtrList.push_back((int*)where);
    MakeFrameBufferRawList.push_back(v);

    return 0;

    // GLuint buffID;
    // glGenBuffers(1, &buffID);
    // glBindBuffer(GL_ARRAY_BUFFER, buffID);
    // glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(VertexData), v.data(), GL_STATIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // return (int)buffID;
}
PUBLIC int  IGLGraphics::MakeVertexBuffer(vector<IVertex> vert) {
    vector<VertexData> v;
    for (int i = 0; i < vert.size(); i++) {
        v.push_back(VertexData { GLfloat(vert[i].x), GLfloat(vert[i].y), GLfloat(vert[i].z), 0.7f, 0.7f, 1.0f, 1.0f, 1.0f, 1.0f });
    }

    GLuint buffID;
    glGenBuffers(1, &buffID);
    glBindBuffer(GL_ARRAY_BUFFER, buffID);
    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(VertexData), v.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return (int)buffID;
}
PUBLIC int  IGLGraphics::MakeVertexBuffer(IModel* model, bool verts) {
    int frame = 0;
    vector<VertexData> v;

    for (int i = 0; i < model->Faces.size(); i++) {
        IFace t = model->Faces[i];

        if (t.Quad) {
            v.push_back(VertexData {
                GLfloat(model->Vertices[frame][t.v1].x), GLfloat(model->Vertices[frame][t.v1].y), GLfloat(model->Vertices[frame][t.v1].z), 0.7f, 0.7f,
                GLfloat(model->Normals[frame][t.v1].x), GLfloat(model->Normals[frame][t.v1].y), GLfloat(model->Normals[frame][t.v1].z), 1.0f });
            v.push_back(VertexData {
                GLfloat(model->Vertices[frame][t.v3].x), GLfloat(model->Vertices[frame][t.v3].y), GLfloat(model->Vertices[frame][t.v3].z), 0.7f, 0.7f,
                GLfloat(model->Normals[frame][t.v3].x), GLfloat(model->Normals[frame][t.v3].y), GLfloat(model->Normals[frame][t.v3].z), 1.0f });
            v.push_back(VertexData {
                GLfloat(model->Vertices[frame][t.v4].x), GLfloat(model->Vertices[frame][t.v4].y), GLfloat(model->Vertices[frame][t.v4].z), 0.7f, 0.7f,
                GLfloat(model->Normals[frame][t.v4].x), GLfloat(model->Normals[frame][t.v4].y), GLfloat(model->Normals[frame][t.v4].z), 1.0f });
        }

        v.push_back(VertexData {
            GLfloat(model->Vertices[frame][t.v1].x), GLfloat(model->Vertices[frame][t.v1].y), GLfloat(model->Vertices[frame][t.v1].z), 0.7f, 0.7f,
            GLfloat(model->Normals[frame][t.v1].x), GLfloat(model->Normals[frame][t.v1].y), GLfloat(model->Normals[frame][t.v1].z), 1.0f });
        v.push_back(VertexData {
            GLfloat(model->Vertices[frame][t.v2].x), GLfloat(model->Vertices[frame][t.v2].y), GLfloat(model->Vertices[frame][t.v2].z), 0.7f, 0.7f,
            GLfloat(model->Normals[frame][t.v2].x), GLfloat(model->Normals[frame][t.v2].y), GLfloat(model->Normals[frame][t.v2].z), 1.0f });
        v.push_back(VertexData {
            GLfloat(model->Vertices[frame][t.v3].x), GLfloat(model->Vertices[frame][t.v3].y), GLfloat(model->Vertices[frame][t.v3].z), 0.7f, 0.7f,
            GLfloat(model->Normals[frame][t.v3].x), GLfloat(model->Normals[frame][t.v3].y), GLfloat(model->Normals[frame][t.v3].z), 1.0f });
    }

    GLuint buffID;
    glGenBuffers(1, &buffID);
    glBindBuffer(GL_ARRAY_BUFFER, buffID);
    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(VertexData), v.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return (int)buffID;
}
PUBLIC void IGLGraphics::DeleteBufferID(int buffID) {
    glDeleteBuffers(1, (GLuint*)&buffID);
}

//*
PUBLIC void IGLGraphics::BeginSpriteListBuffer() {
    RawVertArray.clear();
}
PUBLIC void IGLGraphics::AddToSpriteListBuffer(ISprite* sprite, int X, int Y, int W, int H, int OffX, int OffY, int Flip) {
    float u0_x = float(X) / sprite->Width;
    float u0_y = float(Y) / sprite->Height;
    float u1_x = float(X + W) / sprite->Width;
    float u1_y = float(Y + H) / sprite->Height;

    float temp;
    if (Flip & IE_FLIPX) {
        temp = u0_x;
        u0_x = u1_x;
        u1_x = temp;
    }
    if (Flip & IE_FLIPY) {
        temp = u0_y;
        u0_y = u1_y;
        u1_y = temp;
    }

    float p0_x = OffX;
    float p0_y = OffY;
    float p1_x = p0_x + abs(W);
    float p1_y = p0_y + abs(H);

    RawVertArray.push_back(VertexData { float(p0_x), float(p0_y), 0.0, u0_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
    RawVertArray.push_back(VertexData { float(p1_x), float(p0_y), 0.0, u1_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
    RawVertArray.push_back(VertexData { float(p1_x), float(p1_y), 0.0, u1_x, u1_y, 1.0, 1.0, 1.0, 1.0 });

    RawVertArray.push_back(VertexData { float(p0_x), float(p0_y), 0.0, u0_x, u0_y, 1.0, 1.0, 1.0, 1.0 });
    RawVertArray.push_back(VertexData { float(p1_x), float(p1_y), 0.0, u1_x, u1_y, 1.0, 1.0, 1.0, 1.0 });
    RawVertArray.push_back(VertexData { float(p0_x), float(p1_y), 0.0, u0_x, u1_y, 1.0, 1.0, 1.0, 1.0 });
}
PUBLIC int  IGLGraphics::FinishSpriteListBuffer() {
    GLuint bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, RawVertArray.size() * sizeof(VertexData), RawVertArray.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return (int)bufferID;
}
//*/

PUBLIC void IGLGraphics::SetClip(int x, int y, int w, int h) {
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, App->HEIGHT - y - h, w, h);
}
PUBLIC void IGLGraphics::ClearClip() {
    glDisable(GL_SCISSOR_TEST);
}

PUBLIC void IGLGraphics::MakeClone() {
    HaveClone = true;
}
PUBLIC void IGLGraphics::DrawClone() {
    if (HaveClone) {

    }
}
PUBLIC void IGLGraphics::ClearClone() {
    HaveClone = false;
}

PUBLIC void IGLGraphics::SetDrawFunc(int a) {
	switch (a) {
		case 1:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		default:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
	}
}

PUBLIC void IGLGraphics::SetFade(int fade) {
    IGraphics::SetFade(fade);

    glUniform1f(LocFade, Fade / 255.0 * 3.0);
    glUniform1i(LocFadeToWhite, FadeToWhite);
}
PUBLIC void IGLGraphics::SetFilter(int filter) {
    IGraphics::SetFilter(filter);

    glUniform1i(LocFilterBW, !!(filter & 0x1));
    glUniform1i(LocFilterPR, !!(filter & 0x2));
    glUniform1i(LocFilterFade, !!(filter & 0x4));
}

PUBLIC void IGLGraphics::DrawTriangle(int p0_x, int p0_y, int p1_x, int p1_y, int p2_x, int p2_y, Uint32 col) {
    float r = (col >> 16 & 0xFF) / 255.f;
    float g = (col >> 8 & 0xFF) / 255.f;
    float b = (col & 0xFF) / 255.f;

    glUniform3f(LocTranslate, 0.0f, 0.0f, 0.0f);
    // glUniform3f(LocRotate, 0.0f, 0.0f, 0.0f);
    // glUniform3f(LocScale, 1.0f, 1.0f, 0.0f);
    glUniform4f(LocColor, r, g, b, DrawAlpha / 255.f);

    vector<VertexData> v;
    v.push_back(VertexData { float(p0_x), float(p0_y), 0.0, 0.0, 0.0, 1.0f, 1.0f, 1.0f, 1.0f });
    v.push_back(VertexData { float(p1_x), float(p1_y), 0.0, 0.0, 0.0, 1.0f, 1.0f, 1.0f, 1.0f });
    v.push_back(VertexData { float(p2_x), float(p2_y), 0.0, 0.0, 0.0, 1.0f, 1.0f, 1.0f, 1.0f });

    glUniform1i(LocUseTexture, 0);

    GLuint buffer;
    // glEnableVertexAttribArray(LocPosition);
    // glEnableVertexAttribArray(LocTexCoord);
    // glEnableVertexAttribArray(LocColor);
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(VertexData), v.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
    glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
    // glVertexAttribPointer(LocColor,    4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(5 * sizeof(GLfloat)));
    glDrawArrays(GL_TRIANGLES, 0, v.size());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &buffer);
    // glDisableVertexAttribArray(LocPosition);
    // glDisableVertexAttribArray(LocTexCoord);
    // glDisableVertexAttribArray(LocColor);
}
PUBLIC void IGLGraphics::DrawRectangle(int x, int y, int w, int h, Uint32 col) {
    float r = (col >> 16 & 0xFF) / 255.f;
    float g = (col >> 8 & 0xFF) / 255.f;
    float b = (col & 0xFF) / 255.f;

    glUniform3f(LocTranslate, x, y, 0.0f);
    //glUniform3f(LocRotate, 0.0f, 0.0f, 0.0f);
    glUniform3f(LocScale, float(w), float(h), 0.0f);
    glUniform4f(LocColor, r, g, b, DrawAlpha / 255.f);

    glUniform1i(LocUseTexture, 0);

    glBindBuffer(GL_ARRAY_BUFFER, rectBufferID);
    glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
    glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
    // glVertexAttribPointer(LocColor,    4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(5 * sizeof(GLfloat)));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUniform3f(LocScale, 1.0f, 1.0f, 0.0f);
}
PUBLIC void IGLGraphics::DrawRectangleSkewedH(int x, int y, int w, int h, int sk, Uint32 col) {
    //w--;
    //h--;
    sk--;

    DrawTriangle(
        x, y,
        x + w, y,
        x + w + sk, y + h, col);

    DrawTriangle(
        x, y,
        x + sk, y + h,
        x + w + sk, y + h, col);
}

PUBLIC void IGLGraphics::DrawRectangleStroke(int x, int y, int w, int h, Uint32 col) {
	float r = (col >> 16 & 0xFF) / 255.f;
	float g = (col >> 8 & 0xFF) / 255.f;
	float b = (col & 0xFF) / 255.f;

	glUniform1i(LocUseTexture, 0);
	//glUniform3f(LocRotate, 0.0f, 0.0f, 0.0f);
	glUniform4f(LocColor, r, g, b, DrawAlpha / 255.f);
	glBindBuffer(GL_ARRAY_BUFFER, rectBufferID);

	glUniform3f(LocTranslate, x, y, 0.0f);
	glUniform3f(LocScale, float(w - 1), 1.0f, 0.0f);
	glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
	glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glUniform3f(LocScale, 1.0f, float(h - 1), 0.0f);
	glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
	glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glUniform3f(LocTranslate, x + w - 1, y, 0.0f);
	glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
	glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glUniform3f(LocTranslate, x, y + h - 1, 0.0f);
	glUniform3f(LocScale, float(w), 1.0f, 0.0f);
	glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
	glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUniform3f(LocScale, 1.0f, 1.0f, 0.0f);
}

PUBLIC void IGLGraphics::DrawSprite(ISprite* sprite, int animation, int frame, int x, int y, int angle, int flip) {
    if (!sprite) return;
    if (!sprite->TextureID) return;
    if (animation < 0 || animation >= sprite->Animations.size()) {
        IApp::Print(2, "Animation %d does not exist in sprite %s!", animation, sprite->Filename);
        assert(animation >= 0 && animation < sprite->Animations.size());
    }
    if (frame < 0 || frame >= sprite->Animations[animation].FrameCount) {
        IApp::Print(2, "Frame %d in animation \"%s\" does not exist in sprite %s!", frame, sprite->Animations[animation].Name, sprite->Filename);
        assert(frame >= 0 && frame < sprite->Animations[animation].FrameCount);
    }

    ISprite::AnimFrame animframe = sprite->Animations[animation].Frames[frame];

    glUniform3f(LocTranslate, x, y, 0.0f);
	if (angle)
		glUniform3f(LocRotate, 0.0f, 0.0f, angle);
	if (flip)
		glUniform3f(LocScale,
			(flip & IE_FLIPX) ? -1.0f : 1.0f,
			(flip & IE_FLIPY) ? -1.0f : 1.0f, 0.0f);
        //(float)SX / Width * ((flip & IE_FLIPX) ? -1.0f : 1.0f),
        //(float)SY / Height * ((flip & IE_FLIPY) ? -1.0f : 1.0f), 0.0f);
    glUniform4f(LocColor, ColorBlendR, ColorBlendG, ColorBlendB, DrawAlpha / 255.f);

    glUniform1i(LocUseTexture, 1);
    if (LastSprite != sprite) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprite->TextureID);
        glUniform1i(LocTexture, 0);

        LastSprite = sprite;

        if (sprite->LinkedSprite)
            sprite = sprite->LinkedSprite;

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, sprite->PaletteID);
        glUniform1i(LocPalette, 1);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, sprite->PaletteAltID);
        glUniform1i(LocPaletteAlt, 2);
    }

    if (sprite->Paletted == 2)
        glUniform1f(LocWaterLine, (App->HEIGHT - WaterPaletteStartLine));

    glBindBuffer(GL_ARRAY_BUFFER, animframe.BufferID);
    glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
    glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUniform1f(LocWaterLine, -0xFFFF);
	if (angle)
		glUniform3f(LocRotate, 0.0f, 0.0f, 0.0f);
	if (flip)
		glUniform3f(LocScale, 1.0f, 1.0f, 0.0f);

    ColorBlendR = 1.0f;
    ColorBlendG = 1.0f;
    ColorBlendB = 1.0f;
}
PUBLIC void IGLGraphics::DrawSpriteSized(ISprite* sprite, int animation, int frame, int x, int y, int angle, int flip, int w, int h) {
    if (!sprite) return;
    if (!sprite->TextureID) return;
    if (animation < 0 || animation >= sprite->Animations.size()) {
        IApp::Print(2, "Animation %d does not exist in sprite %s!", animation, sprite->Filename);
        assert(animation >= 0 && animation < sprite->Animations.size());
    }
    if (frame < 0 || frame >= sprite->Animations[animation].FrameCount) {
        IApp::Print(2, "Frame %d in animation \"%s\" does not exist in sprite %s!", frame, sprite->Animations[animation].Name, sprite->Filename);
        assert(frame >= 0 && frame < sprite->Animations[animation].FrameCount);
    }

    ISprite::AnimFrame animframe = sprite->Animations[animation].Frames[frame];

    glUniform3f(LocTranslate,
        x + animframe.OffX - (animframe.OffX * (float)w / animframe.W),
        y + animframe.OffY - (animframe.OffY * (float)h / animframe.H), 0.0f);
	if (angle)
		glUniform3f(LocRotate, 0.0f, 0.0f, angle);
    glUniform3f(LocScale,
        // (flip & IE_FLIPX) ? -1.0f : 1.0f,
        // (flip & IE_FLIPY) ? -1.0f : 1.0f, 0.0f);
        (float)w / animframe.W * ((flip & IE_FLIPX) ? -1.0f : 1.0f),
        (float)h / animframe.H * ((flip & IE_FLIPY) ? -1.0f : 1.0f), 0.0f);
    glUniform4f(LocColor, ColorBlendR, ColorBlendG, ColorBlendB, DrawAlpha / 255.f);

    glUniform1i(LocUseTexture, 1);
    if (LastSprite != sprite) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprite->TextureID);
        glUniform1i(LocTexture, 0);

        LastSprite = sprite;

        if (sprite->LinkedSprite)
            sprite = sprite->LinkedSprite;

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, sprite->PaletteID);
        glUniform1i(LocPalette, 1);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, sprite->PaletteAltID);
        glUniform1i(LocPaletteAlt, 2);
    }

    if (sprite->Paletted == 2)
        glUniform1f(LocWaterLine, (App->HEIGHT - WaterPaletteStartLine));

    glBindBuffer(GL_ARRAY_BUFFER, animframe.BufferID);
    glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
    glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUniform1f(LocWaterLine, -0xFFFF);
	if (angle)
		glUniform3f(LocRotate, 0.0f, 0.0f, 0.0f);
	glUniform3f(LocScale, 1.0f, 1.0f, 0.0f);

    ColorBlendR = 1.0f;
    ColorBlendG = 1.0f;
    ColorBlendB = 1.0f;
}
PUBLIC void IGLGraphics::DrawSprite(ISprite* sprite, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, int Angle, int Flip, int RealCenterX, int RealCenterY) {
    DrawSprite(sprite, SrcX, SrcY, Width, Height, CenterX, CenterY, Angle, Flip, RealCenterX, RealCenterY, Width, Height);
}
PUBLIC void IGLGraphics::DrawSprite(ISprite* sprite, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, int Angle, int Flip, int RealCenterX, int RealCenterY, int SX, int SY) {
    if (!Width) return;
    if (!Height) return;
    if (!sprite) return;

    return;


    /*
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, sprite->TextureID);

    glTranslatef(CenterX, CenterY, 0.0f);
    glRotatef(Angle / 128.0 * M_PI, 0.0f, 0.0f, 1.0f);
    glScalef(SX / Width, SY / Height, 1.0f);

    glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glTexCoord2f(float(SrcX) / sprite->Width, float(SrcY) / sprite->Height);
        glVertex2i(-RealCenterX, -RealCenterY);
        glTexCoord2f(float(SrcX + Width) / sprite->Width, float(SrcY) / sprite->Height);
        glVertex2i(-RealCenterX + Width, -RealCenterY);
        glTexCoord2f(float(SrcX + Width) / sprite->Width, float(SrcY + Height) / sprite->Height);
        glVertex2i(-RealCenterX + Width, -RealCenterY + Height);
        glTexCoord2f(float(SrcX) / sprite->Width, float(SrcY + Height) / sprite->Height);
        glVertex2i(-RealCenterX, -RealCenterY + Height);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
    //*/
    float temp;
    float u0_x = float(SrcX) / sprite->Width;
    float u0_y = float(SrcY) / sprite->Height;
    float u1_x = float(SrcX + Width) / sprite->Width;
    float u1_y = float(SrcY + Height) / sprite->Height;
    if (Flip & IE_FLIPX) {
        temp = u0_x;
        u0_x = u1_x;
        u1_x = temp;
        RealCenterX = -RealCenterX;
        if (RealCenterX != 0)
            RealCenterX -= Width;
    }
    if (Flip & IE_FLIPY) {
        temp = u0_y;
        u0_y = u1_y;
        u1_y = temp;
        RealCenterY = -RealCenterY;
        if (RealCenterY != 0)
            RealCenterY -= Height;
    }

    float p0_x = RealCenterX;
    float p0_y = RealCenterY;
    float p1_x = p0_x + Width;
    float p1_y = p0_y + Height;

    glUniform3f(LocTranslate, CenterX, CenterY, 0.0f);
    glUniform3f(LocRotate, 0.0f, 0.0f, Angle);
    glUniform3f(LocScale, (float)SX / Width, (float)SY / Height, 0.0f);

    vector<VertexData> v;
    v.push_back(VertexData { float(p0_x), float(p0_y), 0.0, u0_x, u0_y, 1.0, 1.0, 1.0, DrawAlpha / 255.f });
    v.push_back(VertexData { float(p1_x), float(p0_y), 0.0, u1_x, u0_y, 1.0, 1.0, 1.0, DrawAlpha / 255.f });
    v.push_back(VertexData { float(p1_x), float(p1_y), 0.0, u1_x, u1_y, 1.0, 1.0, 1.0, DrawAlpha / 255.f });

    v.push_back(VertexData { float(p0_x), float(p0_y), 0.0, u0_x, u0_y, 1.0, 1.0, 1.0, DrawAlpha / 255.f });
    v.push_back(VertexData { float(p1_x), float(p1_y), 0.0, u1_x, u1_y, 1.0, 1.0, 1.0, DrawAlpha / 255.f });
    v.push_back(VertexData { float(p0_x), float(p1_y), 0.0, u0_x, u1_y, 1.0, 1.0, 1.0, DrawAlpha / 255.f });


    glUniform1i(LocUseTexture, 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite->TextureID);
    glUniform1i(LocTexture, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, sprite->PaletteID);
    glUniform1i(LocPalette, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, sprite->PaletteAltID);
    glUniform1i(LocPaletteAlt, 2);

    if (sprite->Paletted == 2)
        glUniform1f(LocWaterLine, (App->HEIGHT - WaterPaletteStartLine));

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(VertexData), v.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
    glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
    // glVertexAttribPointer(LocColor,    4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(5 * sizeof(GLfloat)));
    glDrawArrays(GL_TRIANGLES, 0, v.size());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &buffer);

    glUniform1f(LocWaterLine, -0xFFFF);
}
PUBLIC void IGLGraphics::DrawSpriteBuffered(ISprite* sprite, int bufferID, int x, int y, int angle, int flip) {
    if (!sprite) return;
    if (!sprite->TextureID) return;

    glUniform3f(LocTranslate, x, y, 0.0f);
    // glUniform3f(LocScale, 1.0f, 1.0f, 0.0f);

    glUniform1i(LocUseTexture, 1);
    if (LastSprite != sprite) {
        // glUniform3f(LocRotate, 0.0f, 0.0f, angle);
        glUniform4f(LocColor, 1.0f, 1.0f, 1.0f, DrawAlpha / 255.f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprite->TextureID);
        glUniform1i(LocTexture, 0);

        LastSprite = sprite;

        if (sprite->LinkedSprite)
            sprite = sprite->LinkedSprite;

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, sprite->PaletteID);
        glUniform1i(LocPalette, 1);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, sprite->PaletteAltID);
        glUniform1i(LocPaletteAlt, 2);
    }

    if (sprite->Paletted == 2)
        glUniform1f(LocWaterLine, (App->HEIGHT - WaterPaletteStartLine));

    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
    glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUniform1f(LocWaterLine, -0xFFFF);

    ColorBlendR = 1.0f;
    ColorBlendG = 1.0f;
    ColorBlendB = 1.0f;
}
PUBLIC void IGLGraphics::DrawSpriteListBuffer(ISprite* sprite, int bufferID, int count, int x, int y) {
    if (!sprite) return;
    if (!sprite->TextureID) return;

    glUniform3f(LocTranslate, x, y, 0.0f);
    // glUniform3f(LocScale, 1.0f, 1.0f, 0.0f);
	// glUniform3f(LocRotate, 0.0f, 0.0f, 0.0f);

    glUniform1i(LocUseTexture, 1);
    if (LastSprite != sprite) {
        glUniform4f(LocColor, 1.0f, 1.0f, 1.0f, DrawAlpha / 255.f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprite->TextureID);
        glUniform1i(LocTexture, 0);

        LastSprite = sprite;

        if (sprite->LinkedSprite)
            sprite = sprite->LinkedSprite;

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, sprite->PaletteID);
        glUniform1i(LocPalette, 1);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, sprite->PaletteAltID);
        glUniform1i(LocPaletteAlt, 2);
    }

    if (sprite->Paletted == 2)
        glUniform1f(LocWaterLine, (App->HEIGHT - WaterPaletteStartLine));

    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
    glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
    glDrawArrays(GL_TRIANGLES, 0, 6 * count);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUniform1f(LocWaterLine, -0xFFFF);

    ColorBlendR = 1.0f;
    ColorBlendG = 1.0f;
    ColorBlendB = 1.0f;
}

PUBLIC void IGLGraphics::DrawText(int x, int y, const char* string, unsigned int pixel) {
    float r = (pixel >> 16 & 0xFF) / 255.f;
    float g = (pixel >> 8 & 0xFF) / 255.f;
    float b = (pixel & 0xFF) / 255.f;

    int f;
    for (int i = 0; i < strlen(string); i++) {
        f = string[i];
        if (f >= 'A' && f <= 'Z')
            f = f - 'A' + 10;
        else if (f >= 'a' && f <= 'z')
            f = f - 'a' + 10;
        else if (f >= '0' && f <= '9')
            f = f - '0';
        else if (f >= '*' && f <= '/')
            f = f - '*' + 36;
        else if (f == ':')
            f = f - ':' + 42;
        else
            f = -1;

        if (f < 0)
            continue;

        ColorBlendR = r;
        ColorBlendG = g;
        ColorBlendB = b;
        DrawSprite(TextSprite, 0, f, x + i * 8 + 4, y + 4, 0, IE_NOFLIP);
    }
}
PUBLIC void IGLGraphics::DrawTextShadow(int x, int y, const char* string, unsigned int pixel) {
    DrawText(x, y, string, pixel);
}

PUBLIC void IGLGraphics::DrawLine(int x0, int y0, int x1, int y1, Uint32 col) {

}

PUBLIC void IGLGraphics::DrawModelOn2D(IModel* model, int x, int y, double scale, int rx, int ry, int rz, Uint32 col, bool wireframe) {
    float r = (col >> 16 & 0xFF) / 255.f;
    float g = (col >> 8 & 0xFF) / 255.f;
    float b = (col & 0xFF) / 255.f;

    glUniform3f(LocTranslate, x, y, 32.f);
    glUniform3f(LocRotate, rx, ry, -rz);
    glUniform3f(LocScale, scale, scale, scale);
    glUniform4f(LocColor, r, g, b, DrawAlpha / 255.f);

    glUniform1i(LocUseTexture, 3);

    glUniform1f(LocWaterLine, -0xFFFF);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    // glDepthFunc(GL_LESS);

    int yep = 0;
    for (int i = 0; i < model->Faces.size(); i++) {
        IFace t = model->Faces[i];
        yep += 3;
        if (t.Quad)
            yep += 3;
    }

    glEnableVertexAttribArray(LocNormals);

    glBindBuffer(GL_ARRAY_BUFFER, model->BufferID_V);
    glVertexAttribPointer(LocPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(0 * sizeof(GLfloat)));
    glVertexAttribPointer(LocTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(LocNormals,  3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(5 * sizeof(GLfloat)));
	if (wireframe)
	    glDrawArrays(GL_LINES, 0, yep);
	else
		glDrawArrays(GL_TRIANGLES, 0, yep);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUniform1f(LocWaterLine, -0xFFFF);
	glUniform3f(LocScale, 1.0f, 1.0f, 0.0f);
	glUniform3f(LocRotate, 0.0f, 0.0f, 0.0f);

    glDisableVertexAttribArray(LocNormals);

    glDepthMask(GL_TRUE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    ColorBlendR = 1.0f;
    ColorBlendG = 1.0f;
    ColorBlendB = 1.0f;
}
PUBLIC void IGLGraphics::DrawSpriteIn3D(ISprite* sprite, int animation, int frame, int x, int y, int z, double scale, int rx, int ry, int rz) {

}
