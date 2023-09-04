#include <3ds.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    gfxInitDefault();
    consoleInit(0, NULL);
    int count;

    printf("This program was called with \"%s\".\n", argv[0]);

    if (argc > 1) {
        for (count = 1; count < argc; count++) {
	        printf("argv[%d] = %s\n", count, argv[count]);
	    }
    } else {
        printf("The command had no other arguments.\n");
    }
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break;
    }
    gfxExit();
}