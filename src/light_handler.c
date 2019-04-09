#include "light_handler.h"
#include "elev.h"

void update_lights(void) {
    int btn;
    int floor = elev_get_floor_sensor_signal();
    if(floor > 0) {
        elev_set_floor_indicator(floor); 
    }
    //Loop over all commands in all floors and check if a button is pressed.
    for(int floor = 0; floor < 4; ++floor) {
        for(int button = 0; button < 3; ++button) {
            if ((floor == 0 && button == BUTTON_CALL_DOWN) || (floor == 3 && button == BUTTON_CALL_UP)){
                continue;
            }
            btn = elev_get_button_signal(button, floor);
            if(btn) {
                elev_set_button_lamp(button, floor, 1);
            }
        }
    }
}
