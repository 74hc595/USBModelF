  /**
 * XT Keyboard (IBM Model F) to USB Adapter for Teensy 3.1/3.2
 * Matt Sarnoff (msarnoff.org)
 * December 17, 2020
 * 
 * Tested with Arduino 1.8.13 and Teensyduino 1.53.
 * You must select Keyboard from the "Tools > USB Type" menu.
 * 
 * Initially based on https://github.com/noneucat/xt-usb-teensy.
 */
const int CLOCK_PIN = 14;
const int DATA_PIN = 8;
const int LED_PIN = 13;

/**
 * Define your key mapping here.
 * A physical key press may send up to five key-down events.
 */
#define MAX_CODES_PER_KEY 5
static const uint16_t scancodeToUSBCode[128][MAX_CODES_PER_KEY] = {
              [0x00] = {},
/* Esc */     [0x01] = {KEY_ESC},
/* 1 */       [0x02] = {KEY_1},
/* 2 */       [0x03] = {KEY_2},
/* 3 */       [0x04] = {KEY_3},
/* 4 */       [0x05] = {KEY_4},
/* 5 */       [0x06] = {KEY_5},
/* 6 */       [0x07] = {KEY_6},
/* 7 */       [0x08] = {KEY_7},
/* 8 */       [0x09] = {KEY_8},
/* 9 */       [0x0A] = {KEY_9},
/* 0 */       [0x0B] = {KEY_0},
/* - */       [0x0C] = {KEY_MINUS},
/* = */       [0x0D] = {KEY_EQUAL},
/* Bksp */    [0x0E] = {KEY_BACKSPACE},
/* Tab */     [0x0F] = {KEY_TAB},
/* Q */       [0x10] = {KEY_Q},
/* W */       [0x11] = {KEY_W},
/* E */       [0x12] = {KEY_E},
/* R */       [0x13] = {KEY_R},
/* T */       [0x14] = {KEY_T},
/* Y */       [0x15] = {KEY_Y},
/* U */       [0x16] = {KEY_U},
/* I */       [0x17] = {KEY_I},
/* O */       [0x18] = {KEY_O},
/* P */       [0x19] = {KEY_P},
/* [ */       [0x1A] = {KEY_LEFT_BRACE},
/* ] */       [0x1B] = {KEY_RIGHT_BRACE},
/* Enter */   [0x1C] = {KEY_ENTER},
/* L Ctrl */  [0x1D] = {KEY_LEFT_CTRL},
/* A */       [0x1E] = {KEY_A},
/* S */       [0x1F] = {KEY_S},
/* D */       [0x20] = {KEY_D},
/* F */       [0x21] = {KEY_F},
/* G */       [0x22] = {KEY_G},
/* H */       [0x23] = {KEY_H},
/* J */       [0x24] = {KEY_J},
/* K */       [0x25] = {KEY_K},
/* L */       [0x26] = {KEY_L},
/* ; */       [0x27] = {KEY_SEMICOLON},
/* ' */       [0x28] = {KEY_QUOTE},
/* ` */       [0x29] = {KEY_TILDE},
/* L Shift */ [0x2A] = {KEY_LEFT_SHIFT},
/* \ */       [0x2B] = {KEY_BACKSLASH},
/* Z */       [0x2C] = {KEY_Z},
/* X */       [0x2D] = {KEY_X},
/* C */       [0x2E] = {KEY_C},
/* V */       [0x2F] = {KEY_V},
/* B */       [0x30] = {KEY_B},
/* N */       [0x31] = {KEY_N},
/* M */       [0x32] = {KEY_M},
/* , */       [0x33] = {KEY_COMMA},
/* . */       [0x34] = {KEY_PERIOD},
/* / */       [0x35] = {KEY_SLASH},
/* R Shift */ [0x36] = {KEY_RIGHT_SHIFT},
/* KP * */    [0x37] = {KEY_RIGHT_CTRL},
/* L Alt */   [0x38] = {KEY_LEFT_GUI},
/* Space */   [0x39] = {KEY_SPACE},
/* Caps Lk */ [0x3A] = {KEY_RIGHT_ALT},
/* F1 */      [0x3B] = {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_F}, /* Maximize window */
/* F2 */      [0x3C] = {KEY_TILDE}, /* since it's next to Esc */
/* F3 */      [0x3D] = {KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_LEFT}, /* Window to left half */
/* F4 */      [0x3E] = {KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_RIGHT}, /* Window to right half */
/* F5 */      [0x3F] = {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_LEFT}, /* Window to previous screen */
/* F6 */      [0x40] = {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_RIGHT}, /* Window to next screen */
/* F7 */      [0x41] = {KEY_LEFT_SHIFT, KEY_LEFT_GUI, KEY_3}, /* Screenshot */
/* F8 */      [0x42] = {KEY_LEFT_SHIFT, KEY_LEFT_GUI, KEY_4}, /* Window screenshot */
/* F9 */      [0x43] = {KEY_F14}, /* Decrease brightness */
/* F10 */     [0x44] = {KEY_LEFT_ALT},
/* Num Lk */  [0x45] = {KEY_MEDIA_PLAY_PAUSE},
/* Scr Lk */  [0x46] = {KEY_MEDIA_MUTE},
/* KP 7 */    [0x47] = {KEY_HOME},
/* KP 8 */    [0x48] = {KEY_UP},
/* KP 9 */    [0x49] = {KEY_PAGE_UP},
/* KP - */    [0x4A] = {KEY_MEDIA_VOLUME_DEC},
/* KP 4 */    [0x4B] = {KEY_LEFT},
/* KP 5 */    [0x4C] = {KEY_DOWN}, /* another down arrow, allowing 8/4/5/6 to be used as an inverted-T layout */
/* KP 6 */    [0x4D] = {KEY_RIGHT},
/* KP + */    [0x4E] = {KEY_MEDIA_VOLUME_INC},
/* KP 1 */    [0x4F] = {KEY_END},
/* KP 2 */    [0x50] = {KEY_DOWN},
/* KP 3 */    [0x51] = {KEY_PAGE_DOWN},
/* KP 0 */    [0x52] = {KEY_RIGHT_GUI},
/* KP . */    [0x53] = {KEY_DELETE},
};

static volatile uint8_t bitsReceived = 0;
static volatile uint8_t receivedByte = 0;
static volatile bool keyReady = false;
static volatile uint8_t lastKey = 0;

void clockFallingEdge() {

  bool dataPin = digitalReadFast(DATA_PIN);
  
  if (bitsReceived == 0) {
    // start bit?
    if (dataPin) {  
      receivedByte = 0;
      bitsReceived++;
    }
  } else {
    // data bit
    receivedByte >>= 1;
    receivedByte |= (dataPin) ? 0x80 : 0x00;
    bitsReceived++;
    // after 1 start bit and 8 data bits, push the new byte
    if (bitsReceived == 9) {
      keyReady = true;
      lastKey = receivedByte;
      bitsReceived = 0;
    }
  }
}

void setup() {
  // configure pins
  pinMode(CLOCK_PIN, INPUT);
  pinMode(DATA_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  attachInterrupt(CLOCK_PIN, clockFallingEdge, FALLING);
  
  // blink LED
  digitalWriteFast(LED_PIN, HIGH);
  delay(100);
  digitalWriteFast(LED_PIN, LOW);
  delay(100);
  digitalWriteFast(LED_PIN, HIGH);
  delay(100);
  digitalWriteFast(LED_PIN, LOW);
}

void loop() {
  if (keyReady) {
    for (int i = 0; i < MAX_CODES_PER_KEY; i++) {
      uint16_t usbCode = scancodeToUSBCode[lastKey & 0x7F][i];
      if (usbCode == 0) {
        break;
      }
      if ((lastKey & 0x80) == 0) {
        Keyboard.press(usbCode);
      } else {
        Keyboard.release(usbCode);
      }
    }
    keyReady = false;
  }
}
