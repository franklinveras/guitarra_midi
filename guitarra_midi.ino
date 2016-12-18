/*
	Guitarra MIDI com Arduino
	Criado em: 17 de dezembro de 2016
	Autor: Franklin Véras Sertão
*/

byte pino [6] = {3,5,7,9,11,13};
boolean estado [6] = {false,false,false,false,false,false};
byte nota [6] = {69,67,65,64,62,60}; //Lá, Sol, Fá, Mi, Ré, Dó

void setup() {

	for (int i = 0; i<6; i++) {
		pinMode(pino[i], INPUT);
	}

	Serial.begin(115200); // Para conexão direta com um instrumento MIDI utilizar 38400

}


void MIDI_TX(byte MESSAGE, byte PITCH, byte VELOCITY) {
	byte status1 = MESSAGE;
	Serial.write(status1);
	Serial.write(PITCH);
	Serial.write(VELOCITY);
}

void loop() {
	for (byte i = 0; i<6; i++) {
		byte vel = 0;
		boolean leitura = digitalRead(pino[i]);
		
		if (leitura != estado[i]) {
			estado[i] = leitura;
			vel = (estado[i])?127:0;
			MIDI_TX(144, nota[i], vel); // Mensagem 144 - Note ON Ch.01
		}

	}

}
