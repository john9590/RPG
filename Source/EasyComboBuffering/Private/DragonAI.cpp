// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonAI.h"

const FName ADragonAI::TargetKey(TEXT("Target"));

ADragonAI::ADragonAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Book/AI/BB_ABCharacter.BB_ABCharacter"));
	if (BBObject.Succeeded())
		BBAsset = BBObject.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Book/AI/BT_ABCharacter.BT_ABCharacter"));
	if (BTObject.Succeeded())
		BTAsset = BTObject.Object;
}

void ADragonAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard;
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		if (!RunBehaviorTree(BTAsset))
			UE_LOG(LogTemp, Warning, TEXT("AIController couldn't run behavior tree!"));
	}
}