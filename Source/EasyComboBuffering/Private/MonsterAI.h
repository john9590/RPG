// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAI.generated.h"

/**
 * 
 */
UCLASS()
class AMonsterAI : public AAIController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void GetHit();
	UFUNCTION(BlueprintImplementableEvent)
	void GetDied();
};
