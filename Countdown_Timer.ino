/*************************************************************************************

  Mark Bramwell, July 2010

  This program will test the LCD panel and the buttons.When you push the button on the shield，
  the screen will show the corresponding one.
 
  Connection: Plug the LCD Keypad to the UNO(or other controllers)

**************************************************************************************/

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
int Item        = 0;
int Input       = 0;
int Clear       = 0;
int End         = 0;
int Hours       = 0;
int Minutes     = 0;
int Seconds     = 0;
int SpeedCounter= 0;
int Temp1       = 0;
int Starter     = 0;
int Minus       = 0;
int Timer       = 0;



#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5


int read_LCD_buttons(){               
    adc_key_in = analogRead(0);       
    
    if (adc_key_in > 1000) return btnNONE; 

    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 150)  return btnUP; 
    if (adc_key_in < 300)  return btnDOWN; 
    if (adc_key_in < 500)  return btnLEFT; 
    if (adc_key_in < 650)  return btnSELECT;  

}


void menuOne(){
  lcd.setCursor(0,0);
  lcd.print("Set Timer:");
  lcd.setCursor(10,0);
  lcd.print(Input);
  lcd.print("       ");

  lcd.setCursor(0,1);
  
  HMS();
  lcd.print(Hours);
  lcd.print("h ");
  
  lcd.print(Minutes);
  lcd.print("m ");
  
  lcd.print(Seconds); 
  lcd.print("s  ");
}


void menuTwo(){
  clearer();
  lcd.setCursor(0,0);
  lcd.print("Counting Down");

  if (Starter == 0){
    Temp1 = millis()/1000;
    Starter ++;
  }
  
  lcd.setCursor(0,1);
  
  if (Timer < 0){
    End = 1;
    
  }
  if (Timer>=0){
  HMS();
  lcd.print(Hours);
  lcd.print("h ");
  
  lcd.print(Minutes);
  lcd.print("m ");
  
  lcd.print(Seconds); 
  lcd.print("s  ");
  Timer=Input-StartTime();
  
  }
}


int StartTime(){
 return millis()/1000- Temp1;
}


void clearer(){
  if (Clear == 1){
    Clear = 0;
    lcd.clear();
  }
}


void EndScreen(){
  Clear = 1;
  clearer();
  
  
  for (int i = 0; i < 10; i++){
    lcd.setCursor(0,0);
    lcd.print("Timer");  
    lcd.setCursor(0,1);
    lcd.print("is done!");
    delay(100);
    lcd.clear();
    delay(100);
    }
  
  Item = 0;
  Input = 0;
  Timer = 0;
  End = 0;
  Starter = 0;
}


void HMS(){
  int temp  = 0;
  if (Timer/60 >= 0 && Timer/60 < 61){
    Minutes = Timer/60;
    Seconds = Timer%60;
  }
  if (Timer/60 > 60){
    
    temp = Timer/60;
    Hours = temp/60;
    Minutes = temp%60;
    Seconds = Timer%60;
  }
  }
  

void setup(){
  lcd.begin(16, 2);               
  lcd.setCursor(4,0);              
  char L1[10] = "Arduino";
  
  for (int i = 0; i < strlen(L1); i++){
    lcd.print(L1[i]);
    delay(200);
  }
  
  lcd.setCursor(0,1);
  char L2[16] = "COUNTDOWN TIMER";
  
  for (int i = 0; i < strlen(L2); i++){
    lcd.print(L2[i]);
    delay(50);
  }
  
  delay(2000);
  lcd.clear();

}

 
void loop(){
  
  if (Item == 0 ) menuOne();
  if (Item == 1) menuTwo();
  if (End == 1) EndScreen();

   lcd.setCursor(10,0);
   
   lcd_key = read_LCD_buttons();   // read the buttons
    
   switch (lcd_key){               // depending on which button was pushed, we perform an action

       case btnRIGHT:{             //  push button "RIGHT" and show the word on the screen
            //lcd.print("RIGHT ");
            
            break;
       }
       case btnLEFT:{
             //lcd.print("LEFT   "); //  push button "LEFT" and show the word on the screen
             break;
       }    
       case btnUP:{
             //lcd.print("UP    ");  //  push button "UP" and show the word on the screen
             if (Item == 0){ 
             if (SpeedCounter<30){
                Input++;
                Timer=Input;
                SpeedCounter ++;
               }
             if (SpeedCounter>29) {
              Input+=60;
              Timer=Input;
             }
             delay(100);
             }
             
             break;
       }
       case btnDOWN:{
             //lcd.print("DOWN  ");  //  push button "DOWN" and show the word on the screen
             
             if (Item == 0){ 
             if (SpeedCounter<30) {
              
              Input--;
              Timer=Input;
              SpeedCounter ++;
             }
             if (SpeedCounter>29) {
              Input-=60;
              Timer=Input;
             }
             delay(100);
             }
             
             if(Input<0){
              Timer = 0;
              Input = 0;
             
             }
             
             break;
       }
       case btnSELECT:{
             //lcd.print("SELECT");  //  push button "SELECT" and show the word on the screen
             
             Item++;
             if (Item == 2 && Timer > 0) Item = 1;
             if (Item == 2 && Timer == 0) Item = 0;
             Clear = 1;
             //delay(500);
             break;
       }
       case btnNONE:{
            //lcd.print("NONE  ");  //  No action  will show "None" on the screen
             SpeedCounter = 0;
             break;
       }
   }
   
}
