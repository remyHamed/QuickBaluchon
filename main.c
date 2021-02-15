#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "qrcodegen.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include <stdint.h>
#include "pixel.h"
//gcc *.c -o logIn.exe -I include -L lib -lmingw32 -lSDL2main -lSDL2
//gcc *.c -o logIn.app $(sdl2-config --cflags --libs) -lsdl2_image -lcurl
size_t got_data(char * buffer, size_t itemsize, size_t nitems, void * ignorthis) {
    size_t bytes =  itemsize * nitems;
    int linenumber = 1;
    FILE * f = fopen("docTest.txt", "wb");
    printf("new chunk (%zu bytes)\n", bytes);
    printf("%d:\t", linenumber);
    for (int i = 0; i < bytes; i++) {
        printf("%c", buffer[i]);
        fprintf(f,"%c",buffer[i]);
        if (buffer[i] == '\n') {
            linenumber++;
            printf("%d:\t", linenumber);
        }
    }
    printf("\n\n");
    fclose(f);
    return bytes;
}

int main(int argc, char ** argv) {
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////      SDL_Variable    ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SDL_Surface * drawingSheet;
    Uint32 *pixels;
    size_t i, j;
    int array [60][60]= {{0}};
    int h = 0;
    int w = 0;
    int m;
    int n;
    int count = 0;
    size_t xIndixePixel = 0;
    size_t yIndixePixel = 0;

    drawingSheet = SDL_CreateRGBSurfaceWithFormat(0, 600, 600, 32, SDL_PIXELFORMAT_RGBA8888); 
    int border = 4;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////      CURL_Variable    //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CURL *curl;
    struct curl_slist *headers = NULL;
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////            init librarys       //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SDL_Init(SDL_INIT_VIDEO); // TODO error function

    char* jsonObj = "{ \"id\" : \"alexandre\" , \"pwd\" : \"23\" }"; //TODO this variable must ne init by user
    curl_global_init(CURL_GLOBAL_ALL);// init lib curl
    curl = curl_easy_init(); 
    if (curl == NULL) {
        return 128;
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////      Send data by json    //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charset: utf-8");
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8888/put/put.php");
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonObj);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);
    // perform out action
    CURLcode result = curl_easy_perform(curl);
    if(result != CURLE_OK) {
        fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result));
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////    generate qr code        //////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    bool ok = qrcodegen_encodeText(
    "https://www.google.com/", 
    tempBuffer, 
    qrcode,
    qrcodegen_Ecc_MEDIUM, 
    qrcodegen_VERSION_MIN, 
    qrcodegen_VERSION_MAX, 
    qrcodegen_Mask_AUTO,
    true
    );
    if(ok) {
        int size = qrcodegen_getSize(qrcode);
        for (int y = -border; y < size + border; y++) {
            for (int x = -border; x < size + border; x++) {
                if(qrcodegen_getModule(qrcode, x, y)) {
                    printf("##");
                    array[h][w] = 1;
                    w++;
                    array[h][w] = 1;
                    w++;
                } else {
                    printf("  ");
                    array[h][w] = 0;
                    w++;
                    array[h][w] = 0;
                    w++;
                }
            }
            printf("\n");
            h++;
            w = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////  
    
    SDL_LockSurface(drawingSheet);
    pixels = drawingSheet->pixels;
    for(i = 0; i < 600; i++) {                              // all the surface is in 
        for(j = 0; j < 600; j++) {                          //white
            setPixel(drawingSheet, 0xFF, 0xFF, 0xFF,0xFF, i, j);
        }
    }
    for (m = 0; m < 60; m++) {
        for(n = 0; n < 60; n++) {
            if(array[m][n]) {
                for(size_t q = yIndixePixel; q < 10 + yIndixePixel; q ++) {
                    for(size_t k = xIndixePixel; k < 10 + xIndixePixel; k ++) {
                        setPixel(drawingSheet, 0x0, 0x0, 0x0, 0xFF, k, q);
                    }
                }
                xIndixePixel += 10;
                count++;
            } else {
                xIndixePixel += 10;
                count++;
            }
            if(count == 60) {
                yIndixePixel += 10;
                count  = 0;
            }
        }
        xIndixePixel = 0;
    }
    IMG_SavePNG(drawingSheet, "tr.png");
    SDL_UnlockSurface(drawingSheet);
    SDL_FreeSurface(drawingSheet);
    SDL_Quit();

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return EXIT_SUCCESS;
}
//gcc *.c -o logIn.app $(sdl2-config --cflags --libs) -lsdl2_image -lcurl