int portBMask = 0b00111111;
int portDMask = 0b10000000;
int diceArray[] = {0b00001000, 0b00010100, 0b00011100, 0b10010101, 0b10011101, 0b10110111};
int dice;
char data;
void setup() {
  randomSeed(analogRead(0));
  DDRD |= portDMask; //set pins 8...13 as outputs
  DDRB |= portBMask;//set pin 7 as an output
  Serial.begin(9600);
}
//gets a random number and displays it with the leds
int rollDice() {
  int value = random(1, 7);
  PORTD = diceArray[value - 1] & portDMask;
  PORTB = diceArray[value - 1] & portBMask;
  return value;
}
//clears the dice and waits for t milliseconds
void clearDice(int t){
  PORTD = 0;
  PORTB = 0;
  delay(t);
}

void loop() {
  if ( Serial.available() > 0) {
    data = Serial.read();
    if (data == '1') {
      //rolling animations
      for (int i = 0; i < 10; i++) {
        rollDice();
        delay(100);
        clearDice(50);
      }
      for (int i = 0; i < 3; i++) {
        rollDice();
        delay(300);
        clearDice(100);
      }
    //get the actual number and send it to app via BT   
    dice = rollDice();
    Serial.println(dice);
    delay(1000);
    }
  }
}
