# 🐲 Project RPG - 보스전 중심 단계형 액션 RPG

> 언리얼 엔진 5 기반 1인 개발 RPG 프로젝트  
> **스테이지별 몬스터 패턴 설계**, **포션 시스템**, **보스전 전환**,  
> 그리고 다양한 전투 로직과 애니메이션을 구현하였습니다.

---

## 🧭 게임 구조 개요

### 📍 스테이지 구성

| 단계 | 몬스터  | 특징 |
|------|----------|--------|
| 1단계 | Grux 1마리 | 단거리 돌진 후 **1회 일반 공격** |
| 2단계 | Grux 2마리 | 같은 패턴으로 동시에 등장 |
| 3단계 | Kraken 1마리 | **3가지 패턴을 순환하며 공격** |
| 보스전 | Dragon 1마리 | 원거리 Fireball + 그로기 + 근접공격 |

---

## 🧪 몬스터별 전투 패턴

### 🧟 몬스터 공통
- **AI**: Behavior Tree로 구현
- **피격** : 피격시 행동을 멈추고 피격 애니메이션 재생(보스는 제외)
- **사망** : HP가 0이하일시 사망 판정, 사망 이후엔 행동을 하지 않음
- **패턴** : 조건(거리, 쿨타임)에 따라 패턴 전환

---

### 🦍 Grux

- **패턴 목록**: 
  1. `Attack` - 일반 공격

---

### 🐙 Kraken
- **패턴 목록**:
  1. `SmashAttack` - 땅을 내리쳐서 큰 피해
  2. `SweepAttack` - 좌우로 쓸기 공격 2회
  3. `SweepSmashAttack` - Sweep 공격 후 Smash 공격

---

### 🐉 보스 Dragon
- **패턴 목록**:
  - `AttackMouth`: 전방 근접 베기
  - `Scream`: 500 이하 범위 시 **3초 그로기**
  - `Fireball`: 예측 위치로 경고 장판 → 파이어볼 투하


---

## 🍯 전투 보조 시스템

### 💊 포션 시스템
- 몬스터 사망 시 포션 드랍
- 플레이어가 습득 시 **UI 인벤토리에 등록**
- **사용 가능 포션**:
  - HP 회복 포션 → 체력 즉시 회복
  - 공격력 버프 포션 → 일정 시간 공격력 강화 (`SetBuff`)
  - HP 회복 및 공격력 버프 포션 → 체력 즉시 회복 및 일정시간 공격력 강화 (`SetBuff`)

- 포션 수량은 UI에 실시간 반영되며, 소비 시 감소

---

## 📍 단계 진행 로직

1. 플레이어가 몬스터 처치 → Delegate를 통해 다음 단계 시작
3. 3단계 종료 → 포탈 생성 → `보스맵 이동`
4. Dragon 보스와 최종 결전

---

## 📂 주요 클래스 및 구조

| 클래스 | 역할 | 문서 링크 |
|--------|------|-----------|
| `User` | 플레이어 상태 및 버프 처리 | [📄 User.md](/docs/User.md) |
| `PlayerStat` | 인벤토리 및 아이템 사용 | [📄 PlayerStat.md](/docs/PlayerStat.md) |
| `Monster` | 몬스터 기본 행동 및 체력 UI | [📄 Monster.md](/docs/Monster.md) |
| `MonsterAI` | 몬스터 AI 시스템 | [📄 MonsterAI.md](/docs/MonsterAI.md) |
| `BTTask_FireBall` | 보스 패턴 실행 (투사체) | [📄 BTTask_FireBall.md](/docs/BTTask_FireBall.md) |

---

## 🎥 시연 영상

[![Watch Demo](http://img.youtube.com/vi/BvPEk9q_KU8/0.jpg)](https://www.youtube.com/watch?v=BvPEk9q_KU8)

---
