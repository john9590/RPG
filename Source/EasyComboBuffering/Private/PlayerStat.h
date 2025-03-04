#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "PlayerStat.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct
{
    GENERATED_BODY()

public:
    // ü�� (HP)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Stats")
    float HP;

    // ���� (MP)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Stats")
    float MP;

    // ������ �̹��� (Texture2D) - Texture2D�� Replicated �������� ����!
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Stats")
    UTexture2D* Image;

    // ���� (Count)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Stats")
    int32 Count;

    // �⺻�� ���� (������)
    FItemStruct()
        : HP(0.0f), MP(0.0f), Image(nullptr), Count(0)
    {}
    FItemStruct(float hp, float mp, UTexture2D* image)
        : HP(hp), MP(mp), Image(image), Count(1)
    {}
};

/**
 *
 */
UCLASS()
class EASYCOMBOBUFFERING_API APlayerStat : public APlayerState
{
    GENERATED_BODY()
public:
    APlayerStat();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing = OnRep_Items, Category = "My Data")
    TArray<FItemStruct> Items;
    UFUNCTION(BlueprintCallable)
    void UseItem(int32 index);

    // Replication ó��
    UFUNCTION()
    void OnRep_Items() {};

    virtual void SeamlessTravelTo(APlayerState* NewPlayerState) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
