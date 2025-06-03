#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

void shell(){
  char buf[128], cmd[64], arg[2][64],username[64],company[64];
  strcpy(username, "user");
  strcpy(company, "");

  printString("Welcome to EorzeOS!\r\n");
  while (true) {
    // printString("> ");
    info(username, company);
    readString(buf);
    parseCommand(buf, cmd, arg);

    if (strcmp(cmd,"yo")){
      printString("gurt\r\n");
    }else if(strcmp(cmd,"gurt")){
      printString("yo\r\n");
    }else if(strcmp(cmd,"user")){
      if (arg[0][0] != '\0') {
        strcpy(username, arg[0]);
        printString("Username changed to: ");
        printString(username);
        printString("\r\n");
      }else {
        strcpy(username, "user");
        printString("Username changed to: user\r\n");
      }
    }else if(strcmp(cmd,"grandcompany")){
      if(strcmp(arg[0],"maelstrom")){
        strcpy(company, "@Storm");
        clearScreen();
      }else if(strcmp(arg[0],"immortalflames")){
        strcpy(company, "@Flames");
        clearScreen();
      }else if(strcmp(arg[0],"twinadder")){
        strcpy(company, "@Serpent");
        clearScreen();
      }else {
        printString("Unknown Grand Company\r\n");
      }   
    }else if(strcmp(cmd,"add")){
      int num1, num2,result;
      char resultStr[64];
      if (arg[0][0] != '\0' && arg[1][0] != '\0') {
        atoi(arg[0], &num1);
        atoi(arg[1], &num2);
        result = num1 + num2;
        
        itoa(result, resultStr);       
        printString(resultStr);
        printString("\r\n");
      } else {
        printString("Usage: add <num1> <num2>\r\n");
      }
    }else if(strcmp(cmd,"sub")) {
      int num1, num2,result;
      char resultStr[64];
      if (arg[0][0] != '\0' && arg[1][0] != '\0') {
        atoi(arg[0], &num1);
        atoi(arg[1], &num2);
        result = num1 - num2;
        
        itoa(result, resultStr);
        printString(resultStr);
        printString("\r\n");
      } else {
        printString("Usage: sub <num1> <num2>\r\n");
      }
    }else if(strcmp(cmd,"mul")) {
      int num1, num2,result;
      char resultStr[64];
      if (arg[0][0] != '\0' && arg[1][0] != '\0') {
        atoi(arg[0], &num1);
        atoi(arg[1], &num2);
        result = num1 * num2;
        
        itoa(result, resultStr);
        printString(resultStr);
        printString("\r\n");
      } else {
        printString("Usage: mul <num1> <num2>\r\n");
      }
    }else if(strcmp(cmd,"div")) { 
      int num1, num2,result;
      char resultStr[64];
      if (arg[0][0] != '\0' && arg[1][0] != '\0') {
        atoi(arg[0], &num1);
        atoi(arg[1], &num2);
        if (num2 == 0) {
          printString("Error: Division by zero\r\n");
        } else {
          result = div(num1, num2); // gunakan fungsi div buatan sendiri
          
          itoa(result, resultStr);
          printString(resultStr);
          printString("\r\n");
        }
      }
    }else if(strcmp(cmd,"clear")){
      strcpy(username,"user");
      strcpy(company,"");
      clearScreen();
    }else if(strcmp(cmd,"yogurt")){
      char response[3][100];
      int randomIndex;
      strcpy(response[0], "yo");
      strcpy(response[1], "ts unami gng </3");
      strcpy(response[2], "sygau");
      randomIndex = mod(getBiosTick(), 3); 
      printString(response[randomIndex]);
      printString("\r\n");
    }else{      
      printString(buf);
      printString("\r\n");
    }
  }
}

//void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  //TODO: Implementasi fungsi untuk mem-parsing perintah
//}

// Tambahkan fungsi bila perlu

void info(char *username, char *company) {  
  printString(username);
  printString(company);
  printString("> ");
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, k = 0;
  bool inArg = false;

  // Kosongkan cmd dan arg
  for (i = 0; i < 64; i++) cmd[i] = '\0';
  for (i = 0; i < 2; i++)
    for (j = 0; j < 64; j++) arg[i][j] = '\0';

  // Salin command
  i = 0;
  while (buf[i] != ' ' && buf[i] != '\0') {
    cmd[i] = buf[i];
    i++;
  }
  cmd[i] = '\0';

  // Lewati spasi setelah command
  while (buf[i] == ' ') i++;

  // Ambil argumen pertama
  j = 0;
  while (buf[i] != ' ' && buf[i] != '\0') {
    arg[0][j++] = buf[i++];
  }
  arg[0][j] = '\0';

  // Lewati spasi setelah arg1
  while (buf[i] == ' ') i++;

  // Ambil argumen kedua
  j = 0;
  while (buf[i] != ' ' && buf[i] != '\0') {
    arg[1][j++] = buf[i++];
  }
  arg[1][j] = '\0';
}
