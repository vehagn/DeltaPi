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

    lcd.write(0, 0, "0,1 Æ");
    lcd.write(1, 1, "1,1");
    lcd.write(6, 3, "Fjerde linje?");
    lcd.write(4, 2, "meh...." );
    lcd.write(5, 0, a);




    return 0;
}
