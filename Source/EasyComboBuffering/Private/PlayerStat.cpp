// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStat.h"
#include "User.h"

APlayerStat::APlayerStat()
{
	bReplicates = true; 
}

void APlayerStat::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(APlayerStat, Items, COND_None);
}

void APlayerStat::UseItem(int32 index)
{
	if (Items[index].Count > 0) {
		Items[index].Count--;
		OnRep_Items();
		if (AUser* player = Cast<AUser>(GetOwningController()->GetPawn())) {
			player->Hit(-Items[index].HP);
		}
	}
}

void APlayerStat::SeamlessTravelTo(APlayerState* NewPlayerState)
{
	if (APlayerStat* NewPS = Cast<APlayerStat>(NewPlayerState))
	{
		NewPS->Items = Items;
	}
}
