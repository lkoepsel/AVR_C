#include <avr/pgmspace.h>

/*
* offsets required for timer/counters 
* for setting correct parameters for a given note
*/
#define NOTE_B0  0
#define NOTE_C1  1
#define NOTE_CS1 2
#define NOTE_D1  3
#define NOTE_DS1 4
#define NOTE_E1  5
#define NOTE_F1  6
#define NOTE_FS1 7
#define NOTE_G1  8
#define NOTE_GS1 9
#define NOTE_A1  10
#define NOTE_AS1 11
#define NOTE_B1  12
#define NOTE_C2  13
#define NOTE_CS2 14
#define NOTE_D2  15
#define NOTE_DS2 16
#define NOTE_E2  17
#define NOTE_F2  18
#define NOTE_FS2 19
#define NOTE_G2  20
#define NOTE_GS2 21
#define NOTE_A2  22
#define NOTE_AS2 23
#define NOTE_B2  24
#define NOTE_C3  25
#define NOTE_CS3 26
#define NOTE_D3  27
#define NOTE_DS3 28
#define NOTE_E3  29
#define NOTE_F3  30
#define NOTE_FS3 31
#define NOTE_G3  32
#define NOTE_GS3 33
#define NOTE_A3  34
#define NOTE_AS3 35
#define NOTE_B3  36
#define NOTE_C4  37
#define NOTE_CS4 38
#define NOTE_D4  39
#define NOTE_DS4 40
#define NOTE_E4  41
#define NOTE_F4  42
#define NOTE_FS4 43
#define NOTE_G4  44
#define NOTE_GS4 45
#define NOTE_A4  46
#define NOTE_AS4 47
#define NOTE_B4  48
#define NOTE_C5  49
#define NOTE_CS5 50
#define NOTE_D5  51
#define NOTE_DS5 52
#define NOTE_E5  53
#define NOTE_F5  54
#define NOTE_FS5 55
#define NOTE_G5  56
#define NOTE_GS5 57
#define NOTE_A5  58
#define NOTE_AS5 59
#define NOTE_B5  60
#define NOTE_C6  61
#define NOTE_CS6 62
#define NOTE_D6  63
#define NOTE_DS6 64
#define NOTE_E6  65
#define NOTE_F6  66
#define NOTE_FS6 67
#define NOTE_G6  68
#define NOTE_GS6 69
#define NOTE_A6  70
#define NOTE_AS6 71
#define NOTE_B6  72
#define NOTE_C7  73
#define NOTE_CS7 74
#define NOTE_D7  75
#define NOTE_DS7 76
#define NOTE_E7  77
#define NOTE_F7  78
#define NOTE_FS7 79
#define NOTE_G7  80
#define NOTE_GS7 81
#define NOTE_A7  82
#define NOTE_AS7 83
#define NOTE_B7  84
#define NOTE_C8  85
#define NOTE_CS8 86
#define NOTE_D8  87
#define NOTE_DS8 88

/*
* frequencies for each note, freq = x per sec
* so can be used to time duration of note
*/
const uint16_t notes_freq[89] PROGMEM = {
	31,
	33,
	35,
	37,
	39,
	41,
	44,
	46,
	49,
	52,
	55,
	58,
	62,
	65,
	69,
	73,
	78,
	82,
	87,
	93,
	98,
	104,
	110,
	117,
	123,
	131,
	139,
	147,
	156,
	165,
	175,
	185,
	196,
	208,
	220,
	233,
	247,
	262,
	277,
	294,
	311,
	330,
	349,
	370,
	392,
	415,
	440,
	466,
	494,
	523,
	554,
	587,
	622,
	659,
	698,
	740,
	784,
	831,
	880,
	932,
	988,
	1047,
	1109,
	1175,
	1245,
	1319,
	1397,
	1480,
	1568,
	1661,
	1760,
	1865,
	1976,
	2093,
	2217,
	2349,
	2489,
	2637,
	2794,
	2960,
	3136,
	3322,
	3520,
	3729,
	3951,
	4186,
	4435,
	4699,
	4978
};

/*
* scalars required for timer/counter 1
* for setting correct parameters for a given note
*/
const uint8_t notes_TCCR1B[89] PROGMEM = {
	0x14,
	0x14,
	0x14,
	0x14,
	0x14,
	0x14,
	0x14,
	0x14,
	0x14,
	0x14,
	0x14,
	0x14,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x13,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12,
	0x12
} ;

/*
* counter value required for timer/counter 1
* for setting correct parameters for a given note
*/
const uint16_t notes_OCR1A[89] PROGMEM = {
	504,
	473,
	446,
	422,
	401,
	381,
	355,
	340,
	319,
	300,
	284,
	269,
	1008,
	962,
	906,
	856,
	801,
	762,
	718,
	672,
	638,
	601,
	568,
	534,
	508,
	477,
	450,
	425,
	401,
	379,
	357,
	338,
	319,
	300,
	284,
	268,
	253,
	239,
	226,
	213,
	201,
	189,
	179,
	169,
	159,
	151,
	142,
	134,
	1012,
	956,
	903,
	852,
	804,
	759,
	716,
	676,
	638,
	602,
	568,
	536,
	506,
	478,
	451,
	426,
	402,
	379,
	358,
	338,
	319,
	301,
	284,
	268,
	253,
	239,
	226,
	213,
	201,
	190,
	179,
	169,
	159,
	151,
	142,
	134,
	127,
	119,
	113,
	106,
	100
};

/*
* scalars required for timer/counter 0
* for setting correct parameters for a given note
*/
const uint8_t notes_TCCR0B[89] PROGMEM = {
	0x0D,
	0x0D,
	0x0D,
	0x0D,
	0x0D,
	0x0D,
	0x0D,
	0x0D,
	0x0D,
	0x0D,
	0x0D,
	0x0D,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0C,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0B,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A,
	0x0A
} ;

/*
* counter value required for timer/counter 0
* for setting correct parameters for a given note
*/
const uint8_t notes_OCR0A[89] PROGMEM = {
	126,
	118,
	112,
	106,
	100,
	95,
	89,
	85,
	80,
	75,
	71,
	67,
	252,
	240,
	226,
	214,
	200,
	191,
	180,
	168,
	159,
	150,
	142,
	134,
	127,
	119,
	112,
	106,
	100,
	95,
	89,
	84,
	80,
	75,
	71,
	67,
	253,
	239,
	226,
	213,
	201,
	189,
	179,
	169,
	159,
	151,
	142,
	134,
	127,
	120,
	113,
	106,
	100,
	95,
	90,
	84,
	80,
	75,
	71,
	67,
	63,
	60,
	56,
	53,
	50,
	47,
	45,
	42,
	40,
	38,
	36,
	34,
	253,
	239,
	226,
	213,
	201,
	190,
	179,
	169,
	159,
	151,
	142,
	134,
	127,
	119,
	113,
	106,
	100
};