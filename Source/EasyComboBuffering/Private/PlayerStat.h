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
    // 체력 (HP)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Stats")
    float HP;

    // 마나 (MP)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Stats")
    float MP;

    // 아이템 이미지 (Texture2D) - Texture2D는 Replicated 지원되지 않음!
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Stats")
    UTexture2D* Image;

    // 개수 (Count)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Stats")
    int32 Count;

    // 기본값 설정 (생성자)
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

    // Replication 처리
    UFUNCTION()
    void OnRep_Items() {};

    virtual void SeamlessTravelTo(APlayerState* NewPlayerState) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
