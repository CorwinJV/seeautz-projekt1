#ifndef OGLUTILITY_H
#define OGLUTILITY_H

#include <string>
#include <GL/glut.h>

enum State { 
				Active,		// updating	and drawing
				Passive,	// drawing and not updating
				Hidden,		// not updating and not drawing
				DeleteMe,	// flagged for removal
};

#endif