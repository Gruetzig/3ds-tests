#include <3ds.h>
#include <stdio.h>

void resReturn(const char *str, Result result) {
    printf("%s returned %lx\n", str, result);
}

int main(int argc, char *argv[]) {
    gfxInitDefault();
    consoleInit(0, NULL);
    //start of test code
    FS_Archive twlnArchive;
    FS_DirectoryEntry entry;
    u32 entriesRead = 1;
    Result res;
    fsInit();
    u8 buf[16];
    res = FSUSER_OpenArchive(&twlnArchive, ARCHIVE_NAND_TWL_FS, fsMakePath(PATH_EMPTY, ""));
    resReturn("FSUSER_OpenArchive", res);
    Handle dir;
    res = FSUSER_OpenDirectory(&dir, twlnArchive, fsMakePath(PATH_ASCII, "/"));
    resReturn("FSUSER_OpenDirectory", res);  
    while (entriesRead) {
        res = FSDIR_Read(dir, &entriesRead, 1, &entry);
        utf16_to_utf8(buf, entry.name, 16);
        resReturn("FSDIR_Read", res);
        printf("%s\n", buf);
    }
    res = FSDIR_Close(dir);
    resReturn("FSDIR_Close", res);
    res = FSUSER_CloseArchive(twlnArchive);
    resReturn("FSUSER_CloseArchive", res);
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