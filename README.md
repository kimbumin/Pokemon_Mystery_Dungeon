# Pokemon_Mystery_Dungeon
포켓몬스터 미스터리던전 모작

---
# 팀원 및 역할
- **신동민** (팀장): Player 구현, Enemy AI
- **김부민**: Skill 시스템, 사운드 관리
- **이강욱**: UI 디자인 및 구현
- **임현준**: 타일맵 구조 설계 및 시스템

# 프로젝트 개요
- **프로젝트 목표**
    - 이 프로젝트는 Nintendo의 인기 게임 시리즈 포켓몬스터 미스터리 던전을 모티브로 하여, WinAPI를 기반으로 한 2D 로그라이크 던전 탐험 게임을 구현하고자 시작되었습니다.
- **배경**
    - 단순 모작에 그치지 않고, 다양한 패턴 적용, 절차적 생성을 통한 랜덤 맵 등 다양한 기술적 도전을 통해 게임 개발에 필요한 구조적 사고와 문제 해결 역량을 키우는 것을 목표로 합니다.
- **핵심 주제**
    - 포켓몬의 능력치를 활용한 전투 시스템
    - 턴제 로직
    - 던전 내의 동적 생성 및 이동 시스템 구현

# 개발환경 / 사용 스택
- **개발 언어**: C++
- **개발 툴**: Visual Studio 2022
- **그래픽 라이브러리**: WinAPI, GDI+, SDL2
- **사운드 라이브러리**: SDL_mixer
- **버전 관리**: Git, GitHub
- **데이터 관리**: CSV 파일 기반 (포켓몬 및 스킬 정보)

# **참고 자료**
- 포켓몬스터 기술 데이터
    - [*](https://namu.wiki/w/%ED%8F%AC%EC%BC%93%EB%AA%AC%EC%8A%A4%ED%84%B0/%EA%B8%B0%EC%88%A0)[포켓몬 기술 정보](https://namu.wiki/w/%ED%8F%AC%EC%BC%93%EB%AA%AC%EC%8A%A4%ED%84%B0/%EA%B8%B0%EC%88%A0#s-8.1**)
- **포켓몬스터 데이터**
    - [포켓몬 데이터](https://pokemondb.net/stats)
- **포켓몬스터 데미지 계산**
    - [나무위키 포켓몬스터 데미지 계산식](https://namu.wiki/w/%ED%8F%AC%EC%BC%93%EB%AA%AC%EC%8A%A4%ED%84%B0/%EA%B8%B0%EC%88%A0#s-8.1)
- **포켓몬스터 불가사의 던전 예시 동영상**
    - [YouTube 링](https://www.youtube.com/watch?v=fDiGN_szAmY&t=921s)

# 개발환경 / 사용 스택

- **개발 언어**: C++
- **개발 툴**: Visual Studio 2022
- **그래픽 라이브러리**: WinAPI, GDI+, SDL2
- **사운드 라이브러리**: SDL_mixer
- **버전 관리**: Git, GitHub
- **데이터 관리**: CSV 파일 기반 (포켓몬 및 스킬 정보)

---
---
# 📦 외부 의존성
이 프로젝트는 다음 외부 라이브러리에 의존합니다: SDL2, SDL2_mixer
- SDL2는 멀티미디어 및 게임 개발을 위한 크로스 플랫폼 라이브러리입니다.
이 프로젝트에는 포함되어 있지 않으며, 사용자가 별도로 설치해야 합니다.

# 설치 방법
본인 OS(윈도우 / macOS / 리눅스)에 맞는 개발용 라이브러리 다운로드
개발 환경(IDE, 빌드 시스템)에서 include 및 lib 경로를 연결하도록 설정

⚠ 주의: 프로젝트 빌드 설정에서 요구하는 SDL2 버전과 일치하는지 반드시 확인하세요.
## 윈도우
### SDL2
1. SDL2 개발용 라이브러리 다운로드
    - SDL2 다운로드 페이지에서 SDL2-devel-2.x.x-VC.zip 파일 다운로드
2. 압축 해제 후 폴더 구성
    - include/ : 헤더 파일 (SDL.h 등)
    - lib/x86/ 또는 lib/x64/ : 정적/동적 라이브러리 파일
3. Visual Studio 설정
    - 프로젝트 > 속성 > C/C++ > 일반 > 추가 포함 디렉터리에 include 경로 추가
    - 프로젝트 > 속성 > 링커 > 일반 > 추가 라이브러리 디렉터리에 lib/x64 경로 추가
    - 프로젝트 > 속성 > 링커 > 입력 > 추가 종속성에 SDL2.lib, SDL2main.lib 추가
    - 실행 파일 위치에 SDL2.dll 복사

### SDL2_mixer
1. SDL2 개발용 라이브러리 다운로드
    - SDL2 다운로드 페이지에서 SDL2_mixer-devel-2.x.x-VC.zip 파일 다운로드
2. 압축 해제 후 폴더 구성
    - include/ : 헤더 파일 (SDL_mixer.h 등)
    - lib/x86/ 또는 lib/x64/ : 정적/동적 라이브러리 파일
3. Visual Studio 설정
    - 프로젝트 > 속성 > C/C++ > 일반 > 추가 포함 디렉터리에 include 경로 추가
    - 프로젝트 > 속성 > 링커 > 일반 > 추가 라이브러리 디렉터리에 lib/x64 경로 추가
    - 프로젝트 > 속성 > 링커 > 입력 > 추가 종속성에 SDL2_mixer.lib 추가
    - 실행 파일 위치에 SDL2_mixer.lib 복사

# SDL2 다운로드 주소
- https://github.com/libsdl-org

# 설치 참고 영상
- SDL2: https://www.youtube.com/watch?v=bnPvxWrnq8I
- SDL2_mixer: https://www.youtube.com/watch?v=edBc9wN_HtA
