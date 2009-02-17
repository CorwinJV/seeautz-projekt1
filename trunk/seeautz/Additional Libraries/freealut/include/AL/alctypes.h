#ifndef _ALCTYPES_H_
#define _ALCTYPES_H_

struct _AL_device;
//typedef struct _AL_device ALCdevice;

typedef int ALCenum;

/* Enumerant values begin at column 50. No tabs. */

/* bad value */
#ifndef ALC_INVALID
#define ALC_INVALID                              0
#endif

/**
 * followed by <int> Hz
 */
#ifndef ALC_FREQUENCY
#define ALC_FREQUENCY                            0x100
#endif

/**
 * followed by <int> Hz
 */
#ifndef ALC_REFRESH
#define ALC_REFRESH                              0x101
#endif

/**
 * followed by AL_TRUE, AL_FALSE
 */
#ifndef ALC_SYNC
#define ALC_SYNC                                 0x102
#endif

/**
 * errors
 */

/**
 * No error
 */
#ifndef ALC_NO_ERROR
#define ALC_NO_ERROR                             0
#endif

/**
 * No device
 */
#ifndef ALC_INVALID_DEVICE
#define ALC_INVALID_DEVICE                       0x200
#endif

/**
 * invalid context ID
 */
#ifndef ALC_INVALID_CONTEXT
#define ALC_INVALID_CONTEXT                      0x201
#endif

/**
 * bad enum
 */
#ifndef ALC_INVALID_ENUM
#define ALC_INVALID_ENUM                         0x202
#endif

/**
 * bad value
 */
#ifndef ALC_INVALID_VALUE
#define ALC_INVALID_VALUE                        0x203
#endif

#endif /* _ALCTYPES_H */
