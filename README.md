# Simple Keylogger Project

## Disclaimer

Warning: This project is intended purely for educational purposes and should not be used for any unauthorized or malicious activities. The creator does not condone or support illegal actions. Misuse of this tool can result in severe legal consequences. Always ensure that any software you develop or use complies with applicable laws and ethical standards.

This keylogger has been created as part of a personal project to better understand Windows hooks and the principles of low-level keyboard and window monitoring. The code is open for educational review, experimentation, and learning about Windows API hooks. Use responsibly.

## Overview

This project demonstrates a simple keylogger that records keystrokes and window titles using Windows API hooks. The logger captures keyboard input and writes it to a file, and also monitors changes in the active window title. The information is stored in a text file, and the collected data can be sent to a specified server via a webhook.

### Features:
- Keyboard Input Capture: Monitors and records every key pressed by the user.
- Window Title Tracking: Tracks changes in the foreground window's title.
- DLL Injection: The keylogger and window hook are implemented as a dynamic-link library (DLL).
- File Logging: Captures and logs input data to a local text file (`window_titles.txt`).
- File Upload: Uploads the log file to a specified server via HTTP POST using `libcurl`.

## How It Works

### Components

1. **Keyboard Hook (`llKeyboardProc`)**: This function captures keyboard events using the `WH_KEYBOARD_LL` hook. It records each keystroke to a text file.
2. **Window Hook (`llWindowProc`)**: This function listens for changes in the active window and records the window title to the text file whenever a new window is activated.
3. **DLL (`Win64Manager.dll`)**: The core of the project. It contains hooks to capture keyboard and window title data.
4. **Sending Logs**: The logs are uploaded to a server using `libcurl`. The file is sent via an HTTP POST request.

### Flow:
- When the application starts, it loads the DLL `Win64Manager.dll`.
- The DLL installs a system-wide keyboard hook and window hook.
- The keylogger captures keyboard inputs and window titles, appending the data to `window_titles.txt`.
- Periodically, the log file is uploaded to a specified webhook.

## Setup

### Prerequisites
- Windows: This project is built for Windows OS.
- Dependencies:
  - `libcurl`: Required to send HTTP POST requests for file upload.
  - The project uses the Windows API for hook installation and message dispatching.

### Instructions

1. Clone the repository:
git clone https://github.com/muhammad1966/Logger112.git

2. Install Dependencies:
- Make sure you have `libcurl` installed for uploading files to a server. You can follow the official `libcurl` installation guide (https://curl.se/libcurl/) for more details.

3. Compile:
- Build the DLL (`Win64Manager.dll`) and the application using a C++ compiler that supports Windows API development (such as Visual Studio).

4. Usage:
- Once compiled, run the executable. The keylogger will start recording keystrokes and window titles.
- The log file will be generated in the same directory as the executable.
- The file can be periodically uploaded to your server by configuring the webhook URL in the source code.

## Important Notes
- Ethical Considerations: This software should only be used in a controlled, ethical environment where you have explicit permission to monitor system input (such as during penetration testing with consent or educational experiments).
- Data Privacy: Any data captured by this tool should be handled with care. Ensure that sensitive information is not collected or exposed without consent.
- Use at Your Own Risk: The creator does not take any responsibility for the misuse of this project.

## Contributions

Feel free to contribute to this project if you're interested in adding more features or improving the existing code. If you find any bugs or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contact

If you have any questions or feedback, feel free to contact me at bsmuhammad352@gmail.com
