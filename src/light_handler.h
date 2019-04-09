/**
 * @file
 * @brief Functions for handling light.
 * 
 */
#ifndef LIGHT_HANDLER_H
#define LIGHT_HANDLER_H

/**
 * @brief Turns on all order button lights and floor light.
 * Every time this function is called it will check all buttons and the floor sensor
 * and light all the required lights.
 */
void update_lights(void);

/**
 * @brief Clears all order lights for the current floor.
 * When this function is called it clears all orders for the corresponding floor.
 */
void clear_order_lights(void);

#endif //LIGHT_HANDLER_H
