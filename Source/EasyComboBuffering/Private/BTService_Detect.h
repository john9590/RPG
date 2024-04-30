// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DragonAI.h"
#include "User.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "BTService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class UBTService_Detect : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_Detect();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};