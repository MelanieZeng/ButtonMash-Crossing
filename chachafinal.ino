// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

#include <math.h>

int startButtonPin = D5;
int buttonPin = D7;    
int ledPin = D2;       

int counter = 0;
bool buttonState; //current game button state
bool lastButtonState = HIGH; //previous game button state
bool startButtonState; //starter button state

long lastPublishedAt = 0;
int publishAfter = 10000;

bool myState = false; //indicate my ready state
bool yourState = false; //indicate the other person's ready state

#define PIXEL_PIN D2
#define PIXEL_COUNT 14
#define PIXEL_TYPE WS2812

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Particle.subscribe(  "gameStart" , handleSharedEvent ); // Subscribe to game starting event
  Particle.subscribe(  "gameEnd" , handleSharedEvent );  // Subscribe to game ending event 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  startButtonState = digitalRead(startButtonPin);
  buttonState = digitalRead(buttonPin);

  if (startButtonState == LOW) {
      publishStartingEvent();
  }
      
  if (myState == true and yourState == true){
      counts();
      //standby animation beginning
      breathe();
      }
      
  if (counter >= 50){
      publishEndingEvent();
      //winner animation
        uint32_t a = strip.Color(22, 0, 123); // Blue
        uint32_t b = strip.Color(173, 12, 232); // Purple
        uint32_t c = strip.Color(255, 0, 121); // Violet
        uint32_t d = strip.Color(232, 46, 12); // Red
        uint32_t e = strip.Color(255, 116, 0); // Orange
         
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(i, a); // set a color 
           strip.show();
           delay( 35 );
        }
        
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(i, b); // set a color 
           strip.show();
           delay( 35 );
        }
        
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(i, c); // set a color 
           strip.show();
           delay( 35 );
        }
        
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(i, d); // set a color 
           strip.show();
           delay( 35 );
        }
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(i, e); // set a color 
           strip.show();
           delay( 35 );
        }          for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(i, a); // set a color 
           strip.show();
           delay( 35 );
        }
        
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(i, b); // set a color 
           strip.show();
           delay( 35 );
        }
        
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(i, c); // set a color 
           strip.show();
           delay( 35 );
        }
        
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(i, d); // set a color 
           strip.show();
           delay( 35 );
        }
        
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(i, c); // set a color 
           strip.show();
           delay( 35 );
        } 
      counter = 0;
  }

}

void counts()
{
   if (buttonState == LOW and lastButtonState == HIGH){
       counter += 1;
    } 
     lastButtonState = buttonState;
}

void publishStartingEvent() // Publish function for the starting event 
{

  // check that it's been 10 secondds since our last publish
  if( lastPublishedAt + publishAfter < millis() )
  {

      String eventName = "gameStart" + System.deviceID();

      // then we share it out
      Particle.publish( eventName, "data goes here" );

      // And this will get shared out to all devices using this code

      // we just pubished so capture this.
      // lastPublishedAt = millis();
      myState = true;
  }

}

void publishEndingEvent() // Publish function for the ending event
{

  // check that it's been 10 secondds since our last publish
  if( lastPublishedAt + publishAfter < millis() )
  {

      String eventName = "gameEnd" + System.deviceID();

      // then we share it out
      Particle.publish( eventName, "data goes here" );

      // And this will get shared out to all devices using this code

      // we just pubished so capture this.
      // lastPublishedAt = millis();
      myState = false;
      yourState = false;
      
    }
      
}



void handleSharedEvent(const char *event, const char *data){ // Only need one handle event function for both events 

    // Let's check the event name
    String eventName = String( event ); // convert to a string object

    // We can use this to check if our event name contains the
    // id of this device

    String deviceID = System.deviceID();

    // device id = 0123456789abcdef
    // event = "diot/2019/paired/0123456789abcdef"

    if( eventName.indexOf( deviceID ) != -1 ){
      // if we get anything other than -1
      // the event came from this device.
      // so stop doing stuff
      return;
    }
    
    if(eventName.startsWith("gameStart")){

        yourState = true;

    }
    
    if(eventName.startsWith("gameEnd")){
        
        myState = false;
        yourState = false;
        //loser animation
        uint32_t f = strip.Color(100, 0, 0); // Deep Red
        uint32_t x = strip.Color(0, 0, 0); // OFF

        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(6, f); // set a color 
           strip.setPixelColor(5, f); // set a color 
           strip.setPixelColor(4, f); // set a color 
           
           strip.setPixelColor(1, x); // set a color 
           strip.setPixelColor(2, x); // set a color 
           strip.setPixelColor(3, x); // set a color 
           strip.setPixelColor(7, x); // set a color 
           strip.setPixelColor(8, x); // set a color 
           strip.setPixelColor(9, x); // set a color 
           strip.setPixelColor(10, x); // set a color 
           strip.setPixelColor(11, x); // set a color 
           strip.setPixelColor(12, x); // set a color 
           strip.setPixelColor(13, x); // set a color 
           strip.setPixelColor(14, x); // set a color 

           strip.show();
           delay( 10 );
        }
        
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(5, f); // set a color 
           strip.setPixelColor(4, f); // set a color 
           strip.setPixelColor(3, f); // set a color 
           
           strip.setPixelColor(1, x); // set a color 
           strip.setPixelColor(2, x); // set a color 
           strip.setPixelColor(6, x); // set a color 
           strip.setPixelColor(7, x); // set a color 
           strip.setPixelColor(8, x); // set a color 
           strip.setPixelColor(9, x); // set a color 
           strip.setPixelColor(10, x); // set a color 
           strip.setPixelColor(11, x); // set a color 
           strip.setPixelColor(12, x); // set a color 
           strip.setPixelColor(13, x); // set a color 
           strip.setPixelColor(14, x); // set a color 

           strip.show();
           delay( 10 );
        }
        
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(3, f); // set a color 
           strip.setPixelColor(4, f); // set a color 
           strip.setPixelColor(5, f); // set a color 
           
           strip.setPixelColor(1, x); // set a color 
           strip.setPixelColor(2, x); // set a color 
           strip.setPixelColor(6, x); // set a color 
           strip.setPixelColor(7, x); // set a color 
           strip.setPixelColor(8, x); // set a color 
           strip.setPixelColor(9, x); // set a color 
           strip.setPixelColor(10, x); // set a color 
           strip.setPixelColor(11, x); // set a color 
           strip.setPixelColor(12, x); // set a color 
           strip.setPixelColor(13, x); // set a color 
           strip.setPixelColor(14, x); // set a color 

           strip.show();
           delay( 10 );
        }

        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(2, f); // set a color 
           strip.setPixelColor(3, f); // set a color 
           strip.setPixelColor(4, f); // set a color 
           
           strip.setPixelColor(1, x); // set a color 
           strip.setPixelColor(5, x); // set a color 
           strip.setPixelColor(6, x); // set a color 
           strip.setPixelColor(7, x); // set a color 
           strip.setPixelColor(8, x); // set a color 
           strip.setPixelColor(9, x); // set a color 
           strip.setPixelColor(10, x); // set a color 
           strip.setPixelColor(11, x); // set a color 
           strip.setPixelColor(12, x); // set a color 
           strip.setPixelColor(13, x); // set a color 
           strip.setPixelColor(14, x); // set a color 

           strip.show();
           delay( 10 );
        }
        
        for( int i = 0; i < strip.numPixels(); i++ ){
           strip.setPixelColor(1, f); // set a color 
           strip.setPixelColor(2, f); // set a color 
           strip.setPixelColor(3, f); // set a color 
           
           strip.setPixelColor(4, x); // set a color 
           strip.setPixelColor(5, x); // set a color 
           strip.setPixelColor(6, x); // set a color 
           strip.setPixelColor(7, x); // set a color 
           strip.setPixelColor(8, x); // set a color 
           strip.setPixelColor(9, x); // set a color 
           strip.setPixelColor(10, x); // set a color 
           strip.setPixelColor(11, x); // set a color 
           strip.setPixelColor(12, x); // set a color 
           strip.setPixelColor(13, x); // set a color 
           strip.setPixelColor(14, x); // set a color 

           strip.show();
           delay( 10 );
        }
    }
}


 /* Calc the sin wave for the breathing color led led */
float breathe(){

  float val = (exp(sin(millis()/800.0*M_PI)) - 0.36787944)*108.0;

  uint16_t i;
  uint32_t c = strip.Color(123, val, 123);
  uint32_t d = strip.Color(val, 100, val);
  uint32_t o = strip.Color(0, 0, 0); //off

  for(i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i, c );
    
  }
  strip.show();

}