
int tray_rail_dir = 2;
int tray_rail_step = 3;
int tray_rail_en = 4;

int placer_rail_dir = 5;
int placer_rail_step = 6;
int placer_rail_en = 7;

int placer_dc_up = 9;
int placer_dc_down = 8;
int placer_magnet = 10;

int flux = 11;

int part_detected = 12;
int no_part_detected = 13;

int tray_rail_loc = 0;
int placer_rail_loc = 0;
int s = 0;

int state = 1;

void setup() {
   Serial.begin(9600); 
   
     pinMode(tray_rail_dir,OUTPUT);
     pinMode(tray_rail_step,OUTPUT);
     pinMode(tray_rail_en,OUTPUT);
   
     pinMode(placer_rail_dir,OUTPUT);
     pinMode(placer_rail_step,OUTPUT);
     pinMode(placer_rail_en,OUTPUT);
   
     pinMode(placer_dc_down,OUTPUT);
     pinMode(placer_dc_up,OUTPUT);
   
     pinMode(placer_magnet,OUTPUT);
   
     pinMode(flux,OUTPUT);
   
}


// 1000 step = 4 inch

void loop(){
  
  
  
  
  if(state == 1){
    digitalWrite(flux,LOW);    
        
    digitalWrite(placer_magnet,LOW);
    digitalWrite(tray_rail_en,HIGH);
    digitalWrite(placer_dc_up,LOW);
    digitalWrite(placer_dc_down,LOW);
    
    if(placer_rail_loc < 1400){
      s = (!s) & 0x01;
      placer_rail_loc += 1;
      digitalWrite(placer_rail_dir,HIGH);  
      digitalWrite(placer_rail_en,LOW);  
      digitalWrite(placer_rail_step,s);  
    }else{
      state = 2;
    }
  }else if(state == 2){
    digitalWrite(flux,LOW);    
        
    digitalWrite(placer_magnet,LOW);
    digitalWrite(tray_rail_en,HIGH);
    digitalWrite(placer_rail_en,HIGH);  
    
    digitalWrite(placer_dc_down, HIGH);
    digitalWrite(placer_dc_up, LOW);
    delay(380);
    state = 3;
  }else if(state == 3){
    digitalWrite(flux,LOW);    
        
    digitalWrite(placer_magnet,LOW);
    digitalWrite(placer_dc_up,LOW);
    digitalWrite(placer_dc_down,LOW);
   
    digitalWrite(tray_rail_en,HIGH);
    digitalWrite(placer_rail_en,HIGH);

    digitalWrite(placer_magnet,HIGH);
    delay(1000);
    digitalWrite(placer_dc_up,HIGH);
    delay(360);
    state = 4;
       
  }else if(state == 4){
    digitalWrite(flux,LOW);    
        
    digitalWrite(placer_dc_up,LOW);
    digitalWrite(placer_dc_down,LOW);
   
    digitalWrite(tray_rail_en,LOW);
    digitalWrite(placer_rail_en,HIGH);
    digitalWrite(placer_magnet,HIGH);
    
    if(tray_rail_loc < 1625){
      s = (!s) & 0x01;
      tray_rail_loc += 1;
      digitalWrite(tray_rail_dir,HIGH);  
      digitalWrite(tray_rail_step,s);  
    }else{
      state = 5;  
    }
  }else if(state == 5){
    digitalWrite(flux,LOW);    
        
    digitalWrite(placer_dc_up,LOW);
    digitalWrite(placer_dc_down,LOW);
   
    digitalWrite(tray_rail_en,HIGH);
    digitalWrite(placer_rail_en,LOW);
    digitalWrite(placer_magnet,HIGH);
    
    if(placer_rail_loc > 0){
      s = (!s) & 0x01;
      placer_rail_loc -= 1;
      digitalWrite(placer_rail_dir,LOW);  
      digitalWrite(placer_rail_en,LOW);  
      digitalWrite(placer_rail_step,s);  
    }else{
      state = 6;
    }    
  }else if(state == 6){
    digitalWrite(flux,LOW);    
        
    digitalWrite(placer_dc_up,LOW);
    digitalWrite(placer_dc_down,LOW);
   
    digitalWrite(tray_rail_en,HIGH);
    digitalWrite(placer_rail_en,HIGH);
    digitalWrite(placer_magnet,HIGH);
    
    digitalWrite(tray_rail_en,HIGH);
    digitalWrite(placer_rail_en,HIGH);  
    
    digitalWrite(placer_dc_down, HIGH);
    digitalWrite(placer_dc_up, LOW);
    delay(360);
    state = 7;
  }else if (state == 7){
    digitalWrite(flux,LOW);    
        
    digitalWrite(placer_dc_up,LOW);
    digitalWrite(placer_dc_down,LOW);
   
    digitalWrite(tray_rail_en,HIGH);
    digitalWrite(placer_rail_en,HIGH);
    digitalWrite(placer_magnet,LOW);
    
    digitalWrite(placer_dc_up,HIGH);
    delay(360);
    state = 8;
  }else if(state == 8){
    digitalWrite(flux,LOW);    
    digitalWrite(placer_dc_up,LOW);
    digitalWrite(placer_dc_down,LOW);
   
    digitalWrite(tray_rail_en,LOW);
    digitalWrite(placer_rail_en,HIGH);
    digitalWrite(placer_magnet,LOW);
    
    if(tray_rail_loc > 0){
      s = (!s) & 0x01;
      tray_rail_loc -= 1;
      digitalWrite(tray_rail_dir,LOW);  
      digitalWrite(tray_rail_step,s);  
    }else{
      state = 9;  
    }
  }else if(state == 9){
    digitalWrite(placer_magnet,LOW);
    digitalWrite(tray_rail_en,HIGH);
    digitalWrite(placer_rail_en,HIGH);
    digitalWrite(placer_dc_up,LOW);
    digitalWrite(placer_dc_down,LOW);
    digitalWrite(flux,HIGH);    
    delay(300);
    state = 10;
  }else if(state == 10){
    digitalWrite(flux,LOW);     
  }
  
  
  
  
  delay(3);
}








