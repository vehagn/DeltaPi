#include <rpi-hw.hpp>
#include <rpi-hw/utils.hpp>
#include <rpi-hw/time.hpp>
#include <rpi-hw/display/hd44780.hpp>

using namespace rpihw;
using namespace rpihw::display;

int main( int argc, char *args[]){

    hd44780 lcd(14, 15, 24, 25, 8, 7);
    lcd.init(20, 4);

    lcd.write(0, 0, "0,1 Æ");
    lcd.write(1, 1, "1,1");
    lcd.write(3, 6, "Fjerde linje?");


    return 0;
}
