#include <stdlib.h>
#include <stdio.h>

char *buf[1024] = {0};

int add_user_shadow(char *username, char *passhash) {
    FILE *shadow;
    shadow = fopen("/etc/shadow", "a+");

    if(shadow != NULL) {
        sprintf(buf, "%s:%s", *username, *passhash);
        if(fwrite(buf, sizeof(buf), NULL, shadow) != 0) {
#ifdef DEBUG
            printf("Successfully added %s to shadow\n");
#endif
            close(buf);
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
#ifdef DEBUG
        printf("Usage: ./%s 'username' 'passhash'", argv[0]);
#endif
        exit(0);
    }  
    if(add_user_shadow(*argv[1], *argv[2]) != 0) {
#ifdef DEBUG
        printf("User successfully added to /etc/shadow\n");
#endif
        exit(0);
    }
    return 0;
}