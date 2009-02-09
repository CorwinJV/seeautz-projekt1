#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H

#include "aiInstructionEnums.h"
#include "oglTexture2D.h"
#include <vector>
#include <string>

	//===============================================
	// logicBlock
	// This struct defines a container for a texture
	// (icon), a description (like a tool tip),
	// a point value, and a vector of AiInstructions
	// enum values.
	//
	// These blocks are the building blocks of 
	// execution.

struct logicBlock
{
	logicBlock()
	{
		blockTexture = NULL;
	}
	logicBlock(std::string textureName, int width, int height, std::string description)
	{
		blockTexture = new oglTexture2D();
		blockTexture->loadImage(textureName, width, height);
		blockDescription = description;
	}
	~logicBlock()
	{
		delete blockTexture;
		blockTexture = NULL;
	}
	std::string							blockDescription;
	oglTexture2D*						blockTexture; 
	std::vector<AiInstructions>			instructionList;
};

#endif