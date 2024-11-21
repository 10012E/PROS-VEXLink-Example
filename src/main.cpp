#include "main.h" //including the main file that utilises the PROS Library.

pros::Motor motor(10,
                  pros::MotorGears::blue); // Adding a Blue Motor to the port 10
pros::Controller
    master(pros::E_CONTROLLER_MASTER); // Adding a Controller called master

/*This first function simply allows us to spin one of our motors, this is just
 * to test the live reaction*/
void spin() {
  while (true) { // while loop with true as its condition, meaning it will run
                 // indefinitely
    if (master.get_digital(DIGITAL_L1)) {        // if the L1 button is pressed
      motor.move_velocity(600);                  // spin the motor at 600 RPM
    } else if (master.get_digital(DIGITAL_L2)) { // if the L2 button is pressed
      motor.move_velocity(-600);                 // spin the motor at -600 RPM
    } else {
      motor.move_velocity(0); // if no button is pressed, stop the motor
    }
    pros::delay(20); // delay for 20 milliseconds
  }
}

/*Our second funtion is where the Data gets transmitted*/
void Data() {
  while (true) { // while loop with true as its condition, meaning it will run
                 // indefinitely
    // Get the motor temperature
    std::uint32_t motor_temp = motor.get_temperature(); // Get the motor
                                                        // temperature

    // Check if the temperature reading is valid
    if (motor_temp == PROS_ERR_F) { // If the temperature reading is invalid
      printf("Error reading motor temperature\n");
    } else { // If the temperature reading is valid
      // Debug print to indicate the motor temperature
      printf("| Motor Temp: %u C | RPM: %f \n", motor_temp,
             motor.get_actual_velocity());
    }
    pros::delay(100); // Delay for 0.1 second
  }
}

/*This is the main function that runs when the robot is turned on*/
void opcontrol() {
  pros::Link link(21, "my_link", pros::E_LINK_TX); // Create a link radio

  // Debug print to indicate that opcontrol is running
  printf("opcontrol is running\n");
  pros::Task task2(Data);
  pros::Task task(spin);
}
