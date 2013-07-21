#include <rpi-hw.hpp>
#include <rpi-hw/utils.hpp>
#include <rpi-hw/time.hpp>
#include <rpi-hw/display/hd44780.hpp>
#include <cstdlib>

using namespace rpihw;
using namespace rpihw::display;
using namespace std;

int main( int argc, char *args[]){

    hd44780 lcd(14, 15, 24, 25, 8, 7);
    lcd.init(20, 4);

    string a = "En streng!\n";
    lcd.setAutoscroll( hd44780::HSCROLL_LINE );

    uint8_t smile[8]	= {0x00, 0x0a, 0x0a, 0x00, 0x00, 0x11, 0x0e, 0x00};
    lcd.defChar(hd44780::CCHAR0, smile);

    uint8_t dtop[8]     = {0x00, 0x00, 0x00, 0x00, 0x04, 0x0e, 0x1f, 0x1b};
    uint8_t dleft[8]    = {0x03, 0x07, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00};
    uint8_t dmid[8]     = {0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00};
    uint8_t dright[8]   = {0x18, 0x1c, 0x0e, 0x07, 0x1f, 0x1f, 0x1b, 0x00};
    lcd.defChar(hd44780::CCHAR1, dtop);
    lcd.defChar(hd44780::CCHAR2, dleft);
    lcd.defChar(hd44780::CCHAR3, dmid);
    lcd.defChar(hd44780::CCHAR4, dright);
    

    


    lcd.write("0,1 Æ\n",200);
    lcd.write("1,1\n",200);
    lcd.write("Fjerde linje?\n",200);
    lcd.write("meh...." ,200);
    lcd.write(a,200);
    lcd.write("laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaangt!\n\n", 20);
    lcd.write( hd44780::CCHAR0 );

    lcd.clear();

    lcd.write(10,1, hd44780::CCHAR1);
    lcd.write(9,2, hd44780::CCHAR2);
    lcd.write(10,2, hd44780::CCHAR3);
    lcd.write(11,2, hd44780::CCHAR4,500);
    
    lcd.clear();

    uint8_t delta_TL[8]     = {0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07};
    lcd.defChar(hd44780::CCHAR0, delta_TL);
    lcd.write(3,0,hd44780::CCHAR0);
    
    uint8_t delta_TM[8]     = {0x00, 0x04, 0x0e, 0x1f, 0x1f, 0x1f, 0x1f, 0x11};
    lcd.defChar(hd44780::CCHAR0, delta_TM);
    lcd.write(4,0,hd44780::CCHAR0);
    
    uint8_t delta_TR[8]     = {0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x1c};
    lcd.defChar(hd44780::CCHAR0, delta_TR);
    lcd.write(5,0,hd44780::CCHAR0);
    
    uint8_t delta_MLL[8]    = {0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x00};
    lcd.defChar(hd44780::CCHAR0, delta_MLL);
    lcd.write(2,1,hd44780::CCHAR0);
    
    uint8_t delta_MLR[8]    = {0x1f, 0x1e, 0x1c, 0x18, 0x10, 0x00, 0x00, 0x00};
    lcd.defChar(hd44780::CCHAR0, delta_MLR);
    lcd.write(3,1,hd44780::CCHAR0);
    
    uint8_t delta_MRL[8]    = {0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00};
    lcd.defChar(hd44780::CCHAR0, delta_MRL);
    lcd.write(5,1,hd44780::CCHAR0);
    
    uint8_t delta_MRR[8]    = {0x00, 0x00, 0x10, 0x18, 0x1c, 0x1e, 0x1f, 0x0f};
    lcd.defChar(hd44780::CCHAR0, delta_MRR);
    lcd.write(6,1,hd44780::CCHAR0);
    
    uint8_t delta_BL[8]     = {0x00, 0x00, 0x0f, 0x1f, 0x1f, 0x0f, 0x00, 0x00};
    lcd.defChar(hd44780::CCHAR0, delta_BL);
    lcd.write(1,2,hd44780::CCHAR0);
    
    uint8_t delta_BM[8]     = {0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00};
    lcd.defChar(hd44780::CCHAR0, delta_BM);
    lcd.write(2,2,hd44780::CCHAR0);
    lcd.write(3,2,hd44780::CCHAR0);
    lcd.write(4,2,hd44780::CCHAR0);
    lcd.write(5,2,hd44780::CCHAR0);
    
    uint8_t delta_BRL[8]    = {0x03, 0x01, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00};
    lcd.defChar(hd44780::CCHAR0, delta_BRL);
    lcd.write(6,2,hd44780::CCHAR0);
    
    uint8_t delta_BRR[8]    = {0x18, 0x1c, 0x1e, 0x1f, 0x1f, 0x1e, 0x00, 0x00};
    lcd.defChar(hd44780::CCHAR0, delta_BRL);
    lcd.write(7,2,hd44780::CCHAR0);
    
    lcd.write(2,3,"-DELTA-",500)


    return 0;
}
