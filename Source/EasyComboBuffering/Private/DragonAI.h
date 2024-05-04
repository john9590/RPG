// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DragonAI.generated.h"

/**
 * 
 */
UCLASS()
class ADragonAI : public AAIController
{
	GENERATED_BODY()
public:
	ADragonAI();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName TargetKey;
	static const FName DamageKey;
private:
	UBehaviorTree* BTAsset;
	UBlackboardData* BBAsset;
};
