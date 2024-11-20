#include "main.h"
pros::Motor motor(10, pros::MotorGears::blue);
pros::Controller master(pros::E_CONTROLLER_MASTER);
void spin() {
  while (true) {
    if (master.get_digital(DIGITAL_L1)) {
      motor.move_velocity(600);
    } else if (master.get_digital(DIGITAL_L2)) {
      motor.move_velocity(-600);
    } else {
      motor.move_velocity(0);
    }
    pros::delay(20);
  }
}
void Data() {
  while (true) {
    // Get the motor temperature
    std::uint32_t motor_temp = motor.get_temperature();

    // Check if the temperature reading is valid
    if (motor_temp == PROS_ERR_F) {
      printf("Error reading motor temperature\n");
    } else {
      // Debug print to indicate the motor temperature
      printf("| Motor Temp: %u C | RPM: %f \n", motor_temp,
             motor.get_actual_velocity());
    }
    pros::delay(100); // Delay for 0.1 second
  }
}

void opcontrol() {
  pros::Link link(21, "my_link", pros::E_LINK_TX);

  // Debug print to indicate that opcontrol is running
  printf("opcontrol is running\n");
  pros::Task task2(Data);
  pros::Task task(spin);
}