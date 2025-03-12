# 🧟 Monster 클래스 문서

`AMonster`는 `APawn`을 기반으로 한 몬스터 클래스입니다.  
체력 및 마나 관리, 충돌 설정, 외형 메쉬, 체력 바 UI까지 포함된 기본 구조를 제공합니다.  
또한 `BlueprintImplementableEvent`를 통해 시각적 연출이 자유롭게 확장될 수 있도록 설계되어 있습니다.

---

## 🔧 주요 변수

```cpp
float Hp;
float MaxHp;
float Mp;
float MaxMp;

UCapsuleComponent* capsule;
USkeletalMeshComponent* mesh;
UWidgetComponent* HPBarWidget;
```

- `Hp`, `MaxHp`: 현재 및 최대 체력  
- `Mp`, `MaxMp`: 마나 수치 (스킬 기능 확장 대비)  
- `capsule`: 루트 컴포넌트, 충돌 판정 담당  
- `mesh`: 몬스터 외형  
- `HPBarWidget`: 체력 표시 위젯 (머리 위 UMG)

---

## 🛠 주요 함수

### 1. `AMonster::AMonster()`

- `Tick` 사용 활성화 (`bCanEverTick = true`)
- 캡슐 컴포넌트 생성 및 루트 설정
- SkeletalMesh 및 HPBar 위젯 생성 → 루트에 계층 연결
- 충돌 채널 `Pawn`에 대해 `Block` 설정

---

### 2.  `void Damaged(float damage)`

```cpp
UFUNCTION(BlueprintCallable)
void Damaged(float damage);
```

- 외부에서 호출 가능한 체력 감소 함수  
- 사망 조건이 되면 `MonsterAI`의  `GetDied()` 호출

---

## 🔄 라이프사이클

- `BeginPlay()` / `Tick()` 오버라이드되어 있으며,  
  AI 연동, 체력 회복, 전투 상태 전환 등에서 사용

---

## 🤖 연관 시스템

- `MonsterAI` 컨트롤러와 연결되어 Behavior Tree 또는 FSM 기반 AI 동작 가능

---

## ✅ 요약

- `AMonster`는 전투 기반 캐릭터를 위한 최소 단위 구현체입니다.  
- 컴포넌트 중심 구조로 확장이 용이하며, 블루프린트 이벤트를 통해 다양한 연출을 자유롭게 구현할 수 있습니다.  
- 충돌, 체력바, 피격 처리 등 기본적인 전투 구조가 포함되어 있습니다.
