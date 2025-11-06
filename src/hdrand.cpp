#include "hdrand.h"
#include <time.h>
#include <stdio.h>
#include <iostream>

#define ERROR_CODE 0x128

typedef unsigned long long  uint64;
typedef unsigned long       uint32;
typedef unsigned short      uint16;
typedef unsigned char       uint8;

#define CONSTRUCTOR_MESSAGE std::cout<<"Constructor message\nSeed: "<<(uint64)seed<<"\n"
#define DEFAULT_RANDOM_METHOD __get_hardrand_rdrand

#define CHECK_SUPPORT \
switch(random_method()){\
    case NOT_SUPPORT:\
        std::cout<<"CPU doesn't support random commands.\n";\
        return NOT_SUPPORT;\
        break;\      
}

template class HardwareRandom<uint64>;
template class HardwareRandom<uint32>;
template class HardwareRandom<uint16>;
template class HardwareRandom<uint8>;

extern "C"{
    int __get_hardrand_rdrand(void);
    int __get_hardrand_rdseed(void);
}

template <typename T>
HardwareRandom<T>::HardwareRandom(T seed) : seed(seed), random_method(DEFAULT_RANDOM_METHOD) {
    CONSTRUCTOR_MESSAGE;
};

template <typename T>
HardwareRandom<T>::HardwareRandom(void) : seed(0), random_method(DEFAULT_RANDOM_METHOD){
    update_seed();
    #if (DEBUG)
    CONSTRUCTOR_MESSAGE<<"created with void parameters.\n";
    #endif
};

template <typename T>
HardwareRandom<T>::HardwareRandom(T seed, uint8 method) : seed(seed), 
random_method(
    method == RDRAND_METHOD ? __get_hardrand_rdrand : method == RDSEED_METHOD ? __get_hardrand_rdseed : __get_hardrand_rdrand
) {
    #if(DEBUG)
    CONSTRUCTOR_MESSAGE;
    #endif
};

template <typename T>
uint64 HardwareRandom<T>::random64(void){
    seed = (random_method() * seed * 242353483725792147621796315248697241650ULL + 1LL) % 43583578946312482376987392659358379256ULL;
    return seed;
}

template <typename T>
uint32 HardwareRandom<T>::random32(void){
    seed = (random_method() * seed * 242353483725792147621796315248697241650UL + 1LL) % 43583578946312482376987392659358379256UL;
    return seed;
}

template <typename T>
DEFAULT_MODE HardwareRandom<T>::random(void){
    CHECK_SUPPORT
    seed = (random_method() * seed * 242353483725792147621796315248697241650ULL + 1LL) % 43583578946312482376987392659358379256ULL;
    return seed; 
}

template <typename T>
void HardwareRandom<T>::update_seed(void){
    seed = 1;
    int n;
    while (n == 0){
        n = random_method() * time(0) % 100 + 1;
    }
    for (int i = 0; i<n; i++){

        seed *= random_method();
    }
    seed+=random_method()*time(0);
}