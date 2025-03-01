// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHP.h"

void UMonsterHP::SetHP(float HPPercent)
{
    if (HP_Bar)
    {
        HP_Bar->SetPercent(HPPercent); // HP 값을 업데이트
    }
}
