long readVcc() {
  long result; // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC);
  // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float VCC = float(readVcc())/1000;
  
  char buffer_akku[20];
  char floatString[4];
  // 1: variable to convert, 2: number of digits, 3: number of digits after decimal, 4: buffer
  dtostrf(VCC,2,1,floatString);

  sprintf(buffer_akku, "Akku: %sV", floatString);
  Serial.println(buffer_akku);
  //Serial.println(readVcc()/1000);
  delay(1000);
}
