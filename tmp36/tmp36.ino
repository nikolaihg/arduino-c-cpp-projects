#define BAUD 9600
#define SENSOR_PIN A3
#define VCC 5.0
#define ADC_MAX 1024.0
#define SAMPLE_DELAY 2500

void setup() {
    Serial.begin(BAUD);
}

void loop() {
    /* 
    Temp (*C) = (V_out - 0.5) * 100
    V_out = (reading from ADC) * (5 / 1024)
    */
    int input = analogRead(SENSOR_PIN);
    float voltage = input * (VCC / ADC_MAX);
    float temp = (voltage - 0.5) * 100;

    Serial.print("Raw ADC: ");
    Serial.print(input);
    Serial.print(" | Voltage: ");
    Serial.print(voltage, 2);
    Serial.print("V | Temperature: ");
    Serial.print(temp, 1);
    Serial.println("°C");
    
    delay(SAMPLE_DELAY);
}