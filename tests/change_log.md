# Changelog

All notable changes to the Smart Classroom Comfort Monitor are listed here, newest first.

## [1.0.0] - 2026-11-13
### Added
- Temperature monitoring and logging program (`src/temp_monitor.c`)
- NORMAL / WARNING status check for the 68°F to 76°F range (inclusive)
- Running average of recorded temperatures
- Warning LED on GPIO 17
- Saving of readings and statuses to `data/temperature_log.csv` and `data/status.txt`
- Menu option to change the acceptable temperature range
- Test plan and testing report (`tests/TEST_PLAN.md`)

### Fixed
- Corrected file pointer and string declarations that stopped the program from compiling
- Fixed broken newline characters in the code
- Program now creates the `data/` folder itself if it is missing
- Added input checks when changing the temperature range

## [0.2.0] - (date)
### Added
- Design documentation for the temperature monitor (`docs/`)

## [0.1.0] - (date)
### Added
- Initial project structure (`data/`, `docs/`, `src/`, `tests/`)
- README
- LED test program (`led.c`)
