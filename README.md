# USBModelF
Teensy 3.2 USB converter for IBM Model F (XT) keyboards.

Initially based on https://github.com/noneucat/xt-usb-teensy

Tested with Arduino 1.8.13 and Teensyduino 1.53.
You must select Keyboard from the "Tools > USB Type" menu.


## Connections

| DIN socket pin | Teensy pin      |
| -------------- | --------------- |
| 1 (CLK)        | Digital 14      |
| 2 (GND)        | GND             |
| 3 (DATA)       | Digital 8       |
| 4 (VCC)        | Vin             |
| 5 (RESET)      | (not connected) |


## Keyboard layout

Feel free to customize the Arduino sketch as you see fit. Each physical key press may send up to five key-down events, allowing for simple macros.
I'm a Mac user, so I've reassigned some of the keys as follows:

| Model F Key | Sends                                      |
| ----------- | ------------------------------------------ |
| Alt         | Left Command/Windows                       |
| Caps Lock   | Right Option/Alt                           |
| Numpad 0    | Right Command/Windows                      |
| Num Lock    | Play/Pause                                 |
| Scroll Lock | Mute                                       |
| Numpad -    | Volume Down                                |
| Numpad +    | Volume Up                                  |
| Numpad *    | Right Ctrl                                 |
| F1*         | Ctrl-Opt-Cmd-F (maximize window)           |
| F2          | ` (backquote/tilde)                        |
| F3*         | Opt-Cmd-Left (window to left half)         |
| F4*         | Opt-Cmd-Right (window to right half)       |
| F5*         | Ctrl-Opt-Cmd-Left (window to prev screen)  |
| F6*         | Ctrl-Opt-Cmd-Right (window to next screen) |
| F7          | Shift-Cmd-3 (screenshot)                   |
| F8          | Shift-Cmd-4 (window screenshot)            |
| F9          | F14 (decrease brightness)                  |
| F10         | Left Option/Alt                            |

\* F1/F3/F4/F5/F6 are mapped to my [Rectangle](https://rectangleapp.com) hotkeys.

Lock modes (Caps/Num/Scroll) and multiple layers are not implemented.


## License

This code is released to the public domain.
