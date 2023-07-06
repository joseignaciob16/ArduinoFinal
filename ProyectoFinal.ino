#include <LiquidCrystal.h>  // Incluye la biblioteca LiquidCrystal para controlar la pantalla LCD
#include <DHT.h>  // Incluye la biblioteca DHT para trabajar con el sensor DHT

#define DHTPIN 2  // Define el pin digital al que está conectado el sensor DHT
#define DHTTYPE DHT11  // Define el tipo de sensor DHT

DHT dht(DHTPIN, DHTTYPE);  // Crea una instancia del sensor DHT
const int MQ135_PIN = A0;  // Define el pin analógico al que está conectado el sensor MQ135

int LEDAZUL = 7;  // Define el pin digital para el LED azul
int LEDROJO = 6;  // Define el pin digital para el LED rojo

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);  // Crea una instancia del objeto LiquidCrystal para controlar la pantalla LCD

void setup() {
  Serial.begin(9600);  // Inicia la comunicación serial a una velocidad de 9600 baudios
  lcd.begin(16, 2);  // Inicializa la pantalla LCD con 16 columnas y 2 filas
  dht.begin();  // Inicializa el sensor DHT
  pinMode(LEDAZUL, OUTPUT);  // Configura el pin del LED azul como salida
  pinMode(LEDROJO, OUTPUT);  // Configura el pin del LED rojo como salida
}

void loop() {
  float temperatura = dht.readTemperature();  // Lee la temperatura del sensor DHT y la almacena en la variable 'temperatura'
  float humedad = dht.readHumidity();  // Lee la humedad del sensor DHT y la almacena en la variable 'humedad'

  int aire = analogRead(MQ135_PIN)+140;  // Lee el valor analógico del sensor MQ135 y lo almacena en la variable 'aire'

  lcd.clear();  // Borra el contenido de la pantalla LCD
  lcd.setCursor(2, 0);  // Establece la posición del cursor en la columna 2, fila 0
  lcd.print("TEMPERATURA:");  // Imprime el texto "TEMPERATURA:"
  lcd.setCursor(5, 1);  // Establece la posición del cursor en la columna 5, fila 1
  lcd.print(temperatura);  // Imprime el valor de la temperatura en grados Celsius
  lcd.print("C");  // Imprime la unidad de temperatura (grados Celsius)

  delay(2000);  // Espera 2 segundos

  lcd.clear();  // Borra el contenido de la pantalla LCD
  lcd.setCursor(4, 0);  // Establece la posición del cursor en la columna 4, fila 0
  lcd.print("HUMEDAD:");  // Imprime el texto "HUMEDAD:"
  lcd.setCursor(5, 1);  // Establece la posición del cursor en la columna 5, fila 1
  lcd.print(humedad);  // Imprime el valor de la humedad en porcentaje
  lcd.print("%");  // Imprime el símbolo de porcentaje

  delay(2000);  // Espera 2 segundos

    lcd.clear();  // Borra el contenido de la pantalla LCD
  lcd.setCursor(4, 0);  // Establece la posición del cursor en la columna 6, fila 0
  lcd.print("AIRE:");  // Imprime el texto "AIRE:"
  lcd.setCursor(3, 1);  // Establece la posición del cursor en la columna 7, fila 1
  lcd.print(aire);  // Imprime el valor del aire
  lcd.setCursor(7, 1);  // Establece la posición del cursor en la columna 7, fila 1
  lcd.print("ppm");  // Imprime el valor del aire

  delay(2000);  // Espera 2 segundos

  lcd.clear();  // Borra el contenido de la pantalla LCD
  lcd.setCursor(3, 0);  // Establece la posición del cursor en la columna 3, fila 0
  lcd.print("INFORME DE");  // Imprime el texto "INFORME DE"
  lcd.setCursor(4, 1);  // Establece la posición del cursor en la columna 4, fila 1
  lcd.print("AMBIENTE");  // Imprime el texto "AMBIENTE"

  delay(2000);  // Espera 2 segundos

  if (temperatura > 18 && temperatura < 30) {  // Comprueba si la temperatura está en el rango óptimo
    digitalWrite(LEDROJO, LOW);  // Apaga el LED rojo
    digitalWrite(LEDAZUL, HIGH);  // Enciende el LED azul
    lcd.clear();  // Borra el contenido de la pantalla LCD
    lcd.setCursor(2, 0);  // Establece la posición del cursor en la columna 2, fila 0
    lcd.print("TEMPERATURA:");  // Imprime el texto "TEMPERATURA:"
    lcd.setCursor(5, 1);  // Establece la posición del cursor en la columna 5, fila 1
    lcd.print("OPTIMA");  // Imprime el texto "OPTIMA"
    delay(5000);  // Espera 5 segundos
  } else {
    digitalWrite(LEDAZUL, LOW);  // Apaga el LED azul
    digitalWrite(LEDROJO, HIGH);  // Enciende el LED rojo
    lcd.clear();  // Borra el contenido de la pantalla LCD
    lcd.setCursor(2, 0);  // Establece la posición del cursor en la columna 2, fila 0
    lcd.print("TEMPERATURA:");  // Imprime el texto "TEMPERATURA:"
    lcd.setCursor(3, 1);  // Establece la posición del cursor en la columna 3, fila 1
    lcd.print("NO OPTIMA");  // Imprime el texto "NO OPTIMA"
    delay(5000);  // Espera 5 segundos
  }

  if (humedad > 30) {  // Comprueba si la humedad está en el rango óptimo
    digitalWrite(LEDROJO, LOW);  // Apaga el LED rojo
    digitalWrite(LEDAZUL, HIGH);  // Enciende el LED azul
    lcd.clear();  // Borra el contenido de la pantalla LCD
    lcd.setCursor(3, 0);  // Establece la posición del cursor en la columna 3, fila 0
    lcd.print("HUMEDAD:");  // Imprime el texto "HUMEDAD:"
    lcd.setCursor(4, 1);  // Establece la posición del cursor en la columna 4, fila 1
    lcd.print("OPTIMA");  // Imprime el texto "OPTIMA"
    delay(5000);  // Espera 5 segundos
  } else {
    digitalWrite(LEDROJO, HIGH);  // Enciende el LED rojo
    digitalWrite(LEDAZUL, LOW);  // Apaga el LED azul
    lcd.clear();  // Borra el contenido de la pantalla LCD
    lcd.setCursor(4, 0);  // Establece la posición del cursor en la columna 4, fila 0
    lcd.print("HUMEDAD:");  // Imprime el texto "HUMEDAD:"
    lcd.setCursor(3, 1);  // Establece la posición del cursor en la columna 3, fila 1
    lcd.print("NO OPTIMA");  // Imprime el texto "NO OPTIMA"
    delay(5000);  // Espera 5 segundos
  }

  if (aire < 450) {  // Comprueba si la calidad del aire está en el rango aceptable
    digitalWrite(LEDAZUL, HIGH);  // Enciende el LED azul
    digitalWrite(LEDROJO, LOW);  // Apaga el LED rojo
    lcd.clear();  // Borra el contenido de la pantalla LCD
    lcd.setCursor(2, 0);  // Establece la posición del cursor en la columna 2, fila 0
    lcd.print("CALIDAD AIRE:");  // Imprime el texto "CALIDAD AIRE:"
    lcd.setCursor(4, 1);  // Establece la posición del cursor en la columna 4, fila 1
    lcd.print("ACEPTABLE");  // Imprime el texto "ACEPTABLE"
    delay(5000);  // Espera 5 segundos
  } else {
    digitalWrite(LEDROJO, HIGH);  // Enciende el LED rojo
    digitalWrite(LEDAZUL, LOW);  // Apaga el LED azul
    lcd.clear();  // Borra el contenido de la pantalla LCD
    lcd.setCursor(2, 0);  // Establece la posición del cursor en la columna 2, fila 0
    lcd.print("CALIDAD AIRE:");  // Imprime el texto "CALIDAD AIRE:"
    lcd.setCursor(4, 1);  // Establece la posición del cursor en la columna 4, fila 1
    lcd.print("PELIGROSO");  // Imprime el texto "PELIGROSO"
    delay(5000);  // Espera 5 segundos
  }

  digitalWrite(LEDAZUL, LOW);  // Apaga el LED azul
  digitalWrite(LEDROJO, LOW); // Apaga el LED rojo

}
