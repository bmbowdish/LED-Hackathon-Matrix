// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  randomSeed(analogRead(0));
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  
  // pinMode(13, OUTPUT); debug
  
  
  digitalWrite(1,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);

}


uint8_t image[3][3] = {
  {0, 0, 0},
  {0, 1, 0},
  {0, 0, 0}
};

uint8_t button_prev;
uint8_t button;
uint8_t button_prev1;
uint8_t button1;
uint8_t button_prev2;
uint8_t button2;
uint8_t button_prev3;
uint8_t button3;
uint8_t button_prev4;
uint8_t button4;



void drawCol(uint8_t * rows,int col){
  digitalWrite(col+1,HIGH);
  digitalWrite(1,!rows[0]);
  digitalWrite(2,!rows[1]);
  digitalWrite(3,!rows[2]);
  delay(1);
  digitalWrite(1,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(col+1,LOW);
  delay(1);
}

void draw(int n){
 for(int j = 0; j < n; j++){ 
    for(int i = 0; i < 3; i++){
      drawCol(image[i],i+3);
    }
 }
}

void iterate(){
  button_prev1 = button1;
  button1 = !digitalRead(7);
  button_prev2 = button2;
  button2 = !digitalRead(8);
  if(button1 && !button_prev1){
    for(int x = 0; x < 3; x++){
      for(int y = 0; y < 3; y++){
        if((x < 2) && (image[x][y] == 1)){
          image[x+1][y] = 1;
          image[x][y] = 0;
          x++;
        }
        else if((x == 2) && (y < 2) && (image[x][y] == 1)){
          image[0][y+1] = 1;
          image[x][y] = 0;
          x = 3;
          y = y+1;
        }
        else if((y == 2) && (x == 2) && (image[x][y] == 1)){
          image[0][0] = 1;
          image[x][y] = 0;
          x = 3;
          y = 3;
        }
      }
    }
  }
  if(button2 && !button_prev2){
    for(int x = 0; x < 3; x++){
      for(int y = 0; y < 3; y++){
        if((y < 2) && (image[x][y] == 1)){
          image[x][y+1] = 1;
          image[x][y] = 0;
          y++;
        }
        else if((y == 2) && (x < 2) && (image[x][y] == 1)){
          image[x+1][0] = 1;
          image[x][y] = 0;
          y = 3;
          x = x+1;
        }
        else if((x == 2) && (y == 2) && (image[x][y] == 1)){
          image[0][0] = 1;
          image[x][y] = 0;
          x = 3;
          y = 3;
        }
      }
    }
  }
  draw(1);
}
void up(){
  for(int x = 0; x < 3; x++){
    for(int y = 0; y < 3; y++){
      if((x > 0) && (image[x][y] == 1)){
          image[x-1][y] = 1;
          image[x][y] = 0;
      }
    }     
  }
}
void down(){
  for(int x = 0; x < 3; x++){
    for(int y = 0; y < 3; y++){
      if((x < 2) && (image[x][y] == 1)){
          image[x+1][y] = 1;
          image[x][y] = 0;
          x++;
      }
    }     
  }
}

void left(){
  for(int x = 0; x < 3; x++){
    for(int y = 0; y < 3; y++){
      if((y > 0) && (image[x][y] == 1)){
          image[x][y-1] = 1;
          image[x][y] = 0;
      }
    }     
  }
}

void right(){
  for(int x = 0; x < 3; x++){
    for(int y = 0; y < 3; y++){
      if((y < 2) && (image[x][y] == 1)){
          image[x][y+1] = 1;
          image[x][y] = 0;
          y++;
      }
    }     
  }
}

void traverse(){
  draw(1);
  button_prev1 = button1;
  button1 = !digitalRead(7);
  button_prev2 = button2;
  button2 = !digitalRead(8);
  button_prev3 = button3;
  button3 = !digitalRead(9);
  button_prev4 = button4;
  button4 = !digitalRead(10);
  
  // if the 'up' button has been pressed since the last time this ran, call up()
  if(button1 && !button_prev1){
    up();
  }
  
  // if the 'right' button has been pressed since the last time this ran, call right()
  if(button2 && !button_prev2){
    right();
  }
  
  // if the 'down' button has been pressed since the last time this ran, call down()
  if(button3 && !button_prev3){
    down();
  }  
  
  // if the 'left' button has been pressed since the last time this ran, call left()
  if(button4 && !button_prev4){
    left();
  }
}

void boxes(){
  for(int x = 0; x < 3; x++){
    for(int y = 0; y < 3; y++){
      if(random(1)!= image[x][y]){
        image[x][y] = !image[x][y];  
      }
    }
  }
  draw(50);
}

int set = 0; 
// the loop function runs over and over again forever
void loop() {
  
  //traverse(); debug
  //iterate(); debug
  //boxes(); debug
  //draw(1); debug
  
  // determines if mode button (digitalRead(11)) has been pressed since the last time the line ran
  button_prev = button;
  button = !digitalRead(11);
  
  // if the mode button has been pressed since the last time this ran, change the mode. 
  if(button && !button_prev){
    set = !set;
  }
  
  
  if(set){
    traverse();
  }
  if(!set){
    iterate();
  }
    
}
