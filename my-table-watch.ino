#include <Wire.h>
#include "RTClib.h"

#define DIG1        5
#define DIG2        4
#define DIG3        3
#define DIG4        2
#define SEGA        8
#define SEGB        9
#define SEGC        11
#define SEGD        10
#define SEGE        12
#define SEGF        7
#define SEGG        6

uint8_t seg_code_0[] = {SEGA,SEGB,SEGC,SEGD,SEGE,SEGF,255};
uint8_t seg_code_1[] = {SEGB,SEGC,255};
uint8_t seg_code_2[] = {SEGA,SEGB,SEGD,SEGE,SEGG,255};
uint8_t seg_code_3[] = {SEGA,SEGB,SEGC,SEGD,SEGG,255};
uint8_t seg_code_4[] = {SEGB,SEGC,SEGF,SEGG,255};
uint8_t seg_code_5[] = {SEGA,SEGC,SEGD,SEGF,SEGG,255};
uint8_t seg_code_6[] = {SEGA,SEGC,SEGD,SEGE,SEGF,SEGG,255};
uint8_t seg_code_7[] = {SEGA,SEGB,SEGC,255};
uint8_t seg_code_8[] = {SEGA,SEGB,SEGC,SEGD,SEGE,SEGF,SEGG,255};
uint8_t seg_code_9[] = {SEGA,SEGB,SEGC,SEGF,SEGG,255};
uint8_t loop_ctr;
RTC_DS1307 rtc;
uint8_t d1,d2,d3,d4;

void setup() {
  // Set all as OUTPUT
  pinMode(DIG1, OUTPUT);
  pinMode(DIG2, OUTPUT);
  pinMode(DIG3, OUTPUT);
  pinMode(DIG4, OUTPUT);
  pinMode(SEGA, OUTPUT);
  pinMode(SEGB, OUTPUT);
  pinMode(SEGC, OUTPUT);
  pinMode(SEGD, OUTPUT);
  pinMode(SEGE, OUTPUT);
  pinMode(SEGF, OUTPUT);
  pinMode(SEGG, OUTPUT);

  // Turn OFF every segment
  digitalWrite(DIG1, LOW);
  digitalWrite(DIG2, LOW);
  digitalWrite(DIG3, LOW);
  digitalWrite(DIG4, LOW);
  digitalWrite(SEGA, LOW);
  digitalWrite(SEGB, LOW);
  digitalWrite(SEGC, LOW);
  digitalWrite(SEGD, LOW);
  digitalWrite(SEGE, LOW);
  digitalWrite(SEGF, LOW);
  digitalWrite(SEGG, LOW);

  Serial.begin(9600);
  delay(2000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC lost power, lets set the time!");
  
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
}

void loop() {
  DateTime now = rtc.now();

  d1 = now.hour()/10;
  d2 = now.hour()%10;
  d3 = now.minute()/10;
  d4 = now.minute()%10;
  
  for(loop_ctr=0; loop_ctr<1; ++loop_ctr)
    display_numbers_on_screen(d1,d2,d3,d4);
  
}

void set_seg_val(int seg, int val) {
  digitalWrite(seg,val);
}

void seg_on(int seg) {
  set_seg_val(seg, LOW);
}

void seg_off(int seg) {
  set_seg_val(seg, HIGH);
}

void select_digit(int dig) {
  digitalWrite(dig, HIGH);
}

void deselect_digit(int dig) {
  digitalWrite(dig, LOW);
}

void seg_off_all() {
  seg_off(SEGA);
  seg_off(SEGB);
  seg_off(SEGC);
  seg_off(SEGD);
  seg_off(SEGE);
  seg_off(SEGF);
  seg_off(SEGG);
}

void deselect_digit_all() {
  deselect_digit(DIG1);
  deselect_digit(DIG2);
  deselect_digit(DIG3);
  deselect_digit(DIG4);
}

void loop_thru_arr(uint8_t arr[]) {
  uint8_t looper;
  seg_off_all();
  for(looper=0; arr[looper]!=255; ++looper)
    seg_on(arr[looper]);
}

void display_number(int number) {
  switch(number) {
    case 0: loop_thru_arr(seg_code_0);
            break;
    case 1: loop_thru_arr(seg_code_1);
            break;
    case 2: loop_thru_arr(seg_code_2);
            break;
    case 3: loop_thru_arr(seg_code_3);
            break;
    case 4: loop_thru_arr(seg_code_4);
            break;
    case 5: loop_thru_arr(seg_code_5);
            break;
    case 6: loop_thru_arr(seg_code_6);
            break;
    case 7: loop_thru_arr(seg_code_7);
            break;
    case 8: loop_thru_arr(seg_code_8);
            break;
    case 9: loop_thru_arr(seg_code_9);
            break;
  }
}

void display_number_at_digit(int digit, int number) {
  deselect_digit_all();
  select_digit(digit);
  display_number(number);
}

void display_numbers_on_screen(int number1, int number2, int number3, int number4) {
  display_number_at_digit(DIG1,number1);delay(3);
  display_number_at_digit(DIG2,number2);delay(3);
  display_number_at_digit(DIG3,number3);delay(3);
  display_number_at_digit(DIG4,number4);delay(3);
}

void turn_screen_off() {
  deselect_digit_all();
  seg_off_all();
}
