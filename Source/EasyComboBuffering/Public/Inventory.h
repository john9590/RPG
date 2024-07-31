// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM()
enum EINVENSTATE
{
	ITEM_NONE,
	ITEM_USABLE,
	ITEM_EQUIPMENT
};

class CITEMDATA
{
public:
	CITEMDATA();
	~CITEMDATA();
private:
	FName Name;
	UTexture2D* Texture;
	TEnumAsByte<EINVENSTATE> Type;
	int Count;
};

class EASYCOMBOBUFFERING_API Inventory
{
public:
	Inventory();
	~Inventory();
private:
	FName Name;
	UTexture2D* Texture;
	TEnumAsByte<EINVENSTATE> Type;
	int Count;
};
