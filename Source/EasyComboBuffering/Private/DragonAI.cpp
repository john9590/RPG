// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonAI.h"

const FName ADragonAI::TargetKey(TEXT("Target"));
const FName ADragonAI::DamageKey(TEXT("Damage"));

ADragonAI::ADragonAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/RPG/BB_Dragon.BB_Dragon"));
	if (BBObject.Succeeded())
		BBAsset = BBObject.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/RPG/BT_Dragon.BT_Dragon"));
	if (BTObject.Succeeded()) {
		BTAsset = BTObject.Object;
	}
}

void ADragonAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard;
	UE_LOG(LogTemp, Log, TEXT("OnPossess"));
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		UE_LOG(LogTemp, Log, TEXT("SasdasdDASD"));
		if (!RunBehaviorTree(BTAsset))
			UE_LOG(LogTemp, Warning, TEXT("AIController couldn't run behavior tree!"));
	}
}