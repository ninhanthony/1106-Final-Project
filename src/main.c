#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pigpio.h>

#define PIN 17

int main(int argc, char* argv[]) {
    if (gpioInitialise() < 0) {
        printf("Failed to initialize pigpio. Run with sudo!\n");
        return 1;
    }

    gpioSetMode(PIN, PI_OUTPUT);
    gpioWrite(PIN, 0); 


    mkdir("data", 0755);

    float min_temp = 68.0f;
    float max_temp = 76.0f;
    float temp_sum = 0.0f;
    int temp_count = 0;
    int choice = 0;

    
    FILE *csv_init = fopen("data/temperature_log.csv", "a");
    if (csv_init != NULL) {
        fseek(csv_init, 0, SEEK_END);
        if (ftell(csv_init) == 0) {
            fprintf(csv_init, "Temperature_F,Status,LED,Average_F\n");
        }
        fclose(csv_init);
    } else {
        printf("Warning: could not open data/temperature_log.csv\n");
    }

    while (1) {
        printf("\n=== Smart Classroom Comfort Monitor ===\n");
        printf("Current Acceptable Range: %.1f F - %.1f F\n", min_temp, max_temp);
        printf("1. Enter classroom temperature reading (F)\n");
        printf("2. Change acceptable temperature range\n");
        printf("3. Exit\n");
        printf("Select an option: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (choice == 1) {
            float temp;
            printf("Enter temperature in Fahrenheit: ");
            if (scanf("%f", &temp) != 1) {
                while (getchar() != '\n');
                printf("Invalid temperature input.\n");
                continue;
            }

            temp_sum += temp;
            temp_count++;
            float avg = temp_sum / temp_count;

            const char *status;
            const char *led_state;

            if (temp >= min_temp && temp <= max_temp) {
                status = "NORMAL";
                led_state = "OFF";
                gpioWrite(PIN, 0);
            } else {
                status = "WARNING";
                led_state = "ON";
                gpioWrite(PIN, 1); 
            }

            printf("\nTemperature: %.1f F | System Status: %s | Warning LED: %s\n",
                   temp, status, led_state);
            printf("Average of recorded temperatures (%d readings): %.2f F\n",
                   temp_count, avg);

            
            FILE *log_file = fopen("data/temperature_log.csv", "a");
            if (log_file != NULL) {
                fprintf(log_file, "%.1f,%s,%s,%.2f\n", temp, status, led_state, avg);
                fclose(log_file);
            } else {
                printf("Warning: could not save reading to file.\n");
            }

            
            FILE *status_file = fopen("data/status.txt", "w");
            if (status_file != NULL) {
                fprintf(status_file, "%s\n", status);
                fclose(status_file);
            }

        } else if (choice == 2) {
            float new_min, new_max;
            printf("Enter new minimum acceptable temperature (F): ");
            if (scanf("%f", &new_min) != 1) {
                while (getchar() != '\n');
                printf("Invalid input. Range not changed.\n");
                continue;
            }
            printf("Enter new maximum acceptable temperature (F): ");
            if (scanf("%f", &new_max) != 1) {
                while (getchar() != '\n');
                printf("Invalid input. Range not changed.\n");
                continue;
            }

            if (new_min < new_max) {
                min_temp = new_min;
                max_temp = new_max;
                printf("Acceptable range updated to %.1f F - %.1f F.\n", min_temp, max_temp);
            } else {
                printf("Error: Minimum must be less than maximum.\n");
            }

        } else if (choice == 3) {
            gpioWrite(PIN, 0); 
            gpioTerminate();
            printf("Exiting program. Goodbye!\n");
            break;

        } else {
            printf("Invalid menu option. Choose 1, 2, or 3.\n");
        }
    }

    return 0;
}
