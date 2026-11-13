Changelog 

=== Added ===
- Temperature monitoring and logging program 
- NORMAL / WARNING status check for the 68°F to 76°F range (inclusive)
- Running average of recorded temperatures
- Warning LED on GPIO 17
- Menu option to change the acceptable temperature range
- Test plan and testing report 

=== Fixed ===
- Corrected file pointer and string declarations that stopped the program from compiling
- Fixed broken newline characters in the code
- Program now creates the data/ folder itself if it is missing
- Added input checks when changing the temperature range

=== 11/13/2026 ===

- Design documentation for the temperature monitor

=== 11/06/2026

- Initial project structure 
- README
- LED test program
