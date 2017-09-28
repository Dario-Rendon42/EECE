//
// Created by Dario Rendon on 9/27/2017.
//

/*
 * Converts an angle to a PWM interval in microseconds
 * @param angle The angle 0 to 180 for the servo motor to turn to
 * @return PWM interval in microseconds
 */
int degreeToOnDelay(int angle) {
    return (angle * 10) + 600;
}
