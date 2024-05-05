// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 10000.0f;

	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);

	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			ACharacter* User = Cast<ACharacter>(OverlapResult.GetActor());
			//UE_LOG(LogTemp, Log, TEXT("%s"),*(OverlapResult.GetActor()->GetName()));
			//��Ʈ�ѷ��� �÷��̾��� ��Ʈ�ѷ�����
			if (User && User->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADragonAI::TargetKey, User);

				//�ݰ��� �����ش�
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				//
				DrawDebugPoint(World, User->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), User->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("FALSE"));
		//null�� �������ش�.
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADragonAI::TargetKey, nullptr);
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
