# STM32H7_25-26

This branch contains a project that can be flashed onto the Nucleo H755ZI in order to use QConn to program the ST67W611M1 board to run in "mission mode", which enables BLE and Wifi capabilities.

# Firmware flashing steps (for Windows)
1. Download the X-Cube-ST67W61 software expansion package from https://www.st.com/en/wireless-connectivity/st67w611m1.html#tools-software
2. Replace "x-cube-st67w61\Projects\ST67W6X_Utilities\Binaries\NCP_update_mission_profile_t02.bat" with the NCP_update_mission_profile_t02.bat file in the root folder of this repo.
3. Open this project in STM32CubeIDE, build it, and flash it onto a Nucleo H755ZI. You should observe the red LED blinking three times after flashing successfully.
4. Run the NCP_update_mission_profile_t02.bat file.

Refer to https://www.st.com/resource/en/user_manual/um3475-getting-started-with-xcubest67w61-stmicroelectronics.pdf to read more about the process.
