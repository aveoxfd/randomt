#include "header/hdrand.h"
//#include <time.h>

#define RANDOM_VAL (\
        ((__rndsetting & __RANDOM_METHOD) == RDRAND_METHOD) ? __get_hardrand_rdrand() : ((__rndsetting & __RANDOM_METHOD) == RDSEED_METHOD)\
        ? __get_hardrand_rdseed() : __get_hardrand_rdrand()\
    )

#define DEFAULT_SEED_UPDATE RDRAND_METHOD
//============================================================================================================================================

RND_API void update_seed(rndseed *_sd, const RNDSTNG __rndsetting){ //s -> void -> memory
    int i = 0;

    for (; i<_sd->seed_size; i++){
        ((uint8*)_sd->seed)[i] = 0;
    }
    ((uint8*)_sd->seed)[--i] = 1;

    uint32 n = 0;
    while (n == 0){
        n = (uint32)RANDOM_VAL % 10;
    }
    for (i = 0; i<n; i++){
        for (int j = 0; j<_sd->seed_size; j++){
            uint8 rand_byte = RANDOM_VAL;
            ((uint8*)_sd->seed)[j] ^= rand_byte; //(((uint8)time(NULL)>>j*8) & 0xFF);
        }
    }
    //seed->seed +=__get_hardrand_rdrand()*time(0);
    return;
}

RND_API DEFAULT_MODE random(rndseed *_sd, const RNDSTNG __rndsetting){
    int sum = 0;
    for (int i = 0; i<_sd->seed_size; i++){
        sum += ((uint8*)_sd->seed)[i];
    }
    if (sum == 0){
        update_seed(_sd, DEFAULT_SEED_UPDATE);
    }

    DEFAULT_MODE out = 0;
    for (int i = 0; i<sizeof(DEFAULT_MODE); i++){
        out <<= 8;
        DEFAULT_MODE temp = 0;
        for (int j = 0; j<_sd->seed_size; j++){
            temp += ((uint8*)_sd->seed)[j];
        }
        if (temp == 0){
            temp = (DEFAULT_MODE)RANDOM_VAL + 1;
        }
        out |= (uint8)((uint64)RANDOM_VAL * temp + (uint64)RANDOM_VAL + temp) & 0xff;
    }

    out %= (uint64)RANDOM_VAL + 1;

    if((__rndsetting & __AUTO_UPDATE_SEED) == SET_AUTO_UPDATE_SEED){
        update_seed(_sd, DEFAULT_SEED_UPDATE);
    }
    return (DEFAULT_MODE)out;
}
RND_API uint32 random32(rndseed *_sd, const RNDSTNG __rndsetting){
    int sum = 0;
    for (int i = 0; i<_sd->seed_size; i++){
        sum += ((uint8*)_sd->seed)[i];
    }
    if (sum == 0){
        update_seed(_sd, DEFAULT_SEED_UPDATE);
    }

    uint32 out = 0;
    for (int i = 0; i<sizeof(uint32); i++){
        out <<= 8;
        uint32 temp = 0;
        for (int j = 0; j<_sd->seed_size; j++){
            temp += ((uint8*)_sd->seed)[j];
        }
        if (temp == 0){
            temp = (uint32)RANDOM_VAL + 1;
        }
        out |= (uint8)((uint64)RANDOM_VAL * temp + (uint64)RANDOM_VAL + temp) & 0xff;
    }

    out %= (uint32)RANDOM_VAL + 1;

    if((__rndsetting & __AUTO_UPDATE_SEED) == SET_AUTO_UPDATE_SEED){
        update_seed(_sd, RDSEED_METHOD);
    }
    return out;
}

RND_API uint64 random64(rndseed *_sd, const RNDSTNG __rndsetting){
    int sum = 0;
    for (int i = 0; i<_sd->seed_size; i++){
        sum += ((uint8*)_sd->seed)[i];
    }
    if (sum == 0){
        update_seed(_sd, DEFAULT_SEED_UPDATE);
    }

    uint64 out = 0;
    for (int i = 0; i<sizeof(uint64); i++){
        out <<= 8;
        uint64 temp = 0;
        for (int j = 0; j<_sd->seed_size; j++){
            temp += ((uint8*)_sd->seed)[j];
        }
        if (temp == 0){
            temp = (uint64)RANDOM_VAL + 1;
        }
        out |= (uint8)((uint64)RANDOM_VAL * temp + (uint64)RANDOM_VAL + temp) & 0xff;
    }

    out %= (uint64)RANDOM_VAL + 1;

    if((__rndsetting & __AUTO_UPDATE_SEED) == SET_AUTO_UPDATE_SEED){
        update_seed(_sd, RDSEED_METHOD);
    }
    return out;
}

RND_API uint16 random16(rndseed *_sd, const RNDSTNG __rndsetting){
    int sum = 0;
    for (int i = 0; i<_sd->seed_size; i++){
        sum += ((uint8*)_sd->seed)[i];
    }
    if (sum == 0){
        update_seed(_sd, DEFAULT_SEED_UPDATE);
    }
    uint16 out = 0;

    for (int i = 0; i<sizeof(uint16); i++){
        out <<= 8;
        uint16 temp = 0;
        for (int j = 0; j<_sd->seed_size; j++){
            temp += ((uint8*)_sd->seed)[j];
        }
        if (temp == 0){
            temp = (uint16)RANDOM_VAL + 1;
        }
        out |= (uint8)((uint64)RANDOM_VAL * temp + (uint64)RANDOM_VAL + temp) & 0xff;
    }

    out %= (uint16)RANDOM_VAL + 1;

    if((__rndsetting & __AUTO_UPDATE_SEED) == SET_AUTO_UPDATE_SEED){
        update_seed(_sd, RDSEED_METHOD);
    }
    return (uint16)out;
}

RND_API uint8 random8(rndseed *_sd, const RNDSTNG __rndsetting){
    int sum = 0;
    for (int i = 0; i<_sd->seed_size; i++){
        sum += ((uint8*)_sd->seed)[i];
    }
    if (sum == 0){
        update_seed(_sd, DEFAULT_SEED_UPDATE);
    }
    uint8 out = 0;
    for (int i = 0; i<sizeof(uint8); i++){
        out <<= 8;
        uint8 temp = 0;
        for (int j = 0; j<_sd->seed_size; j++){
            temp += ((uint8*)_sd->seed)[j];
        }
        if (temp == 0){
            temp = (uint8)RANDOM_VAL + 1;
        }
        out |= (uint8)((uint64)RANDOM_VAL * temp + (uint64)RANDOM_VAL + temp) & 0xff;
    }

    out %= (uint8)RANDOM_VAL + 1;

    if((__rndsetting & __AUTO_UPDATE_SEED) == SET_AUTO_UPDATE_SEED){
        update_seed(_sd, RDSEED_METHOD);
    }
    return (uint8)out;
}