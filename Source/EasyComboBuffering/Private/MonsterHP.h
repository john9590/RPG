// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MonsterHP.generated.h"

/**
 * 
 */
UCLASS()
class UMonsterHP : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SetHP(float HPPercent);


private:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HP_Bar;
	
};
