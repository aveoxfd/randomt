#include "hdrand.h"
#include <time.h>


#define ERROR_CODE 0x128

#if (LANG == CPPLANG)
#include <iostream>

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

template class HardwareRandom<sint64>;
template class HardwareRandom<sint32>;
template class HardwareRandom<sint16>;
template class HardwareRandom<sint8>;
template class HardwareRandom<int>;

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
/*
Generates a random 64-bit unsigned integer.
*/
template <typename T>
T HardwareRandom<T>::random64(void){
    seed = 
    return (T) seed;
}
/*
Generates a random 32-bit unsigned integer.
*/
template <typename T>
T HardwareRandom<T>::random32(void){
    seed = (random_method() * seed * 2423534837ULL + 1ULL) % 4358357894ULL;
    return (T)seed;
}

/*
Generates a random number of type T.
*/
template <typename T>
T HardwareRandom<T>::random(void){
    CHECK_SUPPORT
    seed = (random_method() * seed * 2423534837ULL + 1ULL) % 4358357894ULL;
    return (T)seed;
}
/*
Updates the seed using hardware random method.
*/
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
#endif
/*
Generates a random number using hardware random method in C language style.
*/
#if (LANG == CLANG)


#endif