// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "User.h"
#include "DragonAI.h"
#include "BTTASK_Scream.generated.h"

/**
 * 
 */
UCLASS()
class UBTTASK_Scream : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTASK_Scream();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
