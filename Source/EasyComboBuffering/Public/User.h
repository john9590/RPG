// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "User.generated.h"

UCLASS()
class EASYCOMBOBUFFERING_API AUser : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUser();
	void Hit(float damage);
	void Groggy(float time);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float HP;
	UPROPERTY(EditAnywhere)
	float MaxHP;
	bool isgroggy;
	float remaingroggy;
};
