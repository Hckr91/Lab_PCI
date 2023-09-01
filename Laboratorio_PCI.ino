#include <Servo.h>
#include <LiquidCrystal.h>

#define RS 7
#define EN 6

#define D4 5
#define D5 4
#define D6 3
#define D7 2

#define botSim 8
#define botNao 9

#define luzUV 13
#define centrifuga 10
//#define secadorQ 11
#define secador 12
#define percloreto A1

int cent = 2;
int secMais = 15;
int secMenos = 2;
int UV = 4;
int corrosao = 20;

Servo servomotor;
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

void contProgressiva(int);

void centrifugar();
void secar();
void UV_Light();
void corroer();
void menu();
 
void setup() {
 lcd.begin(16,2);
}

void loop() {
  menu();
}


void centrifugar(){
  
  pinMode(botSim,INPUT);
  pinMode(botNao,INPUT);
  pinMode(centrifuga,OUTPUT);

  lcd.setCursor(4,0);
  lcd.print("INICIAR?");
  lcd.setCursor(1,1);
  lcd.print("Sim");
  lcd.setCursor(12,1);
  lcd.print("Nao");

  int Sim = digitalRead(botSim);
  delay(55);
  int Nao = digitalRead(botNao);
  delay(55);
  
  if(Sim == 1){
   digitalWrite(centrifuga,HIGH);
   lcd.clear(); 
   contProgressiva(cent);
   digitalWrite(centrifuga,LOW);
  }
  else if(Nao == 1){
   menu();
  }
}


void secar(){
  
  pinMode(botSim,INPUT);
  pinMode(botNao,INPUT);
  //pinMode(secadorQ,OUTPUT);
  pinMode(secador,OUTPUT);

  lcd.setCursor(4,0);
  lcd.print("INICIAR?");
  lcd.setCursor(0,1);
  lcd.print("15 min");
  lcd.setCursor(11,1);
  lcd.print("2 min");

  int Sim = digitalRead(botSim);
  delay(55);
  int Nao = digitalRead(botNao);
  delay(55);
  
  if(Sim == 1){
  
   digitalWrite(secador,HIGH);
   lcd.clear(); 
   contProgressiva(secMais);
  
   digitalWrite(secador,LOW);
  }
  else if(Nao == 1){
   digitalWrite(secador,HIGH);
   lcd.clear(); 
   contProgressiva(secMenos);
   digitalWrite(secador,LOW);
  }

}

void UV_Light(){
  
  pinMode(botSim,INPUT);
  pinMode(botNao,INPUT);
  pinMode(luzUV,OUTPUT);

  lcd.setCursor(4,0);
  lcd.print("INICIAR?");
  lcd.setCursor(1,1);
  lcd.print("Sim");
  lcd.setCursor(12,1);
  lcd.print("Nao");

  int Sim = digitalRead(botSim);
  delay(55);
  int Nao = digitalRead(botNao);
  delay(55);
  
  if(Sim == 1){
   analogWrite(luzUV,128);
   lcd.clear(); 
   contProgressiva(cent);
   analogWrite(luzUV,0);
  }
  else if(Nao == 1){
    menu();
  }
}

void corroer(){
  
  pinMode(botSim,INPUT);
  pinMode(botNao,INPUT);
  
  servomotor.attach(percloreto);

  lcd.setCursor(4,0);
  lcd.print("INICIAR?");
  lcd.setCursor(1,1);
  lcd.print("Sim");
  lcd.setCursor(12,1);
  lcd.print("Nao");

  int Sim = digitalRead(botSim);
  delay(55);
  int Nao = digitalRead(botNao);
  delay(55);
  
  int segundos = 0;
  int minutos = 0;
  
  if(Sim == 1){
    
   do{ 
   servomotor.write(45);
   delay(1000);
   
   lcd.clear();
     segundos++;
          lcd.setCursor(0,0);
          lcd.print("Tmp decorrido:"); 
          lcd.setCursor(0,1);
          lcd.print(minutos);
          lcd.print(" min e ");
          lcd.print(segundos);
          lcd.setCursor(11,1);
          lcd.print("seg");

   
   servomotor.write(0);
   delay(1000);
    
   lcd.clear();
     
   segundos++;
          lcd.setCursor(0,0);
          lcd.print("Tmp decorrido:"); 
          lcd.setCursor(0,1);
          lcd.print(minutos);
          lcd.print(" min e ");
          lcd.print(segundos);
          lcd.setCursor(11,1);
          lcd.print("seg");
      
  
    if(segundos == 60){ 
      segundos = 0;
      minutos++;
    }
   
   }while(minutos<corrosao);
  }
  else if(Nao == 1){
    menu();
  }
}





void contProgressiva(int temp){
  
  int decimas = 0;
  int segundos = 0;
  int minutos = 0;
  
  int i;

  do{
    i = millis();
    if(i%1000 == 0){
      decimas++;
      if(decimas == 10){
        decimas = 0;
        segundos++;
          lcd.setCursor(0,0);
          lcd.print("Tmp decorrido:"); 
          lcd.setCursor(0,1);
          lcd.print(minutos);
          lcd.print(" min e ");
          lcd.print(segundos);
          lcd.setCursor(11,1);
          lcd.print("seg");
      }
  }
    if(segundos == 60){ 
      segundos = 0;
      minutos++;
    }
    
  }while(minutos!=temp);
  
}




void menu(){
  lcd.setCursor(0,0);
  lcd.print("O que deseja?");
          lcd.setCursor(0,1);
          lcd.print("1-CENTRIFUGAR");
  
  pinMode(botSim,INPUT);
  pinMode(botNao,INPUT);


  int opcao = 0;

  do{
  int op = digitalRead(botSim);
  delay(65);
  int entra = digitalRead(botNao);
  delay(65);
  
    if(op == HIGH){
      opcao++;
 
    }
        if(opcao == 1){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("O que deseja?");
          lcd.setCursor(0,1);
          lcd.print("1-CENTRIFUGAR");
          while(opcao == 1 && entra == 1){
          lcd.clear();
          centrifugar();
         // break;
          }
        }
        if(opcao == 2){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("O que deseja?");
          lcd.setCursor(0,1);
          lcd.print("2-SECAR");
          while(opcao == 2 && entra == 1){
          lcd.clear();
          secar();
          //break;
          }
        }
        if(opcao == 3){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("O que deseja?");
          lcd.setCursor(0,1);
          lcd.print("3-ULTRA VIOLETA");
          while(opcao == 3 && entra == 1){
           lcd.clear();
           UV_Light();
           //break;
          }
        }
        if(opcao == 4){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("O que deseja?");
          lcd.setCursor(0,1);
          lcd.print("4-PERCLORETO");
          while(opcao == 4 && entra == 1){
           lcd.clear();
           corroer();
          // break;
          }
        }
        
        if(opcao > 4){
        opcao = 0;
        }
       
        
  }while(true);
}
