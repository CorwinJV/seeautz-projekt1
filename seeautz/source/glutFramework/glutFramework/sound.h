// Includes ///////////////////////////////////////////////////////////////////////
// OpenAL includes
#ifndef SOUND_H
#define SOUND_H
#include <al.h>
#include <alc.h>
#include <alctypes.h>
#include <altypes.h>
#include <alu.h>
#include <alut.h>

#include <stdio.h>

// Defines ////////////////////////////////////////////////////////////////////////
#define NULL			0
#define NUM_BUFFERS		2
#define NUM_SOURCES		1

class soundEffect
{
public:
	ALuint buffers[NUM_BUFFERS];
	ALuint source[NUM_SOURCES];
	soundEffect();
	~soundEffect();
	int LoadAndAssignWAV(char* _fileName, ALuint _buffer);
	int Init(void);
	int Update(void);
	int Shutdown(void);
	void playSound();
};
#endif