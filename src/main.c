#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>

#define PIN 17

  int main(int argc, char* argv[]) {
    if (gpioInitialise() < 0) {
      printf("Failed to initialize pigpio. Run with sudo!");
    return 1;
  }
  gpioSetMode(PIN, PI_OUTPUT);
  gpioWrite(PIN, 0);
    
  float min_temp = 68.0f;
  float max_temp = 76.0f;
  float temp_sum = 0.0f;
  int temp_count = 0;
  int choice = 0;

  FILE csv_init = fopen("data/temperature_log.csv", "a");
  if (csv_init != NULL) {
      fseek(csv_init, 0, SEEK_END);
  if (ftell(csv_init) == 0) {
  fprintf(csv_init, "Temperature_F,Status,LED,Average_F");
  }
  fclose(csv_init);
  }
  while (1) {
    printf("=== Smart Classroom Comfort Monitor === ");
    printf("Current Acceptable Range: %.1f F - %.1f F", min_temp, max_temp);
    printf("1. Enter classroom temperature reading (F)");
    printf("2. Change acceptable temperature range");
    printf("3. Exit");
    printf("Select an option: ");

  if (scanf("%d", &choice) != 1) {
  while (getchar() != '');
  printf("Invalid input. Please enter a number.");
  continue;
}
if (choice == 1) {
float temp;
printf("Enter temperature in Fahrenheit: ");
  if (scanf("%f", &temp) != 1) {
  while (getchar() != '');
  printf("Invalid temperature input.");
  continue;
  }
  temp_sum += temp;
  temp_count++;
  float avg = temp_sum / temp_count;
  const char status;
  const char led_state;
  if (temp >= min_temp && temp <= max_temp) {
  status = "NORMAL";
  led_state = "OFF";
  gpioWrite(PIN, 0); 
  } else {
  status = "WARNING";
  led_state = "ON";
  gpioWrite(PIN, 1); 
  }
  printf("Temperature: %.1f F | System Status: %s | Warning LED: %s",temp, status, led_state);
  printf("Average of recorded temperatures (%d readings): %.2f F",temp_count, avg);
  
  FILE log_file = fopen("data/temperature_log.csv", "a");
    if (log_file != NULL) {fprintf(log_file, "%.1f,%s,%s,%.2f
  ", temp, status, led_state, avg);
  fclose(log_file);
  }
  
  FILE status_file = fopen("data/status.txt", "w");
  if (status_file != NULL) {
  fprintf(status_file, "%s", status);
  fclose(status_file);
    
  }
  } else if (choice == 2) {
  float new_min, new_max;
  printf("Enter new minimum acceptable temperature (F): ");
  scanf("%f", &new_min);
  printf("Enter new maximum acceptable temperature (F): ");
  scanf("%f", &new_max);
  if (new_min < new_max) {
  min_temp = new_min;
  max_temp = new_max;
  printf("Acceptable range updated to %.1f F - %.1f F.", min_temp, max_temp);
  } else {
  printf("Error: Minimum must be less than maximum.");
  }
  } else if (choice == 3) {
  gpioWrite(PIN, 0);
  gpioTerminate();
  printf("Exiting program. Goodbye!");
  break;
  } else {
  printf("Invalid menu option. Choose 1, 2, or 3.");
  }
}
return 0;
}
