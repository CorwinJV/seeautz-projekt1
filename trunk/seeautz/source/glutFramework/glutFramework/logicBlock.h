#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H

#include "aiInstructionEnums.h"
#include "oglTexture2D.h"
#include <vector>
#include <string>
#include "aiInstructionEnums.h"

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
	logicBlock(std::string textureName, int width, int height, std::string description, int byteCost, AiInstructions enumInstruction)
	{
		blockTexture = new oglTexture2D();
		blockTexture->loadImage(textureName, width, height);
		blockDescription = description;
		logicBlock::byteCost = byteCost;
		logicBlock::enumInstruction = enumInstruction;
	}
	~logicBlock()
	{
		delete blockTexture;
		blockTexture = NULL;
	}
	void addInstruction(AiInstructions instr)
	{
		instructionList.push_back(instr);
	}
	std::string							blockDescription;
	oglTexture2D*						blockTexture; 
	std::vector<AiInstructions>			instructionList;
	int									byteCost;
	AiInstructions						enumInstruction;
};

#endif