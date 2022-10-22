#define CNFG_IMPLEMENTATION
#define CNFGOGL
#define HAS_XSHAPE
#define HAS_XINERAMA

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "include/rawdraw_sf.h"

#define BLINKTIME   15

//states
bool blinking = false;
typedef enum {
    closed,AEI,O,Ee,CDGKNSTXYZ,QW,BMP,L,FV,ChJSH,R,TH
} mouthstate;

mouthstate mouth = closed;
int mx, my;

void DrawMouthA( int x, int y ) {
    
    RDPoint lips[4]={{x+27,y+70},{x+69,y+70},{x+60,y+87},{x+37,y+87}};
    RDPoint hole[4]={{x+32,y+72},{x+64,y+72},{x+58,y+84},{x+37,y+84}};
    
    CNFGColor(0x644e4eff);
    CNFGTackPoly(lips, 4);
    
    CNFGColor(0x000000ff);
    CNFGTackPoly(hole,4);
    
    CNFGColor(0xffffffff);
    CNFGTackRectangle(x+38,y+73,x+58,y+75);//teeth
    
    CNFGColor(0xff0000ff);
    CNFGTackRectangle(x+42,y+80,x+54,y+83);//tongue
    
    
}

void DrawMouth(int x, int y){
    switch(mouth){
        case closed: break;
        case AEI:
        {
            DrawMouthA(x,y);
            break;
        }
    }
}
void DrawPupil(int xcen, int ycen) {
    RDPoint pupil[6]={{xcen,ycen},{xcen,ycen+2},{xcen-3,ycen+ 2},{xcen-2, ycen - 1},{xcen, ycen - 3},{xcen + 3, ycen - 2}};
    CNFGColor(0xffffffff);
    CNFGTackPoly(pupil, 6);
}

void DrawPupils( int x, int y ) {
    DrawPupil(x + 29, y + 37);
    DrawPupil(x + 71, y + 37);
}

void DrawFigure( int x, int y, size_t tick ) {
    
    srand(tick);
    for(int r = 0; r<115; r++) {
        int numx = (rand() % 100);
        int numy = (rand() % 100);
        CNFGColor(0xffffffff);
        CNFGTackPixel(x + numx, y + numy);
        
    }
    srand(tick+2);
    for(int r = 0; r<150; r++) {
        int numx = (rand() % 100);
        int numy = (rand() % 100);
        CNFGColor(0xff0000ff);
        CNFGTackPixel(x + numx, y + numy);
    }
    
    CNFGColor(0x000000ff);
    RDPoint uplef[3] = {{x,y},{x+25,y},{x,y+30}}; 
    RDPoint uprig[3] = {{x+75,y},{x+100,y},{x+100,y+30}}; 
    RDPoint botlef[3] = {{x,y + 75},{x,y + 100},{x + 25,y+100}}; 
    RDPoint botrig[3] = {{x + 75,y + 100},{x+100,y + 75},{x + 100,y+100}};
    CNFGTackPoly( uplef, 3 );
    CNFGTackPoly( uprig, 3 );
    CNFGTackPoly( botlef, 3 );
    CNFGTackPoly( botrig, 3 );
    CNFGTackRectangle(x + 15,y+30,x+43,y+45 );
    CNFGTackRectangle(x + 57,y+30,x+85,y+45 );
    if(!blinking)  DrawPupils( x, y );
    DrawMouth(x,y);     
    //CNFGColor(0xffffffff);
    //CNFGTackPixel(x +  numx, y + numy);
}
void HandleKey( int keycode, int bDown ) {
    if( keycode == 65307 ) exit( 0 );
    if( keycode == 97 ) mouth = AEI;
    if( keycode == 99 ) mouth = closed;
    printf( "Key: %d -> %d\n", keycode, bDown );
}
void HandleButton( int x, int y, int button, int bDown ) {
    if ( button == 1) blinking = true;
}
void HandleMotion( int x, int y, int mask ) {
    mx = x;
    my = y;
    
} 
void HandleDestroy() { }
int main()
{ 
    size_t tick; 
    CNFGSetup( "10011001", 1024, 768 );
    int blinkcount = 0;
    char **buf;
    int buflen;
    while(CNFGHandleInput())
    {
        tick++;
        CNFGBGColor = 0xff; //Black Background
        short w, h;
        CNFGClearFrame();
        CNFGGetDimensions( &w, &h );
        
        if(blinking) blinkcount++;
        if (blinkcount > BLINKTIME) {
            blinking = false;
            blinkcount = 0;
        }
        
        DrawFigure(mx,my,tick);
        
        //Display the image and wait for time to display next frame.
        CNFGSwapBuffers();
        
        //usleep(100000);
    }
    
    
}

