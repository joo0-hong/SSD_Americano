# SSD Project
## Team Americano

## 코딩 컨벤션
- 인덴트: Visual Studio 기능을 이용(4칸짜리 Tab)
- if, if else, else의 괄호는 한 줄로 쓰고, 괄호 생략 가능하더라도 사용하는 걸로 결정

## 역할
- 정혜연(팀장): Project 구축, Test Shell - App 개발
- 윤태웅: Test Shell - App 개발
- 장현진: Test Shell - App 개발
- 유정균: 가상 SSD 제작
- 박준영: 가상 SSD 제작
- 홍주영: 가상 SSD 제작

## Branch Naming
- main: 최종 배포 branch
- feature/ssd: SSD 개발용 branch
- feature/test_shell: Test Shell 개발용 branch

기능 개발 Branch Naming
- feature/ssd_xxxx
- feature/shell_xxx

## 실행 파일
SSD : SSD_Americano.exe
Test Shell : TestShell_Americano.exe

## Mandatory Files
- Folder : [프로젝트 location]/resources
- Folder : [프로젝트 location]/resources/log
- buffer.txt
- nand.txt
- result.txt
- run_list.lst
- test_scenario.json

## 테스트 작성 시 프로젝트 재빌드 하지 않기 위한 테스트 작성법
1. 사용자 테스트 시나리오 작성 시 미리 지정된 test_scenario.json 파일에 지정된 format으로 작성
2. 프로그램은 이를 분석해 테스트 수행해 테스트 작성마다 재빌드 방지
3. 프로그램 실행 후 프롬프트에서 아래 커맨드 입력
```shell
scenario_test
```

### test_scenario.json 소스 위치
[프로젝트 location]/resources/test_scenario.json

### test_scenario.json 작성 방법
- 반드시 { "scenario": [{}, {}, ...] } 작성으로 시작 및 내부에 객체 필드를 생성해 test 작성할 것
- "name": string
  - "scenario" 리스트 안의 객체의 필드로 필수 작성
  - "action" 리스트 안의 객체의 필드로 필수 작성
    - "write"/"read"/"fullwrite"/"fullread"
- "lba": int
  - "read"/"write" 수행 시 "lba" 필수 작성
  - "action" 객체 안에 작성
  - "lba"를 여러 개 입력하려면 아래와 같이 사용
    - "lba_ranges": {
        "start": int
        "end": int
      }
- "data": string
  - "write"/"fullwrite" 수행 시 필수 작성
  - 입력으로 전달할 값 작성. ex) "data": "0x00110011"
- "expect": string
  - "name" 값으로 "read"/"fullread" 사용 시 필수 작성
  - 기대하는 값 입력. ex) "data": "0x11223344"
- 하나의 "action" 동작을 반복 사용하려면 action 객체 내에 아래와 같이 사용
  - "rotate_ranges" {
      "start": int
      "end": int
    }

### 예제 코드
```json
{
  "scenario": [
    {
      "name": "testapp1",
      "action": [
        {
          "name": "fullwrite",
          "data": "0x11111111"
        },
        {
          "name": "fullread",
          "expect": "0x11111111"
        }
      ]
    },
    {
      "name": "testapp2",
      "action": [
        {
          "name": "write",
          "data": "0xAAAABBBB",
          "lba_ranges": {
            "start": 0,
            "end": 6
          },
          "rotate_ranges": {
            "start": 0,
            "end": 30
          }
        },
        {
          "name": "write",
          "data": "0x12345678",
          "lba_ranges": {
            "start": 0,
            "end": 6
          }
        },
        {
          "name": "read",
          "lba_ranges": {
            "start": 0,
            "end": 6
          },
          "expect": "0x12345678"
        }
      ]
    },
    {
      "name": "testapp3",
      "action": [
        {
          "name": "write",
          "lba": 13,
          "data": "0x12341234"
        },
        {
          "name": "read",
          "lba": 13,
          "expect": "0x12341234"
        }
      ]
    }
  ]
}
```

### 예제 수행 결과
```shell
scenario_test
testapp1 --- Run ... Pass
testapp2 --- Run ... Pass
testapp3 --- Run ... Pass
```
