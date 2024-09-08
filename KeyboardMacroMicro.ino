#include <Keyboard.h>

const int swPin = 3; // 마이크로에서 인터럽트에 쓸 수 있는 디지털 핀은 0, 1, 2, 3, 7번이다
bool isRunning = false; // 동작 상태를 나타내는 변수
unsigned long lastDebounceTime = 0; // 버튼이 눌린 시점을 저장하는 변수
const unsigned long debounceDelay = 200; // 디바운싱 간격을 설정하는 변수

void setup() {
  pinMode(swPin, INPUT_PULLUP);
  Keyboard.begin();
  Serial.begin(9600);

  // 인터럽트 설정
  attachInterrupt (
    digitalPinToInterrupt(swPin), // 스위치 핀이
    toggleRunning, // toggleRunning 함수를 호출
    CHANGE // 상태가 바뀌면
  );
}

void loop() {
  if (isRunning) {
    // F9 키 누르기
    Keyboard.press(KEY_F9);
    delay(100);
    Keyboard.releaseAll();
    delay(1000);

    // Page Down 키 누르기
    Keyboard.press(KEY_PAGE_DOWN);
    delay(100);
    Keyboard.releaseAll();
    delay(1000);
  }
}

// 인터럽트 서비스 루틴
void toggleRunning() {
  unsigned long currentTime = millis();
  
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    isRunning = !isRunning;
    if (isRunning)
      Serial.println("시작\n");
    else 
      Serial.println("정지\n");
    lastDebounceTime = currentTime;
  }
}