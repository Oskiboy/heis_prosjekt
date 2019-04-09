#include "light_handler.h"
#include "elev.h"

void update_lights(void) {
    int btn;
    int floor = elev_get_floor_sensor_signal();
    if(floor > 0) {
        elev_set_floor_indicator(floor); 
    }
    //Loop over all commands in all floors and check if a button is pressed.
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 3; ++j) {
            btn = elev_get_button_signal(j, i);
            if(btn) {
                elev_set_button_lamp(j, i, 1);
            }
        }
    }
}
