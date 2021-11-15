#include "audio.h"
#include <MKL25Z4.h>
#include "cmsis_os2.h"

// int musical_notes[] = {555, 123, 222, 113, 820, 590, 911, 444};

uint32_t test_song[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A5, NOTE_B5, REST};

// uint8_t song_durations[] = {6,  10,  6,  6,  1, 1, 1, 1, 6,  9, 1, 1, 16};

/*looping tune start */
uint32_t looping_tune[] = {NOTE_G4, NOTE_G4, NOTE_E4, NOTE_C4, REST, NOTE_C4, REST, NOTE_E4, REST, NOTE_E4, REST, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_FS4, NOTE_A4,
											NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, REST, NOTE_C4, REST, NOTE_E4, REST, NOTE_E4, REST, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_E4, NOTE_C4};

uint8_t looping_tune_durations[] = {DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, 
											DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP,
											DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, 
											DURATION_GAP, DURATION_GAP, DURATION_GAP};
uint8_t num_looping_notes = 32;
									
																	 
// End Tune: never gonna give you up
uint32_t end_tune[] = {NOTE_F4, NOTE_G4, NOTE_AS4, NOTE_G4, NOTE_D5, NOTE_D5, REST, NOTE_D5, NOTE_D5, REST, NOTE_C5, NOTE_C5, REST, REST, REST, REST,
									NOTE_F4, NOTE_G4, NOTE_AS4, NOTE_G4, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_C5, REST, NOTE_AS5, NOTE_AS5, REST,
									NOTE_F4, NOTE_G4, NOTE_AS4, NOTE_G4, NOTE_AS4, NOTE_AS4, REST, NOTE_C5, NOTE_C5, REST, NOTE_A4, NOTE_A4, REST, NOTE_F4, NOTE_F4, NOTE_C5, NOTE_C5, NOTE_AS4, NOTE_AS4};

uint8_t end_tune_durations[] = {DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP,
																DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP,
																DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP, DURATION_GAP};

uint8_t num_end_notes = 48;

void playToneNote(uint32_t n) {
	if (n == REST) {
		TPM0->MOD = 0;
		TPM0_C2V = 0;
	} else {
		TPM0->MOD = FREQ_2_MOD(n);
		TPM0_C2V = ((FREQ_2_MOD(n))/4);
	}
}

void playSong(uint32_t melody[], uint8_t durations[], uint32_t length){
	for(int i = 0; i < length; i++){
		playToneNote(melody[i]);
		osDelay(TEMPO*durations[i]);
	}
}

void playLoopingTune(void) {
	playSong(looping_tune, looping_tune_durations, num_looping_notes);
}

void playEndingTune(void) {
	playSong(end_tune, end_tune_durations, num_end_notes);
}


void playWifiConnectedSong(void)
{
	TPM0_C2V = 0x0666; // = 1638, half of 3276 -> 50% duty cycle.
  int count = 2;
	while (count--) 
    for (char i = 0; i < 8; i++) {
      TPM0->MOD = FREQ_2_MOD(test_song[i]);
      TPM0_C2V = (FREQ_2_MOD(test_song[i])) / 2;
      delay(0x7FFFF);
    }
    TPM0_C2V++;
    delay(0x7FFFF);
  
	TPM0_C2V = 0;
}

void offSound(void) {
	TPM0->MOD = 0;
	TPM0_C2V = 0;
}
