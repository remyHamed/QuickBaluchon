/* 
 * QR Code generator demo (C)
 * 
 * Run this command-line program with no arguments. The program
 * computes a demonstration QR Codes and print it to the console.
 * 
 * Copyright (c) Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/qr-code-generator-library
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * - The Software is provided "as is", without warranty of any kind, express or
 *   implied, including but not limited to the warranties of merchantability,
 *   fitness for a particular purpose and noninfringement. In no event shall the
 *   authors or copyright holders be liable for any claim, damages or other
 *   liability, whether in an action of contract, tort or otherwise, arising from,
 *   out of or in connection with the Software or the use or other dealings in the
 *   Software.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qrcodegen.h"
#include <SDL.h>
#define WINDOW_WIDTH (600)
#define WINDOW_HEIGHT (600)
// Function prototypes
static void doVarietyDemo(void);
static void printQr(const uint8_t qrcode[]);
// The main application program.
int main(int argc, char  ** argv) {
	SDL_Window * win = NULL;
    SDL_Renderer * renderer = NULL;
	int finish  = 0;
	SDL_Init(SDL_INIT_VIDEO); // TODO error function
	win  = SDL_CreateWindow("QRcode generator",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT,0);//TODO error function
	renderer = SDL_CreateRenderer(win, -1,SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	while (!finish) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                finish = 1;
            }
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                       
                    }
                break;
            }
			uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
			uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
			bool ok = qrcodegen_encodeText("314159265358979323846264338327950288419716939937510", tempBuffer, qrcode,
				qrcodegen_Ecc_MEDIUM, qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
			if (ok)
				printQr(qrcode);
        }
        //SDL_RenderClear(renderer);
	}
	doVarietyDemo();
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
	SDL_Quit();
	return EXIT_SUCCESS;
}
/*---- Demo suite ----*/
// Creates a variety of QR Codes that exercise different features of the library, and prints each one to the console.
static void doVarietyDemo(void) {
	{  // Numeric mode encoding (3.33 bits per digit)
		uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
		uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
		bool ok = qrcodegen_encodeText("314159265358979323846264338327950288419716939937510", tempBuffer, qrcode,
			qrcodegen_Ecc_MEDIUM, qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
		if (ok)
			printQr(qrcode);
	}
}
/*---- Utilities ----*/
// Prints the given QR Code to the console.
static void printQr(const uint8_t qrcode[]) {
	int size = qrcodegen_getSize(qrcode);
	int border = 4;
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
	fputs("\n", stdout);
}

static void printQrSDL(const uint8_t qrcode[]) {
	int size = qrcodegen_getSize(qrcode);
	int border = 4;
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
	fputs("\n", stdout);
}

void printDarkRect() {
	
}