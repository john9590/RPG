# 🧍 User (플레이어 캐릭터 클래스)

`ACharacter`를 상속한 플레이어 클래스.  
체력, 공격력, 버프, 그로기 등의 전투 상태를 직접 제어하며  
블루프린트와 연동 가능한 이벤트도 포함되어 있음.

---

## 📌 주요 기능 요약

| 기능 | 설명 |
|------|------|
| 체력/공격력/방어력 관리 | HP, Attack, Defense 값 초기화 및 계산 처리 |
| 데미지 처리 | `Hit()` 함수로 데미지 적용 |
| 버프 적용 | `SetBuff()` 함수로 공격력 강화, 타이머로 해제 |
| 그로기 상태 | 일정 시간동안 조작 불가 상태 |
| 블루프린트 연동 | `Damaged()` 이벤트 제공 (BP에서 이펙트 등 확장 가능) |

---

## 🔧 주요 변수

```cpp
float HP;
float MaxHP;
float Attack;
float Defense;
bool isgroggy;
float remaingroggy;
std::vector<std::pair<int, int>> buffq;
```

- `HP` / `MaxHP`: 현재 및 최대 체력  
- `Attack`: 현재 공격력 (버프 반영됨)  
- `Defense`: 방어력
- `isgroggy`: 현재 그로기 상태 유무  
- `remaingroggy`: 남은 그로기 시간  
- `buffq`: 적용 중인 버프 목록 (idx 기본, 중첩 관리용)

---

##  🛠 주요 함수

### 1. `void Hit(float damage)`

```cpp
void AUser::Hit(float damage) {
    HP -= damage;
}
```

- 외부로부터 데미지를 전달받아 `HP`를 감소시킵니다.  

---

### 2. `void Groggy(float time)`

```cpp
void AUser::Groggy(float time) {
    remaingroggy = time;
    isgroggy = true;
}
```

- 지정한 시간 동안 그로기 상태에 진입  
- `Tick()` 또는 외부 시스템에서 시간 소지 후 해제

---

### 3. `void SetBuff(float enhance, float time, int idx)`

```cpp
void AUser::SetBuff(float enhance, float time, int idx) {
    if (enhance == 1.0f) return;

    bool isinlist = false;

    for (int i = 0; i < buffq.size(); i++) {
        if (buffq[i].first == idx) {
            buffq[i].second++;
            isinlist = true;
        }
    }

    if (!isinlist) {
        Attack *= enhance;
        buffq.push_back(std::pair<int, int>(idx, 1));
    }

    GetWorld()->GetTimerManager().SetTimer(...);
}
```

- 공격력 버프를 적용하며 중복 유무를 검사  
- `idx`를 기준으로 중첩 관리 (`buffq`)  
- 해당 `idx`의 버프가 이미 적용중이라면 `time`만큼 연장

---


## 🔄 라이프사이클 관리 함수

| 함수 | 설명 |
|--------|--------|
| `BeginPlay()` | 게임 시작 시 초기화 로직 |
| `Tick()` | 매 프레임마다 상태 업데이트 (그로기 처리 등) |
| `SetupPlayerInputComponent()` | 키 입력 바인딩 (ACharacter 상속) |

---

## ✅ 요약

- `User` 클래스는 **체력, 버프, 상태 이상 등 전투 관련 상태를 통합 관리**합니다.  
- 공격력 버프는 **시간 기반 중첩 버프 구조**로 설계되어 유연히 적용/해제됩니다.  
- 외부 충돌 처리 (`Hit`) 및 UI/이펙트 확장 (`Damaged`)을 **분리 설계**해서 확장성과 관리가 유의합니다.  
- 그로기 및 버프는 `TimerManager`를 통해 **자동 해제 관리**됩니다.

