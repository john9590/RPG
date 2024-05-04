// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DragonAI.h"
#include "Dragon.h"
#include "BTTask_FireBall.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_FireBall : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_FireBall();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
