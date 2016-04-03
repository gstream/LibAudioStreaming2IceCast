//
//  liblame.c
//  libaudiostream
//
//  Created by User on 2/5/16.
//  Copyright (c) 2016 User. All rights reserved.
//

#include "liblame.h"
#include <string.h>
#include <stdlib.h>
#include "lame.h"

static lame_global_flags *glf = NULL;

void Lame_init(int inSamplerate, int outChannel,
               int outSamplerate, int outBitrate, int quality) {
    if (glf != NULL) {
        lame_close(glf);
        glf = NULL;
    }
    glf = lame_init();
    lame_set_in_samplerate(glf, inSamplerate);
    lame_set_num_channels(glf, outChannel);
    lame_set_out_samplerate(glf, outSamplerate);
    lame_set_brate(glf, outBitrate);
    lame_set_quality(glf, quality);
    lame_init_params(glf);
}

int Lame_encode(const short int* buffer_l, const short int* buffer_r, const int samples, unsigned char* mp3buf, int mp3buf_size) {
    int result = lame_encode_buffer(glf, buffer_l, buffer_r, samples, mp3buf, mp3buf_size);
    
    return result;
}

int Lame_flush(unsigned char* mp3buf, int mp3buf_size) {
    int result = lame_encode_flush(glf, mp3buf, mp3buf_size);
    
    return result;
}

void Lame_close() {
    lame_close(glf);
    glf = NULL;
}