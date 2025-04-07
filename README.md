<div align="center">
<h1>⊹✦𓂋 minishell𓂋 ✦ﾟ⊹</h1>
<i>As beautiful as a shell</i>
</br></br>
<img src="https://github.com/user-attachments/assets/f2235e40-efbb-48b0-9cc9-9416a6496251" alt="screen_shot" width="70%">
</br></br>
</div>

## 📝 프로젝트 개요

이 프로젝트는 bash의 핵심 기능을 재구현한 “minishell”입니다. 명령어 파싱, 프로세스 생성, 파일 디스크립터 관리, 파이프라인 처리, 환경 변수 관리 등 운영체제의 핵심 메커니즘을 다루고, 사용자 입력 해석과 시스템 호출을 통해 명령을 실행하는 전체 프로세스를 구현하여 UNIX/Linux 쉘의 기본 작동 방식을 재현합니다.


## ✨ 주요 기능

- 프롬프트 표시 및 명령어 입력
- 명령 히스토리 기능
- 환경 변수 확장 (`$USER` 등)
- 파이프를 통한 명령어 연결 (`|`)
- 입출력 리다이렉션 (`>`, `>>`, `<`, `<<`)
- 종료 상태 확인 (`$?`)
- 쿼테이션 처리 (작은따옴표, 큰따옴표)
- 신호 처리 (Ctrl+C, Ctrl+D, Ctrl+\)
- 내장 명령어 구현 (아래 참조)

## 🛠️ 내장 명령어 (Builtins)

- `echo`: 인자를 출력 (`n` 옵션 지원)
- `cd`: 디렉토리 변경
- `pwd`: 현재 작업 디렉토리 출력
- `export`: 환경 변수 설정 및 내보내기
- `unset`: 환경 변수 제거
- `env`: 환경 변수 목록 표시
- `exit`: 쉘 종료

## 🗂️ 프로젝트 구조

```
minishell/
├── includes/              # 헤더 파일
│   └── minishell.h        # 주요 헤더 파일
├── libft/                 # libft 라이브러리
├── srcs/                  # 소스 코드
│   ├── builtins/         # 내장 명령어 구현
│   │   ├── builtin_cd.c
│   │   ├── builtin_echo.c
│   │   ├── builtin_env.c
│   │   ├── builtin_exit.c
│   │   ├── builtin_export.c
│   │   ├── builtin_pwd.c
│   │   └── builtin_unset.c
│   ├── execution/        # 명령어 실행 관련
│   │   ├── another_cmd.c
│   │   ├── apply_redirections.c
│   │   ├── cmd_memory_management.c
│   │   ├── heredoc_processor.c
│   │   ├── mini_execution.c
│   │   └── single_cmd.c
│   ├── parsing/          # 구문 분석 관련
│   │   ├── check_env.c
│   │   ├── check_heredoc.c
│   │   ├── check_quotation.c
│   │   ├── do_lexical.c
│   │   ├── do_syntax.c
│   │   ├── env_utils.c
│   │   ├── env_utils2.c
│   │   ├── parse_by_delimiter.c
│   │   ├── parse_cmds.c
│   │   ├── parsing_utils.c
│   │   ├── split_env.c
│   │   ├── split_quotation.c
│   │   └── token_utils.c
│   ├── main.c             # 메인 함수
│   ├── setting_signal.c   # 신호 처리
│   ├── setting_term.c     # 터미널 설정
│   ├── utils.c            # 공통 유틸리티 함수
│   └── utils2.c           
└── Makefile              # 빌드 설정

```

## 🚀 Compile and Run

### Dependencies

- GCC compiler
- GNU Readline library

### Installation and Compilation

```bash
# Clone repository
git clone https://github.com/KRimwoo/minishell.git
cd minishell

# Compile
make

# Run
./minishell

```

### readline 라이브러리 설정

- minishell은 GNU readline 라이브러리를 사용합니다. 환경에 따라 Makefile에서 라이브러리 경로를 조정해야 할 수 있습니다.

## 📚 구현 세부사항

### 1. 파싱 프로세스(@woorikim)


1. **렉시컬 분석 (Lexical Analysis)** (`do_lexical.c`):
    - 입력 문자열을 토큰으로 분리
    - 쿼테이션, 환경변수, 구분자 처리
    - 토큰 유형 분류 (WORD, ARGV, PIPE, REDIR, SPACING)
2. **구문 분석 (Syntax Analysis)** (`do_syntax.c`):
    - 파이프와 리다이렉션 유효성 검사
    - 명령어 구조 검증
3. **명령어 구조화** (`parse_cmds.c`):
    - 파싱된 토큰을 기반으로 명령어 리스트 생성
    - 명령어 인자(argv) 및 리다이렉션 정보 저장
<details>
<summary>🔍 파싱 과정</summary>

<img src="https://github.com/user-attachments/assets/74e386c7-bc58-45bf-bf22-627bcb2b6067" alt="minishell_chart" width="60%">

  
</details>

### 2. 실행 프로세스 (@yeeunpar)

1. **히어독(Heredoc) 처리** (`heredoc_processor.c`):
    - 히어독 문서가 포함된 경우 처리
    - 임시 파일에 히어독 내용 저장
2. **명령어 실행** (`mini_execution.c`, `single_cmd.c`, `another_cmd.c`):
    - 단일 명령어와 파이프라인 명령어 구분
    - 내장 명령어 확인 및 실행
    - 외부 명령어 실행 (경로 검색, 환경변수 설정, execve 호출)
3. **입출력 리다이렉션 적용** (`apply_redirections.c`):
    - 파일 입출력, 히어독, 리다이렉션 설정
    - 파일 디스크립터 관리
4. **파이프라인 처리**:
    - 여러 명령어 연결 처리
    - 파이프 생성 및 자식 프로세스 관리

### 3. Signal 처리(@woorikim, @yeeunpar)

- Ctrl+C (SIGINT): 현재 실행 중인 명령 종료, 새 프롬프트 표시
- Ctrl+D (EOF): 쉘 종료
- Ctrl+\ (SIGQUIT): 쉘에서는 무시, 명령 실행 중에는 종료

## 📋 Usage Examples

```bash
bash
복사
# Basic command execution
$ ls -la

# Using pipes
$ ls -la | grep .c

# Using redirections
$ ls > output.txt
$ cat < input.txt
$ ls >> output.txt

# Using environment variables
$ echo $HOME
$ echo $?

# Using heredoc
$ cat << EOF
heredoc> This text will be
heredoc> passed to standard input.
heredoc> EOF

# Builtin commands examples
# Change directory
$ cd /tmp
$ cd

# Display current directory
$ pwd

# Set environment variable
$ export TEST=value
$ echo $TEST

# Remove environment variable
$ unset TEST

# List environment variables
$ env

# Exit shell
$ exit

```

## 👥 Team

- [@woorikim](https://github.com/KRimwoo) - woorikim@student.42.fr
- [@yeeunpar](https://github.com/yeni023) - yeeunpar@student.42.fr
  
→ [original repository](https://github.com/not-going-to-blackhole/minishell)
