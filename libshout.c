//
//  libshout.c
//  libaudiostream
//
//  Created by User on 2/5/16.
//  Copyright (c) 2016 User. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shout.h"
#include <pthread.h>

#include "libshout.h"
#include "shout.h"



void close_shout();

shout_t *shout = NULL;

void close_shout() {
    if (shout != NULL) {
        shout_close(shout);
        shout_free(shout);
        shout_shutdown();
    }
}

int init_icecast(unsigned char *urlservercastA,int puertocast,unsigned char *montajecastA,unsigned char *usuariocastA,unsigned char *passwdcastA,int IsMp3Ogg) {
    
    shout_init();
    printf ("init_icecast\n");
    if (!(shout = shout_new())) {
        return -1;
    }
    printf ("shout_set_host\n");
    if (shout_set_host(shout,urlservercastA) != SHOUTERR_SUCCESS) {
        return -1;
    }
    printf("shout_set_protocol\n");
    if (shout_set_protocol(shout, SHOUT_PROTOCOL_HTTP) != SHOUTERR_SUCCESS) {
        return -1;
    }
    printf ("shout_set_port\n");
    if (shout_set_port(shout,puertocast) != SHOUTERR_SUCCESS) {
        return -1;
    }
    printf("shout_set_password\n");
    if (shout_set_password(shout,passwdcastA) != SHOUTERR_SUCCESS) {
        return -1;
    }
    printf("shout_set_mount\n");
    if (shout_set_mount(shout,montajecastA) != SHOUTERR_SUCCESS) {
        return -1;
    }
    printf("snhout_set_user\n");
    if (shout_set_user(shout,usuariocastA) != SHOUTERR_SUCCESS) {
        return -1;
    }
    printf("snhout_set_format\n");
    if (shout_set_format(shout, IsMp3Ogg) != SHOUTERR_SUCCESS) {
        return -1;
    }
    printf("shout_Set_format_mp3\n");
    if (shout_set_format(shout, SHOUT_FORMAT_MP3) != SHOUTERR_SUCCESS) {
     return -1;
    }
    printf("shout_open\n");
    if (shout_open(shout) == SHOUTERR_SUCCESS) {
        printf("shout_open_success\n");
        return 1;
    } else {
        printf("shout_open_failed\n");
        return -1;
    }
}

int ShoutOutputStream_Send(unsigned char *pBuffer, int lengthOfArray) {
    if (shout_send(shout, (char *)pBuffer, (int) lengthOfArray) != SHOUTERR_SUCCESS) {
        return -1;
    }
    shout_sync(shout);
    return 1;
}

int ShoutOutputStream_Init(unsigned char *urlservercast,int puertocast,unsigned char *montajecast,unsigned char * usuariocast,unsigned char *passwdcast, int IsMp3Ogg) {
    return init_icecast((unsigned char*)urlservercast,puertocast, (unsigned char*)montajecast, (unsigned char*)usuariocast, (unsigned char*)passwdcast, IsMp3Ogg);
}

int ShoutOutputStream_Close() {
    close_shout();
    return 1;
}





