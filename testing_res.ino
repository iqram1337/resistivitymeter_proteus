#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int pin_analog = A0;
float sensitivity = 185;
float adcvalue = 0;
float voltage_offset = 2500;
float voltage = 0.0; 

float L = 0.008; //asumsi
float R = 0.001;
float A = 3.14*(R*R);
int relay = 2;

void setup() {
  pinMode(relay, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(1,1);
  lcd.print("Loading");
  lcd.setCursor(1,2);
  lcd.print("ResistivityMeter...");
  
  delay(2000);

  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("Kelompok 6");
  delay(2000);
  lcd.clear();
}

void loop() {

    digitalWrite(relay,HIGH);
    delay(1000);

    adcvalue = analogRead(pin_analog);
    voltage = ((adcvalue*5.0)/1023);
    float curr = (abs(voltage-voltage_offset)/sensitivity);
    float nilai_sensor = analogRead(A1);
    float resistansi = voltage / curr;
    float ans_resistivity = resistansi * (A/L);

    lcd.clear();
    delay(500);

    lcd.setCursor(2,0);
    lcd.print("ADC Read: ");
    lcd.setCursor(12,0);
    lcd.print(adcvalue);

    lcd.setCursor(1,1);
    lcd.print("Volt Conv:");
    lcd.setCursor(14, 1);
    lcd.print(voltage,3);
    lcd.setCursor(18,1);
    lcd.print("V");

    lcd.setCursor(1,2);
    lcd.print("Current: ");
    lcd.setCursor(11, 2);
    lcd.print(curr,3);
    lcd.setCursor(18,2);
    lcd.print("A");

    lcd.setCursor(1,3);
    lcd.print("Rest: ");
    lcd.setCursor(7,3);
    lcd.print(ans_resistivity*100000,1);
    lcd.setCursor(10,3);
    lcd.print("x10^-5 ohm.m");

    digitalWrite(relay,LOW);
    delay(2000);     
}
