
int makeColorS(unsigned int hue){
  makeColor(hue, 100, lightness);
}

int makeWhite(){
  makeColor(0, 0, lightness);
}

void set_all(int color){
  for(int i=0; i<nLeds; i++){
    leds.setPixel(i, color);
  }
}


void dm(int wait){
  dmm(wait * 1e3);
}

void dmm(int wait){
    leds.show();
    delayMicroseconds(wait);
}

int keyboard(){
  if (Serial.available()) {
    // read the most recent byte (which will be from 0 to 255):
    int c = Serial.read();
    // set the brightness of the LED:
    Serial.println(c);
    if (c >= 0 && c <17) {
      mode = c;
      timet = millis();
      return 0;
    }
    return 0;
    //Serial.print(".");
  }
}
