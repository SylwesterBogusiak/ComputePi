
/*

 * BRESPI - BRESENHAM AND PI CIRCLES IN COLOURS OF R G B
 * This app is drawing 9 circles in 2 different techniques.
 * First circle in RED color is drawn with Bresenham's method
 * Second BLUE circle in drawn with use Pi number and sin() and cos() functions from math library or written with use Taylor-Maclaurin series, 
 * matched pixels only from this procedure are visible in GREEN, some other pixels are in WHITE.
 *
 * Program is working in graphical mode from 320x200 pixels known from DOS time as 13h up to 1920x1080 pixels
 * The aim of this app is to see by eye layout of pixels which drawing these circles
 *
 * Golden Pi number = 3.1416407865 and GOLDEN MEAN and Fibonacci numbers and Golden number Phi=1.618033 are connected
 *
 * Author: MARTE.BEST - Sylwester Bogusiak
 *
 *
 * Golden Pi number = 3.1416407865 and GOLDEN MEAN and Fibonacci numbers and Golden number Phi=1.618033 are connected
 *
 * Author: MARTE.BEST - Sylwester Bogusiak
 *
 * This program is using Allegro 4.2 library, by Shawn Hargreaves.
 * This is free code.
 * There is no warranty or guarantee of any kind.
 * The Allegro and math library has further restrictions.
 *
 * To Compile:
 * gcc -o brespi brespi.c -lalleg -lm
 * Usage in command line:
 * ./brespi
 */

// NOTE!!! My results from FCPI algo - Fast Fibonacci compute Pi
// ~/Programming/cmd/mpfr/fcpi - fast Fibonacci compute pi$ ./fcpi 1000000000
// For f(1000000000) Pi = 3.14164078649987381784550420123876574126437101576691543456253834724631255538268293964864864502726936498170490569046427010255196063466824431815181607292007162532006690391512749948676598719358391394832145681025052027100205403544843866525185952345835155557633732577971044146440896706554534569909542283443878e0
// Your calculations took 4.00 seconds to run.


//Taylor Sin Cos info:
//Taylor series for sine or sinus
//https://dotancohen.com/eng/taylor-sine.php

#include <allegro.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>


#define BLACK makecol(0,0,0)
#define RED makecol(255,0,0)
#define GREEN makecol(0,255,0)
#define BLUE makecol(0,0,255)
#define CLEAR makecol(255,0,255)
#define GREY makecol(127,127,127)
#define WHITE makecol(255,255,255)

time_t t;


    BITMAP * back_screen=NULL;

    int SCREEN_w;
    int SCREEN_h;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                 SHOW WELCOME SCREEN


int show_welcome_screen()
{
    textout_centre_ex(back_screen, font, " Welcome to BRESPI APP 0.2 (Beta).", SCREEN_w/2, 10, BLACK, -1);
    textout_centre_ex(back_screen, font, " Bresenham and Pi method to draw  ", SCREEN_w/2, 20, BLACK, -1);
    textout_centre_ex(back_screen, font, " circles in selected graphic mode.", SCREEN_w/2, 30, BLACK, -1);
    textout_centre_ex(back_screen, font, " ", 5, 40, BLACK, -1);
    textout_centre_ex(back_screen, font, " Golden Pi = 3.14164078649987381...", SCREEN_w/2, 40, BLACK, -1);
    textout_centre_ex(back_screen, font, " Canonical Pi = 3.14159265358979...", SCREEN_w/2, 50, BLACK, -1);
    textout_centre_ex(back_screen, font, "  Mid Pi =(Golden Pi + Can Pi)/2   ", SCREEN_w/2, 60, BLACK, -1);

    textout_centre_ex(back_screen, font, "                                   ", SCREEN_w/2, 70, BLACK, -1);
    textout_centre_ex(back_screen, font, "  sin() and cos() from math lib    ", SCREEN_w/2, 80, BLACK, -1);
    textout_centre_ex(back_screen, font, "   or as Taylor Maclaurin series   ", SCREEN_w/2, 90, BLACK, -1);
    textout_centre_ex(back_screen, font, "                                   ", SCREEN_w/2, 100, BLACK, -1);
    textout_centre_ex(back_screen, font, "    It's little bit of math.       ", SCREEN_w/2, 110, BLACK, -1);
    textout_centre_ex(back_screen, font, "       Hope You enjoy it.          ", SCREEN_w/2, 120, BLACK, -1);




    textout_centre_ex(back_screen, font, "      Please press space.          ", SCREEN_w/2, 130, BLACK, -1);
    textout_centre_ex(back_screen, font, "   Author: MARTE.BEST 2024 AD      ", SCREEN_w/2, 150, BLACK, -1);

    textout_centre_ex(back_screen, font, "    Using Allegro 4.2 library      ", SCREEN_w/2, 160, BLACK, -1);

    masked_stretch_blit(back_screen, screen, 0, 0, SCREEN_w, SCREEN_h, 0, 0, SCREEN_W, SCREEN_H);

    while(!(key[KEY_SPACE]));
    usleep(200000);

    return 0;


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                 strcmp_no_case


	/* works lik strcmp, but ignores case */
	//int strcmp_no_case(const char*lhs, const char*rhs);

		/* works lik strcmp, but ignores case */
int strcmp_no_case(const char*lhs, const char*rhs) {
	    char v;
	    while (*lhs && *rhs)
	    {
	        v = utolower(*lhs) - utolower(*rhs);
	        if (v)
	           return v;

	        ++lhs;
	        ++rhs;
	    }
	    if (*lhs)
	       return 1;

	    if (*rhs)
	        return -1;
	        	    return 0;
}

int create_brespi_config_file()
{

return 0;


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                 load_config

int load_config()
{
    int w = 800,h = 600,bpp = 24;
    int windowed = GFX_AUTODETECT_WINDOWED;
    int count;
    char **data;

    char *title;

    /* save the current ini file, then set the program specific one */

    push_config_state();

    if (create_brespi_config_file() !=0)
    {

    windowed = GFX_AUTODETECT_WINDOWED;
    title = "BRESPI by MARTE.BEST";
    w = 800;
    h = 600;
    bpp = 24;
    }
    else
    {

    set_config_file("brespi.ini");

    /* the gfx mode is stored like this:
    *    640  480 16
    * the get_config_argv() function returns a pointer to a char
    * array, and stores the size of the char array in an int
    */

    data = get_config_argv("graphics", "mode", &count);
    if (count != 3)
    {
    /* We expect only 3 parameters */

    allegro_message("Found %i parameters in graphics mode instead of the 3 expected.", count);


    allegro_exit();
    }
    else
    {
    w = atoi(data[0]);
    h = atoi(data[1]);
    bpp = atoi(data[2]);
    }

    /* Should we use a windowed mode?
    * In the config file this is stored as either FALSE or TRUE.
    * So we need to read a string and see what it contains.
    * If the entry is not found, we use "FALSE" by default
    */

    windowed = GFX_AUTODETECT_WINDOWED;
    if (strcmp_no_case(get_config_string("graphics", "windowed", "FALSE"), "FALSE") == 0)
    {
    windowed = GFX_AUTODETECT_FULLSCREEN;
    }

    else
    {
    windowed = GFX_AUTODETECT_WINDOWED;
    }

    /* the title string
    * The string returned is stored inside of the config system
    * and would be lost if we call pop_config_state(), so we create
    * a copy of it.
    */
    title = ustrdup(get_config_string("content", "headline", "<no headline>"));

    /* restore the old config file */
    pop_config_state();
    };


    set_color_depth(bpp);


    if (set_gfx_mode(windowed, w, h, 0, 0) != 0)
	{


	allegro_message("Can't set this graphics mode!");


	allegro_exit();

    }

    if (set_display_switch_mode(SWITCH_BACKGROUND)==-1)
    {
    set_display_switch_mode(SWITCH_PAUSE);
    }


    set_window_title(title);

    /* mandatory for screen_buffer resize and elements size */

    SCREEN_w = 320;
    SCREEN_h = 200;


    return 0;

} // load_config()



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// factorial

// recursive factorial
long double fact(long long int n) {

   if (n == 0 || n == 1) return 1;

   return n * fact(n - 1);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// taylor_sin()

// Function for compute sin(x) from Taylor(Maclaurin) series up to 21 is 2Pi radians
/*
    sin(x) = x - (x^3)/3! + (x^5)/5! - (x^7)/7! .......
*/

long double taylor_sin(double x)
{

long long int i,n;
double p;
double sin, temp=1;

n=1;

for(i=1;i<=21;i++)
{

p = pow(x,n);
temp = temp - ((1/(fact(n))) * p);
n=n+2;

p = pow(x,n);
temp = temp + ((1/(fact(n))) * p);
n=n+2;


}

sin = temp;


return sin; //sin;

}

// Function for compute cos(x) from Taylor(Maclaurin) series for 21 is 2 Pi radians 360 degrees
/*
    cos(x) = 1 - (x^2)/2! + (x^4)/4! - (x^6)/6! .......
*/
long double taylor_cos(double x)
{

long long int i,n;
double p;
double cos, temp=1;

n=2;

for(i=1;i<=21;i++)
{

p = pow(x,n);
temp = temp - ((1/(fact(n))) * p);
n=n+2;

p = pow(x,n);
temp = temp + ((1/(fact(n))) * p);
n=n+2;


}

cos = temp;


return cos; //cos;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// bres_circle()

// Function for circle-generation using Bresenham's algorithm

int bres_circle(long double xc,long double yc, long double scr_x, long double scr_y, long double zoom)
{


    int c, i, color;
    long double r, ZOOM;
    long double x, y, err; /* II. Quadrant */
    c = 1.0;

for (i=1;i<=9;i++)  // 9 circles
{
 ZOOM = zoom*i;       // bigger circle

 r=c*ZOOM;

   x = -r;
   err = 2-2*r;
   y = 0;
   do {

    color = RED;

      putpixel(back_screen, xc-x+scr_x, yc+y+scr_y, color); /*   I. Quadrant */
      putpixel(back_screen, xc-y+scr_x, yc-x+scr_y, color); /*  II. Quadrant */
      putpixel(back_screen, xc+x+scr_x, yc-y+scr_y, color); /* III. Quadrant */
      putpixel(back_screen, xc+y+scr_x, yc+x+scr_y, color); /*  IV. Quadrant */
      r = err;
      if (r <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
      if (r > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
   } while (x < 0);

}
return 0;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// pi_circle() sin cos

int pi_circle_0(long double xc,long double yc, long double scr_x, long double scr_y, long double zoom, long double pi)
{

long double c, x,y,r, theta;
int i;
long double ti, ZOOM;
int color;
c=1.0;

int angle;

for (i=1;i<=9;i++)  // 9 circles
{

ZOOM = zoom*i;           // bigger circle
r=c*ZOOM;
    for(angle=0;angle<=360; angle++) //draw the circle of full 360 degrees angle

 {

    theta=(long double)(angle/180.0)*pi;

    x = xc + (r * cos(theta))+scr_x;
    y = yc + (r * sin(theta))+scr_y;


    color = getpixel(back_screen,x,y);


 if (color == RED)
 {
 color = GREEN;  // change color to GREEN if match 100%
 }
 else if (color == GREY)  // make sure is background color and put blue
{
 color = BLUE;
}
 else  if (color == BLUE) // check if this proc doubling pixels
{
 color = BLUE;
} else
{
 color = WHITE;  // otherwise WHITE to check pixels (if no WHITE everything is 100% correct)
}

putpixel(back_screen,x,y,color);

 }

}

return 0;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// pi_circle() taylor sin cos

int pi_circle_1(long double xc,long double yc, long double scr_x, long double scr_y, long double zoom, long double pi)
{

long double c, x,y,r, theta;
int i;
long double ti, ZOOM;
int color;
c=1.0;

int angle;

for (i=1;i<=9;i++)  // 9 circles
{


ZOOM = zoom*i;           // bigger circle
r=c*ZOOM;
    for(angle=0;angle<=360; angle++) //draw the circle of full 360 degrees angle

 {


    theta=(long double)(angle/180.0)*pi;

    x = xc + (r * taylor_cos(theta))+scr_x;
    y = yc + (r * taylor_sin(theta))+scr_y;
    y = y - r;

    color = getpixel(back_screen,x,y);


 if (color == RED)
 {
 color = GREEN;  // change color to GREEN if match 100%
 }
 else if (color == GREY)  // make sure is background color and put blue
{
 color = BLUE;
}
 else  if (color == BLUE) // check if this proc doubling pixels
{
 color = BLUE;
} else
{
 color = WHITE;  // otherwise WHITE to check pixels (if no WHITE everything is 100% correct)
}

putpixel(back_screen,x,y,color);

 }

}

return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

int change_res()
{
    int i,j=0, pos_y=20;

   int colors[6] = {BLACK,BLACK,BLACK,BLACK,BLACK,BLACK};

   start:

    clear_to_color(back_screen,GREY);  //clear bg
    for (i=0;i<6;i++)
    {
    colors[i] = BLACK;
    if (i==j) colors[j] = WHITE;
    }



    textout_centre_ex(back_screen, font, " Choose the app resolution, desktop", SCREEN_w/2, 10, BLACK, -1);
    textout_centre_ex(back_screen, font, " of the app will be scaled to init ", SCREEN_w/2, 20, BLACK, -1);
    textout_centre_ex(back_screen, font, " resolution from config file.      ", SCREEN_w/2, 30, BLACK, -1);
    textout_centre_ex(back_screen, font, "                                   ", SCREEN_w/2, 40, BLACK, -1);
    textout_centre_ex(back_screen, font, " 1 - 320x200 px 13h from DOS time  ", SCREEN_w/2, 50, colors[0], -1);
    textout_centre_ex(back_screen, font, " 2 - 640x480 px VGA                ", SCREEN_w/2, 60, colors[1], -1);
    textout_centre_ex(back_screen, font, " 3 - 800x600 px SVGA               ", SCREEN_w/2, 70, colors[2], -1);
    textout_centre_ex(back_screen, font, " 4 - 1024x768 px XGA               ", SCREEN_w/2, 80, colors[3], -1);
    textout_centre_ex(back_screen, font, " 5 - 1600x900 px HD+               ", SCREEN_w/2, 90, colors[4], -1);
    textout_centre_ex(back_screen, font, " 6 - 1920x1080 px FHD              ", SCREEN_w/2, 100, colors[5], -1);
    textout_centre_ex(back_screen, font, "                                   ", SCREEN_w/2, 110, BLACK, -1);
    textout_centre_ex(back_screen, font, "    Choose option from 1 to 6.     ", SCREEN_w/2, 120, BLACK, -1);





    textout_centre_ex(back_screen, font, "   Please press space to start.    ", SCREEN_w/2, 140, BLACK, -1);
    textout_centre_ex(back_screen, font, "   Author: MARTE.BEST 2023 AD      ", SCREEN_w/2, 160, BLACK, -1);

    textout_centre_ex(back_screen, font, "    Using Allegro 4.2 library      ", SCREEN_w/2, 170, BLACK, -1);

    masked_stretch_blit(back_screen, screen, 0, 0, SCREEN_w, SCREEN_h, 0, 0, SCREEN_W, SCREEN_H);




    while(1)

    {
    if(key[KEY_1])
    {
    SCREEN_w = 320;
    SCREEN_h = 200;
    j=0;
    pos_y=20;
    goto start;
    }

     if(key[KEY_2])
    {
    SCREEN_w = 640;
    SCREEN_h = 480;
    j=1;
    pos_y=40;
    goto start;
    }

     if(key[KEY_3])
    {
    SCREEN_w = 800;
    SCREEN_h = 600;
    j=2;
    pos_y=50;
    goto start;
    }
     if(key[KEY_4])
    {
    SCREEN_w = 1024;
    SCREEN_h = 768;
    j=3;
    pos_y=60;
    goto start;
    }
     if(key[KEY_5])
    {
    SCREEN_w = 1600;
    SCREEN_h = 900;
    j=4;
    pos_y=80;
    goto start;
    }
     if(key[KEY_6])
    {
    SCREEN_w = 1920;
    SCREEN_h = 1080;
    j=5;
    pos_y=100;
    goto start;
    }

    if(key[KEY_SPACE])
    {
    break;

    }
    }
    rest(2000);
 return pos_y;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                 MAIN


int main(void)
{


   /* you should always do this at the start of Allegro programs */
   if (allegro_init() != 0)
      return 1;

   /* set up the keyboard handler */
   install_keyboard();

   load_config();



    /* set the color palette */
    set_palette(desktop_palette);

    if (set_display_switch_mode(SWITCH_BACKGROUND)==-1) set_display_switch_mode(SWITCH_PAUSE);


    /* clear the screen to white */
    clear_to_color(screen, GREY);


    if (back_screen==NULL)
    {
    back_screen=create_bitmap(SCREEN_W,SCREEN_H);



    clear_to_color(back_screen,GREY);  //clear bg


    };

int pos_y;
int sin_cos_type = 0;

    show_welcome_screen();


    long long int f;

f = fact(36);
 printf(" Fact = %ld", f);


start:
    clear_to_color(back_screen,GREY);
    pos_y = change_res();

long double zoom=9.0,scr_x,scr_y;

long double xc,yc;
long double pi;

scr_x=0.0;
scr_y=0.0;
pi = M_PI;




while (1)

{




    xc=SCREEN_w/2.0;
    yc=SCREEN_h/2.0;

    clear_to_color(back_screen,GREY);



    bres_circle(xc,yc,scr_x,scr_y,zoom);

    if (sin_cos_type == 1)
    {
    pi_circle_0(xc,yc,scr_x,scr_y,zoom,pi);   // sequence is important sin cos math
    }
    else if(sin_cos_type == 2)
    {
    pi_circle_1(xc,yc,scr_x,scr_y,zoom,pi);   // sequence is important taylor sin cos
    }



    if (!key[KEY_I])
    {
    textout_centre_ex(back_screen,font,"Press I for more info",SCREEN_w/2,10,BLACK,-1);
    }
    if (sin_cos_type == 0)
    {
    textprintf_centre_ex(back_screen,font,SCREEN_w/2,SCREEN_h-pos_y,BLACK,-1," Bresenhamm's algorithm");
    }
    else
    {
    textprintf_centre_ex(back_screen,font,SCREEN_w/2,SCREEN_h-pos_y,BLACK,-1," Pi = %0Lf",pi);
    }

    if (key[KEY_I])  {
    textout_ex(back_screen,font," 1 - Golden Pi",10,10,BLACK,-1);
    textout_ex(back_screen,font," 2 - Canonical Pi",10,20,BLACK,-1);
    textout_ex(back_screen,font," 3 - Middle Pi",10,30,BLACK,-1);
    textout_ex(back_screen,font," M - sin() cos() MATH LIBRARY",10,40,BLACK,-1);
    textout_ex(back_screen,font," T - sin() cos() TYLOR MACLAURIN",10,50,BLACK,-1);
    textout_ex(back_screen,font," UP/DOWN - change Pi by 0.00000001",10,60,BLACK,-1);
    textout_ex(back_screen,font," LEFT/RIGHT - zoom circles",10,70,BLACK,-1);
    textout_ex(back_screen,font," A D S W - scroll circles",10,80,BLACK,-1);
    textout_ex(back_screen,font," C - center circles",10,90,BLACK,-1);
    textout_ex(back_screen,font," SPACE - ZOOM circles to 9.0",10,100,BLACK,-1);
    textout_ex(back_screen,font," ENTER - BACK",10,110,BLACK,-1);
    textout_ex(back_screen,font," ESC - EXIT",10,120,BLACK,-1);


    textout_ex(back_screen, font, " BLUE - PI METHOD", 10, 130, BLACK, -1);
    textout_ex(back_screen, font, " RED - BRESENHAM METHOD", 10, 140, BLACK, -1);
    textout_ex(back_screen, font, " GREEN - BOTH (MATCHED PIXELS)", 10, 150, BLACK, -1);
    textout_ex(back_screen, font, " WHITE - UNKNOWN", 10, 160, BLACK, -1);
    };

   // acquire_screen();
    masked_stretch_blit(back_screen,screen,0,0,SCREEN_w,SCREEN_h,0,0,SCREEN_W,SCREEN_H);

    /* you must always release bitmaps before calling any input functions */
   // release_screen();

    // if (key[KEY_SPACE]) goto start;

    if (key[KEY_1])  {pi = 3.1416407864998738178455042012387657412643710157669154345625383472;};  // Golden Pi computed with FCPI algo

    if (key[KEY_2])  {pi = M_PI;}; // built-in value Canonical Pi

    if (key[KEY_3])  {pi = 3.14161672;}; // Middle Pi (Golden Pi + Canonical Pi) / 2

    //if (key[KEY_M])  {sin_cos_type = 1; pi = M_PI;}; // SIN COS MATH

    //if (key[KEY_T])  {sin_cos_type = 2; pi = 3.1416407864998738178455042012387657412643710157669154345625383472;}; // SIN COS TAYLOR

    if (key[KEY_M])  {sin_cos_type = 1;}; // SIN COS MATH

    if (key[KEY_T])  {sin_cos_type = 2;}; // SIN COS TAYLOR

    if (key[KEY_UP]) {pi+=0.00000001; };

    if (key[KEY_DOWN]) {pi-=0.00000001; };

    if (key[KEY_D]) {scr_x+=0.1; if (scr_x>SCREEN_w) scr_x=SCREEN_w; };

    if (key[KEY_A]) {scr_x-=0.1; if (scr_x<-SCREEN_w) scr_x=-SCREEN_w;};

    if (key[KEY_W]) {scr_y+=0.1; if (scr_y>SCREEN_h) scr_y=SCREEN_h; };

    if (key[KEY_S]) {scr_y-=0.1; if (scr_y<-SCREEN_h) scr_y=-SCREEN_h;};

    if (key[KEY_LEFT]) {zoom+=0.1; if (zoom>1000) zoom=1; };

    if (key[KEY_RIGHT]) {zoom-=0.1; if (zoom<1) zoom=1000;};

    if (key[KEY_C]) {scr_x =0; scr_y=0; };

    if (key[KEY_SPACE]) {zoom=9.0; };

    if (key[KEY_ENTER]) goto start;

    if (key[KEY_ESC]) goto end;



}
end:


    destroy_bitmap(back_screen);


    allegro_exit();  // obligatory to succesfully close the app.
    return 0;
}

END_OF_MAIN()
