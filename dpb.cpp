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

    uint8_t smile[8]		= { 0x00, 0x0a, 0x0a, 0x00, 0x00, 0x11, 0x0e, 0x00 };
    lcd.defChar( hd44780::CCHAR0, smile );

    lcd.write("0,1 Æ\n",200);
    lcd.write("1,1\n",200);
    lcd.write("Fjerde linje?\n",200);
    lcd.write("meh...." ,200);
    lcd.write(a,200);
    lcd.write("laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaangt!\n\n", 200);
    lcd.write( hd44780::CCHAR0 );




    return 0;
}
