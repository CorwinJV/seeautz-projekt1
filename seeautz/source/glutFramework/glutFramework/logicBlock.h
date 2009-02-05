#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H

#include "aiInstructionEnums.h"
#include "oglTexture2D.h"

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