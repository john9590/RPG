// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MonsterAI.h"
#include "Monster.generated.h"

UCLASS()
class EASYCOMBOBUFFERING_API AMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Damaged(float damage);
	UFUNCTION(BlueprintImplementableEvent)
	void Died();
	UFUNCTION(BlueprintImplementableEvent)
	void hit();

	UPROPERTY(EditAnywhere)
	float MaxHp;
	UPROPERTY(EditAnywhere)
	float MaxMp;
private:
	AMonsterAI* AIController;
	float Hp;
	float Mp;
};
