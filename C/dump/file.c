#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAGIC_NUM_BYTES 16
#define TOTAL_TYPES 10

typedef struct {
	char* name;
	size_t magic_size;
	char* magic_num;
} file;

char JPEG[] = {0xFF, 0xD8, 0xFF};
char PNG[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
char ELF[] = {0x7F, 0x45, 0x4C, 0x46};
char PDF[] = {0x25, 0x50, 0x44, 0x46};
char ZIP[] = {0x50, 0x4B, 0x03, 0x04};
char MP3[] = {0x49, 0x44, 0x33};
char MP4[] = {0x00, 0x00, 0x00, 0x18, 0x66, 0x74, 0x79, 0x70};
char MOV[] = {0x00, 0x00, 0x00, 0x14, 0x66, 0x74, 0x79, 0x70};
char GZIP[] = {0x1F, 0x8B};
char WAV[] = {0x52, 0x49, 0x46, 0x46};

file types[] = {
	{"jpeg", sizeof JPEG, JPEG},
	{"png", sizeof PNG, PNG},
	{"elf", sizeof ELF, ELF},
	{"pdf", sizeof PDF, PDF},
	{"zip", sizeof ZIP, ZIP},
	{"mp3", sizeof MP3, MP3},
	{"mp4", sizeof MP4, MP4},
	{"mov", sizeof MOV, MOV},
	{"gzip", sizeof GZIP, GZIP},
	{"wav", sizeof WAV, WAV},
};

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}
	char* filename = argv[1];
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) {
		perror("fopen");
		printf("can't open file: \"%s\"\n", filename);
		return EXIT_FAILURE;
	}
	char magicNumber[MAGIC_NUM_BYTES] = {0};
	fread(magicNumber, 1, MAGIC_NUM_BYTES, fp);
	int found = false;
	for (unsigned int i = 0; i < TOTAL_TYPES; i++) {
		if (memcmp(magicNumber, types[i].magic_num, types[i].magic_size) == 0) {
			printf("file is %s\n", types[i].name);
			found = true;
			break;
		}
	}
	if (!found)
		printf("Filetype not found\n");
	fclose(fp);
	return 0;
}
