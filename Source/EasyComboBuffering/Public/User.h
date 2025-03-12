// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <vector>
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
	void SetBuff(float enhance, float time, int idx);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isgroggy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Attack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Defense;

private:
	float remaingroggy;
	std::vector<std::pair<int,int>> buffq;
};
