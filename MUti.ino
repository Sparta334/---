// copyright 111019022 5/27-2022-12：10
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

#define  Do NOTE_C4
#define  Re NOTE_D4
#define  Mi NOTE_E4
#define  Fa NOTE_F4
#define So NOTE_G4
#define La NOTE_A4
#define  Si NOTE_B4 

#define Doh NOTE_C5 
#define Reh NOTE_D5 
#define Mih NOTE_E5
#define Fah  NOTE_F5 
#define Soh  NOTE_G5
#define Lah  NOTE_A5
#define Sih  NOTE_B5 

byte BtnA =  4  ;    //   當按鈕A按下的時候，Seven seg 開始倒數
byte BtnB = 3 ;      //   當按鈕B按下的時候，會立即播放另外的曲⼦

byte Buzzer  = 6 ;     // 蜂鳴器
byte pins[7]={13, 12, 11, 10, 9, 8, 7};  //  LED

byte show[10][7]={         //LED SHOW 
  {0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 1, 1, 1},
  {0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 1, 1, 0},
  {1, 0, 0, 1, 1, 0, 0},
  {0, 1, 0, 0, 1, 0, 0},
  {1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0},
};


int melody[3][40] = {
 
 { So , So ,La , So ,Doh ,Si , 0 , So, So ,La ,So,  Reh , Doh , 0 , So ,So ,Soh , Mih , Doh,Si ,La , 0 , Fah , Fah, Mih, Doh, Reh , Doh ,0,0,0 ,-1  },
 { Do ,Re ,Mi ,Fa ,So ,La ,Si , Doh , 0  , Doh , Sih ,Lah ,  Soh , Fah ,Mih ,Reh ,Do ,0,0,0, -1 },
 {Mi ,Re, Do, Re ,Mi ,Mi, Mi ,0 ,Re ,Re, Re,0  , Mi, Mi, Mi,0, Mi ,Re, Do ,Re, Mi, Mi ,Mi,0,Re, Re, Mi ,Re, Do, 0 ,0 ,0 -1}
};

int noteDurations[3][40] = {
  {4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4,4 ,4 ,4,4 ,4 ,4 ,4,4 ,4 ,4 ,4,4 ,4 ,4 },  //28
  {4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4},
  {4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4,4 ,4 ,4  ,4 ,4 ,4  ,4 ,4  ,4 ,4  ,4 ,4}
};
int noteDuration = 0;
long previousTime = 0;
long presentTime = 0;
long pauseBotweenNotes = 0;

int MelodyIndex = 0; //  切換曲子
int Melodyapha  = 0 ;// 音調 

const long LEDdelay = 1000; // LED 一秒一次
long LEDTime = 0 ; //  上次LED
int LEDIndex = 10 ;  // LED 數字
long BtnAPressDelay = 0;
long BtnBPressDelay = 0 ;

bool ButtomAPress = false;

void setup() {

 for(byte i = 0 ; i< 7 ;i++){
   pinMode(pins[i] , OUTPUT);
 }
for(byte j = 0 ; j < 7 ; j++){
   digitalWrite(pins[j], 1);
}
 pinMode(BtnA , INPUT_PULLUP);
 pinMode(BtnB , INPUT_PULLUP);
 pinMode(Buzzer , OUTPUT);
}

void loop() {

  presentTime = millis();
  checkToPlay();
  BtnAISPress();
  ShowLED();

  BtnBISPress();

}

void checkToPlay() {
  
  if(presentTime - previousTime >= pauseBotweenNotes) {

    if(melody[MelodyIndex][Melodyapha] == -1 ) {
      
      pauseBotweenNotes = 1000;
      previousTime = millis();
      Melodyapha = 0;
    } else {
      noteDuration = 1000 / noteDurations[MelodyIndex][Melodyapha];
      tone(6, melody[MelodyIndex][Melodyapha++], noteDuration);
      pauseBotweenNotes = noteDuration * 1.2;
      previousTime = millis();
    }
  }
}

void ShowLED(){
  
  

      if(presentTime - LEDTime >= LEDdelay )
      {
        ButtomAPress == false ? (LEDIndex  = (++LEDIndex)%10) : (LEDIndex <= 0 ?LEDIndex = 9 :LEDIndex  =  --LEDIndex);
        LEDTime = presentTime;
      }
      for(byte j = 0 ; j < 7 ; j++){
        digitalWrite(pins[j], show[LEDIndex][j]);
      }

}
// Copyright 111019022 2022-5/27-12:10
void BtnAISPress(){
  if(digitalRead(BtnA) == LOW){
      if(presentTime -BtnAPressDelay >=200 ){
        ButtomAPress= !ButtomAPress;
        BtnAPressDelay = presentTime;
        return ;
      }
  }


}
// Copyright 111019022 2022-12:10
void BtnBISPress()
{
  if(digitalRead(BtnB) == LOW){
      if(presentTime -BtnBPressDelay >=200 ){

          
        MelodyIndex < 2 ? MelodyIndex++ : MelodyIndex = 0;
        
        Melodyapha = 0;
        BtnBPressDelay = presentTime;
        return ;
      }
  }
}

// Copyright 111019022 5/27-2022-12:10
