/*
 * Basic Arduino Template - Blink
 * ------------------------------
 * Blinks an LED connected to pin 13, once per second.
 *
 * Wiring: plug the LED straight into the top header of the UNO.
 *   - long leg  (+, anode)   -> pin 13
 *   - short leg (-, cathode) -> GND (right next to pin 13)
 *   (a 220 ohm resistor in series is the safer habit for LEDs)
 * The UNO's built-in "L" LED is also on pin 13, so it blinks too.
 *
 *              _____
 *             /     \
 *             | LED |
 *             |_____|
 *              |   |
 *          (-) |   | (+)
 *       short  |   |  long leg
 *   +----------|---|--------------------------------+
 *   |  AREF  GND  13   12   11   10    9    8      |
 *   |                                               |
 *   |  [USB]          ARDUINO UNO                   |
 *   |                                               |
 *   |  [PWR]                                        |
 *   +-----------------------------------------------+
 *
 * Every Arduino sketch has two required functions:
 *   setup() -> runs ONCE when the board powers on or is reset
 *   loop()  -> runs AGAIN AND AGAIN, forever, after setup() finishes
 *
 * In PlatformIO (unlike the Arduino IDE) we must include Arduino.h
 * ourselves. It gives us pinMode(), digitalWrite(), delay(), etc.
 */
#include <Arduino.h>
#include <TM1637Display.h>

// Ligacoes do Grove 4-Digit Display
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

// Tempo inicial: 5 minutos
int minutos = 5;
int segundos = 0;

unsigned long tempoAnterior = 0;

void setup() {
    display.setBrightness(7);
    display.clear();

    // Mostrar 05:00 ao iniciar
    display.showNumberDecEx(500, 0b01000000, true);
}

void loop() {

    unsigned long tempoAtual = millis();

    // Atualizar a cada segundo
    if (tempoAtual - tempoAnterior >= 1000) {
        tempoAnterior += 1000;

        // Contagem decrescente
        if (minutos > 0 || segundos > 0) {

            if (segundos == 0) {
                minutos--;
                segundos = 59;
            } else {
                segundos--;
            }
        }
    }

    // Mostrar MM:SS
    int numero = minutos * 100 + segundos;

    display.showNumberDecEx(
        numero,
        0b01000000,
        true
    );
}