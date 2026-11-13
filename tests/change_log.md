Changelog 

=== Added ===
1. Temperature monitoring and logging program (`src/temp_monitor.c`)
2. NORMAL / WARNING status check for the 68°F to 76°F range (inclusive)
- Running average of recorded temperatures
- Warning LED on GPIO 17
- Saving of readings and statuses to `data/temperature_log.csv` and `data/status.txt`
- Menu option to change the acceptable temperature range
- Test plan and testing report (`tests/TEST_PLAN.md`)

=== Fixed ===
- Corrected file pointer and string declarations that stopped the program from compiling
- Fixed broken newline characters in the code
- Program now creates the `data/` folder itself if it is missing
- Added input checks when changing the temperature range

=== 11/13/2026 ===

- Design documentation for the temperature monitor (`docs/`)

=== 11/06/2026

- Initial project structure (`data/`, `docs/`, `src/`, `tests/`)
- README
- LED test program (`led.c`)
