# 🧾 PlayerStat 클래스 문서

`APlayerStat`는 `APlayerState`를 상속하며,  
플레이어가 보유한 아이템과 이를 통한 체력 회복 및 공격력 버프 기능을 관리합니다.  
네트워크 복제를 지원하고, 무기나 포션과 같은 사용 아이템을 구조체(`FItemStruct`)로 보관합니다.

---

## 📦 주요 구조체: FItemStruct

```cpp
USTRUCT(BlueprintType)
struct FItemStruct {
    float HP;
    float Buff;
    UTexture2D* Image;
    int32 Count;
};
```

- `HP`: 아이템 사용 시 회복되는 체력  
- `Buff`: 공격력 증가 배율  
- `Image`: UI에서 사용되는 텍스처 이미지  
- `Count`: 아이템 보유 개수

---

## 🔧 주요 변수

```cpp
TArray<FItemStruct> Items;
```

- `Items`: 플레이어가 소유한 아이템 목록 (복제 가능)

---

## 🛠 주요 함수

### 1. `void UseItem(int32 index)`

```cpp
void APlayerStat::UseItem(int32 index) {
    if (Items[index].Count > 0) {
        Items[index].Count--;
        OnRep_Items();
        if (AUser* player = Cast<AUser>(GetOwningController()->GetPawn())) {
            player->Hit(-Items[index].HP);
            player->SetBuff(Items[index].Buff, 5.f, index);
        }
    }
}
```

- 인덱스 위치의 아이템을 사용하며:
  - 개수 감소
  - 체력 회복 (`Hit(-HP)`)
  - 공격력 버프 적용 (`SetBuff`)
- UI 갱신을 위해 `OnRep_Items()` 호출

---

### 2. `void SeamlessTravelTo(APlayerState* NewPlayerState)`

- 시점 전환 또는 레벨 이동 시 아이템 정보를 유지하기 위해  
  동일한 아이템 배열을 새로운 플레이어 상태에 복사

---

### 🌐 네트워크 복제 설정

```cpp
void GetLifetimeReplicatedProps(...) {
    DOREPLIFETIME_CONDITION(APlayerStat, Items, COND_None);
}
```

- `Items` 배열은 네트워크를 통해 클라이언트 간에 자동으로 동기화

---

## ✅ 요약

- `APlayerStat`는 **플레이어 아이템 관리** 및 **복제 시스템**을 담당합니다.  
- `UseItem()`을 통해 체력 회복 및 공격력 버프를 실행하며,  
  `FItemStruct`는 각 아이템의 성능과 상태를 정의합니다.  
- SeamlessTravel, UI 갱신, Replication 등의 요소를 활용하여 멀티플레이에서도 안정적으로 작동합니다.
