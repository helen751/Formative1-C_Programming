#define TRIG_PIN 11
#define ECHO_PIN 9

const int red_LED = 6;
const int green_LED = 5;
const int buzzer = 3;

int distance_threshold = 50;

long duration;
float distance;

void setup()
{
    //the pinmode set to the type of device connected to each pin
    pinMode(red_LED, OUTPUT);
    pinMode(green_LED, OUTPUT);
    pinMode(buzzer, OUTPUT);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop()
{
    // Making sure the trigger pin starts LOW
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    // Sending a 10-microsecond sound pulse
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measuring how long the echo takes to return
    duration = pulseIn(ECHO_PIN, HIGH);

    // Converting the time into distance in cm
    distance = duration * 0.0343 / 2.0;

    if(distance <= distance_threshold){
        digitalWrite(buzzer, HIGH);
        digitalWrite(green_LED, LOW);
        digitalWrite(red_LED, HIGH);
    }
    else{
        digitalWrite(buzzer, LOW);
        digitalWrite(green_LED, HIGH);
        digitalWrite(red_LED, LOW);
    }
    delay(200);
}