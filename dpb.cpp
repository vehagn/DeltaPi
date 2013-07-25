#include <rpi-hw.hpp>
#include <rpi-hw/utils.hpp>
#include <rpi-hw/time.hpp>
#include <rpi-hw/display/hd44780.hpp>
#include <cstdlib>
#include <sstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

char getch() {
        
        /*
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);*/     
        struct termios old_tio, new_tio;
        char buf = 0;
        
        tcgetattr(STDIN_FILENO,&old_tio);
        new_tio=old_tio;
        new_tio.c_lflag &= (~ICANON);
        tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

        if (read(0, &buf, 1) < 0)
                perror ("read()");

         tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
         return (buf);     
}


using namespace rpihw;
using namespace rpihw::display;
using namespace std;

int main( int argc, char *args[]){

    hd44780 lcd(14, 15, 24, 25, 8, 7);
    lcd.init(20, 4);

    string a = "En streng!\n";
    lcd.setAutoscroll( hd44780::HSCROLL_LINE );

    uint8_t delta[8]    = {0x00, 0x00, 0x00, 0x04, 0x0a, 0x11, 0x1f, 0x00};
    uint8_t pi[8]	    = {0x00, 0x00, 0x1f, 0x0a, 0x0a, 0x0a, 0x09, 0x00};
    uint8_t beta[8]     = {0x0c, 0x0a, 0x0a, 0x0c, 0x0a, 0x0a, 0x0c, 0x08};
    lcd.defChar(hd44780::CCHAR4, delta);
    lcd.defChar(hd44780::CCHAR5, pi);
    lcd.defChar(hd44780::CCHAR6, beta);

    uint8_t dtop[8]     = {0x00, 0x00, 0x00, 0x00, 0x04, 0x0e, 0x1f, 0x1b};
    uint8_t dleft[8]    = {0x03, 0x07, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00};
    uint8_t dmid[8]     = {0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00};
    uint8_t dright[8]   = {0x18, 0x1c, 0x0e, 0x07, 0x1f, 0x1f, 0x00, 0x00};
    lcd.defChar(hd44780::CCHAR0, dtop);
    lcd.defChar(hd44780::CCHAR1, dleft);
    lcd.defChar(hd44780::CCHAR2, dmid);
    lcd.defChar(hd44780::CCHAR3, dright);
    
/*    if (argc > 1){
        string in;
        stringstream ss;
        lcd.clear();
        for (int i = 1; i <= argc; i++){
            ss << args[i];
            ss >> in;  
            lcd.write(in);
            lcd.write(' ');
        }
    }else{
        lcd.write("0,1 Æ\n",200);
        lcd.write("1,1\n",200);
        lcd.write("Fjerde linje?\n",200);
        lcd.write("meh...." ,200);
        lcd.write(a,200);
        lcd.write("laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaangt!\n\n", 20);
        lcd.write( hd44780::CCHAR0 );
    
        lcd.clear();
    
        lcd.write(10,1, hd44780::CCHAR0);
        lcd.write(9,2, hd44780::CCHAR1);
        lcd.write(10,2, hd44780::CCHAR2);
        lcd.write(11,2, hd44780::CCHAR3);
        lcd.write(9,3, hd44780::CCHAR4);
        lcd.write(10,3, hd44780::CCHAR5);
        lcd.write(11,3, hd44780::CCHAR6);
        lcd.write(12,3, "DPB, dpb");
    }*/
    lcd.clear();
    
    char c, buf[8];
    int i = 0;
    do {
        c = getch();
        buf[i] = c;
        lcd.write(i++%20,0,c);
    }while (c != '\n');
    
    printf("\n %i \n",atoi(buf));

    return 0;
}
