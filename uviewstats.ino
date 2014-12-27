#include <MicroView.h>

#define X 64
#define Y 48
#define SPEED 19200

void setup() {
  Serial.begin(SPEED);    // start serial communication
  uView.begin();          // start microview
}

void loop() {
  String input;

  char data[255];
  char action;
  char needle[] = ",";
  char *result, *load_last, *mem = NULL;
  
  byte i, width, locate, shift, core, load;

  input = read_input();  
  input.substring(1).toCharArray(data, 255);
  action = input[0];

  uView.clear(PAGE);      // clear page

  switch (action) {
  //
  // init core number
  //

  case '0':
    result = strtok(data, needle);
    core = atoi(result);
    width = (int)(X / core);
    width--;
    result = strtok(NULL, needle);
    mem = result;

    uView.setCursor(2, 0);
    uView.print("uViewStats");
    uView.setCursor(2, 32);
    uView.print("Cores    ");
    uView.print(core);
    uView.setCursor(2, 40);
    uView.print("Memory  ");
    uView.print(mem);
    uView.lineH(0, 8, 64);
    uView.display();

    scroll_text("Version 1.2 @fauveauarmel", 0, 64, 16, 10);

    break;

  //
  // view core usage
  //
  
  case '1':
    i = 0;
    result = strtok(data, needle);
    core = atoi(result);
    width = (int)(X / core);
    width--;
    result = strtok(NULL, needle);

    shift = int((64 - (12 * core)) / (core + 1));
    locate = shift;
    
    while (result != NULL) {
      if(core < 6) {
        uView.setCursor(locate, 0);
        uView.print(result);
        locate += shift + 12;
      }
      load = atoi(result);
      load = map(load, 0, 100, 1, 40);

      for (int j = (Y - 1); j > (Y - load); j -= 2) {
        uView.lineH((width * i) + i, j, width);
      }

      result = strtok(NULL, needle);
      i++;
    }

    uView.lineH(0, 8, 64);
    break;

  //
  // view cpu usage
  //
  
  case '2':
    i = 0;
    result = strtok(data, needle);
    while (result != NULL) {
      load = atoi(result);
      load_last = result;
      load = map(load, 0, 100, 1, 40);

      uView.lineV(i, (Y - load), Y);

      result = strtok(NULL, needle);
      i++;
    }

    uView.setCursor(8, 0);
    uView.print("CPU ");
    uView.print(load_last);
    uView.print(" %");
    uView.lineH(0, 8, 64);    
    break;

  //
  // view memory usage
  //
  
  case '3':
    i = 16;
    result = strtok(data, needle);
    while (result != NULL) {
      uView.setCursor(1, i);
      uView.print(result);

      result = strtok(NULL, needle);

      i += 8;
    }

    uView.setCursor(14, 0);
    uView.print("Memory");
    uView.lineH(0, 8, 64);      
    break;

  //
  // view disk usage
  //
  
  case '4':
    i = 16;
    result = strtok(data, needle);
    while (result != NULL) {
      uView.setCursor(1, i);
      uView.print(result);

      result = strtok(NULL, needle);

      i += 8;
    }

    uView.setCursor(22, 0);
    uView.print("Disk");
    uView.lineH(0, 8, 64);      
    break;

  //
  // view net usage
  //
  
  case '5':
    i = 16;
    result = strtok(data, needle);
    while (result != NULL) {
      uView.setCursor(1, i);
      uView.print(result);

      result = strtok(NULL, needle);

      i += 8;
    }

    uView.setCursor(12, 0);
    uView.print("Network");
    uView.lineH(0, 8, 64);      
    break;

  }
  uView.display();
}

String read_input() {
  String input;
  
  while (input.length() == 0) {
    if (Serial.available() > 0) {
      input = Serial.readStringUntil('\r');
    }
  }
  
  return input;
}

void scroll_text(char* message, int font_type, int x, int y, int wait) {
  int size, step, width;

  uView.setFontType(font_type);   // sets font
  step = uView.getFontWidth();

  size = strlen(message);
  while (true) {
    for (int i = 0; i < size; i++) {
      int j = x+step*i;
      if ((j + step > 0) && (j < X)) uView.drawChar(j, y, message[i]);
    }
    x--;
    uView.display();
    delay(wait);

    if (x < -size * step) {
      x = 64; 
      break;
    }
  }
}
