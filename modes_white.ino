
void corners_in_white(){
  int width = 5;
  int i;
  for(i=LPS; i>=(0-width); i--){
    set_all(0);
    int j;
    for(j=0; j < width; j++){
      int n = j + i; 
      if (n >= 0 && n < LPS){
        for(int k=0; k < strips; k++){
          leds.setPixel(n+k*LPS, WHITE);
        }
      }
    }
    dm(20);
  }
}
void corners_out_white(){
  int width = 5;
  for(int i=0; i<=(LPS+width); i++){
    set_all(0);
    for(int j=0; j < width; j++){
      int n = j + i; 
      if (n >= 0 && n < LPS){
        for(int k=0; k < strips; k++){
          leds.setPixel(n+k*LPS, WHITE);
        }
      }
    }
    dm(20);
  }
}


int pos[4] = {0, 10, 20, 30};
int dirct[4] = {1, 1, 1, 1};

void corners_inout_stagared_white(){
  int width = 5;

  set_all(0);
  for (int k=0; k < strips; k++){
    if (pos[k] >= LPS){
      dirct[k] = -1;
    } else if(pos[k] <= 0){
      dirct[k] = 1;
    }
    for (int j=0; j < width; j++){
      int n = pos[k] - j; 
      if (n >= 0 && n < LPS){
        leds.setPixel(n+k*LPS, WHITE);
      }
    }
    pos[k] += dirct[k];
  }
  dm(30);

}


int corners_inout_color = 0;
void corners_inout_stagared(){
  int width = 5;
  set_all(makeColor(corners_inout_color, 100, 50));
  set_all(0);

  for (int k=0; k < strips; k++){
    if (pos[k] >= LPS){
      dirct[k] = -1;
    } else if (pos[k] <= 0){
      dirct[k] = 1;
    }
    for (int j=0; j < width; j++){
      int n = pos[k] - j; 
      if (n >= 0 && n < LPS){
        leds.setPixel(n+k*LPS, makeColor((corners_inout_color+165+k*10),100,50));
      }
    }
    pos[k] += dirct[k];
  }
  corners_inout_color += 1;
  if(corners_inout_color >= 360){
    corners_inout_color = 0;
  }
  dm(30);
}

void rotate_cw_white(){
  int width = 5;
  int j;
  for(j=0; j < strips; j++){
    set_all(0);
    int i;
    for(i=0; i>LPS; i++){
      leds.setPixel(i+j*LPS, WHITE);
    }
    dm(800);
  }
}

void rotate_acw_white(){
}

double fade_step = 0;
void fade_white(){
  fade_step += 0.05;
  for(int i=0; i<nLeds; i++){
    double sin1 = sin(fade_step);
    int light = map(sin1 * 1000, -1000, 1000, 3, 100);
    //Serial.println(light);
    leds.setPixel(i, makeColor(0, 0, light));
  }
  if (fade_step > 1000){
    fade_step = 0;
  }
  dmm(500);
}

int fade_hue = 0;
void fade_color(){
  fade_step += 0.05;
  for(int i=0; i<nLeds; i++){
    double sin1 = sin(fade_step);
    int light = map(sin1 * 1000, -1000, 1000, 3, 100);
    Serial.println(light);
    leds.setPixel(i, makeColor(fade_hue + (i%LPS), 100, light));
  }
  leds.setPixel(random(nLeds), makeColor(random(0, 360), 100,50));
  if (fade_step > 1000){
    fade_step = 0;
  }
  fade_hue += 1;
  if(fade_hue >= 360){
    fade_hue = 0;
  }
  dmm(500);
}


void random_mode(){
  leds.setPixel(random(nLeds), makeColor(random(0, 360), 100,50));
  leds.setPixel(random(nLeds), makeColor(random(0, 360), 100,50));
  leds.setPixel(random(nLeds), 0);
  dm(50);
}

void random_mode_white(){
  for(int i=0; i<60; i++){
    leds.setPixel(random(nLeds), WHITE);
    leds.setPixel(random(nLeds), 0);
  }
  dm(300);
}

int rand_blocks_arr[3] = {0, 0, 0};
int rand_blocks_color = 0;
int rand_blocks_pos = 0;

void random_blocks(int color){
  int pos = rand_blocks_pos;
  set_all(0);

  rand_blocks_arr[pos] = random(nLeds);

  for(int i=0; i<3; i++){
    int pick_color;
    if (color == 1){
      pick_color = makeColor(rand_blocks_color + (120 * i), 100, 50);
    } else {
      pick_color = WHITE;
    }
    Serial.println(pick_color);
    for(int j=0; j<5; j++){
      int n = rand_blocks_arr[i]+j;
      if (n >= 0 && n < nLeds){
        leds.setPixel(n, pick_color);
      }
    }
  }
  dm(100);

  rand_blocks_pos++;
  if(rand_blocks_pos >= 3){
    rand_blocks_pos = 0;
  }
  rand_blocks_color += 5;
  if(rand_blocks_color >= 360){
    rand_blocks_color = 0;
  }
}


void on_mode(){
  for(int i=0; i<nLeds; i++){
    leds.setPixel(i, WHITE);
  }
  leds.show();
}

void off_mode(){
  set_all(0);
  dm(10);
}

