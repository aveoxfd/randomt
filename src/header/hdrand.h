#ifndef _RANDOM_TEMPERATURE_GENERATOR_H
#define _RANDOM_TEMPERATURE_GENERATOR_H

#ifdef __cplusplus
extern "C"{
#endif

typedef unsigned long long          uint64;
typedef unsigned long               uint32;
typedef unsigned short              uint16;
typedef unsigned char               uint8;

typedef signed long long            sint64;
typedef signed long                 sint32;
typedef signed short                sint16;
typedef signed char                 sint8;

#define RDRAND_METHOD 0b00000000
#define RDSEED_METHOD 0b00000010
#define NOSEED      0
#define DEBUG       1
#define NOT_SUPPORT 0xFF
#define SET_AUTO_UPDATE_SEED    0b00000001
#define SET_NO_AUTO_UPDATE_SEED 0b00000000

#define __AUTO_UPDATE_SEED      0b00000001
#define __RANDOM_METHOD         0b00000010

#ifdef RND_STATIC
    #define RND_API
    #elif defined _WIN32 || defined _WIN64 || defined _CYGWIN__
        #ifdef RND_BUILD_DLL
            #define RND_API __declspec(dllexport)
        #else
            #define RND_API __declspec(dllimport)
        #endif
    #elif defined __GNUC__ && __GNUC__ >= 4
        #define RND_API __attribute__ ((visibility ("default")))
    #else
        #define RND_API
#endif

#ifdef __WIN32__
    #define DEFAULT_MODE unsigned long
#elif __WIN64__
    #define DEFAULT_MODE unsigned long long
#endif

typedef void* seed;
typedef seed rndsp, seed_t;

typedef uint8 RNDSTNG; //setting type

typedef struct rndseed{
    seed seed;
    uint8 seed_size; //bytes
}rndseed, rndseed_t;

//assembly functions
int __get_hardrand_rdrand(void);
int __get_hardrand_rdseed(void);

/*
Generates a random number using hardware random method in C language style.
*/
RND_API void update_seed        (rndseed *_sd, const RNDSTNG __rndsetting);
RND_API DEFAULT_MODE random     (rndseed *_sd, const RNDSTNG __rndsetting);
RND_API uint32 random32         (rndseed *_sd, const RNDSTNG __rndsetting);
RND_API uint64 random64         (rndseed *_sd, const RNDSTNG __rndsetting);
RND_API uint16 random16         (rndseed *_sd, const RNDSTNG __rndsetting);
RND_API uint8 random8           (rndseed *_sd, const RNDSTNG __rndsetting);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/*
Generate a random number by hardware using termal entropy and raw entropy.

The library only works with the rdrand and rdseed CPU commands.
If your CPU is younger than the x86 architecture, these commands will not work. 
Make sure your CPU supports these commands before using this library.
Usage:
    #include "hdrand.h"
    HardwareRandom r; // Creates a random generator with default seed and method (rdrand).
    HardwareRandom r(123456); // Creates a random generator with seed 123456 and default method (rdrand).
    HardwareRandom r(123456, RDRAND_METHOD); // Creates a random generator with seed 123456 and rdrand method.
    HardwareRandom r(123456, RDSEED_METHOD); // Creates a random generator with seed 123456 and rdseed method.
    HardwareRandom r; // Creates a random generator with default seed and method (rdrand).
*/
template <typename T = DEFAULT_MODE>
class HardwareRandom{
    private:
    T seed;
    int(*random_method)(void);

    public:
    HardwareRandom(T seed, unsigned char method);
    HardwareRandom(T seed);
    HardwareRandom(void);
    
    T random(void);
    void update_seed(void); 
    T random64(void);
    T random32(void);
};
#endif
#endif