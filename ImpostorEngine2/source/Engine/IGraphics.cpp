#if INTERFACE
#include <Utils/Standard.h>
#include <Utils/StandardSDL2.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>
#include <Engine/IModel.h>

need_t ISprite;
need_t IModel;

class IGraphics {
protected:
	int Filter = 0;
public:
	IApp * App = NULL;
	SDL_Surface* Screen = NULL;
	uint32_t* FrameBuffer = NULL;

	int WindowWidth = 16;
	int WindowHeight = 9;

	SDL_Window* Window = NULL;
	SDL_Renderer* Renderer = NULL;

	SDL_Surface* WindowScreen = NULL;
	SDL_Texture* ScreenTexture = NULL;

	uint32_t* FrameBufferClone = NULL;
	bool HaveClone = false;

	uint8_t Fade = 0;
	bool    FadeToWhite = false;

	int    PixelScale = 2;
	int    RENDER_WIDTH = 400;

	long    ContourX[800][2];
	int    DivTable[0x100];

	int    WaterPaletteStartLine = 0xFFFF;

	int    Clip[4];

	int8_t* Deform = NULL;
	bool    DoDeform = false;

	int    DrawAlpha = 0xFF;
	int    DrawModeOverlay = false;

	double  MyCos[256];
	double  MySin[256]; ////
};
#endif

#include <Engine/IResource.h>
#include <Engine/IResources.h>
#include <Engine/IGraphics.h>
#include <Engine/IMath.h>
#include <Engine/Diagnostics/Memory.h>

unsigned char Font8x8_basic[128][8];
void (IGraphics::*SetPixelFunction)(int, int, uint32_t);
uint32_t (IGraphics::*SetFilterFunction[4])(uint32_t);

PUBLIC IGraphics::IGraphics() {

}

PUBLIC IGraphics::IGraphics(IApp* app) {
	App = app;

	SetPixelFunction = &IGraphics::SetPixelNormal;
	SetFilterFunction[0] = &IGraphics::FilterNone;
	SetFilterFunction[1] = &IGraphics::FilterNone;
	SetFilterFunction[2] = &IGraphics::FilterNone;
	SetFilterFunction[3] = &IGraphics::FilterNone;

	Deform = (int8_t*)calloc(App->HEIGHT, 1);

	Clip[0] = 0;
	Clip[1] = 0;
	Clip[2] = App->WIDTH;
	Clip[3] = App->HEIGHT;

	for (int i = 0; i < 0x100; i++)
		DivTable[i] = i / 3;

	for (int a = 0; a < 256; a++) {
		MySin[a] = -std::sin(a * M_PI / 128);
		MyCos[a] = std::cos(a * M_PI / 128);
	}

	Init();
}

PUBLIC VIRTUAL IGraphics::~IGraphics() {

}

PUBLIC VIRTUAL void IGraphics::MakeAllTexturesAndFrameBuffers() {

}

PUBLIC VIRTUAL void IGraphics::MakeTexture(ISprite* sprite) {

}

PUBLIC VIRTUAL void IGraphics::UpdatePalette(ISprite* sprite) {

}


PUBLIC VIRTUAL int IGraphics::MakeFrameBufferID(ISprite* sprite, void* f) {
	return -2;
}

PUBLIC VIRTUAL int IGraphics::MakeFrameBufferID(ISprite* sprite, void* where, int X, int Y, int W, int H, int OffX, int OffY, int flip) {
	return -2;
}

PUBLIC VIRTUAL int IGraphics::MakeVertexBuffer(vector<IVertex> vert) {
	return -2;
}

PUBLIC VIRTUAL int IGraphics::MakeVertexBuffer(IModel* m, bool verts) {
	return -2;
}

PUBLIC VIRTUAL void IGraphics::DeleteBufferID(int buffID) {

}

PUBLIC VIRTUAL void IGraphics::BeginSpriteListBuffer() {

}

PUBLIC VIRTUAL void IGraphics::AddToSpriteListBuffer(ISprite* sprite, int X, int Y, int W, int H, int OffX, int OffY, int Flip) {

}

PUBLIC VIRTUAL int IGraphics::FinishSpriteListBuffer() {
	return -2;
}

PUBLIC VIRTUAL void IGraphics::Init() {
	PixelScale = 1;
	FrameBuffer = (uint32_t*)calloc(App->WIDTH * App->HEIGHT, sizeof(uint32_t));
	FrameBufferClone = (uint32_t*)calloc(App->WIDTH * App->HEIGHT, sizeof(uint32_t));
	RENDER_WIDTH = App->WIDTH;

	IResource* res = IResources::Load("Sprites/UI/DevFont.bin");
	if (res) {
		res->Read(Font8x8_basic, 0x400);
	}
}

PUBLIC VIRTUAL void IGraphics::SetDisplay(int DesiredWidth, int DesiredHeight, int IsSharp) {
	if (IsSharp)
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	else
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	if (!Window) {
		Window = SDL_CreateWindow("Sonic 3'Mixed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			DesiredWidth, DesiredHeight, SDL_WINDOW_SHOWN
			#if ANDROID | IOS
			| SDL_WINDOW_BORDERLESS
			| SDL_WINDOW_FULLSCREEN
			#endif
			| SDL_WINDOW_ALLOW_HIGHDPI);

		Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC
		);
	}
	else {
		SDL_SetWindowSize(Window, DesiredWidth, DesiredHeight);
		SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}

	WindowWidth = DesiredWidth;
	WindowHeight = DesiredHeight;

	int PixelScale = (DesiredWidth / App->WIDTH);

	unsigned int rmask, gmask, bmask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0x0000ff00;
	gmask = 0x00ff0000;
	bmask = 0xff000000;
#else
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
#endif

	if (!Screen) {
		PixelScale = 1;

		Screen = SDL_CreateRGBSurface(0, App->WIDTH, App->HEIGHT, 32, rmask, gmask, bmask, 0);
		if (!Screen) {
			IApp::Print(2, "Screen could not be created! (%s)", SDL_GetError());
			exit(-1);
		}
		Screen->pixels = FrameBuffer;

		WindowScreen = SDL_CreateRGBSurface(0, App->WIDTH * PixelScale, App->HEIGHT * PixelScale, 32, rmask, gmask, bmask, 0);
		if (!WindowScreen) {
			IApp::Print(2, "Window Screen could not be created! (%s)", SDL_GetError());
			exit(-1);
		}
		ScreenTexture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, App->WIDTH * PixelScale, App->HEIGHT * PixelScale);
		if (!ScreenTexture) {
			IApp::Print(2, "Screen Texture could not be created! (%s)", SDL_GetError());
			exit(-1);
		}
	}
	else {
		SDL_FreeSurface(WindowScreen);
		SDL_DestroyTexture(ScreenTexture);

		WindowScreen = SDL_CreateRGBSurface(0, App->WIDTH * PixelScale, App->HEIGHT * PixelScale, 32, rmask, gmask, bmask, 0);
		if (!WindowScreen) {
			IApp::Print(2, "Window Screen could not be created! (%s)", SDL_GetError());
			exit(-1);
		}
		ScreenTexture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, App->WIDTH * PixelScale, App->HEIGHT * PixelScale);
		if (!ScreenTexture) {
			IApp::Print(2, "Screen Texture could not be created! (%s)", SDL_GetError());
			exit(-1);
		}
	}
}

PUBLIC VIRTUAL void IGraphics::Present() {
	if (IApp::Platform == Platforms::Switch) {
		SDL_RenderClear(Renderer);
		SDL_UpdateTexture(ScreenTexture, NULL, Screen->pixels, Screen->pitch);
		SDL_RenderCopy(Renderer, ScreenTexture, NULL, NULL);
		SDL_RenderPresent(Renderer);
	} else {
		SDL_RenderClear(Renderer);

		//* // Higher quality, working
		SDL_BlitScaled(Screen, NULL, WindowScreen, NULL);
		SDL_UpdateTexture(ScreenTexture, NULL, WindowScreen->pixels, WindowScreen->pitch);
		SDL_RenderCopy(Renderer, ScreenTexture, NULL, NULL);
		//*/

		/*// Working
		SDL_UpdateTexture(ScreenTexture, NULL, Screen->pixels, Screen->pitch);
		SDL_RenderCopy(Renderer, ScreenTexture, NULL, NULL);
		//*/
		SDL_RenderPresent(Renderer);
	}
	// Clear framebuffer
	memset(FrameBuffer, 0, 407040);
}

PUBLIC VIRTUAL void IGraphics::Cleanup() {
	SDL_FreeSurface(WindowScreen);
	SDL_DestroyTexture(ScreenTexture);
	SDL_DestroyWindow(Window);
	SDL_FreeSurface(Screen);
}

PUBLIC void IGraphics::SetPixelNormal(int x, int y, uint32_t pixel) {
	*(FrameBuffer + y * RENDER_WIDTH + x) = pixel;
}

PUBLIC void IGraphics::SetPixelAlpha(int x, int y, uint32_t pixel) {
	*(FrameBuffer + y * RENDER_WIDTH + x) = ColorBlendHex(*(FrameBuffer + y * RENDER_WIDTH + x), pixel, DrawAlpha);
}

PUBLIC void IGraphics::SetPixelAdditive(int x, int y, uint32_t pixel) {
	*(FrameBuffer + y * RENDER_WIDTH + x) = ColorAddHex(*(FrameBuffer + y * RENDER_WIDTH + x), pixel, DrawAlpha);
}

PUBLIC uint32_t IGraphics::FilterNone(uint32_t pixel) {
	return pixel;
}

PUBLIC uint32_t IGraphics::FilterGrayscale(uint32_t pixel) {
	pixel = (DivTable[(pixel >> 16) & 0xFF] + DivTable[(pixel >> 8) & 0xFF] + DivTable[(pixel) & 0xFF]) & 0xFF;
	pixel = pixel << 16 | pixel << 8 | pixel;
	return pixel;
}

PUBLIC uint32_t IGraphics::FilterInversionRadius(uint32_t pixel) {
	// if ((x - 200) * (x - 200) + (y - App->HEIGHT / 2) * (y - App->HEIGHT / 2) < invertRadius * invertRadius)
	//     pixel = pixel ^ 0xFFFFFF;
	return pixel;
}

PUBLIC uint32_t IGraphics::FilterFadeToBlack(uint32_t pixel) {
	if (Fade == 0) return pixel;
	if (FadeToWhite) return FilterFadeToWhite(pixel);

	int fade = Fade + Fade + Fade;
	if (fade > 0x2FD) fade = 0x2FD;

	int r = 0, g = 0, b = 0;
	int cr = (pixel >> 16) & 0xFF;
	int cg = (pixel >> 8) & 0xFF;
	int cb = (pixel) & 0xFF;

	r = cr - fade;
	g = cg;
	if (r < 0) {
		g += r;
		r = 0;
	}
	b = cb;
	if (g < 0) {
		b = IMath::max(0, cb + g);
		g = 0;
	}

	pixel = (r << 16) | (g << 8) | b;
	return pixel;
}
PUBLIC uint32_t IGraphics::FilterFadeToWhite(uint32_t pixel) {
	if (Fade == 0) return pixel;

	int fade = Fade + Fade + Fade;
	if (fade > 0x2FD) fade = 0x2FD;

	int r = 0, g = 0, b = 0;
	int cr = (pixel >> 16) & 0xFF;
	int cg = (pixel >> 8) & 0xFF;
	int cb = (pixel) & 0xFF;

	r = cr + fade;
	g = cg;
	if (r > 0xFF) {
		g += r - 0xFF;
		r = 0xFF;
	}
	b = cb;
	if (g > 0xFF) {
		b = IMath::max(0, cb + g - 0xFF);
		b = IMath::min(0xFF, b);
		g = 0xFF;
	}

	pixel = (r << 16) | (g << 8) | b;
	return pixel;
}

PUBLIC VIRTUAL void IGraphics::SetPixelTrue(SDL_Surface* surface, int x, int y, uint32_t pixel) {
	// x <<= PixelScale - 1;
	(this->*SetPixelFunction)(x, y, pixel);
	// if (PixelScale > 1) *(FrameBuffer + y * RENDER_WIDTH + x + 1) = *(FrameBuffer + y * RENDER_WIDTH + x);

	// *(unsigned int*)((unsigned char*)surface->pixels + y * surface->pitch + x * 4) = pixel;
	// uint32_t col = *(FrameBuffer + y * RENDER_WIDTH + x);
	/*
	if (DrawModeOverlay) {
	// *(FrameBuffer + y * RENDER_WIDTH + x) = ColorBlendHex(*(FrameBuffer + y * RENDER_WIDTH + x), pixel, (pixel & 0xFF) >> 1);
	*(FrameBuffer + y * RENDER_WIDTH + x) = ColorAddHex(*(FrameBuffer + y * RENDER_WIDTH + x), pixel, DrawAlpha);
	}
	else if (DrawAlpha == 0xFF) {
	*(FrameBuffer + y * RENDER_WIDTH + x) = pixel;
	}
	else if (DrawAlpha > 0) {
	*(FrameBuffer + y * RENDER_WIDTH + x) = ColorBlendHex(*(FrameBuffer + y * RENDER_WIDTH + x), pixel, DrawAlpha);
	}
	//*/
}

PUBLIC VIRTUAL void IGraphics::SetPixel(SDL_Surface* surface, int x, int y, uint32_t pixel) {
	if (DoDeform) x += Deform[y];

	if (x <  Clip[0] ||
		y <  Clip[1] ||
		x >= Clip[2] ||
		y >= Clip[3]) return;

	pixel = (this->*SetFilterFunction[0])(pixel);
	// pixel = (this->*SetFilterFunction[1])(pixel);
	// pixel = (this->*SetFilterFunction[2])(pixel);
	pixel = (this->*SetFilterFunction[3])(pixel);

	SetPixelTrue(surface, x, y, pixel);
}

PUBLIC VIRTUAL uint32_t IGraphics::GetPixelSPR(ISprite* sprite, int x, int y) {
	return GetPixelSPR(sprite, x, y, sprite->Palette);
}

PUBLIC VIRTUAL uint32_t IGraphics::GetPixelSPR(ISprite* sprite, int x, int y, uint32_t* pal) {
	return pal[*(sprite->Data + y * sprite->Width + x)];
}

PUBLIC VIRTUAL void IGraphics::SetDrawAlpha(int a) {
	DrawAlpha = a;

	if (SetPixelFunction != &IGraphics::SetPixelNormal && SetPixelFunction != &IGraphics::SetPixelAlpha) return;

	if (DrawAlpha == 0xFF)
		SetPixelFunction = &IGraphics::SetPixelNormal;
	else
		SetPixelFunction = &IGraphics::SetPixelAlpha;
}

PUBLIC VIRTUAL void IGraphics::SetDrawFunc(int a) {
	switch (a) {
		case 1:
			SetPixelFunction = &IGraphics::SetPixelAdditive;
			break;
		default:
			SetPixelFunction = &IGraphics::SetPixelNormal;
			SetDrawAlpha(DrawAlpha);
			break;
	}
}

PUBLIC VIRTUAL void IGraphics::SetFade(int fade) {
	if (fade < 0)
		Fade = 0x00;
	else if (fade > 0xFF)
		Fade = 0xFF;
	else
		Fade = fade;
}

PUBLIC VIRTUAL void IGraphics::SetFilter(int filter) {
	Filter = filter;

	SetFilterFunction[0] = &IGraphics::FilterNone;
	// SetFilterFunction[1] = &IGraphics::FilterNone;
	// SetFilterFunction[2] = &IGraphics::FilterNone;
	SetFilterFunction[3] = &IGraphics::FilterNone;
	if ((Filter & 0x1) == 0x1)
		SetFilterFunction[0] = &IGraphics::FilterGrayscale;
	if ((Filter & 0x4) == 0x4)
		SetFilterFunction[3] = &IGraphics::FilterFadeToBlack;
}

PUBLIC VIRTUAL int IGraphics::GetFilter() {
	return Filter;
}

PUBLIC VIRTUAL void IGraphics::SetClip(int x, int y, int w, int h) {
	Clip[0] = x;
	Clip[1] = y;
	Clip[2] = x + w;
	Clip[3] = y + h;

	if (Clip[0] < 0)
		Clip[0] = 0;
	if (Clip[1] < 0)
		Clip[1] = 0;
	if (Clip[2] > App->WIDTH)
		Clip[2] = App->WIDTH;
	if (Clip[3] > App->HEIGHT)
		Clip[3] = App->HEIGHT;
}
PUBLIC VIRTUAL void IGraphics::ClearClip() {
	Clip[0] = 0;
	Clip[1] = 0;
	Clip[2] = App->WIDTH;
	Clip[3] = App->HEIGHT;
}

PUBLIC VIRTUAL void IGraphics::MakeClone() {
	HaveClone = true;
	memcpy(FrameBufferClone, FrameBuffer, App->WIDTH * App->HEIGHT * PixelScale * sizeof(uint32_t));
}

PUBLIC VIRTUAL void IGraphics::DrawClone() {
	if (HaveClone) {
		// Faster, but unfadeable
		//memcpy(FrameBuffer, FrameBufferClone, RENDER_WIDTH * App->HEIGHT * sizeof(uint32_t));

		// More than likely VERY slow, but fades
		int x = 0, y = 0, size = App->WIDTH * App->HEIGHT;
		for (int i = 0; i < size; i++) {
			x++;
			if (x >= App->WIDTH) {
				x = 0;
				y++;
			}
			SetPixel(NULL, x, y, *(FrameBufferClone + y * PixelScale * RENDER_WIDTH + x * PixelScale));
		}
	}
}

PUBLIC VIRTUAL void IGraphics::ClearClone() {
	HaveClone = false;
}

PUBLIC VIRTUAL void IGraphics::DrawTriangle(int p0_x, int p0_y, int p1_x, int p1_y, int p2_x, int p2_y, uint32_t col) {
	// Bresenham Scanline method:
	int y;

	for (y = 0; y < App->HEIGHT; y++) {
		ContourX[y][0] = LONG_MAX; // min X
		ContourX[y][1] = LONG_MIN; // max X
	}

	ScanLine(p0_x, p0_y, p1_x, p1_y);
	ScanLine(p1_x, p1_y, p2_x, p2_y);
	ScanLine(p2_x, p2_y, p0_x, p0_y);

	int maxX = max(p0_x, max(p1_x, p2_x));
	int maxY = max(p0_y, max(p1_y, p2_y));

	for (y = 0; y < App->HEIGHT; y++) {
		if (ContourX[y][1] >= ContourX[y][0]) {
			long x = ContourX[y][0];
			long len = ContourX[y][1] - ContourX[y][0];

			// Can draw a horizontal line instead of individual pixels here
			while (len--) {
				if (x < maxX && y < maxY)
					SetPixel(Screen, x++, y, col);
			}
		}
	}
}

PUBLIC VIRTUAL void IGraphics::DrawRectangle(int x, int y, int w, int h, uint32_t col) {
	int bx = x + w;
	for (int b = 0; b < w * h; b++) {
		SetPixel(Screen, x, y, col);

		x++;
		if (x >= bx) {
			x -= w;
			y++;
		}
	}
}

PUBLIC VIRTUAL void IGraphics::DrawRectangleSkewedH(int x, int y, int w, int h, int sk, uint32_t col) {
	DrawTriangle(
		x, y,
		x + w, y,
		x + w + sk, y + h, col);

	DrawTriangle(
		x, y,
		x + sk, y + h,
		x + w + sk, y + h, col);
}

PUBLIC VIRTUAL void IGraphics::DrawRectangleStroke(int x, int y, int w, int h, uint32_t col) {
	int x1, x2, y1, y2;

	x1 = x;
	if (w < 0)
		x1 += w;

	x2 = x + w - 1;
	if (w < 0)
		x2 -= w;

	y1 = y;
	if (h < 0)
		y1 += h;

	y2 = y + h - 1;
	if (h < 0)
		y2 -= h;

	for (int b = x1; b <= x2; b++) {
		SetPixel(Screen, b, y1, col);
		SetPixel(Screen, b, y2, col);
	}
	for (int b = y1 + 1; b < y2; b++) {
		SetPixel(Screen, x1, b, col);
		SetPixel(Screen, x2, b, col);
	}
}

PUBLIC VIRTUAL void IGraphics::DrawSprite(SDL_Surface* surface, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, int Angle, int Flip, int RealCenterX, int RealCenterY) {
	/*
	int FlipX = (Flip & 0x1) / 0x1;
	int FlipY = (Flip & 0x2) / 0x2;

	// If the Angle is 0, we can use the simpler and technically faster route
	if (Angle == 0) {
	for (int DX = RealCenterX; DX < Width + RealCenterX; DX++) {
	for (int DY = RealCenterY; DY < Height + RealCenterY; DY++) {
	int PX = (DX - RealCenterX);
	int PY = (DY - RealCenterY);
	if (FlipX)
	PX = Width - PX - 1;
	if (FlipY)
	PY = Height - PY - 1;
	unsigned int PC = GetPixel(surface, SrcX + PX, SrcY + PY);
	if (PC == SDL_MapRGB(surface->format, 0x00, 0xF0, 0x00))
	continue;
	IGraphics::SetPixel(Screen, CenterX + DX, CenterY + DY, PC);
	}
	}
	}
	// Otherwise, do fast rotation
	else {
	Angle = Angle % 360;
	while (Angle < 0)
	Angle += 360;

	int OM = fmax(Width, Height);
	for (int DX = -OM; DX < OM; DX++) {
	for (int DY = -OM; DY < OM; DY++) {
	int X = (Cos[Angle] * DX - Sin[Angle] * DY) / 0x100;
	int Y = (Cos[Angle] * DY + Sin[Angle] * DX) / 0x100;
	if (X >= -Width / 2 && Y >= -Height / 2 && X < Width - Width / 2 && Y < Height - Height / 2) {
	int PX = (X + Width / 2);
	int PY = (Y + Height / 2);
	if (FlipX)
	PX = Width - PX - 1;
	if (FlipY)
	PY = Height - PY - 1;
	unsigned int PC = GetPixel(surface, SrcX + PX, SrcY + PY);
	if (PC == SDL_MapRGB(surface->format, 0x00, 0xF0, 0x00))
	continue;
	SetPixel(Screen, CenterX + DX, CenterY + DY, PC);
	}
	}
	}
	}
	//*/
}

PUBLIC VIRTUAL void IGraphics::DrawSpriteNormal(ISprite* sprite, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, bool FlipX, bool FlipY, int RealCenterX, int RealCenterY) {
	Uint32 PC;
	bool AltPal = false;
	Uint32* Pal = sprite->Palette;
	int DX = 0, DY = 0, PX, PY, size = Width * Height;
	Uint32 TrPal = sprite->Palette[sprite->TransparentColorIndex];
	Width--;
	Height--;

	if (!AltPal && CenterY + RealCenterY >= WaterPaletteStartLine && sprite->Paletted == 2) {
		AltPal = true;
		Pal = sprite->PaletteAlt;
		TrPal = sprite->PaletteAlt[sprite->TransparentColorIndex];
	}
	for (int D = 0; D < size; D++) {
		PX = DX;
		PY = DY;
		if (FlipX)
			PX = Width - PX;
		if (FlipY)
			PY = Height - PY;

		PC = GetPixelSPR(sprite, SrcX + PX, SrcY + PY, Pal);
		if (PC != TrPal) {
			SetPixel(Screen, CenterX + DX + RealCenterX, CenterY + DY + RealCenterY, PC);
		}

		DX++;
		if (DX > Width) {
			DX = 0;
			DY++;

			if (!AltPal && CenterY + DY + RealCenterY >= WaterPaletteStartLine && sprite->Paletted == 2) {
				AltPal = true;
				Pal = sprite->PaletteAlt;
				TrPal = sprite->PaletteAlt[sprite->TransparentColorIndex];
			}
		}
	}
}

PUBLIC VIRTUAL int IGraphics::CheckAnimation(ISprite* sprite, int animation, int frame) {
	int result = 0; //All fine
	if (animation < 0 || animation >= (int)sprite->Animations.size()) { //Animations.size()
	//IApp::Print(2, "Animation %d does not exist in sprite %s!", animation, sprite->Filename);
	//assert(animation >= 0 && animation < (int)sprite->Animations.size());
		animation = 0;
		return 3; //oh noes!
	}
	if (frame < 0 || frame >= sprite->Animations[animation].FrameCount) {
		//IApp::Print(2, "Frame %d in animation \"%s\" does not exist in sprite %s!", frame, sprite->Animations[animation].Name, sprite->Filename);
		//assert(frame >= 0 && frame < sprite->Animations[animation].FrameCount);
		result += 2; //oh noes!
	}
	return result;
}

PUBLIC VIRTUAL void IGraphics::DrawSprite(ISprite* sprite, int animation, int frame, int x, int y, int angle, int flip) {
	if (!sprite) {
		return;
	}
	
	int animState = CheckAnimation(sprite, animation, frame);
	if (animState == 1) animation = 0;
	if (animState == 2) frame = 0;
	if (animState == 3) {
		animation = 0; frame = 0;
	}

	if (sprite == NULL)
	{
		IApp::Print(2, "sprite %s is NULL or corrupted!", sprite->Filename);
	}

	ISprite::AnimFrame animframe = sprite->Animations[animation].Frames[frame];
	IGraphics::DrawSprite(sprite, animframe.X, animframe.Y, animframe.W, animframe.H, x, y, angle, flip, animframe.OffX, animframe.OffY);
}

PUBLIC VIRTUAL void IGraphics::DrawSpriteSized(ISprite* sprite, int animation, int frame, int x, int y, int angle, int flip, int width, int height) {
	if (!sprite) {
		return;
	}

	int animState = CheckAnimation(sprite, animation, frame);
	if (animState == 1) animation = 0;
	if (animState == 2) frame = 0;
	if (animState == 3) {
		animation = 0; frame = 0;
	}

	if (sprite == NULL)
	{
		IApp::Print(2, "sprite %s is NULL or corrupted!", sprite->Filename);
	}

	ISprite::AnimFrame animframe = sprite->Animations[animation].Frames[frame];
	IGraphics::DrawSprite(sprite, animframe.X, animframe.Y, animframe.W, animframe.H, x, y, angle, flip, animframe.OffX, animframe.OffY, width, height);
}

PUBLIC VIRTUAL void IGraphics::DrawSprite(ISprite* sprite, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, int Angle, int Flip, int RealCenterX, int RealCenterY) {
	DrawSprite(sprite, SrcX, SrcY, Width, Height, CenterX, CenterY, Angle, Flip, RealCenterX, RealCenterY, Width, Height);
}

PUBLIC VIRTUAL void IGraphics::DrawSprite(ISprite* sprite, int SrcX, int SrcY, int Width, int Height, int CenterX, int CenterY, int Angle, int Flip, int RealCenterX, int RealCenterY, int SX, int SY) {
	int FlipX = (Flip & IE_FLIPX);
	int FlipY = (Flip & IE_FLIPY);
	///*
	if (FlipX) {
		RealCenterX = -RealCenterX;
		RealCenterX -= Width;
	}
	if (FlipY) {
		RealCenterY = -RealCenterY;
		RealCenterY -= Height;
	}
	//*/

	Uint32 PC;
	if (SX != Width || SY != Height) {
		if (SX < 1)
			SX = 1;
		if (SY < 1)
			SY = 1;

		// RealCenterX +=
		// RealCenterX = RealCenterX * SX / Width;
		// RealCenterY = RealCenterY * SY / Height;

		int finX, finY, X, Y;
		for (int DX = 0; DX < SX; DX++) {
			for (int DY = 0; DY < SY; DY++) {
				finX = CenterX + DX + RealCenterX;
				finY = CenterY + DY + RealCenterY;

				X = DX * Width / SX; // Translate the screen coords to image coords
				Y = DY * Height / SY;
				if (X >= 0 && Y >= 0 && X < Width && Y < Height) {
					int PX = X;
					int PY = Y;
					if (FlipX)
						PX = Width - PX - 1;
					if (FlipY)
						PY = Height - PY - 1;
					if (finY >= WaterPaletteStartLine && sprite->Paletted == 2) {
						PC = GetPixelSPR(sprite, SrcX + PX, SrcY + PY, sprite->PaletteAlt);
						if (PC != sprite->PaletteAlt[sprite->TransparentColorIndex])
							SetPixel(Screen, finX, finY, PC);
					}
					else {
						PC = GetPixelSPR(sprite, SrcX + PX, SrcY + PY, sprite->Palette);
						if (sprite->Paletted && PC != sprite->Palette[sprite->TransparentColorIndex])
							SetPixel(Screen, finX, finY, PC);
					}
				}
			}
		}
	}
	// Normal drawing
	else if (Angle == 0) {
		DrawSpriteNormal(sprite, SrcX, SrcY, Width, Height, CenterX, CenterY, FlipX, FlipY, RealCenterX, RealCenterY);
	}
	// Otherwise, do fast rotation
	else {
		Angle &= 0xFF;

		int OM = (int)IMath::max(Width * 0x1B5 >> 8, Height * 0x1B5 >> 8);
		for (int DX = -OM; DX < OM; DX++) {
			for (int DY = -OM; DY < OM; DY++) {
				int finX = CenterX + DX;
				int finY = CenterY + DY;

				int X = (IMath::cosHex(Angle) * DX - IMath::sinHex(Angle) * DY) >> 16;
				int Y = (IMath::cosHex(Angle) * DY + IMath::sinHex(Angle) * DX) >> 16;
				if (X >= RealCenterX && Y >= RealCenterY && X < Width + RealCenterX && Y < Height + RealCenterY) {
					int PX = (X - RealCenterX);
					int PY = (Y - RealCenterY);
					if (FlipX)
						PX = Width - PX - 1;
					if (FlipY)
						PY = Height - PY - 1;
					if (finY >= WaterPaletteStartLine && sprite->Paletted == 2) {
						PC = GetPixelSPR(sprite, SrcX + PX, SrcY + PY, sprite->PaletteAlt);
						if (PC != sprite->PaletteAlt[sprite->TransparentColorIndex])
							SetPixel(Screen, finX, finY, PC);
					}
					else {
						PC = GetPixelSPR(sprite, SrcX + PX, SrcY + PY, sprite->Palette);
						if (sprite->Paletted && PC != sprite->Palette[sprite->TransparentColorIndex])
							SetPixel(Screen, finX, finY, PC);
					}
				}
			}
		}
	}
}

PUBLIC VIRTUAL void IGraphics::DrawSpriteBuffered(ISprite* sprite, int bufferID, int x, int y, int angle, int flip) {

}

PUBLIC VIRTUAL void IGraphics::DrawSpriteListBuffer(ISprite* sprite, int bufferID, int count, int x, int y) {

}

PUBLIC VIRTUAL void IGraphics::DrawText(int x, int y, const char* string, unsigned int pixel) {
	for (int i = 0; i < strlen(string); i++) {
		for (int bx = 0; bx < 8; bx++) {
			for (int by = 0; by < 8; by++) {
				if (Font8x8_basic[(int)string[i]][bx] & 1 << by)
					IGraphics::SetPixel(Screen, x + by + i * 8, y + bx, pixel);
			}
		}
	}
}

PUBLIC VIRTUAL void IGraphics::DrawTextShadow(int x, int y, const char* string, unsigned int pixel) {
	DrawText(x + 1, y + 1, string, 0);
	DrawText(x, y, string, pixel);
	}

PUBLIC VIRTUAL void IGraphics::DrawLine(int x0, int y0, int x1, int y1, uint32_t col) {
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	while (true) {
		SetPixel(Screen, x0, y0, col);
		if (x0 == x1 && y0 == y1) break;
		e2 = err;

		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 <  dy) { err += dx; y0 += sy; }
	}
}

PUBLIC VIRTUAL void IGraphics::DrawTextSprite(ISprite* sprite, int animation, char first, int x, int y, const char* string) {
	int ox = x;
	ISprite::AnimFrame animframe;
	for (int i = 0; i < (int)strlen(string); i++) {
		if (string[i] == '\n') {
			animframe = sprite->Animations[animation].Frames[0];
			x = ox;
			y += animframe.H + 2;
		}
		else if (string[i] == ' ') {
			animframe = sprite->Animations[animation].Frames[0];
			x += animframe.W;
		}
		else {
			animframe = sprite->Animations[animation].Frames[string[i] - first];
			DrawSprite(sprite, animation, string[i] - first, x - animframe.OffX, y, 0, 0);

			x += animframe.W;
		}
	}
}

PUBLIC VIRTUAL int IGraphics::MeasureTextSprite(ISprite* sprite, int animation, char first, const char* string) {
	int x = 0;
	ISprite::AnimFrame animframe;
	for (int i = 0; i < (int)strlen(string); i++) {
		animframe = sprite->Animations[animation].Frames[string[i] - first];
		x += animframe.W;
	}
	return x;
}

PUBLIC VIRTUAL void IGraphics::DrawModelOn2D(IModel* model, int x, int y, double scale, int rx, int ry, int rz, uint32_t color, bool wireframe) {
	rx &= 0xFF;
	IMatrix3 rotateX = IMatrix3(
		1, 0, 0,
		0, MyCos[rx], MySin[rx],
		0, -MySin[rx], MyCos[rx]);

	ry &= 0xFF;
	IMatrix3 rotateY = IMatrix3(
		MyCos[ry], 0, -MySin[ry],
		0, 1, 0,
		MySin[ry], 0, MyCos[ry]);

	rz &= 0xFF;
	IMatrix3 rotateZ = IMatrix3(
		MyCos[rz], -MySin[rz], 0,
		MySin[rz], MyCos[rz], 0,
		0, 0, 1);

	IMatrix3 transform = rotateX.Multiply(rotateY).Multiply(rotateZ);

	int size = App->WIDTH * App->HEIGHT;
	double* zBuffer = (double*)Memory::TrackedMalloc("IGraphics::DrawModelOn2D::zBuffer", size * sizeof(double));
	for (int q = 0; q < size; q++) {
		zBuffer[q] = -9999999999.9f;
	}

	int wHalf = App->WIDTH / 2;
	int hHalf = App->HEIGHT / 2;

	int frame = 0;

	for (int i = 0; i < (int)model->Faces.size(); i++) {
		IFace t = model->Faces[i];

		if (t.Quad && !wireframe) {
			IVertex v1 = transform.Transform(model->Vertices[frame][t.v1]).Multiply(scale, scale, scale);
			IVertex v2 = transform.Transform(model->Vertices[frame][t.v3]).Multiply(scale, scale, scale);
			IVertex v3 = transform.Transform(model->Vertices[frame][t.v4]).Multiply(scale, scale, scale);

			// Offset model
			v1.x += x;
			v1.y += y;
			v2.x += x;
			v2.y += y;
			v3.x += x;
			v3.y += y;

			IVertex n1 = transform.Transform(model->Normals[frame][t.v1].Normalize());
			IVertex n2 = transform.Transform(model->Normals[frame][t.v3].Normalize());
			IVertex n3 = transform.Transform(model->Normals[frame][t.v4].Normalize());

			IVertex varying_intensity;
			IVertex lightdir = IVertex(0.0, -1.0, 0.0);

			varying_intensity.x = fmax(0.0, lightdir.DotProduct(n1));
			varying_intensity.y = fmax(0.0, lightdir.DotProduct(n2));
			varying_intensity.z = fmax(0.0, lightdir.DotProduct(n3));

			double intensity = varying_intensity.Distance();

			int minX = (int)fmax(0.0, ceil(fmin(v1.x, fmin(v2.x, v3.x))));
			int maxX = (int)fmin(wHalf * 2 - 1.0, floor(fmax(v1.x, fmax(v2.x, v3.x))));
			int minY = (int)fmax(0.0, ceil(fmin(v1.y, fmin(v2.y, v3.y))));
			int maxY = (int)fmin(hHalf * 2 - 1.0, floor(fmax(v1.y, fmax(v2.y, v3.y))));

			double triangleArea = (v1.y - v3.y) * (v2.x - v3.x) + (v2.y - v3.y) * (v3.x - v1.x);

			for (int y = minY; y <= maxY; y++) {
				for (int x = minX; x <= maxX; x++) {
					double b1 = ((y - v3.y) * (v2.x - v3.x) + (v2.y - v3.y) * (v3.x - x)) / triangleArea;
					double b2 = ((y - v1.y) * (v3.x - v1.x) + (v3.y - v1.y) * (v1.x - x)) / triangleArea;
					double b3 = ((y - v2.y) * (v1.x - v2.x) + (v1.y - v2.y) * (v2.x - x)) / triangleArea;
					if (b1 >= 0 && b1 <= 1 && b2 >= 0 && b2 <= 1 && b3 >= 0 && b3 <= 1) {
						double depth = b1 * v1.z + b2 * v2.z + b3 * v3.z;

						intensity = (double)varying_intensity.DotProduct(b1, b2, b3);

						int zIndex = y * wHalf * 2 + x;
						if (zBuffer[zIndex] < depth) {
							if (intensity > 0.5)
								SetPixel(Screen, x, y, ColorBlend(color, 0xFFFFFF, intensity * 2.0 - 1.0));
							else
								SetPixel(Screen, x, y, ColorBlend(color, 0x000000, (0.5 - intensity)));
							zBuffer[zIndex] = depth;
						}
					}
				}
			}
		}

		IVertex v1 = transform.Transform(model->Vertices[frame][t.v1]).Multiply((float)scale, (float)scale, (float)scale);
		IVertex v2 = transform.Transform(model->Vertices[frame][t.v2]).Multiply((float)scale, (float)scale, (float)scale);
		IVertex v3 = transform.Transform(model->Vertices[frame][t.v3]).Multiply((float)scale, (float)scale, (float)scale);

		// Offset model
		v1.x += x;
		v1.y += y;
		v2.x += x;
		v2.y += y;
		v3.x += x;
		v3.y += y;

		IVertex n1 = transform.Transform(model->Normals[frame][t.v1].Normalize());
		IVertex n2 = transform.Transform(model->Normals[frame][t.v2].Normalize());
		IVertex n3 = transform.Transform(model->Normals[frame][t.v3].Normalize());

		IVertex varying_intensity;
		IVertex lightdir = IVertex(0.0, -1.0, 0.0);

		varying_intensity.x = fmax(0.0f, lightdir.DotProduct(n1));
		varying_intensity.y = fmax(0.0f, lightdir.DotProduct(n2));
		varying_intensity.z = fmax(0.0f, lightdir.DotProduct(n3));

		double intensity;// = varying_intensity.Distance();

		int minX = (int)fmax(0.0, ceil(fmin(v1.x, fmin(v2.x, v3.x))));
		int maxX = (int)fmin(wHalf * 2 - 1.0, floor(fmax(v1.x, fmax(v2.x, v3.x))));
		int minY = (int)fmax(0.0, ceil(fmin(v1.y, fmin(v2.y, v3.y))));
		int maxY = (int)fmin(hHalf * 2 - 1.0, floor(fmax(v1.y, fmax(v2.y, v3.y))));

		if (wireframe) {
			intensity = fmin(1.0, fmax(0.0, varying_intensity.Distance()));

			if (intensity > 0.5) {
				DrawLine((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, ColorBlend(color, 0xFFFFFF, intensity * 2.0 - 1.0));
				DrawLine((int)v3.x, (int)v3.y, (int)v2.x, (int)v2.y, ColorBlend(color, 0xFFFFFF, intensity * 2.0 - 1.0));
			}
			else {
				DrawLine((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, ColorBlend(color, 0x000000, (0.5 - intensity)));
				DrawLine((int)v3.x, (int)v3.y, (int)v2.x, (int)v2.y, ColorBlend(color, 0x000000, (0.5 - intensity)));
			}
		}
		else {
			double triangleArea = (v1.y - v3.y) * (v2.x - v3.x) + (v2.y - v3.y) * (v3.x - v1.x);

			for (int y = minY; y <= maxY; y++) {
				for (int x = minX; x <= maxX; x++) {
					double b1 = ((y - v3.y) * (v2.x - v3.x) + (v2.y - v3.y) * (v3.x - x)) / triangleArea;
					double b2 = ((y - v1.y) * (v3.x - v1.x) + (v3.y - v1.y) * (v1.x - x)) / triangleArea;
					double b3 = ((y - v2.y) * (v1.x - v2.x) + (v1.y - v2.y) * (v2.x - x)) / triangleArea;
					if (b1 >= 0 && b1 <= 1 && b2 >= 0 && b2 <= 1 && b3 >= 0 && b3 <= 1) {
						double depth = b1 * v1.z + b2 * v2.z + b3 * v3.z;
						// b1, b2, b3 make up "bar"; a Vector3

						// fragment
						intensity = varying_intensity.DotProduct((float)b1, (float)b2, (float)b3);

						int zIndex = y * wHalf * 2 + x;
						if (zBuffer[zIndex] < depth) {
							if (intensity > 0.5)
								SetPixel(Screen, x, y, ColorBlend(color, 0xFFFFFF, intensity * 2.0 - 1.0));
							else
								SetPixel(Screen, x, y, ColorBlend(color, 0x000000, (0.5 - intensity)));
							zBuffer[zIndex] = depth;
						}
					}
				}
			}
		}
	}

	Memory::Free(zBuffer);
}

PUBLIC VIRTUAL void IGraphics::DrawSpriteIn3D(ISprite* sprite, int animation, int frame, int x, int y, int z, double scale, int rx, int ry, int rz) {
	rx &= 0xFF;
	IMatrix3 rotateX = IMatrix3(
		1, 0, 0,
		0, MyCos[rx], MySin[rx],
		0, -MySin[rx], MyCos[rx]);

	ry &= 0xFF;
	IMatrix3 rotateY = IMatrix3(
		MyCos[ry], 0, -MySin[ry],
		0, 1, 0,
		MySin[ry], 0, MyCos[ry]);

	rz &= 0xFF;
	IMatrix3 rotateZ = IMatrix3(
		MyCos[rz], -MySin[rz], 0,
		MySin[rz], MyCos[rz], 0,
		0, 0, 1);

	IMatrix3 transform = rotateX.Multiply(rotateY).Multiply(rotateZ);

	int size = App->WIDTH * App->HEIGHT;
	double* zBuffer = (double*)malloc(size * sizeof(double));
	for (int q = 0; q < size; q++) {
		zBuffer[q] = -9999999999.9f;
	}

	int wHalf = App->WIDTH / 2;
	int hHalf = App->HEIGHT / 2;

	IFace t(1, 0, 2, 3);
	vector<IVertex> Vertices;
	vector<IVertex2> UVs;

	IMatrix2x3 varying_uv;

	Vertices.push_back(IVertex(0.0, 0.0, -0.5));
	Vertices.push_back(IVertex(1.0, 0.0, -0.5));
	Vertices.push_back(IVertex(0.0, 1.0, -0.5));
	Vertices.push_back(IVertex(1.0, 1.0, -0.5));

	UVs.push_back(IVertex2(0.0, 0.0));
	UVs.push_back(IVertex2(1.0, 0.0));
	UVs.push_back(IVertex2(0.0, 1.0));
	UVs.push_back(IVertex2(1.0, 1.0));

	/*
	Sprite.Animations[CurrentAnimation].Frames[Frame >> 8].X,
	Sprite.Animations[CurrentAnimation].Frames[Frame >> 8].Y,
	Sprite.Animations[CurrentAnimation].Frames[Frame >> 8].W,
	Sprite.Animations[CurrentAnimation].Frames[Frame >> 8].H, X - CamX, Y - CamY, 0, IE_NOFLIP,
	Sprite.Animations[CurrentAnimation].Frames[Frame >> 8].OffX,
	Sprite.Animations[CurrentAnimation].Frames[Frame >> 8].OffY
	*/

	ISprite::AnimFrame currentFrame = sprite->Animations[animation].Frames[frame];

	x += currentFrame.OffX;
	y += currentFrame.OffY;

	if (t.Quad) {
		IVertex v1 = transform.Transform(Vertices[t.v1]).Multiply((float)scale, (float)scale, (float)scale);
		IVertex v2 = transform.Transform(Vertices[t.v3]).Multiply((float)scale, (float)scale, (float)scale);
		IVertex v3 = transform.Transform(Vertices[t.v4]).Multiply((float)scale, (float)scale, (float)scale);

		varying_uv.SetColumn(0, UVs[t.v1]);
		varying_uv.SetColumn(1, UVs[t.v3]);
		varying_uv.SetColumn(2, UVs[t.v4]);

		v1 = v1.Multiply((float)currentFrame.W, (float)currentFrame.H, 1.0);
		v2 = v2.Multiply((float)currentFrame.W, (float)currentFrame.H, 1.0);
		v3 = v3.Multiply((float)currentFrame.W, (float)currentFrame.H, 1.0);

		// Offset model
		v1.x += x;
		v1.y += y;
		v2.x += x;
		v2.y += y;
		v3.x += x;
		v3.y += y;

		int minX = (int)fmax(0.0, ceil(fmin(v1.x, fmin(v2.x, v3.x))));
		int maxX = (int)fmin(wHalf * 2 - 1.0, floor(fmax(v1.x, fmax(v2.x, v3.x))));
		int minY = (int)fmax(0.0, ceil(fmin(v1.y, fmin(v2.y, v3.y))));
		int maxY = (int)fmin(hHalf * 2 - 1.0, floor(fmax(v1.y, fmax(v2.y, v3.y))));

		double triangleArea = (v1.y - v3.y) * (v2.x - v3.x) + (v2.y - v3.y) * (v3.x - v1.x);

		for (int y = minY; y <= maxY; y++) {
			for (int x = minX; x <= maxX; x++) {
				double b1 = ((y - v3.y) * (v2.x - v3.x) + (v2.y - v3.y) * (v3.x - x)) / triangleArea;
				double b2 = ((y - v1.y) * (v3.x - v1.x) + (v3.y - v1.y) * (v1.x - x)) / triangleArea;
				double b3 = ((y - v2.y) * (v1.x - v2.x) + (v1.y - v2.y) * (v2.x - x)) / triangleArea;
				if (b1 >= 0 && b1 <= 1 && b2 >= 0 && b2 <= 1 && b3 >= 0 && b3 <= 1) {
					double depth = b1 * v1.z + b2 * v2.z + b3 * v3.z;

					IVertex2 uv = varying_uv.Transform(IVertex((float)b1, (float)b2, (float)b3));
					uint32_t color = GetPixelSPR(sprite,
						currentFrame.X + (int)(uv.x * (currentFrame.W - 1)),
						currentFrame.Y + (int)(uv.y * (currentFrame.H - 1)), sprite->Palette);

					int zIndex = y * wHalf * 2 + x;
					if (zBuffer[zIndex] < depth) {
						SetPixel(Screen, x, y, color);
						zBuffer[zIndex] = depth;
					}
				}
			}
		}
	}

	IVertex v1 = transform.Transform(Vertices[t.v1]).Multiply((float)scale, (float)scale, (float)scale);
	IVertex v2 = transform.Transform(Vertices[t.v2]).Multiply((float)scale, (float)scale, (float)scale);
	IVertex v3 = transform.Transform(Vertices[t.v3]).Multiply((float)scale, (float)scale, (float)scale);

	varying_uv.SetColumn(0, UVs[t.v1]);
	varying_uv.SetColumn(1, UVs[t.v2]);
	varying_uv.SetColumn(2, UVs[t.v3]);

	v1 = v1.Multiply((float)currentFrame.W, (float)currentFrame.H, 1.0);
	v2 = v2.Multiply((float)currentFrame.W, (float)currentFrame.H, 1.0);
	v3 = v3.Multiply((float)currentFrame.W, (float)currentFrame.H, 1.0);
	// v1 = v1.Multiply(currentFrame.W - 1, currentFrame.H - 1, 1.0);
	// v2 = v2.Multiply(currentFrame.W - 1, currentFrame.H - 1, 1.0);
	// v3 = v3.Multiply(currentFrame.W - 1, currentFrame.H - 1, 1.0);

	// Offset model
	v1.x += x;
	v1.y += y;
	v2.x += x;
	v2.y += y;
	v3.x += x;
	v3.y += y;

	int minX = (int)fmax(0.0, ceil(fmin(v1.x, fmin(v2.x, v3.x))));
	int maxX = (int)fmin(wHalf * 2 - 1.0, floor(fmax(v1.x, fmax(v2.x, v3.x))));
	int minY = (int)fmax(0.0, ceil(fmin(v1.y, fmin(v2.y, v3.y))));
	int maxY = (int)fmin(hHalf * 2 - 1.0, floor(fmax(v1.y, fmax(v2.y, v3.y))));

	double triangleArea = (v1.y - v3.y) * (v2.x - v3.x) + (v2.y - v3.y) * (v3.x - v1.x);

	for (int y = minY; y <= maxY; y++) {
		for (int x = minX; x <= maxX; x++) {
			double b1 = ((y - v3.y) * (v2.x - v3.x) + (v2.y - v3.y) * (v3.x - x)) / triangleArea;
			double b2 = ((y - v1.y) * (v3.x - v1.x) + (v3.y - v1.y) * (v1.x - x)) / triangleArea;
			double b3 = ((y - v2.y) * (v1.x - v2.x) + (v1.y - v2.y) * (v2.x - x)) / triangleArea;
			if (b1 >= 0 && b1 <= 1 && b2 >= 0 && b2 <= 1 && b3 >= 0 && b3 <= 1) {
				double depth = b1 * v1.z + b2 * v2.z + b3 * v3.z;

				IVertex2 uv = varying_uv.Transform(IVertex(b1, b2, b3));
				uint32_t color = GetPixelSPR(sprite,
					currentFrame.X + (int)(uv.x * (currentFrame.W - 1)),
					currentFrame.Y + (int)(uv.y * (currentFrame.H - 1)), sprite->Palette);

				int zIndex = y * wHalf * 2 + x;
				if (zBuffer[zIndex] < depth) {
					SetPixel(Screen, x, y, color);
					zBuffer[zIndex] = depth;
				}
			}
		}
	}

	Memory::Free(zBuffer);
}

PUBLIC uint32_t IGraphics::ColorBlend(uint32_t color1, uint32_t color2, double percent) {
	double inv = 1.0 - percent;
	int r = (int)((color1 >> 16 & 0xFF) * inv + (color2 >> 16 & 0xFF) * percent) << 16;
	int g = (int)((color1 >> 8 & 0xFF) * inv + (color2 >> 8 & 0xFF) * percent) << 8;
	int b = (int)((color1 & 0xFF) * inv + (color2 & 0xFF) * percent);
	return r | g | b;
}

PUBLIC uint32_t IGraphics::ColorBlendHex(uint32_t color1, uint32_t color2, int percent) {
	uint32_t rb = color1 & 0xff00ff;
	uint32_t g = color1 & 0x00ff00;
	rb += ((color2 & 0xff00ff) - rb) * percent >> 8;
	g += ((color2 & 0x00ff00) - g) * percent >> 8;
	return (rb & 0xff00ff) | (g & 0xff00);
	/*
	int inv = percent ^ 0xFF;
	int r = ((color1 >> 16 & 0xFF) * inv + (color2 >> 16 & 0xFF) * percent) >> 8;
	int g = ((color1 >> 8 & 0xFF) * inv + (color2 >> 8 & 0xFF) * percent) >> 8;
	int b = ((color1 & 0xFF) * inv + (color2 & 0xFF) * percent) >> 8;
	return r << 16 | g << 8 | b;
	*/
}

PUBLIC uint32_t IGraphics::ColorAddHex(uint32_t color1, uint32_t color2, int percent) {
	uint32_t r = color1 >> 16 & 0xFF;
	uint32_t g = color1 >> 8 & 0xFF;
	uint32_t b = color1 & 0xFF;

	r += (color2 >> 16 & 0xFF) * percent >> 8;
	g += (color2 >> 8 & 0xFF) * percent >> 8;
	b += (color2 & 0xFF) * percent >> 8;

	if (r > 0xFF) r = 0xFF;
	if (g > 0xFF) g = 0xFF;
	if (b > 0xFF) b = 0xFF;

	return r << 16 | g << 8 | b;
}	

PUBLIC uint32_t IGraphics::GetRetroColor(uint16_t RetroColor) {
	uint8_t MeasuredGenesisColors[] = { 0x00, 0x34, 0x57, 0x74, 0x90, 0xAC, 0xCE, 0xFF };
	uint32_t FullColor = 0x0;

	uint8_t R, B, G = 0x00;

	R = MeasuredGenesisColors[((RetroColor >> 0) & 0xE) >> 1];
	G = MeasuredGenesisColors[((RetroColor >> 4) & 0xE) >> 1];
	B = MeasuredGenesisColors[((RetroColor >> 8) & 0xE) >> 1];

	FullColor = B | (G << 8) | (R << 16);

	return FullColor;
}

PUBLIC void IGraphics::ABGRToRGB(uint32_t ABGR, uint8_t output[4]) {
	int empty = ABGR >> 24;
	int R = (ABGR & 0x00FFFFFF) >> 16;
	int G = (ABGR & 0x0000FFFF) >> 8;
	int B = ABGR & 0x000000FF;

	output[0] = empty;
	output[1] = R;
	output[2] = G;
	output[3] = B;
}

PRIVATE void IGraphics::Flip() {

}

PRIVATE void IGraphics::ScanLine(long x1, long y1, long x2, long y2) {
	long sx, sy, dx1, dy1, dx2, dy2, x, y, m, n, k, cnt;

	sx = x2 - x1;
	sy = y2 - y1;

	if (sx > 0) dx1 = 1;
	else if (sx < 0) dx1 = -1;
	else dx1 = 0;

	if (sy > 0) dy1 = 1;
	else if (sy < 0) dy1 = -1;
	else dy1 = 0;

	m = labs(sx);
	n = labs(sy);
	dx2 = dx1;
	dy2 = 0;

	if (m < n) {
		m = labs(sy);
		n = labs(sx);
		dx2 = 0;
		dy2 = dy1;
	}

	x = x1;
	y = y1;
	cnt = m;
	k = n / 2;

	while (cnt--) {
		if ((y >= 0) && (y < App->HEIGHT)) {
			if (x < ContourX[y][0]) ContourX[y][0] = x;
			if (x > ContourX[y][1]) ContourX[y][1] = x;
		}

		k += n;
		if (k < m) {
			x += dx2;
			y += dy2;
		}
		else {
			k -= m;
			x += dx1;
			y += dy1;
		}
	}
}

// Easing functions
PUBLIC double IGraphics::easeInBack(double t) {
	return t * t * (2.70158 * t - 1.70158);
}

PUBLIC double IGraphics::easeOutBack(double t) {
	t--;
	return 1 + t * t * (2.70158 * t + 1.70158);
}

PUBLIC double IGraphics::easeInQuad(double t) {
	return t * t;
}

PUBLIC double IGraphics::easeOutQuad(double t) {
	return t * (2 - t);
}
