# DDP(Device Driver Project)
---
<br>
# 구현한 내용
1. 디바이스 드라이버는 입출력 다중화(Poll)와 Blocking I/O를 구현하여 처리할 데이터가 없을 시 프로세스를 대기 상태(Sleep on)로 전환하고, key interrupt 발생 시 wake up하여 준비/실행 상태로 전환하여 처리.

2. 타이머 시간과 LED 값은 App 실행 시 argument로 전달하여 처리.(미입력 시 사용법 출력 후 종료)

3. ioctl() 함수를 사용하여 다음 명령어를 구현. 
- TIMER\_START : 커널 타이머 시작
- TIMER\_STOP : 커널 타이머 정지
- TIMER\_VALUE : led on/off 주기 변경

4. key 값 읽기 : read(),  led 값 쓰기 : write()

5. 다음 내용을 구현.
- key1를 입력 시 커널 타이머를 정지.
- key2를 입력 시 키보드로 커널 타이머 시간을 10ms 단위로 입력받아 동작시킴.
- key3를 입력 시 키보드로 led 값을 입력받아(0x00~0xff) 변경된 값으로 led on/off를 동작시킴.
- key4를 입력 시 커널 타이머를 동작시킴.

6. ioctl에 사용할 구조체 arg는 다음과 같은 형태로 제한함.
```
typedef struct {
	unsigned long timer_val
} __attribute__ ((packed__)) keyled_data;
```

7. 디바이스 파일은 /dev/keyled\_dev로 만들고, 주번호는 230, 부번호는 0으로 지정.
