#if INTERFACE
#include <Engine/IResource.h>

class IResources {
public:

};
#endif

#include <Engine/IApp.h>
#include <Engine/IResources.h>

PUBLIC STATIC IResource* IResources::Load(const char* path) {
    return IResources::Load(path, false);
}

PUBLIC STATIC IResource* IResources::Load(const char* path, bool inMemory) {
    char FullName[256];
    sprintf(FullName, "%s%s", IFILE(""), path);

    IResource* res = new IResource();
    res->ZipLoading = false;
    res->RW = NULL;

    if (res->ZipLoading) { // zip loading
        #if 0
		const char* zipfilename = IFILE("../Resources.zip");

        #ifdef USEWIN32IOAPI
			fill_win32_filefunc64A(&ffunc);
			res->uf = unzOpen2_64(zipfilename,&ffunc);
		#else
			res->uf = unzOpen64(zipfilename);
		#endif

		if (res->uf == NULL) {
            zipfilename = "Resources.zip";
            #ifdef USEWIN32IOAPI
    			fill_win32_filefunc64A(&ffunc);
    			res->uf = unzOpen2_64(zipfilename, &ffunc);
    		#else
    			res->uf = unzOpen64(zipfilename);
    		#endif

            if (res->uf == NULL) {
                IApp::Print(2, "Resources.zip not found!");
                return NULL;
            }
		}

        if (unzLocateFile(res->uf, path, 1) != UNZ_OK) {
            IApp::Print(2, "'%s' was not found in Resources.zip!", path);
            return NULL;
        }

        if (unzOpenCurrentFile(res->uf) != UNZ_OK) {
            IApp::Print(2, "Could not open '%s'!", path);
            return NULL;
        }


        char filename_inzip[256];
        if (unzGetCurrentFileInfo64(res->uf, &res->info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0) != UNZ_OK) {
            IApp::Print(2, "Could not get information on '%s'!", path);
            return NULL;
        }

        if (inMemory) {
            int err = 0;
            size_t offset = 0;
            uint8_t* buffer = (uint8_t*)malloc(0x4000);
            res->Buffer = (uint8_t*)malloc((size_t)res->info.uncompressed_size);
            do {
                err = unzReadCurrentFile(res->uf, buffer, 0x4000);
                if (err < 0) {
                    IApp::Print(2, "Error while reading '%s'! (Error Code: %d)", path, err);
                    break;
                }
                if (err == 0)
                    break;
                memcpy(res->Buffer + offset, buffer, err);
                offset += err;
            }
            while (err > 0);

            free(buffer);

            res->RW = SDL_RWFromMem(res->Buffer, (size_t)res->info.uncompressed_size);

            res->ZipLoading = false;
        }
        #endif
    } else {
        res->RW = SDL_RWFromFile(FullName, "rb");
        if (!res->RW) {
			IApp::Print(2, "%s", SDL_GetError());
            return NULL;
        }
    }
    res->path = path;

    return res;
}
PUBLIC STATIC IResource* IResources::Open(const char* path) {
	char FullName[256];
	sprintf(FullName, "%s%s", IFILE(""), path);

	IResource* res = new IResource();
	res->ZipLoading = false;
	res->RW = SDL_RWFromFile(FullName, "wb");
	if (!res->RW) {
		return NULL;
	}
	res->path = path;

	return res;
}

PUBLIC STATIC bool IResources::Close(IResource* res) {
    if (res == NULL) {
        IApp::Print(2, "Resource error.");
        return false;
    }
    if (!res->ZipLoading) {
        if (res->RW == NULL) {
            IApp::Print(2, "Resource \"%s\" does not exist.\n", res->path);
            return false;
        }
        SDL_RWclose(res->RW);
        res->RW = NULL;
    }
    if (res->Buffer) {
        free(res->Buffer);
        res->Buffer = NULL;
    }
    delete res;
    return true;
}

PUBLIC STATIC uint64_t IResources::Decompress(void* dst, int dstLen, const void* src, int srcLen) {
    z_stream strm  = {0};
    strm.total_in  = strm.avail_in  = srcLen;
    strm.total_out = strm.avail_out = dstLen;
    strm.next_in   = (Bytef *) src;
    strm.next_out  = (Bytef *) dst;

    strm.zalloc = Z_NULL;
    strm.zfree  = Z_NULL;
    strm.opaque = Z_NULL;

    int err = -1;
    unsigned long ret = -1;

    err = inflateInit2(&strm, (15 + 32)); //15 window bits, and the +32 tells zlib to to detect if using gzip or zlib
    if (err == Z_OK) {
        err = inflate(&strm, Z_FINISH);
        if (err == Z_STREAM_END) {
            ret = strm.total_out;
        }
        else {
             inflateEnd(&strm);
             return err;
        }
    }
    else {
        inflateEnd(&strm);
        return err;
    }

    inflateEnd(&strm);
    return ret;
}
