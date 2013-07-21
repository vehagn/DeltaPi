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

    string a = "En streng!";
    lcd.setAutoscroll( hd44780::HSCROLL_LINE );

    lcd.write("0,1 Æ",200);
    lcd.write("1,1",200);
    lcd.write("Fjerde linje?",200);
    lcd.write("meh...." ,200);
    lcd.write(a,200);
    lcd.write("laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaangt!", 200);




    return 0;
}
