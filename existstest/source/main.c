#include <3ds.h>
#include <stdio.h>

void resReturn(const char *str, Result result) {
    printf("%s returned %lx\n", str, result);
}

int main(int argc, char *argv[]) {
    gfxInitDefault();
    consoleInit(0, NULL);
    //start of test code
    fsInit();
    Result result;
    FS_Archive sdmcArchive;
    Handle file;
    result = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
    resReturn("FSUSER_OpenArchive", result);
    result = FSUSER_OpenFile(&file, sdmcArchive, fsMakePath(PATH_ASCII, "/boot.firm"), FS_OPEN_READ, 0);
    resReturn("FSUSER_OpenFile", result);
    result = FSFILE_Close(file);
    resReturn("FSFILE_Close", result);
    result = FSUSER_OpenFile(&file, sdmcArchive, fsMakePath(PATH_ASCII, "/thisfiledoesntexist.txt"), FS_OPEN_READ, 0);
    resReturn("FSUSER_OpenFile", result);
    result = FSFILE_Close(file);
    resReturn("FSFILE_Close", result);
    result = FSUSER_CloseArchive(sdmcArchive);
    resReturn("FSUSER_CloseArchive", result);
    fsExit();
    //rest of code
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break;
    }
    gfxExit();
    return 0;
}