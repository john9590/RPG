# 🔥 BTTask_FireBall 문서

`UBTTask_FireBall`는 언리얼 엔진의 Behavior Tree Task를 상속하여 구현된 보스의 원거리 공격 스킬 태스크입니다.  
Dragon AI가 플레이어를 조준하여 Fireball을 생성하고 특정 위치에 발사하는 역할을 수행합니다.

---

## 🧩 클래스 정의

```cpp
UCLASS()
class UBTTask_FireBall : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTTask_FireBall();
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
```

- `UBTTaskNode`를 상속
- `ExecuteTask()`를 통해 Fireball 생성 및 발사 구현


---

## 🧠 ExecuteTask()

```cpp
EBTNodeResult::Type UBTTask_FireBall::ExecuteTask(...) {
    auto player = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADragonAI::TargetKey));
    if (nullptr == player) return EBTNodeResult::Failed;

    auto Dragon = OwnerComp.GetAIOwner()->GetPawn();
    FVector Direction = Dragon->GetActorLocation() - player->GetActorLocation();
    FVector GetRot = FVector(Direction.X, Direction.Y, 0.0f);
    FVector initpos = GetRot.GetSafeNormal();
    initpos = FVector(270.0f * initpos.X, 270.0f * initpos.Y, -260.0f);

    AFireBall* fireball = (AFireBall*)GetWorld()->SpawnActor<AFireBall>(AFireBall::StaticClass(), player->GetActorLocation() + initpos, FRotator::ZeroRotator);
    fireball->SetActorEnableCollision(true);

    return EBTNodeResult::Succeeded;
}
```

### 주요 처리 과정

1. **타겟 획득**:
   - Blackboard에서 타겟 플레이어 객체 획득
2. **방향 벡터 계산**:
   - 드래곤과 플레이어 사이의 벡터 차를 기반으로 발사 방향 산출
3. **초기 위치 계산**:
   - 일정 거리 앞쪽, 아래 방향 오프셋을 적용
4. **Fireball 생성**:
   - `SpawnActor<AFireBall>()`로 투사체를 생성
   - 충돌 활성화 후 Succeeded 반환

---

## ✅ 요약

- `BTTask_FireBall`은 보스의 **예측 발사형 스킬**을 담당합니다.
- Behavior Tree에서 노드로 배치되어 특정 조건에서 실행됩니다.
- 플레이어 위치 기반 벡터 연산을 통해 자연스러운 낙하형 스킬을 구현합니다.
