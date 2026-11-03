// https://github.com/kachurovskiy/nanoels

/* Change values in this section to suit your hardware. */

// Define your hardware parameters here. These are firmware defaults; the Web UI
// can override them in ESP32 Preferences and apply them after restart.
const int DEFAULT_ENCODER_PPR = 1200; // 1200 step spindle optical rotary encoder. Fractional values not supported.
const int DEFAULT_ENCODER_BACKLASH = 3; // Number of impulses encoder can issue without movement of the spindle
const int DEFAULT_AXIS_ENCODER_BACKLASH = 0; // Number of handwheel encoder impulses ignored after direction reverses
int ENCODER_PPR = DEFAULT_ENCODER_PPR;
int ENCODER_BACKLASH = DEFAULT_ENCODER_BACKLASH;
int AXIS_ENCODER_BACKLASH = DEFAULT_AXIS_ENCODER_BACKLASH;

// Spindle rotary encoder pins. Swap values if the rotation direction is wrong.
#define ENC_A 13
#define ENC_B 14

// Main lead screw (Z) parameters.
const long DEFAULT_SCREW_Z_DU = 40000; // 4mm SFU1204 ball screw in deci-microns (10^-7 of a meter)
const long DEFAULT_MOTOR_STEPS_Z = 800;
const long DEFAULT_SPEED_START_Z = DEFAULT_MOTOR_STEPS_Z; // Initial speed of a motor, steps / second.
const long DEFAULT_ACCELERATION_Z = 25 * DEFAULT_MOTOR_STEPS_Z; // Acceleration of a motor, steps / second ^ 2.
const long DEFAULT_SPEED_MANUAL_MOVE_Z = 8 * DEFAULT_MOTOR_STEPS_Z; // Maximum speed of a motor during manual move, steps / second.
const bool DEFAULT_INVERT_Z = false; // change (true/false) if the carriage moves e.g. "left" when you press "right".
const bool DEFAULT_INVERT_Z_ENABLE = false; // change (true/false) if the Z axis enable pin is inverted
const bool DEFAULT_NEEDS_REST_Z = false; // Set to false for closed-loop drivers, true for open-loop.
const long DEFAULT_MAX_TRAVEL_MM_Z = 300; // Lathe bed doesn't allow to travel more than this in one go, 30cm / ~1 foot
const long DEFAULT_BACKLASH_DU_Z = 0; // 0mm backlash in deci-microns (10^-7 of a meter)
long SCREW_Z_DU = DEFAULT_SCREW_Z_DU;
long MOTOR_STEPS_Z = DEFAULT_MOTOR_STEPS_Z;
long SPEED_START_Z = DEFAULT_SPEED_START_Z;
long ACCELERATION_Z = DEFAULT_ACCELERATION_Z;
long SPEED_MANUAL_MOVE_Z = DEFAULT_SPEED_MANUAL_MOVE_Z;
bool INVERT_Z = DEFAULT_INVERT_Z;
bool INVERT_Z_ENABLE = DEFAULT_INVERT_Z_ENABLE;
bool NEEDS_REST_Z = DEFAULT_NEEDS_REST_Z;
long MAX_TRAVEL_MM_Z = DEFAULT_MAX_TRAVEL_MM_Z;
long BACKLASH_DU_Z = DEFAULT_BACKLASH_DU_Z;
const char NAME_Z = 'Z'; // Text shown on screen before axis position value, GCode axis name

// Cross-slide lead screw (X) parameters.
const long DEFAULT_SCREW_X_DU = 40000; // 4mm SFU1204 ball screw in deci-microns (10^-7 of a meter)
const long DEFAULT_MOTOR_STEPS_X = 800;
const long DEFAULT_SPEED_START_X = DEFAULT_MOTOR_STEPS_X; // Initial speed of a motor, steps / second.
const long DEFAULT_ACCELERATION_X = 25 * DEFAULT_MOTOR_STEPS_X; // Acceleration of a motor, steps / second ^ 2.
const long DEFAULT_SPEED_MANUAL_MOVE_X = 8 * DEFAULT_MOTOR_STEPS_X; // Maximum speed of a motor during manual move, steps / second.
const bool DEFAULT_INVERT_X = true; // change (true/false) if the carriage moves e.g. "left" when you press "right".
const bool DEFAULT_INVERT_X_ENABLE = false; // change (true/false) if the X axis enable pin is inverted
const bool DEFAULT_NEEDS_REST_X = false; // Set to false for all kinds of drivers or X will be unlocked when not moving.
const long DEFAULT_MAX_TRAVEL_MM_X = 100; // Cross slide doesn't allow to travel more than this in one go, 10cm
const long DEFAULT_BACKLASH_DU_X = 0; // 0.15mm backlash in deci-microns (10^-7 of a meter)
long SCREW_X_DU = DEFAULT_SCREW_X_DU;
long MOTOR_STEPS_X = DEFAULT_MOTOR_STEPS_X;
long SPEED_START_X = DEFAULT_SPEED_START_X;
long ACCELERATION_X = DEFAULT_ACCELERATION_X;
long SPEED_MANUAL_MOVE_X = DEFAULT_SPEED_MANUAL_MOVE_X;
bool INVERT_X = DEFAULT_INVERT_X;
bool INVERT_X_ENABLE = DEFAULT_INVERT_X_ENABLE;
bool NEEDS_REST_X = DEFAULT_NEEDS_REST_X;
long MAX_TRAVEL_MM_X = DEFAULT_MAX_TRAVEL_MM_X;
long BACKLASH_DU_X = DEFAULT_BACKLASH_DU_X;
const char NAME_X = 'X'; // Text shown on screen before axis position value, GCode axis name

// Manual stepping with left/right/up/down buttons. Used when the selected move step should not be continuous.
const long DEFAULT_STEP_TIME_MS = 500; // Time in milliseconds it should take to make 1 manual step.
const long DEFAULT_DELAY_BETWEEN_STEPS_MS = 80; // Time in milliseconds to wait between steps.
const bool DEFAULT_ENABLE_CONTINUOUS_MOVE = true; // If true, move buttons use continuous motion for the default step.
long STEP_TIME_MS = DEFAULT_STEP_TIME_MS;
long DELAY_BETWEEN_STEPS_MS = DEFAULT_DELAY_BETWEEN_STEPS_MS;
bool ENABLE_CONTINUOUS_MOVE = DEFAULT_ENABLE_CONTINUOUS_MOVE;

// Connect to WiFi and expose web UI to control and receive GCode.
// Credentials are stored in ESP32 Preferences and can be changed from the Web UI.
// On first boot or connection failure, H5 starts a setup access point.
const bool DEFAULT_WIFI_ENABLED = true;
const char* DEFAULT_WIFI_SSID = "";
const char* DEFAULT_WIFI_PASSWORD = "";
bool WIFI_ENABLED = DEFAULT_WIFI_ENABLED;
String WIFI_SSID = DEFAULT_WIFI_SSID;
String WIFI_PASSWORD = DEFAULT_WIFI_PASSWORD;
const char* WIFI_SETUP_AP_SSID = "NanoEls-H5-Setup";
const char* WIFI_SETUP_AP_PASSWORD = "nanoels-h5";
const long INCOMING_BUFFER_SIZE = 100000;
const long OUTGOING_BUFFER_SIZE = 100000;

/* Changing anything below shouldn't be needed for basic use. */

// Configuration for axis connected to Y. This is uncommon. Dividing head (C) motor parameters.
// Throughout the configuration below we assume 1mm = 1degree of rotation, so 1du = 0.0001degree.
const bool DEFAULT_ACTIVE_Y = false; // Whether the axis is connected
const bool DEFAULT_ROTARY_Y = true; // Whether the axis is rotary or linear
const long DEFAULT_MOTOR_STEPS_Y = 300; // Number of motor steps for 1 rotation of the worm gear screw (full step with 20:30 reduction)
const long DEFAULT_SCREW_Y_DU = 20000; // Degrees multiplied by 10000 that the spindle travels per 1 turn of the worm gear. 2 degrees.
const long DEFAULT_SPEED_START_Y = 1600; // Initial speed of a motor, steps / second.
const long DEFAULT_ACCELERATION_Y = 16000; // Acceleration of a motor, steps / second ^ 2.
const long DEFAULT_SPEED_MANUAL_MOVE_Y = 3200; // Maximum speed of a motor during manual move, steps / second.
const bool DEFAULT_INVERT_Y = false; // change (true/false) if the carriage moves e.g. "left" when you press "right".
const bool DEFAULT_INVERT_Y_ENABLE = false; // change (true/false) if the Y axis enable pin is inverted
const bool DEFAULT_NEEDS_REST_Y = false; // Set to false for closed-loop drivers. Open-loop: true if you need holding torque, false otherwise.
const long DEFAULT_MAX_TRAVEL_MM_Y = 360; // Probably doesn't make sense to ask the dividing head to travel multiple turns.
const long DEFAULT_BACKLASH_DU_Y = 0; // Assuming no backlash on the worm gear
bool ACTIVE_Y = DEFAULT_ACTIVE_Y;
bool ROTARY_Y = DEFAULT_ROTARY_Y;
long MOTOR_STEPS_Y = DEFAULT_MOTOR_STEPS_Y;
long SCREW_Y_DU = DEFAULT_SCREW_Y_DU;
long SPEED_START_Y = DEFAULT_SPEED_START_Y;
long ACCELERATION_Y = DEFAULT_ACCELERATION_Y;
long SPEED_MANUAL_MOVE_Y = DEFAULT_SPEED_MANUAL_MOVE_Y;
bool INVERT_Y = DEFAULT_INVERT_Y;
bool INVERT_Y_ENABLE = DEFAULT_INVERT_Y_ENABLE;
bool NEEDS_REST_Y = DEFAULT_NEEDS_REST_Y;
long MAX_TRAVEL_MM_Y = DEFAULT_MAX_TRAVEL_MM_Y;
long BACKLASH_DU_Y = DEFAULT_BACKLASH_DU_Y;
const char NAME_Y = 'Y'; // Text shown on screen before axis position value, GCode axis name

// Manual handwheels. Ignore if you don't have them installed.
const float DEFAULT_PULSE_PER_REVOLUTION_Z = 600; // PPR of Z handwheel.
const float DEFAULT_PULSE_PER_REVOLUTION_X = 600; // PPR of X handwheel.
const float DEFAULT_PULSE_PER_REVOLUTION_Y = 600; // PPR of Y handwheel.
float PULSE_PER_REVOLUTION_Z = DEFAULT_PULSE_PER_REVOLUTION_Z;
float PULSE_PER_REVOLUTION_X = DEFAULT_PULSE_PER_REVOLUTION_X;
float PULSE_PER_REVOLUTION_Y = DEFAULT_PULSE_PER_REVOLUTION_Y;
const unsigned long HANDWHEEL_PULSE_WAIT_MS = 20; // Keep fast handwheel pulses in one continuous move.

// Up to 3-axis analog joystick. Leave disabled unless the joystick is wired and its
// potentiometers are powered from 3.3V, not 5V.
const bool DEFAULT_JOYSTICK_ENABLED = false;
const bool DEFAULT_JOYSTICK_Z_ENABLED = true;
const bool DEFAULT_JOYSTICK_X_ENABLED = true;
const bool DEFAULT_JOYSTICK_Y_ENABLED = true;
const bool DEFAULT_JOYSTICK_BUTTON_TOGGLES_ON_OFF = false;
const int DEFAULT_JOYSTICK_CENTER_SAMPLES = 64;
const int DEFAULT_JOYSTICK_OVERSAMPLES = 4;
const int DEFAULT_JOYSTICK_SAMPLE_INTERVAL_MS = 20;
const int DEFAULT_JOYSTICK_ADC_MAX = 4095;
const int DEFAULT_JOYSTICK_DEADBAND = 250; // Raw ADC counts around center ignored.
const int DEFAULT_JOYSTICK_PULSE_QUEUE_LIMIT = 10000;
const float DEFAULT_JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND = 1.0;
const float DEFAULT_JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND = 8.0;
const float JOYSTICK_PITCH_CHANGES_PER_SECOND = 20.0;
const unsigned long JOYSTICK_PITCH_STATUS_HOLD_MS = 500;
const unsigned long JOYSTICK_BUTTON_DEBOUNCE_MS = 30;
const unsigned long JOYSTICK_BUTTON_TOGGLE_MAX_MS = 500;
const int JOYSTICK_STARTUP_CENTER_TOLERANCE_MIN = 32; // Reject startup centers too far from ADC midpoint.
const bool DEFAULT_INVERT_JOYSTICK_Z = false;
const bool DEFAULT_INVERT_JOYSTICK_X = false;
const bool DEFAULT_INVERT_JOYSTICK_Y = false;
const bool DEFAULT_INVERT_JOYSTICK_BUTTON = false;
bool JOYSTICK_ENABLED = DEFAULT_JOYSTICK_ENABLED;
bool JOYSTICK_Z_ENABLED = DEFAULT_JOYSTICK_Z_ENABLED;
bool JOYSTICK_X_ENABLED = DEFAULT_JOYSTICK_X_ENABLED;
bool JOYSTICK_Y_ENABLED = DEFAULT_JOYSTICK_Y_ENABLED;
bool JOYSTICK_BUTTON_TOGGLES_ON_OFF = DEFAULT_JOYSTICK_BUTTON_TOGGLES_ON_OFF;
int JOYSTICK_CENTER_SAMPLES = DEFAULT_JOYSTICK_CENTER_SAMPLES;
int JOYSTICK_OVERSAMPLES = DEFAULT_JOYSTICK_OVERSAMPLES;
int JOYSTICK_SAMPLE_INTERVAL_MS = DEFAULT_JOYSTICK_SAMPLE_INTERVAL_MS;
int JOYSTICK_ADC_MAX = DEFAULT_JOYSTICK_ADC_MAX;
int JOYSTICK_DEADBAND = DEFAULT_JOYSTICK_DEADBAND;
int JOYSTICK_PULSE_QUEUE_LIMIT = DEFAULT_JOYSTICK_PULSE_QUEUE_LIMIT;
float JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND = DEFAULT_JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND;
float JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND = DEFAULT_JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND;
bool INVERT_JOYSTICK_Z = DEFAULT_INVERT_JOYSTICK_Z;
bool INVERT_JOYSTICK_X = DEFAULT_INVERT_JOYSTICK_X;
bool INVERT_JOYSTICK_Y = DEFAULT_INVERT_JOYSTICK_Y;
bool INVERT_JOYSTICK_BUTTON = DEFAULT_INVERT_JOYSTICK_BUTTON;

int ENCODER_STEPS_INT = DEFAULT_ENCODER_PPR * 2; // Number of encoder impulses PCNT counts per revolution of the spindle
const int ENCODER_FILTER = 1; // Encoder pulses shorter than this will be ignored. Clock cycles, 1 - 1023.
const int PCNT_LIM = 31000; // Limit used in hardware pulse counter logic.
const int PCNT_CLEAR = 30000; // Limit where we reset hardware pulse counter value to avoid overflow. Less than PCNT_LIM.
const long DUPR_MAX = 254000; // No more than 1 inch pitch
const int32_t STARTS_MAX = 124; // No more than 124-start thread
const long PASSES_MAX = 999; // No more turn or face passes than this
const long DEFAULT_SAFE_DISTANCE_DU = 5000; // Step back 0.5mm from the material when moving between cuts in automated modes
long SAFE_DISTANCE_DU = DEFAULT_SAFE_DISTANCE_DU;
const long DEFAULT_SLOT_LEFT_REDUCTION_DU = 0; // Shorten each slotting pass by this Z distance to leave chip room in blind slots
long SLOT_LEFT_REDUCTION_DU = DEFAULT_SLOT_LEFT_REDUCTION_DU;
const long DEFAULT_CONE_DIA_BIG_DU = 500000; // Cone mode: biggest diameter of the workpiece, 50.00 mm
const long DEFAULT_CONE_DIA_SMALL_DU = 250000; // Cone mode: smallest diameter of the workpiece, 25.00 mm
long CONE_DIA_BIG_DU = DEFAULT_CONE_DIA_BIG_DU;
long CONE_DIA_SMALL_DU = DEFAULT_CONE_DIA_SMALL_DU;
const long SAVE_DELAY_US = 5000000; // Wait 5s after last save and last change of saveable data before saving again
const long DIRECTION_SETUP_DELAY_US = 10; // Stepper driver needs some time to adjust to direction change
const long STEPPED_ENABLE_DELAY_MS = 100; // Delay after stepper is enabled and before issuing steps

// Version of the pref storage format, should be changed when non-backward-compatible
// changes are made to the storage logic, resulting in Preferences wipe on first start.
#define PREFERENCES_VERSION 1
#define PREF_NAMESPACE "h5"
#define CONFIG_VERSION 1
#define CONFIG_NAMESPACE "h5cfg"
#define WIFI_CONFIG_VERSION 1
#define WIFI_CONFIG_NAMESPACE "h5wifi"
#define KEYBOARD_CONFIG_VERSION 1
#define KEYBOARD_CONFIG_NAMESPACE "h5keys"

// GCode-related constants.
const float LINEAR_INTERPOLATION_PRECISION = 0.1; // 0 < x <= 1, smaller values make for quicker G0 and G1 moves
const long GCODE_WAIT_EPSILON_STEPS = 10;
const bool SPINDLE_PAUSES_GCODE = true; // pause GCode execution when spindle stops
const int GCODE_MIN_RPM = 30; // pause GCode execution if RPM is below this

// To be incremented whenever a measurable improvement is made.
#define SOFTWARE_VERSION 64

// To be changed whenever a different PCB / encoder / stepper / ... design is used.
#define HARDWARE_VERSION 5

#define NANOELS_STRINGIFY_VALUE(value) #value
#define NANOELS_STRINGIFY(value) NANOELS_STRINGIFY_VALUE(value)
#define CONTROLLER_VERSION_TEXT "H" NANOELS_STRINGIFY(HARDWARE_VERSION) "V" NANOELS_STRINGIFY(SOFTWARE_VERSION)

#define Z_ENA 41
#define Z_DIR 42
#define Z_STEP 35

#define Z_PULSE_A 18
#define Z_PULSE_B 8

#define X_ENA 16
#define X_DIR 15
#define X_STEP 7

#define X_PULSE_A 47
#define X_PULSE_B 21

#define Y_ENA 1
#define Y_DIR 2
#define Y_STEP 17

#define Y_PULSE_A 46
#define Y_PULSE_B 3

#define JOY_Z 4
#define JOY_X 5
#define JOY_Y 6
#define JOY_BUTTON 38

#define KEY_DATA 37
#define KEY_CLOCK 36

const bool DEFAULT_SHOW_KEY_PRESSES = false;
bool SHOW_KEY_PRESSES = DEFAULT_SHOW_KEY_PRESSES;

#define B_LEFT 21 // Left arrow - controls Z axis movement to the left
#define B_RIGHT 22 // Right arrow - controls Z axis movement to the right
#define B_UP 23 // Up arrow - controls X axis movement forwards
#define B_DOWN 24 // Down arrow - controls X axis movement backwards
#define B_FORWARD 85 // u - Advance Y axis
#define B_BACK 74 // j - Retreat Y axis
#define B_MINUS 60 // Numpad minus - decrements the pitch or number of passes
#define B_PLUS 95 // Numpad plus - increments the pitch or number of passes
#define B_ON 30 // Enter - starts operation or mode
#define B_OFF 27 // ESC - stops operation or mode
#define B_STOPL 65 // a - sets left stop
#define B_STOPR 68 // d - sets right stop
#define B_STOPU 87 // w - sets forward stop
#define B_STOPD 83 // s - sets rear stop
#define B_STOPF 73 // i - Y forward stop
#define B_STOPB 75 // k - Y backward stop
#define B_MULTISTART 84 // t - multi-start thread button
#define B_DISPL 12 // Win - changes info displayed in the bottom line (angle, rpm, ...)
#define B_STEP 64 // Tilda - changes distance moved when movement buttons are used
#define B_MEASURE 77 // m - controls metric / imperial / tpi
#define B_REVERSE 82 // r - changes pitch sign (left / right thread)
#define B_DIAMETER 79 // o - sets X0 so that centerline is at the middle of a given diameter value
#define B_0 48 // 0 top row - for number entry
#define B_1 49 // 1 top row
#define B_2 50 // ...
#define B_3 51
#define B_4 52
#define B_5 53
#define B_6 54
#define B_7 55
#define B_8 56
#define B_9 57
#define B_BACKSPACE 28 // removes the last entered number
#define B_MODE_GEARS 97 // F1 - sets the mode to gearbox
#define B_MODE_TURN 98 // F2 - ...
#define B_MODE_FACE 99 // F3
#define B_MODE_CONE 100 // F4
#define B_MODE_CUT 101 // F5
#define B_MODE_THREAD 102 // F6
#define B_MODE_ASYNC 103 // F7
#define B_MODE_ELLIPSE 104 // F8
#define B_MODE_GCODE 105 // F9
#define B_MODE_Y 106 // F10
#define B_MODE 107 // F11 - cycles through modes
#define B_MODE_JOYSTICK 108 // F12 - sets the mode to joystick lathe
#define B_MODE_XGEAR 109 // screen-only - sets the mode to X gearbox
#define B_MODE_SLOT 110 // screen-only - sets the mode to slotting
#define B_X 88 // x - zeroes X axis
#define B_Z 90 // z - zeroes Z axis
#define B_Y 72 // h - zeroes Y axis
#define B_X_ENA 67 // c - enables / disables X axis
#define B_Z_ENA 81 // q - enables / disables Z axis
#define B_Y_ENA 89 // y - enables / disables Y axis

struct KeyboardBinding {
  const char* id;
  const char* label;
  byte actionCode;
  byte defaultCode;
  byte code;
};

struct WebUiEvent {
  byte actionCode;
  bool isPress;
};

#define KEY_BINDING(id, label, code) { id, label, code, code, code }

KeyboardBinding keyboardBindings[] = {
  KEY_BINDING("left", "Sinistra", B_LEFT),
  KEY_BINDING("right", "Destra", B_RIGHT),
  KEY_BINDING("up", "Su", B_UP),
  KEY_BINDING("down", "Giù", B_DOWN),
  KEY_BINDING("forward", "Y avanti", B_FORWARD),
  KEY_BINDING("back", "Y indietro", B_BACK),
  KEY_BINDING("minus", "Meno", B_MINUS),
  KEY_BINDING("plus", "Più", B_PLUS),
  KEY_BINDING("on", "On / avvia", B_ON),
  KEY_BINDING("off", "Off / stop", B_OFF),
  KEY_BINDING("stopL", "Imposta fermo Z sx", B_STOPL),
  KEY_BINDING("stopR", "Imposta fermo Z dx", B_STOPR),
  KEY_BINDING("stopU", "Imposta fermo X avanti", B_STOPU),
  KEY_BINDING("stopD", "Imposta fermo X dietro", B_STOPD),
  KEY_BINDING("stopF", "Imposta fermo Y avanti", B_STOPF),
  KEY_BINDING("stopB", "Imposta fermo Y dietro", B_STOPB),
  KEY_BINDING("multistart", "Avvii multipli", B_MULTISTART),
  KEY_BINDING("display", "Info display", B_DISPL),
  KEY_BINDING("step", "Incremento", B_STEP),
  KEY_BINDING("measure", "Unità di misura", B_MEASURE),
  KEY_BINDING("reverse", "Inverti passo", B_REVERSE),
  KEY_BINDING("diameter", "Imposta diametro", B_DIAMETER),
  KEY_BINDING("digit0", "Cifra 0", B_0),
  KEY_BINDING("digit1", "Cifra 1", B_1),
  KEY_BINDING("digit2", "Cifra 2", B_2),
  KEY_BINDING("digit3", "Cifra 3", B_3),
  KEY_BINDING("digit4", "Cifra 4", B_4),
  KEY_BINDING("digit5", "Cifra 5", B_5),
  KEY_BINDING("digit6", "Cifra 6", B_6),
  KEY_BINDING("digit7", "Cifra 7", B_7),
  KEY_BINDING("digit8", "Cifra 8", B_8),
  KEY_BINDING("digit9", "Cifra 9", B_9),
  KEY_BINDING("backspace", "Cancella", B_BACKSPACE),
  KEY_BINDING("modeGears", "Modalità ingranaggi", B_MODE_GEARS),
  KEY_BINDING("modeTurn", "Modalità tornitura", B_MODE_TURN),
  KEY_BINDING("modeFace", "Modalità spianatura", B_MODE_FACE),
  KEY_BINDING("modeCone", "Modalità cono", B_MODE_CONE),
  KEY_BINDING("modeCut", "Modalità troncatura", B_MODE_CUT),
  KEY_BINDING("modeThread", "Modalità filettatura", B_MODE_THREAD),
  KEY_BINDING("modeAsync", "Modalità asincrona", B_MODE_ASYNC),
  KEY_BINDING("modeEllipse", "Modalità ellisse", B_MODE_ELLIPSE),
  KEY_BINDING("modeGcode", "Modalità GCode", B_MODE_GCODE),
  KEY_BINDING("modeY", "Modalità Y", B_MODE_Y),
  KEY_BINDING("mode", "Menu modalità", B_MODE),
  KEY_BINDING("modeJoystick", "Modalità joystick", B_MODE_JOYSTICK),
  KEY_BINDING("modeXGear", "Modalità X ingranaggi", B_MODE_XGEAR),
  KEY_BINDING("modeSlot", "Modalità scanalatura", B_MODE_SLOT),
  KEY_BINDING("zeroX", "Azzera X", B_X),
  KEY_BINDING("zeroZ", "Azzera Z", B_Z),
  KEY_BINDING("zeroY", "Azzera Y", B_Y),
  KEY_BINDING("enableX", "Abilita X", B_X_ENA),
  KEY_BINDING("enableZ", "Abilita Z", B_Z_ENA),
  KEY_BINDING("enableY", "Abilita Y", B_Y_ENA),
};

const int KEYBOARD_BINDING_COUNT = sizeof(keyboardBindings) / sizeof(keyboardBindings[0]);

#define PREF_VERSION "v"
#define PREF_DUPR "d"
#define PREF_POS_Z "zp"
#define PREF_LEFT_STOP_Z "zls"
#define PREF_RIGHT_STOP_Z "zrs"
#define PREF_ORIGIN_POS_Z "zpo"
#define PREF_POS_GLOBAL_Z "zpg"
#define PREF_MOTOR_POS_Z "zpm"
#define PREF_DISABLED_Z "zd"
#define PREF_POS_X "xp"
#define PREF_LEFT_STOP_X "xls"
#define PREF_RIGHT_STOP_X "xrs"
#define PREF_ORIGIN_POS_X "xpo"
#define PREF_POS_GLOBAL_X "xpg"
#define PREF_MOTOR_POS_X "xpm"
#define PREF_DISABLED_X "xd"
#define PREF_POS_Y "y1p"
#define PREF_LEFT_STOP_Y "y1ls"
#define PREF_RIGHT_STOP_Y "y1rs"
#define PREF_ORIGIN_POS_Y "y1po"
#define PREF_POS_GLOBAL_Y "y1pg"
#define PREF_MOTOR_POS_Y "y1pm"
#define PREF_DISABLED_Y "y1d"
#define PREF_SPINDLE_POS "sp"
#define PREF_SPINDLE_POS_AVG "spa"
#define PREF_OUT_OF_SYNC "oos"
#define PREF_SPINDLE_POS_GLOBAL "spg"
#define PREF_SHOW_ANGLE "ang"
#define PREF_SHOW_TACHO "rpm"
#define PREF_STARTS "sta"
#define PREF_MODE "mod"
#define PREF_MEASURE "mea"
#define PREF_CONE_RATIO "cr"
#define PREF_TURN_PASSES "tp"
#define PREF_MOVE_STEP "ms"
#define PREF_AUX_FORWARD "af"

#define CFG_VERSION "v"
#define CFG_ENCODER_PPR "encPpr"
#define CFG_ENCODER_BACKLASH "encBacklash"
#define CFG_AXIS_ENCODER_BACKLASH "axisEncBacklash"
#define CFG_SCREW_Z_DU "zScrew"
#define CFG_MOTOR_STEPS_Z "zMotor"
#define CFG_SPEED_START_Z "zStart"
#define CFG_ACCELERATION_Z "zAccel"
#define CFG_SPEED_MANUAL_MOVE_Z "zManual"
#define CFG_INVERT_Z "zInv"
#define CFG_INVERT_Z_ENABLE "zInvEn"
#define CFG_NEEDS_REST_Z "zRest"
#define CFG_MAX_TRAVEL_MM_Z "zTravel"
#define CFG_BACKLASH_DU_Z "zBacklash"
#define CFG_SCREW_X_DU "xScrew"
#define CFG_MOTOR_STEPS_X "xMotor"
#define CFG_SPEED_START_X "xStart"
#define CFG_ACCELERATION_X "xAccel"
#define CFG_SPEED_MANUAL_MOVE_X "xManual"
#define CFG_INVERT_X "xInv"
#define CFG_INVERT_X_ENABLE "xInvEn"
#define CFG_NEEDS_REST_X "xRest"
#define CFG_MAX_TRAVEL_MM_X "xTravel"
#define CFG_BACKLASH_DU_X "xBacklash"
#define CFG_STEP_TIME_MS "stepMs"
#define CFG_DELAY_BETWEEN_STEPS_MS "stepDelay"
#define CFG_ENABLE_CONTINUOUS_MOVE "contStep"
#define CFG_SAFE_DISTANCE_DU "safeDistDu"
#define CFG_SLOT_LEFT_REDUCTION_DU "slotLeftDu"
#define CFG_CONE_DIA_BIG_DU "coneDiaBigDu"
#define CFG_CONE_DIA_SMALL_DU "coneDiaSmallDu"
#define CFG_ACTIVE_Y "yActive"
#define CFG_ROTARY_Y "yRotary"
#define CFG_MOTOR_STEPS_Y "yMotor"
#define CFG_SCREW_Y_DU "yScrew"
#define CFG_SPEED_START_Y "yStart"
#define CFG_ACCELERATION_Y "yAccel"
#define CFG_SPEED_MANUAL_MOVE_Y "yManual"
#define CFG_INVERT_Y "yInv"
#define CFG_INVERT_Y_ENABLE "yInvEn"
#define CFG_NEEDS_REST_Y "yRest"
#define CFG_MAX_TRAVEL_MM_Y "yTravel"
#define CFG_BACKLASH_DU_Y "yBacklash"
#define CFG_PULSE_PER_REVOLUTION "pulseRev"
#define CFG_PULSE_PER_REVOLUTION_Z "zPulseRev"
#define CFG_PULSE_PER_REVOLUTION_X "xPulseRev"
#define CFG_PULSE_PER_REVOLUTION_Y "yPulseRev"
#define CFG_JOYSTICK_ENABLED "joyOn"
#define CFG_JOYSTICK_Z_ENABLED "joyZOn"
#define CFG_JOYSTICK_X_ENABLED "joyXOn"
#define CFG_JOYSTICK_Y_ENABLED "joyYOn"
#define CFG_JOYSTICK_BUTTON_TOGGLES_ON_OFF "joyBtnOn"
#define CFG_JOYSTICK_CENTER_SAMPLES "joyCenter"
#define CFG_JOYSTICK_OVERSAMPLES "joyOver"
#define CFG_JOYSTICK_SAMPLE_INTERVAL_MS "joySample"
#define CFG_JOYSTICK_ADC_MAX "joyAdc"
#define CFG_JOYSTICK_DEADBAND "joyDead"
#define CFG_JOYSTICK_PULSE_QUEUE_LIMIT "joyQueue"
#define CFG_JOYSTICK_NORMAL_RPS "joyNormal"
#define CFG_JOYSTICK_RAPID_RPS "joyRapid"
#define CFG_INVERT_JOYSTICK_Z "joyInvZ"
#define CFG_INVERT_JOYSTICK_X "joyInvX"
#define CFG_INVERT_JOYSTICK_Y "joyInvY"
#define CFG_INVERT_JOYSTICK_BUTTON "joyInvB"

#define WCFG_VERSION "v"
#define WCFG_ENABLED "en"
#define WCFG_SSID "ssid"
#define WCFG_PASSWORD "pwd"

#define KCFG_VERSION "v"
#define KCFG_SHOW_KEY_PRESSES "showKeys"

#define MOVE_STEP_1 10000 // 1mm
#define MOVE_STEP_2 1000 // 0.1mm
#define MOVE_STEP_3 100 // 0.01mm

#define MOVE_STEP_IMP_1 25400 // 1/10"
#define MOVE_STEP_IMP_2 2540 // 1/100"
#define MOVE_STEP_IMP_3 254 // 1/1000" also known as 1 thou

#define MODE_NORMAL 0
#define MODE_XGEAR 1
#define MODE_ASYNC 2
#define MODE_CONE 3
#define MODE_TURN 4
#define MODE_FACE 5
#define MODE_CUT 6
#define MODE_THREAD 7
#define MODE_ELLIPSE 8
#define MODE_GCODE 9
#define MODE_Y 10
#define MODE_JOYSTICK 11
#define MODE_SLOT 12

#define MEASURE_METRIC 0
#define MEASURE_INCH 1
#define MEASURE_TPI 2

#define ESTOP_NONE 0
#define ESTOP_POS 2
#define ESTOP_MARK_ORIGIN 3
#define ESTOP_ON_OFF 4
#define ESTOP_OFF_MANUAL_MOVE 5

#define TIMER_FREQ 1000000 // 1MHz async timer frequency

enum PulseCounter {
  PULSE_COUNTER_SPINDLE,
  PULSE_COUNTER_Z,
  PULSE_COUNTER_X,
  PULSE_COUNTER_Y,
  PULSE_COUNTER_COUNT
};

struct CircleBuffer {
  char* buffer;
  size_t head;
  size_t tail;
  size_t size;
};

#include <FS.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>
#include <WebSocketsServer.h> // install via Libraries as "WebSockets"
#include <driver/pulse_cnt.h>
#include <Preferences.h>
#include <PS2KeyAdvanced.h> // install via Libraries as "PS2KeyAdvanced"
#include <soc/soc.h>

const long NEXTION_NORMAL_BAUD = 115200;
const long NEXTION_FIRST_UPLOAD_BAUD = 9600;
const long NEXTION_UPLOAD_BAUD = 115200;
const int NEXTION_TFT_PACKET_SIZE = 4096;
const unsigned long NEXTION_CONNECT_TIMEOUT_MS = 2000;
const unsigned long NEXTION_ACK_TIMEOUT_MS = 5000;

const char indexhtml[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="it">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>NanoEls H5</title>
  <link rel="icon" href="data:;base64,">
  <style>
    :root {
      --bg: #f4f6f8;
      --panel: #fff;
      --border: #c9d0d6;
      --text: #222;
      --muted: #5d6770;
      --primary: #217346;
      --primary-dark: #14572f;
      --secondary: #59636d;
      --secondary-dark: #3f474f;
      --link: #0a5d9f;
      color-scheme: light;
    }
    * {
      box-sizing: border-box;
    }
    body {
      background-color: var(--bg);
      color: var(--text);
      font-family: Roboto, Arial, sans-serif;
      font-size: 17px;
      margin: 0;
    }
    a {
      color: var(--link);
    }
    .page-shell {
      margin: 0 auto;
      max-width: 920px;
      padding: 16px;
    }
    h1, h2 {
      color: var(--text);
      margin: 0;
    }
    h1 {
      font-size: 1.8rem;
    }
    h2 {
      font-size: 1.35rem;
    }
    h3 {
      font-size: 1.08rem;
      margin: 0 0 10px;
    }
    p {
      line-height: 1.4;
      margin: 8px 0;
    }
    .app-footer {
      color: var(--muted);
      font-size: 0.85rem;
      line-height: 1.35;
      margin-top: 18px;
      text-align: center;
    }
    body.control-section-active .app-footer {
      display: none;
    }
    body.control-section-active.control-fullscreen-active .page-topbar {
      display: none;
    }
    .app-footer p {
      margin: 0;
    }
    .section-note, .action-status {
      color: var(--muted);
    }
    .notice {
      background: #fff7e8;
      border: 1px solid #e0b46a;
      border-radius: 4px;
      margin: 0;
      padding: 10px 12px;
    }
    [hidden] {
      display: none !important;
    }
    .page-topbar {
      align-items: center;
      background: var(--bg);
      border-bottom: 1px solid var(--border);
      display: none;
      gap: 10px;
      margin: 0 0 14px;
      padding: 8px 0;
      position: sticky;
      top: 0;
      z-index: 10;
    }
    body.page-open .page-topbar {
      display: flex;
    }
    body.control-fullscreen-active .page-topbar {
      display: none;
    }
    .page-back {
      align-items: center;
      background: #e7ecef;
      border: 1px solid var(--border);
      border-radius: 8px;
      color: var(--text);
      display: inline-flex;
      flex: 0 0 auto;
      font-size: 1rem;
      font-weight: 700;
      gap: 6px;
      min-height: 42px;
      padding: 8px 14px;
      text-decoration: none;
    }
    .page-back:hover {
      background: #d9e1e6;
    }
    .page-back svg {
      height: 18px;
      width: 18px;
    }
    .page-title {
      font-size: 1.15rem;
      font-weight: 800;
      margin: 0;
      min-width: 0;
      overflow: hidden;
      text-overflow: ellipsis;
      white-space: nowrap;
    }
    .home-brand {
      align-items: center;
      display: flex;
      gap: 12px;
      margin: 8px 0 18px;
    }
    .home-logo {
      align-items: center;
      background: var(--primary);
      border-radius: 12px;
      color: #fff;
      display: flex;
      flex: 0 0 auto;
      height: 52px;
      justify-content: center;
      width: 52px;
    }
    .home-logo svg {
      height: 30px;
      width: 30px;
    }
    .home-title {
      font-size: 1.65rem;
    }
    .home-subtitle {
      color: var(--muted);
      margin: 2px 0 0;
    }
    .home-grid {
      display: grid;
      gap: 12px;
      grid-template-columns: repeat(auto-fill, minmax(260px, 1fr));
    }
    .home-card {
      align-items: start;
      background: var(--panel);
      border: 1px solid var(--border);
      border-radius: 10px;
      box-shadow: 0 2px 6px rgba(20, 40, 60, 0.06);
      color: var(--text);
      display: grid;
      gap: 4px 12px;
      grid-template-areas:
        "icon title chevron"
        "icon desc chevron";
      grid-template-columns: 48px minmax(0, 1fr) 16px;
      padding: 14px;
      text-decoration: none;
      transition: border-color 0.12s ease, box-shadow 0.12s ease, transform 0.12s ease;
    }
    .home-card:hover {
      border-color: var(--primary);
      box-shadow: 0 6px 16px rgba(20, 40, 60, 0.14);
      transform: translateY(-1px);
    }
    .home-card:active {
      transform: translateY(0);
    }
    .home-icon {
      align-items: center;
      background: #e6f2ea;
      border-radius: 10px;
      color: var(--primary);
      display: flex;
      grid-area: icon;
      height: 48px;
      justify-content: center;
      width: 48px;
    }
    .home-icon svg {
      height: 27px;
      width: 27px;
    }
    .home-card-title {
      align-self: end;
      font-size: 1.1rem;
      font-weight: 800;
      grid-area: title;
    }
    .home-card-desc {
      color: var(--muted);
      font-size: 0.92rem;
      grid-area: desc;
      line-height: 1.32;
    }
    .home-chevron {
      align-self: center;
      color: var(--muted);
      font-size: 1.5rem;
      grid-area: chevron;
      line-height: 1;
    }
    .app-section {
      display: none;
    }
    .app-section.active {
      display: block;
    }
    .section-header {
      display: grid;
      gap: 4px;
      margin-bottom: 12px;
    }
    .section-stack {
      display: grid;
      gap: 14px;
    }
    .panel, .config-section {
      background-color: var(--panel);
      border: 1px solid var(--border);
      border-radius: 4px;
      padding: 12px;
    }
    input[type=text], input[type=file], input[type=number], input[type=password], textarea, select {
      border: 1px solid var(--border);
      border-radius: 4px;
      color: var(--text);
      font: inherit;
      padding: 10px;
      width: 100%;
    }
    #log {
      background-color: var(--panel);
      border: 1px solid var(--border);
      border-radius: 4px;
      height: 260px;
      margin-bottom: 12px;
      overflow-y: scroll;
      padding: 10px;
    }
    #log p {
      margin: 0;
      padding: 0;
    }
    #command-container {
      display: flex;
      align-items: center;
      gap: 10px;
      margin-bottom: 12px;
    }
    #command {
      flex: 1;
    }
    button, .button-like {
      background-color: var(--primary);
      border: none;
      border-radius: 4px;
      color: #fff;
      cursor: pointer;
      display: inline-block;
      font: inherit;
      min-height: 40px;
      padding: 10px 18px;
      text-align: center;
    }
    button:hover, .button-like:hover {
      background-color: var(--primary-dark);
    }
    #gcode-list {
      background-color: var(--panel);
      border: 1px solid var(--border);
      border-radius: 4px;
      margin-top: 10px;
      padding: 0;
    }
    #gcode-list.empty {
      padding: 10px;
      text-align: center;
    }
    #gcode-name, #gcode-content {
      margin-bottom: 10px;
    }
    #gcode-content {
      height: 200px;
      resize: vertical;
    }
    .remove-icon {
      cursor: pointer;
      color: #dc3545;
      font-size: 16px;
      width: 20px;
    }
    .remove-icon:hover {
      color: #c82333;
    }
    button.disabled, .button-like.disabled {
      background-color: #b7bec5;
      cursor: not-allowed;
      pointer-events: none;
    }
    button.disabled:hover, .button-like.disabled:hover {
      background-color: #b7bec5;
    }
    .gcode-row {
      align-items: center;
      display: flex;
      gap: 10px;
      justify-content: space-between;
      min-height: 44px;
      padding: 10px;
      cursor: pointer;
    }
    .gcode-row:hover {
      background-color: #f0f0f0;
    }
    .gcode-item {
      flex: 1;
      min-width: 0;
      overflow-wrap: anywhere;
    }
    .gcode-size {
      flex-basis: 80px;
      font-size: 0.9em;
      color: var(--muted);
    }
    .checkbox-container {
      align-items: center;
      display: flex;
      flex-wrap: wrap;
      gap: 10px;
      margin-bottom: 10px;
    }
    .checkbox-container input {
      margin: 0;
    }
    .config-grid {
      display: grid;
      gap: 10px 16px;
      grid-template-columns: repeat(auto-fit, minmax(220px, 1fr));
    }
    .config-field {
      display: grid;
      gap: 6px;
    }
    .config-label {
      font-weight: 600;
    }
    .config-unit {
      color: var(--muted);
      font-weight: 400;
    }
    .config-help {
      color: var(--muted);
      font-size: 0.85em;
      line-height: 1.35;
    }
    .config-checkbox {
      align-items: center;
      display: flex;
      gap: 8px;
      min-height: 34px;
    }
    .config-checkbox-field {
      align-content: start;
    }
    .config-checkbox-field .config-checkbox {
      min-height: 0;
    }
    .config-actions {
      align-items: center;
      display: flex;
      flex-wrap: wrap;
      gap: 10px;
      margin: 10px 0;
    }
    .sticky-actions {
      background: rgba(244, 246, 248, 0.96);
      border: 1px solid var(--border);
      border-radius: 4px;
      bottom: 0;
      margin-top: 12px;
      padding: 10px;
      position: sticky;
      z-index: 8;
    }
    .action-status {
      flex: 1 1 220px;
      min-height: 1.2em;
      overflow-wrap: anywhere;
    }
    #config-fields, #keyboard-fields {
      display: grid;
      gap: 10px;
      margin: 10px 0;
    }
    .settings-group, .keyboard-group {
      padding: 0;
    }
    .settings-group summary, .keyboard-group summary {
      cursor: pointer;
      font-weight: 700;
      padding: 12px;
    }
    .settings-group[open] summary, .keyboard-group[open] summary {
      border-bottom: 1px solid var(--border);
    }
    .settings-group .config-grid, .keyboard-group .keyboard-grid {
      padding: 12px;
    }
    .accessibility-settings .config-actions {
      padding: 0 12px 12px;
    }
    .config-field > .config-help {
      color: var(--muted);
      display: block;
      line-height: 1.35;
    }
    .keyboard-grid {
      display: grid;
      gap: 10px 16px;
      grid-template-columns: repeat(auto-fit, minmax(260px, 1fr));
    }
    .keyboard-binding {
      align-items: center;
      display: grid;
      gap: 6px 8px;
      grid-template-columns: minmax(110px, 1fr) 78px auto;
    }
    .keyboard-binding label {
      font-weight: 600;
    }
    .keyboard-binding input[type=number] {
      width: 100%;
    }
    .keyboard-binding button {
      padding: 8px 10px;
      white-space: nowrap;
    }
    button.secondary {
      background-color: var(--secondary);
    }
    button.secondary:hover {
      background-color: var(--secondary-dark);
    }
    #gcode-upload-controls, #tft-upload-controls, #firmware-upload-controls {
      align-items: center;
      display: flex;
      flex-wrap: wrap;
      gap: 10px;
      margin-bottom: 10px;
    }
    #gcode-file, #tft-file, #firmware-file {
      display: none;
    }
    #tft-upload-controls input, #firmware-upload-controls input {
      margin-left: 10px;
    }
    #tft-progress, #firmware-progress {
      width: 100%;
      margin-top: 10px;
    }
    #tft-status, #firmware-status {
      min-height: 1.2em;
    }
    .control-status-panel {
      padding: 12px;
    }
    .control-status-grid {
      display: grid;
      gap: 10px;
      grid-template-columns: repeat(auto-fit, minmax(120px, 1fr));
    }
    .control-status-item {
      background: #f8fafb;
      border: 1px solid var(--border);
      border-radius: 4px;
      min-height: 62px;
      padding: 10px;
    }
    .control-status-button {
      cursor: pointer;
      user-select: none;
    }
    .control-status-button:hover {
      background: #edf3f7;
    }
    .control-status-button.active {
      background: #d8ecf6;
      border-color: var(--primary);
    }
    .control-status-button.disabled {
      cursor: not-allowed;
      opacity: 0.58;
    }
    .control-status-label {
      color: var(--muted);
      display: block;
      font-size: 0.86rem;
      font-weight: 700;
      margin-bottom: 6px;
      text-transform: uppercase;
    }
    .control-status-value {
      display: block;
      font-size: 1.28rem;
      font-weight: 700;
      overflow-wrap: anywhere;
    }
    .control-axis-stops {
      color: var(--muted);
      display: block;
      font-size: 0.9rem;
      font-weight: 700;
      margin-top: 3px;
      overflow: hidden;
      text-overflow: ellipsis;
      white-space: nowrap;
    }
    .control-mode-pitch {
      display: none;
    }
    .control-extra-toggle {
      cursor: pointer;
    }
    .control-mobile-tabs, .control-bottom-bar {
      display: none;
    }
    .control-message {
      grid-column: 1 / -1;
    }
    .control-message-heading {
      align-items: baseline;
      display: flex;
      gap: 8px;
      justify-content: space-between;
      min-width: 0;
    }
    .control-action-status {
      color: var(--muted);
      flex: 1;
      font-size: 0.9rem;
      font-weight: 700;
      min-width: 0;
      overflow: hidden;
      text-align: right;
      text-overflow: ellipsis;
      white-space: nowrap;
    }
    .control-grid {
      display: grid;
      gap: 14px;
      grid-template-columns: repeat(auto-fit, minmax(260px, 1fr));
    }
    .control-panel {
      align-content: start;
      display: grid;
      gap: 10px;
    }
    .control-button-grid, .control-numpad {
      display: grid;
      gap: 8px;
      grid-template-columns: repeat(3, minmax(0, 1fr));
    }
    .control-jog-grid {
      display: grid;
      gap: 8px;
      grid-template-columns: repeat(3, minmax(0, 1fr));
    }
    .control-jog-arrow {
      align-items: center;
      display: grid;
      gap: 2px;
      justify-items: center;
      min-height: 72px;
    }
    .control-jog-symbol {
      font-size: 1.9rem;
      font-weight: 800;
      line-height: 1;
    }
    .control-jog-axis {
      font-size: 0.82rem;
      font-weight: 700;
      line-height: 1;
    }
    .control-jog-up {
      grid-column: 2;
      grid-row: 1;
    }
    .control-jog-left {
      grid-column: 1;
      grid-row: 2;
    }
    .control-jog-center {
      align-self: stretch;
      background: #e7ecef;
      border: 1px solid var(--border);
      border-radius: 4px;
      grid-column: 2;
      grid-row: 2;
      min-height: 72px;
    }
    .control-jog-right {
      grid-column: 3;
      grid-row: 2;
    }
    .control-jog-down {
      grid-column: 2;
      grid-row: 3;
    }
    .control-jog-y-forward {
      grid-column: 1 / 3;
      grid-row: 4;
    }
    .control-jog-y-back {
      grid-column: 3;
      grid-row: 4;
    }
    .control-button {
      font-size: 1.05rem;
      min-height: 54px;
      padding: 8px;
      touch-action: manipulation;
      user-select: none;
      width: 100%;
    }
    .control-button.hold {
      touch-action: none;
    }
    .control-button.active {
      background-color: #0f5f87;
    }
    .control-button.active:hover {
      background-color: #0f5f87;
    }
    .control-button.neutral {
      background-color: var(--secondary);
    }
    .control-button.neutral:hover {
      background-color: var(--secondary-dark);
    }
    .control-button.warning {
      background-color: #a05a00;
    }
    .control-button.warning:hover {
      background-color: #7c4400;
    }
    .control-button.danger {
      background-color: #b3261e;
    }
    .control-button.danger:hover {
      background-color: #8f1f18;
    }
    .control-button.mode {
      background-color: #0f5f87;
    }
    .control-button.mode:hover {
      background-color: #0b4968;
    }
    .control-button.mode-long-label {
      font-size: 0.85rem;
    }
    .control-wide {
      grid-column: span 2;
    }
    @media (max-width: 640px) {
      .page-shell {
        padding: 10px;
      }
      h1 {
        font-size: 1.55rem;
      }
      .page-topbar {
        margin-left: -10px;
        margin-right: -10px;
        padding: 8px 10px;
      }
      .page-title {
        font-size: 1.08rem;
      }
      .home-brand {
        margin: 4px 0 14px;
      }
      .home-grid {
        grid-template-columns: 1fr;
      }
      .home-card {
        grid-template-columns: 44px minmax(0, 1fr) 16px;
        padding: 12px;
      }
      .home-icon {
        height: 44px;
        width: 44px;
      }
      .home-icon svg {
        height: 25px;
        width: 25px;
      }
      .config-grid, .keyboard-grid {
        grid-template-columns: 1fr;
      }
      .keyboard-binding {
        grid-template-columns: minmax(0, 1fr) 82px 76px;
      }
      #command-container {
        align-items: stretch;
        flex-direction: column;
      }
      #command-container button {
        width: 100%;
      }
      .config-actions, .sticky-actions {
        align-items: stretch;
        flex-direction: column;
      }
      .config-actions button, .sticky-actions button {
        width: 100%;
      }
      .action-status {
        flex-basis: auto;
        width: 100%;
      }
      #gcode-content {
        height: 180px;
      }
      #log {
        height: 220px;
      }
      #section-control.active {
        padding-bottom: 82px;
      }
      .control-stack {
        gap: 10px;
      }
      .control-status-panel {
        background: rgba(255, 255, 255, 0.96);
        border: 1px solid var(--border);
        border-radius: 4px;
        box-shadow: 0 3px 10px rgba(0, 0, 0, 0.08);
        padding: 8px;
      }
      .control-status-grid {
        gap: 6px;
        grid-template-columns: repeat(3, minmax(0, 1fr));
      }
      .control-status-item {
        min-height: 54px;
        min-width: 0;
        padding: 8px;
      }
      .control-status-panel.control-y-active .control-status-grid {
        grid-template-columns: repeat(4, minmax(0, 1fr));
      }
      .control-status-extra {
        display: none;
      }
      .control-status-panel.control-extra-visible .control-status-extra {
        display: block;
      }
      .control-status-panel.control-extra-visible .control-message {
        border-color: var(--primary);
      }
      .control-status-label {
        font-size: 0.82rem;
        margin-bottom: 4px;
      }
      .control-status-value {
        font-size: 1.18rem;
        overflow: hidden;
        text-overflow: ellipsis;
        white-space: nowrap;
      }
      .control-axis-stops {
        font-size: 0.86rem;
      }
      .control-mode-pitch {
        color: var(--muted);
        display: block;
        font-size: 0.86rem;
        font-weight: 700;
        margin-top: 3px;
        overflow: hidden;
        text-overflow: ellipsis;
        white-space: nowrap;
      }
      .control-status-panel.control-extra-visible .control-mode-pitch {
        display: none;
      }
      .control-mobile-tabs {
        display: grid;
        gap: 6px;
        grid-template-columns: repeat(5, minmax(0, 1fr));
      }
      .control-mobile-tab {
        background: #e7ecef;
        border: 1px solid var(--border);
        color: var(--text);
        font-size: 0.98rem;
        font-weight: 700;
        min-height: 44px;
        padding: 8px 4px;
      }
      .control-mobile-tab.active {
        background: var(--primary);
        border-color: var(--primary);
        color: #fff;
      }
      .control-grid {
        display: block;
      }
      .control-panel {
        display: none;
      }
      .control-panel.active {
        display: grid;
      }
      .control-button {
        font-size: 1.14rem;
        min-height: 62px;
        padding: 8px 6px;
      }
      .control-jog-arrow, .control-jog-center {
        min-height: 68px;
      }
      .control-jog-symbol {
        font-size: 2rem;
      }
      .control-bottom-bar {
        align-items: center;
        background: rgba(255, 255, 255, 0.97);
        border-top: 1px solid var(--border);
        bottom: 0;
        box-shadow: 0 -4px 14px rgba(0, 0, 0, 0.14);
        gap: 8px;
        grid-template-columns: 60px minmax(0, 1fr) 68px 78px 78px;
        left: 0;
        padding: 8px 10px calc(8px + env(safe-area-inset-bottom));
        position: fixed;
        right: 0;
        z-index: 30;
      }
      #section-control.active .control-bottom-bar {
        display: grid;
      }
      .control-bottom-state {
        min-width: 0;
      }
      .control-bottom-state .control-status-label, .control-bottom-rpm .control-status-label {
        font-size: 0.78rem;
        margin-bottom: 2px;
      }
      .control-bottom-state .control-status-value, .control-bottom-rpm .control-status-value {
        font-size: 1.18rem;
        overflow: hidden;
        text-overflow: ellipsis;
        white-space: nowrap;
      }
      .control-bottom-rpm {
        min-width: 0;
      }
      .control-bottom-button {
        min-height: 52px;
      }
      .control-fullscreen-button {
        background: #e7ecef;
        border: 1px solid var(--border);
        color: var(--text);
        min-height: 52px;
        padding: 8px 4px;
      }
      .control-fullscreen-button:hover {
        background: #d9e1e6;
      }
    }
  </style>
</head>
<body>
  <div class="page-shell">
    <nav class="page-topbar" aria-label="Navigazione pagina">
      <a href="#home" class="page-back" aria-label="Torna al menu principale">
        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true"><path d="m15 18-6-6 6-6"/></svg>
        Menu
      </a>
      <h2 id="page-title" class="page-title">Comando</h2>
    </nav>

    <main>
      <section id="section-home" class="app-section home-section" data-section="home">
        <header class="home-brand">
          <span class="home-logo" aria-hidden="true">
            <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><circle cx="11" cy="12" r="4.5"/><path d="M3 12h2M17 12h4M11 3v2M11 19v2"/></svg>
          </span>
          <div>
            <h1 class="home-title">NanoEls H5</h1>
            <p class="home-subtitle">Scegli una funzione per aprire la pagina dedicata.</p>
          </div>
        </header>
        <div class="home-grid">
          <a class="home-card" href="#control" data-section-link="control">
            <span class="home-icon" aria-hidden="true">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><rect x="2" y="7" width="20" height="10" rx="5"/><path d="M7 10v4M5 12h4M16 11h.01M18.5 13h.01"/></svg>
            </span>
            <span class="home-card-title">Comando</span>
            <span class="home-card-desc">Jog X/Z, ON e OFF, modalità di lavoro, tastierino e finecorsa.</span>
            <span class="home-chevron" aria-hidden="true">&rsaquo;</span>
          </a>
          <a class="home-card" href="#gcode" data-section-link="gcode">
            <span class="home-icon" aria-hidden="true">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M14 3H7a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h10a2 2 0 0 0 2-2V8z"/><path d="M14 3v5h5"/><path d="m10 12-2 2 2 2M14 12l2 2-2 2"/></svg>
            </span>
            <span class="home-card-title">GCode</span>
            <span class="home-card-desc">File salvati in memoria, creazione e invio di nuovi programmi.</span>
            <span class="home-chevron" aria-hidden="true">&rsaquo;</span>
          </a>
          <a class="home-card" href="#updates" data-section-link="updates">
            <span class="home-icon" aria-hidden="true">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M12 3v12"/><path d="m7 8 5-5 5 5"/><path d="M4 15v3a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2v-3"/></svg>
            </span>
            <span class="home-card-title">Aggiornamenti</span>
            <span class="home-card-desc">Carica il firmware ESP32 o aggiorna il display Nextion.</span>
            <span class="home-chevron" aria-hidden="true">&rsaquo;</span>
          </a>
          <a class="home-card" href="#wifi" data-section-link="wifi">
            <span class="home-icon" aria-hidden="true">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M2 9a15 15 0 0 1 20 0"/><path d="M5 12.5a10 10 0 0 1 14 0"/><path d="M8.5 16a5.5 5.5 0 0 1 7 0"/><path d="M12 19.5h.01"/></svg>
            </span>
            <span class="home-card-title">WiFi</span>
            <span class="home-card-desc">Attiva la rete, imposta nome e password o dimentica la connessione.</span>
            <span class="home-chevron" aria-hidden="true">&rsaquo;</span>
          </a>
          <a class="home-card" href="#ui" data-section-link="ui">
            <span class="home-icon" aria-hidden="true">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M4 7h16M4 12h16M4 17h16"/><circle cx="9" cy="7" r="2.2" fill="#fff"/><circle cx="15" cy="12" r="2.2" fill="#fff"/><circle cx="7" cy="17" r="2.2" fill="#fff"/></svg>
            </span>
            <span class="home-card-title">Interfaccia</span>
            <span class="home-card-desc">Voce, annunci di accessibilità e velocità di lettura.</span>
            <span class="home-chevron" aria-hidden="true">&rsaquo;</span>
          </a>
          <a class="home-card" href="#settings" data-section-link="settings">
            <span class="home-icon" aria-hidden="true">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.6" stroke-linecap="round" stroke-linejoin="round"><path d="M12.22 2h-.44a2 2 0 0 0-2 2v.18a2 2 0 0 1-1 1.73l-.43.25a2 2 0 0 1-2 0l-.15-.08a2 2 0 0 0-2.73.73l-.22.38a2 2 0 0 0 .73 2.73l.15.1a2 2 0 0 1 1 1.72v.51a2 2 0 0 1-1 1.74l-.15.09a2 2 0 0 0-.73 2.73l.22.38a2 2 0 0 0 2.73.73l.15-.08a2 2 0 0 1 2 0l.43.25a2 2 0 0 1 1 1.73V20a2 2 0 0 0 2 2h.44a2 2 0 0 0 2-2v-.18a2 2 0 0 1 1-1.73l.43-.25a2 2 0 0 1 2 0l.15.08a2 2 0 0 0 2.73-.73l.22-.39a2 2 0 0 0-.73-2.73l-.15-.08a2 2 0 0 1-1-1.74v-.5a2 2 0 0 1 1-1.74l.15-.09a2 2 0 0 0 .73-2.73l-.22-.38a2 2 0 0 0-2.73-.73l-.15.08a2 2 0 0 1-2 0l-.43-.25a2 2 0 0 1-1-1.73V4a2 2 0 0 0-2-2z"/><circle cx="12" cy="12" r="3"/></svg>
            </span>
            <span class="home-card-title">Impostazioni</span>
            <span class="home-card-desc">Parametri macchina e configurazione generale del controller.</span>
            <span class="home-chevron" aria-hidden="true">&rsaquo;</span>
          </a>
          <a class="home-card" href="#keyboard" data-section-link="keyboard">
            <span class="home-icon" aria-hidden="true">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><rect x="2" y="6" width="20" height="12" rx="2"/><path d="M6 10h.01M10 10h.01M14 10h.01M18 10h.01M8 14h.01M12 14h.01M16 14h.01"/></svg>
            </span>
            <span class="home-card-title">Tastiera</span>
            <span class="home-card-desc">Mappatura dei tasti fisici e tasti premuti a schermo.</span>
            <span class="home-chevron" aria-hidden="true">&rsaquo;</span>
          </a>
          <a class="home-card" href="#logs" data-section-link="logs">
            <span class="home-icon" aria-hidden="true">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="4" width="18" height="16" rx="2"/><path d="m7 9 3 3-3 3M13 15h4"/></svg>
            </span>
            <span class="home-card-title">Registro</span>
            <span class="home-card-desc">Log in tempo reale, comandi manuali e comandi websocket.</span>
            <span class="home-chevron" aria-hidden="true">&rsaquo;</span>
          </a>
        </div>
      </section>

      <section id="section-control" class="app-section" data-section="control" data-page-title="Comando">
        <div class="section-stack control-stack">
          <section id="control-status" class="panel control-status-panel" aria-label="Stato controller">
            <div class="control-status-grid">
              <div class="control-status-item control-status-button" data-control-shortcut-panel="modes" role="button" tabindex="0" aria-label="Apri modalità">
                <span class="control-status-label">Modo</span>
                <span id="control-mode" class="control-status-value">--</span>
                <span id="control-mode-pitch" class="control-mode-pitch">--</span>
              </div>
              <div class="control-status-item control-status-button" data-control-shortcut-action="88" data-control-shortcut-label="Azzera X" role="button" tabindex="0" aria-label="Azzera X">
                <span class="control-status-label">X</span>
                <span id="control-x" class="control-status-value">--</span>
                <span id="control-x-inline-stops" class="control-axis-stops">--</span>
              </div>
              <div class="control-status-item control-status-button" data-control-shortcut-action="90" data-control-shortcut-label="Azzera Z" role="button" tabindex="0" aria-label="Azzera Z">
                <span class="control-status-label">Z</span>
                <span id="control-z" class="control-status-value">--</span>
                <span id="control-z-inline-stops" class="control-axis-stops">--</span>
              </div>
              <div class="control-status-item control-status-button control-y" data-control-shortcut-action="72" data-control-shortcut-label="Azzera Y" role="button" tabindex="0" aria-label="Azzera Y" hidden>
                <span class="control-status-label">Y</span>
                <span id="control-y" class="control-status-value">--</span>
                <span id="control-y-inline-stops" class="control-axis-stops">--</span>
              </div>
              <div class="control-status-item control-status-button control-status-extra" data-control-shortcut-action="27" data-control-shortcut-label="OFF" role="button" tabindex="0" aria-label="Spegni controller">
                <span class="control-status-label">Stato</span>
                <span id="control-state" class="control-status-value">--</span>
              </div>
              <div class="control-status-item control-status-button control-status-extra" data-control-shortcut-action="82" data-control-shortcut-label="Inverti" role="button" tabindex="0" aria-label="Inverti passo">
                <span class="control-status-label">Passo</span>
                <span id="control-pitch" class="control-status-value">--</span>
              </div>
              <div class="control-status-item control-status-button control-status-extra" data-control-shortcut-action="77" data-control-shortcut-label="Unità" role="button" tabindex="0" aria-label="Cambia unità">
                <span class="control-status-label">Unità</span>
                <span id="control-measure" class="control-status-value">--</span>
              </div>
              <div class="control-status-item control-status-button control-status-extra" data-control-shortcut-action="64" data-control-shortcut-label="Incremento" role="button" tabindex="0" aria-label="Cambia incremento">
                <span class="control-status-label">Incremento</span>
                <span id="control-step" class="control-status-value">--</span>
              </div>
              <div class="control-status-item control-status-button control-status-extra" data-control-shortcut-action="27" data-control-shortcut-label="Stop" role="button" tabindex="0" aria-label="Azzera giri e angolo">
                <span class="control-status-label">Giri</span>
                <span id="control-turns" class="control-status-value">--</span>
              </div>
              <div class="control-status-item control-status-button control-status-extra" data-control-shortcut-action="27" data-control-shortcut-label="Stop" role="button" tabindex="0" aria-label="Azzera giri e angolo">
                <span class="control-status-label">Angolo</span>
                <span id="control-angle" class="control-status-value">--</span>
              </div>
              <div class="control-status-item control-status-extra">
                <span class="control-status-label">RPM</span>
                <span id="control-rpm" class="control-status-value">--</span>
              </div>
              <div class="control-status-item control-message control-extra-toggle" data-control-extra-toggle role="button" tabindex="0" aria-label="Mostra o nascondi dettagli controller" aria-expanded="false">
                <div class="control-message-heading">
                  <span class="control-status-label">Messaggio</span>
                  <span class="control-action-status" data-control-action-status role="status" aria-live="polite"></span>
                </div>
                <span id="control-message" class="control-status-value">--</span>
              </div>
            </div>
          </section>

          <div class="control-mobile-tabs" role="tablist" aria-label="Gruppi di comando">
            <button type="button" class="control-mobile-tab active" data-control-panel-tab="jog">Jog</button>
            <button type="button" class="control-mobile-tab" data-control-panel-tab="run">Esegui</button>
            <button type="button" class="control-mobile-tab" data-control-panel-tab="numpad">Tastierino</button>
            <button type="button" class="control-mobile-tab" data-control-panel-tab="stops">Finecorsa</button>
            <button type="button" class="control-mobile-tab" data-control-panel-tab="modes">Modalità</button>
          </div>
          <div class="control-grid">
            <section class="panel control-panel active" data-control-panel="jog">
              <h3>Jog</h3>
              <div class="control-jog-grid">
                <button type="button" class="control-button hold control-jog-arrow control-jog-up" data-control-action="23" data-control-hold="1" data-control-label="X avanti" aria-label="Jog X avanti" title="X avanti">
                  <span class="control-jog-symbol">↑</span>
                  <span class="control-jog-axis">X</span>
                </button>
                <button type="button" class="control-button hold control-jog-arrow control-jog-left" data-control-action="21" data-control-hold="1" data-control-label="Z sinistra" aria-label="Jog Z sinistra" title="Z sinistra">
                  <span class="control-jog-symbol">←</span>
                  <span class="control-jog-axis">Z</span>
                </button>
                <div class="control-jog-center" aria-hidden="true"></div>
                <button type="button" class="control-button hold control-jog-arrow control-jog-right" data-control-action="22" data-control-hold="1" data-control-label="Z destra" aria-label="Jog Z destra" title="Z destra">
                  <span class="control-jog-symbol">→</span>
                  <span class="control-jog-axis">Z</span>
                </button>
                <button type="button" class="control-button hold control-jog-arrow control-jog-down" data-control-action="24" data-control-hold="1" data-control-label="X indietro" aria-label="Jog X indietro" title="X indietro">
                  <span class="control-jog-symbol">↓</span>
                  <span class="control-jog-axis">X</span>
                </button>
                <button type="button" class="control-button hold control-jog-arrow control-jog-y-forward control-y" data-control-action="85" data-control-hold="1" data-control-label="Y avanti" aria-label="Jog Y avanti" title="Y avanti" hidden>
                  <span class="control-jog-symbol">↑</span>
                  <span class="control-jog-axis">Y</span>
                </button>
                <button type="button" class="control-button hold control-jog-arrow control-jog-y-back control-y" data-control-action="74" data-control-hold="1" data-control-label="Y indietro" aria-label="Jog Y indietro" title="Y indietro" hidden>
                  <span class="control-jog-symbol">↓</span>
                  <span class="control-jog-axis">Y</span>
                </button>
              </div>
            </section>

            <section class="panel control-panel" data-control-panel="run">
              <h3>Operazione</h3>
              <div class="control-button-grid">
                <button type="button" class="control-button" data-control-action="30">ON</button>
                <button type="button" class="control-button danger" data-control-action="27">OFF</button>
                <button type="button" class="control-button neutral" data-control-action="64">Incr.</button>
                <button type="button" class="control-button" data-control-action="95">Più</button>
                <button type="button" class="control-button" data-control-action="60">Meno</button>
                <button type="button" class="control-button neutral" data-control-action="82">Inverti</button>
                <button type="button" class="control-button neutral" data-control-action="77">Unità</button>
                <button type="button" class="control-button neutral" data-control-action="12">Info</button>
                <button type="button" class="control-button neutral" data-control-action="84">Avvii</button>
              </div>
            </section>

            <section class="panel control-panel" data-control-panel="numpad">
              <h3>Tastierino</h3>
              <div class="control-numpad">
                <button type="button" class="control-button neutral" data-control-action="49">1</button>
                <button type="button" class="control-button neutral" data-control-action="50">2</button>
                <button type="button" class="control-button neutral" data-control-action="51">3</button>
                <button type="button" class="control-button neutral" data-control-action="52">4</button>
                <button type="button" class="control-button neutral" data-control-action="53">5</button>
                <button type="button" class="control-button neutral" data-control-action="54">6</button>
                <button type="button" class="control-button neutral" data-control-action="55">7</button>
                <button type="button" class="control-button neutral" data-control-action="56">8</button>
                <button type="button" class="control-button neutral" data-control-action="57">9</button>
                <button type="button" class="control-button neutral" data-control-action="48">0</button>
                <button type="button" class="control-button neutral control-wide" data-control-action="28">Cancella</button>
              </div>
            </section>

            <section class="panel control-panel" data-control-panel="stops">
              <h3>Finecorsa e assi</h3>
              <div class="control-button-grid">
                <button type="button" class="control-button warning" data-control-action="65">Fermo Z sx</button>
                <button type="button" class="control-button warning" data-control-action="68">Fermo Z dx</button>
                <button type="button" class="control-button neutral" data-control-action="90">Azzera Z</button>
                <button type="button" class="control-button warning" data-control-action="87">Fermo X avanti</button>
                <button type="button" class="control-button warning" data-control-action="83">Fermo X dietro</button>
                <button type="button" class="control-button neutral" data-control-action="88">Azzera X</button>
                <button type="button" class="control-button warning control-y" data-control-action="73" hidden>Fermo Y avanti</button>
                <button type="button" class="control-button warning control-y" data-control-action="75" hidden>Fermo Y dietro</button>
                <button type="button" class="control-button neutral control-y" data-control-action="72" hidden>Azzera Y</button>
                <button type="button" class="control-button neutral" data-control-action="81">Abilita Z</button>
                <button type="button" class="control-button neutral" data-control-action="67">Abilita X</button>
                <button type="button" class="control-button neutral control-y" data-control-action="89" hidden>Abilita Y</button>
                <button type="button" class="control-button neutral" data-control-action="79">Diametro</button>
              </div>
            </section>

            <section class="panel control-panel" data-control-panel="modes">
              <h3>Modalità</h3>
              <div class="control-button-grid">
                <button type="button" class="control-button mode" data-control-action="97">INGR.</button>
                <button type="button" class="control-button mode" data-control-action="109">X-ING</button>
                <button type="button" class="control-button mode" data-control-action="108">JOY</button>
                <button type="button" class="control-button mode" data-control-action="98">TORN.</button>
                <button type="button" class="control-button mode" data-control-action="99">SPIAN.</button>
                <button type="button" class="control-button mode" data-control-action="100">CONO</button>
                <button type="button" class="control-button mode" data-control-action="101">TRONC.</button>
                <button type="button" class="control-button mode" data-control-action="110">SCAN.</button>
                <button type="button" class="control-button mode mode-long-label" data-control-action="102">FILETTATURA</button>
                <button type="button" class="control-button mode" data-control-action="104">ELLIS.</button>
                <button type="button" class="control-button mode" data-control-action="105">G-CODE</button>
                <button type="button" class="control-button mode" data-control-action="103">ASINC.</button>
                <button type="button" class="control-button mode control-y" data-control-action="106" hidden>ASSE Y</button>
              </div>
            </section>
          </div>
          <div class="control-bottom-bar">
            <button type="button" id="control-fullscreen" class="control-button control-fullscreen-button" aria-label="Schermo intero">Intero</button>
            <div class="control-bottom-state control-status-button" data-control-shortcut-action="27" data-control-shortcut-label="OFF" role="button" tabindex="0" aria-label="Spegni controller">
              <span class="control-status-label">Stato</span>
              <span id="control-bottom-state" class="control-status-value">--</span>
            </div>
            <div class="control-bottom-rpm">
              <span class="control-status-label">RPM</span>
              <span id="control-bottom-rpm" class="control-status-value">--</span>
            </div>
            <button type="button" class="control-button control-bottom-button" data-control-action="30">ON</button>
            <button type="button" class="control-button control-bottom-button danger" data-control-action="27">OFF</button>
          </div>
        </div>
      </section>

      <section id="section-gcode" class="app-section" data-section="gcode" data-page-title="GCode">
        <div class="section-stack">
          <section class="panel">
            <h3>GCode salvati</h3>
            <div id="gcode-list"></div>
            <p id="free-space"></p>
          </section>
          <section class="panel">
            <h3>Aggiungi GCode</h3>
            <p class="section-note">Genera file compatibili con <a href="https://kachurovskiy.com/lathecode/" target="_blank">lathecode</a>.</p>
            <div id="gcode-upload-controls">
              <label for="gcode-file" id="gcode-browse" class="button-like">Sfoglia file .gcode</label>
              <input type="file" id="gcode-file" accept=".gcode,.nc,.txt,text/plain">
            </div>
            <input type="text" id="gcode-name" placeholder="Nome GCode" required minlength="2">
            <textarea id="gcode-content" placeholder="Contenuto GCode" required minlength="2"></textarea>
            <div class="checkbox-container">
              <button id="add-gcode">Salva</button>
              <input type="checkbox" id="remove-comments" checked>
              <label for="remove-comments">Rimuovi commenti prima di salvare</label>
            </div>
          </section>
        </div>
      </section>

      <section id="section-updates" class="app-section" data-section="updates" data-page-title="Aggiornamenti">
        <div class="section-header">
          <p class="section-note">Tieni aperta questa pagina finché l'aggiornamento non termina.</p>
        </div>
        <div class="section-stack">
          <section class="panel">
            <h3>Aggiorna TFT Nextion</h3>
            <div id="tft-upload-controls">
              <label for="tft-file" id="tft-browse" class="button-like">Sfoglia</label>
              <input type="file" id="tft-file" accept=".tft">
              <input type="checkbox" id="tft-first-upload" checked>
              <label for="tft-first-upload">Primo caricamento / display di fabbrica (9600 baud)</label>
            </div>
            <progress id="tft-progress" value="0" max="100" hidden></progress>
            <p id="tft-status"></p>
          </section>
          <section class="panel">
            <h3>Aggiorna firmware ESP32</h3>
            <div id="firmware-upload-controls">
              <label for="firmware-file" id="firmware-browse" class="button-like">Sfoglia</label>
              <input type="file" id="firmware-file" accept=".bin,application/octet-stream">
            </div>
            <progress id="firmware-progress" value="0" max="100" hidden></progress>
            <p id="firmware-status"></p>
          </section>
        </div>
      </section>

      <section id="section-wifi" class="app-section" data-section="wifi" data-page-title="WiFi">
        <form id="wifi-form" class="config-section">
          <div class="config-grid">
            <label class="config-checkbox" for="wifi-enabled">
              <input type="checkbox" id="wifi-enabled">
              <span>WiFi attivo</span>
            </label>
            <label class="config-field" for="wifi-ssid">
              <span>Nome rete</span>
              <input type="text" id="wifi-ssid" maxlength="32" autocomplete="off">
            </label>
            <label class="config-field" for="wifi-password">
              <span>Password</span>
              <input type="password" id="wifi-password" maxlength="63" autocomplete="new-password" placeholder="Lascia invariata">
            </label>
            <label class="config-checkbox" for="wifi-clear-password">
              <input type="checkbox" id="wifi-clear-password">
              <span>Cancella password salvata</span>
            </label>
          </div>
          <div class="config-actions">
            <button id="save-wifi" type="submit">Salva e riavvia</button>
            <button id="reset-wifi" type="button" class="secondary">Dimentica rete</button>
            <span id="wifi-status" class="action-status" role="status" aria-live="polite"></span>
          </div>
        </form>
      </section>

      <section id="section-ui" class="app-section" data-section="ui" data-page-title="Interfaccia">
        <div class="section-stack">
          <details class="config-section settings-group accessibility-settings" open>
            <summary>Accessibilità (7)</summary>
            <div class="config-grid">
              <label class="config-checkbox" for="accessibility-voice-feedback">
                <input type="checkbox" id="accessibility-voice-feedback">
                <span>Voce</span>
              </label>
              <label class="config-checkbox" for="accessibility-announce-buttons">
                <input type="checkbox" id="accessibility-announce-buttons">
                <span>Annuncia pressione pulsanti</span>
              </label>
              <label class="config-checkbox" for="accessibility-announce-status">
                <input type="checkbox" id="accessibility-announce-status">
                <span>Annuncia cambi di stato</span>
              </label>
              <label class="config-checkbox" for="accessibility-announce-warnings">
                <input type="checkbox" id="accessibility-announce-warnings">
                <span>Annuncia avvisi ed errori</span>
              </label>
              <label class="config-checkbox" for="accessibility-announce-axis">
                <input type="checkbox" id="accessibility-announce-axis">
                <span>Annuncia variazione posizione assi</span>
              </label>
              <label class="config-checkbox" for="accessibility-quiet-hold">
                <input type="checkbox" id="accessibility-quiet-hold">
                <span>Silenzio durante jog</span>
              </label>
              <label class="config-field" for="accessibility-speech-rate">
                <span class="config-label">Velocità voce</span>
                <select id="accessibility-speech-rate">
                  <option value="1">1x</option>
                  <option value="1.5">1.5x</option>
                  <option value="2">2x</option>
                  <option value="3">3x</option>
                </select>
              </label>
            </div>
            <div class="config-actions">
              <button id="accessibility-test-voice" type="button" class="secondary">Prova voce</button>
              <span id="accessibility-status" class="action-status" role="status" aria-live="polite"></span>
            </div>
          </details>
        </div>
      </section>

      <section id="section-settings" class="app-section" data-section="settings" data-page-title="Impostazioni">
        <form id="config-form">
          <div id="config-fields"></div>
          <div class="config-actions sticky-actions">
            <button id="save-config" type="submit">Salva e riavvia</button>
            <button id="reset-config" type="button" class="secondary">Ripristina default</button>
            <span id="config-status" class="action-status" role="status" aria-live="polite"></span>
          </div>
        </form>
      </section>

      <section id="section-keyboard" class="app-section" data-section="keyboard" data-page-title="Tastiera">
        <form id="keyboard-form">
          <section class="config-section">
            <label class="config-checkbox" for="keyboard-show-keys">
              <input type="checkbox" id="keyboard-show-keys">
              <span>Mostra tasti premuti sullo schermo</span>
            </label>
            <small class="config-help">Ultimo codice tasto fisico: <span id="keyboard-last-key">nessuno</span></small>
          </section>
          <div id="keyboard-fields"></div>
          <div class="config-actions sticky-actions">
            <button id="save-keyboard" type="submit">Salva tastiera</button>
            <button id="reset-keyboard" type="button" class="secondary">Ripristina tastiera</button>
            <span id="keyboard-status" class="action-status" role="status" aria-live="polite"></span>
          </div>
        </form>
      </section>

      <section id="section-logs" class="app-section" data-section="logs" data-page-title="Registro">
        <div id="log"></div>
        <div id="command-container">
          <input type="text" id="command" placeholder="Inserisci comando" value="?" minlength="1" required>
          <button id="send">Invia</button>
        </div>
        <details class="panel">
          <summary>Comandi websocket supportati</summary>
          <ul>
            <li><code>?</code> richiede lo stato del controller</li>
            <li><code>@21:1</code> preme il codice azione diretto 21; <code>@21:0</code> lo rilascia senza rimappatura tastiera</li>
            <li><code>=20</code> invia il codice tasto 20 come se fosse premuto sulla tastiera</li>
            <li><code>!</code> spegne il controller</li>
            <li><code>~</code> accende il controller</li>
            <li><code>""</code> rimuove tutti i GCode</li>
          </ul>
        </details>
      </section>
    </main>

    <footer class="app-footer">
      <p>NanoEls )rawliteral" CONTROLLER_VERSION_TEXT R"rawliteral(. Solo rete locale fidata. Spegni il controller prima di aggiornamenti o modifiche alle impostazioni.</p>
    </footer>
  </div>

  <script>
    const defaultSection = 'home';
    const sectionLinks = Array.from(document.querySelectorAll('[data-section-link]'));
    const pageTitle = document.getElementById('page-title');
    const appSections = Array.from(document.querySelectorAll('[data-section]'));
    const controlButtons = Array.from(document.querySelectorAll('[data-control-action]'));
    const controlYElements = Array.from(document.querySelectorAll('.control-y'));
    const controlStatusPanel = document.getElementById('control-status');
    const controlExtraToggle = document.querySelector('[data-control-extra-toggle]');
    const controlMobileTabs = Array.from(document.querySelectorAll('[data-control-panel-tab]'));
    const controlPanelElements = Array.from(document.querySelectorAll('[data-control-panel]'));
    const controlShortcutElements = Array.from(document.querySelectorAll('[data-control-shortcut-action], [data-control-shortcut-panel]'));
    const controlMobileMedia = window.matchMedia ? window.matchMedia('(max-width: 640px)') : { matches: false };
    const controlState = document.getElementById('control-state');
    const controlBottomState = document.getElementById('control-bottom-state');
    const controlMode = document.getElementById('control-mode');
    const controlModePitch = document.getElementById('control-mode-pitch');
    const controlPitch = document.getElementById('control-pitch');
    const controlMeasure = document.getElementById('control-measure');
    const controlStep = document.getElementById('control-step');
    const controlTurns = document.getElementById('control-turns');
    const controlAngle = document.getElementById('control-angle');
    const controlX = document.getElementById('control-x');
    const controlXInlineStops = document.getElementById('control-x-inline-stops');
    const controlXStops = controlXInlineStops;
    const controlY = document.getElementById('control-y');
    const controlYInlineStops = document.getElementById('control-y-inline-stops');
    const controlYStops = controlYInlineStops;
    const controlZ = document.getElementById('control-z');
    const controlZInlineStops = document.getElementById('control-z-inline-stops');
    const controlZStops = controlZInlineStops;
    const controlRpm = document.getElementById('control-rpm');
    const controlBottomRpm = document.getElementById('control-bottom-rpm');
    const controlFullscreenButton = document.getElementById('control-fullscreen');
    const controlMessage = document.getElementById('control-message');
    const controlActionStatusElements = Array.from(document.querySelectorAll('[data-control-action-status]'));
    const controlActionStatus = {
      set textContent(value) {
        controlActionStatusElements.forEach(element => { element.textContent = value || ''; });
      },
      get textContent() {
        return controlActionStatusElements.length > 0 ? controlActionStatusElements[0].textContent : '';
      }
    };
    const log = document.getElementById('log');
    const commandInput = document.getElementById('command');
    const sendButton = document.getElementById('send');
    const gcodeList = document.getElementById('gcode-list');
    const gcodeNameInput = document.getElementById('gcode-name');
    const gcodeContentInput = document.getElementById('gcode-content');
    const addGcodeButton = document.getElementById('add-gcode');
    const gcodeBrowseButton = document.getElementById('gcode-browse');
    const gcodeFileInput = document.getElementById('gcode-file');
    const removeCommentsCheckbox = document.getElementById('remove-comments');
    const configForm = document.getElementById('config-form');
    const configFields = document.getElementById('config-fields');
    const configStatus = document.getElementById('config-status');
    const saveConfigButton = document.getElementById('save-config');
    const resetConfigButton = document.getElementById('reset-config');
    const accessibilityVoiceFeedbackInput = document.getElementById('accessibility-voice-feedback');
    const accessibilityAnnounceButtonsInput = document.getElementById('accessibility-announce-buttons');
    const accessibilityAnnounceStatusInput = document.getElementById('accessibility-announce-status');
    const accessibilityAnnounceWarningsInput = document.getElementById('accessibility-announce-warnings');
    const accessibilityAnnounceAxisInput = document.getElementById('accessibility-announce-axis');
    const accessibilityQuietHoldInput = document.getElementById('accessibility-quiet-hold');
    const accessibilitySpeechRateInput = document.getElementById('accessibility-speech-rate');
    const accessibilityTestVoiceButton = document.getElementById('accessibility-test-voice');
    const accessibilityStatus = document.getElementById('accessibility-status');
    const tftFirstUploadCheckbox = document.getElementById('tft-first-upload');
    const tftBrowseButton = document.getElementById('tft-browse');
    const tftFileInput = document.getElementById('tft-file');
    const tftProgress = document.getElementById('tft-progress');
    const tftStatus = document.getElementById('tft-status');
    const firmwareBrowseButton = document.getElementById('firmware-browse');
    const firmwareFileInput = document.getElementById('firmware-file');
    const firmwareProgress = document.getElementById('firmware-progress');
    const firmwareStatus = document.getElementById('firmware-status');
    const wifiForm = document.getElementById('wifi-form');
    const wifiEnabledInput = document.getElementById('wifi-enabled');
    const wifiSsidInput = document.getElementById('wifi-ssid');
    const wifiPasswordInput = document.getElementById('wifi-password');
    const wifiClearPasswordInput = document.getElementById('wifi-clear-password');
    const saveWifiButton = document.getElementById('save-wifi');
    const resetWifiButton = document.getElementById('reset-wifi');
    const wifiStatusElement = document.getElementById('wifi-status');
    const keyboardForm = document.getElementById('keyboard-form');
    const keyboardFields = document.getElementById('keyboard-fields');
    const keyboardShowKeysInput = document.getElementById('keyboard-show-keys');
    const keyboardLastKey = document.getElementById('keyboard-last-key');
    const keyboardStatus = document.getElementById('keyboard-status');
    const saveKeyboardButton = document.getElementById('save-keyboard');
    const resetKeyboardButton = document.getElementById('reset-keyboard');
    let tftUploadInProgress = false;
    let firmwareUploadInProgress = false;
    let firmwareReloadTimer = 0;
    let firmwareStatusPollTimer = 0;
    let firmwareStatusPollBusy = false;
    let keyboardLearnTarget = '';
    let keyboardLearnTimer = 0;
    let controlHoldHeartbeatTimer = 0;
    let controlWakeLock = null;
    let controlWakeLockBusy = false;
    let controlNoSleepVideo = null;
    let controlNoSleepDrawTimer = 0;
    let accessibilityAxisTimer = 0;
    let accessibilityMessageTimer = 0;
    let accessibilityHoldAnnouncementTimer = 0;
    let accessibilityLastSpeechPhrase = '';
    let accessibilityLastSpeechMillis = 0;
    let accessibilityLastSpeechKind = '';
    let accessibilityLastStatusText = '';
    let accessibilityLastMessageText = '';
    let webUiNumpadEntryActive = false;
    let webUiNumpadDigits = '';
    const accessibilityPendingAxisValues = {};
    const accessibilityLastAxisValues = { x: '', y: '', z: '' };
    const activeControlActions = new Set();
    const tftFirstUploadStorageKey = 'nanoels-h5.tft-first-upload';
    const accessibilityStorageKey = 'nanoels-h5.accessibility';
    const accessibilityDefaults = {
      voiceFeedback: false,
      announceButtons: true,
      announceStatus: true,
      announceWarnings: true,
      announceAxis: false,
      quietHold: true,
      speechRate: '1'
    };
    let accessibilitySettings = Object.assign({}, accessibilityDefaults);
    const machineConfigSections = [
      {
        title: 'Encoder mandrino',
        fields: [
          { key: 'encoderPpr', label: 'PPR encoder', unit: 'impulsi/giro', min: 1, max: 15000, step: 1, help: "Impulsi per giro del mandrino secondo la specifica dell'encoder, prima del conteggio in quadratura. Valori comuni: 600 o 1200." },
          { key: 'encoderBacklash', label: 'Gioco encoder', unit: 'impulsi', min: 0, max: 30000, step: 1, help: "Impulsi encoder ignorati dopo l'inversione del mandrino. Aumentare solo se l'angolo mostrato oscilla dopo l'inversione." }
        ]
      },
      {
        title: 'Asse Z',
        fields: [
          { key: 'zScrewDu', label: 'Passo vite madre', unit: 'mm/giro', min: 0.0001, max: 1000, step: 0.0001, firmwareScale: 10000, help: "Distanza percorsa da Z per un giro della vite. Vite metrica: usare il passo indicato. Vite in pollici: 25,4 / TPI, quindi 8 TPI = 3,175." },
          { key: 'zMotorSteps', label: 'Passi motore per giro', unit: 'passi/giro', min: 1, max: 1000000, step: 1, help: "Passi interi motore * microstep driver * rapporto motore/vite. Esempio: motore da 200 passi con microstep 4x = 800." },
          { key: 'zPulsePerRevolution', label: 'PPR volantino', unit: 'impulsi/giro', min: 1, max: 100000, step: 0.01, help: "Impulsi fisici per giro dell'encoder opzionale del volantino Z. Usare la specifica del volantino." },
          { key: 'zSpeedStart', label: 'Velocità iniziale', unit: 'passi/s', min: 1, max: 1000000, step: 1, help: "Frequenza iniziale dei passi all'avvio del movimento. Usare un valore da cui il motore parte in modo affidabile senza perdere passi." },
          { key: 'zAcceleration', label: 'Accelerazione', unit: 'passi/s^2', min: 1, max: 100000000, step: 1, help: "Ramp di accelerazione e decelerazione. Più alto è più reattivo ma può perdere passi se il motore o il carico non seguono." },
          { key: 'zSpeedManualMove', label: 'Velocità manuale', unit: 'passi/s', min: 1, max: 1000000, step: 1, help: "Velocità massima per jog, ritorni rapidi e movimenti GCode su Z. La velocità dipende anche dai passi per mm." },
          { key: 'zMaxTravelMm', label: 'Corsa massima', unit: 'mm', min: 1, max: 10000, step: 1, help: "Massimo movimento Z singolo consentito. Impostare poco sopra la corsa fisica sicura del carro." },
          { key: 'zBacklashDu', label: 'Gioco', unit: 'mm', min: 0, max: 1000, step: 0.0001, firmwareScale: 10000, help: "Movimento Z perso all'inversione. Misurare con comparatore: muovere in un verso, azzerare, invertire finché l'indice non si muove." },
          { key: 'zInvert', label: 'Inverti direzione', type: 'checkbox', help: "Attivare se l'asse Z si muove nel verso opposto a schermo o tastiera." },
          { key: 'zInvertEnable', label: 'Inverti abilitazione', type: 'checkbox', help: "Attivare solo se l'ingresso enable del driver lavora al contrario." },
          { key: 'zNeedsRest', label: 'Riposo motore', type: 'checkbox', help: "Attivare se il driver deve essere alimentato solo durante il movimento. Lasciare disattivo se Z deve mantenere la posizione da fermo." }
        ]
      },
      {
        title: 'Asse X',
        fields: [
          { key: 'xScrewDu', label: 'Passo vite madre', unit: 'mm/giro', min: 0.0001, max: 1000, step: 0.0001, firmwareScale: 10000, help: "Distanza percorsa da X per un giro della vite. Vite metrica: usare il passo indicato. Vite in pollici: 25,4 / TPI, quindi 10 TPI = 2,54." },
          { key: 'xMotorSteps', label: 'Passi motore per giro', unit: 'passi/giro', min: 1, max: 1000000, step: 1, help: "Passi interi motore * microstep driver * rapporto motore/vite. Esempio: motore da 200 passi con microstep 4x = 800." },
          { key: 'xPulsePerRevolution', label: 'PPR volantino', unit: 'impulsi/giro', min: 1, max: 100000, step: 0.01, help: "Impulsi fisici per giro dell'encoder opzionale del volantino X. Usare la specifica del volantino." },
          { key: 'xSpeedStart', label: 'Velocità iniziale', unit: 'passi/s', min: 1, max: 1000000, step: 1, help: "Frequenza iniziale dei passi all'avvio del movimento. Usare un valore da cui il motore parte in modo affidabile senza perdere passi." },
          { key: 'xAcceleration', label: 'Accelerazione', unit: 'passi/s^2', min: 1, max: 100000000, step: 1, help: "Ramp di accelerazione e decelerazione. Più alto è più reattivo ma può perdere passi se il motore o la slitta non seguono." },
          { key: 'xSpeedManualMove', label: 'Velocità manuale', unit: 'passi/s', min: 1, max: 1000000, step: 1, help: "Velocità massima per jog, ritorni rapidi e movimenti GCode su X. La velocità dipende anche dai passi per mm." },
          { key: 'xMaxTravelMm', label: 'Corsa massima', unit: 'mm', min: 1, max: 10000, step: 1, help: "Massimo movimento X singolo consentito. Impostare poco sopra la corsa fisica sicura della slitta trasversale." },
          { key: 'xBacklashDu', label: 'Gioco', unit: 'mm', min: 0, max: 1000, step: 0.0001, firmwareScale: 10000, help: "Movimento X perso all'inversione. Misurare con comparatore: muovere in un verso, azzerare, invertire finché l'indice non si muove." },
          { key: 'xInvert', label: 'Inverti direzione', type: 'checkbox', help: "Attivare se l'asse X si muove nel verso opposto a schermo o tastiera." },
          { key: 'xInvertEnable', label: 'Inverti abilitazione', type: 'checkbox', help: "Attivare solo se l'ingresso enable del driver lavora al contrario." },
          { key: 'xNeedsRest', label: 'Riposo motore', type: 'checkbox', help: "Attivare se il driver deve essere alimentato solo durante il movimento. Lasciare disattivo se X deve mantenere la posizione da fermo." }
        ]
      },
      {
        title: 'Movimento manuale',
        fields: [
          { key: 'stepTimeMs', label: 'Tempo passo', unit: 'ms', min: 1, max: 10000, step: 1, help: "Tempo obiettivo per un passo di precisione quando l'incremento selezionato non è continuo." },
          { key: 'delayBetweenStepsMs', label: 'Ritardo passo', unit: 'ms', min: 0, max: 10000, step: 1, help: "Pausa tra passi di precisione ripetuti mentre si tiene premuto un pulsante di movimento." },
          { key: 'enableContinuousMove', label: 'Abilita movimenti continui', type: 'checkbox', help: "Fa scorrere i pulsanti di movimento in continuo quando l'incremento è 1 mm o 0,1 in." },
          { key: 'axisEncoderBacklash', label: 'Gioco volantino', unit: 'impulsi', min: 0, max: 30000, step: 1, help: "Impulsi del volantino ignorati dopo l'inversione sugli ingressi Z/X/Y. Impostare 0 per encoder diretti senza gioco meccanico." }
        ]
      },
      {
        title: 'Modalità automatiche',
        fields: [
          { key: 'safeDistanceDu', label: 'Distanza di arretramento', unit: 'mm', min: 0, max: 1000, step: 0.0001, firmwareScale: 10000, help: "Distanza di cui l'asse ausiliario si allontana dal materiale tra le passate automatiche. Impostare 0 per disattivare l'arretramento extra." },
          { key: 'slotLeftReductionDu', label: 'Riduzione sinistra scanalatura', unit: 'mm/passata', min: 0, max: 1000, step: 0.0001, firmwareScale: 10000, help: "Accorcia progressivamente il taglio sinistro di ogni scanalatura di questa distanza Z per scanalature cieche. Impostare 0 per passate a tutta lunghezza." }
        ]
      },
      {
        title: 'Cono',
        fields: [
          { key: 'coneDiaBigDu', label: 'Diametro grande', unit: 'mm', min: 0.1, max: 999.99, step: 0.01, firmwareScale: 10000, help: "Diametro maggiore del pezzo. Con il diametro piccolo e la corsa Z definisce il rapporto del cono." },
          { key: 'coneDiaSmallDu', label: 'Diametro piccolo', unit: 'mm', min: 0, max: 999.99, step: 0.01, firmwareScale: 10000, help: "Diametro minore del pezzo. Il rapporto mostrato sul display è corsa Z / (diametro grande − diametro piccolo), lo stesso valore delle tabelle dei coni." }
        ]
      },
      {
        title: 'Asse Y',
        fields: [
          { key: 'activeY', label: 'Asse Y collegato', type: 'checkbox', help: "Attivare solo se l'asse Y opzionale o il divisore è cablato e configurato." },
          { key: 'rotaryY', label: 'Asse rotativo', type: 'checkbox', help: "Attivo: valori Y in gradi. Disattivo: valori Y come distanza lineare." },
          { key: 'yMotorSteps', label: 'Passi motore per giro', unit: 'passi/giro', min: 1, max: 1000000, step: 1, help: "Passi interi motore * microstep driver * rapporto motore/asse." },
          { key: 'yPulsePerRevolution', label: 'PPR volantino', unit: 'impulsi/giro', min: 1, max: 100000, step: 0.01, help: "Impulsi fisici per giro dell'encoder opzionale del volantino Y. Usare la specifica del volantino." },
          { key: 'yScrewDu', label: 'Corsa per giro vite', unit: 'mm o gradi/giro', min: 0.0001, max: 1000, step: 0.0001, firmwareScale: 10000, help: "Per Y rotativo, gradi per giro della vite senza fine. Per Y lineare, mm per giro della vite madre." },
          { key: 'ySpeedStart', label: 'Velocità iniziale', unit: 'passi/s', min: 1, max: 1000000, step: 1, help: "Frequenza iniziale dei passi all'avvio del movimento Y. Usare un valore da cui il motore parte in modo affidabile." },
          { key: 'yAcceleration', label: 'Accelerazione', unit: 'passi/s^2', min: 1, max: 100000000, step: 1, help: "Ramp di accelerazione e decelerazione del movimento Y." },
          { key: 'ySpeedManualMove', label: 'Velocità manuale', unit: 'passi/s', min: 1, max: 1000000, step: 1, help: "Velocità massima per movimenti Y manuali e GCode." },
          { key: 'yMaxTravelMm', label: 'Corsa massima', unit: 'mm o gradi', min: 1, max: 10000, step: 1, help: "Massimo movimento Y singolo consentito. Per Y rotativo è in gradi." },
          { key: 'yBacklashDu', label: 'Gioco', unit: 'mm o gradi', min: 0, max: 1000, step: 0.0001, firmwareScale: 10000, help: "Movimento Y perso all'inversione. Per Y rotativo inserire gradi; per Y lineare inserire mm." },
          { key: 'yInvert', label: 'Inverti direzione', type: 'checkbox', help: "Attivare se Y si muove nel verso opposto a quello atteso." },
          { key: 'yInvertEnable', label: 'Inverti abilitazione', type: 'checkbox', help: "Attivare solo se l'ingresso enable del driver Y lavora al contrario." },
          { key: 'yNeedsRest', label: 'Riposo motore', type: 'checkbox', help: "Attivare se il driver Y deve essere alimentato solo durante il movimento. Lasciare disattivo se deve mantenere la posizione da fermo." }
        ]
      },
      {
        title: 'Joystick',
        fields: [
          { key: 'joystickEnabled', label: 'Joystick attivo', type: 'checkbox', help: "Attivare solo dopo aver cablato il joystick analogico opzionale. Gli assi devono fornire ingressi ADC da 3,3 V compatibili con ESP32." },
          { key: 'joystickZEnabled', label: 'Ingresso Z attivo', type: 'checkbox', help: "Attivare se il joystick ha il potenziometro Z cablato su JZ. Disattivare per joystick senza questo asse." },
          { key: 'joystickXEnabled', label: 'Ingresso X attivo', type: 'checkbox', help: "Attivare se il joystick ha il potenziometro X cablato su JX. Disattivare per joystick senza questo asse." },
          { key: 'joystickYEnabled', label: 'Ingresso Y attivo', type: 'checkbox', help: "Attivare se il joystick ha il potenziometro Y cablato su JY. Disattivare per joystick senza questo asse." },
          { key: 'joystickButtonTogglesOnOff', label: 'Pulsante attiva/disattiva', type: 'checkbox', help: "In modalità JOY, un clic breve con Z e X in centro attiva/disattiva l'avanzamento. Tenendo premuto con Z o X deflesso si esegue il movimento rapido." },
          { key: 'joystickCenterSamples', label: 'Campioni centro', unit: 'campioni', min: 1, max: 1024, step: 1, help: "Numero di letture ADC mediate all'avvio per apprendere il centro del joystick." },
          { key: 'joystickOversamples', label: 'Sovracampionamento', unit: 'campioni', min: 1, max: 1024, step: 1, help: "Letture ADC mediate per ogni aggiornamento del joystick. Valori alti riducono il rumore ma aggiungono ritardo." },
          { key: 'joystickSampleIntervalMs', label: 'Intervallo campioni', unit: 'ms', min: 1, max: 1000, step: 1, help: "Tempo tra gli aggiornamenti del joystick. Valori piccoli reagiscono più in fretta e usano più CPU." },
          { key: 'joystickAdcMax', label: 'ADC massimo', unit: 'valori', min: 1, max: 65535, step: 1, help: "Massimo valore ADC grezzo. L'ADC a 12 bit dell'ESP32 normalmente usa 4095." },
          { key: 'joystickDeadband', label: 'Zona morta', unit: 'valori', min: 0, max: 65534, step: 1, help: "Valori ADC attorno al centro trattati come zero. Aumentare se un asse va alla deriva al rilascio." },
          { key: 'joystickPulseQueueLimit', label: 'Limite coda impulsi', unit: 'impulsi', min: 1, max: 1000000, step: 1, help: "Massimo numero di impulsi virtuali del volantino in coda. Valori alti consentono più movimento bufferizzato." },
          { key: 'joystickNormalRevolutionsPerSecond', label: 'Velocità normale', unit: 'giri/s', min: 0.01, max: 1000, step: 0.01, help: "Velocità jog del joystick in giri vite equivalenti al secondo quando il rapido non è premuto." },
          { key: 'joystickRapidRevolutionsPerSecond', label: 'Velocità rapida', unit: 'giri/s', min: 0.01, max: 1000, step: 0.01, help: "Velocità jog del joystick in giri vite equivalenti al secondo mentre il pulsante è premuto." },
          { key: 'invertJoystickZ', label: 'Inverti Z', type: 'checkbox', help: "Attivare se la deflessione Z del joystick muove il carro nel verso sbagliato." },
          { key: 'invertJoystickX', label: 'Inverti X', type: 'checkbox', help: "Attivare se la deflessione X del joystick muove la slitta trasversale nel verso sbagliato." },
          { key: 'invertJoystickY', label: 'Inverti Y', type: 'checkbox', help: "Attivare se la deflessione Y del joystick cambia il valore nel verso sbagliato." },
          { key: 'invertJoystickButton', label: 'Inverti pulsante', type: 'checkbox', help: "Attivare se il pulsante del joystick risulta premuto quando è rilasciato." }
        ]
      }
    ];
    const machineConfigFields = machineConfigSections.flatMap(section => section.fields);
    const keyboardBindingSections = [
      {
        title: 'Movimento',
        fields: [
          { key: 'left', label: 'Sinistra' },
          { key: 'right', label: 'Destra' },
          { key: 'up', label: 'Su' },
          { key: 'down', label: 'Giù' },
          { key: 'forward', label: 'Y avanti' },
          { key: 'back', label: 'Y indietro' }
        ]
      },
      {
        title: 'Operazione',
        fields: [
          { key: 'on', label: 'On / avvia' },
          { key: 'off', label: 'Off / stop' },
          { key: 'plus', label: 'Più' },
          { key: 'minus', label: 'Meno' },
          { key: 'step', label: 'Incremento' },
          { key: 'reverse', label: 'Inverti passo' },
          { key: 'measure', label: 'Unità di misura' },
          { key: 'display', label: 'Info display' },
          { key: 'multistart', label: 'Avvii multipli' }
        ]
      },
      {
        title: 'Fermi e assi',
        fields: [
          { key: 'stopL', label: 'Imposta fermo Z sx' },
          { key: 'stopR', label: 'Imposta fermo Z dx' },
          { key: 'stopU', label: 'Imposta fermo X avanti' },
          { key: 'stopD', label: 'Imposta fermo X dietro' },
          { key: 'stopF', label: 'Imposta fermo Y avanti' },
          { key: 'stopB', label: 'Imposta fermo Y dietro' },
          { key: 'zeroX', label: 'Azzera X' },
          { key: 'zeroZ', label: 'Azzera Z' },
          { key: 'zeroY', label: 'Azzera Y' },
          { key: 'diameter', label: 'Imposta diametro' },
          { key: 'enableX', label: 'Abilita X' },
          { key: 'enableZ', label: 'Abilita Z' },
          { key: 'enableY', label: 'Abilita Y' }
        ]
      },
      {
        title: 'Inserimento numeri',
        fields: [
          { key: 'digit0', label: 'Cifra 0' },
          { key: 'digit1', label: 'Cifra 1' },
          { key: 'digit2', label: 'Cifra 2' },
          { key: 'digit3', label: 'Cifra 3' },
          { key: 'digit4', label: 'Cifra 4' },
          { key: 'digit5', label: 'Cifra 5' },
          { key: 'digit6', label: 'Cifra 6' },
          { key: 'digit7', label: 'Cifra 7' },
          { key: 'digit8', label: 'Cifra 8' },
          { key: 'digit9', label: 'Cifra 9' },
          { key: 'backspace', label: 'Cancella' }
        ]
      },
      {
        title: 'Modalità',
        fields: [
          { key: 'mode', label: 'Menu modalità' },
          { key: 'modeGears', label: 'Modalità ingranaggi' },
          { key: 'modeXGear', label: 'Modalità X-ingranaggi' },
          { key: 'modeJoystick', label: 'Modalità joystick' },
          { key: 'modeTurn', label: 'Modalità tornitura' },
          { key: 'modeFace', label: 'Modalità spianatura' },
          { key: 'modeCone', label: 'Modalità cono' },
          { key: 'modeCut', label: 'Modalità troncatura' },
          { key: 'modeSlot', label: 'Modalità scanalatura' },
          { key: 'modeThread', label: 'Modalità filettatura' },
          { key: 'modeEllipse', label: 'Modalità ellisse' },
          { key: 'modeGcode', label: 'Modalità GCode' },
          { key: 'modeAsync', label: 'Modalità asincrona' },
          { key: 'modeY', label: 'Modalità asse Y' }
        ]
      }
    ];
    const keyboardBindingFields = keyboardBindingSections.flatMap(section => section.fields);

    const normalizeSection = (section) => {
      return appSections.some(element => element.dataset.section === section) ? section : defaultSection;
    };

    const sectionFromHash = () => {
      const hash = window.location.hash || '';
      return normalizeSection(hash.length > 1 ? hash.substring(1).toLowerCase() : '');
    };

    const showSection = (section) => {
      const activeSection = normalizeSection(section);
      appSections.forEach(element => {
        element.classList.toggle('active', element.dataset.section === activeSection);
      });
      sectionLinks.forEach(link => {
        link.classList.toggle('active', link.dataset.sectionLink === activeSection);
      });
      const activeElement = appSections.find(element => element.dataset.section === activeSection);
      if (pageTitle) pageTitle.textContent = (activeElement && activeElement.dataset.pageTitle) || activeSection;
      document.body.classList.toggle('control-section-active', activeSection === 'control');
      document.body.classList.toggle('page-open', activeSection !== 'home');
    };

    const handleSectionChange = (scrollToTop) => {
      showSection(sectionFromHash());
      if (scrollToTop) window.scrollTo(0, 0);
    };

    function speechSupported() {
      return 'speechSynthesis' in window && 'SpeechSynthesisUtterance' in window;
    }

    function normalizeSpeechPhrase(value) {
      return String(value || '')
        .replace(/\b([XYZ])-(?=\d)/gi, '$1 meno ')
        .replace(/\s+/g, ' ')
        .trim();
    }

    function speechRate() {
      const rate = Number(accessibilitySettings.speechRate);
      return Number.isFinite(rate) ? Math.min(3, Math.max(0.5, rate)) : 1;
    }

    function cancelAxisAnnouncement() {
      clearTimeout(accessibilityAxisTimer);
      accessibilityAxisTimer = 0;
      Object.keys(accessibilityPendingAxisValues).forEach(key => { delete accessibilityPendingAxisValues[key]; });
      if (accessibilityLastSpeechKind === 'axis' && speechSupported()) {
        window.speechSynthesis.cancel();
        accessibilityLastSpeechKind = '';
      }
    }

    function cancelMessageAnnouncement() {
      clearTimeout(accessibilityMessageTimer);
      accessibilityMessageTimer = 0;
      if (accessibilityLastSpeechKind === 'message' && speechSupported()) {
        window.speechSynthesis.cancel();
        accessibilityLastSpeechKind = '';
      }
    }

    function speakAccessibility(phrase, options = {}) {
      const text = normalizeSpeechPhrase(phrase);
      if (!text || !speechSupported()) return false;
      if (!options.force && !accessibilitySettings.voiceFeedback) return false;
      if (!options.force) {
        const now = Date.now();
        const cooldown = options.cooldownMs === undefined ? 1500 : options.cooldownMs;
        if (text === accessibilityLastSpeechPhrase && now - accessibilityLastSpeechMillis < cooldown) return false;
      }
      if (options.kind !== 'axis' && (options.cancelPrevious || options.kind === 'button' || options.kind === 'panel' || options.kind === 'warning')) {
        cancelAxisAnnouncement();
      }
      if (options.kind !== 'message' && (options.cancelPrevious || options.kind === 'button' || options.kind === 'panel' || options.kind === 'warning' || options.kind === 'status')) {
        cancelMessageAnnouncement();
      }
      if (options.cancelPrevious) window.speechSynthesis.cancel();
      const utterance = new SpeechSynthesisUtterance(text);
      utterance.rate = speechRate();
      utterance.onend = () => {
        if (accessibilityLastSpeechKind === options.kind) accessibilityLastSpeechKind = '';
      };
      utterance.onerror = utterance.onend;
      window.speechSynthesis.speak(utterance);
      accessibilityLastSpeechPhrase = text;
      accessibilityLastSpeechMillis = Date.now();
      accessibilityLastSpeechKind = options.kind || '';
      return true;
    }

    function announceButtonAction(label, state = '') {
      if (!accessibilitySettings.announceButtons) return;
      const phrase = normalizeSpeechPhrase(`${label}${state ? ' ' + state : ''}`);
      speakAccessibility(phrase, { kind: 'button' });
    }

    function axisStatusValue(axisName) {
      const elements = { x: controlX, y: controlY, z: controlZ };
      const element = elements[axisName.toLowerCase()];
      return normalizeSpeechPhrase(element ? element.textContent : '');
    }

    function axisLooksEnabled(axisName) {
      const value = axisStatusValue(axisName);
      return !!value && value !== '--';
    }

    function stopDatasetForAxis(axisName) {
      const elements = { x: controlXStops, y: controlYStops, z: controlZStops };
      return elements[axisName.toLowerCase()] || null;
    }

    function enteredNumpadValueText() {
      const message = normalizeSpeechPhrase(controlMessage ? controlMessage.textContent : '');
      const match = message.match(/^Usa\s+(.+)\?$/i);
      if (match) return match[1];
      return '';
    }

    function stopActionAnnouncement(actionCode) {
      const stopActions = {
        '65': { axis: 'Z', side: 'left', label: 'sinistro' },
        '68': { axis: 'Z', side: 'right', label: 'destro' },
        '87': { axis: 'X', side: 'left', label: 'avanti' },
        '83': { axis: 'X', side: 'right', label: 'dietro' },
        '73': { axis: 'Y', side: 'left', label: 'avanti' },
        '75': { axis: 'Y', side: 'right', label: 'dietro' }
      };
      const action = stopActions[String(actionCode)];
      if (!action) return '';
      if (webUiNumpadEntryActive) {
        const valueText = enteredNumpadValueText();
        return `Fermo ${action.axis} ${action.label} impostato${valueText ? ' a ' + valueText : ' al valore inserito'}`;
      }
      const stops = stopDatasetForAxis(action.axis);
      const current = stops ? (stops.dataset[action.side] || '') : '';
      return `Fermo ${action.axis} ${action.label} ${current ? 'rimosso' : 'aggiunto'}`;
    }

    function enableActionAnnouncement(actionCode) {
      const enableActions = { '81': 'Z', '67': 'X', '89': 'Y' };
      const axis = enableActions[String(actionCode)];
      if (!axis) return '';
      return `Asse ${axis} ${axisLooksEnabled(axis) ? 'disabilitato' : 'abilitato'}`;
    }

    function actionAnnouncementForSpeech(actionCode, label) {
      return stopActionAnnouncement(actionCode) || enableActionAnnouncement(actionCode) || actionLabelForSpeech(actionCode, label);
    }

    function updateWebUiNumpadTracking(actionCode) {
      const code = String(actionCode);
      const codeNumber = Number(code);
      if (codeNumber >= 48 && codeNumber <= 57) {
        if (!webUiNumpadEntryActive) webUiNumpadDigits = '';
        webUiNumpadEntryActive = true;
        if (webUiNumpadDigits.length < 8) webUiNumpadDigits += String.fromCharCode(codeNumber);
        return;
      }
      if (code === '28') {
        webUiNumpadEntryActive = true;
        webUiNumpadDigits = webUiNumpadDigits.substring(0, Math.max(0, webUiNumpadDigits.length - 1));
        return;
      }
      if (webUiNumpadEntryActive && (code === '95' || code === '60')) return;
      webUiNumpadEntryActive = false;
      webUiNumpadDigits = '';
    }

    function announcePanelChange(panelName) {
      if (!accessibilitySettings.announceButtons) return;
      const labels = { jog: 'Jog', run: 'Esegui', numpad: 'Tastierino', stops: 'Fermi', modes: 'Modalità' };
      speakAccessibility(labels[panelName] || panelName, { kind: 'panel' });
    }

    function announceWarning(text) {
      if (!accessibilitySettings.announceWarnings) return;
      speakAccessibility(text, { kind: 'warning', cancelPrevious: true });
    }

    function statusPhrase(value) {
      const status = normalizeSpeechPhrase(value).toUpperCase();
      if (status === 'ON') return 'Controller acceso';
      if (status === 'OFF') return 'Controller spento';
      if (status === 'SIN') return 'Controller sincronizzato';
      if (status === 'CONNECTED') return 'Connesso';
      if (status === 'DISCONNECTED') return 'Disconnesso';
      return normalizeSpeechPhrase(value);
    }

    function announceStatusChange(value) {
      const phrase = statusPhrase(value);
      if (!phrase || phrase === accessibilityLastStatusText) return;
      accessibilityLastStatusText = phrase;
      if (!accessibilitySettings.announceStatus) return;
      speakAccessibility(phrase, { kind: 'status' });
    }

    function announceControlMessage(value) {
      const phrase = normalizeSpeechPhrase(value);
      if (!phrase || phrase === '--' || phrase === accessibilityLastMessageText) return;
      accessibilityLastMessageText = phrase;
      if (!accessibilitySettings.announceStatus) return;
      cancelMessageAnnouncement();
      accessibilityMessageTimer = setTimeout(() => {
        accessibilityMessageTimer = 0;
        speakAccessibility(phrase, { kind: 'message', cancelPrevious: true, cooldownMs: 500 });
      }, 650);
    }

    function announceAxisPosition(axisName, value) {
      if (!accessibilitySettings.announceAxis) return;
      const axisKey = axisName.toLowerCase();
      const cleanValue = normalizeSpeechPhrase(value);
      if (!cleanValue || cleanValue === '--' || accessibilityLastAxisValues[axisKey] === cleanValue) return;
      accessibilityLastAxisValues[axisKey] = cleanValue;
      clearTimeout(accessibilityAxisTimer);
      accessibilityAxisTimer = 0;
      if (accessibilityLastSpeechKind === 'axis' && speechSupported()) {
        window.speechSynthesis.cancel();
        accessibilityLastSpeechKind = '';
      }
      accessibilityPendingAxisValues[axisName] = cleanValue;
      accessibilityAxisTimer = setTimeout(() => {
        const phrase = Object.keys(accessibilityPendingAxisValues).map(axis => `${axis} ${accessibilityPendingAxisValues[axis]}`).join(', ');
        Object.keys(accessibilityPendingAxisValues).forEach(key => { delete accessibilityPendingAxisValues[key]; });
        accessibilityAxisTimer = 0;
        speakAccessibility(phrase, { kind: 'axis', cancelPrevious: true, cooldownMs: 250 });
      }, 450);
    }

    function actionLabelForSpeech(actionCode, label) {
      const text = normalizeSpeechPhrase(label);
      const actionLabels = {
        '21': 'Jog Z sinistra',
        '22': 'Jog Z destra',
        '23': 'Jog X avanti',
        '24': 'Jog X indietro',
        '85': 'Jog Y avanti',
        '74': 'Jog Y indietro',
        '27': 'OFF',
        '30': 'ON',
        '64': 'Incremento',
        '82': 'Inverti passo',
        '77': 'Unità',
        '88': 'Azzera X',
        '90': 'Azzera Z',
        '72': 'Azzera Y',
        '97': 'Modalità ingranaggi',
        '98': 'Modalità tornitura',
        '99': 'Modalità spianatura',
        '100': 'Modalità cono',
        '101': 'Modalità troncatura',
        '102': 'Modalità filettatura',
        '103': 'Modalità asincrona',
        '104': 'Modalità ellisse',
        '105': 'Modalità G code',
        '106': 'Modalità asse Y',
        '108': 'Modalità joystick',
        '109': 'Modalità X ingranaggi',
        '110': 'Modalità scanalatura'
      };
      return actionLabels[String(actionCode)] || text;
    }

    function announceActiveHolds() {
      if (accessibilitySettings.quietHold || !accessibilitySettings.announceButtons || activeControlActions.size === 0) return;
      activeControlActions.forEach(actionCode => {
        const button = document.querySelector(`[data-control-action="${actionCode}"]`);
        const label = actionAnnouncementForSpeech(actionCode, controlButtonLabel(button));
        speakAccessibility(`${label} premuto`, { kind: 'button', cooldownMs: 2200 });
      });
    }

    function updateHoldAnnouncementTimer() {
      clearInterval(accessibilityHoldAnnouncementTimer);
      accessibilityHoldAnnouncementTimer = 0;
      if (!accessibilitySettings.quietHold && activeControlActions.size > 0) {
        accessibilityHoldAnnouncementTimer = setInterval(announceActiveHolds, 2500);
      }
    }

    function loadAccessibilitySettings() {
      try {
        const stored = localStorage.getItem(accessibilityStorageKey);
        if (stored) accessibilitySettings = Object.assign({}, accessibilityDefaults, JSON.parse(stored));
      } catch (error) {
        accessibilitySettings = Object.assign({}, accessibilityDefaults);
      }
      accessibilityVoiceFeedbackInput.checked = !!accessibilitySettings.voiceFeedback;
      accessibilityAnnounceButtonsInput.checked = !!accessibilitySettings.announceButtons;
      accessibilityAnnounceStatusInput.checked = !!accessibilitySettings.announceStatus;
      accessibilityAnnounceWarningsInput.checked = !!accessibilitySettings.announceWarnings;
      accessibilityAnnounceAxisInput.checked = !!accessibilitySettings.announceAxis;
      accessibilityQuietHoldInput.checked = !!accessibilitySettings.quietHold;
      if (!['1', '1.5', '2', '3'].includes(String(accessibilitySettings.speechRate))) {
        accessibilitySettings.speechRate = accessibilityDefaults.speechRate;
      }
      accessibilitySpeechRateInput.value = accessibilitySettings.speechRate || accessibilityDefaults.speechRate;
      if (!speechSupported()) {
        accessibilityStatus.textContent = 'Lettura vocale non supportata da questo browser';
        accessibilityVoiceFeedbackInput.disabled = true;
        accessibilityTestVoiceButton.disabled = true;
        accessibilityTestVoiceButton.classList.add('disabled');
      }
    }

    function saveAccessibilitySettings() {
      accessibilitySettings = {
        voiceFeedback: accessibilityVoiceFeedbackInput.checked,
        announceButtons: accessibilityAnnounceButtonsInput.checked,
        announceStatus: accessibilityAnnounceStatusInput.checked,
        announceWarnings: accessibilityAnnounceWarningsInput.checked,
        announceAxis: accessibilityAnnounceAxisInput.checked,
        quietHold: accessibilityQuietHoldInput.checked,
        speechRate: accessibilitySpeechRateInput.value
      };
      if (!accessibilitySettings.announceAxis) cancelAxisAnnouncement();
      if (!accessibilitySettings.announceStatus) cancelMessageAnnouncement();
      if (!accessibilitySettings.voiceFeedback && speechSupported()) {
        cancelAxisAnnouncement();
        cancelMessageAnnouncement();
        window.speechSynthesis.cancel();
      }
      updateHoldAnnouncementTimer();
      try {
        localStorage.setItem(accessibilityStorageKey, JSON.stringify(accessibilitySettings));
      } catch (error) {
      }
      accessibilityStatus.textContent = speechSupported() ? 'Impostazioni accessibilità salvate su questo browser' : 'Lettura vocale non supportata da questo browser';
    }

    function setupAccessibilitySettings() {
      loadAccessibilitySettings();
      [
        accessibilityVoiceFeedbackInput,
        accessibilityAnnounceButtonsInput,
        accessibilityAnnounceStatusInput,
        accessibilityAnnounceWarningsInput,
        accessibilityAnnounceAxisInput,
        accessibilityQuietHoldInput,
        accessibilitySpeechRateInput
      ].forEach(input => input.addEventListener('change', () => {
        const wasVoiceEnabled = accessibilitySettings.voiceFeedback;
        saveAccessibilitySettings();
        if (!wasVoiceEnabled && accessibilitySettings.voiceFeedback) {
          speakAccessibility('Lettura vocale attivata', { force: true, kind: 'test', cancelPrevious: true });
        }
      }));
      accessibilityTestVoiceButton.addEventListener('click', () => {
        speakAccessibility('Prova lettura vocale', { force: true, kind: 'test', cancelPrevious: true });
        accessibilityStatus.textContent = speechSupported() ? 'Prova vocale inviata' : 'Lettura vocale non supportata da questo browser';
      });
    }

    function setControlText(element, value) {
      if (element) element.textContent = value || '--';
    }

    function setControlStateText(value) {
      announceStatusChange(value);
      setControlText(controlState, value);
      setControlText(controlBottomState, value);
    }

    function setControlModeText(value) {
      setControlText(controlMode, value);
    }

    function setControlPitchText(value) {
      setControlText(controlPitch, value);
      if (controlModePitch) controlModePitch.textContent = value ? `Pitch ${value}` : '--';
    }

    function setControlRpmText(value) {
      setControlText(controlRpm, value);
      setControlText(controlBottomRpm, value);
    }

    function setControlMessageText(value) {
      announceControlMessage(value);
      setControlText(controlMessage, value);
    }

    function setControlAxisText(axisElement, value, axisName = '') {
      setControlText(axisElement, value);
      if (axisName) announceAxisPosition(axisName, value);
    }

    function setControlExtraVisible(visible) {
      if (!controlStatusPanel) return;
      controlStatusPanel.classList.toggle('control-extra-visible', visible);
      if (controlExtraToggle) controlExtraToggle.setAttribute('aria-expanded', visible ? 'true' : 'false');
    }

    function toggleControlExtraInfo() {
      if (!controlMobileMedia.matches || !controlStatusPanel) return;
      setControlExtraVisible(!controlStatusPanel.classList.contains('control-extra-visible'));
    }

    function setupControlExtraToggle() {
      if (!controlExtraToggle) return;
      controlExtraToggle.addEventListener('click', event => {
        event.preventDefault();
        toggleControlExtraInfo();
      });
      controlExtraToggle.addEventListener('keydown', event => {
        if (event.key !== 'Enter' && event.key !== ' ') return;
        event.preventDefault();
        toggleControlExtraInfo();
      });
      if (controlMobileMedia.addEventListener) {
        controlMobileMedia.addEventListener('change', () => setControlExtraVisible(false));
      } else if (controlMobileMedia.addListener) {
        controlMobileMedia.addListener(() => setControlExtraVisible(false));
      }
    }

    function setActiveControlPanel(panelName, scrollToPanel = false, announce = false) {
      const activePanel = controlPanelElements.some(panel => panel.dataset.controlPanel === panelName) ? panelName : 'jog';
      controlPanelElements.forEach(panel => {
        panel.classList.toggle('active', panel.dataset.controlPanel === activePanel);
      });
      controlMobileTabs.forEach(tab => {
        const active = tab.dataset.controlPanelTab === activePanel;
        tab.classList.toggle('active', active);
        tab.setAttribute('aria-selected', active ? 'true' : 'false');
      });
      if (scrollToPanel) {
        const panel = controlPanelElements.find(element => element.dataset.controlPanel === activePanel);
        if (panel && panel.scrollIntoView) panel.scrollIntoView({ block: 'start', behavior: 'smooth' });
      }
      if (announce) announcePanelChange(activePanel);
    }

    function setupControlPanelTabs() {
      controlMobileTabs.forEach(tab => {
        tab.setAttribute('role', 'tab');
        tab.addEventListener('click', event => {
          event.preventDefault();
          setActiveControlPanel(tab.dataset.controlPanelTab, false, true);
        });
      });
      setActiveControlPanel('jog');
    }

    function activateControlShortcut(element) {
      if (element.classList.contains('disabled')) return;
      const panelName = element.dataset.controlShortcutPanel;
      if (panelName) {
        setActiveControlPanel(panelName, true, true);
        controlActionStatus.textContent = `${panelName === 'stops' ? 'Fermi' : 'Modalità'} aperti`;
        return;
      }
      const actionCode = element.dataset.controlShortcutAction;
      if (actionCode) {
        pulseControlAction(actionCode, element.dataset.controlShortcutLabel || element.textContent.trim(), element);
      }
    }

    function setupControlStatusShortcuts() {
      controlShortcutElements.forEach(element => {
        element.addEventListener('click', event => {
          event.preventDefault();
          activateControlShortcut(element);
        });
        element.addEventListener('keydown', event => {
          if (event.key !== 'Enter' && event.key !== ' ') return;
          event.preventDefault();
          activateControlShortcut(element);
        });
      });
    }

    function fullscreenElement() {
      return document.fullscreenElement || document.webkitFullscreenElement || null;
    }

    function fullscreenSupported() {
      return !!(document.documentElement.requestFullscreen || document.documentElement.webkitRequestFullscreen);
    }

    function wakeLockSupported() {
      return !!(navigator.wakeLock && navigator.wakeLock.request);
    }

    function stopControlNoSleepFallback() {
      clearInterval(controlNoSleepDrawTimer);
      controlNoSleepDrawTimer = 0;
      if (!controlNoSleepVideo) return;
      controlNoSleepVideo.pause();
      if (controlNoSleepVideo.srcObject) {
        controlNoSleepVideo.srcObject.getTracks().forEach(track => track.stop());
      }
      controlNoSleepVideo.remove();
      controlNoSleepVideo = null;
    }

    function startControlNoSleepFallback() {
      if (controlNoSleepVideo) return;
      const canvas = document.createElement('canvas');
      if (!canvas.captureStream) return;
      canvas.width = 2;
      canvas.height = 2;
      const context = canvas.getContext('2d');
      if (!context) return;
      const drawFrame = () => {
        const dark = Math.floor(Date.now() / 1000) % 2 === 0;
        context.fillStyle = dark ? '#000' : '#111';
        context.fillRect(0, 0, 2, 2);
      };
      drawFrame();
      const video = document.createElement('video');
      video.muted = true;
      video.playsInline = true;
      video.setAttribute('playsinline', '');
      video.setAttribute('aria-hidden', 'true');
      video.style.cssText = 'position:fixed;left:0;bottom:0;width:1px;height:1px;opacity:0.01;pointer-events:none;';
      video.srcObject = canvas.captureStream(1);
      document.body.appendChild(video);
      controlNoSleepVideo = video;
      controlNoSleepDrawTimer = setInterval(drawFrame, 15000);
      const playResult = video.play();
      if (playResult && playResult.catch) playResult.catch(stopControlNoSleepFallback);
    }

    function releaseControlWakeLock() {
      stopControlNoSleepFallback();
      if (!controlWakeLock) return;
      const lock = controlWakeLock;
      controlWakeLock = null;
      if (lock.release) lock.release().catch(() => {});
    }

    function requestControlWakeLock() {
      if (!fullscreenElement() || document.hidden || controlWakeLock || controlWakeLockBusy) return;
      if (!wakeLockSupported()) {
        startControlNoSleepFallback();
        return;
      }
      controlWakeLockBusy = true;
      navigator.wakeLock.request('screen')
        .then(lock => {
          controlWakeLock = lock;
          stopControlNoSleepFallback();
          lock.addEventListener('release', () => {
            if (controlWakeLock === lock) controlWakeLock = null;
          });
        })
        .catch(() => {
          if (fullscreenElement() && !document.hidden) startControlNoSleepFallback();
        })
        .then(() => {
          controlWakeLockBusy = false;
        });
    }

    function syncControlWakeLock() {
      if (fullscreenElement() && !document.hidden) requestControlWakeLock();
      else releaseControlWakeLock();
    }

    function updateFullscreenButton() {
      if (!controlFullscreenButton) return;
      const supported = fullscreenSupported();
      const active = !!fullscreenElement();
      document.body.classList.toggle('control-fullscreen-active', active);
      controlFullscreenButton.disabled = !supported;
      controlFullscreenButton.classList.toggle('disabled', !supported);
      controlFullscreenButton.textContent = active ? 'Esci' : 'Intero';
      controlFullscreenButton.setAttribute('aria-label', active ? 'Esci da schermo intero' : 'Schermo intero');
    }

    function afterFullscreenChange() {
      updateFullscreenButton();
      syncControlWakeLock();
    }

    function toggleFullscreen() {
      if (!fullscreenSupported()) return;
      let result;
      const enteringFullscreen = !fullscreenElement();
      if (!enteringFullscreen) {
        if (document.exitFullscreen) result = document.exitFullscreen();
        else if (document.webkitExitFullscreen) result = document.webkitExitFullscreen();
      } else if (document.documentElement.requestFullscreen) {
        result = document.documentElement.requestFullscreen();
      } else if (document.documentElement.webkitRequestFullscreen) {
        result = document.documentElement.webkitRequestFullscreen();
      }
      if (enteringFullscreen) startControlNoSleepFallback();
      updateFullscreenButton();
      if (enteringFullscreen) setTimeout(syncControlWakeLock, 1000);
      if (result && result.then) {
        result.then(afterFullscreenChange).catch(() => {
          updateFullscreenButton();
          syncControlWakeLock();
        });
      }
    }

    if (controlFullscreenButton) {
      controlFullscreenButton.addEventListener('click', event => {
        event.preventDefault();
        toggleFullscreen();
      });
      document.addEventListener('fullscreenchange', afterFullscreenChange);
      document.addEventListener('webkitfullscreenchange', afterFullscreenChange);
      document.addEventListener('visibilitychange', syncControlWakeLock);
      updateFullscreenButton();
    }

    setupAccessibilitySettings();
    setupControlExtraToggle();
    setupControlPanelTabs();
    setupControlStatusShortcuts();
    showSection(sectionFromHash());
    window.addEventListener('hashchange', () => handleSectionChange(true));

    const ws = new WebSocket(`ws://${window.location.host.split(':')[0]}:81`);

    ws.onopen = () => {
      logMessage('Connesso al server');
      setControlStateText('Connesso');
      setControlMessageText('Connesso');
      controlActionStatus.textContent = 'Connesso';
      updateButtonStates();
    };

    ws.onmessage = (event) => {
      const handled = handleRealtimeMessage(event.data);
      if (!handled) logMessage('Ricevuto: ' + event.data);
    };

    ws.onclose = () => {
      releaseAllControlActions(false);
      setControlStateText('Disconnesso');
      setControlMessageText('Disconnesso');
      controlActionStatus.textContent = 'Disconnesso';
      updateButtonStates();
      logMessage('Disconnesso dal server');
    };

    function updateButtonStates() {
      const uploadInProgress = tftUploadInProgress || firmwareUploadInProgress;
      sendButton.disabled = commandInput.value.trim().length < 1 || uploadInProgress;
      addGcodeButton.disabled = gcodeNameInput.value.trim().length < 2 || gcodeContentInput.value.trim().length < 2 || uploadInProgress;
      saveConfigButton.disabled = uploadInProgress;
      resetConfigButton.disabled = uploadInProgress;
      saveWifiButton.disabled = uploadInProgress;
      resetWifiButton.disabled = uploadInProgress;
      saveKeyboardButton.disabled = uploadInProgress;
      resetKeyboardButton.disabled = uploadInProgress;
      tftFirstUploadCheckbox.disabled = uploadInProgress;
      tftFileInput.disabled = uploadInProgress;
      firmwareFileInput.disabled = uploadInProgress;
      gcodeFileInput.disabled = uploadInProgress;
      const controlDisabled = uploadInProgress || ws.readyState !== WebSocket.OPEN;
      controlButtons.forEach(button => {
        button.disabled = controlDisabled;
        button.classList.toggle('disabled', controlDisabled);
      });
      controlShortcutElements.forEach(element => {
        const disabled = !!element.dataset.controlShortcutAction && controlDisabled;
        element.classList.toggle('disabled', disabled);
        element.setAttribute('aria-disabled', disabled ? 'true' : 'false');
      });
      sendButton.classList.toggle('disabled', sendButton.disabled);
      addGcodeButton.classList.toggle('disabled', addGcodeButton.disabled);
      saveConfigButton.classList.toggle('disabled', saveConfigButton.disabled);
      resetConfigButton.classList.toggle('disabled', resetConfigButton.disabled);
      saveWifiButton.classList.toggle('disabled', saveWifiButton.disabled);
      resetWifiButton.classList.toggle('disabled', resetWifiButton.disabled);
      saveKeyboardButton.classList.toggle('disabled', saveKeyboardButton.disabled);
      resetKeyboardButton.classList.toggle('disabled', resetKeyboardButton.disabled);
      document.querySelectorAll('.keyboard-learn').forEach(button => {
        button.disabled = uploadInProgress;
        button.classList.toggle('disabled', button.disabled);
      });
      tftBrowseButton.classList.toggle('disabled', uploadInProgress);
      firmwareBrowseButton.classList.toggle('disabled', uploadInProgress);
      gcodeBrowseButton.classList.toggle('disabled', uploadInProgress);
    }

    function websocketReady() {
      return ws.readyState === WebSocket.OPEN;
    }

    function setControlButtonsActive(actionCode, active) {
      document.querySelectorAll(`[data-control-action="${actionCode}"]`).forEach(button => {
        button.classList.toggle('active', active);
      });
    }

    function sendWebControlAction(actionCode, isPress) {
      if (!websocketReady()) {
        controlActionStatus.textContent = 'Disconnesso';
        announceWarning('Disconnesso dal server');
        updateButtonStates();
        return false;
      }
      ws.send(`@${actionCode}:${isPress ? 1 : 0}\n`);
      return true;
    }

    function controlButtonLabel(button) {
      if (!button) return '';
      return button.dataset.controlLabel || button.getAttribute('aria-label') || button.textContent.trim();
    }

    function startControlHoldHeartbeat() {
      if (controlHoldHeartbeatTimer) return;
      controlHoldHeartbeatTimer = setInterval(() => {
        if (!websocketReady()) {
          releaseAllControlActions(false);
          return;
        }
        activeControlActions.forEach(actionCode => {
          sendWebControlAction(actionCode, true);
        });
      }, 200);
    }

    function stopControlHoldHeartbeatIfIdle() {
      if (activeControlActions.size > 0) return;
      clearInterval(controlHoldHeartbeatTimer);
      controlHoldHeartbeatTimer = 0;
    }

    function pressControlButton(button) {
      if (button.disabled) return;
      const actionCode = button.dataset.controlAction;
      if (!actionCode || activeControlActions.has(actionCode)) return;
      if (sendWebControlAction(actionCode, true)) {
        activeControlActions.add(actionCode);
        setControlButtonsActive(actionCode, true);
        startControlHoldHeartbeat();
        const label = controlButtonLabel(button);
        controlActionStatus.textContent = `${label} premuto`;
        announceButtonAction(actionAnnouncementForSpeech(actionCode, label), 'premuto');
        updateWebUiNumpadTracking(actionCode);
        updateHoldAnnouncementTimer();
      }
    }

    function releaseControlAction(actionCode, sendRelease) {
      if (!activeControlActions.has(actionCode)) return;
      activeControlActions.delete(actionCode);
      setControlButtonsActive(actionCode, false);
      if (sendRelease) sendWebControlAction(actionCode, false);
      stopControlHoldHeartbeatIfIdle();
      updateHoldAnnouncementTimer();
      if (sendRelease) {
        const button = document.querySelector(`[data-control-action="${actionCode}"]`);
        announceButtonAction(actionAnnouncementForSpeech(actionCode, controlButtonLabel(button)), 'rilasciato');
      }
    }

    function releaseControlButton(button, sendRelease) {
      const actionCode = button.dataset.controlAction;
      if (actionCode) releaseControlAction(actionCode, sendRelease);
    }

    function releaseAllControlActions(sendRelease = true) {
      Array.from(activeControlActions).forEach(actionCode => releaseControlAction(actionCode, sendRelease));
    }

    function pulseControlAction(actionCode, label, activeElement) {
      if (!actionCode || !sendWebControlAction(actionCode, true)) return false;
      if (activeElement) activeElement.classList.add('active');
      controlActionStatus.textContent = `${label} inviato`;
      announceButtonAction(actionAnnouncementForSpeech(actionCode, label));
      updateWebUiNumpadTracking(actionCode);
      setTimeout(() => {
        sendWebControlAction(actionCode, false);
        if (activeElement) activeElement.classList.remove('active');
      }, 70);
      return true;
    }

    function pulseControlButton(button) {
      if (button.disabled) return;
      const actionCode = button.dataset.controlAction;
      pulseControlAction(actionCode, controlButtonLabel(button), button);
    }

    function setupControlButtons() {
      controlButtons.forEach(button => {
        if (button.dataset.controlHold === '1') {
          button.addEventListener('pointerdown', event => {
            if (event.button !== undefined && event.button !== 0) return;
            event.preventDefault();
            if (button.setPointerCapture) button.setPointerCapture(event.pointerId);
            pressControlButton(button);
          });
          button.addEventListener('pointerup', event => {
            event.preventDefault();
            releaseControlButton(button, true);
          });
          button.addEventListener('pointercancel', () => releaseControlButton(button, true));
          button.addEventListener('lostpointercapture', () => releaseControlButton(button, true));
          button.addEventListener('pointerleave', event => {
            if (event.pointerType === 'mouse') releaseControlButton(button, true);
          });
        } else {
          button.addEventListener('click', event => {
            event.preventDefault();
            pulseControlButton(button);
          });
        }
      });
      window.addEventListener('blur', () => releaseAllControlActions(true));
      window.addEventListener('beforeunload', () => releaseAllControlActions(true));
      document.addEventListener('visibilitychange', () => {
        if (document.hidden) releaseAllControlActions(true);
      });
    }

    function updateControlStatusFromText(line) {
      if (!line.startsWith('<') || !line.endsWith('>')) return false;
      const parts = line.substring(1, line.length - 1).split('|');
      setControlStateText(parts[0]);
      const wpos = parts.find(part => part.startsWith('WPos:'));
      if (wpos) {
        const values = wpos.substring('WPos:'.length).split(',');
        setControlAxisText(controlX, values[0], 'X');
        setControlAxisText(controlZ, values[2], 'Z');
      }
      const fs = parts.find(part => part.startsWith('FS:'));
      if (fs) {
        const values = fs.substring('FS:'.length).split(',');
        setControlRpmText(values[1]);
      }
      return true;
    }

    function updateControlStatusLine(line) {
      const index = line.indexOf('=');
      if (index <= 3 || !line.startsWith('UI.')) return false;
      const key = line.substring(3, index);
      const value = line.substring(index + 1);
      if (key === 'status') setControlStateText(value);
      else if (key === 'mode') setControlModeText(value);
      else if (key === 'pitch') setControlPitchText(value);
      else if (key === 'measure') setControlText(controlMeasure, value);
      else if (key === 'step') setControlText(controlStep, value);
      else if (key === 'turns') setControlText(controlTurns, value);
      else if (key === 'angle') setControlText(controlAngle, value);
      else if (key === 'x') setControlAxisText(controlX, value, 'X');
      else if (key === 'xLeft') controlXStops.dataset.left = value;
      else if (key === 'xRight') controlXStops.dataset.right = value;
      else if (key === 'y') setControlAxisText(controlY, value, 'Y');
      else if (key === 'yLeft') controlYStops.dataset.left = value;
      else if (key === 'yRight') controlYStops.dataset.right = value;
      else if (key === 'z') setControlAxisText(controlZ, value, 'Z');
      else if (key === 'zLeft') controlZStops.dataset.left = value;
      else if (key === 'zRight') controlZStops.dataset.right = value;
      else if (key === 'rpm') setControlRpmText(value);
      else if (key === 'message') setControlMessageText(value);
      updateAxisStopDisplays(controlXStops, controlXInlineStops);
      updateAxisStopDisplays(controlYStops, controlYInlineStops);
      updateAxisStopDisplays(controlZStops, controlZInlineStops);
      return true;
    }

    function updateStopDisplay(element) {
      if (!element) return;
      const left = element.dataset.left || '';
      const right = element.dataset.right || '';
      element.textContent = left || right ? `${left || '-'} / ${right || '-'}` : '--';
    }

    function updateInlineStopDisplay(element, left, right) {
      setControlText(element, left || right ? `${left || '-'} / ${right || '-'}` : '');
    }

    function updateAxisStopDisplays(statusElement, inlineElement) {
      if (!statusElement) return;
      const left = statusElement.dataset.left || '';
      const right = statusElement.dataset.right || '';
      updateStopDisplay(statusElement);
      updateInlineStopDisplay(inlineElement, left, right);
    }

    function applyControlConfigValues(values) {
      const showY = values.activeY === '1';
      controlYElements.forEach(element => {
        element.hidden = !showY;
      });
      if (controlStatusPanel) controlStatusPanel.classList.toggle('control-y-active', showY);
    }

    function parseStatusValue(data, key) {
      const prefix = key + '=';
      const line = data.split('\n').find(l => l.startsWith(prefix));
      return line ? line.substring(prefix.length) : '';
    }

    function parseKeyValueText(data) {
      const values = {};
      data.split('\n').forEach(line => {
        const index = line.indexOf('=');
        if (index > 0) {
          values[line.substring(0, index)] = line.substring(index + 1);
        }
      });
      return values;
    }

    function updateFirmwareProgress(percent, message) {
      if (!firmwareUploadInProgress && percent < 100) return;
      firmwareProgress.hidden = false;
      firmwareProgress.value = Math.max(Number(firmwareProgress.value) || 0, Math.min(100, Math.max(0, percent)));
      if (message) firmwareStatus.textContent = message;
    }

    function updateFirmwareStatusFromText(data) {
      const size = Number(parseStatusValue(data, 'FW.size'));
      const uploaded = Number(parseStatusValue(data, 'FW.uploaded'));
      const message = parseStatusValue(data, 'FW.message');
      if (size > 0 && uploaded >= 0) {
        updateFirmwareProgress(Math.round(uploaded * 100 / size), message || `Scrittura firmware ${Math.round(uploaded * 100 / size)}%`);
      } else if (message) {
        firmwareStatus.textContent = message;
      }
    }

    function pollFirmwareStatus() {
      if (firmwareStatusPollBusy) return;
      firmwareStatusPollBusy = true;
      fetch(`/status?ts=${Date.now()}`, { cache: 'no-store' })
        .then(response => response.text())
        .then(updateFirmwareStatusFromText)
        .catch(() => {})
        .then(() => {
          firmwareStatusPollBusy = false;
        });
    }

    function startFirmwareStatusPolling() {
      clearInterval(firmwareStatusPollTimer);
      firmwareStatusPollTimer = setInterval(pollFirmwareStatus, 1000);
    }

    function stopFirmwareStatusPolling() {
      clearInterval(firmwareStatusPollTimer);
      firmwareStatusPollTimer = 0;
    }

    function formatScaledConfigValue(value) {
      if (!Number.isFinite(value)) return '';
      return value.toFixed(4).replace(/\.?0+$/, '');
    }

    function configValueToDisplay(field, value) {
      if (field.firmwareScale) {
        return formatScaledConfigValue(Number(value) / field.firmwareScale);
      }
      return value;
    }

    function configValueToFirmware(field, value) {
      const trimmed = value.trim();
      if (field.firmwareScale) {
        const parsed = Number(trimmed);
        return Number.isFinite(parsed) ? String(Math.round(parsed * field.firmwareScale)) : trimmed;
      }
      return trimmed;
    }

    function addConfigHelp(row, field) {
      if (!field.help) return;
      const help = document.createElement('small');
      help.className = 'config-help';
      help.textContent = field.help;
      row.appendChild(help);
    }

    function renderConfigFields() {
      configFields.innerHTML = '';
      machineConfigSections.forEach((section, index) => {
        const sectionElement = document.createElement('details');
        sectionElement.className = 'config-section settings-group';
        const summary = document.createElement('summary');
        summary.textContent = `${section.title} (${section.fields.length})`;
        const grid = document.createElement('div');
        grid.className = 'config-grid';
        section.fields.forEach(field => {
          const id = `config-${field.key}`;
          const row = document.createElement('div');
          row.className = field.type === 'checkbox' ? 'config-field config-checkbox-field' : 'config-field';
          if (field.type === 'checkbox') {
            const label = document.createElement('label');
            label.className = 'config-checkbox';
            label.htmlFor = id;
            const input = document.createElement('input');
            input.type = 'checkbox';
            input.id = id;
            input.dataset.key = field.key;
            const text = document.createElement('span');
            text.textContent = field.label;
            label.appendChild(input);
            label.appendChild(text);
            row.appendChild(label);
            addConfigHelp(row, field);
          } else {
            const label = document.createElement('label');
            label.className = 'config-label';
            label.htmlFor = id;
            label.textContent = field.label;
            if (field.unit) {
              const unit = document.createElement('span');
              unit.className = 'config-unit';
              unit.textContent = ` (${field.unit})`;
              label.appendChild(unit);
            }
            const input = document.createElement('input');
            input.type = 'number';
            input.id = id;
            input.dataset.key = field.key;
            input.min = field.min;
            input.max = field.max;
            input.step = field.step;
            input.required = true;
            row.appendChild(label);
            row.appendChild(input);
            addConfigHelp(row, field);
          }
          grid.appendChild(row);
        });
        sectionElement.appendChild(summary);
        sectionElement.appendChild(grid);
        configFields.appendChild(sectionElement);
      });
    }

    function applyConfigValues(values) {
      machineConfigFields.forEach(field => {
        const input = document.getElementById(`config-${field.key}`);
        if (!input || !(field.key in values)) return;
        if (field.type === 'checkbox') {
          input.checked = values[field.key] === '1';
        } else {
          input.value = configValueToDisplay(field, values[field.key]);
        }
      });
    }

    function loadConfig() {
      configStatus.textContent = 'Caricamento configurazione macchina...';
      fetch('/config', { cache: 'no-store' })
        .then(response => response.text())
        .then(data => {
          const values = parseKeyValueText(data);
          applyConfigValues(values);
          applyControlConfigValues(values);
          configStatus.textContent = '';
        })
        .catch(() => {
          configStatus.textContent = 'Impossibile caricare la configurazione macchina';
        });
    }

    function collectConfigValues() {
      const values = new URLSearchParams();
      machineConfigFields.forEach(field => {
        const input = document.getElementById(`config-${field.key}`);
        values.append(field.key, field.type === 'checkbox' ? (input.checked ? '1' : '0') : configValueToFirmware(field, input.value));
      });
      return values;
    }

    function saveConfig(event) {
      event.preventDefault();
      configStatus.textContent = 'Salvataggio configurazione macchina...';
      fetch('/config', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: collectConfigValues()
      })
      .then(response => response.text().then(text => ({ ok: response.ok, text })))
      .then(result => {
        configStatus.textContent = result.text;
        logMessage(result.text);
        if (result.ok) {
          waitForControllerReload();
        }
      })
      .catch(() => {
        configStatus.textContent = 'Impossibile salvare la configurazione macchina';
      });
    }

    function resetConfig() {
      if (!confirm('Ripristinare la configurazione macchina ai valori di fabbrica e riavviare il controller?')) return;
      configStatus.textContent = 'Ripristino configurazione macchina...';
      fetch('/config/reset', { method: 'POST' })
        .then(response => response.text().then(text => ({ ok: response.ok, text })))
        .then(result => {
          configStatus.textContent = result.text;
          logMessage(result.text);
          if (result.ok) {
            waitForControllerReload();
          }
        })
        .catch(() => {
          configStatus.textContent = 'Impossibile ripristinare la configurazione macchina';
        });
    }

    function renderKeyboardFields() {
      keyboardFields.innerHTML = '';
      keyboardBindingSections.forEach((section, index) => {
        const sectionElement = document.createElement('details');
        sectionElement.className = 'config-section keyboard-group';
        sectionElement.open = index === 0;
        const summary = document.createElement('summary');
        summary.textContent = `${section.title} (${section.fields.length})`;
        const grid = document.createElement('div');
        grid.className = 'keyboard-grid';
        section.fields.forEach(field => {
          const id = `keyboard-${field.key}`;
          const row = document.createElement('div');
          row.className = 'keyboard-binding';

          const label = document.createElement('label');
          label.htmlFor = id;
          label.textContent = field.label;

          const input = document.createElement('input');
          input.type = 'number';
          input.id = id;
          input.dataset.key = field.key;
          input.min = 1;
          input.max = 255;
          input.step = 1;
          input.required = true;

          const learnButton = document.createElement('button');
          learnButton.type = 'button';
          learnButton.className = 'secondary keyboard-learn';
          learnButton.dataset.key = field.key;
          learnButton.textContent = 'Impara';
          learnButton.addEventListener('click', () => beginKeyboardLearn(field));

          row.appendChild(label);
          row.appendChild(input);
          row.appendChild(learnButton);
          grid.appendChild(row);
        });
        sectionElement.appendChild(summary);
        sectionElement.appendChild(grid);
        keyboardFields.appendChild(sectionElement);
      });
    }

    function applyKeyboardValues(values) {
      keyboardShowKeysInput.checked = values.showKeyPresses === '1';
      keyboardBindingFields.forEach(field => {
        const input = document.getElementById(`keyboard-${field.key}`);
        if (input && field.key in values) input.value = values[field.key];
      });
    }

    function loadKeyboardConfig() {
      keyboardStatus.textContent = 'Caricamento configurazione tastiera...';
      fetch('/keyboard-config', { cache: 'no-store' })
        .then(response => response.text())
        .then(data => {
          applyKeyboardValues(parseKeyValueText(data));
          keyboardStatus.textContent = '';
        })
        .catch(() => {
          keyboardStatus.textContent = 'Impossibile caricare la configurazione tastiera';
        });
    }

    function collectKeyboardConfigValues() {
      const values = new URLSearchParams();
      values.append('showKeyPresses', keyboardShowKeysInput.checked ? '1' : '0');
      keyboardBindingFields.forEach(field => {
        const input = document.getElementById(`keyboard-${field.key}`);
        values.append(field.key, input.value.trim());
      });
      return values;
    }

    function stopKeyboardCaptureRequest() {
      fetch('/keyboard-capture', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: new URLSearchParams({ enabled: '0' })
      }).catch(() => {});
    }

    function clearKeyboardLearn() {
      clearTimeout(keyboardLearnTimer);
      keyboardLearnTimer = 0;
      keyboardLearnTarget = '';
    }

    function saveKeyboardConfig(event) {
      event.preventDefault();
      clearKeyboardLearn();
      stopKeyboardCaptureRequest();
      keyboardStatus.textContent = 'Salvataggio configurazione tastiera...';
      fetch('/keyboard-config', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: collectKeyboardConfigValues()
      })
      .then(response => response.text().then(text => ({ ok: response.ok, text })))
      .then(result => {
        keyboardStatus.textContent = result.text;
        logMessage(result.text);
      })
      .catch(() => {
        keyboardStatus.textContent = 'Impossibile salvare la configurazione tastiera';
      });
    }

    function resetKeyboardConfig() {
      if (!confirm('Ripristinare la mappatura tastiera ai valori di fabbrica?')) return;
      clearKeyboardLearn();
      stopKeyboardCaptureRequest();
      keyboardStatus.textContent = 'Ripristino configurazione tastiera...';
      fetch('/keyboard-config/reset', { method: 'POST' })
        .then(response => response.text().then(text => ({ ok: response.ok, text })))
        .then(result => {
          keyboardStatus.textContent = result.text;
          logMessage(result.text);
          if (result.ok) loadKeyboardConfig();
        })
        .catch(() => {
          keyboardStatus.textContent = 'Impossibile ripristinare la configurazione tastiera';
        });
    }

    function beginKeyboardLearn(field) {
      clearKeyboardLearn();
      keyboardLearnTarget = field.key;
      keyboardStatus.textContent = `Apprendimento ${field.label}: premi un tasto sulla tastiera fisica`;
      keyboardLearnTimer = setTimeout(() => {
        keyboardLearnTarget = '';
        keyboardStatus.textContent = 'Acquisizione tasto scaduta';
        stopKeyboardCaptureRequest();
      }, 30000);
      fetch('/keyboard-capture', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: new URLSearchParams({ enabled: '1' })
      })
      .then(response => response.text().then(text => ({ ok: response.ok, text })))
      .then(result => {
        if (!result.ok) {
          clearKeyboardLearn();
          keyboardStatus.textContent = result.text;
        }
      })
      .catch(() => {
        clearKeyboardLearn();
        keyboardStatus.textContent = 'Acquisizione tasto non riuscita';
      });
    }

    function handleKeyboardPressCode(code) {
      keyboardLastKey.textContent = String(code);
      if (!keyboardLearnTarget) return;
      const input = document.getElementById(`keyboard-${keyboardLearnTarget}`);
      if (input) {
        input.value = String(code);
        const field = keyboardBindingFields.find(item => item.key === keyboardLearnTarget);
        keyboardStatus.textContent = `${field ? field.label : keyboardLearnTarget} impostato al codice tasto ${code}`;
      }
      clearKeyboardLearn();
    }

    function applyWifiValues(values) {
      wifiEnabledInput.checked = values.wifiEnabled === '1';
      wifiSsidInput.value = values.wifiSsid || '';
      wifiPasswordInput.value = '';
      wifiPasswordInput.placeholder = values.wifiPasswordSet === '1' ? 'Lascia invariata' : 'Password';
      wifiClearPasswordInput.checked = false;
      const mode = values.wifiMode || 'sconosciuto';
      const ip = values.wifiIp ? `, ${values.wifiIp}` : '';
      const setup = values.setupApSsid ? `, AP di configurazione ${values.setupApSsid}` : '';
      wifiStatusElement.textContent = `Modo: ${mode}${ip}${setup}`;
    }

    function loadWifi() {
      wifiStatusElement.textContent = 'Caricamento configurazione WiFi...';
      fetch('/wifi', { cache: 'no-store' })
        .then(response => response.text())
        .then(data => {
          applyWifiValues(parseKeyValueText(data));
        })
        .catch(() => {
          wifiStatusElement.textContent = 'Impossibile caricare la configurazione WiFi';
        });
    }

    function collectWifiValues() {
      return new URLSearchParams({
        wifiEnabled: wifiEnabledInput.checked ? '1' : '0',
        wifiSsid: wifiSsidInput.value.trim(),
        wifiPassword: wifiPasswordInput.value,
        wifiClearPassword: wifiClearPasswordInput.checked ? '1' : '0'
      });
    }

    function saveWifi(event) {
      event.preventDefault();
      wifiStatusElement.textContent = 'Salvataggio configurazione WiFi...';
      fetch('/wifi', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: collectWifiValues()
      })
      .then(response => response.text().then(text => ({ ok: response.ok, text })))
      .then(result => {
        wifiStatusElement.textContent = result.text;
        logMessage(result.text);
        if (result.ok) {
          waitForControllerReload();
        }
      })
      .catch(() => {
        wifiStatusElement.textContent = 'Impossibile salvare la configurazione WiFi';
      });
    }

    function resetWifi() {
      if (!confirm('Dimenticare la rete WiFi salvata e riavviare l\'AP di configurazione?')) return;
      wifiStatusElement.textContent = 'Ripristino configurazione WiFi...';
      fetch('/wifi/reset', { method: 'POST' })
        .then(response => response.text().then(text => ({ ok: response.ok, text })))
        .then(result => {
          wifiStatusElement.textContent = result.text;
          logMessage(result.text);
          if (result.ok) {
            waitForControllerReload();
          }
        })
        .catch(() => {
          wifiStatusElement.textContent = 'Impossibile ripristinare la configurazione WiFi';
        });
    }

    function handleRealtimeMessage(message) {
      let handled = false;
      message.split('\n').map(line => line.trim()).filter(line => !!line).forEach(line => {
        if (updateControlStatusLine(line)) {
          handled = true;
        } else if (updateControlStatusFromText(line)) {
          handled = true;
        } else if (line.startsWith('WEBUI.error=')) {
          const text = line.substring('WEBUI.error='.length);
          controlActionStatus.textContent = text;
          announceWarning(text);
          handled = true;
        } else if (line.startsWith('WEBUI.warning=')) {
          const text = line.substring('WEBUI.warning='.length);
          controlActionStatus.textContent = text;
          announceWarning(text);
          handled = true;
        } else if (line.startsWith('KEY.press=')) {
          const code = Number(line.substring('KEY.press='.length));
          if (!Number.isNaN(code)) handleKeyboardPressCode(code);
          handled = true;
        } else if (line.startsWith('KEY.release=') || line.startsWith('KEY.action=')) {
          handled = true;
        } else if (line.startsWith('FW: avanzamento ')) {
          const percent = Number(line.substring('FW: avanzamento '.length).replace('%', ''));
          if (!Number.isNaN(percent)) {
            updateFirmwareProgress(percent, `Scrittura firmware ${percent}%`);
          }
          handled = true;
        } else if (line === 'FW: upload completato, riavvio del controller') {
          updateFirmwareProgress(100, 'Upload firmware completato. Riavvio del controller...');
          handled = true;
        } else if (line.startsWith('FW: errore:')) {
          firmwareStatus.textContent = line.substring('FW: '.length);
          announceWarning(firmwareStatus.textContent);
          handled = true;
        }
      });
      return handled;
    }

    function waitForControllerReload() {
      clearTimeout(firmwareReloadTimer);
      firmwareReloadTimer = setTimeout(() => {
        fetch(`/status?reload=${Date.now()}`, { cache: 'no-store' })
          .then(response => {
            if (response.ok) {
              window.location.reload();
            } else {
              waitForControllerReload();
            }
          })
          .catch(waitForControllerReload);
      }, 2000);
    }

    function waitForFirmwareReload() {
      waitForControllerReload();
    }

    commandInput.addEventListener('input', updateButtonStates);
    gcodeNameInput.addEventListener('input', updateButtonStates);
    gcodeContentInput.addEventListener('input', updateButtonStates);
    configForm.addEventListener('submit', saveConfig);
    resetConfigButton.addEventListener('click', resetConfig);
    wifiForm.addEventListener('submit', saveWifi);
    resetWifiButton.addEventListener('click', resetWifi);
    keyboardForm.addEventListener('submit', saveKeyboardConfig);
    resetKeyboardButton.addEventListener('click', resetKeyboardConfig);
    tftFirstUploadCheckbox.addEventListener('change', saveTftFirstUploadPreference);
    tftFileInput.addEventListener('change', uploadTftFile);
    firmwareFileInput.addEventListener('change', uploadFirmwareFile);
    gcodeFileInput.addEventListener('change', loadGcodeFile);

    document.addEventListener('DOMContentLoaded', () => {
      setupControlButtons();
      loadTftFirstUploadPreference();
      renderConfigFields();
      renderKeyboardFields();
      loadConfig();
      loadWifi();
      loadKeyboardConfig();
      updateButtonStates();
    });

    function loadTftFirstUploadPreference() {
      try {
        const stored = localStorage.getItem(tftFirstUploadStorageKey);
        if (stored === 'true') {
          tftFirstUploadCheckbox.checked = true;
        } else if (stored === 'false') {
          tftFirstUploadCheckbox.checked = false;
        }
      } catch (error) {
      }
    }

    function saveTftFirstUploadPreference() {
      try {
        localStorage.setItem(tftFirstUploadStorageKey, tftFirstUploadCheckbox.checked ? 'true' : 'false');
      } catch (error) {
      }
    }

    function send() {
      const command = commandInput.value.trim();
      if (command) {
        logMessage('Inviato: ' + command);
        ws.send(command + '\n');
        commandInput.value = '';
        updateButtonStates();
      }
    }

    commandInput.addEventListener('keydown', (event) => {
      if (event.key === 'Enter') send();
    });

    sendButton.addEventListener('click', () => {
      send();
    });

    function removeComments(content) {
      return content.split('\n').map(line => line.split(';')[0].trim()).filter(line => !!line).join('\n');
    }

    function loadGcodeFile() {
      const file = gcodeFileInput.files[0];
      if (!file) return;
      const reader = new FileReader();
      reader.onload = () => {
        const text = String(reader.result || '');
        gcodeContentInput.value = text;
        gcodeNameInput.value = file.name.replace(/\.(gcode|nc|txt)$/i, '');
        gcodeFileInput.value = '';
        updateButtonStates();
        logMessage(`File ${file.name} caricato (${(text.length / 1024).toFixed(1)} KB): premi Salva per memorizzarlo.`);
      };
      reader.onerror = () => {
        gcodeFileInput.value = '';
        logMessage(`Impossibile leggere il file ${file.name}`);
      };
      reader.readAsText(file);
    }

    addGcodeButton.addEventListener('click', () => {
      const name = gcodeNameInput.value.trim();
      let content = gcodeContentInput.value.trim();
      if (removeCommentsCheckbox.checked) {
        content = removeComments(content);
      }
      if (name && content) {
        fetch('/gcode/add', {
          method: 'POST',
          headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
          body: new URLSearchParams({ name, gcode: content })
        })
        .then(response => response.text())
        .then(data => {
          logMessage(data);
          listGcodes();
          gcodeNameInput.value = '';
          gcodeContentInput.value = '';
          updateButtonStates();
        });
      }
    });

    function uploadTftFile() {
      const file = tftFileInput.files[0];
      if (!file || tftUploadInProgress) return;
      const nextionBaud = tftFirstUploadCheckbox.checked ? 9600 : 115200;

      const formData = new FormData();
      formData.append('tft', file, file.name);
      const request = new XMLHttpRequest();
      tftUploadInProgress = true;
      tftProgress.value = 0;
      tftProgress.hidden = false;
      tftStatus.textContent = `Caricamento di ${file.name} a ${nextionBaud} baud. Lascia aperta questa pagina; la scrittura del display può richiedere diversi minuti.`;
      updateButtonStates();

      request.upload.onprogress = event => {
        if (event.lengthComputable) {
          tftProgress.value = Math.round(event.loaded * 100 / event.total);
        }
      };
      request.onload = () => {
        tftUploadInProgress = false;
        tftStatus.textContent = request.responseText;
        logMessage(request.responseText);
        tftFileInput.value = '';
        tftProgress.hidden = true;
        updateButtonStates();
      };
      request.onerror = () => {
        tftUploadInProgress = false;
        tftStatus.textContent = 'Upload TFT non riuscito';
        logMessage('Upload TFT non riuscito');
        announceWarning('Upload TFT non riuscito');
        tftFileInput.value = '';
        tftProgress.hidden = true;
        updateButtonStates();
      };
      request.open('POST', `/tft/upload?size=${file.size}&baud=${nextionBaud}`);
      request.send(formData);
    }

    function uploadFirmwareFile() {
      const file = firmwareFileInput.files[0];
      if (!file || tftUploadInProgress || firmwareUploadInProgress) return;
      if (!file.name.toLowerCase().endsWith('.bin')) {
        firmwareStatus.textContent = 'Seleziona un file firmware .bin compilato';
        announceWarning('Seleziona un file firmware bin compilato');
        firmwareFileInput.value = '';
        return;
      }

      const formData = new FormData();
      formData.append('firmware', file, file.name);
      const request = new XMLHttpRequest();
      firmwareUploadInProgress = true;
      firmwareProgress.value = 0;
      firmwareProgress.hidden = false;
      firmwareStatus.textContent = `Caricamento di ${file.name}. Lascia aperta questa pagina; il controller si riavvierà al termine dell'upload.`;
      startFirmwareStatusPolling();
      updateButtonStates();

      request.upload.onprogress = event => {
        if (event.lengthComputable) {
          firmwareStatus.textContent = `Invio firmware al controller ${Math.round(event.loaded * 100 / event.total)}%. Attendo l'avanzamento di scrittura dal controller.`;
        }
      };
      request.onload = () => {
        logMessage(request.responseText);
        firmwareFileInput.value = '';
        stopFirmwareStatusPolling();
        if (request.status >= 200 && request.status < 300) {
          firmwareProgress.value = 100;
          firmwareStatus.textContent = `${request.responseText} Attendo che il controller torni online.`;
          waitForFirmwareReload();
        } else {
          firmwareUploadInProgress = false;
          firmwareStatus.textContent = request.responseText;
          announceWarning(request.responseText);
          firmwareProgress.hidden = true;
          updateButtonStates();
        }
      };
      request.onerror = () => {
        firmwareUploadInProgress = false;
        stopFirmwareStatusPolling();
        firmwareStatus.textContent = 'Upload firmware non riuscito';
        logMessage('Upload firmware non riuscito');
        announceWarning('Upload firmware non riuscito');
        firmwareFileInput.value = '';
        firmwareProgress.hidden = true;
        updateButtonStates();
      };
      request.open('POST', `/firmware/upload?size=${file.size}`);
      request.send(formData);
    }

    function listGcodes() {
      fetch('/gcode/list')
        .then(response => response.text())
        .then(data => {
          gcodeList.innerHTML = '';
          gcodeList.classList.toggle('empty', !data);
          if (data) {
            data.split('\n').map(g => g.trim()).filter(g => !!g).forEach(gcode => {
              const row = document.createElement('div');
              row.className = 'gcode-row';
              row.dataset.name = gcode;
              row.innerHTML = `
                <span class="gcode-item" data-name="${gcode}">${gcode}</span>
                <span class="gcode-size"></span>
                <span class="remove-icon" data-name="${gcode}">&times;</span>
              `;
              row.addEventListener('click', (event) => {
                loadGcode(event.target.dataset.name);
              });
              row.title = 'Clicca per caricare il G-code';
              gcodeList.appendChild(row);
              fetch(`/gcode/get?name=${encodeURIComponent(gcode)}`)
                .then(response => response.text())
                .then(text => {
                  row.querySelector('.gcode-size').textContent = `${(text.length / 1024).toFixed(1)} KB`;
                })
            });
            document.querySelectorAll('.remove-icon').forEach(icon => {
              icon.title = 'Clicca per rimuovere il G-code';
              icon.addEventListener('click', (event) => {
                const name = event.target.getAttribute('data-name');
                removeGcode(name);
              });
            });
          } else {
            gcodeList.innerHTML = 'Nessun G-code salvato';
          }
          fetchFreeSpace();
        });
    }

    function loadGcode(name) {
      fetch(`/gcode/get?name=${encodeURIComponent(name)}`)
        .then(response => response.text())
        .then(data => {
          gcodeNameInput.value = name;
          gcodeContentInput.value = data;
          updateButtonStates();
        });
    }

    function removeGcode(name) {
      fetch('/gcode/remove', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: new URLSearchParams({ name })
      })
      .then(response => response.text())
      .then(data => {
        logMessage(data);
        listGcodes();
      });
    }

    function fetchFreeSpace() {
      fetch('/status')
        .then(response => response.text())
        .then(data => {
          const freeSpaceBytes = Number(data.split('\n').find(l => l.startsWith('LittleFS.freeSpace=')).substr('LittleFS.freeSpace='.length));
          if (freeSpaceBytes) {
            const freeSpaceElement = document.getElementById('free-space');
            freeSpaceElement.textContent = `Spazio libero: ${Math.floor(freeSpaceBytes / 1024)} KB`;
          }
        });
    }

    function logMessage(message) {
      const p = document.createElement('p');
      p.textContent = message;
      log.appendChild(p);
      log.scrollTop = log.scrollHeight;
    }

    listGcodes();
  </script>
</body>
</html>
)rawliteral";

#define FORMAT_LITTLEFS_IF_FAILED true

// For MEASURE_TPI, round TPI to the nearest integer if it's within this range of it.
// E.g. 80.02tpi would be shown as 80tpi but 80.04tpi would be shown as-is.
const float TPI_ROUND_EPSILON = 0.03;

float ENCODER_STEPS_FLOAT = ENCODER_STEPS_INT; // Convenience float version of ENCODER_STEPS_INT
long RPM_BULK = ENCODER_STEPS_INT; // Measure RPM averaged over this number of encoder pulses

const long GCODE_FEED_DEFAULT_DU_SEC = 20000; // Default feed in du/sec in GCode mode
const float GCODE_FEED_MIN_DU_SEC = 167; // Minimum feed in du/sec in GCode mode - F1

#define DHIGH(x) digitalWrite(x, HIGH)
#define DLOW(x) digitalWrite(x, LOW)

#define DELAY(x) vTaskDelay(x / portTICK_PERIOD_MS);

#define LCD_HASH_INITIAL -3845709 // Random number that's unlikely to naturally occur as an actual hash
long lcdHashLine0 = LCD_HASH_INITIAL;
long lcdHashLine1 = LCD_HASH_INITIAL;
long lcdHashLine2 = LCD_HASH_INITIAL;
long lcdHashLine3 = LCD_HASH_INITIAL;
bool splashScreen = false;

unsigned long keypadTimeUs = 0;

// Most buttons we only have "down" handling, holding them has no effect.
// Buttons with special "holding" logic have flags below.
bool buttonLeftPressed = false;
bool buttonRightPressed = false;
bool buttonUpPressed = false;
bool buttonDownPressed = false;
bool buttonOffPressed = false;
bool buttonBackPressed = false;
bool buttonForwardPressed = false;

volatile bool joystickRapidPressed = false;
volatile int joystickLatheDirectionZ = 0; // -1 carriage right, 0 neutral, 1 carriage left in joystick lathe mode.
volatile int joystickLatheDirectionX = 0; // -1 cross out, 0 neutral, 1 cross in in joystick lathe mode.
volatile bool joystickLatheRapid = false;
volatile int joystickPitchAdjustDirection = 0;
volatile int joystickPitchStatusDirection = 0;
volatile unsigned long joystickPitchStatusMillis = 0;
bool joystickAvailable = false;
portMUX_TYPE joystickPulseMux = portMUX_INITIALIZER_UNLOCKED;
float joystickPitchChangeFraction = 0;
unsigned long joystickSampleTimeUs = 0;
int joystickLatheFeedSignZ = 0;
int joystickLatheFeedSignX = 0;
long joystickLathePitchZ = 0;
long joystickLathePitchX = 0;
bool joystickLatheThreadLocked = false;
int joystickLatheSyncAxis = 0;
long joystickLatheSyncPitch = 0;
bool joystickLatheRebaseZAfterSync = false;
bool joystickLatheRebaseXAfterSync = false;
bool joystickButtonRawPressed = false;
bool joystickButtonPressed = false;
bool joystickButtonToggleBlocked = false;
unsigned long joystickButtonRawChangeMillis = 0;
unsigned long joystickButtonPressMillis = 0;
String joystickStartupWarning = "";

void adjustPitch(bool plus);
void buttonPlusMinusPress(bool plus);
void buttonOnOffPress(bool on);
void tftSetStatus(const String &message, unsigned long ms);
void resetJoystickLatheFeedPosition();
void cancelJoystickLatheSync();
void resetJoystickLatheFeed();
void updateAsyncTimerSettings();

bool inNumpad = false;
int numpadDigits[20];
int numpadIndex = 0;

bool isOn = false;
bool nextIsOn; // isOn value that should be applied asap
bool nextIsOnFlag; // whether nextIsOn requires attention
unsigned long resetMillis = 0;
int emergencyStop = 0;

bool beepFlag = false; // allows time-critical code to ask for a beep on another core

long dupr = 0; // pitch, tenth of a micron per rotation
long savedDupr = 0; // dupr saved in Preferences
long nextDupr = dupr; // dupr value that should be applied asap
bool nextDuprFlag = false; // whether nextDupr requires attention

SemaphoreHandle_t motionMutex; // controls blocks of code where variables affecting the motion loop() are changed

int starts = 1; // number of starts in a multi-start thread
int savedStarts = 0; // starts saved in Preferences
int nextStarts = starts; // number of starts that should be used asap
bool nextStartsFlag = false; // whether nextStarts requires attention

struct Axis {
  SemaphoreHandle_t mutex;

  char name;
  bool active;
  bool rotational;
  float motorSteps; // motor steps per revolution of the axis
  float screwPitch; // lead screw pitch in deci-microns (10^-7 of a meter)
  float pulsePerRevolution; // pulses per revolution of this axis handwheel

  long pos; // relative position of the tool in stepper motor steps
  long savedPos; // value saved in Preferences
  float fractionalPos; // fractional distance in steps that we meant to travel but couldn't
  long originPos; // relative position of the stepper motor to origin, in steps
  long savedOriginPos; // originPos saved in Preferences
  long posGlobal; // global position of the motor in steps
  long savedPosGlobal; // posGlobal saved in Preferences
  int pendingPos; // steps of the stepper motor that we should make as soon as possible
  long motorPos; // position of the motor in stepper motor steps, same as pos unless moving back, then differs by backlashSteps
  long savedMotorPos; // motorPos saved in Preferences
  bool continuous; // whether current movement is expected to continue until an unknown position

  long leftStop; // left stop value of pos
  long savedLeftStop; // value saved in Preferences
  long nextLeftStop; // left stop value that should be applied asap
  bool nextLeftStopFlag; // whether nextLeftStop requires attention

  long rightStop; // right stop value of pos
  long savedRightStop; // value saved in Preferences
  long nextRightStop; // right stop value that should be applied asap
  bool nextRightStopFlag; // whether nextRightStop requires attention

  long speed; // motor speed in steps / second
  long speedStart; // Initial speed of a motor, steps / second.
  long speedMax; // To limit max speed e.g. for manual moves
  long speedManualMove; // Maximum speed of a motor during manual move, steps / second.
  long acceleration; // Acceleration of a motor, steps / second ^ 2.
  long decelerateSteps; // Number of steps before the end position the deceleration should start.

  bool direction; // To reset speed when direction changes.
  bool directionInitialized;
  unsigned long stepStartUs;
  int stepperEnableCounter;
  bool disabled;
  bool savedDisabled;

  bool invertStepper; // change (true/false) if the carriage moves e.g. "left" when you press "right".
  bool invertEnable; // change (true/false) if the Enable pin is inverted
  bool needsRest; // set to false for closed-loop drivers, true for open-loop.
  bool movingManually; // whether stepper is being moved by left/right buttons
  long estopSteps; // amount of steps to exceed machine limits
  long backlashSteps; // amount of steps in reverse direction to re-engage the carriage
  long gcodeRelativePos; // absolute position in steps that relative GCode refers to

  int ena; // Enable pin of this motor
  int dir; // Direction pin of this motor
  int step; // Step pin of this motor

  int pulseA;
  int pulseB;
  int pulseCount;
  long pulsePos;
  long pulsePosAvg;
  PulseCounter pulseCounter;
};

void initAxis(Axis* a, char name, bool active, bool rotational, float motorSteps, float screwPitch, float pulsePerRevolution, long speedStart, long speedManualMove,
    long acceleration, bool invertStepper, bool invertEnable, bool needsRest, long maxTravelMm, long backlashDu, int ena, int dir, int step, int pulseA, int pulseB, PulseCounter pulseCounter) {
  a->mutex = xSemaphoreCreateMutex();

  a->name = name;
  a->active = active;
  a->rotational = rotational;
  a->motorSteps = motorSteps;
  a->screwPitch = screwPitch;
  a->pulsePerRevolution = pulsePerRevolution;

  a->pos = 0;
  a->savedPos = 0;
  a->fractionalPos = 0.0;
  a->originPos = 0;
  a->savedOriginPos = 0;
  a->posGlobal = 0;
  a->savedPosGlobal = 0;
  a->pendingPos = 0;
  a->motorPos = 0;
  a->savedMotorPos = 0;
  a->continuous = false;

  a->leftStop = 0;
  a->savedLeftStop = 0;
  a->nextLeftStopFlag = false;

  a->rightStop = 0;
  a->savedRightStop = 0;
  a->nextRightStopFlag = false;

  a->speed = speedStart;
  a->speedStart = speedStart;
  a->speedMax = LONG_MAX;
  a->speedManualMove = speedManualMove;
  a->acceleration = acceleration;
  a->decelerateSteps = 0;
  long s = speedManualMove;
  while (s > speedStart) {
    a->decelerateSteps++;
    s -= a->acceleration / float(s);
  }

  a->direction = true;
  a->directionInitialized = false;
  a->stepStartUs = 0;
  a->stepperEnableCounter = 0;
  a->disabled = false;
  a->savedDisabled = false;

  a->invertStepper = invertStepper;
  a->invertEnable = invertEnable;
  a->needsRest = needsRest;
  a->movingManually = false;
  a->estopSteps = maxTravelMm * 10000 / a->screwPitch * a->motorSteps;
  a->backlashSteps = backlashDu * a->motorSteps / a->screwPitch;
  a->gcodeRelativePos = 0;

  a->ena = ena;
  a->dir = dir;
  a->step = step;

  a->pulseA = pulseA;
  a->pulseB = pulseB;
  a->pulseCounter = pulseCounter;
  a->pulseCount = 0;
  a->pulsePos = 0;
  a->pulsePosAvg = 0;
}

Axis z;
Axis x;
Axis y;

struct JoystickAxisState {
  Axis* axis;
  int pin;
  bool* enabled;
  bool* invert;
  volatile int manualDirection;
  volatile long manualSpeed;
  volatile int queuedPulses;
  int center;
  int filtered;
  float pulseFraction;
  float deflection;
  int direction;
};

enum JoystickAxisIndex {
  JOYSTICK_AXIS_Z = 0,
  JOYSTICK_AXIS_X = 1,
  JOYSTICK_AXIS_Y = 2,
};

JoystickAxisState joystickAxes[] = {
  {&z, JOY_Z, &JOYSTICK_Z_ENABLED, &INVERT_JOYSTICK_Z, 0, 0, 0, 2048, 2048, 0, 0, 0},
  {&x, JOY_X, &JOYSTICK_X_ENABLED, &INVERT_JOYSTICK_X, 0, 0, 0, 2048, 2048, 0, 0, 0},
  {&y, JOY_Y, &JOYSTICK_Y_ENABLED, &INVERT_JOYSTICK_Y, 0, 0, 0, 2048, 2048, 0, 0, 0},
};
const int JOYSTICK_AXIS_COUNT = sizeof(joystickAxes) / sizeof(joystickAxes[0]);

bool joystickAxisEnabled(JoystickAxisState* joystickAxis) {
  return joystickAxis->enabled == nullptr || *joystickAxis->enabled;
}

bool anyJoystickAxisEnabled() {
  for (int i = 0; i < JOYSTICK_AXIS_COUNT; i++) {
    if (joystickAxisEnabled(&joystickAxes[i])) return true;
  }
  return false;
}

pcnt_unit_handle_t pulseUnits[PULSE_COUNTER_COUNT] = {};
volatile bool pulseCountersReady = false;

unsigned long saveTime = 0; // micros() of the previous Prefs write
unsigned long spindleEncTime = 0; // micros() of the previous spindle update
unsigned long spindleEncTimeDiffBulk = 0; // micros() between RPM_BULK spindle updates
unsigned long spindleEncTimeAtIndex0 = 0; // micros() when spindleEncTimeIndex was 0
int spindleEncTimeIndex = 0; // counter going between 0 and RPM_BULK - 1
long spindlePos = 0; // Spindle position
long spindlePosAvg = 0; // Spindle position accounting for encoder backlash
long savedSpindlePosAvg = 0; // spindlePosAvg saved in Preferences
long savedSpindlePos = 0; // spindlePos value saved in Preferences
int spindleCount = 0; // Last processed spindle encoder pulse counter value.
int spindlePosSync = 0; // Non-zero while waiting for spindle phase before resuming synchronized motion.
int savedSpindlePosSync = 0; // spindlePosSync saved in Preferences
long spindlePosGlobal = 0; // global spindle position that is unaffected by e.g. zeroing
long savedSpindlePosGlobal = 0; // spindlePosGlobal saved in Preferences

bool showAngle = false; // Whether to show 0-359 spindle angle on screen
bool showTacho = false; // Whether to show spindle RPM on screen
bool savedShowAngle = false; // showAngle value saved in Preferences
bool savedShowTacho = false; // showTacho value saved in Preferences
int shownRpm = 0;
unsigned long shownRpmTime = 0; // micros() when shownRpm was set

long moveStep = 0; // in deci-microns
long savedMoveStep = 0; // moveStep saved in Preferences

volatile int mode = -1; // mode of operation (ELS, multi-start ELS, asynchronous)
int nextMode = 0; // mode value that should be applied asap
bool nextModeFlag = false; // whether nextMode needs attention
int savedMode = -1; // mode saved in Preferences

int measure = MEASURE_METRIC; // Whether to show distances in inches
int savedMeasure = MEASURE_METRIC; // measure value saved in Preferences

float coneRatio = 0; // 0 = cylindrical; the cone comes from the measurements
float savedConeRatio = 0; // value of coneRatio saved in Preferences
float nextConeRatio = 0; // coneRatio that should be applied asap
bool nextConeRatioFlag = false; // whether nextConeRatio requires attention

void recomputeConeRatio();
String coneRatioText();

int turnPasses = 3; // In turn mode, how many turn passes to make
int savedTurnPasses = 0; // value of turnPasses saved in Preferences

long setupIndex = 0; // Index of automation setup step
bool auxForward = true; // True for external, false for internal thread
bool savedAuxForward = false; // value of auxForward saved in Preferences

long opIndex = 0; // Index of an automation operation
bool opIndexAdvanceFlag = false; // Whether user requested to move to the next pass
long opSubIndex = 0; // Sub-index of an automation operation
int opDuprSign = 1; // 1 if dupr was positive when operation started, -1 if negative
long opDupr = 0; // dupr that the multi-pass operation started with

String gcodeCommand = "";
long gcodeFeedDuPerSec = GCODE_FEED_DEFAULT_DU_SEC;
bool gcodeInitialized = false;
bool gcodeAbsolutePositioning = true;
bool gcodeInBrace = false;
bool gcodeInSemicolon = false;
bool wsInKeycode = false;
int wsKeycode = 0;
String keycodeCommand = "";
bool gcodeInSave = false;
bool gcodeInSaveFirstLine = false;
String gcodeSaveName = "";
String gcodeSaveValue = "";
int gcodeProgramIndex = 0;
int gcodeProgramCount = 0;
String gcodeProgram = "";
int gcodeProgramCharIndex = 0;

PS2KeyAdvanced keyboard;

hw_timer_t *async_timer = timerBegin(TIMER_FREQ);
bool timerAttached = false;

CircleBuffer inBuffer;
CircleBuffer outBuffer;
volatile bool webBuffersReady = false;
QueueHandle_t webUiEventQueue = NULL;
volatile int webUiEventPendingCount = 0;
portMUX_TYPE webUiEventMux = portMUX_INITIALIZER_UNLOCKED;
const int WEB_UI_EVENT_QUEUE_LENGTH = 32;
const unsigned long WEB_UI_MOVE_TIMEOUT_MS = 750;
volatile byte webUiHeldMoveAction = 0;
volatile unsigned long webUiHeldMoveMillis = 0;
volatile bool webUiMoveReleaseRequested = false;

bool bufferAvailable(CircleBuffer* b) {
  return b->head != b->tail;
}

bool writeBuffer(CircleBuffer* b, char c) {
  if ((b->head + 1) % b->size == b->tail) {
    return false;
  }
  b->buffer[b->head] = c;
  b->head = (b->head + 1) % b->size;
  return true;
}

bool writeBuffer(CircleBuffer* b, const char* str) {
  while (*str) {
    if (!writeBuffer(b, *str++)) {
      return false;
    }
  }
  return true;
}

bool writeBuffer(CircleBuffer* b, const String& str) {
  return writeBuffer(b, str.c_str());
}

bool writeBuffer(CircleBuffer* b, float f, int precision) {
  char buffer[16];
  dtostrf(f, 0, precision, buffer);
  return writeBuffer(b, buffer);
}

char shiftBuffer(CircleBuffer* b) {
  if (b->head == b->tail) {
    return 0;
  }
  char c = b->buffer[b->tail];
  b->tail = (b->tail + 1) % b->size;
  return c;
}

void initBuffer(CircleBuffer* b, size_t size) {
  b->size = size;
  b->buffer = (char*)malloc(size);
  b->head = 0;
  b->tail = 0;
}

void clearBuffer(CircleBuffer* b) {
  b->head = 0;
  b->tail = 0;
}

WebServer server(80);
WebSocketsServer webSocket(81);
volatile int webSocketClientCount = 0;
volatile bool machineStatusForcePublish = false;
String lastMachineStatus = "";
String wifiStatus = "Senza WiFi";
unsigned long wifiStatusMillis = 0;
bool wifiSetupApActive = false;
bool wifiStationConnected = false;
String wifiIpAddress = "";
volatile bool tftUploadActive = false;
bool tftUploadFailed = false;
int tftUploadHttpStatus = 200;
String tftUploadMessage = "";
long tftUploadExpectedSize = 0;
long tftUploadReceivedSize = 0;
long tftUploadSentSize = 0;
int tftUploadPacketLength = 0;
int tftUploadProgressPercent = 0;
long nextionSerialBaud = NEXTION_NORMAL_BAUD;
byte tftUploadPacket[NEXTION_TFT_PACKET_SIZE];
const int NEXTION_BUFFER_LENGTH = 256;
byte nextionBuffer[NEXTION_BUFFER_LENGTH];
int nextionBufferIndex = 0;
byte lastNextionPageId = 255;
// Diagnostics for the display link, exposed by /status.
byte tftDiagPage = 255;
byte tftDiagCode = 0;
uint32_t tftDiagEvents = 0;
uint32_t tftDiagReboots = 0;
volatile bool firmwareUploadActive = false;
bool firmwareUploadFailed = false;
int firmwareUploadHttpStatus = 200;
String firmwareUploadMessage = "";
size_t firmwareUploadExpectedSize = 0;
size_t firmwareUploadReceivedSize = 0;
int firmwareUploadProgressPercent = 0;
bool firmwareUploadRestartPending = false;
unsigned long firmwareUploadRestartAt = 0;
bool configRestartPending = false;
unsigned long configRestartAt = 0;
bool keyboardCaptureActive = false;
byte keyboardCaptureReleaseCode = 0;
unsigned long keyboardCaptureUntil = 0;

long clampLongValue(long value, long minValue, long maxValue) {
  if (value < minValue) return minValue;
  if (value > maxValue) return maxValue;
  return value;
}

int clampIntValue(int value, int minValue, int maxValue) {
  if (value < minValue) return minValue;
  if (value > maxValue) return maxValue;
  return value;
}

float clampFloatValue(float value, float minValue, float maxValue) {
  if (value < minValue) return minValue;
  if (value > maxValue) return maxValue;
  return value;
}

void setMachineConfigDefaults() {
  ENCODER_PPR = DEFAULT_ENCODER_PPR;
  ENCODER_BACKLASH = DEFAULT_ENCODER_BACKLASH;
  AXIS_ENCODER_BACKLASH = DEFAULT_AXIS_ENCODER_BACKLASH;
  SCREW_Z_DU = DEFAULT_SCREW_Z_DU;
  MOTOR_STEPS_Z = DEFAULT_MOTOR_STEPS_Z;
  SPEED_START_Z = DEFAULT_SPEED_START_Z;
  ACCELERATION_Z = DEFAULT_ACCELERATION_Z;
  SPEED_MANUAL_MOVE_Z = DEFAULT_SPEED_MANUAL_MOVE_Z;
  INVERT_Z = DEFAULT_INVERT_Z;
  INVERT_Z_ENABLE = DEFAULT_INVERT_Z_ENABLE;
  NEEDS_REST_Z = DEFAULT_NEEDS_REST_Z;
  MAX_TRAVEL_MM_Z = DEFAULT_MAX_TRAVEL_MM_Z;
  BACKLASH_DU_Z = DEFAULT_BACKLASH_DU_Z;
  SCREW_X_DU = DEFAULT_SCREW_X_DU;
  MOTOR_STEPS_X = DEFAULT_MOTOR_STEPS_X;
  SPEED_START_X = DEFAULT_SPEED_START_X;
  ACCELERATION_X = DEFAULT_ACCELERATION_X;
  SPEED_MANUAL_MOVE_X = DEFAULT_SPEED_MANUAL_MOVE_X;
  INVERT_X = DEFAULT_INVERT_X;
  INVERT_X_ENABLE = DEFAULT_INVERT_X_ENABLE;
  NEEDS_REST_X = DEFAULT_NEEDS_REST_X;
  MAX_TRAVEL_MM_X = DEFAULT_MAX_TRAVEL_MM_X;
  BACKLASH_DU_X = DEFAULT_BACKLASH_DU_X;
  STEP_TIME_MS = DEFAULT_STEP_TIME_MS;
  DELAY_BETWEEN_STEPS_MS = DEFAULT_DELAY_BETWEEN_STEPS_MS;
  ENABLE_CONTINUOUS_MOVE = DEFAULT_ENABLE_CONTINUOUS_MOVE;
  SAFE_DISTANCE_DU = DEFAULT_SAFE_DISTANCE_DU;
  SLOT_LEFT_REDUCTION_DU = DEFAULT_SLOT_LEFT_REDUCTION_DU;
  CONE_DIA_BIG_DU = DEFAULT_CONE_DIA_BIG_DU;
  CONE_DIA_SMALL_DU = DEFAULT_CONE_DIA_SMALL_DU;
  ACTIVE_Y = DEFAULT_ACTIVE_Y;
  ROTARY_Y = DEFAULT_ROTARY_Y;
  MOTOR_STEPS_Y = DEFAULT_MOTOR_STEPS_Y;
  SCREW_Y_DU = DEFAULT_SCREW_Y_DU;
  SPEED_START_Y = DEFAULT_SPEED_START_Y;
  ACCELERATION_Y = DEFAULT_ACCELERATION_Y;
  SPEED_MANUAL_MOVE_Y = DEFAULT_SPEED_MANUAL_MOVE_Y;
  INVERT_Y = DEFAULT_INVERT_Y;
  INVERT_Y_ENABLE = DEFAULT_INVERT_Y_ENABLE;
  NEEDS_REST_Y = DEFAULT_NEEDS_REST_Y;
  MAX_TRAVEL_MM_Y = DEFAULT_MAX_TRAVEL_MM_Y;
  BACKLASH_DU_Y = DEFAULT_BACKLASH_DU_Y;
  PULSE_PER_REVOLUTION_Z = DEFAULT_PULSE_PER_REVOLUTION_Z;
  PULSE_PER_REVOLUTION_X = DEFAULT_PULSE_PER_REVOLUTION_X;
  PULSE_PER_REVOLUTION_Y = DEFAULT_PULSE_PER_REVOLUTION_Y;
  JOYSTICK_ENABLED = DEFAULT_JOYSTICK_ENABLED;
  JOYSTICK_Z_ENABLED = DEFAULT_JOYSTICK_Z_ENABLED;
  JOYSTICK_X_ENABLED = DEFAULT_JOYSTICK_X_ENABLED;
  JOYSTICK_Y_ENABLED = DEFAULT_JOYSTICK_Y_ENABLED;
  JOYSTICK_BUTTON_TOGGLES_ON_OFF = DEFAULT_JOYSTICK_BUTTON_TOGGLES_ON_OFF;
  JOYSTICK_CENTER_SAMPLES = DEFAULT_JOYSTICK_CENTER_SAMPLES;
  JOYSTICK_OVERSAMPLES = DEFAULT_JOYSTICK_OVERSAMPLES;
  JOYSTICK_SAMPLE_INTERVAL_MS = DEFAULT_JOYSTICK_SAMPLE_INTERVAL_MS;
  JOYSTICK_ADC_MAX = DEFAULT_JOYSTICK_ADC_MAX;
  JOYSTICK_DEADBAND = DEFAULT_JOYSTICK_DEADBAND;
  JOYSTICK_PULSE_QUEUE_LIMIT = DEFAULT_JOYSTICK_PULSE_QUEUE_LIMIT;
  JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND = DEFAULT_JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND;
  JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND = DEFAULT_JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND;
  INVERT_JOYSTICK_Z = DEFAULT_INVERT_JOYSTICK_Z;
  INVERT_JOYSTICK_X = DEFAULT_INVERT_JOYSTICK_X;
  INVERT_JOYSTICK_Y = DEFAULT_INVERT_JOYSTICK_Y;
  INVERT_JOYSTICK_BUTTON = DEFAULT_INVERT_JOYSTICK_BUTTON;
}

void applyDerivedMachineConfig() {
  ENCODER_STEPS_INT = ENCODER_PPR * 2;
  ENCODER_STEPS_FLOAT = ENCODER_STEPS_INT;
  RPM_BULK = ENCODER_STEPS_INT;
  if (spindleEncTimeIndex >= RPM_BULK) spindleEncTimeIndex = 0;
}

void normalizeMachineConfig() {
  ENCODER_PPR = clampIntValue(ENCODER_PPR, 1, 15000);
  ENCODER_BACKLASH = clampIntValue(ENCODER_BACKLASH, 0, 30000);
  AXIS_ENCODER_BACKLASH = clampIntValue(AXIS_ENCODER_BACKLASH, 0, 30000);
  SCREW_Z_DU = clampLongValue(SCREW_Z_DU, 1, 10000000);
  MOTOR_STEPS_Z = clampLongValue(MOTOR_STEPS_Z, 1, 1000000);
  SPEED_START_Z = clampLongValue(SPEED_START_Z, 1, 1000000);
  ACCELERATION_Z = clampLongValue(ACCELERATION_Z, 1, 100000000);
  SPEED_MANUAL_MOVE_Z = clampLongValue(SPEED_MANUAL_MOVE_Z, 1, 1000000);
  MAX_TRAVEL_MM_Z = clampLongValue(MAX_TRAVEL_MM_Z, 1, 10000);
  BACKLASH_DU_Z = clampLongValue(BACKLASH_DU_Z, 0, 10000000);
  SCREW_X_DU = clampLongValue(SCREW_X_DU, 1, 10000000);
  MOTOR_STEPS_X = clampLongValue(MOTOR_STEPS_X, 1, 1000000);
  SPEED_START_X = clampLongValue(SPEED_START_X, 1, 1000000);
  ACCELERATION_X = clampLongValue(ACCELERATION_X, 1, 100000000);
  SPEED_MANUAL_MOVE_X = clampLongValue(SPEED_MANUAL_MOVE_X, 1, 1000000);
  MAX_TRAVEL_MM_X = clampLongValue(MAX_TRAVEL_MM_X, 1, 10000);
  BACKLASH_DU_X = clampLongValue(BACKLASH_DU_X, 0, 10000000);
  STEP_TIME_MS = clampLongValue(STEP_TIME_MS, 1, 10000);
  DELAY_BETWEEN_STEPS_MS = clampLongValue(DELAY_BETWEEN_STEPS_MS, 0, 10000);
  SAFE_DISTANCE_DU = clampLongValue(SAFE_DISTANCE_DU, 0, 10000000);
  MOTOR_STEPS_Y = clampLongValue(MOTOR_STEPS_Y, 1, 1000000);
  SCREW_Y_DU = clampLongValue(SCREW_Y_DU, 1, 10000000);
  SPEED_START_Y = clampLongValue(SPEED_START_Y, 1, 1000000);
  ACCELERATION_Y = clampLongValue(ACCELERATION_Y, 1, 100000000);
  SPEED_MANUAL_MOVE_Y = clampLongValue(SPEED_MANUAL_MOVE_Y, 1, 1000000);
  MAX_TRAVEL_MM_Y = clampLongValue(MAX_TRAVEL_MM_Y, 1, 10000);
  BACKLASH_DU_Y = clampLongValue(BACKLASH_DU_Y, 0, 10000000);
  PULSE_PER_REVOLUTION_Z = clampFloatValue(PULSE_PER_REVOLUTION_Z, 1.0, 100000.0);
  PULSE_PER_REVOLUTION_X = clampFloatValue(PULSE_PER_REVOLUTION_X, 1.0, 100000.0);
  PULSE_PER_REVOLUTION_Y = clampFloatValue(PULSE_PER_REVOLUTION_Y, 1.0, 100000.0);
  JOYSTICK_CENTER_SAMPLES = clampIntValue(JOYSTICK_CENTER_SAMPLES, 1, 1024);
  JOYSTICK_OVERSAMPLES = clampIntValue(JOYSTICK_OVERSAMPLES, 1, 1024);
  JOYSTICK_SAMPLE_INTERVAL_MS = clampIntValue(JOYSTICK_SAMPLE_INTERVAL_MS, 1, 1000);
  JOYSTICK_ADC_MAX = clampIntValue(JOYSTICK_ADC_MAX, 1, 65535);
  JOYSTICK_DEADBAND = clampIntValue(JOYSTICK_DEADBAND, 0, JOYSTICK_ADC_MAX - 1);
  JOYSTICK_PULSE_QUEUE_LIMIT = clampIntValue(JOYSTICK_PULSE_QUEUE_LIMIT, 1, 1000000);
  JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND = clampFloatValue(JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND, 0.01, 1000.0);
  JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND = clampFloatValue(JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND, 0.01, 1000.0);
  SLOT_LEFT_REDUCTION_DU = clampLongValue(SLOT_LEFT_REDUCTION_DU, 0, 10000000);
  CONE_DIA_BIG_DU = clampLongValue(CONE_DIA_BIG_DU, 1000, 9999900);
  CONE_DIA_SMALL_DU = clampLongValue(CONE_DIA_SMALL_DU, 0, 9999900);
  if (SPEED_START_Z > SPEED_MANUAL_MOVE_Z) SPEED_START_Z = SPEED_MANUAL_MOVE_Z;
  if (SPEED_START_X > SPEED_MANUAL_MOVE_X) SPEED_START_X = SPEED_MANUAL_MOVE_X;
  if (SPEED_START_Y > SPEED_MANUAL_MOVE_Y) SPEED_START_Y = SPEED_MANUAL_MOVE_Y;
  applyDerivedMachineConfig();
}

void loadMachineConfig() {
  setMachineConfigDefaults();
  Preferences cfg;
  cfg.begin(CONFIG_NAMESPACE);
  if (cfg.getInt(CFG_VERSION) != CONFIG_VERSION) {
    cfg.clear();
    cfg.putInt(CFG_VERSION, CONFIG_VERSION);
  }
  ENCODER_PPR = cfg.getInt(CFG_ENCODER_PPR, ENCODER_PPR);
  ENCODER_BACKLASH = cfg.getInt(CFG_ENCODER_BACKLASH, ENCODER_BACKLASH);
  AXIS_ENCODER_BACKLASH = cfg.getInt(CFG_AXIS_ENCODER_BACKLASH, AXIS_ENCODER_BACKLASH);
  SCREW_Z_DU = cfg.getLong(CFG_SCREW_Z_DU, SCREW_Z_DU);
  MOTOR_STEPS_Z = cfg.getLong(CFG_MOTOR_STEPS_Z, MOTOR_STEPS_Z);
  SPEED_START_Z = cfg.getLong(CFG_SPEED_START_Z, SPEED_START_Z);
  ACCELERATION_Z = cfg.getLong(CFG_ACCELERATION_Z, ACCELERATION_Z);
  SPEED_MANUAL_MOVE_Z = cfg.getLong(CFG_SPEED_MANUAL_MOVE_Z, SPEED_MANUAL_MOVE_Z);
  INVERT_Z = cfg.getBool(CFG_INVERT_Z, INVERT_Z);
  INVERT_Z_ENABLE = cfg.getBool(CFG_INVERT_Z_ENABLE, INVERT_Z_ENABLE);
  NEEDS_REST_Z = cfg.getBool(CFG_NEEDS_REST_Z, NEEDS_REST_Z);
  MAX_TRAVEL_MM_Z = cfg.getLong(CFG_MAX_TRAVEL_MM_Z, MAX_TRAVEL_MM_Z);
  BACKLASH_DU_Z = cfg.getLong(CFG_BACKLASH_DU_Z, BACKLASH_DU_Z);
  SCREW_X_DU = cfg.getLong(CFG_SCREW_X_DU, SCREW_X_DU);
  MOTOR_STEPS_X = cfg.getLong(CFG_MOTOR_STEPS_X, MOTOR_STEPS_X);
  SPEED_START_X = cfg.getLong(CFG_SPEED_START_X, SPEED_START_X);
  ACCELERATION_X = cfg.getLong(CFG_ACCELERATION_X, ACCELERATION_X);
  SPEED_MANUAL_MOVE_X = cfg.getLong(CFG_SPEED_MANUAL_MOVE_X, SPEED_MANUAL_MOVE_X);
  INVERT_X = cfg.getBool(CFG_INVERT_X, INVERT_X);
  INVERT_X_ENABLE = cfg.getBool(CFG_INVERT_X_ENABLE, INVERT_X_ENABLE);
  NEEDS_REST_X = cfg.getBool(CFG_NEEDS_REST_X, NEEDS_REST_X);
  MAX_TRAVEL_MM_X = cfg.getLong(CFG_MAX_TRAVEL_MM_X, MAX_TRAVEL_MM_X);
  BACKLASH_DU_X = cfg.getLong(CFG_BACKLASH_DU_X, BACKLASH_DU_X);
  STEP_TIME_MS = cfg.getLong(CFG_STEP_TIME_MS, STEP_TIME_MS);
  DELAY_BETWEEN_STEPS_MS = cfg.getLong(CFG_DELAY_BETWEEN_STEPS_MS, DELAY_BETWEEN_STEPS_MS);
  ENABLE_CONTINUOUS_MOVE = cfg.getBool(CFG_ENABLE_CONTINUOUS_MOVE, ENABLE_CONTINUOUS_MOVE);
  SAFE_DISTANCE_DU = cfg.getLong(CFG_SAFE_DISTANCE_DU, SAFE_DISTANCE_DU);
  SLOT_LEFT_REDUCTION_DU = cfg.getLong(CFG_SLOT_LEFT_REDUCTION_DU, SLOT_LEFT_REDUCTION_DU);
  CONE_DIA_BIG_DU = cfg.getLong(CFG_CONE_DIA_BIG_DU, CONE_DIA_BIG_DU);
  CONE_DIA_SMALL_DU = cfg.getLong(CFG_CONE_DIA_SMALL_DU, CONE_DIA_SMALL_DU);
  ACTIVE_Y = cfg.getBool(CFG_ACTIVE_Y, ACTIVE_Y);
  ROTARY_Y = cfg.getBool(CFG_ROTARY_Y, ROTARY_Y);
  MOTOR_STEPS_Y = cfg.getLong(CFG_MOTOR_STEPS_Y, MOTOR_STEPS_Y);
  SCREW_Y_DU = cfg.getLong(CFG_SCREW_Y_DU, SCREW_Y_DU);
  SPEED_START_Y = cfg.getLong(CFG_SPEED_START_Y, SPEED_START_Y);
  ACCELERATION_Y = cfg.getLong(CFG_ACCELERATION_Y, ACCELERATION_Y);
  SPEED_MANUAL_MOVE_Y = cfg.getLong(CFG_SPEED_MANUAL_MOVE_Y, SPEED_MANUAL_MOVE_Y);
  INVERT_Y = cfg.getBool(CFG_INVERT_Y, INVERT_Y);
  INVERT_Y_ENABLE = cfg.getBool(CFG_INVERT_Y_ENABLE, INVERT_Y_ENABLE);
  NEEDS_REST_Y = cfg.getBool(CFG_NEEDS_REST_Y, NEEDS_REST_Y);
  MAX_TRAVEL_MM_Y = cfg.getLong(CFG_MAX_TRAVEL_MM_Y, MAX_TRAVEL_MM_Y);
  BACKLASH_DU_Y = cfg.getLong(CFG_BACKLASH_DU_Y, BACKLASH_DU_Y);
  float legacyPulsePerRevolution = cfg.getFloat(CFG_PULSE_PER_REVOLUTION, -1.0);
  PULSE_PER_REVOLUTION_Z = cfg.getFloat(CFG_PULSE_PER_REVOLUTION_Z, legacyPulsePerRevolution >= 1.0 ? legacyPulsePerRevolution : PULSE_PER_REVOLUTION_Z);
  PULSE_PER_REVOLUTION_X = cfg.getFloat(CFG_PULSE_PER_REVOLUTION_X, legacyPulsePerRevolution >= 1.0 ? legacyPulsePerRevolution : PULSE_PER_REVOLUTION_X);
  PULSE_PER_REVOLUTION_Y = cfg.getFloat(CFG_PULSE_PER_REVOLUTION_Y, legacyPulsePerRevolution >= 1.0 ? legacyPulsePerRevolution : PULSE_PER_REVOLUTION_Y);
  JOYSTICK_ENABLED = cfg.getBool(CFG_JOYSTICK_ENABLED, JOYSTICK_ENABLED);
  JOYSTICK_Z_ENABLED = cfg.getBool(CFG_JOYSTICK_Z_ENABLED, JOYSTICK_Z_ENABLED);
  JOYSTICK_X_ENABLED = cfg.getBool(CFG_JOYSTICK_X_ENABLED, JOYSTICK_X_ENABLED);
  JOYSTICK_Y_ENABLED = cfg.getBool(CFG_JOYSTICK_Y_ENABLED, JOYSTICK_Y_ENABLED);
  JOYSTICK_BUTTON_TOGGLES_ON_OFF = cfg.getBool(CFG_JOYSTICK_BUTTON_TOGGLES_ON_OFF, JOYSTICK_BUTTON_TOGGLES_ON_OFF);
  JOYSTICK_CENTER_SAMPLES = cfg.getInt(CFG_JOYSTICK_CENTER_SAMPLES, JOYSTICK_CENTER_SAMPLES);
  JOYSTICK_OVERSAMPLES = cfg.getInt(CFG_JOYSTICK_OVERSAMPLES, JOYSTICK_OVERSAMPLES);
  JOYSTICK_SAMPLE_INTERVAL_MS = cfg.getInt(CFG_JOYSTICK_SAMPLE_INTERVAL_MS, JOYSTICK_SAMPLE_INTERVAL_MS);
  JOYSTICK_ADC_MAX = cfg.getInt(CFG_JOYSTICK_ADC_MAX, JOYSTICK_ADC_MAX);
  JOYSTICK_DEADBAND = cfg.getInt(CFG_JOYSTICK_DEADBAND, JOYSTICK_DEADBAND);
  JOYSTICK_PULSE_QUEUE_LIMIT = cfg.getInt(CFG_JOYSTICK_PULSE_QUEUE_LIMIT, JOYSTICK_PULSE_QUEUE_LIMIT);
  JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND = cfg.getFloat(CFG_JOYSTICK_NORMAL_RPS, JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND);
  JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND = cfg.getFloat(CFG_JOYSTICK_RAPID_RPS, JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND);
  INVERT_JOYSTICK_Z = cfg.getBool(CFG_INVERT_JOYSTICK_Z, INVERT_JOYSTICK_Z);
  INVERT_JOYSTICK_X = cfg.getBool(CFG_INVERT_JOYSTICK_X, INVERT_JOYSTICK_X);
  INVERT_JOYSTICK_Y = cfg.getBool(CFG_INVERT_JOYSTICK_Y, INVERT_JOYSTICK_Y);
  INVERT_JOYSTICK_BUTTON = cfg.getBool(CFG_INVERT_JOYSTICK_BUTTON, INVERT_JOYSTICK_BUTTON);
  cfg.end();
  normalizeMachineConfig();
}

void saveMachineConfig() {
  normalizeMachineConfig();
  Preferences cfg;
  cfg.begin(CONFIG_NAMESPACE);
  cfg.putInt(CFG_VERSION, CONFIG_VERSION);
  cfg.putInt(CFG_ENCODER_PPR, ENCODER_PPR);
  cfg.putInt(CFG_ENCODER_BACKLASH, ENCODER_BACKLASH);
  cfg.putInt(CFG_AXIS_ENCODER_BACKLASH, AXIS_ENCODER_BACKLASH);
  cfg.putLong(CFG_SCREW_Z_DU, SCREW_Z_DU);
  cfg.putLong(CFG_MOTOR_STEPS_Z, MOTOR_STEPS_Z);
  cfg.putLong(CFG_SPEED_START_Z, SPEED_START_Z);
  cfg.putLong(CFG_ACCELERATION_Z, ACCELERATION_Z);
  cfg.putLong(CFG_SPEED_MANUAL_MOVE_Z, SPEED_MANUAL_MOVE_Z);
  cfg.putBool(CFG_INVERT_Z, INVERT_Z);
  cfg.putBool(CFG_INVERT_Z_ENABLE, INVERT_Z_ENABLE);
  cfg.putBool(CFG_NEEDS_REST_Z, NEEDS_REST_Z);
  cfg.putLong(CFG_MAX_TRAVEL_MM_Z, MAX_TRAVEL_MM_Z);
  cfg.putLong(CFG_BACKLASH_DU_Z, BACKLASH_DU_Z);
  cfg.putLong(CFG_SCREW_X_DU, SCREW_X_DU);
  cfg.putLong(CFG_MOTOR_STEPS_X, MOTOR_STEPS_X);
  cfg.putLong(CFG_SPEED_START_X, SPEED_START_X);
  cfg.putLong(CFG_ACCELERATION_X, ACCELERATION_X);
  cfg.putLong(CFG_SPEED_MANUAL_MOVE_X, SPEED_MANUAL_MOVE_X);
  cfg.putBool(CFG_INVERT_X, INVERT_X);
  cfg.putBool(CFG_INVERT_X_ENABLE, INVERT_X_ENABLE);
  cfg.putBool(CFG_NEEDS_REST_X, NEEDS_REST_X);
  cfg.putLong(CFG_MAX_TRAVEL_MM_X, MAX_TRAVEL_MM_X);
  cfg.putLong(CFG_BACKLASH_DU_X, BACKLASH_DU_X);
  cfg.putLong(CFG_STEP_TIME_MS, STEP_TIME_MS);
  cfg.putLong(CFG_DELAY_BETWEEN_STEPS_MS, DELAY_BETWEEN_STEPS_MS);
  cfg.putBool(CFG_ENABLE_CONTINUOUS_MOVE, ENABLE_CONTINUOUS_MOVE);
  cfg.putLong(CFG_SAFE_DISTANCE_DU, SAFE_DISTANCE_DU);
  cfg.putLong(CFG_SLOT_LEFT_REDUCTION_DU, SLOT_LEFT_REDUCTION_DU);
  cfg.putLong(CFG_CONE_DIA_BIG_DU, CONE_DIA_BIG_DU);
  cfg.putLong(CFG_CONE_DIA_SMALL_DU, CONE_DIA_SMALL_DU);
  cfg.putBool(CFG_ACTIVE_Y, ACTIVE_Y);
  cfg.putBool(CFG_ROTARY_Y, ROTARY_Y);
  cfg.putLong(CFG_MOTOR_STEPS_Y, MOTOR_STEPS_Y);
  cfg.putLong(CFG_SCREW_Y_DU, SCREW_Y_DU);
  cfg.putLong(CFG_SPEED_START_Y, SPEED_START_Y);
  cfg.putLong(CFG_ACCELERATION_Y, ACCELERATION_Y);
  cfg.putLong(CFG_SPEED_MANUAL_MOVE_Y, SPEED_MANUAL_MOVE_Y);
  cfg.putBool(CFG_INVERT_Y, INVERT_Y);
  cfg.putBool(CFG_INVERT_Y_ENABLE, INVERT_Y_ENABLE);
  cfg.putBool(CFG_NEEDS_REST_Y, NEEDS_REST_Y);
  cfg.putLong(CFG_MAX_TRAVEL_MM_Y, MAX_TRAVEL_MM_Y);
  cfg.putLong(CFG_BACKLASH_DU_Y, BACKLASH_DU_Y);
  cfg.putFloat(CFG_PULSE_PER_REVOLUTION_Z, PULSE_PER_REVOLUTION_Z);
  cfg.putFloat(CFG_PULSE_PER_REVOLUTION_X, PULSE_PER_REVOLUTION_X);
  cfg.putFloat(CFG_PULSE_PER_REVOLUTION_Y, PULSE_PER_REVOLUTION_Y);
  cfg.putBool(CFG_JOYSTICK_ENABLED, JOYSTICK_ENABLED);
  cfg.putBool(CFG_JOYSTICK_Z_ENABLED, JOYSTICK_Z_ENABLED);
  cfg.putBool(CFG_JOYSTICK_X_ENABLED, JOYSTICK_X_ENABLED);
  cfg.putBool(CFG_JOYSTICK_Y_ENABLED, JOYSTICK_Y_ENABLED);
  cfg.putBool(CFG_JOYSTICK_BUTTON_TOGGLES_ON_OFF, JOYSTICK_BUTTON_TOGGLES_ON_OFF);
  cfg.putInt(CFG_JOYSTICK_CENTER_SAMPLES, JOYSTICK_CENTER_SAMPLES);
  cfg.putInt(CFG_JOYSTICK_OVERSAMPLES, JOYSTICK_OVERSAMPLES);
  cfg.putInt(CFG_JOYSTICK_SAMPLE_INTERVAL_MS, JOYSTICK_SAMPLE_INTERVAL_MS);
  cfg.putInt(CFG_JOYSTICK_ADC_MAX, JOYSTICK_ADC_MAX);
  cfg.putInt(CFG_JOYSTICK_DEADBAND, JOYSTICK_DEADBAND);
  cfg.putInt(CFG_JOYSTICK_PULSE_QUEUE_LIMIT, JOYSTICK_PULSE_QUEUE_LIMIT);
  cfg.putFloat(CFG_JOYSTICK_NORMAL_RPS, JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND);
  cfg.putFloat(CFG_JOYSTICK_RAPID_RPS, JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND);
  cfg.putBool(CFG_INVERT_JOYSTICK_Z, INVERT_JOYSTICK_Z);
  cfg.putBool(CFG_INVERT_JOYSTICK_X, INVERT_JOYSTICK_X);
  cfg.putBool(CFG_INVERT_JOYSTICK_Y, INVERT_JOYSTICK_Y);
  cfg.putBool(CFG_INVERT_JOYSTICK_BUTTON, INVERT_JOYSTICK_BUTTON);
  cfg.end();
}

bool parseLongValue(const String& text, long* value) {
  String trimmed = text;
  trimmed.trim();
  if (trimmed.length() == 0) return false;
  char* end = nullptr;
  long parsed = strtol(trimmed.c_str(), &end, 10);
  if (end == trimmed.c_str() || *end != '\0') return false;
  *value = parsed;
  return true;
}

bool parseFloatValue(const String& text, float* value) {
  String trimmed = text;
  trimmed.trim();
  if (trimmed.length() == 0) return false;
  char* end = nullptr;
  float parsed = strtof(trimmed.c_str(), &end);
  if (end == trimmed.c_str() || *end != '\0' || !isfinite(parsed)) return false;
  *value = parsed;
  return true;
}

bool parseBoolValue(const String& text, bool* value) {
  String normalized = text;
  normalized.trim();
  normalized.toLowerCase();
  if (normalized == "1" || normalized == "true" || normalized == "on") {
    *value = true;
    return true;
  }
  if (normalized == "0" || normalized == "false" || normalized == "off") {
    *value = false;
    return true;
  }
  return false;
}

bool readLongConfigArg(const char* name, long* target, long minValue, long maxValue, String* error) {
  if (!server.hasArg(name)) {
    *error = String("Valore di configurazione mancante: ") + name;
    return false;
  }
  long value;
  if (!parseLongValue(server.arg(name), &value) || value < minValue || value > maxValue) {
    *error = String(name) + " deve essere compreso tra " + String(minValue) + " e " + String(maxValue);
    return false;
  }
  *target = value;
  return true;
}

bool readIntConfigArg(const char* name, int* target, int minValue, int maxValue, String* error) {
  long value;
  if (!readLongConfigArg(name, &value, minValue, maxValue, error)) return false;
  *target = int(value);
  return true;
}

bool readFloatConfigArg(const char* name, float* target, float minValue, float maxValue, String* error) {
  if (!server.hasArg(name)) {
    *error = String("Valore di configurazione mancante: ") + name;
    return false;
  }
  float value;
  if (!parseFloatValue(server.arg(name), &value) || value < minValue || value > maxValue) {
    *error = String(name) + " deve essere compreso tra " + String(minValue, 2) + " e " + String(maxValue, 2);
    return false;
  }
  *target = value;
  return true;
}

bool readBoolConfigArg(const char* name, bool* target, String* error) {
  if (!server.hasArg(name)) {
    *error = String("Valore di configurazione mancante: ") + name;
    return false;
  }
  if (!parseBoolValue(server.arg(name), target)) {
    *error = String(name) + " deve essere 0 o 1";
    return false;
  }
  return true;
}

bool readPulsePerRevolutionConfigArgs(String* error) {
  if (server.hasArg("zPulsePerRevolution") || server.hasArg("xPulsePerRevolution") || server.hasArg("yPulsePerRevolution")) {
    return
      readFloatConfigArg("zPulsePerRevolution", &PULSE_PER_REVOLUTION_Z, 1.0, 100000.0, error) &&
      readFloatConfigArg("xPulsePerRevolution", &PULSE_PER_REVOLUTION_X, 1.0, 100000.0, error) &&
      readFloatConfigArg("yPulsePerRevolution", &PULSE_PER_REVOLUTION_Y, 1.0, 100000.0, error);
  }

  float pulsePerRevolution;
  if (!readFloatConfigArg("pulsePerRevolution", &pulsePerRevolution, 1.0, 100000.0, error)) return false;
  PULSE_PER_REVOLUTION_Z = pulsePerRevolution;
  PULSE_PER_REVOLUTION_X = pulsePerRevolution;
  PULSE_PER_REVOLUTION_Y = pulsePerRevolution;
  return true;
}

bool validateMachineConfig(String* error) {
  if (SPEED_START_Z > SPEED_MANUAL_MOVE_Z) {
    *error = "zSpeedStart deve essere minore o uguale a zSpeedManualMove";
    return false;
  }
  if (SPEED_START_X > SPEED_MANUAL_MOVE_X) {
    *error = "xSpeedStart deve essere minore o uguale a xSpeedManualMove";
    return false;
  }
  if (SPEED_START_Y > SPEED_MANUAL_MOVE_Y) {
    *error = "ySpeedStart deve essere minore o uguale a ySpeedManualMove";
    return false;
  }
  if (JOYSTICK_DEADBAND >= JOYSTICK_ADC_MAX) {
    *error = "joystickDeadband deve essere minore di joystickAdcMax";
    return false;
  }
  if (JOYSTICK_ENABLED && !anyJoystickAxisEnabled()) {
    *error = "almeno un asse joystick deve essere abilitato quando joystickEnabled è attivo";
    return false;
  }
  return true;
}

bool readMachineConfigFromRequest(String* error) {
  return
    readIntConfigArg("encoderPpr", &ENCODER_PPR, 1, 15000, error) &&
    readIntConfigArg("encoderBacklash", &ENCODER_BACKLASH, 0, 30000, error) &&
    readIntConfigArg("axisEncoderBacklash", &AXIS_ENCODER_BACKLASH, 0, 30000, error) &&
    readLongConfigArg("zScrewDu", &SCREW_Z_DU, 1, 10000000, error) &&
    readLongConfigArg("zMotorSteps", &MOTOR_STEPS_Z, 1, 1000000, error) &&
    readLongConfigArg("zSpeedStart", &SPEED_START_Z, 1, 1000000, error) &&
    readLongConfigArg("zAcceleration", &ACCELERATION_Z, 1, 100000000, error) &&
    readLongConfigArg("zSpeedManualMove", &SPEED_MANUAL_MOVE_Z, 1, 1000000, error) &&
    readBoolConfigArg("zInvert", &INVERT_Z, error) &&
    readBoolConfigArg("zInvertEnable", &INVERT_Z_ENABLE, error) &&
    readBoolConfigArg("zNeedsRest", &NEEDS_REST_Z, error) &&
    readLongConfigArg("zMaxTravelMm", &MAX_TRAVEL_MM_Z, 1, 10000, error) &&
    readLongConfigArg("zBacklashDu", &BACKLASH_DU_Z, 0, 10000000, error) &&
    readLongConfigArg("xScrewDu", &SCREW_X_DU, 1, 10000000, error) &&
    readLongConfigArg("xMotorSteps", &MOTOR_STEPS_X, 1, 1000000, error) &&
    readLongConfigArg("xSpeedStart", &SPEED_START_X, 1, 1000000, error) &&
    readLongConfigArg("xAcceleration", &ACCELERATION_X, 1, 100000000, error) &&
    readLongConfigArg("xSpeedManualMove", &SPEED_MANUAL_MOVE_X, 1, 1000000, error) &&
    readBoolConfigArg("xInvert", &INVERT_X, error) &&
    readBoolConfigArg("xInvertEnable", &INVERT_X_ENABLE, error) &&
    readBoolConfigArg("xNeedsRest", &NEEDS_REST_X, error) &&
    readLongConfigArg("xMaxTravelMm", &MAX_TRAVEL_MM_X, 1, 10000, error) &&
    readLongConfigArg("xBacklashDu", &BACKLASH_DU_X, 0, 10000000, error) &&
    readLongConfigArg("stepTimeMs", &STEP_TIME_MS, 1, 10000, error) &&
    readLongConfigArg("delayBetweenStepsMs", &DELAY_BETWEEN_STEPS_MS, 0, 10000, error) &&
    readBoolConfigArg("enableContinuousMove", &ENABLE_CONTINUOUS_MOVE, error) &&
    readLongConfigArg("safeDistanceDu", &SAFE_DISTANCE_DU, 0, 10000000, error) &&
    readLongConfigArg("slotLeftReductionDu", &SLOT_LEFT_REDUCTION_DU, 0, 10000000, error) &&
    readLongConfigArg("coneDiaBigDu", &CONE_DIA_BIG_DU, 1000, 9999900, error) &&
    readLongConfigArg("coneDiaSmallDu", &CONE_DIA_SMALL_DU, 0, 9999900, error) &&
    readBoolConfigArg("activeY", &ACTIVE_Y, error) &&
    readBoolConfigArg("rotaryY", &ROTARY_Y, error) &&
    readLongConfigArg("yMotorSteps", &MOTOR_STEPS_Y, 1, 1000000, error) &&
    readLongConfigArg("yScrewDu", &SCREW_Y_DU, 1, 10000000, error) &&
    readLongConfigArg("ySpeedStart", &SPEED_START_Y, 1, 1000000, error) &&
    readLongConfigArg("yAcceleration", &ACCELERATION_Y, 1, 100000000, error) &&
    readLongConfigArg("ySpeedManualMove", &SPEED_MANUAL_MOVE_Y, 1, 1000000, error) &&
    readBoolConfigArg("yInvert", &INVERT_Y, error) &&
    readBoolConfigArg("yInvertEnable", &INVERT_Y_ENABLE, error) &&
    readBoolConfigArg("yNeedsRest", &NEEDS_REST_Y, error) &&
    readLongConfigArg("yMaxTravelMm", &MAX_TRAVEL_MM_Y, 1, 10000, error) &&
    readLongConfigArg("yBacklashDu", &BACKLASH_DU_Y, 0, 10000000, error) &&
    readPulsePerRevolutionConfigArgs(error) &&
    readBoolConfigArg("joystickEnabled", &JOYSTICK_ENABLED, error) &&
    readBoolConfigArg("joystickZEnabled", &JOYSTICK_Z_ENABLED, error) &&
    readBoolConfigArg("joystickXEnabled", &JOYSTICK_X_ENABLED, error) &&
    readBoolConfigArg("joystickYEnabled", &JOYSTICK_Y_ENABLED, error) &&
    readBoolConfigArg("joystickButtonTogglesOnOff", &JOYSTICK_BUTTON_TOGGLES_ON_OFF, error) &&
    readIntConfigArg("joystickCenterSamples", &JOYSTICK_CENTER_SAMPLES, 1, 1024, error) &&
    readIntConfigArg("joystickOversamples", &JOYSTICK_OVERSAMPLES, 1, 1024, error) &&
    readIntConfigArg("joystickSampleIntervalMs", &JOYSTICK_SAMPLE_INTERVAL_MS, 1, 1000, error) &&
    readIntConfigArg("joystickAdcMax", &JOYSTICK_ADC_MAX, 1, 65535, error) &&
    readIntConfigArg("joystickDeadband", &JOYSTICK_DEADBAND, 0, 65534, error) &&
    readIntConfigArg("joystickPulseQueueLimit", &JOYSTICK_PULSE_QUEUE_LIMIT, 1, 1000000, error) &&
    readFloatConfigArg("joystickNormalRevolutionsPerSecond", &JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND, 0.01, 1000.0, error) &&
    readFloatConfigArg("joystickRapidRevolutionsPerSecond", &JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND, 0.01, 1000.0, error) &&
    readBoolConfigArg("invertJoystickZ", &INVERT_JOYSTICK_Z, error) &&
    readBoolConfigArg("invertJoystickX", &INVERT_JOYSTICK_X, error) &&
    readBoolConfigArg("invertJoystickY", &INVERT_JOYSTICK_Y, error) &&
    readBoolConfigArg("invertJoystickButton", &INVERT_JOYSTICK_BUTTON, error) &&
    validateMachineConfig(error);
}

void appendConfigLine(String* response, const char* name, const String& value) {
  *response += name;
  *response += "=";
  *response += value;
  *response += "\n";
}

void appendConfigLine(String* response, const char* name, long value) {
  appendConfigLine(response, name, String(value));
}

void appendConfigLine(String* response, const char* name, int value) {
  appendConfigLine(response, name, String(value));
}

void appendConfigLine(String* response, const char* name, bool value) {
  appendConfigLine(response, name, String(value ? 1 : 0));
}

void appendConfigLine(String* response, const char* name, float value) {
  appendConfigLine(response, name, String(value, 4));
}

void setKeyboardConfigDefaults() {
  SHOW_KEY_PRESSES = DEFAULT_SHOW_KEY_PRESSES;
  for (int i = 0; i < KEYBOARD_BINDING_COUNT; i++) {
    keyboardBindings[i].code = keyboardBindings[i].defaultCode;
  }
}

const char* keyboardActionLabel(byte actionCode) {
  for (int i = 0; i < KEYBOARD_BINDING_COUNT; i++) {
    if (keyboardBindings[i].actionCode == actionCode) {
      return keyboardBindings[i].label;
    }
  }
  return "Non mappato";
}

byte keyboardActionForCode(byte physicalCode) {
  for (int i = 0; i < KEYBOARD_BINDING_COUNT; i++) {
    if (keyboardBindings[i].code == physicalCode) {
      return keyboardBindings[i].actionCode;
    }
  }
  return 0;
}

bool validateKeyboardConfig(String* error) {
  for (int i = 0; i < KEYBOARD_BINDING_COUNT; i++) {
    if (keyboardBindings[i].code == 0) {
      *error = String(keyboardBindings[i].label) + " deve usare un codice tasto 1..255";
      return false;
    }
    if (keyboardBindings[i].code == 170) {
      *error = String(keyboardBindings[i].label) + " non può usare il codice riservato 170";
      return false;
    }
    for (int j = i + 1; j < KEYBOARD_BINDING_COUNT; j++) {
      if (keyboardBindings[i].code == keyboardBindings[j].code) {
        *error = String("Il codice tasto ") + String(keyboardBindings[i].code) + " è assegnato sia a " + keyboardBindings[i].label + " sia a " + keyboardBindings[j].label;
        return false;
      }
    }
  }
  return true;
}

void saveKeyboardConfig() {
  Preferences cfg;
  cfg.begin(KEYBOARD_CONFIG_NAMESPACE);
  cfg.putInt(KCFG_VERSION, KEYBOARD_CONFIG_VERSION);
  cfg.putBool(KCFG_SHOW_KEY_PRESSES, SHOW_KEY_PRESSES);
  for (int i = 0; i < KEYBOARD_BINDING_COUNT; i++) {
    cfg.putUChar(keyboardBindings[i].id, keyboardBindings[i].code);
  }
  cfg.end();
}

void loadKeyboardConfig() {
  setKeyboardConfigDefaults();
  Preferences cfg;
  cfg.begin(KEYBOARD_CONFIG_NAMESPACE);
  if (cfg.getInt(KCFG_VERSION) != KEYBOARD_CONFIG_VERSION) {
    cfg.clear();
    cfg.putInt(KCFG_VERSION, KEYBOARD_CONFIG_VERSION);
  }
  SHOW_KEY_PRESSES = cfg.getBool(KCFG_SHOW_KEY_PRESSES, SHOW_KEY_PRESSES);
  for (int i = 0; i < KEYBOARD_BINDING_COUNT; i++) {
    keyboardBindings[i].code = cfg.getUChar(keyboardBindings[i].id, keyboardBindings[i].code);
  }
  cfg.end();

  String error = "";
  if (!validateKeyboardConfig(&error)) {
    setKeyboardConfigDefaults();
    saveKeyboardConfig();
  }
}

bool readKeyboardConfigFromRequest(String* error) {
  if (!readBoolConfigArg("showKeyPresses", &SHOW_KEY_PRESSES, error)) return false;

  for (int i = 0; i < KEYBOARD_BINDING_COUNT; i++) {
    if (!server.hasArg(keyboardBindings[i].id)) {
      *error = String("Valore tastiera mancante: ") + keyboardBindings[i].id;
      return false;
    }
    long value;
    if (!parseLongValue(server.arg(keyboardBindings[i].id), &value) || value < 1 || value > 255) {
      *error = String(keyboardBindings[i].label) + " deve usare un codice tasto 1..255";
      return false;
    }
    keyboardBindings[i].code = byte(value);
  }

  return validateKeyboardConfig(error);
}

String getKeyboardConfigResponse() {
  String response = "";
  response.reserve(1200);
  appendConfigLine(&response, "showKeyPresses", SHOW_KEY_PRESSES);
  for (int i = 0; i < KEYBOARD_BINDING_COUNT; i++) {
    appendConfigLine(&response, keyboardBindings[i].id, int(keyboardBindings[i].code));
  }
  return response;
}

void queueWebSocketText(const String& text) {
  if (!webBuffersReady) return;
  writeBuffer(&outBuffer, text);
}

bool isWebUiActionCode(byte actionCode) {
  for (int i = 0; i < KEYBOARD_BINDING_COUNT; i++) {
    if (keyboardBindings[i].actionCode == actionCode) {
      return true;
    }
  }
  return false;
}

bool parseWebUiStateToken(const String& token, bool* isPress) {
  if (token == "1" || token == "p" || token == "press" || token == "down") {
    *isPress = true;
    return true;
  }
  if (token == "0" || token == "r" || token == "release" || token == "up") {
    *isPress = false;
    return true;
  }
  return false;
}

bool parseWebUiEventCommand(uint8_t* payload, size_t length, WebUiEvent* event, String* error) {
  size_t start = 0;
  while (start < length && payload[start] <= 32) start++;
  size_t end = length;
  while (end > start && payload[end - 1] <= 32) end--;
  if (start >= end || payload[start] != '@') return false;

  size_t i = start + 1;
  long actionCode = 0;
  bool hasActionCode = false;
  while (i < end && payload[i] >= '0' && payload[i] <= '9') {
    hasActionCode = true;
    actionCode = actionCode * 10 + (payload[i] - '0');
    if (actionCode > 255) {
      *error = "codice azione web deve essere 1..255";
      return true;
    }
    i++;
  }

  if (!hasActionCode) {
    *error = "codice azione web mancante";
    return true;
  }
  if (actionCode < 1 || !isWebUiActionCode(byte(actionCode))) {
    *error = String("codice azione web sconosciuto ") + String(actionCode);
    return true;
  }

  if (i >= end) {
    *error = "stato azione web mancante";
    return true;
  }

  char separator = char(payload[i]);
  if (separator != ':' && separator != '=' && separator != ',') {
    *error = "formato atteso @azione:stato";
    return true;
  }
  i++;
  if (i >= end) {
    *error = "stato azione web mancante";
    return true;
  }

  bool isPress = true;
  String state = "";
  while (i < end) {
    state += char(payload[i]);
    i++;
  }
  state.trim();
  state.toLowerCase();
  if (!parseWebUiStateToken(state, &isPress)) {
    *error = String("stato azione web sconosciuto ") + state;
    return true;
  }

  event->actionCode = byte(actionCode);
  event->isPress = isPress;
  return true;
}

bool queueWebUiEvent(byte actionCode, bool isPress) {
  if (webUiEventQueue == NULL) return false;
  WebUiEvent event = { actionCode, isPress };
  bool queued = xQueueSend(webUiEventQueue, &event, 0) == pdTRUE;
  if (queued) {
    portENTER_CRITICAL(&webUiEventMux);
    webUiEventPendingCount = webUiEventPendingCount + 1;
    portEXIT_CRITICAL(&webUiEventMux);
  }
  return queued;
}

bool readWebUiEvent(WebUiEvent* event) {
  if (webUiEventQueue == NULL || webUiEventPendingCount <= 0) return false;
  bool received = xQueueReceive(webUiEventQueue, event, 0) == pdTRUE;
  portENTER_CRITICAL(&webUiEventMux);
  if (received && webUiEventPendingCount > 0) webUiEventPendingCount = webUiEventPendingCount - 1;
  else if (!received) webUiEventPendingCount = 0;
  portEXIT_CRITICAL(&webUiEventMux);
  return received;
}

bool isWebUiMoveAction(byte actionCode) {
  return actionCode == B_LEFT || actionCode == B_RIGHT || actionCode == B_UP || actionCode == B_DOWN || actionCode == B_FORWARD || actionCode == B_BACK;
}

void setMoveButtonPressed(byte actionCode, bool isPress) {
  if (actionCode == B_LEFT) {
    buttonLeftPressed = isPress;
  } else if (actionCode == B_RIGHT) {
    buttonRightPressed = isPress;
  } else if (actionCode == B_UP) {
    buttonUpPressed = isPress;
  } else if (actionCode == B_DOWN) {
    buttonDownPressed = isPress;
  } else if (actionCode == B_FORWARD) {
    buttonForwardPressed = isPress;
  } else if (actionCode == B_BACK) {
    buttonBackPressed = isPress;
  }
}

void releaseWebUiHeldMove() {
  byte actionCode = webUiHeldMoveAction;
  if (actionCode != 0) {
    setMoveButtonPressed(actionCode, false);
  }
  webUiHeldMoveAction = 0;
  webUiHeldMoveMillis = 0;
}

void requestWebUiMoveRelease() {
  if (webUiHeldMoveAction == 0 && webUiEventPendingCount <= 0) return;
  webUiMoveReleaseRequested = true;
  queueWebUiEvent(B_LEFT, false);
  queueWebUiEvent(B_RIGHT, false);
  queueWebUiEvent(B_UP, false);
  queueWebUiEvent(B_DOWN, false);
  queueWebUiEvent(B_FORWARD, false);
  queueWebUiEvent(B_BACK, false);
}

void processWebUiMoveFailsafe() {
  if (webUiMoveReleaseRequested) {
    webUiMoveReleaseRequested = false;
    releaseWebUiHeldMove();
  } else if (webUiHeldMoveAction != 0 && millis() - webUiHeldMoveMillis > WEB_UI_MOVE_TIMEOUT_MS) {
    releaseWebUiHeldMove();
    queueWebSocketText("WEBUI.warning=movimento rilasciato dopo perdita del segnale\n");
  }
}

void updateWebUiMoveWatchdog(byte actionCode, bool isPress) {
  if (!isWebUiMoveAction(actionCode)) return;
  if (isPress) {
    webUiHeldMoveAction = actionCode;
    webUiHeldMoveMillis = millis();
  } else if (webUiHeldMoveAction == actionCode) {
    releaseWebUiHeldMove();
  }
}

bool handleWebUiEventCommand(uint8_t* payload, size_t length) {
  WebUiEvent event = {};
  String error = "";
  if (!parseWebUiEventCommand(payload, length, &event, &error)) {
    return false;
  }
  if (error.length() > 0) {
    queueWebSocketText(String("WEBUI.error=") + error + "\n");
    return true;
  }
  if (!queueWebUiEvent(event.actionCode, event.isPress)) {
    queueWebSocketText("WEBUI.error=coda eventi piena\n");
  }
  return true;
}

void publishKeyboardEvent(byte physicalCode, byte actionCode, bool isPress) {
  String line = String("KEY.") + (isPress ? "press=" : "release=") + String(physicalCode) + "\n";
  line += "KEY.action=";
  line += keyboardActionLabel(actionCode);
  line += "\n";
  queueWebSocketText(line);
  if (SHOW_KEY_PRESSES) {
    // Same place as the old bottom strip, now painted by the display task.
    tftSetStatus((isPress ? "Premi " : "Rilascia ") + String(physicalCode), 3000);
  }
}

void startKeyboardCapture() {
  keyboardCaptureActive = true;
  keyboardCaptureReleaseCode = 0;
  keyboardCaptureUntil = millis() + 30000;
}

void stopKeyboardCapture() {
  keyboardCaptureActive = false;
  keyboardCaptureReleaseCode = 0;
}

bool shouldConsumeKeyboardCapture(byte physicalCode, bool isPress) {
  if (keyboardCaptureReleaseCode != 0 && physicalCode == keyboardCaptureReleaseCode && !isPress) {
    keyboardCaptureReleaseCode = 0;
    return true;
  }
  if (!keyboardCaptureActive) return false;
  if (long(millis() - keyboardCaptureUntil) > 0) {
    stopKeyboardCapture();
    return false;
  }
  if (isPress) {
    keyboardCaptureActive = false;
    keyboardCaptureReleaseCode = physicalCode;
  }
  return true;
}

String getMachineConfigResponse() {
  String response = "";
  response.reserve(2600);
  appendConfigLine(&response, "encoderPpr", ENCODER_PPR);
  appendConfigLine(&response, "encoderBacklash", ENCODER_BACKLASH);
  appendConfigLine(&response, "axisEncoderBacklash", AXIS_ENCODER_BACKLASH);
  appendConfigLine(&response, "zScrewDu", SCREW_Z_DU);
  appendConfigLine(&response, "zMotorSteps", MOTOR_STEPS_Z);
  appendConfigLine(&response, "zPulsePerRevolution", PULSE_PER_REVOLUTION_Z);
  appendConfigLine(&response, "zSpeedStart", SPEED_START_Z);
  appendConfigLine(&response, "zAcceleration", ACCELERATION_Z);
  appendConfigLine(&response, "zSpeedManualMove", SPEED_MANUAL_MOVE_Z);
  appendConfigLine(&response, "zInvert", INVERT_Z);
  appendConfigLine(&response, "zInvertEnable", INVERT_Z_ENABLE);
  appendConfigLine(&response, "zNeedsRest", NEEDS_REST_Z);
  appendConfigLine(&response, "zMaxTravelMm", MAX_TRAVEL_MM_Z);
  appendConfigLine(&response, "zBacklashDu", BACKLASH_DU_Z);
  appendConfigLine(&response, "xScrewDu", SCREW_X_DU);
  appendConfigLine(&response, "xMotorSteps", MOTOR_STEPS_X);
  appendConfigLine(&response, "xPulsePerRevolution", PULSE_PER_REVOLUTION_X);
  appendConfigLine(&response, "xSpeedStart", SPEED_START_X);
  appendConfigLine(&response, "xAcceleration", ACCELERATION_X);
  appendConfigLine(&response, "xSpeedManualMove", SPEED_MANUAL_MOVE_X);
  appendConfigLine(&response, "xInvert", INVERT_X);
  appendConfigLine(&response, "xInvertEnable", INVERT_X_ENABLE);
  appendConfigLine(&response, "xNeedsRest", NEEDS_REST_X);
  appendConfigLine(&response, "xMaxTravelMm", MAX_TRAVEL_MM_X);
  appendConfigLine(&response, "xBacklashDu", BACKLASH_DU_X);
  appendConfigLine(&response, "stepTimeMs", STEP_TIME_MS);
  appendConfigLine(&response, "delayBetweenStepsMs", DELAY_BETWEEN_STEPS_MS);
  appendConfigLine(&response, "enableContinuousMove", ENABLE_CONTINUOUS_MOVE);
  appendConfigLine(&response, "safeDistanceDu", SAFE_DISTANCE_DU);
  appendConfigLine(&response, "slotLeftReductionDu", SLOT_LEFT_REDUCTION_DU);
  appendConfigLine(&response, "coneDiaBigDu", CONE_DIA_BIG_DU);
  appendConfigLine(&response, "coneDiaSmallDu", CONE_DIA_SMALL_DU);
  appendConfigLine(&response, "activeY", ACTIVE_Y);
  appendConfigLine(&response, "rotaryY", ROTARY_Y);
  appendConfigLine(&response, "yMotorSteps", MOTOR_STEPS_Y);
  appendConfigLine(&response, "yPulsePerRevolution", PULSE_PER_REVOLUTION_Y);
  appendConfigLine(&response, "yScrewDu", SCREW_Y_DU);
  appendConfigLine(&response, "ySpeedStart", SPEED_START_Y);
  appendConfigLine(&response, "yAcceleration", ACCELERATION_Y);
  appendConfigLine(&response, "ySpeedManualMove", SPEED_MANUAL_MOVE_Y);
  appendConfigLine(&response, "yInvert", INVERT_Y);
  appendConfigLine(&response, "yInvertEnable", INVERT_Y_ENABLE);
  appendConfigLine(&response, "yNeedsRest", NEEDS_REST_Y);
  appendConfigLine(&response, "yMaxTravelMm", MAX_TRAVEL_MM_Y);
  appendConfigLine(&response, "yBacklashDu", BACKLASH_DU_Y);
  appendConfigLine(&response, "pulsePerRevolution", PULSE_PER_REVOLUTION_Z);
  appendConfigLine(&response, "joystickEnabled", JOYSTICK_ENABLED);
  appendConfigLine(&response, "joystickZEnabled", JOYSTICK_Z_ENABLED);
  appendConfigLine(&response, "joystickXEnabled", JOYSTICK_X_ENABLED);
  appendConfigLine(&response, "joystickYEnabled", JOYSTICK_Y_ENABLED);
  appendConfigLine(&response, "joystickButtonTogglesOnOff", JOYSTICK_BUTTON_TOGGLES_ON_OFF);
  appendConfigLine(&response, "joystickCenterSamples", JOYSTICK_CENTER_SAMPLES);
  appendConfigLine(&response, "joystickOversamples", JOYSTICK_OVERSAMPLES);
  appendConfigLine(&response, "joystickSampleIntervalMs", JOYSTICK_SAMPLE_INTERVAL_MS);
  appendConfigLine(&response, "joystickAdcMax", JOYSTICK_ADC_MAX);
  appendConfigLine(&response, "joystickDeadband", JOYSTICK_DEADBAND);
  appendConfigLine(&response, "joystickPulseQueueLimit", JOYSTICK_PULSE_QUEUE_LIMIT);
  appendConfigLine(&response, "joystickNormalRevolutionsPerSecond", JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND);
  appendConfigLine(&response, "joystickRapidRevolutionsPerSecond", JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND);
  appendConfigLine(&response, "invertJoystickZ", INVERT_JOYSTICK_Z);
  appendConfigLine(&response, "invertJoystickX", INVERT_JOYSTICK_X);
  appendConfigLine(&response, "invertJoystickY", INVERT_JOYSTICK_Y);
  appendConfigLine(&response, "invertJoystickButton", INVERT_JOYSTICK_BUTTON);
  return response;
}

void setWifiConfigDefaults() {
  WIFI_ENABLED = DEFAULT_WIFI_ENABLED;
  WIFI_SSID = DEFAULT_WIFI_SSID;
  WIFI_PASSWORD = DEFAULT_WIFI_PASSWORD;
}

bool validateWifiConfig(String* error) {
  if (WIFI_SSID.length() > 32) {
    *error = "wifiSsid deve essere lungo al massimo 32 caratteri";
    return false;
  }
  if (WIFI_PASSWORD.length() > 63) {
    *error = "wifiPassword deve essere lunga al massimo 63 caratteri";
    return false;
  }
  if (WIFI_PASSWORD.length() > 0 && WIFI_PASSWORD.length() < 8) {
    *error = "wifiPassword deve essere vuota o di almeno 8 caratteri";
    return false;
  }
  return true;
}

void loadWifiConfig() {
  setWifiConfigDefaults();
  Preferences cfg;
  cfg.begin(WIFI_CONFIG_NAMESPACE);
  if (cfg.getInt(WCFG_VERSION) != WIFI_CONFIG_VERSION) {
    cfg.clear();
    cfg.putInt(WCFG_VERSION, WIFI_CONFIG_VERSION);
  }
  WIFI_ENABLED = cfg.getBool(WCFG_ENABLED, WIFI_ENABLED);
  WIFI_SSID = cfg.getString(WCFG_SSID, WIFI_SSID);
  WIFI_PASSWORD = cfg.getString(WCFG_PASSWORD, WIFI_PASSWORD);
  cfg.end();

  String error = "";
  if (!validateWifiConfig(&error)) {
    setWifiConfigDefaults();
  }
}

void saveWifiConfig() {
  Preferences cfg;
  cfg.begin(WIFI_CONFIG_NAMESPACE);
  cfg.putInt(WCFG_VERSION, WIFI_CONFIG_VERSION);
  cfg.putBool(WCFG_ENABLED, WIFI_ENABLED);
  cfg.putString(WCFG_SSID, WIFI_SSID);
  cfg.putString(WCFG_PASSWORD, WIFI_PASSWORD);
  cfg.end();
}

String getWifiMode() {
  if (!WIFI_ENABLED) return "off";
  if (wifiSetupApActive) return "setup-ap";
  if (wifiStationConnected) return "station";
  return "starting";
}

String getWifiConfigResponse() {
  String response = "";
  response.reserve(360);
  appendConfigLine(&response, "wifiEnabled", WIFI_ENABLED);
  appendConfigLine(&response, "wifiSsid", WIFI_SSID);
  appendConfigLine(&response, "wifiPasswordSet", WIFI_PASSWORD.length() > 0);
  appendConfigLine(&response, "wifiMode", getWifiMode());
  appendConfigLine(&response, "wifiIp", wifiIpAddress);
  appendConfigLine(&response, "wifiStatus", wifiStatus);
  appendConfigLine(&response, "setupApSsid", WIFI_SETUP_AP_SSID);
  return response;
}

bool readWifiConfigFromRequest(String* error) {
  bool enabled = WIFI_ENABLED;
  if (!readBoolConfigArg("wifiEnabled", &enabled, error)) {
    return false;
  }
  if (!server.hasArg("wifiSsid")) {
    *error = "Valore WiFi mancante: wifiSsid";
    return false;
  }
  if (!server.hasArg("wifiPassword")) {
    *error = "Valore WiFi mancante: wifiPassword";
    return false;
  }

  bool clearPassword = false;
  if (!readBoolConfigArg("wifiClearPassword", &clearPassword, error)) {
    return false;
  }

  String ssid = server.arg("wifiSsid");
  ssid.trim();
  String password = server.arg("wifiPassword");

  WIFI_ENABLED = enabled;
  WIFI_SSID = ssid;
  if (clearPassword) {
    WIFI_PASSWORD = "";
  } else if (password.length() > 0) {
    WIFI_PASSWORD = password;
  }
  return validateWifiConfig(error);
}

void scheduleConfigRestart() {
  configRestartPending = true;
  configRestartAt = millis() + 1500;
}

void tftUploadLog(const String& message) {
  String line = String("TFT: ") + message + "\n";
  Serial.print(line);
  webSocket.broadcastTXT(line);
  webSocket.loop();
}

void firmwareUploadLog(const String& message) {
  String line = String("FW: ") + message + "\n";
  Serial.print(line);
  webSocket.broadcastTXT(line);
  webSocket.loop();
}

void handleWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  if (type == WStype_CONNECTED) {
    webSocketClientCount = webSocketClientCount + 1;
    machineStatusForcePublish = true;
  } else if (type == WStype_DISCONNECTED) {
    requestWebUiMoveRelease();
    if (webSocketClientCount > 0) webSocketClientCount = webSocketClientCount - 1;
  } else if (type == WStype_TEXT) {
    if (handleWebUiEventCommand(payload, length)) {
      return;
    }
    for (size_t i = 0; i < length; i++) {
      writeBuffer(&inBuffer, payload[i]);
    }
  }
}

void handleClientRequests() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "0");
  server.send_P(200, PSTR("text/html"), indexhtml);
}

int getGcodeProgramCount() {
  File root = LittleFS.open("/");
  if (!root || !root.isDirectory()) {
    writeBuffer(&outBuffer, "error: failed to open directory\n");
    return 0;
  }

  int count = 0;
  File file = root.openNextFile();
  while (file) {
    String filename = file.name();
    file.close();
    if (filename.endsWith(".gcode")) {
      count++;
    }
    file = root.openNextFile();
  }

  return count;
}

bool saveGcode() {
  if (gcodeSaveName.length() < 2) {
    writeBuffer(&outBuffer, "error: name must be at least 2 chars\n");
    return false;
  }
  if (gcodeSaveValue.length() < 2) {
    writeBuffer(&outBuffer, "error: program too short\n");
    return false;
  }

  String filename = "/" + gcodeSaveName + ".gcode";
  File file = LittleFS.open(filename, "w");
  if (!file) {
    writeBuffer(&outBuffer, "error: failed to open file\n");
    return false;
  }

  file.print(gcodeSaveValue);
  file.close();

  writeBuffer(&outBuffer, "success: G-code saved\n");
  gcodeProgramCount = getGcodeProgramCount();
  return true;
}

bool removeGcodeByName(const String& name) {
  if (name.length() == 0) return false;

  String filename = "/" + name + ".gcode";
  if (!LittleFS.exists(filename)) {
    writeBuffer(&outBuffer, "error: file not found\n");
    return false;
  }

  if (!LittleFS.remove(filename)) {
    writeBuffer(&outBuffer, "error: failed to delete " + filename + "\n");
    return false;
  }

  writeBuffer(&outBuffer, "success: " + name + " deleted\n");
  gcodeProgramCount = getGcodeProgramCount();
  return true;
}

String readGcodeProgram(const String& name) {
  String filename = "/" + name + ".gcode";
  File file = LittleFS.open(filename, "r");
  if (!file) {
    return "";
  }

  String result;
  result.reserve(file.size());
  char buf[64];
  while (file.available()) {
    size_t bytesRead = file.readBytes(buf, sizeof(buf));
    result.concat(buf, bytesRead);
  }
  file.close();
  return result;
}

void handleGcodeAdd() {
  if (server.hasArg("name") && server.hasArg("gcode")) {
    gcodeSaveName = server.arg("name");
    gcodeSaveValue = server.arg("gcode");
    if (saveGcode()) {
      server.send(200, "text/plain", "G-code salvato correttamente");
    } else {
      server.send(500, "text/plain", "Salvataggio G-code non riuscito");
    }
  } else {
    server.send(400, "text/plain", "Parametri mancanti");
  }
}

void handleGcodeList() {
  String response = "";
  File root = LittleFS.open("/");
  if (root && root.isDirectory()) {
    File file = root.openNextFile();
    while (file) {
      String filename = file.name();
      if (filename.endsWith(".gcode")) {
        response += filename.substring(0, filename.length() - 6) + "\n";
      }
      file.close();
      file = root.openNextFile();
    }
  }
  server.send(200, "text/plain", response);
}

void handleGcodeGet() {
  if (server.hasArg("name")) {
    String gcode = readGcodeProgram(server.arg("name"));
    if (gcode != "") {
      server.send(200, "text/plain", gcode);
    } else {
      server.send(404, "text/plain", "File G-code non trovato");
    }
  } else {
    server.send(400, "text/plain", "Parametro mancante: name");
  }
}

void handleGcodeRemove() {
  if (server.hasArg("name")) {
    if (removeGcodeByName(server.arg("name"))) {
      server.send(200, "text/plain", "G-code rimosso correttamente");
    } else {
      server.send(500, "text/plain", "Rimozione G-code non riuscita");
    }
  } else {
    server.send(400, "text/plain", "Parametro mancante: name");
  }
}

bool machineConfigChangeBlocked() {
  return isOn || tftUploadActive || firmwareUploadActive || firmwareUploadRestartPending || configRestartPending;
}

void handleConfigGet() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.send(200, "text/plain", getMachineConfigResponse());
}

void handleConfigSave() {
  if (machineConfigChangeBlocked()) {
    server.send(409, "text/plain", "Spegni il controller e attendi la fine degli upload prima di modificare la configurazione macchina");
    return;
  }

  String error = "";
  if (!readMachineConfigFromRequest(&error)) {
    loadMachineConfig();
    server.send(400, "text/plain", error);
    return;
  }

  saveMachineConfig();
  scheduleConfigRestart();
  server.send(200, "text/plain", "Configurazione macchina salvata. Riavvio del controller...");
}

void handleConfigReset() {
  if (machineConfigChangeBlocked()) {
    server.send(409, "text/plain", "Spegni il controller e attendi la fine degli upload prima di ripristinare la configurazione macchina");
    return;
  }

  setMachineConfigDefaults();
  saveMachineConfig();
  scheduleConfigRestart();
  server.send(200, "text/plain", "Configurazione macchina ripristinata. Riavvio del controller...");
}

void handleKeyboardConfigGet() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.send(200, "text/plain", getKeyboardConfigResponse());
}

void handleKeyboardConfigSave() {
  if (machineConfigChangeBlocked()) {
    server.send(409, "text/plain", "Spegni il controller e attendi la fine degli upload prima di modificare la configurazione tastiera");
    return;
  }

  String error = "";
  if (!readKeyboardConfigFromRequest(&error)) {
    loadKeyboardConfig();
    server.send(400, "text/plain", error);
    return;
  }

  saveKeyboardConfig();
  server.send(200, "text/plain", "Configurazione tastiera salvata");
}

void handleKeyboardConfigReset() {
  if (machineConfigChangeBlocked()) {
    server.send(409, "text/plain", "Spegni il controller e attendi la fine degli upload prima di ripristinare la configurazione tastiera");
    return;
  }

  setKeyboardConfigDefaults();
  saveKeyboardConfig();
  server.send(200, "text/plain", "Configurazione tastiera ripristinata");
}

void handleKeyboardCapture() {
  bool enabled = false;
  String error = "";
  if (!readBoolConfigArg("enabled", &enabled, &error)) {
    server.send(400, "text/plain", error);
    return;
  }
  if (enabled && machineConfigChangeBlocked()) {
    server.send(409, "text/plain", "Spegni il controller e attendi la fine degli upload prima di apprendere i tasti");
    return;
  }

  if (enabled) {
    startKeyboardCapture();
    server.send(200, "text/plain", "Acquisizione tasti avviata");
  } else {
    stopKeyboardCapture();
    server.send(200, "text/plain", "Acquisizione tasti fermata");
  }
}

void handleWifiGet() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.send(200, "text/plain", getWifiConfigResponse());
}

void handleWifiSave() {
  if (machineConfigChangeBlocked()) {
    server.send(409, "text/plain", "Spegni il controller e attendi la fine degli upload prima di modificare la configurazione WiFi");
    return;
  }

  String error = "";
  if (!readWifiConfigFromRequest(&error)) {
    loadWifiConfig();
    server.send(400, "text/plain", error);
    return;
  }

  saveWifiConfig();
  scheduleConfigRestart();
  server.send(200, "text/plain", "Configurazione WiFi salvata. Riavvio del controller...");
}

void handleWifiReset() {
  if (machineConfigChangeBlocked()) {
    server.send(409, "text/plain", "Spegni il controller e attendi la fine degli upload prima di ripristinare la configurazione WiFi");
    return;
  }

  setWifiConfigDefaults();
  saveWifiConfig();
  scheduleConfigRestart();
  server.send(200, "text/plain", "Configurazione WiFi ripristinata. Riavvio del controller...");
}

// The main loop (page loads) and taskDisplay (live values) both write command
// frames; without a lock their bytes interleave and the display parses a
// corrupted command, drawing stray rectangles (the "veil").
static SemaphoreHandle_t nextionWriteMutex = NULL;
// While a page repaint runs the commands are spaced out a few ms each: a whole
// burst sent back to back overflows the display parser and the first fields
// come out as solid white blocks.
static volatile bool tftPaceCommands = false;

void writeNextionCommandRaw(const String& command) {
  if (nextionWriteMutex != NULL) xSemaphoreTake(nextionWriteMutex, portMAX_DELAY);
  Serial1.print(command);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  if (tftPaceCommands) delay(4);
  if (nextionWriteMutex != NULL) xSemaphoreGive(nextionWriteMutex);
}

void beginNextionSerial(long baud) {
  if (nextionSerialBaud == baud) {
    return;
  }

  Serial1.updateBaudRate(baud);
  nextionSerialBaud = baud;
  DELAY(5);
}

void clearNextionInput() {
  while (Serial1.available() > 0) {
    Serial1.read();
  }
}

bool waitForNextionByte(byte expected, unsigned long timeoutMs, const String& context) {
  unsigned long start = millis();
  while (millis() - start < timeoutMs) {
    while (Serial1.available() > 0) {
      if (Serial1.read() == expected) {
        return true;
      }
    }
    DELAY(1);
    taskYIELD();
  }
  tftUploadLog(context + ": timeout in attesa di ACK dal display");
  return false;
}

bool waitForNextionConnect(unsigned long timeoutMs, const String& context) {
  String response = "";
  unsigned long start = millis();
  while (millis() - start < timeoutMs) {
    while (Serial1.available() > 0) {
      byte b = Serial1.read();
      if (b != 0xFF && response.length() < 120) {
        response += char(b);
      }
      if (response.indexOf("comok") >= 0) {
        return true;
      }
    }
    DELAY(1);
    taskYIELD();
  }
  tftUploadLog(context + ": timeout connessione");
  return false;
}

unsigned long nextionBaudDelayMs(long baud) {
  return 1000000 / baud + 30;
}

void setTftUploadError(const String& message, int status) {
  tftUploadFailed = true;
  tftUploadHttpStatus = status;
  tftUploadMessage = message;
  tftUploadLog(message);
}

bool startNextionTftUpload(long fileSize, long currentBaud) {
  tftUploadLog(String("upload avviato, dimensione=") + String(fileSize) + " byte, baud display=" + String(currentBaud));
  if (fileSize <= 0) {
    setTftUploadError("errore: file TFT vuoto", 400);
    return false;
  }
  if (currentBaud != NEXTION_FIRST_UPLOAD_BAUD && currentBaud != NEXTION_NORMAL_BAUD) {
    setTftUploadError(String("errore: baud Nextion non supportato ") + String(currentBaud), 400);
    return false;
  }
  if (isOn) {
    setTftUploadError("errore: spegni il controller prima dell'upload TFT", 409);
    return false;
  }

  tftUploadActive = true;
  tftUploadFailed = false;
  tftUploadHttpStatus = 200;
  tftUploadMessage = "Upload TFT avviato";
  tftUploadExpectedSize = fileSize;
  tftUploadReceivedSize = 0;
  tftUploadSentSize = 0;
  tftUploadPacketLength = 0;
  tftUploadProgressPercent = 0;
  nextionBufferIndex = 0;
  beginNextionSerial(currentBaud);
  clearNextionInput();

  writeNextionCommandRaw("");
  DELAY(nextionBaudDelayMs(currentBaud));
  clearNextionInput();
  writeNextionCommandRaw("connect");
  if (!waitForNextionConnect(NEXTION_CONNECT_TIMEOUT_MS, String("connessione al baud selezionato ") + String(currentBaud))) {
    setTftUploadError(String("errore: il display Nextion non risponde al baud selezionato ") + String(currentBaud) + ". Alimenta H5 dalla porta POWER, non da USB, e riprova", 500);
    beginNextionSerial(NEXTION_NORMAL_BAUD);
    tftUploadActive = false;
    return false;
  }
  tftUploadLog(String("display connesso a ") + String(currentBaud) + " baud");
  long uploadBaud = NEXTION_UPLOAD_BAUD;
  clearNextionInput();
  writeNextionCommandRaw("");
  writeNextionCommandRaw(String("whmi-wri ") + String(fileSize) + "," + String(uploadBaud) + ",0");
  if (currentBaud != uploadBaud) {
    DELAY(nextionBaudDelayMs(currentBaud) + 50);
    beginNextionSerial(uploadBaud);
  }
  if (!waitForNextionByte(0x05, NEXTION_ACK_TIMEOUT_MS, "whmi-wri")) {
    setTftUploadError("errore: il display Nextion non ha accettato l'upload TFT", 500);
    beginNextionSerial(NEXTION_NORMAL_BAUD);
    tftUploadActive = false;
    return false;
  }
  tftUploadLog(String("display pronto, invio a ") + String(uploadBaud) + " baud");
  return true;
}

bool flushTftUploadPacket() {
  if (tftUploadPacketLength == 0) {
    return true;
  }

  Serial1.write(tftUploadPacket, tftUploadPacketLength);
  Serial1.flush();
  tftUploadSentSize += tftUploadPacketLength;
  tftUploadPacketLength = 0;
  int progress = tftUploadExpectedSize > 0 ? int(tftUploadSentSize * 100 / tftUploadExpectedSize) : 0;
  if (progress >= tftUploadProgressPercent + 10 || progress == 100) {
    tftUploadProgressPercent = progress;
    tftUploadLog(String("avanzamento ") + String(progress) + "%");
  }
  if (!waitForNextionByte(0x05, NEXTION_ACK_TIMEOUT_MS, "pacchetto")) {
    setTftUploadError("errore: il display Nextion non ha confermato i dati TFT", 500);
    return false;
  }
  return true;
}

bool writeTftUploadData(const byte* data, size_t length) {
  size_t offset = 0;
  while (offset < length) {
    int packetSpace = NEXTION_TFT_PACKET_SIZE - tftUploadPacketLength;
    int copyLength = min(int(length - offset), packetSpace);
    memcpy(tftUploadPacket + tftUploadPacketLength, data + offset, copyLength);
    tftUploadPacketLength += copyLength;
    tftUploadReceivedSize += copyLength;
    offset += copyLength;
    if (tftUploadPacketLength == NEXTION_TFT_PACKET_SIZE && !flushTftUploadPacket()) {
      return false;
    }
  }
  return true;
}

void finishTftUpload() {
  if (!tftUploadFailed && tftUploadReceivedSize != tftUploadExpectedSize) {
    setTftUploadError("errore: dimensione upload TFT non corrispondente", 400);
  }
  if (!tftUploadFailed && !flushTftUploadPacket()) {
    // flushTftUploadPacket sets the error message.
  }
  if (!tftUploadFailed) {
    tftUploadMessage = "Upload TFT completato";
    tftUploadLog("upload completato, attesa reset display");
    waitForNextionByte(0x88, 5000, "reset display");
  }
  beginNextionSerial(NEXTION_NORMAL_BAUD);
  lcdHashLine0 = LCD_HASH_INITIAL;
  lcdHashLine1 = LCD_HASH_INITIAL;
  lcdHashLine2 = LCD_HASH_INITIAL;
  lcdHashLine3 = LCD_HASH_INITIAL;
  tftUploadActive = false;
}

void handleTftUpload() {
  // Raw (non-multipart) bodies carry no filename, so the .tft check
  // only applies to the multipart path below.
  if (server.hasRaw()) {
    HTTPRaw& raw = server.raw();
    if (raw.status == RAW_START) {
      // Query arguments are parsed only after the body, so raw uploads take the
      // size from Content-Length and the baud from the X-Baud header.
      long fileSize = server.clientContentLength();
      long currentBaud = server.hasHeader("X-Baud") ? server.header("X-Baud").toInt() : NEXTION_FIRST_UPLOAD_BAUD;
      tftUploadLog(String("selezionato upload diretto, baud=") + String(currentBaud));
      startNextionTftUpload(fileSize, currentBaud);
    } else if (raw.status == RAW_WRITE) {
      if (!tftUploadFailed) {
        writeTftUploadData(raw.buf, raw.currentSize);
      }
    } else if (raw.status == RAW_END) {
      finishTftUpload();
    } else {
      setTftUploadError("errore: upload TFT interrotto", 400);
      beginNextionSerial(NEXTION_NORMAL_BAUD);
      tftUploadActive = false;
    }
    return;
  }

  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    filename.toLowerCase();
    long fileSize = server.hasArg("size") ? server.arg("size").toInt() : upload.totalSize;
    long currentBaud = server.hasArg("baud") ? server.arg("baud").toInt() : NEXTION_FIRST_UPLOAD_BAUD;
    tftUploadLog(String("selezionato ") + upload.filename + ", baud=" + String(currentBaud));
    if (!filename.endsWith(".tft")) {
      setTftUploadError("errore: si possono caricare solo file .tft", 400);
      return;
    }
    startNextionTftUpload(fileSize, currentBaud);
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (!tftUploadFailed) {
      writeTftUploadData(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    finishTftUpload();
  } else if (upload.status == UPLOAD_FILE_ABORTED) {
    setTftUploadError("errore: upload TFT interrotto", 400);
    beginNextionSerial(NEXTION_NORMAL_BAUD);
    tftUploadActive = false;
  }
}

void handleTftUploadResult() {
  server.send(tftUploadHttpStatus, "text/plain", tftUploadMessage);
}

void setFirmwareUploadError(const String& message, int status) {
  firmwareUploadFailed = true;
  firmwareUploadHttpStatus = status;
  firmwareUploadMessage = message;
  firmwareUploadLog(message);
}

bool startFirmwareUpload(size_t fileSize) {
  firmwareUploadLog(String("upload avviato, dimensione=") + String((unsigned long)fileSize) + " byte");
  firmwareUploadRestartPending = false;
  if (fileSize == 0) {
    setFirmwareUploadError("errore: file firmware vuoto", 400);
    return false;
  }
  if (tftUploadActive) {
    setFirmwareUploadError("errore: attendi la fine dell'upload TFT prima di aggiornare il firmware", 409);
    return false;
  }
  if (isOn) {
    setFirmwareUploadError("errore: spegni il controller prima dell'upload firmware", 409);
    return false;
  }

  firmwareUploadActive = true;
  firmwareUploadFailed = false;
  firmwareUploadHttpStatus = 200;
  firmwareUploadMessage = "Upload firmware avviato";
  firmwareUploadExpectedSize = fileSize;
  firmwareUploadReceivedSize = 0;
  firmwareUploadProgressPercent = 0;

  if (!Update.begin(fileSize, U_FLASH)) {
    setFirmwareUploadError(String("errore: impossibile avviare l'aggiornamento firmware: ") + Update.errorString(), 500);
    firmwareUploadActive = false;
    return false;
  }
  return true;
}

bool writeFirmwareUploadData(const byte* data, size_t length) {
  size_t written = Update.write((uint8_t*)data, length);
  firmwareUploadReceivedSize += written;
  if (written != length) {
    setFirmwareUploadError(String("errore: scrittura firmware non riuscita: ") + Update.errorString(), 500);
    return false;
  }

  int progress = firmwareUploadExpectedSize > 0 ? int(firmwareUploadReceivedSize * 100 / firmwareUploadExpectedSize) : 0;
  if (progress >= firmwareUploadProgressPercent + 10 || progress == 100) {
    firmwareUploadProgressPercent = progress;
    firmwareUploadLog(String("avanzamento ") + String(progress) + "%");
  }
  return true;
}

void finishFirmwareUpload() {
  if (!firmwareUploadFailed && firmwareUploadReceivedSize != firmwareUploadExpectedSize) {
    setFirmwareUploadError("errore: dimensione upload firmware non corrispondente", 400);
  }
  if (!firmwareUploadFailed && !Update.end(true)) {
    setFirmwareUploadError(String("errore: aggiornamento firmware non riuscito: ") + Update.errorString(), 500);
  }
  if (!firmwareUploadFailed) {
    firmwareUploadMessage = "Upload firmware completato. Riavvio del controller...";
    firmwareUploadLog("upload completato, riavvio del controller");
    firmwareUploadRestartPending = true;
    firmwareUploadRestartAt = millis() + 1500;
  } else if (firmwareUploadActive) {
    Update.abort();
  }
  firmwareUploadActive = false;
}

void handleFirmwareUpload() {
  // Raw (non-multipart) bodies carry no filename, so the .bin check
  // only applies to the multipart path below.
  if (server.hasRaw()) {
    HTTPRaw& raw = server.raw();
    if (raw.status == RAW_START) {
      size_t fileSize = server.clientContentLength();
      firmwareUploadLog("selezionato upload diretto");
      startFirmwareUpload(fileSize);
    } else if (raw.status == RAW_WRITE) {
      if (!firmwareUploadFailed) {
        writeFirmwareUploadData(raw.buf, raw.currentSize);
      }
    } else if (raw.status == RAW_END) {
      finishFirmwareUpload();
    } else {
      if (firmwareUploadActive) {
        Update.abort();
      }
      setFirmwareUploadError("errore: upload firmware interrotto", 400);
      firmwareUploadActive = false;
    }
    return;
  }

  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    filename.toLowerCase();
    size_t fileSize = server.hasArg("size") ? server.arg("size").toInt() : upload.totalSize;
    firmwareUploadLog(String("selezionato ") + upload.filename);
    if (!filename.endsWith(".bin")) {
      setFirmwareUploadError("errore: si possono caricare solo file firmware .bin", 400);
      return;
    }
    startFirmwareUpload(fileSize);
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (!firmwareUploadFailed) {
      writeFirmwareUploadData(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    finishFirmwareUpload();
  } else if (upload.status == UPLOAD_FILE_ABORTED) {
    if (firmwareUploadActive) {
      Update.abort();
    }
    setFirmwareUploadError("errore: upload firmware interrotto", 400);
    firmwareUploadActive = false;
  }
}

void handleFirmwareUploadResult() {
  server.sendHeader("Connection", "close");
  server.send(firmwareUploadHttpStatus, "text/plain", firmwareUploadMessage);
}

void handleStatus() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.send(200, "text/plain",
    String("LittleFS.freeSpace=") + String(LittleFS.totalBytes() - LittleFS.usedBytes()) + "\n" +
    "TFT.uploadActive=" + String(tftUploadActive ? 1 : 0) + "\n" +
    "TFT.uploaded=" + String(tftUploadSentSize) + "\n" +
    "TFT.size=" + String(tftUploadExpectedSize) + "\n" +
    "TFT.message=" + tftUploadMessage + "\n" +
    "TFT.page=" + String(tftDiagPage) + "\n" +
    "TFT.code=" + String(tftDiagCode, HEX) + "\n" +
    "TFT.events=" + String(tftDiagEvents) + "\n" +
    "TFT.reboots=" + String(tftDiagReboots) + "\n" +
    "TFT.mode=" + String(mode) + "\n" +
    "TFT.on=" + String(isOn ? 1 : 0) + "\n" +
    "FW.uploadActive=" + String(firmwareUploadActive ? 1 : 0) + "\n" +
    "FW.uploaded=" + String((unsigned long)firmwareUploadReceivedSize) + "\n" +
    "FW.size=" + String((unsigned long)firmwareUploadExpectedSize) + "\n" +
    "FW.message=" + firmwareUploadMessage + "\n" +
    "WiFi.mode=" + getWifiMode() + "\n" +
    "WiFi.ip=" + wifiIpAddress + "\n" +
    "WiFi.status=" + wifiStatus + "\n" +
    "Config.restartPending=" + String(configRestartPending ? 1 : 0) + "\n");
}

void setWiFiStatus(const String& status) {
  wifiStatus = status;
  wifiStatusMillis = millis();
}

void registerWebRoutes() {
  static const char* extraHeaders[] = {"X-Baud"};
  server.collectHeaders(extraHeaders, 1);
  server.on("/", handleClientRequests);
  server.on("/gcode/add", HTTP_POST, handleGcodeAdd);
  server.on("/gcode/list", HTTP_GET, handleGcodeList);
  server.on("/gcode/get", HTTP_GET, handleGcodeGet);
  server.on("/gcode/remove", HTTP_POST, handleGcodeRemove);
  server.on("/config", HTTP_GET, handleConfigGet);
  server.on("/config", HTTP_POST, handleConfigSave);
  server.on("/config/reset", HTTP_POST, handleConfigReset);
  server.on("/keyboard-config", HTTP_GET, handleKeyboardConfigGet);
  server.on("/keyboard-config", HTTP_POST, handleKeyboardConfigSave);
  server.on("/keyboard-config/reset", HTTP_POST, handleKeyboardConfigReset);
  server.on("/keyboard-capture", HTTP_POST, handleKeyboardCapture);
  server.on("/wifi", HTTP_GET, handleWifiGet);
  server.on("/wifi", HTTP_POST, handleWifiSave);
  server.on("/wifi/reset", HTTP_POST, handleWifiReset);
  server.on("/tft/upload", HTTP_POST, handleTftUploadResult, handleTftUpload);
  server.on("/firmware/upload", HTTP_POST, handleFirmwareUploadResult, handleFirmwareUpload);
  server.on("/status", HTTP_GET, handleStatus);
}

String getStationWifiError() {
  if (WiFi.status() == WL_NO_SSID_AVAIL) return "Nessun SSID";
  if (WiFi.status() == WL_CONNECT_FAILED) return "WiFi fallito";
  if (WiFi.status() == WL_CONNECTION_LOST) return "WiFi perso";
  if (WiFi.status() == WL_DISCONNECTED) return "WiFi scollegato";
  return "Errore WiFi";
}

bool connectStationWifi() {
  wifiSetupApActive = false;
  wifiStationConnected = false;
  wifiIpAddress = "";

  if (WIFI_SSID.length() == 0) {
    setWiFiStatus("Nessun SSID");
    return false;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID.c_str(), WIFI_PASSWORD.c_str());
  setWiFiStatus("Connessione");
  for (int i = 0; i < 40; i++) {
    if (WiFi.status() == WL_CONNECTED) break;
    DELAY(500);
    taskYIELD();
  }
  if (WiFi.status() != WL_CONNECTED) {
    setWiFiStatus(getStationWifiError());
    return false;
  }

  wifiStationConnected = true;
  wifiIpAddress = WiFi.localIP().toString();
  setWiFiStatus("IP " + wifiIpAddress);
  Serial.print("Web UI: http://");
  Serial.println(wifiIpAddress);
  return true;
}

bool startSetupAccessPoint() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP);
  wifiSetupApActive = WiFi.softAP(WIFI_SETUP_AP_SSID, WIFI_SETUP_AP_PASSWORD);
  wifiStationConnected = false;
  if (!wifiSetupApActive) {
    wifiIpAddress = "";
    setWiFiStatus("AP WiFi fallito");
    return false;
  }

  wifiIpAddress = WiFi.softAPIP().toString();
  setWiFiStatus("Setup " + wifiIpAddress);
  Serial.print("Setup AP: ");
  Serial.print(WIFI_SETUP_AP_SSID);
  Serial.print(" / ");
  Serial.println(WIFI_SETUP_AP_PASSWORD);
  Serial.print("Web UI: http://");
  Serial.println(wifiIpAddress);
  return true;
}

void taskWiFi(void *param) {
  if (!connectStationWifi() && !startSetupAccessPoint()) {
    vTaskDelete(NULL);
    return;
  }

  initBuffer(&inBuffer, 1024);
  initBuffer(&outBuffer, 1024);
  webBuffersReady = true;

  registerWebRoutes();
  server.begin();

  webSocket.begin();
  webSocket.onEvent(handleWebSocketEvent);

  while (emergencyStop == ESTOP_NONE) {
    server.handleClient();
    webSocket.loop();
    if (wifiStationConnected && WiFi.status() != WL_CONNECTED) {
      requestWebUiMoveRelease();
      webSocketClientCount = 0;
      wifiStationConnected = false;
      wifiIpAddress = "";
      setWiFiStatus("WiFi perso");
    }
    if (firmwareUploadRestartPending && ((long)(millis() - firmwareUploadRestartAt) >= 0)) {
      firmwareUploadLog("riavvio in corso");
      DELAY(50);
      ESP.restart();
    }
    if (configRestartPending && ((long)(millis() - configRestartAt) >= 0)) {
      Serial.println("Configurazione macchina salvata, riavvio in corso");
      DELAY(50);
      ESP.restart();
    }

    if (bufferAvailable(&outBuffer)) {
      String outData = "";
      while (bufferAvailable(&outBuffer)) {
        outData += shiftBuffer(&outBuffer);
      }
      webSocket.broadcastTXT(outData);
    }
    taskYIELD();
  }
  vTaskDelete(NULL);
}

void setAsyncTimerEnable(bool value) {
  if (value) {
    timerStart(async_timer);
  } else {
    timerStop(async_timer);
  }
}

void setEmergencyStop(int kind) {
  emergencyStop = kind;
  setAsyncTimerEnable(false);
  xSemaphoreTake(z.mutex, 10);
  xSemaphoreTake(x.mutex, 10);
  xSemaphoreTake(y.mutex, 10);
}

void updateEnable(Axis* a) {
  if (!a->disabled && (!a->needsRest || a->stepperEnableCounter > 0)) {
    digitalWrite(a->ena, a->invertEnable ? LOW : HIGH);
    // Stepper driver needs some time before it will react to pulses.
    DELAY(STEPPED_ENABLE_DELAY_MS);
  } else {
    digitalWrite(a->ena, a->invertEnable ? HIGH : LOW);
  }
}

void stepperEnable(Axis* a, bool value) {
  if (!a->needsRest || !a->active) {
    return;
  }
  if (value) {
    a->stepperEnableCounter++;
    if (a->stepperEnableCounter == 1) {
      updateEnable(a);
    }
  } else if (a->stepperEnableCounter > 0) {
    a->stepperEnableCounter--;
    if (a->stepperEnableCounter == 0) {
      updateEnable(a);
    }
  }
}

void markAxisOrigin(Axis* a) {
  bool hasSemaphore = xSemaphoreTake(a->mutex, 10) == pdTRUE;
  if (!hasSemaphore) {
    beepFlag = true;
  }
  if (a->leftStop != LONG_MAX) {
    a->leftStop -= a->pos;
  }
  if (a->rightStop != LONG_MIN) {
    a->rightStop -= a->pos;
  }
  a->motorPos -= a->pos;
  a->originPos += a->pos;
  a->pos = 0;
  a->fractionalPos = 0;
  a->pendingPos = 0;
  if (hasSemaphore) {
    xSemaphoreGive(a->mutex);
  }
}

void zeroSpindlePos() {
  spindlePos = 0;
  spindlePosAvg = 0;
  spindlePosSync = 0;
}

// Lose the thread and mark current physical positions of
// encoder and stepper as a new 0. To be called when pitch magnitude
// changes or ELS is turned on/off. Without this, changing dupr will
// result in stepper rushing across the lathe to the new position.
// Must be called while holding motionMutex.
void markOrigin() {
  markAxisOrigin(&z);
  markAxisOrigin(&x);
  markAxisOrigin(&y);
  zeroSpindlePos();
}

void markAxis0(Axis* a) {
  a->originPos = -a->pos;
}

void tftAutoOpenWorkPage();
bool tftIsWorkMode();

void setIsOnFromTask(bool on) {
  nextIsOn = on;
  nextIsOnFlag = true;
}

void setIsOnFromLoop(bool on) {
  if (isOn && on) {
    return;
  }
  bool joystickMode = mode == MODE_JOYSTICK;
  if (!on) {
    isOn = false;
    setupIndex = 0;
  }
  stepperEnable(&z, on);
  stepperEnable(&x, on);
  stepperEnable(&y, on);
  if (joystickMode) {
    cancelJoystickLatheSync();
    resetJoystickLatheFeedPosition();
  } else {
    markOrigin();
  }
  if (on) {
    if (mode == MODE_ASYNC || mode == MODE_Y) {
      updateAsyncTimerSettings();
    }
    isOn = true;
    opDuprSign = dupr >= 0 ? 1 : -1;
    opDupr = dupr;
    opIndex = 0;
    opIndexAdvanceFlag = false;
    opSubIndex = 0;
    setupIndex = 0;
    if (tftIsWorkMode()) tftAutoOpenWorkPage();
  }
}

int getApproxRpm() {
  unsigned long t = micros();
  unsigned long elapsedTime = t - spindleEncTime;
  if (elapsedTime > 50000) {
    // RPM less than 10.
    spindleEncTimeDiffBulk = 0;
    return 0;
  }
  int rpm = 0;
  if (spindleEncTimeDiffBulk > 0) {
    rpm = 60000000 / spindleEncTimeDiffBulk;
    if (abs(rpm - shownRpm) > (rpm < 1000 ? 3 : 5)) {
      // Don't update RPM with insignificant differences.
      shownRpm = rpm;
      shownRpmTime = t;
    }
  }
  return rpm;
}

bool stepperIsRunning(Axis* a) {
  return micros() - a->stepStartUs < 50000;
}

void toScreen(const String &command) {
  if (tftUploadActive) return;
  writeNextionCommandRaw(command);
}

// Returns number of letters printed.
String printDeciMicrons(long deciMicrons, int precisionPointsMax) {
  if (deciMicrons == 0) {
    return "0";
  }
  bool imperial = measure != MEASURE_METRIC;
  long v = imperial ? round(deciMicrons / 25.4) : deciMicrons;
  int points = 0;
  if (v == 0 && precisionPointsMax >= 5) {
    points = 5;
  } else if ((v % 10) != 0 && precisionPointsMax >= 4) {
    points = 4;
  } else if ((v % 100) != 0 && precisionPointsMax >= 3) {
    points = 3;
  } else if ((v % 1000) != 0 && precisionPointsMax >= 2) {
    points = 2;
  } else if ((v % 10000) != 0 && precisionPointsMax >= 1) {
    points = 1;
  }
  return String(deciMicrons / (imperial ? 254000.0 : 10000.0), points);
}

String printDegrees(long degrees10000) {
  int points = 0;
  if ((degrees10000 % 100) != 0) {
    points = 3;
  } else if ((degrees10000 % 1000) != 0) {
    points = 2;
  } else if ((degrees10000 % 10000) != 0) {
    points = 1;
  }
  return String(degrees10000 / 10000.0, points) + char(223); // degree symbol
}

String printDupr(long value) {
  if (measure != MEASURE_TPI || value == 0) return printDeciMicrons(value, 5);

  float tpi = 254000.0 / value;
  String result = "";
  if (abs(tpi - round(tpi)) < TPI_ROUND_EPSILON) {
    result = String(int(round(tpi)));
  } else {
    int tpi100 = round(tpi * 100);
    int points = 0;
    if ((tpi100 % 10) != 0) {
      points = 2;
    } else if ((tpi100 % 100) != 0) {
      points = 1;
    }
    result = String(tpi, points);
  }
  return result;
}

long stepsToDu(Axis* a, long steps) {
  return round(steps * a->screwPitch / a->motorSteps);
}

long duToSteps(Axis* a, long du) {
  return round(du * a->motorSteps / a->screwPitch);
}

long getAxisPosDu(Axis* a) {
  return stepsToDu(a, a->pos + a->originPos);
}

long getAxisStopDiffDu(Axis* a) {
  if (a->leftStop == LONG_MAX || a->rightStop == LONG_MIN) return 0;
  return stepsToDu(a, a->leftStop - a->rightStop);
}

String printAxisPos(Axis* a) {
  if (a->rotational) return printDegrees(getAxisPosDu(a));
  return printDeciMicrons(getAxisPosDu(a), 3);
}

long getAxisLeftStopDistanceDu(Axis* a) {
  return stepsToDu(a, a->leftStop - a->pos);
}

String printDistanceToLeftStop(Axis* a) {
  if (a->leftStop == LONG_MAX) return "";
  if (a->rotational) return printDegrees(getAxisLeftStopDistanceDu(a));
  return printDeciMicrons(getAxisLeftStopDistanceDu(a), 3);
}

long getAxisRightStopDistanceDu(Axis* a) {
  return stepsToDu(a, a->pos - a->rightStop);
}

String printDistanceToRightStop(Axis* a) {
  if (a->rightStop == LONG_MIN) return "";
  if (a->rotational) return printDegrees(getAxisRightStopDistanceDu(a));
  return printDeciMicrons(getAxisRightStopDistanceDu(a), 3);
}

String printAxisStopDiff(Axis* a, bool addTrailingSpace) {
  String result = "";
  if (a->rotational) {
    result = printDegrees(getAxisStopDiffDu(a));
  } else {
    result = printDeciMicrons(getAxisStopDiffDu(a), 3);
  }
  return addTrailingSpace ? result + ' ' : result;
}

String printNoTrailing0(float value) {
  long v = round(value * 100000);
  int points = 0;
  if ((v % 10) != 0) {
    points = 5;
  } else if ((v % 100) != 0) {
    points = 4;
  } else if ((v % 1000) != 0) {
    points = 3;
  } else if ((v % 10000) != 0) {
    points = 2;
  } else if ((v % 100000) != 0) {
    points = 1;
  }
  return String(value, points);
}

String joystickLatheDirectionText(int zDirection, int xDirection) {
  String result = "";
  if (zDirection > 0) result += "Carro sx";
  else if (zDirection < 0) result += "Carro dx";
  if (xDirection != 0) {
    if (result != "") result += " ";
    result += (xDirection > 0 ? "Trasv. dentro" : "Trasv. fuori");
  }
  return result;
}

bool needZStops() {
  return mode == MODE_TURN || mode == MODE_FACE || mode == MODE_THREAD || mode == MODE_ELLIPSE || mode == MODE_SLOT;
}

bool isPassMode() {
  return mode == MODE_TURN || mode == MODE_FACE || mode == MODE_CUT || mode == MODE_THREAD || mode == MODE_ELLIPSE || mode == MODE_SLOT;
}

bool isGearboxMode() {
  return mode == MODE_NORMAL || mode == MODE_XGEAR;
}

bool manualMovesAllowedWhenOn() {
  return isGearboxMode() || mode == MODE_ASYNC || mode == MODE_CONE || mode == MODE_Y || mode == MODE_JOYSTICK;
}

bool manualMovesIgnoredWhenOn() {
  return mode == MODE_GCODE || isPassMode();
}

bool joystickPitchAdjustmentAllowed() {
  if (mode == MODE_GCODE) return false;
  if (!isOn) return true;
  return mode != MODE_THREAD && mode != MODE_ELLIPSE;
}

int getJoystickPitchStatusDirection() {
  int direction = joystickPitchAdjustDirection;
  if (direction != 0) return direction;
  if (millis() - joystickPitchStatusMillis < JOYSTICK_PITCH_STATUS_HOLD_MS) {
    return joystickPitchStatusDirection;
  }
  return 0;
}

int getLastSetupIndex() {
  if (mode == MODE_CONE || mode == MODE_GCODE) return 2;
  if (mode == MODE_THREAD) return 4;
  if (mode == MODE_TURN || mode == MODE_FACE || mode == MODE_CUT || mode == MODE_ELLIPSE || mode == MODE_SLOT) return 3;
  return 0;
}

Axis* getPitchAxis() {
  return (mode == MODE_FACE || mode == MODE_XGEAR) ? &x : &z;
}

bool isGearboxManualMove(Axis* a) {
  return isGearboxMode() && a == getPitchAxis();
}

long getPassModeZStart() {
  if (mode == MODE_TURN || mode == MODE_THREAD) return dupr > 0 ? z.rightStop : z.leftStop;
  if (mode == MODE_SLOT) return z.rightStop;
  if (mode == MODE_FACE) return auxForward ? z.rightStop : z.leftStop;
  if (mode == MODE_ELLIPSE) return dupr > 0 ? z.leftStop : z.rightStop;
  return z.pos;
}

long getPassModeXStart() {
  if (mode == MODE_TURN || mode == MODE_THREAD) return auxForward ? x.rightStop : x.leftStop;
  if (mode == MODE_SLOT) return auxForward ? x.rightStop : x.leftStop;
  if (mode == MODE_FACE || mode == MODE_CUT) return dupr > 0 ? x.rightStop : x.leftStop;
  if (mode == MODE_ELLIPSE) return x.rightStop;
  return x.pos;
}

long getNumpadResult() {
  long result = 0;
  for (int i = 0; i < numpadIndex; i++) {
    result = result * 10 + numpadDigits[i];
  }
  return result;
}

float numpadToConeRatio() {
  return getNumpadResult() / 100000.0;
}

long numpadToDeciMicrons() {
  long result = getNumpadResult();
  if (result == 0) {
    return 0;
  }
  if (measure == MEASURE_INCH) {
    result = result * 254;
  } else if (measure == MEASURE_TPI) {
    result = round(254000.0 / result);
  } else { // Metric
    result = result * 10;
  }
  return result;
}

long spindleModulo(long value) {
  value = value % ENCODER_STEPS_INT;
  if (value < 0) {
    value += ENCODER_STEPS_INT;
  }
  return value;
}

bool removeAllGcode() {
  File root = LittleFS.open("/");
  if (!root || !root.isDirectory()) {
    writeBuffer(&outBuffer, "error: failed to open directory\n");
    return false;
  }

  File file = root.openNextFile();
  while (file) {
    String path = file.path();
    file.close(); // can't remove while open
    if (path.endsWith(".gcode")) {
      if (!LittleFS.remove(path)) {
        writeBuffer(&outBuffer, "error: failed to delete " + path + "\n");
      }
    }
    file = root.openNextFile();
  }

  gcodeProgramCount = getGcodeProgramCount();
  return true;
}

String getCurrentGcodeProgramName() {
  File root = LittleFS.open("/");
  if (!root || !root.isDirectory()) {
    writeBuffer(&outBuffer, "error: failed to open directory\n");
    return "";
  }

  int count = 0;
  File file = root.openNextFile();
  while (file) {
    String filename = file.name();
    file.close();
    if (filename.endsWith(".gcode")) {
      if (count == gcodeProgramIndex) {
        return filename.substring(0, filename.length() - 6);
      }
      count++;
    }
    file = root.openNextFile();
  }

  return "";
}

String printMode() {
  if (mode == MODE_NORMAL) return "INGR.";
  if (mode == MODE_XGEAR) return "X-ING";
  if (mode == MODE_ASYNC) return "ASINC.";
  if (mode == MODE_CONE) return "CONO";
  if (mode == MODE_TURN) return "TORN.";
  if (mode == MODE_FACE) return "SPIAN.";
  if (mode == MODE_CUT) return "TRONC.";
  if (mode == MODE_SLOT) return "SCAN.";
  if (mode == MODE_THREAD) return "FILETT.";
  if (mode == MODE_ELLIPSE) return "ELLIS.";
  if (mode == MODE_GCODE) return "G-CODE";
  if (mode == MODE_Y) return "ASSE Y";
  if (mode == MODE_JOYSTICK) return "JOY";
  return "";
}

unsigned long lastDisplayUpdateTime = 0;
const unsigned long NEXTION_UPDATE_INTERVAL_MS = 100;
const unsigned long NEXTION_WEB_UPDATE_INTERVAL_MS = 200;

bool webUiIsConnected() {
  return webSocketClientCount > 0;
}

unsigned long getDisplayUpdateIntervalMs() {
  return webUiIsConnected() ? NEXTION_WEB_UPDATE_INTERVAL_MS : NEXTION_UPDATE_INTERVAL_MS;
}

String buildDisplayMessage(int rpm, long numpadResult, bool spindleStopped, int pitchStatusDirection) {
  String result = "";
  if (mode != MODE_JOYSTICK && pitchStatusDirection > 0) {
    result = "Passo +";
  } else if (mode != MODE_JOYSTICK && pitchStatusDirection < 0) {
    result = "Passo -";
  } else if (mode == MODE_GCODE) {
    if (setupIndex == 1 && gcodeProgramCount == 0) {
      result = "Nessun programma";
    } else if (setupIndex == 1) {
      if (gcodeProgramIndex >= gcodeProgramCount) {
        result = "Programma eliminato";
      } else {
        result = getCurrentGcodeProgramName();
      }
    } else if (setupIndex == 2) {
      if (spindleStopped) result = "Accendi il mandrino!";
      else result = "Mandrino ON. Vai?";
    } else if (isOn) {
      result = gcodeCommand.substring(0, 20);
    }
  } else if (isPassMode()) {
    bool missingZStops = needZStops() && (z.leftStop == LONG_MAX || z.rightStop == LONG_MIN);
    bool missingStops = missingZStops || x.leftStop == LONG_MAX || x.rightStop == LONG_MIN;
    if (!inNumpad && missingStops) {
      result = needZStops() ? "Imposta finecorsa" : "Imposta finecorsa X";
    } else if (numpadResult != 0 && setupIndex == 1) {
      long passes = min(PASSES_MAX, numpadResult);
      result = String(passes);
      if (passes == 1) result += " passata?";
      else result += " passate?";
    } else if (!isOn && setupIndex == 1) {
      result = String(turnPasses);
      if (turnPasses == 1) result += " passata?";
      else result += " passate?";
    } else if (!isOn && setupIndex == 2) {
      if (mode == MODE_FACE) {
        result = auxForward ? "Da destra a sinistra?" : "Da sinistra a destra?";
      } else if (mode == MODE_CUT) {
        result = dupr >= 0 ? "Passo > 0, esterno" : "Passo < 0, interno";
      } else {
        result = auxForward ? "Esterno?" : "Interno?";
      }
    } else if (mode == MODE_THREAD && !isOn && setupIndex == 3) {
      float ratio = numpadResult != 0 ? numpadToConeRatio() : coneRatio;
      result = "Rapporto cono " + String(ratio, 5) + "?";
    } else if (!isOn && setupIndex == getLastSetupIndex()) {
      long zOffset = getPassModeZStart() - z.pos;
      long xOffset = getPassModeXStart() - x.pos;
      result = "Vai";
      if (zOffset != 0) {
        result += " ";
        result += z.name;
        result += printDeciMicrons(stepsToDu(&z, zOffset), 2);
      }
      if (xOffset != 0) {
        result += " ";
        result += x.name;
        result += printDeciMicrons(stepsToDu(&x, xOffset), 2);
      }
      result += "?";
    } else if (mode == MODE_SLOT && isOn && dupr == 0 && !inNumpad) {
      result = "Imposta passo";
    } else if (isOn && numpadResult == 0) {
      result = "Passata " + String(opIndex) + " di " + String(max(opIndex, long(turnPasses * starts)));
    }
  } else if (mode == MODE_CONE) {
    if (!isOn && setupIndex == 1) result = "Usa " + coneRatioText() + "?";
    else if (!isOn && setupIndex == 2) result = auxForward ? "Esterno?" : "Interno?";
    else if (!isOn && setupIndex == 3) result = "Vai?";
    else if (isOn && numpadResult == 0) result = "Rapporto " + coneRatioText();
  } else if (mode == MODE_JOYSTICK && !inNumpad) {
    String directionText = joystickLatheDirectionText(joystickLatheDirectionZ, joystickLatheDirectionX);
    if (!JOYSTICK_ENABLED) result = "Joystick disattivato";
    else if (!joystickAvailable) result = joystickStartupWarning.length() > 0 ? joystickStartupWarning : "Joystick non collegato";
    else if (joystickLatheRapid && directionText != "") {
      result = "Rapido ";
      result += directionText;
    } else if (spindlePosSync != 0 && directionText != "") {
      result = "Sincro ";
      result += directionText;
    } else if (pitchStatusDirection > 0) result = "Passo +";
    else if (pitchStatusDirection < 0) result = "Passo -";
    else if (!isOn && directionText != "") {
      result = "Jog ";
      result += directionText;
    } else if (dupr == 0) result = "Imposta passo";
    else if (!isOn) result = "Avanzamento off";
    else if (directionText != "") {
      result = "Avanzamento ";
      result += directionText;
    } else result = "Avanzamento fermo";
  }

  if (inNumpad && result == "") result = "Usa " + printDupr(numpadToDeciMicrons()) + "?";

  if (result == "" && (millis() - wifiStatusMillis < 7000 || !x.active || x.disabled)) result = wifiStatus;

  if (result == "" && x.active && !x.disabled) result = "Diametro " + printDeciMicrons(abs(2 * getAxisPosDu(&x)), 2);

  return result;
}

String webSafeText(const String& value) {
  String result = "";
  result.reserve(value.length());
  for (int i = 0; i < value.length(); i++) {
    byte c = byte(value.charAt(i));
    if (c == 223) {
      // skip
    } else if (c >= 32 && c <= 126) {
      result += char(c);
    } else {
      result += "?";
    }
  }
  return result;
}

void appendUiLine(String* response, const char* name, const String& value) {
  appendConfigLine(response, name, webSafeText(value));
}

void publishMachineStatus(const String& status, const String& modeText, const String& pitchText, const String& measureText,
    const String& stepText, const String& rpmText, const String& turnsText, const String& angleText,
    const String& xText, const String& xLeftText, const String& xRightText,
    const String& yText, const String& yLeftText, const String& yRightText,
    const String& zText, const String& zLeftText, const String& zRightText, const String& messageText) {
  if (!webBuffersReady || !webUiIsConnected()) return;

  String response = "";
  response.reserve(520);
  appendUiLine(&response, "UI.status", status);
  appendUiLine(&response, "UI.mode", modeText);
  appendUiLine(&response, "UI.pitch", pitchText);
  appendUiLine(&response, "UI.measure", measureText);
  appendUiLine(&response, "UI.step", stepText);
  appendUiLine(&response, "UI.rpm", rpmText);
  appendUiLine(&response, "UI.turns", turnsText);
  appendUiLine(&response, "UI.angle", angleText);
  appendUiLine(&response, "UI.x", xText);
  appendUiLine(&response, "UI.xLeft", xLeftText);
  appendUiLine(&response, "UI.xRight", xRightText);
  appendUiLine(&response, "UI.y", yText);
  appendUiLine(&response, "UI.yLeft", yLeftText);
  appendUiLine(&response, "UI.yRight", yRightText);
  appendUiLine(&response, "UI.z", zText);
  appendUiLine(&response, "UI.zLeft", zLeftText);
  appendUiLine(&response, "UI.zRight", zRightText);
  appendUiLine(&response, "UI.message", messageText);

  if (!machineStatusForcePublish && response == lastMachineStatus) return;
  machineStatusForcePublish = false;
  lastMachineStatus = response;
  queueWebSocketText(response);
}

void tftServiceTick();
void tftDrawWorkUpdate();
void tftDrawWorkAll();
void tftDrawEmergency(const String &reason);
void tftKeypadOpenValue(uint8_t page, uint8_t kind, const String &text);
void tftPageLoaded(uint8_t page);

void updateDisplay() {
  if (tftUploadActive) return;
  tftServiceTick();
  if (millis() - lastDisplayUpdateTime < getDisplayUpdateIntervalMs()) return;
  lastDisplayUpdateTime = millis();
  bool publishStatus = webBuffersReady && webUiIsConnected();

  long newHashLine0 = isOn + spindlePosSync + mode + measure + dupr + starts;
  bool updateLine0 = lcdHashLine0 != newHashLine0;
  String statusText = "";
  String modeText = "";
  String pitchText = "";
  String measureText = "";
  if (updateLine0 || publishStatus) {
    statusText = spindlePosSync ? "SIN" : (isOn ? "ON" : "OFF");
    modeText = printMode();
    pitchText = printDupr(dupr);
    measureText = measure == MEASURE_INCH ? "POL" : measure == MEASURE_METRIC ? "MM" : "TPI";
  }
  if (updateLine0) {
    lcdHashLine0 = newHashLine0;
  }

  int rpm = getApproxRpm();
  long newHashLine1 = moveStep + rpm + spindlePos + measure;
  bool updateLine1 = lcdHashLine1 != newHashLine1;
  String stepText = "";
  String rpmText = "";
  String turnsText = "";
  String angleText = "";
  if (updateLine1 || publishStatus) {
    stepText = printDeciMicrons(moveStep, 5);
    rpmText = String(rpm);
    float turns = (float) abs(spindlePos) / ENCODER_STEPS_INT;
    turnsText = String(turns, turns < 100 ? 2 : (turns < 1000 ? 1 : 0));
    angleText = String(spindleModulo(spindlePos) * 360 / ENCODER_STEPS_FLOAT, 2) + String(char(223));
  }
  if (updateLine1) {
    lcdHashLine1 = newHashLine1;
  }

  long newHashLine2 =
    x.pos + x.originPos + x.disabled + x.leftStop - x.rightStop +
    z.pos + z.originPos + z.disabled + z.leftStop - z.rightStop +
    y.pos + y.originPos + y.disabled + y.leftStop - y.rightStop + measure + x.pos % 100;
  bool updateLine2 = lcdHashLine2 != newHashLine2;
  String xText = "";
  String xLeftText = "";
  String xRightText = "";
  String yText = "";
  String yLeftText = "";
  String yRightText = "";
  String zText = "";
  String zLeftText = "";
  String zRightText = "";
  if (updateLine2 || publishStatus) {
    xText = !x.active || x.disabled ? "" : printAxisPos(&x);
    xLeftText = !x.active || x.disabled ? "" : printDistanceToLeftStop(&x);
    xRightText = !x.active || x.disabled ? "" : printDistanceToRightStop(&x);
    yText = !y.active || y.disabled ? "" : printAxisPos(&y);
    yLeftText = !y.active || y.disabled ? "" : printDistanceToLeftStop(&y);
    yRightText = !y.active || y.disabled ? "" : printDistanceToRightStop(&y);
    zText = !z.active || z.disabled ? "" : printAxisPos(&z);
    zLeftText = !z.active || z.disabled ? "" : printDistanceToLeftStop(&z);
    zRightText = !z.active || z.disabled ? "" : printDistanceToRightStop(&z);
  }
  if (updateLine2) {
    lcdHashLine2 = newHashLine2;
  }

  long numpadResult = getNumpadResult();
  long gcodeCommandHash = 0;
  for (int i = 0; i < gcodeCommand.length(); i++) {
    gcodeCommandHash += gcodeCommand.charAt(i);
  }
  for (int i = 0; i < wifiStatus.length(); i++) {
    gcodeCommandHash += wifiStatus.charAt(i);
  }
  bool spindleStopped = micros() > spindleEncTime + 100000;
  int pitchStatusDirection = getJoystickPitchStatusDirection();
  long newHashLine3 = z.pos + (showAngle ? spindlePos : -1) + (showTacho ? rpm : -2) + measure + (numpadResult > 0 ? numpadResult : -1) + mode * 5 + dupr +
      (mode == MODE_CONE ? round(coneRatio * 10000) : 0) + turnPasses + opIndex + setupIndex + gcodeProgramIndex + gcodeProgramCount + spindleStopped * 3 + (isOn ? 139 : -117) + (inNumpad ? 10 : 0) + (auxForward ? 17 : -31) +
      (z.leftStop == LONG_MAX ? 123 : z.leftStop) + (z.rightStop == LONG_MIN ? 1234 : z.rightStop) +
      (x.leftStop == LONG_MAX ? 1235 : x.leftStop) + (x.rightStop == LONG_MIN ? 123456 : x.rightStop) + gcodeCommandHash +
      (mode == MODE_Y ? y.pos + y.originPos + (y.leftStop == LONG_MAX ? 123 : y.leftStop) + (y.rightStop == LONG_MIN ? 1234 : y.rightStop) + y.disabled : 0) +
      pitchStatusDirection * 149 +
      (mode == MODE_JOYSTICK ? joystickLatheDirectionZ * 97 + joystickLatheDirectionX * 101 + joystickLatheFeedSignZ * 131 + joystickLatheFeedSignX * 137 + joystickLatheRapid * 17 + JOYSTICK_ENABLED * 19 + spindlePosSync * 151 : 0) + x.pos + x.originPos + z.pos;
  bool updateLine3 = lcdHashLine3 != newHashLine3;
  String messageText = "";
  if (updateLine3 || publishStatus) {
    messageText = buildDisplayMessage(rpm, numpadResult, spindleStopped, pitchStatusDirection);
  }
  if (updateLine3) {
    lcdHashLine3 = newHashLine3;
  }

  if (publishStatus) {
    publishMachineStatus(statusText, modeText, pitchText, measureText, stepText, rpmText, turnsText, angleText,
      xText, xLeftText, xRightText, yText, yLeftText, yRightText, zText, zLeftText, zRightText, messageText);
  }
}

bool saveIfChanged() {
  // Should avoid calling Preferences whenever possible to reduce memory wear and avoid ~20ms write delay that blocks interrupts.
  if (dupr == savedDupr && starts == savedStarts && z.pos == z.savedPos && z.originPos == z.savedOriginPos && z.posGlobal == z.savedPosGlobal && z.motorPos == z.savedMotorPos && z.leftStop == z.savedLeftStop && z.rightStop == z.savedRightStop && z.disabled == z.savedDisabled &&
      spindlePos == savedSpindlePos && spindlePosAvg == savedSpindlePosAvg && spindlePosSync == savedSpindlePosSync && savedSpindlePosGlobal == spindlePosGlobal && showAngle == savedShowAngle && showTacho == savedShowTacho && moveStep == savedMoveStep &&
      mode == savedMode && measure == savedMeasure && x.pos == x.savedPos && x.originPos == x.savedOriginPos && x.posGlobal == x.savedPosGlobal && x.motorPos == x.savedMotorPos && x.leftStop == x.savedLeftStop && x.rightStop == x.savedRightStop && x.disabled == x.savedDisabled &&
      y.pos == y.savedPos && y.originPos == y.savedOriginPos && y.posGlobal == y.savedPosGlobal && y.motorPos == y.savedMotorPos && y.leftStop == y.savedLeftStop && y.rightStop == y.savedRightStop && y.disabled == y.savedDisabled &&
      coneRatio == savedConeRatio && turnPasses == savedTurnPasses && savedAuxForward == auxForward) return false;

  Preferences pref;
  pref.begin(PREF_NAMESPACE);
  if (dupr != savedDupr) pref.putLong(PREF_DUPR, savedDupr = dupr);
  if (starts != savedStarts) pref.putInt(PREF_STARTS, savedStarts = starts);
  if (z.pos != z.savedPos) pref.putLong(PREF_POS_Z, z.savedPos = z.pos);
  if (z.posGlobal != z.savedPosGlobal) pref.putLong(PREF_POS_GLOBAL_Z, z.savedPosGlobal = z.posGlobal);
  if (z.originPos != z.savedOriginPos) pref.putLong(PREF_ORIGIN_POS_Z, z.savedOriginPos = z.originPos);
  if (z.motorPos != z.savedMotorPos) pref.putLong(PREF_MOTOR_POS_Z, z.savedMotorPos = z.motorPos);
  if (z.leftStop != z.savedLeftStop) pref.putLong(PREF_LEFT_STOP_Z, z.savedLeftStop = z.leftStop);
  if (z.rightStop != z.savedRightStop) pref.putLong(PREF_RIGHT_STOP_Z, z.savedRightStop = z.rightStop);
  if (z.disabled != z.savedDisabled) pref.putBool(PREF_DISABLED_Z, z.savedDisabled = z.disabled);
  if (spindlePos != savedSpindlePos) pref.putLong(PREF_SPINDLE_POS, savedSpindlePos = spindlePos);
  if (spindlePosAvg != savedSpindlePosAvg) pref.putLong(PREF_SPINDLE_POS_AVG, savedSpindlePosAvg = spindlePosAvg);
  if (spindlePosSync != savedSpindlePosSync) pref.putInt(PREF_OUT_OF_SYNC, savedSpindlePosSync = spindlePosSync);
  if (spindlePosGlobal != savedSpindlePosGlobal) pref.putLong(PREF_SPINDLE_POS_GLOBAL, savedSpindlePosGlobal = spindlePosGlobal);
  if (showAngle != savedShowAngle) pref.putBool(PREF_SHOW_ANGLE, savedShowAngle = showAngle);
  if (showTacho != savedShowTacho) pref.putBool(PREF_SHOW_TACHO, savedShowTacho = showTacho);
  if (moveStep != savedMoveStep) pref.putLong(PREF_MOVE_STEP, savedMoveStep = moveStep);
  if (mode != savedMode) pref.putInt(PREF_MODE, savedMode = mode);
  if (measure != savedMeasure) pref.putInt(PREF_MEASURE, savedMeasure = measure);
  if (x.pos != x.savedPos) pref.putLong(PREF_POS_X, x.savedPos = x.pos);
  if (x.posGlobal != x.savedPosGlobal) pref.putLong(PREF_POS_GLOBAL_X, x.savedPosGlobal = x.posGlobal);
  if (x.originPos != x.savedOriginPos) pref.putLong(PREF_ORIGIN_POS_X, x.savedOriginPos = x.originPos);
  if (x.motorPos != x.savedMotorPos) pref.putLong(PREF_MOTOR_POS_X, x.savedMotorPos = x.motorPos);
  if (x.leftStop != x.savedLeftStop) pref.putLong(PREF_LEFT_STOP_X, x.savedLeftStop = x.leftStop);
  if (x.rightStop != x.savedRightStop) pref.putLong(PREF_RIGHT_STOP_X, x.savedRightStop = x.rightStop);
  if (x.disabled != x.savedDisabled) pref.putBool(PREF_DISABLED_X, x.savedDisabled = x.disabled);
  if (y.pos != y.savedPos) pref.putLong(PREF_POS_Y, y.savedPos = y.pos);
  if (y.posGlobal != y.savedPosGlobal) pref.putLong(PREF_POS_GLOBAL_Y, y.savedPosGlobal = y.posGlobal);
  if (y.originPos != y.savedOriginPos) pref.putLong(PREF_ORIGIN_POS_Y, y.savedOriginPos = y.originPos);
  if (y.motorPos != y.savedMotorPos) pref.putLong(PREF_MOTOR_POS_Y, y.savedMotorPos = y.motorPos);
  if (y.leftStop != y.savedLeftStop) pref.putLong(PREF_LEFT_STOP_Y, y.savedLeftStop = y.leftStop);
  if (y.rightStop != y.savedRightStop) pref.putLong(PREF_RIGHT_STOP_Y, y.savedRightStop = y.rightStop);
  if (y.disabled != y.savedDisabled) pref.putBool(PREF_DISABLED_Y, y.savedDisabled = y.disabled);
  if (coneRatio != savedConeRatio) pref.putFloat(PREF_CONE_RATIO, savedConeRatio = coneRatio);
  if (turnPasses != savedTurnPasses) pref.putInt(PREF_TURN_PASSES, savedTurnPasses = turnPasses);
  if (auxForward != savedAuxForward) pref.putBool(PREF_AUX_FORWARD, savedAuxForward = auxForward);
  pref.end();
  return true;
}

void beep() {
  toScreen("play 0,0,0");
}

void taskDisplay(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    updateDisplay();
    // Calling Preferences.commit() blocks all interrupts for 30ms, don't call saveIfChanged() if
    // encoder is likely to move soon.
    unsigned long now = micros();
    if (!stepperIsRunning(&z) && !stepperIsRunning(&x) && (now > spindleEncTime + SAVE_DELAY_US) && (now < saveTime || now > saveTime + SAVE_DELAY_US) && (now < keypadTimeUs || now > keypadTimeUs + SAVE_DELAY_US)) {
      if (saveIfChanged()) {
        saveTime = now;
      }
    }
    if (beepFlag) {
      beepFlag = false;
      beep();
    }
    if (abs(z.pendingPos) > z.estopSteps || abs(x.pendingPos) > x.estopSteps) {
      setEmergencyStop(ESTOP_POS);
    }
    taskYIELD();
  }
  String reason;
  if (emergencyStop == ESTOP_POS) {
    reason = "Posizione fuori macchina";
  } else if (emergencyStop == ESTOP_MARK_ORIGIN) {
    reason = "Impossibile segnare origine";
  } else if (emergencyStop == ESTOP_ON_OFF) {
    reason = "Impossibile ON/OFF";
  } else if (emergencyStop == ESTOP_OFF_MANUAL_MOVE) {
    reason = "Spento in manuale";
  } else {
    reason = "Arresto di emergenza";
  }
  tftDrawEmergency(reason);
  // The display task dies here: push the state once, otherwise the web UI
  // keeps showing the last live values as if the machine were still running.
  queueWebSocketText(String("UI.status=ESTOP\nUI.message=") + webSafeText(reason) + "\n");
  vTaskDelete(NULL);
}

void setMeasure(int value) {
  if (measure == value) {
    return;
  }
  measure = value;
  moveStep = measure == MEASURE_METRIC ? MOVE_STEP_1 : MOVE_STEP_IMP_1;
}

void resetGcodeState() {
  gcodeCommand = "";
  gcodeFeedDuPerSec = GCODE_FEED_DEFAULT_DU_SEC;
  gcodeAbsolutePositioning = true;
  gcodeInBrace = false;
  gcodeInSemicolon = false;
  setMeasure(MEASURE_METRIC);
}

void waitForPendingPosNear0(Axis* a) {
  while (abs(a->pendingPos) > a->motorSteps / 3) {
    taskYIELD();
  }
}

void waitForPendingPos0(Axis* a) {
  while (a->pendingPos != 0) {
    taskYIELD();
  }
}

bool markOriginOrEmergencyStop() {
  if (xSemaphoreTake(motionMutex, 100) != pdTRUE) {
    setEmergencyStop(ESTOP_MARK_ORIGIN);
    return false;
  } else {
    markOrigin();
    xSemaphoreGive(motionMutex);
    return true;
  }
}

void resetJoystickLatheFeedPosition() {
  joystickLatheFeedSignZ = 0;
  joystickLatheFeedSignX = 0;
  joystickLathePitchZ = 0;
  joystickLathePitchX = 0;
  joystickLatheRebaseZAfterSync = false;
  joystickLatheRebaseXAfterSync = false;
}

void cancelJoystickLatheSync() {
  if (mode == MODE_JOYSTICK) {
    spindlePosSync = 0;
    joystickLatheSyncPitch = 0;
    joystickLatheRebaseZAfterSync = false;
    joystickLatheRebaseXAfterSync = false;
  }
}

bool joystickUsable() {
  return JOYSTICK_ENABLED && joystickAvailable;
}

void prepareJoystickLatheManualMove() {
  if (isOn && mode == MODE_JOYSTICK) {
    cancelJoystickLatheSync();
    resetJoystickLatheFeedPosition();
  }
}

bool isContinuousStep() {
  if (!ENABLE_CONTINUOUS_MOVE) return false;
  return moveStep == (measure == MEASURE_METRIC ? MOVE_STEP_1 : MOVE_STEP_IMP_1);
}

bool isRapidManualMove() {
  return joystickUsable() && joystickRapidPressed;
}

int joystickDirectionFromDeflection(float deflection) {
  return deflection > 0 ? 1 : (deflection < 0 ? -1 : 0);
}

JoystickAxisState* getJoystickAxisState(Axis* a) {
  for (int i = 0; i < JOYSTICK_AXIS_COUNT; i++) {
    if (joystickAxes[i].axis == a) return &joystickAxes[i];
  }
  return nullptr;
}

int getJoystickManualDirection(Axis* a) {
  JoystickAxisState* joystickAxis = getJoystickAxisState(a);
  return joystickAxis == nullptr ? 0 : joystickAxis->manualDirection;
}

long getJoystickManualSpeed(Axis* a) {
  JoystickAxisState* joystickAxis = getJoystickAxisState(a);
  return joystickAxis == nullptr ? 0 : joystickAxis->manualSpeed;
}

bool isJoystickManualMove(Axis* a) {
  return joystickUsable() && getJoystickManualDirection(a) != 0;
}

bool joystickManualMoveActive(Axis* a, int sign) {
  return joystickUsable() && getJoystickManualDirection(a) == sign;
}

bool pulseDeltaMatchesDirection(int pulseDelta, int sign) {
  return pulseDelta != 0 && (pulseDelta > 0 ? 1 : -1) == sign;
}

void addJoystickPulses(Axis* a, int delta);
int getAndResetPulses(Axis* a);

// Keep joystick jogs continuous between ADC samples so short task delays do not
// drain the step queue and force a new acceleration ramp.
int waitForNextJoystickPulseDelta(Axis* a, int sign) {
  if (!joystickManualMoveActive(a, sign)) return 0;
  unsigned long start = millis();
  unsigned long timeoutMs = min(100, max(10, JOYSTICK_SAMPLE_INTERVAL_MS * 3));
  while (emergencyStop == ESTOP_NONE && joystickManualMoveActive(a, sign) && millis() - start < timeoutMs) {
    int pulseDelta = getAndResetPulses(a);
    if (pulseDelta == 0) {
      DELAY(1);
      continue;
    }
    if (pulseDeltaMatchesDirection(pulseDelta, sign)) {
      if (a->speed < a->speedMax) {
        a->speed = a->speedMax;
      }
      return pulseDelta;
    }
    addJoystickPulses(a, pulseDelta);
    return 0;
  }
  return 0;
}

int waitForNextHandwheelPulseDelta(Axis* a) {
  unsigned long start = millis();
  while (emergencyStop == ESTOP_NONE && millis() - start < HANDWHEEL_PULSE_WAIT_MS) {
    int pulseDelta = getAndResetPulses(a);
    if (pulseDelta == 0) {
      DELAY(1);
      continue;
    }
    return pulseDelta;
  }
  return 0;
}

int waitForNextPulseMoveDelta(Axis* a, int sign) {
  if (joystickManualMoveActive(a, sign)) {
    return waitForNextJoystickPulseDelta(a, sign);
  }
  return waitForNextHandwheelPulseDelta(a);
}

// For rotational axis the moveStep of 0.1" means 0.1°.
long getMoveStepForAxis(Axis* a) {
  return (a->rotational && measure != MEASURE_METRIC) ? (moveStep / 25.4) : moveStep;
}

long getStepMaxSpeed(Axis* a) {
  long joystickSpeed = getJoystickManualSpeed(a);
  if (isJoystickManualMove(a) && joystickSpeed > 0) return joystickSpeed;
  return (isContinuousStep() || isRapidManualMove()) ? a->speedManualMove : min(long(a->speedManualMove), abs(getMoveStepForAxis(a)) * 1000 / STEP_TIME_MS);
}

long getManualMoveSpeedMax(Axis* a, bool pulseMove) {
  return pulseMove && !isJoystickManualMove(a) ? a->speedManualMove : getStepMaxSpeed(a);
}

void waitForStep(Axis* a) {
  if (isContinuousStep() || isRapidManualMove() || isJoystickManualMove(a)) {
    // Move continuously for default step.
    waitForPendingPosNear0(a);
  } else {
    // Move with tiny pauses allowing to stop precisely.
    a->continuous = false;
    waitForPendingPos0(a);
    DELAY(DELAY_BETWEEN_STEPS_MS);
  }
}

void waitForManualMoveStep(Axis* a, bool pulseMove) {
  if (pulseMove) waitForPendingPosNear0(a);
  else waitForStep(a);
}

volatile int* getJoystickPulseQueue(Axis* a) {
  JoystickAxisState* joystickAxis = getJoystickAxisState(a);
  return joystickAxis == nullptr ? nullptr : &joystickAxis->queuedPulses;
}

void addJoystickPulses(Axis* a, int delta) {
  if (delta == 0) return;
  volatile int* pulseQueue = getJoystickPulseQueue(a);
  if (pulseQueue == nullptr) return;
  portENTER_CRITICAL(&joystickPulseMux);
  int queued = *pulseQueue + delta;
  if (queued > JOYSTICK_PULSE_QUEUE_LIMIT) {
    queued = JOYSTICK_PULSE_QUEUE_LIMIT;
  } else if (queued < -JOYSTICK_PULSE_QUEUE_LIMIT) {
    queued = -JOYSTICK_PULSE_QUEUE_LIMIT;
  }
  *pulseQueue = queued;
  portEXIT_CRITICAL(&joystickPulseMux);
}

void clearJoystickPulses(JoystickAxisState* joystickAxis) {
  portENTER_CRITICAL(&joystickPulseMux);
  joystickAxis->queuedPulses = 0;
  portEXIT_CRITICAL(&joystickPulseMux);
}

void cancelPendingJoystickMove(JoystickAxisState* joystickAxis, int previousDirection) {
  if (previousDirection == 0) return;
  clearJoystickPulses(joystickAxis);
  joystickAxis->pulseFraction = 0;

  Axis* axis = joystickAxis->axis;
  if (xSemaphoreTake(axis->mutex, 10) != pdTRUE) return;
  int pendingDirection = axis->pendingPos > 0 ? 1 : (axis->pendingPos < 0 ? -1 : 0);
  if (pendingDirection == previousDirection) {
    axis->pendingPos = 0;
    axis->fractionalPos = 0;
    axis->continuous = false;
    axis->speed = axis->speedStart;
  }
  xSemaphoreGive(axis->mutex);
}

int getAndResetJoystickPulses(Axis* a) {
  volatile int* pulseQueue = getJoystickPulseQueue(a);
  if (pulseQueue == nullptr) return 0;
  portENTER_CRITICAL(&joystickPulseMux);
  int delta = *pulseQueue;
  *pulseQueue = 0;
  portEXIT_CRITICAL(&joystickPulseMux);
  return delta;
}

int applyAxisEncoderBacklash(Axis* a, int delta) {
  if (delta == 0) return 0;

  long previousPulsePosAvg = a->pulsePosAvg;
  a->pulsePos += delta;
  if (a->pulsePos > a->pulsePosAvg) {
    a->pulsePosAvg = a->pulsePos;
  } else if (a->pulsePos < a->pulsePosAvg - AXIS_ENCODER_BACKLASH) {
    a->pulsePosAvg = a->pulsePos + AXIS_ENCODER_BACKLASH;
  }
  return int(a->pulsePosAvg - previousPulsePosAvg);
}

int getAndResetPulses(Axis* a) {
  int joystickDelta = getAndResetJoystickPulses(a);
  pcnt_unit_handle_t unit = pulseUnits[a->pulseCounter];
  if (unit == nullptr) {
    return (isOn && manualMovesIgnoredWhenOn()) ? 0 : joystickDelta;
  }
  int count;
  pcnt_unit_get_count(unit, &count);
  int delta = count - a->pulseCount;
  if (isOn && manualMovesIgnoredWhenOn()) {
    applyAxisEncoderBacklash(a, delta);
    pcnt_unit_clear_count(unit);
    a->pulseCount = 0;
    return 0;
  }
  if (count >= PCNT_CLEAR || count <= -PCNT_CLEAR) {
    pcnt_unit_clear_count(unit);
    a->pulseCount = 0;
  } else {
    a->pulseCount = count;
  }
  int pulseDelta = applyAxisEncoderBacklash(a, delta);
  return pulseDelta + joystickDelta;
}

int readJoystickPin(int pin) {
  long total = 0;
  for (int i = 0; i < JOYSTICK_OVERSAMPLES; i++) {
    total += analogRead(pin);
  }
  return total / JOYSTICK_OVERSAMPLES;
}

int calibrateJoystickCenter(int pin) {
  long total = 0;
  for (int i = 0; i < JOYSTICK_CENTER_SAMPLES; i++) {
    total += readJoystickPin(pin);
    DELAY(2);
  }
  return total / JOYSTICK_CENTER_SAMPLES;
}

float getJoystickDeflection(JoystickAxisState* joystickAxis) {
  int raw = readJoystickPin(joystickAxis->pin);
  int rawDelta = raw - joystickAxis->center;
  int filteredDelta = joystickAxis->filtered - joystickAxis->center;
  if (*joystickAxis->invert) {
    rawDelta = -rawDelta;
    filteredDelta = -filteredDelta;
  }

  bool rawNeutral = abs(rawDelta) <= JOYSTICK_DEADBAND;
  bool filteredNeutral = abs(filteredDelta) <= JOYSTICK_DEADBAND;
  bool rawReversed = !rawNeutral && !filteredNeutral && ((rawDelta > 0) != (filteredDelta > 0));
  if (rawNeutral) {
    joystickAxis->filtered = joystickAxis->center;
  } else if (filteredNeutral || rawReversed) {
    joystickAxis->filtered = raw;
  } else {
    joystickAxis->filtered = (joystickAxis->filtered * 3 + raw) / 4;
  }

  int delta = joystickAxis->filtered - joystickAxis->center;
  if (*joystickAxis->invert) delta = -delta;
  int absDelta = abs(delta);
  if (absDelta <= JOYSTICK_DEADBAND) return 0;

  int range = delta > 0 ? JOYSTICK_ADC_MAX - joystickAxis->center : joystickAxis->center;
  range = max(1, range - JOYSTICK_DEADBAND);
  float normalized = (absDelta - JOYSTICK_DEADBAND) / float(range);
  if (normalized > 1.0) normalized = 1.0;
  float curved = normalized * normalized;
  return delta > 0 ? curved : -curved;
}

int getJoystickPulseDelta(JoystickAxisState* joystickAxis, unsigned long elapsedUs) {
  float revolutionsPerSecond = joystickRapidPressed ? JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND : JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND;
  joystickAxis->pulseFraction += joystickAxis->deflection * joystickAxis->axis->pulsePerRevolution * revolutionsPerSecond * elapsedUs / 1000000.0;
  int delta = int(joystickAxis->pulseFraction);
  joystickAxis->pulseFraction -= delta;
  return delta;
}

long getJoystickSpeedFromDeflection(JoystickAxisState* joystickAxis) {
  if (joystickAxis->deflection == 0) return 0;
  float revolutionsPerSecond = joystickRapidPressed ? JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND : JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND;
  long speed = round(abs(joystickAxis->deflection) * revolutionsPerSecond * joystickAxis->axis->motorSteps);
  if (speed < 1) speed = 1;
  return min(joystickAxis->axis->speedManualMove, speed);
}

void readJoystickAxis(JoystickAxisState* joystickAxis) {
  if (!joystickAxisEnabled(joystickAxis)) {
    joystickAxis->deflection = 0;
    joystickAxis->direction = 0;
    return;
  }
  joystickAxis->deflection = getJoystickDeflection(joystickAxis);
  joystickAxis->direction = joystickDirectionFromDeflection(joystickAxis->deflection);
}

void updateJoystickManualAxis(JoystickAxisState* joystickAxis, bool enabled, bool queueWhenNeutral, unsigned long elapsedUs) {
  int previousDirection = joystickAxis->manualDirection;
  joystickAxis->manualDirection = enabled ? joystickAxis->direction : 0;
  joystickAxis->manualSpeed = joystickAxis->manualDirection == 0 ? 0 : getJoystickSpeedFromDeflection(joystickAxis);
  if (previousDirection != 0 && previousDirection != joystickAxis->manualDirection) {
    cancelPendingJoystickMove(joystickAxis, previousDirection);
  }
  if (enabled && (queueWhenNeutral || joystickAxis->manualDirection != 0)) {
    addJoystickPulses(joystickAxis->axis, getJoystickPulseDelta(joystickAxis, elapsedUs));
  } else {
    joystickAxis->pulseFraction = 0;
  }
}

void resetJoystickAxisMotion(JoystickAxisState* joystickAxis) {
  int previousDirection = joystickAxis->manualDirection;
  joystickAxis->manualDirection = 0;
  joystickAxis->manualSpeed = 0;
  cancelPendingJoystickMove(joystickAxis, previousDirection);
  clearJoystickPulses(joystickAxis);
  joystickAxis->pulseFraction = 0;
}

bool joystickStartupCenterLooksNeutral(int center) {
  int midpoint = JOYSTICK_ADC_MAX / 2;
  int tolerance = max(JOYSTICK_DEADBAND, JOYSTICK_STARTUP_CENTER_TOLERANCE_MIN);
  return abs(center - midpoint) <= tolerance;
}

bool updateJoystickButton(bool rawPressed, bool moveNeutral) {
  unsigned long now = millis();
  if (rawPressed != joystickButtonRawPressed) {
    joystickButtonRawPressed = rawPressed;
    joystickButtonRawChangeMillis = now;
  }

  if (rawPressed != joystickButtonPressed && now - joystickButtonRawChangeMillis >= JOYSTICK_BUTTON_DEBOUNCE_MS) {
    joystickButtonPressed = rawPressed;
    if (joystickButtonPressed) {
      joystickButtonPressMillis = now;
      joystickButtonToggleBlocked = mode != MODE_JOYSTICK || !moveNeutral;
    } else {
      bool shortClick = now - joystickButtonPressMillis <= JOYSTICK_BUTTON_TOGGLE_MAX_MS;
      if (JOYSTICK_BUTTON_TOGGLES_ON_OFF && mode == MODE_JOYSTICK && moveNeutral && shortClick && !joystickButtonToggleBlocked) {
        buttonOnOffPress(!isOn);
      }
      joystickButtonToggleBlocked = false;
    }
  }

  if (joystickButtonPressed && (mode != MODE_JOYSTICK || !moveNeutral || now - joystickButtonPressMillis > JOYSTICK_BUTTON_TOGGLE_MAX_MS)) {
    joystickButtonToggleBlocked = true;
  }

  return joystickButtonPressed;
}

void initJoystick() {
  joystickAvailable = false;
  joystickStartupWarning = "";
  if (!JOYSTICK_ENABLED) return;
  if (!anyJoystickAxisEnabled()) return;
  analogReadResolution(12);
  for (int i = 0; i < JOYSTICK_AXIS_COUNT; i++) {
    if (!joystickAxisEnabled(&joystickAxes[i])) continue;
    pinMode(joystickAxes[i].pin, INPUT_PULLDOWN);
  }
  pinMode(JOY_BUTTON, INPUT_PULLUP);

  for (int i = 0; i < JOYSTICK_AXIS_COUNT; i++) {
    if (!joystickAxisEnabled(&joystickAxes[i])) continue;
    joystickAxes[i].center = calibrateJoystickCenter(joystickAxes[i].pin);
    if (!joystickStartupCenterLooksNeutral(joystickAxes[i].center)) {
      int offset = joystickAxes[i].center - JOYSTICK_ADC_MAX / 2;
      char axisName = i == JOYSTICK_AXIS_Z ? NAME_Z : (i == JOYSTICK_AXIS_X ? NAME_X : NAME_Y);
      joystickStartupWarning = "Joy ";
      joystickStartupWarning += axisName;
      joystickStartupWarning += (offset >= 0 ? " +" : " -");
      joystickStartupWarning += String(max(0, abs(offset) - JOYSTICK_DEADBAND));
      joystickStartupWarning += " oltre zona morta";
      return;
    }
  }

  for (int i = 0; i < JOYSTICK_AXIS_COUNT; i++) {
    if (!joystickAxisEnabled(&joystickAxes[i])) {
      joystickAxes[i].center = JOYSTICK_ADC_MAX / 2;
      joystickAxes[i].filtered = joystickAxes[i].center;
      joystickAxes[i].deflection = 0;
      joystickAxes[i].direction = 0;
      joystickAxes[i].manualDirection = 0;
      joystickAxes[i].manualSpeed = 0;
      joystickAxes[i].queuedPulses = 0;
      joystickAxes[i].pulseFraction = 0;
      continue;
    }
    joystickAxes[i].filtered = joystickAxes[i].center;
  }
  joystickSampleTimeUs = micros();
  joystickAvailable = true;
}

void taskJoystick(void *param) {
  JoystickAxisState* joystickZ = &joystickAxes[JOYSTICK_AXIS_Z];
  JoystickAxisState* joystickX = &joystickAxes[JOYSTICK_AXIS_X];
  JoystickAxisState* joystickY = &joystickAxes[JOYSTICK_AXIS_Y];
  while (emergencyStop == ESTOP_NONE && joystickUsable()) {
    bool rawButtonPressed = digitalRead(JOY_BUTTON) == (INVERT_JOYSTICK_BUTTON ? HIGH : LOW);
    unsigned long now = micros();
    unsigned long elapsedUs = now - joystickSampleTimeUs;
    joystickSampleTimeUs = now;

    readJoystickAxis(joystickZ);
    readJoystickAxis(joystickX);
    readJoystickAxis(joystickY);

    bool moveNeutral = joystickZ->direction == 0 && joystickX->direction == 0;
    bool buttonPressed = updateJoystickButton(rawButtonPressed, moveNeutral);
    joystickRapidPressed = buttonPressed;

    bool yAdjustsPitch = !buttonPressed && joystickPitchAdjustmentAllowed();
    int pitchDirection = yAdjustsPitch ? joystickY->direction : 0;
    joystickPitchAdjustDirection = pitchDirection;
    if (pitchDirection != 0) {
      joystickPitchStatusDirection = pitchDirection;
      joystickPitchStatusMillis = millis();
      joystickPitchChangeFraction += abs(joystickY->deflection) * JOYSTICK_PITCH_CHANGES_PER_SECOND * elapsedUs / 1000000.0;
      int changes = min(10, int(joystickPitchChangeFraction));
      joystickPitchChangeFraction -= changes;
      for (int i = 0; i < changes; i++) {
        adjustPitch(pitchDirection > 0);
      }
    } else {
      joystickPitchChangeFraction = 0;
    }

    if (mode == MODE_JOYSTICK) {
      bool manualJoystickMove = buttonPressed || !isOn;
      joystickLatheDirectionZ = joystickZ->direction;
      joystickLatheDirectionX = joystickX->direction;
      joystickLatheRapid = buttonPressed && !moveNeutral;
      updateJoystickManualAxis(joystickZ, manualJoystickMove, false, elapsedUs);
      updateJoystickManualAxis(joystickX, manualJoystickMove, false, elapsedUs);
      updateJoystickManualAxis(joystickY, false, false, elapsedUs);
    } else {
      joystickLatheDirectionZ = 0;
      joystickLatheDirectionX = 0;
      joystickLatheRapid = false;
      updateJoystickManualAxis(joystickZ, true, true, elapsedUs);
      updateJoystickManualAxis(joystickX, true, true, elapsedUs);
      updateJoystickManualAxis(joystickY, y.active && !yAdjustsPitch, true, elapsedUs);
    }

    DELAY(JOYSTICK_SAMPLE_INTERVAL_MS);
  }
  vTaskDelete(NULL);
}

// Calculates stepper position from spindle position.
long posFromSpindleWithModePitch(Axis* a, long s, bool respectStops, long pitch) {
  long newPos = s * a->motorSteps / a->screwPitch / ENCODER_STEPS_FLOAT * pitch * starts;

  // Respect left/right stops.
  if (respectStops) {
    if (newPos < a->rightStop) {
      newPos = a->rightStop;
    } else if (newPos > a->leftStop) {
      newPos = a->leftStop;
    }
  }

  return newPos;
}

long posFromSpindle(Axis* a, long s, bool respectStops) {
  return posFromSpindleWithModePitch(a, s, respectStops, dupr);
}

// Calculates spindle position from stepper position.
long spindleFromPosWithModePitch(Axis* a, long p, long pitch) {
  return p * a->screwPitch * ENCODER_STEPS_FLOAT / a->motorSteps / (pitch * starts);
}

long spindleFromPos(Axis* a, long p) {
  return spindleFromPosWithModePitch(a, p, dupr);
}

bool stepTo(Axis* a, long newPos, bool continuous) {
  if (xSemaphoreTake(a->mutex, 10) == pdTRUE) {
    a->continuous = continuous;
    if (newPos == a->pos) {
      a->pendingPos = 0;
    } else {
      a->pendingPos = newPos - a->motorPos - (newPos > a->pos ? 0 : a->backlashSteps);
    }
    xSemaphoreGive(a->mutex);
    return true;
  }
  return false;
}

// Moves the stepper so that the tool is located at the newPos.
bool stepToContinuous(Axis* a, long newPos) {
  return stepTo(a, newPos, true);
}

bool stepToFinal(Axis* a, long newPos) {
  return stepTo(a, newPos, false);
}

void setDir(Axis* a, bool dir) {
  // Start slow if direction changed.
  if (a->direction != dir || !a->directionInitialized) {
    a->speed = a->speedStart;
    a->direction = dir;
    a->directionInitialized = true;
    digitalWrite(a->dir, dir ^ a->invertStepper);
    delayMicroseconds(DIRECTION_SETUP_DELAY_US);
  }
}

Axis* getAsyncAxis() {
  return mode == MODE_Y ? &y : &z;
}

unsigned int getTimerLimit() {
  if (dupr == 0) {
    return 65535;
  }
  return min(long(65535), long(TIMER_FREQ / (z.motorSteps * abs(dupr) / z.screwPitch)) - 1);
}

void updateAsyncTimerSettings() {
  // dupr and therefore direction can change while we're in async mode.
  setDir(getAsyncAxis(), dupr > 0);

  // dupr can change while we're in async mode, keep updating timer frequency.
  timerAlarm(async_timer, getTimerLimit(), true, 0);
  // without this timer stops working if already above new limit
  timerWrite(async_timer, 0);
}

bool gearboxMoveButtonPressed(Axis* a, int sign) {
  if (a == &z) return sign > 0 ? buttonLeftPressed : buttonRightPressed;
  if (a == &x) return sign > 0 ? buttonUpPressed : buttonDownPressed;
  return false;
}

bool moveGearboxAxisManually(Axis* a, int pulseDelta, int sign) {
  // Move by moveStep in the desired direction but stay in the thread by
  // possibly traveling a little more.
  float fraction = pulseDelta == 0 ? 1.0 : abs(pulseDelta) / a->pulsePerRevolution;
  float turns = moveStep * fraction / abs(dupr * starts);
  int fullTurns = ceil(turns);
  int diff = fullTurns * ENCODER_STEPS_FLOAT * sign * (dupr > 0 ? 1 : -1);
  long prevSpindlePos = spindlePos;
  bool stepperOn = true;
  bool resting = false;
  do {
    a->speedMax = a->speedManualMove;
    if (xSemaphoreTake(motionMutex, 100) == pdTRUE) {
      if (!resting) {
        spindlePos += diff;
        spindlePosAvg += diff;
      }
      // If spindle is moving, it will be changing spindlePos at the same time. Account for it.
      while (diff > 0 ? (spindlePos < prevSpindlePos) : (spindlePos > prevSpindlePos)) {
        spindlePos += diff;
        spindlePosAvg += diff;
      };
      prevSpindlePos = spindlePos;
      xSemaphoreGive(motionMutex);
    }

    long newPos = posFromSpindle(a, prevSpindlePos, true);
    if (newPos != a->pos) {
      stepToContinuous(a, newPos);
      waitForPendingPosNear0(a);
      getAndResetPulses(a); // Discard any pulses during movement.
    } else if (a->pos == (sign > 0 ? a->leftStop : a->rightStop)) {
      // We're standing on a stop with the move button pressed.
      resting = true;
      if (stepperOn) {
        stepperEnable(a, false);
        stepperOn = false;
      }
      DELAY(200);
    }
  } while (pulseDelta == 0 && gearboxMoveButtonPressed(a, sign));
  return stepperOn;
}

long getManualMoveTargetPos(Axis* a, int sign) {
  // pendingPos is motor travel; convert it back to the intended tool position.
  if (sign > 0 && a->pendingPos > 0) return a->motorPos + a->pendingPos;
  if (sign < 0 && a->pendingPos < 0) return a->motorPos + a->pendingPos + a->backlashSteps;
  return a->pos;
}

void taskMoveZ(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    int pulseDelta = getAndResetPulses(&z);
    bool left = buttonLeftPressed;
    bool right = buttonRightPressed;
    if (!left && !right && pulseDelta == 0) {
      taskYIELD();
      continue;
    }
    if (spindlePosSync != 0) {
      // Edge case.
      taskYIELD();
      continue;
    }
    if (isOn && !manualMovesAllowedWhenOn()) {
      setIsOnFromTask(false);
      taskYIELD();
      continue;
    }
    int sign = pulseDelta == 0 ? (left ? 1 : -1) : (pulseDelta > 0 ? 1 : -1);
    bool stepperOn = true;
    stepperEnable(&z, true);
    z.movingManually = true;
    prepareJoystickLatheManualMove();
    if (isOn && dupr != 0 && isGearboxManualMove(&z)) {
      stepperOn = moveGearboxAxisManually(&z, pulseDelta, sign);
    } else {
      z.speedMax = getStepMaxSpeed(&z);
      int delta = 0;
      do {
        bool pulseMove = pulseDelta != 0;
        float fractionalDelta = (pulseMove ? pulseDelta / z.pulsePerRevolution : moveStep * sign / z.screwPitch) * z.motorSteps + z.fractionalPos;
        delta = round(fractionalDelta);
        // Don't lose fractional steps when moving by 0.01" or 0.001".
        z.fractionalPos = fractionalDelta - delta;
        if (delta == 0) {
          // When moveStep is e.g. 1 micron and MOTOR_STEPS_Z is 200, make delta non-zero.
          delta = sign;
        }

        int deltaSign = delta > 0 ? 1 : -1;
        long posCopy = getManualMoveTargetPos(&z, deltaSign);
        // Don't left-right move out of stops.
        if (posCopy + delta > z.leftStop) {
          delta = z.leftStop - posCopy;
        } else if (posCopy + delta < z.rightStop) {
          delta = z.rightStop - posCopy;
        }
        z.speedMax = getManualMoveSpeedMax(&z, pulseMove);
        stepToContinuous(&z, posCopy + delta);
        waitForManualMoveStep(&z, pulseMove);
        if (pulseMove && delta != 0) {
          sign = deltaSign;
          pulseDelta = waitForNextPulseMoveDelta(&z, sign);
        } else {
          pulseDelta = 0;
        }
      } while (delta != 0 && (pulseDelta != 0 || (left ? buttonLeftPressed : buttonRightPressed)));
      z.continuous = false;
      waitForPendingPos0(&z);
      if (isOn && mode == MODE_CONE) {
        markOriginOrEmergencyStop();
      } else if (isOn && mode == MODE_ASYNC) {
        // Restore async direction.
        updateAsyncTimerSettings();
      }
    }
    z.movingManually = false;
    if (stepperOn) {
      stepperEnable(&z, false);
    }
    z.speedMax = LONG_MAX;
    taskYIELD();
  }
  vTaskDelete(NULL);
}

void taskMoveX(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    int pulseDelta = getAndResetPulses(&x);
    bool up = buttonUpPressed || pulseDelta > 0;
    bool down = buttonDownPressed || pulseDelta < 0;
    if (!up && !down) {
      taskYIELD();
      continue;
    }
    if (spindlePosSync != 0 && isGearboxManualMove(&x)) {
      // Edge case.
      taskYIELD();
      continue;
    }
    if (isOn && !manualMovesAllowedWhenOn()) {
      setIsOnFromTask(false);
      taskYIELD();
      continue;
    }
    x.movingManually = true;
    x.speedMax = getStepMaxSpeed(&x);
    stepperEnable(&x, true);
    bool stepperOn = true;
    prepareJoystickLatheManualMove();

    int delta = 0;
    bool positiveMove = pulseDelta == 0 ? up : pulseDelta > 0;
    int sign = positiveMove ? 1 : -1;
    if (isOn && dupr != 0 && isGearboxManualMove(&x)) {
      stepperOn = moveGearboxAxisManually(&x, pulseDelta, sign);
    } else {
      do {
        bool pulseMove = pulseDelta != 0;
        float fractionalDelta = (pulseMove ? pulseDelta / x.pulsePerRevolution : moveStep * sign / x.screwPitch) * x.motorSteps + x.fractionalPos;
        delta = round(fractionalDelta);
        // Don't lose fractional steps when moving by 0.01" or 0.001".
        x.fractionalPos = fractionalDelta - delta;
        if (delta == 0) {
          // When moveStep is e.g. 1 micron and MOTOR_STEPS_Z is 200, make delta non-zero.
          delta = sign;
        }

        int deltaSign = delta > 0 ? 1 : -1;
        long posCopy = getManualMoveTargetPos(&x, deltaSign);
        if (posCopy + delta > x.leftStop) {
          delta = x.leftStop - posCopy;
        } else if (posCopy + delta < x.rightStop) {
          delta = x.rightStop - posCopy;
        }
        x.speedMax = getManualMoveSpeedMax(&x, pulseMove);
        stepToContinuous(&x, posCopy + delta);
        waitForManualMoveStep(&x, pulseMove);
        if (pulseMove && delta != 0) {
          sign = deltaSign;
          pulseDelta = waitForNextPulseMoveDelta(&x, sign);
        } else if (pulseMove) {
          pulseDelta = 0;
        } else {
          pulseDelta = getAndResetPulses(&x);
        }
      } while (delta != 0 && (pulseDelta != 0 || (positiveMove ? buttonUpPressed : buttonDownPressed)));
      x.continuous = false;
      waitForPendingPos0(&x);
      if (isOn && mode == MODE_CONE) {
        markOriginOrEmergencyStop();
      }
    }
    x.movingManually = false;
    x.speedMax = LONG_MAX;
    if (stepperOn) {
      stepperEnable(&x, false);
    }

    taskYIELD();
  }
  vTaskDelete(NULL);
}

void taskMoveY(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    int pulseDelta = getAndResetPulses(&y);
    bool plus = buttonForwardPressed || pulseDelta > 0;
    bool minus = buttonBackPressed || pulseDelta < 0;
    if (!plus && !minus) {
      taskYIELD();
      continue;
    }
    y.movingManually = true;
    y.speedMax = getStepMaxSpeed(&y);
    stepperEnable(&y, true);

    int delta = 0;
    int sign = plus ? 1 : -1;
    do {
      bool pulseMove = pulseDelta != 0;
      float fractionalDelta = (pulseMove ? pulseDelta / y.pulsePerRevolution : getMoveStepForAxis(&y) * sign / y.screwPitch) * y.motorSteps + y.fractionalPos;
      delta = round(fractionalDelta);
      y.fractionalPos = fractionalDelta - delta;
      if (delta == 0) delta = sign;

      int deltaSign = delta > 0 ? 1 : -1;
      long posCopy = getManualMoveTargetPos(&y, deltaSign);
      if (posCopy + delta > y.leftStop) {
        delta = y.leftStop - posCopy;
      } else if (posCopy + delta < y.rightStop) {
        delta = y.rightStop - posCopy;
      }
      y.speedMax = getManualMoveSpeedMax(&y, pulseMove);
      stepToContinuous(&y, posCopy + delta);
      waitForManualMoveStep(&y, pulseMove);
      if (pulseMove && delta != 0) {
        sign = deltaSign;
        pulseDelta = waitForNextPulseMoveDelta(&y, sign);
      } else if (pulseMove) {
        pulseDelta = 0;
      } else {
        pulseDelta = getAndResetPulses(&y);
      }
    } while (delta != 0 && (pulseDelta != 0 || (plus ? buttonForwardPressed : buttonBackPressed)));
    y.continuous = false;
    waitForPendingPos0(&y);
    // Restore async direction.
    if (isOn && mode == MODE_Y) updateAsyncTimerSettings();
    y.movingManually = false;
    y.speedMax = LONG_MAX;
    stepperEnable(&y, false);
    taskYIELD();
  }
  vTaskDelete(NULL);
}

String getValueString(const String& command, char letter) {
  int index = command.indexOf(letter);
  if (index == -1) {
    return "";
  }
  String valueString;
  for (int i = index + 1; i < command.length(); i++) {
    char c = command.charAt(i);
    if (isDigit(c) || c == '.' || c == '-') {
      valueString += c;
    } else {
      break;
    }
  }
  return valueString;
}

float getFloat(const String& command, char letter) {
  return getValueString(command, letter).toFloat();
}

int getInt(const String& command, char letter) {
  return getValueString(command, letter).toInt();
}

float gcodeUnitScaleDu() {
  return measure == MEASURE_METRIC ? 10000.0 : 254000.0;
}

long gcodeUnitToDu(float value) {
  return round(value * gcodeUnitScaleDu());
}

void setFeedRate(const String& command) {
  float feed = getFloat(command, 'F');
  if (feed <= 0) return;
  gcodeFeedDuPerSec = round(feed * gcodeUnitScaleDu() / 60.0);
}

long mmOrInchToAbsolutePos(Axis* a, float mmOrInch) {
  long part1 = a->gcodeRelativePos;
  long part2 = round(mmOrInch * gcodeUnitScaleDu() / a->screwPitch * a->motorSteps);
  return part1 + part2;
}

void updateAxisSpeeds(long diffX, long diffZ, long diffY) {
  if (diffX == 0 && diffZ == 0 && diffY == 0) return;
  long absX = abs(diffX);
  long absZ = abs(diffZ);
  long absC = abs(diffY);
  float stepsPerSecX = gcodeFeedDuPerSec * x.motorSteps / x.screwPitch;
  float minStepsPerSecX = GCODE_FEED_MIN_DU_SEC * x.motorSteps / x.screwPitch;
  if (stepsPerSecX > x.speedManualMove) stepsPerSecX = x.speedManualMove;
  else if (stepsPerSecX < minStepsPerSecX) stepsPerSecX = minStepsPerSecX;
  float stepsPerSecZ = gcodeFeedDuPerSec * z.motorSteps / z.screwPitch;
  float minStepsPerSecZ = GCODE_FEED_MIN_DU_SEC * z.motorSteps / z.screwPitch;
  if (stepsPerSecZ > z.speedManualMove) stepsPerSecZ = z.speedManualMove;
  else if (stepsPerSecZ < minStepsPerSecZ) stepsPerSecZ = minStepsPerSecZ;
  float stepsPerSecY = gcodeFeedDuPerSec * y.motorSteps / y.screwPitch;
  float minStepsPerSecY = GCODE_FEED_MIN_DU_SEC * y.motorSteps / y.screwPitch;
  if (stepsPerSecY > y.speedManualMove) stepsPerSecY = y.speedManualMove;
  else if (stepsPerSecY < minStepsPerSecY) stepsPerSecY = minStepsPerSecY;
  float secX = absX / stepsPerSecX;
  float secZ = absZ / stepsPerSecZ;
  float secY = absC / stepsPerSecY;
  float sec = ACTIVE_Y ? max(max(secX, secZ), secY) : max(secX, secZ);
  x.speedMax = sec > 0 ? absX / sec : x.speedManualMove;
  z.speedMax = sec > 0 ? absZ / sec : z.speedManualMove;
  y.speedMax = sec > 0 ? absC / sec : y.speedManualMove;
  if (x.speedMax < minStepsPerSecX) x.speedMax = minStepsPerSecX;
  if (z.speedMax < minStepsPerSecZ) z.speedMax = minStepsPerSecZ;
  if (y.speedMax < minStepsPerSecY) y.speedMax = minStepsPerSecY;
}

void gcodeWaitEpsilon(int epsilon) {
  while (isOn && (abs(x.pendingPos) > epsilon || abs(z.pendingPos) > epsilon || abs(y.pendingPos) > epsilon || (SPINDLE_PAUSES_GCODE && getApproxRpm() < GCODE_MIN_RPM))) {
    taskYIELD();
  }
}

void gcodeWaitNear() {
  gcodeWaitEpsilon(GCODE_WAIT_EPSILON_STEPS);
}

void gcodeWaitStop() {
  gcodeWaitEpsilon(0);
}

// Rapid positioning / linear interpolation.
void G00_01(const String& command) {
  long xStart = x.pos;
  long zStart = z.pos;
  long yStart = y.pos;
  long xEnd = command.indexOf(x.name) >= 0 ? mmOrInchToAbsolutePos(&x, getFloat(command, x.name)) : xStart;
  long zEnd = command.indexOf(z.name) >= 0 ? mmOrInchToAbsolutePos(&z, getFloat(command, z.name)) : zStart;
  long yEnd = command.indexOf(y.name) >= 0 ? mmOrInchToAbsolutePos(&y, getFloat(command, y.name)) : yStart;
  long xDiff = xEnd - xStart;
  long zDiff = zEnd - zStart;
  long yDiff = yEnd - yStart;
  updateAxisSpeeds(xDiff, zDiff, yDiff);
  long chunks = round(max(max(abs(xDiff), abs(zDiff)), abs(yDiff)) * LINEAR_INTERPOLATION_PRECISION);
  for (long i = 0; i < chunks; i++) {
    if (!isOn) return;
    float scale = i / float(chunks);
    stepToContinuous(&x, xStart + xDiff * scale);
    stepToContinuous(&z, zStart + zDiff * scale);
    if (ACTIVE_Y) stepToContinuous(&y, yStart + yDiff * scale);
    gcodeWaitNear();
  }
  // To avoid any rounding error, move to precise position.
  stepToFinal(&x, xEnd);
  stepToFinal(&z, zEnd);
  if (ACTIVE_Y) stepToFinal(&y, yEnd);
  gcodeWaitStop();
}

bool gcodeError(const String& message, const String& command) {
  setIsOnFromTask(false);
  writeBuffer(&outBuffer, "error: ");
  writeBuffer(&outBuffer, message);
  writeBuffer(&outBuffer, " ");
  writeBuffer(&outBuffer, command);
  writeBuffer(&outBuffer, "\n");
  return false;
}

long spindleFromPosWithPitch(Axis* a, long pos, long pitchDu) {
  return round(pos * a->screwPitch * ENCODER_STEPS_FLOAT / a->motorSteps / pitchDu);
}

bool gcodeWaitForSpindle() {
  while (isOn && getApproxRpm() < GCODE_MIN_RPM) {
    taskYIELD();
  }
  return isOn;
}

long gcodeWaitForThreadPhase(Axis* lead, long pitchDu) {
  if (!gcodeWaitForSpindle()) return -1;

  long lastPhase = spindleModulo(spindlePosGlobal - spindleFromPosWithPitch(lead, lead->posGlobal, pitchDu));
  while (isOn) {
    if (getApproxRpm() < GCODE_MIN_RPM) {
      if (!gcodeWaitForSpindle()) return -1;
      lastPhase = spindleModulo(spindlePosGlobal - spindleFromPosWithPitch(lead, lead->posGlobal, pitchDu));
    }

    long phase = spindleModulo(spindlePosGlobal - spindleFromPosWithPitch(lead, lead->posGlobal, pitchDu));
    if (phase == 0) {
      return 0;
    }
    if (phase - lastPhase < -ENCODER_STEPS_INT / 2) {
      return phase;
    }
    lastPhase = phase;
    taskYIELD();
  }
  return -1;
}

bool gcodeMarkThreadOrigin(long spindleAtOrigin) {
  if (xSemaphoreTake(motionMutex, 100) != pdTRUE) {
    setIsOnFromTask(false);
    writeBuffer(&outBuffer, "error: failed to synchronize G32\n");
    return false;
  }
  markOrigin();
  spindlePos = spindleAtOrigin;
  spindlePosAvg = spindleAtOrigin;
  xSemaphoreGive(motionMutex);
  return true;
}

// Single-pass spindle-synchronized thread cutting.
bool G32(const String& command) {
  // G32 uses F as thread lead per spindle revolution, not feed per minute.
  float feed = getFloat(command, 'F');
  if (feed <= 0) {
    return gcodeError("G32 requires positive F pitch", command);
  }

  long pitchDuAbs = abs(gcodeUnitToDu(feed));
  if (pitchDuAbs == 0 || pitchDuAbs > DUPR_MAX) {
    return gcodeError("G32 F pitch out of range", command);
  }

  long xStart = x.pos;
  long zStart = z.pos;
  long yStart = y.pos;
  long xEnd = command.indexOf(x.name) >= 0 ? mmOrInchToAbsolutePos(&x, getFloat(command, x.name)) : xStart;
  long zEnd = command.indexOf(z.name) >= 0 ? mmOrInchToAbsolutePos(&z, getFloat(command, z.name)) : zStart;
  long yEnd = command.indexOf(y.name) >= 0 ? mmOrInchToAbsolutePos(&y, getFloat(command, y.name)) : yStart;
  long xDiff = xEnd - xStart;
  long zDiff = zEnd - zStart;
  long yDiff = yEnd - yStart;

  Axis* lead = NULL;
  long leadDiff = 0;
  if (zDiff != 0) {
    lead = &z;
    leadDiff = zDiff;
  } else if (xDiff != 0) {
    lead = &x;
    leadDiff = xDiff;
  } else if (ACTIVE_Y && yDiff != 0) {
    lead = &y;
    leadDiff = yDiff;
  } else {
    return gcodeError("G32 requires an axis move", command);
  }

  long pitchDu = leadDiff > 0 ? pitchDuAbs : -pitchDuAbs;
  long spindleTarget = spindleFromPosWithPitch(lead, leadDiff, pitchDu);
  if (spindleTarget <= 0) {
    return gcodeError("G32 move too short for pitch", command);
  }

  long spindleAtOrigin = gcodeWaitForThreadPhase(lead, pitchDu);
  if (spindleAtOrigin < 0) return true;
  if (!gcodeMarkThreadOrigin(spindleAtOrigin)) return false;

  x.speedMax = LONG_MAX;
  z.speedMax = LONG_MAX;
  y.speedMax = LONG_MAX;

  while (isOn) {
    long spindle = spindlePosAvg;
    bool finished = spindle >= spindleTarget;
    float progress = finished ? 1.0 : spindle / float(spindleTarget);
    if (progress < 0) progress = 0;
    else if (progress > 1) progress = 1;

    stepToContinuous(&x, round(xDiff * progress));
    stepToContinuous(&z, round(zDiff * progress));
    if (ACTIVE_Y) stepToContinuous(&y, round(yDiff * progress));

    if (finished) break;
    taskYIELD();
  }

  if (!isOn) return true;
  stepToFinal(&x, xDiff);
  stepToFinal(&z, zDiff);
  if (ACTIVE_Y) stepToFinal(&y, yDiff);
  gcodeWaitStop();
  return true;
}

bool handleGcode(const String& command) {
  int op = getInt(command, 'G');
  if (op == 0 || op == 1) { // 0 also covers X and Z commands without G.
    G00_01(command);
  } else if (op == 32) {
    return G32(command);
  } else if (op == 20 || op == 21) {
    setMeasure(op == 20 ? MEASURE_INCH : MEASURE_METRIC);
  } else if (op == 90 || op == 91) {
    gcodeAbsolutePositioning = op == 90;
  } else if (op == 94) {
    /* no-op feed per minute */
  } else if (op == 18) {
    /* no-op ZX plane selection */
  } else {
    writeBuffer(&outBuffer, "error: unsupported command ");
    writeBuffer(&outBuffer, command);
    writeBuffer(&outBuffer, "\n");
    return false;
  }
  return true;
}

bool handleMcode(const String& command) {
  int op = getInt(command, 'M');
  if (op == 0 || op == 1 || op == 2 || op == 30) {
    setIsOnFromTask(false);
  } else {
    setIsOnFromTask(false);
    writeBuffer(&outBuffer, "error: unsupported command ");
    writeBuffer(&outBuffer, command);
    writeBuffer(&outBuffer, "\n");
    return false;
  }
  return true;
}

// Process one command, return ok flag.
bool handleGcodeCommand(String command) {
  command.trim();
  if (command.length() == 0) return false;

  // Trim N.. prefix.
  char code = command.charAt(0);
  int spaceIndex = command.indexOf(' ');
  if (code == 'N' && spaceIndex > 0) {
    command = command.substring(spaceIndex + 1);
    code = command.charAt(0);
  }

  // Update position for relative calculations right before performing them.
  z.gcodeRelativePos = gcodeAbsolutePositioning ? -z.originPos : z.pos;
  x.gcodeRelativePos = gcodeAbsolutePositioning ? -x.originPos : x.pos;
  y.gcodeRelativePos = gcodeAbsolutePositioning ? -y.originPos : y.pos;

  if (!(code == 'G' && getInt(command, 'G') == 32)) {
    setFeedRate(command);
  }
  switch (code) {
    case 'G':
    case NAME_Z:
    case NAME_X:
    case NAME_Y: return handleGcode(command);
    case 'F': return true; /* feed already handled above */
    case 'M': return handleMcode(command);
    case 'T': return true; /* ignoring tool changes */
    default: writeBuffer(&outBuffer, "error: unsupported command "); writeBuffer(&outBuffer, code); writeBuffer(&outBuffer, "\n"); return false;
  }
  return false;
}

void taskGcode(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    if (mode != MODE_GCODE) {
      gcodeInitialized = false;
    } else if (!gcodeInitialized) {
      gcodeInitialized = true;
      resetGcodeState();
    }
    // Implementing a relevant subset of RS274 (Gcode) and GRBL (state management) covering basic use cases.
    char receivedChar = '\0';
    bool isWebSocket = false;
    if (mode == MODE_GCODE && isOn && gcodeProgramCharIndex < gcodeProgram.length()) {
      receivedChar = gcodeProgram.charAt(gcodeProgramCharIndex);
      gcodeProgramCharIndex++;
    } else if (bufferAvailable(&inBuffer)) {
      isWebSocket = true;
      receivedChar = shiftBuffer(&inBuffer);
    }
    int charCode = int(receivedChar);
    if (charCode > 0) {
      if (gcodeInBrace) {
        if (receivedChar == ')') gcodeInBrace = false;
      } else if (wsInKeycode) {
        if (charCode < 32) {
          if (wsKeycode == 0) {
            wsKeycode = keycodeCommand.toInt();
            writeBuffer(&outBuffer, String(wsKeycode));
            writeBuffer(&outBuffer, "\n");
          } else {
            writeBuffer(&outBuffer, "slower\n");
          }
          wsInKeycode = false;
          keycodeCommand = "";
        } else {
          keycodeCommand += receivedChar;
        }
      } else if (receivedChar == '(') {
        gcodeInBrace = true;
      } else if (receivedChar == ';' /* start of comment till end of line */) {
        gcodeInSemicolon = true;
      } else if (gcodeInSemicolon && charCode >= 32) {
        // Ignoring comment.
      } else if (receivedChar == '!' /* stop */) {
        setIsOnFromTask(false);
      } else if (receivedChar == '~' /* resume */) {
        setIsOnFromTask(true);
      } else if (receivedChar == '%' /* start/end marker */) {
        resetGcodeState();
      } else if (receivedChar == '?' /* status */) {
        writeBuffer(&outBuffer, "<");
        writeBuffer(&outBuffer, isOn ? "Run" : "Idle");
        writeBuffer(&outBuffer, "|WPos:");
        float divisor = measure == MEASURE_METRIC ? 10000.0 : 254000.0;
        writeBuffer(&outBuffer, getAxisPosDu(&x) / divisor, 3);
        writeBuffer(&outBuffer, ",0.000,");
        writeBuffer(&outBuffer, getAxisPosDu(&z) / divisor, 3);
        writeBuffer(&outBuffer, "|FS:");
        writeBuffer(&outBuffer, round(gcodeFeedDuPerSec * 60 / 10000.0));
        writeBuffer(&outBuffer, ",");
        writeBuffer(&outBuffer, String(getApproxRpm()));
        writeBuffer(&outBuffer, "|Id:");
        writeBuffer(&outBuffer, "H" + String(HARDWARE_VERSION) + "V" + String(SOFTWARE_VERSION));
        writeBuffer(&outBuffer, ">"); // no new line to allow client to easily cut out the status response
      } else if (gcodeInSave && receivedChar == '"' /* end of saved program */) {
        gcodeInSave = false;
        if (gcodeSaveName.length() == 0) {
          if (removeAllGcode()) writeBuffer(&outBuffer, "ok\n");
        } else if (gcodeSaveValue.length() > 1) {
          if (saveGcode()) writeBuffer(&outBuffer, "ok\n");
        } else if (gcodeSaveName.length() == 1) {
          writeBuffer(&outBuffer, "error: name must be at least 2 chars\n");
        } else {
          removeGcodeByName(gcodeSaveName);
        }
        gcodeSaveName = "";
        gcodeSaveValue = "";
      } else if (!gcodeInSave && receivedChar == '"' /* start of save program */) {
        gcodeInSave = true;
        gcodeInSaveFirstLine = true;
      } else if (gcodeInSaveFirstLine && receivedChar >= 32) {
        gcodeSaveName += receivedChar;
      } else if (gcodeInSaveFirstLine && receivedChar < 32) {
        gcodeInSaveFirstLine = false;
        writeBuffer(&outBuffer, "ok\n");
      } else if (gcodeInSave) {
        gcodeSaveValue += receivedChar;
        if (receivedChar < 32) {
          gcodeInBrace = false;
          gcodeInSemicolon = false;
          writeBuffer(&outBuffer, "ok\n");
        }
      } else if (isOn) {
        if (gcodeInBrace && charCode < 32) {
          writeBuffer(&outBuffer, "error: comment not closed\n");
          setIsOnFromTask(false);
        } else if (charCode < 32 && gcodeCommand.length() > 1) {
          if (handleGcodeCommand(gcodeCommand)) {
            if (isWebSocket) writeBuffer(&outBuffer, "ok\n");
          }
          gcodeCommand = "";
          gcodeInSemicolon = false;
        } else if (charCode < 32) {
          if (isWebSocket) writeBuffer(&outBuffer, "ok\n");
          gcodeCommand = "";
          gcodeInSemicolon = false;
        } else if (charCode >= 32 && (charCode == 'G' || charCode == 'M')) {
          // Split consequent G and M commands on one line.
          // No "ok" for commands in the middle of the line.
          handleGcodeCommand(gcodeCommand);
          gcodeCommand = receivedChar;
        } else if (charCode >= 32) {
          gcodeCommand += receivedChar;
        }
      } else if (receivedChar == '=' /* start of keycode command */) {
        wsInKeycode = true;
        keycodeCommand = "";
      } else {
        // ignoring non-realtime command input when off
        // to flush any commands coming after an error
      }
    }
    if (mode == MODE_GCODE && isOn && gcodeProgramCharIndex > 0 && gcodeProgramCharIndex == gcodeProgram.length()) {
      setIsOnFromTask(false);
    }
    taskYIELD();
  }
  vTaskDelete(NULL);
}

void startPulseCounter(PulseCounter pulseCounter, int gpioA, int gpioB) {
  pcnt_unit_config_t unitConfig = {};
  unitConfig.low_limit = -PCNT_LIM;
  unitConfig.high_limit = PCNT_LIM;

  pcnt_unit_handle_t unit = nullptr;
  ESP_ERROR_CHECK(pcnt_new_unit(&unitConfig, &unit));

  pcnt_glitch_filter_config_t filterConfig = {};
  filterConfig.max_glitch_ns = ((uint64_t)ENCODER_FILTER * 1000000000ULL + APB_CLK_FREQ - 1) / APB_CLK_FREQ;
  ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(unit, &filterConfig));

  pcnt_chan_config_t channelConfig = {};
  channelConfig.edge_gpio_num = gpioA;
  channelConfig.level_gpio_num = gpioB;

  pcnt_channel_handle_t channel = nullptr;
  ESP_ERROR_CHECK(pcnt_new_channel(unit, &channelConfig, &channel));
  ESP_ERROR_CHECK(pcnt_channel_set_edge_action(channel, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
  ESP_ERROR_CHECK(pcnt_channel_set_level_action(channel, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
  ESP_ERROR_CHECK(pcnt_unit_enable(unit));
  ESP_ERROR_CHECK(pcnt_unit_clear_count(unit));
  ESP_ERROR_CHECK(pcnt_unit_start(unit));

  pulseUnits[pulseCounter] = unit;
}

// Attaching interrupt on core 0 to have more time on core 1 where axes are moved.
void taskAttachInterrupts(void *param) {
  startPulseCounter(PULSE_COUNTER_SPINDLE, ENC_A, ENC_B);
  startPulseCounter(PULSE_COUNTER_Z, Z_PULSE_A, Z_PULSE_B);
  startPulseCounter(PULSE_COUNTER_X, X_PULSE_A, X_PULSE_B);
  startPulseCounter(PULSE_COUNTER_Y, Y_PULSE_A, Y_PULSE_B);
  pulseCountersReady = true;
  vTaskDelete(NULL);
}

void setDupr(long value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  nextDupr = value;
  nextDuprFlag = true;
}

void applyDuprSignReverse() {
  spindlePos = -spindlePos;
  spindlePosAvg = -spindlePosAvg;
  if (spindlePosSync != 0) {
    Axis* a = getPitchAxis();
    spindlePosSync = spindleModulo(spindlePos - spindleFromPos(a, a->pos));
  }
}

// Must be called while holding motionMutex.
void applyDupr() {
  if (nextDupr == dupr) {
    return;
  }
  bool signReverse = isOn && (isGearboxMode() || mode == MODE_CONE) && dupr != 0 && nextDupr == -dupr;
  bool joystickSamePitchMagnitude = mode == MODE_JOYSTICK && abs(nextDupr) == abs(dupr);
  dupr = nextDupr;
  if (mode == MODE_SLOT) {
    return;
  } else if (joystickSamePitchMagnitude) {
    return;
  } else if (signReverse) {
    applyDuprSignReverse();
  } else {
    markOrigin();
    if (mode == MODE_JOYSTICK) {
      resetJoystickLatheFeed();
    }
  }
  if (mode == MODE_ASYNC || mode == MODE_Y) {
    updateAsyncTimerSettings();
  }
}

void setStarts(int value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  nextStarts = value;
  nextStartsFlag = true;
}

// Must be called while holding motionMutex.
void applyStarts() {
  if (starts == nextStarts) {
    return;
  }
  starts = nextStarts;
  markOrigin();
}

// Only used for async movement in ASYNC and Y modes.
// Keep code in this method to absolute minimum to achieve high stepper speeds.
void IRAM_ATTR onAsyncTimer() {
  Axis* a = getAsyncAxis();
  if (!isOn || a->movingManually || (mode != MODE_ASYNC && mode != MODE_Y)) {
    return;
  } else if (dupr > 0 && a->pos < a->leftStop) {
    if (a->pos <= a->motorPos) {
      a->pos++;
    }
    a->motorPos++;
    a->posGlobal++;
  } else if (dupr < 0 && a->pos > a->rightStop) {
    if (a->pos >= a->motorPos + a->backlashSteps) {
      a->pos--;
    }
    a->motorPos--;
    a->posGlobal--;
  } else {
    return;
  }

  DLOW(a->step);
  a->stepStartUs = micros();
  delayMicroseconds(10);
  DHIGH(a->step);
}

void resetJoystickLatheFeed() {
  resetJoystickLatheFeedPosition();
  joystickLatheDirectionZ = 0;
  joystickLatheDirectionX = 0;
  joystickLatheRapid = false;
  for (int i = 0; i < JOYSTICK_AXIS_COUNT; i++) {
    resetJoystickAxisMotion(&joystickAxes[i]);
  }
  joystickPitchAdjustDirection = 0;
  joystickPitchStatusDirection = 0;
  joystickPitchStatusMillis = 0;
  joystickLatheThreadLocked = false;
  joystickLatheSyncPitch = 0;
  joystickPitchChangeFraction = 0;
}

void setModeFromTask(int value) {
  nextMode = value;
  nextModeFlag = true;
}

void setModeFromLoop(int value) {
  if (mode == value) {
    return;
  }
  if (isOn) {
    setIsOnFromLoop(false);
  }
  if (mode == MODE_THREAD) {
    setStarts(1);
  } else if (mode == MODE_ASYNC || mode == MODE_Y) {
    setAsyncTimerEnable(false);
  } else if (mode == MODE_JOYSTICK) {
    resetJoystickLatheFeed();
  }
  mode = value;
  setupIndex = 0;
  if (mode == MODE_CONE) {
    recomputeConeRatio();
  }
  if (mode == MODE_JOYSTICK) {
    resetJoystickLatheFeed();
  }
  if (mode == MODE_ASYNC || mode == MODE_Y) {
    if (!timerAttached) {
      timerAttached = true;
      timerAttachInterrupt(async_timer, &onAsyncTimer);
    }
    updateAsyncTimerSettings();
    setAsyncTimerEnable(true);
  }
}

void setTurnPasses(int value) {
  if (isOn) {
    beep();
  } else {
    turnPasses = value;
  }
}

void setConeRatio(float value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  nextConeRatio = value;
  nextConeRatioFlag = true;
}

void applyConeRatio() {
  if (nextConeRatio == coneRatio) {
    return;
  }
  coneRatio = nextConeRatio;
  markOrigin();
}

// Taper length: the Z travel the cone is cut over, taken from the Z stop.
float coneTaperLengthMm() {
  if (z.leftStop == LONG_MAX) return 0;
  long du = stepsToDu(&z, z.leftStop);
  return du > 0 ? du / 10000.0f : 0;
}

String coneRatioText() {
  if (coneRatio <= 0 || (mode == MODE_CONE && coneTaperLengthMm() <= 0)) return "1 : ---";
  // coneRatio is the diameter conicity (D - d) / L, the value found in taper
  // tables; the X axis itself moves coneRatio / 2 per unit of Z.
  return "1 : " + String(1 / coneRatio, 2);
}

// Cone ratio is not typed in: it comes from the two diameters and the taper
// length. Setting it goes through setConeRatio so the origin is re-marked.
void recomputeConeRatio() {
  float big = CONE_DIA_BIG_DU / 10000.0f;
  float small = CONE_DIA_SMALL_DU / 10000.0f;
  float length = coneTaperLengthMm();
  if (length < 1.0f || big - small < 0.01f) return;
  setConeRatio(constrain((big - small) / length, 0.01f, 10.0f));
}

void reset() {
  z.leftStop = LONG_MAX;
  z.nextLeftStopFlag = false;
  z.rightStop = LONG_MIN;
  z.nextRightStopFlag = false;
  z.originPos = 0;
  z.posGlobal = 0;
  z.motorPos = 0;
  z.pendingPos = 0;
  z.disabled = false;
  x.leftStop = LONG_MAX;
  x.nextLeftStopFlag = false;
  x.rightStop = LONG_MIN;
  x.nextRightStopFlag = false;
  x.originPos = 0;
  x.posGlobal = 0;
  x.motorPos = 0;
  x.pendingPos = 0;
  x.disabled = false;
  y.leftStop = LONG_MAX;
  y.nextLeftStopFlag = false;
  y.rightStop = LONG_MIN;
  y.nextRightStopFlag = false;
  y.originPos = 0;
  y.posGlobal = 0;
  y.motorPos = 0;
  y.pendingPos = 0;
  y.disabled = false;
  setDupr(0);
  setStarts(1);
  moveStep = MOVE_STEP_1;
  setModeFromTask(MODE_NORMAL);
  measure = MEASURE_METRIC;
  showTacho = false;
  showAngle = false;
  setConeRatio(0);
  auxForward = true;
}

long normalizePitch(long pitch) {
  int scale = 1;
  if (measure == MEASURE_METRIC) {
    // Drop the 3rd and 4th precision point if any.
    scale = 100;
  } else if (measure == MEASURE_INCH) {
    // Always drop the 4th precision point in inch representation if any.
    scale = 254;
  }
  return round(pitch / scale) * scale;
}

void adjustPitch(bool plus) {
  bool minus = !plus;
  long currentDupr = nextDuprFlag ? nextDupr : dupr;
  if (measure != MEASURE_TPI) {
    int delta = measure == MEASURE_METRIC ? MOVE_STEP_3 : MOVE_STEP_IMP_3;
    // Switching between mm/inch/tpi often results in getting non-0 3rd and 4th
    // precision points that can't be easily controlled. Remove them.
    long normalizedDupr = normalizePitch(currentDupr);
    if (minus && currentDupr > -DUPR_MAX) {
      setDupr(max(-DUPR_MAX, normalizedDupr - delta));
    } else if (plus && currentDupr < DUPR_MAX) {
      setDupr(min(DUPR_MAX, normalizedDupr + delta));
    }
  } else { // TPI
    if (currentDupr == 0) {
      setDupr(plus ? 1 : -1);
    } else {
      long currentTpi = round(254000.0 / currentDupr);
      long tpi = currentTpi + (plus ? 1 : -1);
      long newDupr = tpi == 0 ? (plus ? DUPR_MAX : -DUPR_MAX) : round(254000.0 / tpi);
      // Happens for small pitches like 0.01mm.
      if (newDupr == currentDupr) {
        newDupr += plus ? -1 : 1;
      }
      if (newDupr != currentDupr && newDupr < DUPR_MAX && newDupr > -DUPR_MAX) {
        setDupr(newDupr);
      }
    }
  }
}

void buttonPlusMinusPress(bool plus) {
  // Mutex is aquired in setDupr() and setStarts().
  bool minus = !plus;
  if (mode == MODE_THREAD && setupIndex == 2) {
    if (minus && starts > 1) {
      setStarts(starts - 1);
    } else if (plus && starts < STARTS_MAX) {
      setStarts(starts + 1);
    }
  } else if (isPassMode() && setupIndex == 1 && getNumpadResult() == 0) {
    if (minus && turnPasses > 1) {
      setTurnPasses(turnPasses - 1);
    } else if (plus && turnPasses < PASSES_MAX) {
      setTurnPasses(turnPasses + 1);
    }
  } else {
    adjustPitch(plus);
  }
}

void buttonOnOffPress(bool on) {
  resetMillis = millis();
  bool missingZStops = needZStops() && (z.leftStop == LONG_MAX || z.rightStop == LONG_MIN);
  if (on && isPassMode() && (missingZStops || x.leftStop == LONG_MAX || x.rightStop == LONG_MIN)) {
    beep();
  } else if (!isOn && on && mode == MODE_GCODE && gcodeProgramIndex >= gcodeProgramCount && setupIndex == 1) {
    beep();
  } else if (!isOn && on && setupIndex < getLastSetupIndex()) {
    // The thread cone ratio is a page field: confirming the step keeps it.
    setupIndex++;
  } else if (isOn && on && (mode == MODE_TURN || mode == MODE_FACE || mode == MODE_THREAD)) {
    // Move to the next pass.
    opIndexAdvanceFlag = true;
  } else if (!on && (z.movingManually || x.movingManually || y.movingManually)) {
    setEmergencyStop(ESTOP_OFF_MANUAL_MOVE);
  } else if (!isOn && on && mode == MODE_GCODE && gcodeProgramIndex >= gcodeProgramCount) {
    beep();
  } else if (!isOn && on && mode == MODE_GCODE) {
    String name = getCurrentGcodeProgramName();
    if (name.length() == 0) {
      beep();
    } else {
      gcodeProgramCharIndex = 0;
      gcodeProgram = readGcodeProgram(name);
      if (gcodeProgram.length() == 0) {
        beep();
      } else {
        gcodeProgram += '\n'; // ensures the last line is executed
        resetGcodeState();
        setIsOnFromTask(true);
      }
    }
  } else {
    setIsOnFromTask(on);
  }
}

void buttonOffRelease() {
  if (millis() - resetMillis > 3000) {
    reset();
    splashScreen = true;
  }
}

void setLeftStop(Axis* a, long value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  a->nextLeftStop = value;
  a->nextLeftStopFlag = true;
}

void leaveStop(Axis* a, long oldStop) {
  if (mode == MODE_CONE) {
    // To avoid rushing to a far away position if standing on limit.
    markOrigin();
  } else if (isGearboxMode() && a == getPitchAxis() && a->pos == oldStop) {
    // Spindle is most likely out of sync with the stepper because
    // it was spinning while the lead screw was on the stop.
    spindlePosSync = spindleModulo(spindlePos - spindleFromPos(a, a->pos));
  }
}

void applyLeftStop(Axis* a) {
  // Accept left stop even if it's lower than pos.
  // Stop button press processing takes time during which motor could have moved.
  long oldStop = a->leftStop;
  a->leftStop = a->nextLeftStop;
  leaveStop(a, oldStop);
  // The Z stop is the taper length: a new stop means a new cone ratio.
  if (a == &z && mode == MODE_CONE) recomputeConeRatio();
}

void setRightStop(Axis* a, long value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  a->nextRightStop = value;
  a->nextRightStopFlag = true;
}

void applyRightStop(Axis* a) {
  // Accept right stop even if it's higher than pos.
  // Stop button press processing takes time during which motor could have moved.
  long oldStop = a->rightStop;
  a->rightStop = a->nextRightStop;
  leaveStop(a, oldStop);
}

void buttonLeftStopPress(Axis* a) {
  setLeftStop(a, a->leftStop == LONG_MAX ? a->pos : LONG_MAX);
}

void buttonRightStopPress(Axis* a) {
  setRightStop(a, a->rightStop == LONG_MIN ? a->pos : LONG_MIN);
}

void buttonDisplayPress() {
  if (!showAngle && !showTacho) {
    showAngle = true;
  } else if (showAngle) {
    showAngle = false;
    showTacho = true;
  } else {
    showTacho = false;
  }
}

void buttonMoveStepPress() {
  if (measure == MEASURE_METRIC) {
    if (moveStep == MOVE_STEP_1) {
      moveStep = MOVE_STEP_2;
    } else if (moveStep == MOVE_STEP_2) {
      moveStep = MOVE_STEP_3;
    } else {
      moveStep = MOVE_STEP_1;
    }
  } else {
    if (moveStep == MOVE_STEP_IMP_1) {
      moveStep = MOVE_STEP_IMP_2;
    } else if (moveStep == MOVE_STEP_IMP_2) {
      moveStep = MOVE_STEP_IMP_3;
    } else {
      moveStep = MOVE_STEP_IMP_1;
    }
  }
}

void buttonMeasurePress() {
  if (measure == MEASURE_METRIC) {
    setMeasure(MEASURE_INCH);
  } else if (measure == MEASURE_INCH) {
    setMeasure(MEASURE_TPI);
  } else {
    setMeasure(MEASURE_METRIC);
  }
}

void buttonReversePress() {
  setDupr(-dupr);
}

void numpadPress(int digit) {
  if (!inNumpad) {
    numpadIndex = 0;
  }
  numpadDigits[numpadIndex] = digit;
  if (numpadIndex < 7) {
    numpadIndex++;
  } else {
    numpadIndex = 0;
  }
}

void numpadBackspace() {
  if (inNumpad && numpadIndex > 0) {
    numpadIndex--;
  }
}

void resetNumpad() {
  numpadIndex = 0;
}

void trimLeadingNumpadZeros() {
  while (numpadIndex > 1 && numpadDigits[0] == 0) {
    for (int i = 1; i < numpadIndex; i++) {
      numpadDigits[i - 1] = numpadDigits[i];
    }
    numpadIndex--;
  }
}

void numpadPlusMinus(bool plus) {
  if (numpadIndex == 0) {
    return;
  }
  if (plus) {
    for (int i = numpadIndex - 1; i >= 0; i--) {
      if (numpadDigits[i] < 9) {
        numpadDigits[i]++;
        trimLeadingNumpadZeros();
        return;
      }
      numpadDigits[i] = 0;
    }
    if (numpadIndex < 7) {
      numpadDigits[numpadIndex] = 0;
      numpadDigits[0] = 1;
      numpadIndex++;
    } else {
      for (int i = 0; i < numpadIndex; i++) {
        numpadDigits[i] = 9;
      }
    }
    return;
  }
  if (getNumpadResult() <= 1) {
    return;
  }
  for (int i = numpadIndex - 1; i >= 0; i--) {
    if (numpadDigits[i] > 0) {
      numpadDigits[i]--;
      trimLeadingNumpadZeros();
      return;
    }
    numpadDigits[i] = 9;
  }
}

unsigned long multistartPressMillis = 0;

void buttonMultistartPress() {
  if (millis() - multistartPressMillis > 3000 && starts > 1) {
    setStarts(1);
  } else {
    setStarts(starts + 1);
  }
  multistartPressMillis = millis();
}

bool processNumpadResult(int keyCode) {
  long newDu = numpadToDeciMicrons();
  float newConeRatio = numpadToConeRatio();
  long numpadResult = getNumpadResult();
  resetNumpad();
  // Ignore numpad input unless confirmed with ON.
  if (keyCode == B_ON) {
    if (isPassMode() && setupIndex == 1) {
      setTurnPasses(int(min(PASSES_MAX, numpadResult)));
      setupIndex++;
    } else if (mode == MODE_THREAD && setupIndex == 3) {
      setConeRatio(newConeRatio);
      setupIndex++;
    } else if (mode == MODE_CONE && setupIndex == 1) {
      // The cone ratio comes from the diameters and the Z stop, not from the keypad.
      setupIndex++;
    } else {
      if (abs(newDu) <= DUPR_MAX) {
        setDupr(newDu);
      }
    }
    // Don't use this ON press for starting the motion.
    return true;
  }

  // Shared piece for stops and moves.
  Axis* a = (keyCode == B_STOPL || keyCode == B_STOPR || keyCode == B_LEFT || keyCode == B_RIGHT || keyCode == B_Z) ? &z : &x;
  int sign = ((keyCode == B_STOPL || keyCode == B_STOPU || keyCode == B_LEFT || keyCode == B_UP || keyCode == B_Z || keyCode == B_X || keyCode == B_X_ENA) ? 1 : -1);
  if (keyCode == B_STOPF || keyCode == B_STOPB || keyCode == B_FORWARD || keyCode == B_BACK || keyCode == B_Y) {
    a = &y;
    sign = (keyCode == B_BACK || keyCode == B_STOPB) ? -1 : 1;
  }
  long posDiffAbs = (a->rotational ? numpadResult * 10 : newDu) / a->screwPitch * a->motorSteps;
  long pos = a->pos + posDiffAbs * sign;

  // Potentially assign a new value to a limit. Treat newDu as a relative distance from current position.
  if (keyCode == B_STOPL) {
    setLeftStop(&z, pos);
    return true;
  } else if (keyCode == B_STOPR) {
    setRightStop(&z, pos);
    return true;
  } else if (keyCode == B_STOPU) {
    setLeftStop(&x, pos);
    return true;
  } else if (keyCode == B_STOPD) {
    setRightStop(&x, pos);
    return true;
  } else if (keyCode == B_STOPF && ACTIVE_Y) {
    setLeftStop(&y, pos);
    return true;
  } else if (keyCode == B_STOPB && ACTIVE_Y) {
    setRightStop(&y, pos);
    return true;
  }

  // Potentially move by newDu in the given direction.
  // We don't support precision manual moves when ON yet. Can't stay in the thread for most modes.
  if (!isOn && (keyCode == B_LEFT || keyCode == B_RIGHT || keyCode == B_UP || keyCode == B_DOWN || keyCode == B_FORWARD || keyCode == B_BACK)) {
    if (pos < a->rightStop) {
      pos = a->rightStop;
      beep();
    } else if (pos > a->leftStop) {
      pos = a->leftStop;
      beep();
    } else if (abs(pos - a->pos) > a->estopSteps) {
      beep();
      return true;
    }
    a->speedMax = a->speedManualMove;
    stepToFinal(a, pos);
    return true;
  }

  // Set axis 0 newDu ahead.
  if (keyCode == B_Z || keyCode == B_X || keyCode == B_Y) {
    a->originPos = -pos;
    return true;
  }

  // Set X axis 0 from diameter.
  if (keyCode == B_DIAMETER || keyCode == B_X_ENA) {
    a->originPos = -a->pos - posDiffAbs / 2;
    return true;
  }

  if (keyCode == B_STEP) {
    if (newDu > 0) {
      moveStep = newDu;
    } else {
      beep();
    }
    return true;
  }

  return false;
}

bool processNumpad(int keyCode) {
  if (keyCode == B_0) {
    numpadPress(0);
    inNumpad = true;
  } else if (keyCode == B_1) {
    numpadPress(1);
    inNumpad = true;
  } else if (keyCode == B_2) {
    numpadPress(2);
    inNumpad = true;
  } else if (keyCode == B_3) {
    numpadPress(3);
    inNumpad = true;
  } else if (keyCode == B_4) {
    numpadPress(4);
    inNumpad = true;
  } else if (keyCode == B_5) {
    numpadPress(5);
    inNumpad = true;
  } else if (keyCode == B_6) {
    numpadPress(6);
    inNumpad = true;
  } else if (keyCode == B_7) {
    numpadPress(7);
    inNumpad = true;
  } else if (keyCode == B_8) {
    numpadPress(8);
    inNumpad = true;
  } else if (keyCode == B_9) {
    numpadPress(9);
    inNumpad = true;
  } else if (keyCode == B_BACKSPACE) {
    numpadBackspace();
    inNumpad = true;
  } else if (inNumpad && (keyCode == B_PLUS || keyCode == B_MINUS)) {
    numpadPlusMinus(keyCode == B_PLUS);
    return true;
  } else if (inNumpad) {
    inNumpad = false;
    return processNumpadResult(keyCode);
  }
  return inNumpad;
}

bool checkForTerminator() {
  if (nextionBufferIndex < 3) return false;
  return nextionBuffer[nextionBufferIndex - 3] == 0xFF &&
      nextionBuffer[nextionBufferIndex - 2] == 0xFF &&
      nextionBuffer[nextionBufferIndex - 1] == 0xFF;
}

const byte HEX_TO_KEYCODE[256] = {
  // Page 0 array indexes are "id" attribute values in the Nextion h5.hmi
  [0] = 0,
  [1] = 0,
  [2] = 0,
  [3] = B_OFF,
  [4] = B_MODE,
  [5] = B_REVERSE,
  [6] = B_MEASURE,
  [7] = B_STEP,
  [8] = 0,
  [9] = B_OFF, // tTurns
  [10] = B_OFF, // tAngle
  [11] = B_X_ENA,
  [12] = B_X,
  [13] = 0,
  [14] = 0,
  [15] = B_Y_ENA,
  [16] = 0,
  [17] = B_Y,
  [18] = 0,
  [19] = B_Z_ENA,
  [20] = 0,
  [21] = B_Z,
  [22] = 0,
  [23] = B_OFF,
  [24] = B_BACKSPACE,
  [25] = B_ON,
  [26] = B_0,
  [27] = B_1,
  [28] = B_2,
  [29] = B_3,
  [30] = B_4,
  [31] = B_5,
  [32] = B_6,
  [33] = B_7,
  [34] = B_8,
  [35] = B_9,
  [36] = B_STOPU,
  [37] = B_STOPD,
  [38] = B_STOPF,
  [39] = B_STOPB,
  [40] = B_STOPL,
  [41] = B_STOPR,
  [42] = B_PLUS,
  [43] = B_MINUS,
  [44] = B_UP,
  [45] = B_DOWN,
  [46] = B_FORWARD,
  [47] = B_BACK,
  [48] = B_LEFT,
  [49] = B_RIGHT,
  [50] = B_MULTISTART,
  // Restyling 2026: i pulsanti a immagine (23..25, 44..49) sono nascosti e
  // sostituiti da pulsanti con testo, aggiunti in coda con id 52..60.
  [51] = 0, // tStarts, solo testo
  [52] = B_OFF,
  [53] = B_BACKSPACE,
  [54] = B_ON,
  [55] = B_UP,
  [56] = B_DOWN,
  [57] = B_FORWARD,
  [58] = B_BACK,
  [59] = B_LEFT,
  [60] = B_RIGHT,
};

// ---------- Mode pages: values drawn with the glyph sprite ----------
// The display sends "printh 68 <page> <code> 5A FF FF FF" from page events.
// The firmware answers by drawing the value with fill + xpic on the sprite
// picture (16x26 cells, ASCII 32..126, 50 cells per row).
#define TFT_SPRITE_PIC 38
#define TFT_SPRITE_CARD_PIC 43 // same glyphs on the card color, for the side card
#define TFT_CALC_LABEL_PIC 42  // side-card labels, one 26px row per page
#define TFT_CALC_LABEL_X 502
#define TFT_CALC_LABEL_W 284
#define TFT_BG_COLOR 4226
#define TFT_GLYPH_W 16
#define TFT_GLYPH_H 26
#define TFT_SPRITE_COLS 50
#define TFT_PAGE_COUNT 18
#define TFT_STATUS_RIGHT 768 // right edge of the STATO value in the side card
#define TFT_STATUS_Y 341     // top of the STATO value row of the quoted card
#define TFT_STATUS_Y_CONE 312 // CONO aligns STATO with its label, leaving room for RAPPORTO
#define TFT_STATUS_LEFT 688  // left edge of its clear area
#define TFT_CARD_COLOR 4259  // #15161A: side card background
#define TFT_ACCENT_COLOR 7034 // #1A6DD6: blue highlight
#define TFT_GREEN_COLOR 5385  // #16A34A: green highlight
#define TFT_RED_COLOR 63488   // #F80000: red highlight

// sys0 is a global display variable: 0 = base page, 1 = setup panel,
// 2 = text keyboard. Page touch scripts branch on it.
static uint8_t tftLayer = 0;
// Last half of the shared "MAX / MIN" chip tapped on SCANALATURA: 0 = MAX,
// 1 = MIN. The -/+ steppers of that row act on the half the user picked.
static uint8_t tftStopAdjustSide = 0;

enum TftFieldKind : uint8_t {
  TK_NONE, TK_PITCH, TK_STARTS, TK_PASSES, TK_SIDE, TK_RATIO,
  TK_ZMAX, TK_ZMIN, TK_XMAX, TK_XMIN, TK_YMAX, TK_JOYN, TK_JOYR, TK_JOYD,
  TK_SIGN, TK_FWD, TK_SLOTRED, TK_ZSTOPS, TK_ZSTOPS_MIN, TK_HAND,
  TK_DIABIG, TK_DIASMALL, TK_CONERATIO, TK_AXES,
  TK_FEED, TK_ASYNCSPEED, TK_JOYSPEED, TK_SLOTSHIFT,
  // Values printed inside the drawing of the side card.
  TK_CARD_PITCH, TK_CARD_PITCH_Y, TK_CARD_PITCH_X, TK_CARD_AV,
  TK_CARD_ZMAX, TK_CARD_XMAX, TK_CARD_YMAX
};

struct TftField {
  uint8_t kind;
  int16_t right; // right edge of the number area
  int16_t y;     // top of the number area
  int16_t clearLeft; // left edge of the number box (borders excluded)
};

struct TftPage {
  uint8_t mode;
  uint8_t count;
  TftField f[6];
  TftField c[2]; // values written inside the card drawing (empty background)
};

static const TftPage TFT_PAGES[TFT_PAGE_COUNT] = {
  { MODE_NORMAL, 0, {} },                                                                                             // 0 MENU
  { MODE_NORMAL, 5, {{TK_PITCH, 342, 92, 259}, {TK_STARTS, 328, 158, 263}, {TK_ZMAX, 342, 224, 244}, {TK_ZMIN, 337, 290, 263}, {TK_FEED, 768, 393, 610}},
    {{TK_CARD_PITCH, 714, 155, 569}, {TK_CARD_ZMAX, 691, 274, 596}} },                                               // 1 INGRANAGGI
  { MODE_THREAD, 6, {{TK_PITCH, 342, 92, 259}, {TK_STARTS, 328, 158, 263}, {TK_RATIO, 367, 224, 263}, {TK_ZMAX, 342, 290, 244}, {TK_HAND, 612, 25, 372}, {TK_FEED, 768, 393, 610}},
    {{TK_CARD_PITCH, 714, 155, 569}, {TK_CARD_ZMAX, 691, 274, 596}} },                                               // 2 FILETTATURA
  { MODE_TURN, 5, {{TK_PITCH, 342, 92, 259}, {TK_PASSES, 328, 158, 263}, {TK_SIDE, 368, 224, 243}, {TK_ZMAX, 342, 290, 244}, {TK_FEED, 768, 393, 610}},
    {{TK_CARD_PITCH, 712, 155, 567}, {TK_CARD_ZMAX, 685, 274, 591}} },                                               // 3 TORNITURA
  { MODE_FACE, 5, {{TK_PITCH, 342, 92, 259}, {TK_PASSES, 328, 158, 263}, {TK_SIDE, 368, 224, 257}, {TK_XMAX, 342, 290, 259}, {TK_FEED, 768, 393, 610}},
    {{TK_CARD_PITCH, 683, 276, 538}, {TK_CARD_XMAX, 745, 186, 651}} },                                               // 4 SPIANATURA
  { MODE_CONE, 6, {{TK_DIABIG, 342, 92, 240}, {TK_DIASMALL, 342, 150, 240}, {TK_ZMAX, 342, 208, 244}, {TK_SIDE, 368, 266, 243}, {TK_XMAX, 342, 324, 240}, {TK_CONERATIO, 768, 345, 600}} }, // 5 CONO
  { MODE_CUT, 5, {{TK_PITCH, 342, 92, 259}, {TK_PASSES, 328, 158, 263}, {TK_SIDE, 368, 224, 243}, {TK_XMAX, 342, 290, 259}, {TK_FEED, 768, 393, 610}},
    {{TK_CARD_PITCH, 687, 153, 542}, {TK_CARD_XMAX, 759, 237, 665}} },                                               // 6 TRONCATURA
  { MODE_ELLIPSE, 5, {{TK_PITCH, 342, 92, 259}, {TK_PASSES, 328, 158, 263}, {TK_SIDE, 368, 224, 243}, {TK_ZMAX, 342, 290, 259}, {TK_FEED, 768, 393, 610}},
    {{TK_CARD_PITCH, 714, 155, 569}, {TK_CARD_ZMAX, 691, 260, 596}} },                                               // 7 ELLISSE
  { MODE_ASYNC, 5, {{TK_PITCH, 342, 92, 259}, {TK_STARTS, 328, 158, 263}, {TK_SIGN, 328, 224, 263}, {TK_ZMAX, 342, 290, 244}, {TK_ASYNCSPEED, 768, 393, 610}},
    {{TK_CARD_PITCH, 714, 155, 569}, {TK_CARD_ZMAX, 689, 274, 594}} },                                               // 8 ASINCRONO
  { MODE_GCODE, 0, {} },                                                                                             // 9 G-CODE
  { MODE_Y, 5, {{TK_PITCH, 342, 92, 259}, {TK_STARTS, 328, 158, 263}, {TK_SIGN, 328, 224, 263}, {TK_YMAX, 342, 290, 244}, {TK_FEED, 768, 393, 610}},
    {{TK_CARD_PITCH_Y, 765, 149, 620}, {TK_CARD_YMAX, 763, 206, 668}} },                                             // 10 ASSE Y
  { MODE_JOYSTICK, 5, {{TK_JOYN, 334, 92, 263}, {TK_JOYR, 334, 158, 263}, {TK_JOYD, 343, 224, 263}, {TK_AXES, 474, 290, 374}, {TK_JOYSPEED, 768, 393, 610}} },  // 11 JOYSTICK
  { MODE_XGEAR, 5, {{TK_PITCH, 342, 92, 259}, {TK_STARTS, 328, 158, 263}, {TK_XMAX, 342, 224, 259}, {TK_XMIN, 337, 290, 263}, {TK_FEED, 768, 393, 610}},
    {{TK_CARD_PITCH_X, 691, 155, 546}, {TK_CARD_XMAX, 753, 278, 659}} },                                             // 12 X-INGRANAGGI
  { MODE_NORMAL, 0, {} },                                                                                            // 13 COMANDO
  { MODE_NORMAL, 0, {} },                                                                                            // 14 SETUP
  { MODE_NORMAL, 0, {} },                                                                                            // 15 WIFI
  { MODE_NORMAL, 0, {} },                                                                                            // 16 INFO
  { MODE_SLOT, 6, {{TK_PASSES, 336, 86, 271}, {TK_SLOTRED, 350, 140, 267}, {TK_PITCH, 350, 194, 267}, {TK_FWD, 374, 248, 271}, {TK_ZSTOPS, 357, 302, 181}, {TK_SLOTSHIFT, 768, 393, 610}},
    {{TK_CARD_AV, 714, 155, 569}, {TK_CARD_ZMAX, 687, 274, 592}} },                                                  // 17 SCANALATURA
};

// The eleven quoted cards are stacked in pictures 44..46, five per picture
// (Nextion refuses taller images), 358 px per card, so the firmware shows the
// right one with a single cropped xpic.
#define TFT_CARD_FIRST_PIC 44
#define TFT_CARD_PER_PIC 5
#define TFT_CARD_X 500
#define TFT_CARD_Y 74
#define TFT_CARD_W 288
#define TFT_CARD_H 358
static const int8_t TFT_CARD_SLOT[TFT_PAGE_COUNT] = {
  -1, 0, 1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, -1, -1, -1, 10
};

String tftStopText(Axis* a, bool isLeft, bool adaptive) {
  long stop = isLeft ? a->leftStop : a->rightStop;
  if (isLeft ? stop == LONG_MAX : stop == LONG_MIN) return "---";
  long du = stepsToDu(a, stop);
  if (adaptive || measure != MEASURE_METRIC) return printDeciMicrons(du, 2);
  return String(du / 10000.0, 2);
}

String tftZStopsText() {
  String mx = tftStopText(&z, true, false);
  String mn = tftStopText(&z, false, false);
  String text = mx + "/" + mn;
  if (text.length() > 11) {
    mx = z.leftStop == LONG_MAX ? "---" : String(stepsToDu(&z, z.leftStop) / 10000);
    mn = z.rightStop == LONG_MIN ? "---" : String(stepsToDu(&z, z.rightStop) / 10000);
    text = mx + "/" + mn;
  }
  return text;
}

// Physical direction on SPIANATURA, side of the material elsewhere. On
// TRONCATURA the side is not a setting: it follows the sign of the pitch.
String tftSideText() {
  if (mode == MODE_FACE) return auxForward ? "DX>SX" : "SX>DX";
  if (mode == MODE_CUT) return (nextDuprFlag ? nextDupr : dupr) >= 0 ? "EST" : "INT";
  return auxForward ? "EST" : "INT";
}

String tftAxesText() {
  String text;
  if (JOYSTICK_Z_ENABLED) text += "Z ";
  if (JOYSTICK_X_ENABLED) text += "X ";
  if (JOYSTICK_Y_ENABLED) text += "Y ";
  text.trim();
  return text.length() > 0 ? text : "---";
}

String tftFieldText(const TftField &f, bool adaptive = false) {
  switch (f.kind) {
    case TK_PITCH: return printDupr(nextDuprFlag ? nextDupr : dupr);
    case TK_STARTS: return String(starts);
    case TK_PASSES: return String(turnPasses);
    case TK_SIDE: return tftSideText();
    case TK_AXES: return tftAxesText();
    case TK_RATIO: return String(coneRatio, 3);
    case TK_DIABIG: return String(CONE_DIA_BIG_DU / 10000.0, 2);
    case TK_DIASMALL: return String(CONE_DIA_SMALL_DU / 10000.0, 2);
    case TK_CONERATIO: return coneRatioText();
    // Values derived from the measurements, shown on the side card.
    case TK_FEED: return String(fabs((nextDuprFlag ? nextDupr : dupr) / 10000.0) * (starts < 1 ? 1 : starts), 3);
    case TK_ASYNCSPEED: return String(fabs((nextDuprFlag ? nextDupr : dupr) / 10000.0) * 60.0, 2);
    case TK_JOYSPEED: return String(JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND * (z.screwPitch / 10000.0) * 60.0, 0);
    case TK_SLOTSHIFT: return String(SLOT_LEFT_REDUCTION_DU / 10000.0 * (turnPasses > 1 ? (long)(turnPasses - 1) : 0L), 2);
    // Annotations printed on the card drawing, next to the quoted figure.
    case TK_CARD_PITCH: return String("P ") + printDupr(nextDuprFlag ? nextDupr : dupr);
    case TK_CARD_PITCH_Y: return String("P Y ") + printDupr(nextDuprFlag ? nextDupr : dupr);
    case TK_CARD_PITCH_X: return String("P X ") + printDupr(nextDuprFlag ? nextDupr : dupr);
    case TK_CARD_AV: return String("AV. ") + printDupr(nextDuprFlag ? nextDupr : dupr);
    case TK_CARD_ZMAX: return tftStopText(&z, true, false);
    case TK_CARD_XMAX: return tftStopText(&x, true, false);
    case TK_CARD_YMAX: return tftStopText(&y, true, false);
    case TK_ZMAX: return tftStopText(&z, true, adaptive);
    case TK_ZMIN: return tftStopText(&z, false, adaptive);
    case TK_XMAX: return tftStopText(&x, true, adaptive);
    case TK_XMIN: return tftStopText(&x, false, adaptive);
    case TK_YMAX: return tftStopText(&y, true, adaptive);
    case TK_JOYN: return String(JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND, 2);
    case TK_JOYR: return String(JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND, 2);
    case TK_JOYD: return String(JOYSTICK_DEADBAND);
    case TK_SIGN: return (nextDuprFlag ? nextDupr : dupr) >= 0 ? "+" : "-";
    case TK_HAND: return String("SENSO ") + ((nextDuprFlag ? nextDupr : dupr) >= 0 ? "DX" : "SX");
    case TK_FWD: return auxForward ? "AVANTI" : "DIETRO";
    case TK_SLOTRED: return String(SLOT_LEFT_REDUCTION_DU / 10000.0, adaptive ? 2 : 3);
    case TK_ZSTOPS:
    case TK_ZSTOPS_MIN: return tftZStopsText();
    default: return "";
  }
}

// Draws a run of sprite glyphs at the given top-left corner.
void tftGlyphs(int x, int y, const String &text) {
  for (int i = 0; i < (int)text.length(); i++) {
    int c = (uint8_t)text[i];
    if (c < 32 || c > 126) c = '?';
    int code = c - 32;
    int sx = (code % TFT_SPRITE_COLS) * TFT_GLYPH_W;
    int sy = (code / TFT_SPRITE_COLS) * TFT_GLYPH_H;
    toScreen("xpic " + String(x + i * TFT_GLYPH_W) + "," + String(y) + "," + String(TFT_GLYPH_W) + "," + String(TFT_GLYPH_H) + "," + String(sx) + "," + String(sy) + "," + String(TFT_SPRITE_PIC));
  }
}

void tftFill(int x, int y, int w, int h, uint16_t color) {
  if (w <= 0 || h <= 0) return;
  toScreen("fill " + String(x) + "," + String(y) + "," + String(w) + "," + String(h) + "," + String(color));
}

String tftClip(const String &text, int maxGlyphs) {
  if ((int)text.length() <= maxGlyphs) return text;
  if (maxGlyphs <= 0) return "";
  return text.substring(0, maxGlyphs);
}

// Glyphs first, residual strip last: xpic cells are opaque and carry the box
// colour as background, so the new text replaces the old one in place and the
// line never flashes dark (the "ombra" seen over PASSO after the keypad OK).
void tftLineLeft(int left, int y, int right, const String &text, uint16_t bg) {
  String t = tftClip(text, (right - left + 2) / TFT_GLYPH_W);
  tftGlyphs(left, y, t);
  tftFill(left + (int)t.length() * TFT_GLYPH_W, y, right - left - (int)t.length() * TFT_GLYPH_W, TFT_GLYPH_H, bg);
}

void tftLineRight(int left, int y, int right, const String &text, uint16_t bg) {
  String t = tftClip(text, (right - left + 2) / TFT_GLYPH_W);
  int gw = (int)t.length() * TFT_GLYPH_W;
  tftGlyphs(right - gw, y, t);
  tftFill(left, y, right - gw - left, TFT_GLYPH_H, bg);
}

void tftLineCenter(int cx, int y, int left, int right, const String &text, uint16_t bg) {
  String t = tftClip(text, (right - left + 2) / TFT_GLYPH_W);
  int gw = (int)t.length() * TFT_GLYPH_W;
  int gx = cx - gw / 2;
  tftGlyphs(gx, y, t);
  tftFill(left, y, gx - left, TFT_GLYPH_H, bg);
  tftFill(gx + gw, y, right - (gx + gw), TFT_GLYPH_H, bg);
}

void tftSetLayer(uint8_t value) {
  tftLayer = value;
  toScreen("sys0=" + String(value));
}

// Values that are computed from the measurements and shown read-only on the
// side card, the same way CONO derives its ratio.
bool tftIsCalcKind(uint8_t kind) {
  return kind == TK_FEED || kind == TK_ASYNCSPEED || kind == TK_JOYSPEED || kind == TK_SLOTSHIFT;
}

void tftDrawField(const TftField &f, uint8_t page) {
  if (f.kind == TK_NONE) return;
  if (f.kind == TK_AXES) {
    // Chip without a touch zone: centre the list of the inputs actually
    // enabled, then clear the sample letters left and right of it.
    int w = f.right - f.clearLeft;
    String text = tftFieldText(f);
    int gw = (int)text.length() * TFT_GLYPH_W;
    int gx = f.clearLeft + (w - gw) / 2;
    tftGlyphs(gx, f.y, text);
    tftFill(f.clearLeft, f.y, gx - f.clearLeft, TFT_GLYPH_H, TFT_BG_COLOR);
    tftFill(gx + gw, f.y, f.right + 2 - (gx + gw), TFT_GLYPH_H, TFT_BG_COLOR);
    return;
  }
  if (f.kind == TK_HAND) {
    // Thread hand chip in the FILETTO header: square steps approximate the
    // rounded boxes of the background picture.
    int w = f.right - f.clearLeft;
    int x = f.clearLeft;
    int y = f.y - 6;
    tftFill(x + 6, y, w - 12, 38, TFT_BG_COLOR);
    tftFill(x + 2, y + 3, w - 4, 32, TFT_BG_COLOR);
    tftFill(x, y + 7, w, 24, TFT_BG_COLOR);
    String text = tftFieldText(f);
    tftGlyphs(x + (w - (int)text.length() * TFT_GLYPH_W) / 2, f.y, text);
    return;
  }
  bool onCard = f.kind == TK_CONERATIO || tftIsCalcKind(f.kind);
  if (tftIsCalcKind(f.kind)) {
    // Picture 42 holds one label row per page, at the page index.
    toScreen("xpic " + String(TFT_CALC_LABEL_X) + "," + String(f.y) + "," + String(TFT_CALC_LABEL_W) + "," + String(TFT_GLYPH_H) + ",0," + String((int)page * TFT_GLYPH_H) + "," + String(TFT_CALC_LABEL_PIC));
  }
  int maxGlyphs = (f.right - f.clearLeft + 2) / TFT_GLYPH_W;
  if (maxGlyphs < 1) return;
  String text = tftFieldText(f);
  if (text.length() > maxGlyphs) text = tftFieldText(f, true);
  if (text.length() > maxGlyphs) text = text.substring(0, maxGlyphs);
  int n = text.length();
  int left = f.right - n * TFT_GLYPH_W;
  int clearFrom = min((int)f.clearLeft, left);
  // The ratio and the computed rows sit on the side card, not in a value box.
  uint16_t bg = onCard ? TFT_CARD_COLOR : TFT_BG_COLOR;
  uint8_t pic = onCard ? TFT_SPRITE_CARD_PIC : TFT_SPRITE_PIC;
  for (int i = 0; i < n; i++) {
    int code = (int)text[i] - 32;
    if (code < 0 || code > 94) continue;
    int sx = (code % TFT_SPRITE_COLS) * TFT_GLYPH_W;
    int sy = (code / TFT_SPRITE_COLS) * TFT_GLYPH_H;
    toScreen("xpic " + String(left + i * TFT_GLYPH_W) + "," + String(f.y) + "," + String(TFT_GLYPH_W) + "," + String(TFT_GLYPH_H) + "," + String(sx) + "," + String(sy) + "," + String(pic));
  }
  tftFill(clearFrom, f.y, left - clearFrom, TFT_GLYPH_H, bg);
  tftFill(f.right, f.y, 2, TFT_GLYPH_H, bg);
}

void tftDrawCardField(const TftField &f);

void tftDrawPage(uint8_t page) {
  if (page >= TFT_PAGE_COUNT) return;
  const TftPage &pg = TFT_PAGES[page];
  for (uint8_t i = 0; i < 2; i++) tftDrawCardField(pg.c[i]);
  for (uint8_t i = 0; i < pg.count; i++) tftDrawField(pg.f[i], page);
}

// The quoted card replaces the icon card of the background picture, so it is
// painted on page load only: the dynamic values are redrawn over it.
void tftDrawCardBackdrop(uint8_t page) {
  if (page >= TFT_PAGE_COUNT) return;
  int8_t slot = TFT_CARD_SLOT[page];
  if (slot < 0) return;
  uint8_t pic = TFT_CARD_FIRST_PIC + slot / TFT_CARD_PER_PIC;
  int offset = (slot % TFT_CARD_PER_PIC) * TFT_CARD_H;
  toScreen("xpic " + String(TFT_CARD_X) + "," + String(TFT_CARD_Y) + "," + String(TFT_CARD_W) + "," + String(TFT_CARD_H) + ",0," + String(offset) + "," + String(pic));
}

// Same sprite glyphs as the value boxes, centred inside the empty chip or
// dimension box already drawn in the card picture.
void tftDrawCardField(const TftField &f) {
  if (f.kind == TK_NONE) return;
  int maxGlyphs = (f.right - f.clearLeft + 2) / TFT_GLYPH_W;
  if (maxGlyphs < 1) return;
  String text = tftFieldText(f);
  if ((int)text.length() > maxGlyphs) text = text.substring(0, maxGlyphs);
  int n = text.length();
  int cx = (f.clearLeft + f.right + 1) / 2;
  int left = cx - n * TFT_GLYPH_W / 2;
  for (int i = 0; i < n; i++) {
    int code = (int)text[i] - 32;
    if (code < 0 || code > 94) continue;
    int sx = (code % TFT_SPRITE_COLS) * TFT_GLYPH_W;
    int sy = (code / TFT_SPRITE_COLS) * TFT_GLYPH_H;
    toScreen("xpic " + String(left + i * TFT_GLYPH_W) + "," + String(f.y) + "," + String(TFT_GLYPH_W) + "," + String(TFT_GLYPH_H) + "," + String(sx) + "," + String(sy) + "," + String(TFT_SPRITE_PIC));
  }
  tftFill(f.clearLeft, f.y, left - f.clearLeft, TFT_GLYPH_H, TFT_BG_COLOR);
  tftFill(left + n * TFT_GLYPH_W, f.y, f.right + 2 - (left + n * TFT_GLYPH_W), TFT_GLYPH_H, TFT_BG_COLOR);
}

String tftStateText();

// The mode pages 1..12 and 17 share the same side card with STATO. The text in
// the background image is always "OFF", so the real state must be drawn on top.
void tftDrawStatus(uint8_t page) {
  if (page < 1 || page > 12) {
    if (page != 17) return;
  }
  String text = tftStateText();
  int y = page == 5 ? TFT_STATUS_Y_CONE : TFT_STATUS_Y;
  int n = text.length();
  int left = TFT_STATUS_RIGHT - n * TFT_GLYPH_W;
  int clearFrom = min((int)TFT_STATUS_LEFT, left);
  for (int i = 0; i < n; i++) {
    int sx = ((int)text[i] - 32) % TFT_SPRITE_COLS * TFT_GLYPH_W;
    int sy = ((int)text[i] - 32) / TFT_SPRITE_COLS * TFT_GLYPH_H;
    toScreen("xpic " + String(left + i * TFT_GLYPH_W) + "," + String(y) + "," + String(TFT_GLYPH_W) + "," + String(TFT_GLYPH_H) + "," + String(sx) + "," + String(sy) + "," + String(TFT_SPRITE_CARD_PIC));
  }
  tftFill(clearFrom, y, left - clearFrom, TFT_GLYPH_H, TFT_CARD_COLOR);
  tftFill(TFT_STATUS_RIGHT, y, 2, TFT_GLYPH_H, TFT_CARD_COLOR);
}

// ---------- Service pages (MENU, COMANDO, SETUP, WIFI, INFO, G-CODE) ----------
// These pages have no Nextion components: the firmware paints every dynamic
// value with the glyph sprite and reads tap events from page Touch scripts.
#define TFT_MENU_PAGE 0
#define TFT_GCODE_PAGE 9
#define TFT_COMANDO_PAGE 13
#define TFT_SETUP_PAGE 14
#define TFT_WIFI_PAGE 15
#define TFT_INFO_PAGE 16
#define TFT_PANEL_PAGE 19    // firmware-painted settings panel
#define TFT_KEYBOARD_PAGE 20 // firmware-painted text keyboard
#define TFT_WORK_PAGE 21     // LAVORAZIONE: live axes and pass data while running
#define TFT_SERVICE_BG 2113  // #080808: background of the firmware-painted pages (19, 20, 21)
#define TFT_ROW_COLOR 4226   // #101010: unselected G-code row
#define TFT_SELECT_COLOR 4391 // #102439: selected G-code row
#define TFT_BUTTON_COLOR 10598 // #292C31: neutral button
#define TFT_RED_BUTTON 51429  // #CE1C29: red button

static uint8_t tftCurrentPage = 255;
static bool tftOpenWorkPagePending = false;
static unsigned long tftLastDynamicMs = 0;
static String tftStatusMessage = "";
static unsigned long tftStatusUntil = 0;
static uint8_t tftHeldMove = 0;
static unsigned long tftHeldMoveMs = 0;
static String tftFooterCache = "";

// Text keyboard state (page 20): 0 = SSID, 1 = password. The buffer is only
// shown masked for the password and is never written to the logs.
static uint8_t kbTarget = 0;
static bool kbShift = false;
static char kbBuf[64];
static uint8_t kbLen = 0;

void tftSetStatus(const String &message, unsigned long ms) {
  tftStatusMessage = message;
  tftStatusUntil = millis() + ms;
}

String tftActiveStatus() {
  if (tftStatusMessage.length() == 0) return "";
  if ((long)(millis() - tftStatusUntil) >= 0) return "";
  return tftStatusMessage;
}

String tftStateText() {
  if (emergencyStop != ESTOP_NONE) return "ESTOP";
  return spindlePosSync ? "SIN" : isOn ? "ON" : "OFF";
}

String tftModeName(int value) {
  switch (value) {
    case MODE_NORMAL: return "NORMALE";
    case MODE_THREAD: return "FILETTATURA";
    case MODE_TURN: return "TORNITURA";
    case MODE_FACE: return "SPIANATURA";
    case MODE_CONE: return "CONO";
    case MODE_CUT: return "TRONCATURA";
    case MODE_ELLIPSE: return "ELLISSE";
    case MODE_ASYNC: return "ASINCRONO";
    case MODE_GCODE: return "G-CODE";
    case MODE_Y: return "ASSE Y";
    case MODE_JOYSTICK: return "JOYSTICK";
    case MODE_XGEAR: return "X-INGRANAGGI";
    case MODE_SLOT: return "SCANALATURA";
  }
  return "";
}

// ---------- Setup panel model ----------
enum TctKind : uint8_t {
  TCT_I, TCT_L, TCT_FLOAT, TCT_DU, TCT_MM, TCT_B, TCT_MEASURE,
  TCT_INFO, TCT_ACTION, TCT_STOP
};

struct TctRow {
  const char* label;
  uint8_t kind;
  void* p;
  long a;
  long b;
};

struct TctPanel {
  const char* title;
  uint8_t count;
  const TctRow* rows;
};

static const TctRow TCT_ROWS_PASSI[] = {
  {"IMPULSI ENCODER", TCT_I, &ENCODER_PPR, 1, 15000},
  {"BACKLASH ENCODER", TCT_I, &ENCODER_BACKLASH, 0, 30000},
  {"PASSI MOTORE Z", TCT_L, &MOTOR_STEPS_Z, 1, 1000000},
  {"PASSI MOTORE X", TCT_L, &MOTOR_STEPS_X, 1, 1000000},
  {"PASSI MOTORE Y", TCT_L, &MOTOR_STEPS_Y, 1, 1000000},
  {"VITE Z MM/GIRO", TCT_DU, &SCREW_Z_DU, 1, 10000000},
  {"VITE X MM/GIRO", TCT_DU, &SCREW_X_DU, 1, 10000000},
};

static const TctRow TCT_ROWS_LIMITI[] = {
  {"CORSA MAX Z", TCT_MM, &MAX_TRAVEL_MM_Z, 1, 10000},
  {"CORSA MAX X", TCT_MM, &MAX_TRAVEL_MM_X, 1, 10000},
  {"CORSA MAX Y", TCT_MM, &MAX_TRAVEL_MM_Y, 1, 10000},
  {"BACKLASH Z", TCT_DU, &BACKLASH_DU_Z, 0, 10000000},
  {"BACKLASH X", TCT_DU, &BACKLASH_DU_X, 0, 10000000},
  {"BACKLASH Y", TCT_DU, &BACKLASH_DU_Y, 0, 10000000},
  {"DIST. SICUREZZA", TCT_DU, &SAFE_DISTANCE_DU, 0, 10000000},
  {"FINECORSA Z MAX", TCT_STOP, NULL, 0, 1},
  {"FINECORSA Z MIN", TCT_STOP, NULL, 0, 0},
  {"FINECORSA X MAX", TCT_STOP, NULL, 1, 1},
  {"FINECORSA X MIN", TCT_STOP, NULL, 1, 0},
};

static const TctRow TCT_ROWS_VELOCITA[] = {
  {"VEL. AVVIO Z", TCT_L, &SPEED_START_Z, 1, 1000000},
  {"VEL. AVVIO X", TCT_L, &SPEED_START_X, 1, 1000000},
  {"VEL. AVVIO Y", TCT_L, &SPEED_START_Y, 1, 1000000},
  {"ACCEL. Z", TCT_L, &ACCELERATION_Z, 1, 100000000},
  {"ACCEL. X", TCT_L, &ACCELERATION_X, 1, 100000000},
  {"ACCEL. Y", TCT_L, &ACCELERATION_Y, 1, 100000000},
  {"VEL. MANUALE Z", TCT_L, &SPEED_MANUAL_MOVE_Z, 1, 1000000},
  {"VEL. MANUALE X", TCT_L, &SPEED_MANUAL_MOVE_X, 1, 1000000},
  {"VEL. MANUALE Y", TCT_L, &SPEED_MANUAL_MOVE_Y, 1, 1000000},
  {"RITARDO STEP", TCT_L, &STEP_TIME_MS, 1, 10000},
  {"PAUSA STEP", TCT_L, &DELAY_BETWEEN_STEPS_MS, 0, 10000},
};

static const TctRow TCT_ROWS_UNITA[] = {
  {"MISURA", TCT_MEASURE, NULL, 0, 0},
  {"MOSTRA TACHIMETRO", TCT_B, &showTacho, 0, 0},
  {"MOSTRA ANGOLO", TCT_B, &showAngle, 0, 0},
  {"PASSO MANUALE", TCT_L, &moveStep, 1, DUPR_MAX},
  {"ASSE Y ATTIVO", TCT_B, &ACTIVE_Y, 0, 0},
  {"ASSE Y ROTATIVO", TCT_B, &ROTARY_Y, 0, 0},
};

static const TctRow TCT_ROWS_LINGUA[] = {
  {"LINGUA", TCT_INFO, NULL, 0, 0},
  {"DISPLAY", TCT_INFO, NULL, 1, 0},
  {"FIRMWARE", TCT_INFO, NULL, 2, 0},
  {"SERVIZIO", TCT_INFO, NULL, 3, 0},
};

static const TctRow TCT_ROWS_RIPRISTINA[] = {
  {"RIPRISTINA MACCHINA", TCT_ACTION, NULL, 0, 0},
  {"RIPRISTINA WIFI", TCT_ACTION, NULL, 1, 0},
};

static const TctPanel TCT_PANELS[] = {
  {"PASSI ASSI", 7, TCT_ROWS_PASSI},
  {"LIMITI E FINECORSE", 11, TCT_ROWS_LIMITI},
  {"VELOCITA' E RAMPE", 11, TCT_ROWS_VELOCITA},
  {"UNITA' E FORMATO", 6, TCT_ROWS_UNITA},
  {"LINGUA E DISPLAY", 4, TCT_ROWS_LINGUA},
  {"RIPRISTINA", 2, TCT_ROWS_RIPRISTINA},
};
#define TCT_PANEL_COUNT 6
#define TFT_SETUP_PAGE_SIZE 7

static uint8_t tftSetupSection = 0;
static uint8_t tftSetupPage = 0;
static bool tftSetupOpen = false;
static uint8_t tftActionArmed = 255;
static unsigned long tftActionArmMs = 0;

Axis* tctAxis(long value) {
  return value == 1 ? &x : value == 2 ? &y : &z;
}

String tctInfoText(long index) {
  if (index == 0) return "ITALIANO";
  if (index == 1) return "NX8048P050";
  if (index == 2) return CONTROLLER_VERSION_TEXT;
  return "NESSUNO";
}

String tctText(const TctRow &r) {
  switch (r.kind) {
    case TCT_I: return String(*(int*)r.p);
    case TCT_L: case TCT_MM: return String(*(long*)r.p);
    case TCT_FLOAT: return String(*(float*)r.p, 3);
    case TCT_DU: return String(*(long*)r.p / 10000.0, 3);
    case TCT_B: return *(bool*)r.p ? "SI" : "NO";
    case TCT_MEASURE: return measure == MEASURE_METRIC ? "MM" : measure == MEASURE_INCH ? "POL" : "TPI";
    case TCT_STOP: return tftStopText(tctAxis(r.a), r.b != 0, false);
    case TCT_INFO: return tctInfoText(r.a);
    case TCT_ACTION: return "PREMI";
  }
  return "";
}

String tftWifiStateText();

String tftFooterText() {
  if (tftCurrentPage == 255) return "";
  String status = tftActiveStatus();
  if (status.length()) return status;
  String state = tftStateText();
  if (tftCurrentPage == TFT_MENU_PAGE) return "MENU  " + state;
  if (tftCurrentPage == TFT_GCODE_PAGE) return "G-CODE  " + String(gcodeProgramCount) + " PROGRAMMI";
  if (tftCurrentPage == TFT_COMANDO_PAGE) return "COMANDO  " + state;
  if (tftCurrentPage == TFT_SETUP_PAGE) return String("SETUP  ") + TCT_PANELS[tftSetupSection].title;
  if (tftCurrentPage == TFT_PANEL_PAGE) return String("SETUP  ") + TCT_PANELS[tftSetupSection].title;
  if (tftCurrentPage == TFT_WIFI_PAGE) return "WIFI  " + tftWifiStateText();
  if (tftCurrentPage == TFT_KEYBOARD_PAGE) return "WIFI  " + String(kbTarget == 0 ? "NOME RETE" : "PASSWORD");
  if (tftCurrentPage == TFT_INFO_PAGE) return String("INFO  ") + CONTROLLER_VERSION_TEXT;
  String text = (mode == MODE_THREAD ? String("FILETTATURA") : printMode()) + " " + state;
  String message = buildDisplayMessage(0, 0, true, getJoystickPitchStatusDirection());
  if (message.length()) text += " " + message;
  return text;
}

void tftDrawFooter(bool force) {
  if (tftLayer != 0) return;
  String text = tftFooterText();
  if (!force && text == tftFooterCache) return;
  tftFooterCache = text;
  // Only pages 19..21 are painted on the #080808 background: every other page
  // (menu, service pages, keypad) has a #101010 strip under the footer.
  bool darkPage = tftCurrentPage == TFT_PANEL_PAGE || tftCurrentPage == TFT_KEYBOARD_PAGE || tftCurrentPage == TFT_WORK_PAGE;
  uint16_t bg = darkPage ? TFT_SERVICE_BG : TFT_BG_COLOR;
  tftLineLeft(10, 456, 710, text, bg);
}

// ---------- MENU ----------
static uint8_t tftMenuStateCache = 255;

void tftDrawMenuState(bool force) {
  uint8_t state = spindlePosSync ? 2 : isOn ? 1 : 0;
  if (!force && state == tftMenuStateCache) return;
  tftMenuStateCache = state;
  String text = state == 2 ? "SIN" : state == 1 ? "ON" : "OFF";
  tftFill(684, 18, 106, 38, TFT_CARD_COLOR);
  tftGlyphs(689, 24, "ELS");
  tftGlyphs(784 - (int)text.length() * TFT_GLYPH_W, 24, text);
}

// ---------- COMANDO ----------
static String tftComCache[8] = {"", "", "", "", "", "", "", ""};

void tftDrawComandoUpdate() {
  String value;
  value = tftStateText();
  if (value != tftComCache[0]) { tftComCache[0] = value; tftLineCenter(58, 88, 14, 103, value, TFT_CARD_COLOR); }
  value = tftModeName(mode);
  if (value != tftComCache[1]) { tftComCache[1] = value; tftLineCenter(219, 88, 116, 322, value, TFT_ACCENT_COLOR); }
  value = String(starts);
  if (value != tftComCache[2]) { tftComCache[2] = value; tftLineLeft(348, 96, 456, value, TFT_CARD_COLOR); }
  value = printDupr(nextDuprFlag ? nextDupr : dupr);
  if (value != tftComCache[3]) { tftComCache[3] = value; tftLineLeft(490, 96, 634, value, TFT_CARD_COLOR); }
  value = measure == MEASURE_METRIC ? "MM" : measure == MEASURE_INCH ? "POL" : "TPI";
  if (value != tftComCache[4]) { tftComCache[4] = value; tftLineLeft(666, 96, 778, value, TFT_GREEN_COLOR); }
  value = !x.active || x.disabled ? "" : printAxisPos(&x);
  if (value != tftComCache[5]) { tftComCache[5] = value; tftLineRight(70, 205, 260, value, TFT_CARD_COLOR); }
  value = !y.active || y.disabled ? "" : printAxisPos(&y);
  if (value != tftComCache[6]) { tftComCache[6] = value; tftLineRight(334, 205, 522, value, TFT_CARD_COLOR); }
  value = !z.active || z.disabled ? "" : printAxisPos(&z);
  if (value != tftComCache[7]) { tftComCache[7] = value; tftLineRight(598, 205, 784, value, TFT_CARD_COLOR); }
}

void tftDrawComandoAll() {
  // The STATO card is white in the background image: repaint it dark. The
  // MODALITA card is accent blue and gets the full name centered.
  tftFill(12, 72, 94, 57, TFT_CARD_COLOR);
  tftFill(114, 72, 210, 56, TFT_ACCENT_COLOR);
  // Tiny MAX/MIN headers cannot be redrawn at this glyph size: clear them.
  tftFill(118, 148, 134, 18, TFT_CARD_COLOR);
  tftFill(388, 148, 140, 18, TFT_CARD_COLOR);
  tftFill(650, 148, 140, 18, TFT_CARD_COLOR);
  for (int i = 0; i < 8; i++) tftComCache[i] = "";
  tftDrawComandoUpdate();
}

// ---------- INFO ----------
static String tftInfoCache[6] = {"", "", "", "", "", ""};

String tftUptimeText() {
  unsigned long total = millis() / 1000;
  unsigned long hours = total / 3600;
  total %= 3600;
  char buffer[12];
  snprintf(buffer, sizeof(buffer), "%02lu:%02lu:%02lu", hours % 100, total / 60, total % 60);
  return String(buffer);
}

void tftDrawInfoUpdate() {
  String value;
  value = String(CONTROLLER_VERSION_TEXT) + " 20261030";
  if (value != tftInfoCache[0]) { tftInfoCache[0] = value; tftLineLeft(30, 114, 390, value, TFT_CARD_COLOR); }
  value = "IT 20261030";
  if (value != tftInfoCache[1]) { tftInfoCache[1] = value; tftLineLeft(424, 114, 780, value, TFT_CARD_COLOR); }
  value = wifiIpAddress.length() > 0 ? wifiIpAddress : "---";
  if (value != tftInfoCache[2]) { tftInfoCache[2] = value; tftLineLeft(30, 238, 390, value, TFT_CARD_COLOR); }
  value = tftUptimeText();
  if (value != tftInfoCache[3]) { tftInfoCache[3] = value; tftLineLeft(424, 238, 780, value, TFT_CARD_COLOR); }
  value = String(ESP.getFreeHeap() / 1048576.0, 1) + " MB";
  if (value != tftInfoCache[4]) { tftInfoCache[4] = value; tftLineLeft(30, 362, 390, value, TFT_CARD_COLOR); }
  value = "0 NESSUNO";
  if (value != tftInfoCache[5]) { tftInfoCache[5] = value; tftLineLeft(424, 362, 780, value, TFT_CARD_COLOR); }
}

void tftDrawInfoAll() {
  for (int i = 0; i < 6; i++) tftInfoCache[i] = "";
  tftDrawInfoUpdate();
}

// ---------- WIFI ----------
String tftWifiStateText() {
  if (!WIFI_ENABLED) return "DISATTIVATO";
  if (wifiSetupApActive) return "AP SETUP";
  if (wifiStationConnected) return "CONNESSO";
  return "CONNESSIONE";
}

static String tftWifiCache[7] = {"", "", "", "", "", "", ""};
static bool tftWifiForgetArm = false;
static unsigned long tftWifiForgetMs = 0;

void tftDrawWifiUpdate() {
  String value;
  value = WIFI_SSID.length() > 0 ? WIFI_SSID : "---";
  if (value != tftWifiCache[0]) { tftWifiCache[0] = value; tftLineLeft(34, 139, 456, value, TFT_BG_COLOR); }
  // Never reveal the stored password: fixed mask, no length.
  value = WIFI_PASSWORD.length() > 0 ? "********" : "---";
  if (value != tftWifiCache[1]) { tftWifiCache[1] = value; tftLineLeft(34, 216, 456, value, TFT_BG_COLOR); }
  value = tftWifiStateText();
  if (value != tftWifiCache[2]) { tftWifiCache[2] = value; tftLineRight(24, 332, 470, value, TFT_CARD_COLOR); }
  value = wifiIpAddress.length() > 0 ? wifiIpAddress : "---";
  if (value != tftWifiCache[3]) { tftWifiCache[3] = value; tftLineRight(24, 356, 470, value, TFT_CARD_COLOR); }
  value = tftWifiStateText();
  if (value != tftWifiCache[4]) { tftWifiCache[4] = value; tftLineCenter(645, 222, 508, 782, value, TFT_CARD_COLOR); }
  value = WIFI_SSID.length() > 0 ? WIFI_SSID : "---";
  if (value != tftWifiCache[5]) { tftWifiCache[5] = value; tftLineCenter(645, 250, 508, 782, value, TFT_CARD_COLOR); }
  value = wifiIpAddress.length() > 0 ? wifiIpAddress : "---";
  if (value != tftWifiCache[6]) { tftWifiCache[6] = value; tftLineCenter(645, 278, 508, 782, value, TFT_CARD_COLOR); }
}

void tftDrawWifiAll() {
  for (int i = 0; i < 7; i++) tftWifiCache[i] = "";
  tftDrawWifiUpdate();
  tftDrawFooter(true);
}

void tftWifiConnect() {
  if (WIFI_SSID.length() == 0) {
    tftSetStatus("IMPOSTA IL NOME RETE", 4000);
    beep();
    return;
  }
  WIFI_ENABLED = true;
  saveWifiConfig();
  tftSetStatus("SALVATO, RIAVVIO...", 5000);
  scheduleConfigRestart();
}

void tftWifiForget() {
  if (isOn) {
    tftSetStatus("SPEGNI PRIMA", 3000);
    beep();
    return;
  }
  if (!tftWifiForgetArm || (long)(millis() - tftWifiForgetMs) >= 0) {
    tftWifiForgetArm = true;
    tftWifiForgetMs = millis() + 3000;
    tftSetStatus("TOCCA DI NUOVO PER DIMENTICARE", 3000);
    return;
  }
  tftWifiForgetArm = false;
  setWifiConfigDefaults();
  saveWifiConfig();
  tftSetStatus("WIFI CANCELLATO, RIAVVIO...", 5000);
  scheduleConfigRestart();
}

// ---------- Text keyboard (page 20) ----------
static const char KB_KEYS[4][10] = {
  {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
  {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
  {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 0, 0},
  {'z', 'x', 'c', 'v', 'b', 'n', 'm', '.', '-', '_'},
};
static const uint8_t KB_COUNTS[4] = {10, 10, 9, 10};
#define KB_KEY_W 74
#define KB_KEY_H 46
#define KB_KEY_GAP 4
#define KB_ROW_Y 120
#define KB_ROW_STEP 52

void tftKbDrawField() {
  tftFill(12, 50, 776, 44, TFT_BUTTON_COLOR);
  String text;
  if (kbTarget == 1) {
    for (int i = 0; i < kbLen; i++) text += '*';
  } else {
    text = String(kbBuf);
  }
  int maxGlyphs = (776 - 24 + 2) / TFT_GLYPH_W;
  if ((int)text.length() > maxGlyphs) text = text.substring(text.length() - maxGlyphs);
  tftLineRight(24, 59, 776, text, TFT_BUTTON_COLOR);
}

void tftKbDraw() {
  tftFill(0, 0, 800, 480, TFT_SERVICE_BG);
  tftGlyphs(24, 14, kbTarget == 0 ? "NOME RETE (SSID)" : "PASSWORD");
  tftKbDrawField();
  for (int row = 0; row < 4; row++) {
    int count = KB_COUNTS[row];
    int total = count * KB_KEY_W + (count - 1) * KB_KEY_GAP;
    int x0 = (800 - total) / 2;
    int y = KB_ROW_Y + row * KB_ROW_STEP;
    for (int i = 0; i < count; i++) {
      int x = x0 + i * (KB_KEY_W + KB_KEY_GAP);
      tftFill(x, y, KB_KEY_W, KB_KEY_H, TFT_BUTTON_COLOR);
      char c = KB_KEYS[row][i];
      if (kbShift && c >= 'a' && c <= 'z') c -= 32;
      tftLineCenter(x + KB_KEY_W / 2, y + 10, x, x + KB_KEY_W, String(c), TFT_BUTTON_COLOR);
    }
  }
  int sy = 340;
  tftFill(12, sy, 140, KB_KEY_H, kbShift ? TFT_ACCENT_COLOR : TFT_BUTTON_COLOR);
  tftLineCenter(82, sy + 10, 12, 152, "MAIUSC", kbShift ? TFT_ACCENT_COLOR : TFT_BUTTON_COLOR);
  tftFill(158, sy, 280, KB_KEY_H, TFT_BUTTON_COLOR);
  tftLineCenter(298, sy + 10, 158, 438, "SPAZIO", TFT_BUTTON_COLOR);
  tftFill(444, sy, 140, KB_KEY_H, TFT_BUTTON_COLOR);
  tftLineCenter(514, sy + 10, 444, 584, "CANC", TFT_BUTTON_COLOR);
  tftFill(590, sy, 100, KB_KEY_H, TFT_BUTTON_COLOR);
  tftLineCenter(640, sy + 10, 590, 690, "ANN.", TFT_BUTTON_COLOR);
  tftFill(696, sy, 92, KB_KEY_H, TFT_GREEN_COLOR);
  tftLineCenter(742, sy + 10, 696, 788, "OK", TFT_GREEN_COLOR);
}

void tftKbCopyText(const String &text) {
  kbLen = 0;
  uint8_t maxLen = kbTarget == 0 ? 32 : 63;
  for (int i = 0; i < (int)text.length() && kbLen < maxLen; i++) kbBuf[kbLen++] = text[i];
  kbBuf[kbLen] = 0;
}

void tftKbOpen(uint8_t target) {
  kbTarget = target;
  kbShift = false;
  // Password buffer always starts empty: an empty confirmation keeps the
  // stored password untouched.
  tftKbCopyText(target == 0 ? WIFI_SSID : String(""));
  toScreen("page " + String(TFT_KEYBOARD_PAGE));
}

void tftKbChar(char c) {
  uint8_t maxLen = kbTarget == 0 ? 32 : 63;
  if (kbLen >= maxLen) {
    beep();
    return;
  }
  kbBuf[kbLen++] = c;
  kbBuf[kbLen] = 0;
  tftKbDrawField();
}

void tftKbOk() {
  if (kbTarget == 0) {
    String ssid = String(kbBuf);
    ssid.trim();
    if (ssid.length() == 0) {
      tftSetStatus("NOME RETE VUOTO", 4000);
      beep();
      toScreen("page " + String(TFT_WIFI_PAGE));
      return;
    }
    WIFI_SSID = ssid;
    WIFI_ENABLED = true;
  } else {
    if (kbLen > 0 && kbLen < 8) {
      tftSetStatus("MIN 8 CARATTERI", 4000);
      beep();
      return;
    }
    if (kbLen > 0) WIFI_PASSWORD = String(kbBuf);
  }
  saveWifiConfig();
  tftSetStatus("SALVATO, RIAVVIO...", 5000);
  toScreen("page " + String(TFT_WIFI_PAGE));
  scheduleConfigRestart();
}

bool tftKbEvent(uint8_t code) {
  if (code == 0x10) {
    tftCurrentPage = TFT_KEYBOARD_PAGE;
    tftKbDraw();
    tftDrawFooter(true);
    return true;
  }
  if (code >= 0x70 && code <= 0x79) {
    tftKbChar(KB_KEYS[0][code - 0x70]);
  } else if (code >= 0x80 && code <= 0x89) {
    char c = KB_KEYS[1][code - 0x80];
    tftKbChar(kbShift && c >= 'a' && c <= 'z' ? c - 32 : c);
  } else if (code >= 0x90 && code <= 0x98) {
    char c = KB_KEYS[2][code - 0x90];
    tftKbChar(kbShift && c >= 'a' && c <= 'z' ? c - 32 : c);
  } else if (code >= 0xA0 && code <= 0xA9) {
    char c = KB_KEYS[3][code - 0xA0];
    tftKbChar(kbShift && c >= 'a' && c <= 'z' ? c - 32 : c);
  } else if (code == 0xB0) {
    kbShift = !kbShift;
    tftKbDraw();
  } else if (code == 0xB1) {
    tftKbChar(' ');
  } else if (code == 0xB2) {
    if (kbLen > 0) {
      kbBuf[--kbLen] = 0;
      tftKbDrawField();
    }
  } else if (code == 0xB3) {
    toScreen("page " + String(TFT_WIFI_PAGE));
  } else if (code == 0xB4) {
    tftKbOk();
  }
  return true;
}

// ---------- G-CODE ----------
#define TFT_GCODE_MAX 32
#define TFT_GCODE_ROW_TOP 109
#define TFT_GCODE_ROW_STEP 66

static String tftGcodeNames[TFT_GCODE_MAX];
static long tftGcodeSizes[TFT_GCODE_MAX];
static int tftGcodeCount = 0;
static int tftGcodeSel = 0;
static int tftGcodeTop = 0;
static bool tftGcodeExecArm = false;
static unsigned long tftGcodeExecMs = 0;
static bool tftGcodeDeleteArm = false;
static unsigned long tftGcodeDeleteMs = 0;
static bool tftGcodePendingRun = false;

int tftGcodeList(String* names, long* sizes, int max) {
  File root = LittleFS.open("/");
  if (!root || !root.isDirectory()) return 0;
  int count = 0;
  File file = root.openNextFile();
  while (file) {
    String name = file.name();
    long size = file.size();
    file.close();
    int slash = name.lastIndexOf('/');
    if (slash >= 0) name = name.substring(slash + 1);
    if (name.endsWith(".gcode")) {
      if (count < max) {
        names[count] = name.substring(0, name.length() - 6);
        sizes[count] = size;
      }
      count++;
    }
    file = root.openNextFile();
  }
  return count;
}

String tftBytesText(long size) {
  if (size < 1024) return String(size) + " B";
  return String(size / 1024.0, 1) + " KB";
}

void tftGcodeDetails(String* name, String* sizeText, String* linesText, String* timeText) {
  *name = "";
  *sizeText = "";
  *linesText = "";
  *timeText = "";
  if (tftGcodeCount == 0 || tftGcodeSel < 0 || tftGcodeSel >= tftGcodeCount) return;
  const String &base = tftGcodeNames[tftGcodeSel];
  *name = base;
  *sizeText = tftBytesText(tftGcodeSizes[tftGcodeSel]);
  File file = LittleFS.open("/" + base + ".gcode", "r");
  if (!file) return;
  long lines = 0;
  bool hasBytes = false;
  char last = 0;
  uint8_t buf[128];
  while (true) {
    size_t n = file.read(buf, sizeof(buf));
    if (n == 0) break;
    hasBytes = true;
    for (size_t i = 0; i < n; i++) {
      if (buf[i] == '\n') lines++;
    }
    last = (char)buf[n - 1];
  }
  if (hasBytes && last != '\n') lines++;
  time_t modified = file.getLastWrite();
  file.close();
  *linesText = String(lines);
  struct tm info;
  if (modified > 0 && gmtime_r(&modified, &info) != NULL) {
    char buffer[18];
    snprintf(buffer, sizeof(buffer), "%02d/%02d %02d:%02d", info.tm_mday, info.tm_mon + 1, info.tm_hour, info.tm_min);
    *timeText = buffer;
  } else {
    *timeText = "---";
  }
}

void tftDrawGcodeAll() {
  tftGcodeCount = tftGcodeList(tftGcodeNames, tftGcodeSizes, TFT_GCODE_MAX);
  gcodeProgramCount = tftGcodeCount;
  if (tftGcodeCount == 0) tftGcodeSel = 0;
  else if (tftGcodeSel >= tftGcodeCount) tftGcodeSel = tftGcodeCount - 1;
  if (tftGcodeTop > tftGcodeSel) tftGcodeTop = tftGcodeSel;
  if (tftGcodeSel > tftGcodeTop + 3) tftGcodeTop = tftGcodeSel - 3;
  // The header sits on the list card, not on the page background.
  tftFill(20, 78, 300, 28, TFT_CARD_COLOR);
  tftGlyphs(24, 80, "FILE SALVATI");
  tftLineLeft(224, 80, 320, String(tftGcodeCount), TFT_CARD_COLOR);
  for (int i = 0; i < 4; i++) {
    int y = TFT_GCODE_ROW_TOP + i * TFT_GCODE_ROW_STEP;
    int index = tftGcodeTop + i;
    uint16_t bg = index == tftGcodeSel ? TFT_SELECT_COLOR : TFT_ROW_COLOR;
    tftFill(26, y, 448, 56, bg);
    if (index < tftGcodeCount) {
      tftLineLeft(39, y + 15, 310, tftGcodeNames[index], bg);
      tftLineRight(320, y + 15, 461, tftBytesText(tftGcodeSizes[index]), bg);
    }
  }
  String name, sizeText, linesText, timeText;
  tftGcodeDetails(&name, &sizeText, &linesText, &timeText);
  if (name.length() > 0) {
    tftLineLeft(516, 104, 782, name, TFT_CARD_COLOR);
    tftLineRight(600, 140, 775, sizeText, TFT_CARD_COLOR);
    tftLineRight(600, 164, 775, linesText, TFT_CARD_COLOR);
    tftLineRight(600, 188, 775, timeText, TFT_CARD_COLOR);
  } else {
    tftFill(510, 100, 272, 112, TFT_CARD_COLOR);
    tftLineLeft(516, 104, 782, "NESSUN FILE", TFT_CARD_COLOR);
  }
  tftDrawFooter(true);
}

void tftGcodeSelect(int index) {
  if (tftGcodeCount == 0) return;
  tftGcodeSel = constrain(index, 0, tftGcodeCount - 1);
  if (tftGcodeSel < tftGcodeTop) tftGcodeTop = tftGcodeSel;
  if (tftGcodeSel > tftGcodeTop + 3) tftGcodeTop = tftGcodeSel - 3;
  tftDrawGcodeAll();
}

void tftGcodeExecute() {
  if (tftGcodeCount == 0) {
    tftSetStatus("NESSUN PROGRAMMA", 3000);
    beep();
    return;
  }
  if (isOn) {
    tftSetStatus("SPEGNI PRIMA", 3000);
    beep();
    return;
  }
  if (!tftGcodeExecArm || (long)(millis() - tftGcodeExecMs) >= 0) {
    tftGcodeExecArm = true;
    tftGcodeExecMs = millis() + 3000;
    tftSetStatus("TOCCA DI NUOVO PER ESEGUIRE", 3000);
    return;
  }
  tftGcodeExecArm = false;
  gcodeProgramIndex = tftGcodeSel;
  tftGcodePendingRun = true;
  if (mode != MODE_GCODE) setModeFromTask(MODE_GCODE);
  tftSetStatus("AVVIO G-CODE...", 4000);
}

void tftGcodeDelete() {
  if (tftGcodeCount == 0) return;
  if (isOn) {
    tftSetStatus("SPEGNI PRIMA", 3000);
    beep();
    return;
  }
  if (!tftGcodeDeleteArm || (long)(millis() - tftGcodeDeleteMs) >= 0) {
    tftGcodeDeleteArm = true;
    tftGcodeDeleteMs = millis() + 3000;
    tftSetStatus("TOCCA DI NUOVO PER ELIMINARE", 3000);
    return;
  }
  tftGcodeDeleteArm = false;
  String name = tftGcodeNames[tftGcodeSel];
  if (removeGcodeByName(name)) {
    tftSetStatus("ELIMINATO " + name, 4000);
  } else {
    tftSetStatus("ERRORE ELIMINAZIONE", 4000);
  }
  tftDrawGcodeAll();
}

// ---------- Settings panel (page 19) ----------
String tctEditText(const TctRow &row) {
  switch (row.kind) {
    case TCT_I: return String(*(int*)row.p);
    case TCT_L: case TCT_MM: return String(*(long*)row.p);
    case TCT_FLOAT: return String(*(float*)row.p, 3);
    case TCT_DU: return String(*(long*)row.p / 10000.0, 3);
    case TCT_STOP: {
      Axis* a = tctAxis(row.a);
      bool isLeft = row.b != 0;
      long stop = isLeft ? a->leftStop : a->rightStop;
      if (isLeft ? stop == LONG_MAX : stop == LONG_MIN) return "";
      long du = stepsToDu(a, stop);
      return measure == MEASURE_METRIC ? String(du / 10000.0, 2) : printDeciMicrons(du, 2);
    }
  }
  return "";
}

void tctApply(const TctRow &row, float value) {
  switch (row.kind) {
    case TCT_I: {
      long v = (long)round(value);
      *(int*)row.p = (int)constrain(v, row.a, row.b);
      break;
    }
    case TCT_L: case TCT_MM: {
      long v = (long)round(value);
      *(long*)row.p = constrain(v, row.a, row.b);
      break;
    }
    case TCT_FLOAT: *(float*)row.p = value; break;
    case TCT_DU: {
      long v = (long)round(value * 10000.0);
      *(long*)row.p = constrain(v, row.a, row.b);
      break;
    }
    case TCT_STOP: {
      Axis* a = tctAxis(row.a);
      bool isLeft = row.b != 0;
      long du = measure == MEASURE_METRIC ? (long)round(value * 10000.0) : (long)round(value * 254000.0);
      long steps = duToSteps(a, du);
      if (isLeft) {
        if (a->rightStop != LONG_MIN && steps <= a->rightStop) return;
        setLeftStop(a, steps);
      } else {
        if (a->leftStop != LONG_MAX && steps >= a->leftStop) return;
        setRightStop(a, steps);
      }
      break;
    }
    default: return;
  }
  saveMachineConfig();
}

void tctAdjust(const TctRow &row, bool plus) {
  switch (row.kind) {
    case TCT_I: {
      long v = *(int*)row.p + (plus ? 1 : -1);
      *(int*)row.p = (int)constrain(v, row.a, row.b);
      break;
    }
    case TCT_L: case TCT_MM: {
      long v = *(long*)row.p + (plus ? 1 : -1);
      *(long*)row.p = constrain(v, row.a, row.b);
      break;
    }
    case TCT_DU: {
      long v = *(long*)row.p + (plus ? 100 : -100);
      *(long*)row.p = constrain(v, row.a, row.b);
      break;
    }
    case TCT_FLOAT: *(float*)row.p = *(float*)row.p + (plus ? 0.01f : -0.01f); break;
    case TCT_STOP: {
      Axis* a = tctAxis(row.a);
      bool isLeft = row.b != 0;
      long cur = isLeft ? a->leftStop : a->rightStop;
      if (isLeft ? cur == LONG_MAX : cur == LONG_MIN) cur = a->pos;
      long step = duToSteps(a, 100);
      if (step < 1) step = 1;
      long next = cur + (plus ? step : -step);
      if (isLeft) {
        if (a->rightStop != LONG_MIN && next <= a->rightStop) return;
        setLeftStop(a, next);
      } else {
        if (a->leftStop != LONG_MAX && next >= a->leftStop) return;
        setRightStop(a, next);
      }
      break;
    }
    default: return;
  }
  saveMachineConfig();
}

void tctToggle(const TctRow &row) {
  if (row.kind == TCT_B) {
    *(bool*)row.p = !*(bool*)row.p;
    saveMachineConfig();
    if (row.p == &ACTIVE_Y || row.p == &ROTARY_Y) {
      tftSetStatus("RIAVVIO PER APPLICARE", 5000);
      scheduleConfigRestart();
    }
  } else if (row.kind == TCT_MEASURE) {
    buttonMeasurePress();
  }
}

void tctAction(uint8_t index, const TctRow &row) {
  if (isOn) {
    tftSetStatus("SPEGNI PRIMA", 3000);
    beep();
    return;
  }
  if (tftActionArmed != index || (long)(millis() - tftActionArmMs) >= 0) {
    tftActionArmed = index;
    tftActionArmMs = millis() + 3000;
    tftSetStatus("TOCCA DI NUOVO PER CONFERMARE", 3000);
    return;
  }
  tftActionArmed = 255;
  if (row.a == 0) {
    setMachineConfigDefaults();
    saveMachineConfig();
    tftSetStatus("RIPRISTINO, RIAVVIO...", 5000);
  } else {
    setWifiConfigDefaults();
    saveWifiConfig();
    tftSetStatus("WIFI CANCELLATO, RIAVVIO...", 5000);
  }
  scheduleConfigRestart();
}

void tftDrawSetupPanel() {
  const TctPanel &panel = TCT_PANELS[tftSetupSection];
  tftFill(0, 0, 800, 480, TFT_SERVICE_BG);
  tftFill(0, 0, 800, 52, TFT_CARD_COLOR);
  tftGlyphs(24, 14, panel.title);
  tftFill(716, 10, 72, 32, TFT_BUTTON_COLOR);
  tftLineCenter(752, 13, 716, 788, "X", TFT_BUTTON_COLOR);
  int start = tftSetupPage * TFT_SETUP_PAGE_SIZE;
  for (int i = 0; i < TFT_SETUP_PAGE_SIZE; i++) {
    int index = start + i;
    if (index >= panel.count) break;
    const TctRow &row = panel.rows[index];
    int y = 68 + i * 46;
    tftFill(12, y, 776, 42, TFT_CARD_COLOR);
    tftLineLeft(24, y + 8, 300, row.label, TFT_CARD_COLOR);
    String value = row.kind == TCT_ACTION && tftActionArmed == index ? "CONFERMA" : tctText(row);
    tftLineRight(308, y + 8, 620, value, TFT_CARD_COLOR);
    if (row.kind != TCT_INFO && row.kind != TCT_B && row.kind != TCT_MEASURE && row.kind != TCT_ACTION) {
      tftFill(636, y + 4, 44, 34, TFT_BUTTON_COLOR);
      tftLineCenter(658, y + 8, 636, 680, "-", TFT_BUTTON_COLOR);
      tftFill(692, y + 4, 44, 34, TFT_BUTTON_COLOR);
      tftLineCenter(714, y + 8, 692, 736, "+", TFT_BUTTON_COLOR);
    }
  }
  int pages = (panel.count + TFT_SETUP_PAGE_SIZE - 1) / TFT_SETUP_PAGE_SIZE;
  if (pages > 1) {
    if (tftSetupPage > 0) {
      tftFill(24, 404, 120, 40, TFT_BUTTON_COLOR);
      tftLineCenter(84, 411, 24, 144, "PREC", TFT_BUTTON_COLOR);
    }
    if (tftSetupPage + 1 < pages) {
      tftFill(656, 404, 120, 40, TFT_BUTTON_COLOR);
      tftLineCenter(716, 411, 656, 776, "SUCC", TFT_BUTTON_COLOR);
    }
    tftLineCenter(400, 411, 300, 500, String(tftSetupPage + 1) + "/" + String(pages), TFT_SERVICE_BG);
  }
  tftDrawFooter(true);
}

// FNV hash of the visible field texts and of the state text: the mode pages
// are repainted only when something actually changes.
static uint8_t tftPageHashId = 255;
static uint32_t tftPageHashValue = 0;

// The PostInit (0x10) event arrives while the display is still decoding the
// 800x480 page background: commands sent in that window are misparsed and the
// first value box comes out as solid white blocks (the "veil" over PASSO
// after the keypad returns). The repaint is deferred until the render is
// over, then repeated once as a safety net.
static uint8_t tftModeRepaintPage = 255;
static unsigned long tftModeRepaintAtMs = 0;
static uint8_t tftModeRepaintPass = 0;
// LAVORAZIONE (page 21) needs the same treatment: painting it straight from
// the PostInit event garbles the values over the decoding background and the
// cache then keeps them from ever being redrawn.
static uint8_t tftWorkRepaintPass = 0;
static unsigned long tftWorkRepaintAtMs = 0;

uint32_t tftPageHash(uint8_t page);

void tftRunDeferredModeRepaint() {
  if (tftWorkRepaintPass != 0) {
    if ((long)(millis() - tftWorkRepaintAtMs) < 0) return;
    tftPaceCommands = true;
    tftDrawWorkAll();
    tftPaceCommands = false;
    if (tftWorkRepaintPass == 1) {
      tftWorkRepaintPass = 2;
      tftWorkRepaintAtMs = millis() + 500;
    } else {
      tftWorkRepaintPass = 0;
    }
    return;
  }
  if (tftModeRepaintPage == 255) return;
  if ((long)(millis() - tftModeRepaintAtMs) < 0) return;
  uint8_t page = tftModeRepaintPage;
  if (page >= TFT_PAGE_COUNT) {
    tftModeRepaintPage = 255;
    return;
  }
  tftPaceCommands = true;
  const TftPage &pg = TFT_PAGES[page];
  for (uint8_t i = 0; i < pg.count; i++) tftDrawField(pg.f[i], page);
  tftDrawCardBackdrop(page);
  for (uint8_t i = 0; i < 2; i++) tftDrawCardField(pg.c[i]);
  tftDrawStatus(page);
  tftDrawFooter(true);
  tftPaceCommands = false;
  tftPageHashId = page;
  tftPageHashValue = tftPageHash(page);
  if (tftModeRepaintPass == 0) {
    tftModeRepaintPass = 1;
    tftModeRepaintAtMs = millis() + 500;
  } else {
    tftModeRepaintPage = 255;
  }
}

uint32_t tftPageHash(uint8_t page) {
  const TftPage &pg = TFT_PAGES[page];
  uint32_t h = 2166136261u;
  h = (h ^ (spindlePosSync ? 2u : isOn ? 1u : 0u)) * 16777619u;
  for (uint8_t i = 0; i < pg.count; i++) {
    String text = tftFieldText(pg.f[i]);
    for (int j = 0; j < (int)text.length(); j++) h = (h ^ (uint8_t)text[j]) * 16777619u;
    h = (h ^ (uint8_t)'|') * 16777619u;
  }
  return h;
}

// Runs from updateDisplay(): periodic values, jog watchdog and the deferred
// G-code start (the mode change is applied by applySettings, so the start must
// wait for the next tick).
void tftServiceTick() {
  if (tftUploadActive) return;
  unsigned long now = millis();
  if (tftHeldMove != 0 && now - tftHeldMoveMs > 15000) {
    setMoveButtonPressed(B_RIGHT, false);
    setMoveButtonPressed(B_LEFT, false);
    setMoveButtonPressed(B_FORWARD, false);
    setMoveButtonPressed(B_BACK, false);
    setMoveButtonPressed(B_UP, false);
    setMoveButtonPressed(B_DOWN, false);
    tftHeldMove = 0;
  }
  if (tftGcodePendingRun && mode == MODE_GCODE && !nextModeFlag && !isOn) {
    tftGcodePendingRun = false;
    setupIndex = 2;
    if (micros() <= spindleEncTime + 100000) {
      tftSetStatus("ACCENDI IL MANDRINO", 5000);
    } else {
      String name = getCurrentGcodeProgramName();
      gcodeProgram = readGcodeProgram(name);
      if (gcodeProgram.length() == 0) {
        tftSetStatus("PROGRAMMA NON VALIDO", 4000);
        beep();
      } else {
        gcodeProgram += '\n';
        resetGcodeState();
        setIsOnFromTask(true);
        tftSetStatus("G-CODE IN CORSO", 4000);
      }
    }
  }
  if (tftCurrentPage == 255) return;
  // While a deferred page repaint is pending the display is still settling:
  // the service tick must not join in mid-sequence.
  if (tftModeRepaintPage != 255) return;
  if (tftWorkRepaintPass != 0) return;
  if (now - tftLastDynamicMs < 250) return;
  tftLastDynamicMs = now;
  if (tftCurrentPage == TFT_MENU_PAGE) {
    tftDrawMenuState(false);
  } else if (tftCurrentPage == TFT_COMANDO_PAGE) {
    tftDrawComandoUpdate();
  } else if (tftCurrentPage == TFT_WIFI_PAGE) {
    tftDrawWifiUpdate();
  } else if (tftCurrentPage == TFT_INFO_PAGE) {
    tftDrawInfoUpdate();
  } else if ((tftCurrentPage >= 1 && tftCurrentPage <= 12) || tftCurrentPage == 17) {
    uint32_t hash = tftPageHash(tftCurrentPage);
    if (tftCurrentPage != tftPageHashId || hash != tftPageHashValue) {
      tftPageHashId = tftCurrentPage;
      tftPageHashValue = hash;
      tftDrawPage(tftCurrentPage);
      tftDrawStatus(tftCurrentPage);
    }
  } else if (tftCurrentPage == TFT_WORK_PAGE) {
    tftDrawWorkUpdate();
  } else {
    return;
  }
  tftDrawFooter(false);
}


// Tapping a value zone sends 0x40+i; the firmware opens page 18, shows the
// current value in the black card (2x glyph sprite) and applies what is typed
// on OK. Digits 0x50..0x59, '.' 0x5E, backspace 0x5B, OK 0x5C, cancel 0x5D.
#define TFT_KEYPAD_PAGE 18
#define TFT_KEYPAD_SPRITE 39
#define TFT_KEYPAD_GLYPH_W 32
#define TFT_KEYPAD_GLYPH_H 52
#define TFT_KEYPAD_COLS 50
#define TFT_KEYPAD_RIGHT 768
#define TFT_KEYPAD_Y 104
#define TFT_KEYPAD_MAXLEN 12

static uint8_t keypadPage = 255;
static uint8_t keypadIndex = 0;
static char keypadBuf[TFT_KEYPAD_MAXLEN + 1];
static uint8_t keypadLen = 0;
static bool keypadFresh = false;
// The keypad is also used for the settings panel (a TctRow), for COMANDO
// (starts/pitch) and for the Z fine stops: in those cases the target is not a
// TftField of a mode page.
static const TctRow* keypadRow = NULL;
static uint8_t keypadKind = TK_NONE;
static uint8_t keypadReturnPage = 255;

void tftKeypadDraw() {
  toScreen("fill 13,79,773,102,0");
  if (keypadLen == 0) return;
  String text = String(keypadBuf);
  int n = text.length();
  int left = TFT_KEYPAD_RIGHT - n * TFT_KEYPAD_GLYPH_W;
  for (int i = 0; i < n; i++) {
    int code = (int)text[i] - 32;
    if (code < 0 || code > 58) continue;
    int sx = (code % TFT_KEYPAD_COLS) * TFT_KEYPAD_GLYPH_W;
    int sy = (code / TFT_KEYPAD_COLS) * TFT_KEYPAD_GLYPH_H;
    toScreen("xpic " + String(left + i * TFT_KEYPAD_GLYPH_W) + "," + String(TFT_KEYPAD_Y) + "," + String(TFT_KEYPAD_GLYPH_W) + "," + String(TFT_KEYPAD_GLYPH_H) + "," + String(sx) + "," + String(sy) + "," + String(TFT_KEYPAD_SPRITE));
  }
}

void tftKeypadLoad(const String &text) {
  keypadFresh = true;
  keypadLen = 0;
  keypadBuf[0] = 0;
  String t = text == "---" ? String("") : text;
  for (int i = 0; i < (int)t.length() && keypadLen < TFT_KEYPAD_MAXLEN; i++) {
    keypadBuf[keypadLen++] = t[i];
  }
  keypadBuf[keypadLen] = 0;
  toScreen("page " + String(TFT_KEYPAD_PAGE));
  tftKeypadDraw();
}

void tftKeypadOpen(uint8_t page, uint8_t index) {
  const TftField &f = TFT_PAGES[page].f[index];
  keypadPage = page;
  keypadIndex = index;
  keypadRow = NULL;
  keypadKind = TK_NONE;
  keypadReturnPage = 255;
  tftKeypadLoad(tftFieldText(f));
}

// Numeric value that is not a TftField (COMANDO starts/pitch, Z fine stops).
void tftKeypadOpenValue(uint8_t page, uint8_t kind, const String &text) {
  keypadPage = 255;
  keypadIndex = 0;
  keypadRow = NULL;
  keypadKind = kind;
  keypadReturnPage = page;
  tftKeypadLoad(text);
}

// Row of the settings panel: the value is re-read from the live variable.
void tftKeypadOpenRow(const TctRow &row) {
  keypadPage = 255;
  keypadIndex = 0;
  keypadRow = &row;
  keypadKind = TK_NONE;
  keypadReturnPage = TFT_PANEL_PAGE;
  tftKeypadLoad(tctEditText(row));
}

void tftKeypadDigit(char c) {
  if (keypadFresh) {
    keypadLen = 0;
    keypadBuf[0] = 0;
    keypadFresh = false;
  }
  if (c == '.') {
    if (strchr(keypadBuf, '.') != NULL) return;
    if (keypadLen == 0) keypadBuf[keypadLen++] = '0';
  }
  if (keypadLen >= TFT_KEYPAD_MAXLEN) return;
  keypadBuf[keypadLen++] = c;
  keypadBuf[keypadLen] = 0;
  tftKeypadDraw();
}

void tftKeypadBackspace() {
  if (keypadFresh) {
    keypadLen = 0;
    keypadBuf[0] = 0;
    keypadFresh = false;
  } else if (keypadLen > 0) {
    keypadBuf[--keypadLen] = 0;
  }
  tftKeypadDraw();
}

void tftKeypadSetStop(Axis* a, bool isLeft, float value) {
  long du = measure == MEASURE_METRIC ? round(value * 10000.0) : round(value * 254000.0);
  long steps = duToSteps(a, du);
  if (isLeft) {
    if (a->rightStop != LONG_MIN && steps <= a->rightStop) return;
    setLeftStop(a, steps);
  } else {
    if (a->leftStop != LONG_MAX && steps >= a->leftStop) return;
    setRightStop(a, steps);
  }
}

void tftKeypadApply() {
  // Nothing typed: keep the current value untouched (also avoids rounding
  // the displayed text back into the setting).
  if (keypadLen == 0 || keypadFresh) return;
  float v = atof(keypadBuf);
  if (keypadRow != NULL) {
    tctApply(*keypadRow, v);
    return;
  }
  uint8_t kind = keypadKind;
  if (kind == TK_NONE) {
    if (keypadPage >= TFT_PAGE_COUNT) return;
    kind = TFT_PAGES[keypadPage].f[keypadIndex].kind;
  }
  switch (kind) {
    case TK_PITCH: {
      long du;
      if (measure == MEASURE_TPI) du = v > 0 ? round(254000.0 / v) : 0;
      else if (measure == MEASURE_INCH) du = round(v * 254000.0);
      else du = round(v * 10000.0);
      if (du != 0 && abs(du) <= DUPR_MAX) setDupr(du);
      break;
    }
    case TK_STARTS: setStarts(constrain((long)round(v), 1L, (long)STARTS_MAX)); break;
    case TK_PASSES: setTurnPasses(constrain((long)round(v), 1L, PASSES_MAX)); break;
    case TK_RATIO: setConeRatio(constrain(v, 0.0f, 10.0f)); break;
    case TK_DIABIG:
    case TK_DIASMALL: {
      long du = constrain((long)round(v * 10000.0), 0L, 9999900L);
      if (kind == TK_DIABIG) CONE_DIA_BIG_DU = max(du, 1000L);
      else CONE_DIA_SMALL_DU = du;
      saveMachineConfig();
      recomputeConeRatio();
      break;
    }
    case TK_ZMAX: tftKeypadSetStop(&z, true, v); break;
    case TK_ZMIN: tftKeypadSetStop(&z, false, v); break;
    case TK_XMAX: tftKeypadSetStop(&x, true, v); break;
    case TK_XMIN: tftKeypadSetStop(&x, false, v); break;
    case TK_YMAX: tftKeypadSetStop(&y, true, v); break;
    case TK_JOYN: JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND = constrain(v, 0.1f, 10.0f); break;
    case TK_JOYR: JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND = constrain(v, 0.1f, 20.0f); break;
    case TK_JOYD: JOYSTICK_DEADBAND = constrain((long)round(v), 0L, (long)JOYSTICK_ADC_MAX - 1); break;
    case TK_SLOTRED: {
      SLOT_LEFT_REDUCTION_DU = constrain((long)round(v * 10000.0), 0L, 10000000L);
      saveMachineConfig();
      break;
    }
  }
}

void tftKeypadReturn() {
  uint8_t page = keypadReturnPage != 255 ? keypadReturnPage : keypadPage;
  keypadPage = 255;
  keypadRow = NULL;
  keypadKind = TK_NONE;
  keypadReturnPage = 255;
  if (page != 255) toScreen("page " + String(page));
}

bool tftKeypadEvent(uint8_t code) {
  if (code == 0x10) {
    // Without this the page stays e.g. 21 while the keypad shows: the periodic
    // refresh then repaints LAVORAZIONE values during the page transition and
    // the display draws them garbled (dark veil) until the next full repaint.
    tftPageLoaded(TFT_KEYPAD_PAGE);
    tftKeypadDraw();
    return true;
  }
  if (keypadPage >= TFT_PAGE_COUNT && keypadRow == NULL && keypadKind == TK_NONE) {
    // Stale keypad page (for example left open across an ESP reboot): only
    // OK/Cancel can recover, everything else is dropped.
    if (code == 0x5C || code == 0x5D) toScreen("page 0");
    return true;
  }
  if (code >= 0x50 && code <= 0x59) {
    // Page 18 assigns 0x50..0x59 in reading order of the on-screen keys:
    // 1,2,3 / 4,5,6 / 7,8,9 / 0, so 0x50..0x58 are 1..9 and 0x59 is 0.
    tftKeypadDigit(code == 0x59 ? '0' : char('1' + code - 0x50));
  } else if (code == 0x5E) {
    tftKeypadDigit('.');
  } else if (code == 0x5B) {
    tftKeypadBackspace();
  } else if (code == 0x5C) {
    tftKeypadApply();
    tftKeypadReturn();
  } else if (code == 0x5D) {
    tftKeypadReturn();
  }
  return true;
}

void tftAdjustStop(Axis* a, bool isLeft, bool plus) {
  long cur = isLeft ? a->leftStop : a->rightStop;
  if (isLeft ? cur == LONG_MAX : cur == LONG_MIN) cur = a->pos;
  long step = duToSteps(a, 1000);
  if (step < 1) step = 1;
  long next = cur + (plus ? step : -step);
  if (isLeft) {
    if (a->rightStop != LONG_MIN && next <= a->rightStop) return;
    setLeftStop(a, next);
  } else {
    if (a->leftStop != LONG_MAX && next >= a->leftStop) return;
    setRightStop(a, next);
  }
}

void tftAdjustField(const TftField &f, bool plus) {
  switch (f.kind) {
    case TK_PITCH: adjustPitch(plus); break;
    case TK_STARTS:
      if (plus && starts < STARTS_MAX) setStarts(starts + 1);
      else if (!plus && starts > 1) setStarts(starts - 1);
      break;
    case TK_PASSES:
      if (plus && turnPasses < PASSES_MAX) setTurnPasses(turnPasses + 1);
      else if (!plus && turnPasses > 1) setTurnPasses(turnPasses - 1);
      break;
    case TK_SIDE:
      if (mode == MODE_CUT) {
        // The side follows the pitch sign: flipping it is the only way to
        // change side, and it must not happen while the cut is running.
        if (isOn) {
          tftSetStatus("SPEGNI PRIMA", 3000);
          beep();
          break;
        }
        long cur = nextDuprFlag ? nextDupr : dupr;
        if (cur != 0) setDupr(-cur);
      } else {
        auxForward = !auxForward;
      }
      break;
    case TK_RATIO: setConeRatio(constrain(coneRatio + (plus ? 0.01 : -0.01), 0.0, 10.0)); break;
    case TK_DIABIG:
      CONE_DIA_BIG_DU = clampLongValue(CONE_DIA_BIG_DU + (plus ? 1000 : -1000), 1000, 9999900);
      saveMachineConfig();
      recomputeConeRatio();
      break;
    case TK_DIASMALL:
      CONE_DIA_SMALL_DU = clampLongValue(CONE_DIA_SMALL_DU + (plus ? 1000 : -1000), 0, 9999900);
      saveMachineConfig();
      recomputeConeRatio();
      break;
    case TK_ZMAX: tftAdjustStop(&z, true, plus); break;
    case TK_ZMIN: tftAdjustStop(&z, false, plus); break;
    case TK_XMAX: tftAdjustStop(&x, true, plus); break;
    case TK_XMIN: tftAdjustStop(&x, false, plus); break;
    case TK_YMAX: tftAdjustStop(&y, true, plus); break;
    case TK_JOYN:
      JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND = constrain(JOYSTICK_NORMAL_REVOLUTIONS_PER_SECOND + (plus ? 0.1 : -0.1), 0.1, 10.0);
      break;
    case TK_JOYR:
      JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND = constrain(JOYSTICK_RAPID_REVOLUTIONS_PER_SECOND + (plus ? 0.1 : -0.1), 0.1, 20.0);
      break;
    case TK_JOYD: JOYSTICK_DEADBAND = constrain(JOYSTICK_DEADBAND + (plus ? 10 : -10), 0, JOYSTICK_ADC_MAX - 1); break;
    case TK_SIGN: {
      long cur = nextDuprFlag ? nextDupr : dupr;
      if (cur != 0) setDupr(-cur);
      break;
    }
    case TK_FWD: auxForward = !auxForward; break;
    case TK_SLOTRED: SLOT_LEFT_REDUCTION_DU = constrain(SLOT_LEFT_REDUCTION_DU + (plus ? 100 : -100), 0L, 10000000L); break;
    case TK_ZSTOPS: tftAdjustStop(&z, tftStopAdjustSide == 0, plus); break;
    case TK_ZSTOPS_MIN: tftAdjustStop(&z, false, plus); break;
  }
}

// ---------- Page event routing ----------
void tftPageLoaded(uint8_t page) {
  tftCurrentPage = page;
  // Defer the periodic repaint by one tick: the page-load draw takes a few
  // hundred ms and the service tick must not join in mid-draw.
  tftLastDynamicMs = millis();
}

void tftMenuEvent(uint8_t code) {
  if (code == 0x10) {
    tftPageLoaded(TFT_MENU_PAGE);
    tftDrawMenuState(true);
    tftDrawFooter(true);
  } else if (code == 0x70) {
    setIsOnFromTask(!isOn);
    beep();
  } else if (code >= 0x71 && code <= 0x7C) {
    uint8_t page = 1 + (code - 0x71);
    setModeFromTask(TFT_PAGES[page].mode);
    toScreen("page " + String(page));
  } else if (code == 0x7D) {
    setModeFromTask(MODE_SLOT);
    toScreen("page 17");
  } else if (code >= 0x80 && code <= 0x84) {
    const uint8_t pages[5] = {TFT_COMANDO_PAGE, TFT_GCODE_PAGE, TFT_SETUP_PAGE, TFT_WIFI_PAGE, TFT_INFO_PAGE};
    toScreen("page " + String(pages[code - 0x80]));
  }
}

void tftReleaseJogs() {
  setMoveButtonPressed(B_RIGHT, false);
  setMoveButtonPressed(B_LEFT, false);
  setMoveButtonPressed(B_FORWARD, false);
  setMoveButtonPressed(B_BACK, false);
  setMoveButtonPressed(B_UP, false);
  setMoveButtonPressed(B_DOWN, false);
  tftHeldMove = 0;
}

// ---------- LAVORAZIONE (page 21) ----------
// Picture 47 holds the static labels and the jog buttons; the live values are
// painted with the glyph sprite on the card colour, so every box already has
// the background it needs.
#define TFT_WORK_CACHE_N 24
static String tftWorkCache[TFT_WORK_CACHE_N];

void tftGlyphsCard(int x, int y, const String &text) {
  for (int i = 0; i < (int)text.length(); i++) {
    int c = (uint8_t)text[i];
    if (c < 32 || c > 126) c = '?';
    int code = c - 32;
    int sx = (code % TFT_SPRITE_COLS) * TFT_GLYPH_W;
    int sy = (code / TFT_SPRITE_COLS) * TFT_GLYPH_H;
    toScreen("xpic " + String(x + i * TFT_GLYPH_W) + "," + String(y) + "," + String(TFT_GLYPH_W) + "," + String(TFT_GLYPH_H) + "," + String(sx) + "," + String(sy) + "," + String(TFT_SPRITE_CARD_PIC));
  }
}

void tftWorkLineLeft(int left, int y, int right, const String &text) {
  String t = tftClip(text, (right - left + 2) / TFT_GLYPH_W);
  tftGlyphsCard(left, y, t);
  tftFill(left + (int)t.length() * TFT_GLYPH_W, y, right - left - (int)t.length() * TFT_GLYPH_W, TFT_GLYPH_H, TFT_CARD_COLOR);
}

void tftWorkLineRight(int left, int y, int right, const String &text) {
  String t = tftClip(text, (right - left + 2) / TFT_GLYPH_W);
  int gw = (int)t.length() * TFT_GLYPH_W;
  tftGlyphsCard(right - gw, y, t);
  tftFill(left, y, right - gw - left, TFT_GLYPH_H, TFT_CARD_COLOR);
}

void tftWorkLineCenter(int cx, int y, int left, int right, const String &text) {
  String t = tftClip(text, (right - left + 2) / TFT_GLYPH_W);
  int gw = (int)t.length() * TFT_GLYPH_W;
  int gx = cx - gw / 2;
  tftGlyphsCard(gx, y, t);
  tftFill(left, y, gx - left, TFT_GLYPH_H, TFT_CARD_COLOR);
  tftFill(gx + gw, y, right - (gx + gw), TFT_GLYPH_H, TFT_CARD_COLOR);
}

// Last paint of the display task: the footer carries the reason and the page's
// STATO card switches to ESTOP. Everything goes through the glyph sprites, the
// Nextion components of the old HMI (bMode, t3) no longer exist.
void tftDrawEmergency(const String &reason) {
  tftSetStatus("ESTOP - " + reason, 600000);
  tftDrawFooter(true);
  if (tftCurrentPage == TFT_WORK_PAGE) {
    tftWorkLineLeft(552, 322, 776, "ESTOP");
  } else if ((tftCurrentPage >= 1 && tftCurrentPage <= 12) || tftCurrentPage == 17) {
    tftDrawStatus(tftCurrentPage);
  }
}

void tftDrawWorkUpdate() {
  String value;
  value = tftModeName(mode);
  if (value != tftWorkCache[0]) { tftWorkCache[0] = value; tftWorkLineCenter(556, 17, 456, 656, value); }

  value = printDupr(dupr);
  if (value != tftWorkCache[1]) { tftWorkCache[1] = value; tftWorkLineLeft(23, 94, 151, value); }
  value = String(starts);
  if (value != tftWorkCache[2]) { tftWorkCache[2] = value; tftWorkLineLeft(179, 94, 307, value); }
  value = String(turnPasses);
  if (value != tftWorkCache[3]) { tftWorkCache[3] = value; tftWorkLineLeft(335, 94, 463, value); }
  value = dupr >= 0 ? "DX" : "SX";
  if (value != tftWorkCache[4]) { tftWorkCache[4] = value; tftWorkLineLeft(491, 94, 619, value); }
  value = auxForward ? "ESTERNO" : "INTERNO";
  if (value != tftWorkCache[5]) { tftWorkCache[5] = value; tftWorkLineLeft(647, 94, 779, value); }

  value = !x.active || x.disabled ? "--" : printAxisPos(&x);
  if (value != tftWorkCache[6]) { tftWorkCache[6] = value; tftWorkLineLeft(24, 184, 217, value); }
  value = !x.active || x.disabled ? "---" : tftStopText(&x, true, false);
  if (value != tftWorkCache[7]) { tftWorkCache[7] = value; tftWorkLineRight(64, 210, 241, value); }
  value = !x.active || x.disabled ? "---" : tftStopText(&x, false, false);
  if (value != tftWorkCache[8]) { tftWorkCache[8] = value; tftWorkLineRight(64, 238, 241, value); }

  value = !y.active || y.disabled ? "--" : printAxisPos(&y);
  if (value != tftWorkCache[9]) { tftWorkCache[9] = value; tftWorkLineLeft(284, 184, 477, value); }
  value = !y.active || y.disabled ? "---" : tftStopText(&y, true, false);
  if (value != tftWorkCache[10]) { tftWorkCache[10] = value; tftWorkLineRight(324, 210, 501, value); }
  value = !y.active || y.disabled ? "---" : tftStopText(&y, false, false);
  if (value != tftWorkCache[11]) { tftWorkCache[11] = value; tftWorkLineRight(324, 238, 501, value); }

  value = !z.active || z.disabled ? "--" : printAxisPos(&z);
  if (value != tftWorkCache[12]) { tftWorkCache[12] = value; tftWorkLineLeft(544, 184, 737, value); }
  value = !z.active || z.disabled ? "---" : tftStopText(&z, true, false);
  if (value != tftWorkCache[13]) { tftWorkCache[13] = value; tftWorkLineRight(584, 210, 761, value); }
  value = !z.active || z.disabled ? "---" : tftStopText(&z, false, false);
  if (value != tftWorkCache[14]) { tftWorkCache[14] = value; tftWorkLineRight(584, 238, 761, value); }

  float turns = (float)abs(spindlePos) / ENCODER_STEPS_INT;
  value = String(turns, turns < 100 ? 2 : (turns < 1000 ? 1 : 0));
  if (value != tftWorkCache[15]) { tftWorkCache[15] = value; tftWorkLineLeft(26, 322, 250, value); }
  value = String(getApproxRpm());
  if (value != tftWorkCache[16]) { tftWorkCache[16] = value; tftWorkLineLeft(286, 322, 510, value); }
  // The degree sign is not in the sprite: the background carries it.
  value = String(spindleModulo(spindlePos) * 360.0 / ENCODER_STEPS_FLOAT, 1);
  if (value != tftWorkCache[17]) { tftWorkCache[17] = value; tftWorkLineLeft(26, 364, 250, value); }
  if (isPassMode()) {
    long total = (long)turnPasses * (starts < 1 ? 1 : starts);
    value = String(opIndex) + " / " + String(total);
  } else {
    value = "--";
  }
  if (value != tftWorkCache[18]) { tftWorkCache[18] = value; tftWorkLineLeft(286, 364, 510, value); }
  value = tftStateText();
  if (value != tftWorkCache[19]) { tftWorkCache[19] = value; tftWorkLineLeft(552, 322, 776, value); }
  value = isOn ? "STOP" : "AVVIA";
  if (value != tftWorkCache[20]) { tftWorkCache[20] = value; tftWorkLineCenter(664, 360, 556, 772, value); }
}

void tftDrawWorkAll() {
  for (int i = 0; i < TFT_WORK_CACHE_N; i++) tftWorkCache[i] = "";
  tftDrawWorkUpdate();
  tftDrawFooter(true);
}

bool tftIsWorkMode() {
  return mode != MODE_NORMAL && mode != MODE_GCODE;
}

// Starting a work mode from the MENU (or from the mode page with the physical
// ON key) lands on the live LAVORAZIONE page. COMANDO and the service pages
// keep what the user is looking at.
void tftAutoOpenWorkPage() {
  if (tftCurrentPage == TFT_WORK_PAGE) return;
  bool fromMenuOrModePage = tftCurrentPage == TFT_MENU_PAGE || (tftCurrentPage >= 1 && tftCurrentPage <= 12) || tftCurrentPage == 17;
  if (!fromMenuOrModePage) return;
  toScreen("page " + String(TFT_WORK_PAGE));
}

void tftWorkZero(Axis* a, const char* name) {
  if (!a->active || a->disabled) {
    tftSetStatus("ASSE NON USATO", 3000);
    beep();
    return;
  }
  markAxis0(a);
  tftSetStatus(String("ZERO ") + name, 2000);
}

void tftWorkSetStop(Axis* a, bool isLeft) {
  if (isOn) {
    tftSetStatus("SPEGNI PRIMA", 3000);
    beep();
    return;
  }
  if (!a->active || a->disabled) {
    tftSetStatus("ASSE NON USATO", 3000);
    beep();
    return;
  }
  if (isLeft) {
    if (a->rightStop != LONG_MIN && a->pos <= a->rightStop) {
      tftSetStatus("MAX SOTTO IL MIN", 3000);
      beep();
      return;
    }
    setLeftStop(a, a->pos);
    tftSetStatus("MAX IMPOSTATO", 2000);
  } else {
    if (a->leftStop != LONG_MAX && a->pos >= a->leftStop) {
      tftSetStatus("MIN SOPRA IL MAX", 3000);
      beep();
      return;
    }
    setRightStop(a, a->pos);
    tftSetStatus("MIN IMPOSTATO", 2000);
  }
}

void tftWorkOpenNumbers(uint8_t kind, const String &text) {
  if (isOn) {
    tftSetStatus("SPEGNI PRIMA", 3000);
    beep();
    return;
  }
  tftKeypadOpenValue(TFT_WORK_PAGE, kind, text);
}

void tftWorkEvent(uint8_t code) {
  if (code == 0x10) {
    tftPageLoaded(TFT_WORK_PAGE);
    // Deferred like the mode pages (see tftRunDeferredModeRepaint).
    tftWorkRepaintPass = 1;
    tftWorkRepaintAtMs = millis() + 300;
    return;
  }
  if (code >= 0x60 && code <= 0x65) {
    const uint8_t moves[6] = {B_UP, B_DOWN, B_FORWARD, B_BACK, B_RIGHT, B_LEFT};
    uint8_t action = moves[code - 0x60];
    setMoveButtonPressed(action, true);
    tftHeldMove = action;
    tftHeldMoveMs = millis();
    return;
  }
  if (code == 0x6F) {
    tftReleaseJogs();
    return;
  }
  if (code == 0x70) {
    if (isOn) {
      tftReleaseJogs();
      buttonOnOffPress(false);
    } else if (mode == MODE_GCODE) {
      // The G-code page runs a program with its own checks: keep one step here.
      buttonOnOffPress(true);
    } else {
      // LAVORAZIONE shows no setup prompts: the values were set on the mode
      // page, so accept the steps in one touch.
      for (uint8_t i = 0; i <= (uint8_t)getLastSetupIndex(); i++) {
        uint8_t before = setupIndex;
        buttonOnOffPress(true);
        if (setupIndex == before) break;
      }
    }
    beep();
    return;
  }
  if (code == 0x31) {
    tftReleaseJogs();
    toScreen("page " + String(TFT_MENU_PAGE));
    return;
  }
  if (code == 0x75) { tftWorkZero(&x, "X"); return; }
  if (code == 0x76) { tftWorkZero(&y, "Y"); return; }
  if (code == 0x77) { tftWorkZero(&z, "Z"); return; }
  if (code == 0x85) { tftWorkSetStop(&x, true); return; }
  if (code == 0x86) { tftWorkSetStop(&x, false); return; }
  if (code == 0x87) { tftWorkSetStop(&y, true); return; }
  if (code == 0x88) { tftWorkSetStop(&y, false); return; }
  if (code == 0x89) { tftWorkSetStop(&z, true); return; }
  if (code == 0x8A) { tftWorkSetStop(&z, false); return; }
  if (code == 0x8B) { tftWorkOpenNumbers(TK_PITCH, printDupr(dupr)); return; }
  if (code == 0x8C) { tftWorkOpenNumbers(TK_STARTS, String(starts)); return; }
  if (code == 0x8D) { tftWorkOpenNumbers(TK_PASSES, String(turnPasses)); return; }
}

void tftComandoEvent(uint8_t code) {
  if (code == 0x10) {
    tftPageLoaded(TFT_COMANDO_PAGE);
    tftDrawComandoAll();
    tftDrawFooter(true);
    return;
  }
  if (code >= 0x60 && code <= 0x65) {
    const uint8_t moves[6] = {B_UP, B_DOWN, B_FORWARD, B_BACK, B_RIGHT, B_LEFT};
    uint8_t action = moves[code - 0x60];
    setMoveButtonPressed(action, true);
    tftHeldMove = action;
    tftHeldMoveMs = millis();
  } else if (code == 0x6F) {
    tftReleaseJogs();
  } else if (code == 0x70) {
    setIsOnFromTask(!isOn);
    beep();
  } else if (code == 0x71 || code == 0x31) {
    toScreen("page " + String(TFT_MENU_PAGE));
  } else if (code == 0x72) {
    tftKeypadOpenValue(TFT_COMANDO_PAGE, TK_STARTS, String(starts));
  } else if (code == 0x73) {
    tftKeypadOpenValue(TFT_COMANDO_PAGE, TK_PITCH, printDupr(nextDuprFlag ? nextDupr : dupr));
  } else if (code == 0x74) {
    buttonMeasurePress();
  } else if (code == 0x75) {
    markAxis0(&x);
  } else if (code == 0x76) {
    markAxis0(&y);
  } else if (code == 0x77) {
    markAxis0(&z);
  } else if (code == 0x78) {
    tftReleaseJogs();
    buttonOnOffPress(false);
  } else if (code >= 0x79 && code <= 0x82) {
    uint8_t index = code - 0x79;
    processNumpad(index < 9 ? '1' + index : '0');
  } else if (code == 0x83) {
    processNumpad(B_BACKSPACE);
  } else if (code == 0x84) {
    processNumpad(B_ON);
  }
}

void tftGcodeEvent(uint8_t code) {
  if (code == 0x10) {
    tftPageLoaded(TFT_GCODE_PAGE);
    tftDrawGcodeAll();
    return;
  }
  if (code >= 0xA0 && code <= 0xA3) {
    tftGcodeSelect(tftGcodeTop + (code - 0xA0));
  } else if (code == 0xB0) {
    tftGcodeExecute();
  } else if (code == 0xB1) {
    tftGcodeDelete();
  } else if (code == 0xB2) {
    tftDrawGcodeAll();
    tftSetStatus("ELENCO AGGIORNATO", 3000);
    tftDrawFooter(true);
  } else if (code == 0x31) {
    toScreen("page 0");
  }
}

void tftSetupEvent(uint8_t code) {
  if (code == 0x10) {
    tftPageLoaded(TFT_SETUP_PAGE);
    tftDrawFooter(true);
  } else if (code >= 0xA0 && code <= 0xA5) {
    tftSetupSection = code - 0xA0;
    tftSetupPage = 0;
    tftActionArmed = 255;
    toScreen("page " + String(TFT_PANEL_PAGE));
  } else if (code == 0x31) {
    toScreen("page 0");
  }
}

void tftWifiEvent(uint8_t code) {
  if (code == 0x10) {
    tftPageLoaded(TFT_WIFI_PAGE);
    tftDrawWifiAll();
  } else if (code == 0xA0) {
    tftKbOpen(0);
  } else if (code == 0xA1) {
    tftKbOpen(1);
  } else if (code == 0xB0) {
    tftWifiConnect();
  } else if (code == 0xB1) {
    tftWifiForget();
  } else if (code == 0x31) {
    toScreen("page 0");
  }
}

void tftInfoEvent(uint8_t code) {
  if (code == 0x10) {
    tftPageLoaded(TFT_INFO_PAGE);
    tftDrawInfoAll();
    tftDrawFooter(true);
  } else if (code == 0x31) {
    toScreen("page 0");
  }
}

void tftPanelEvent(uint8_t code) {
  const TctPanel &panel = TCT_PANELS[tftSetupSection];
  if (code == 0x10) {
    tftPageLoaded(TFT_PANEL_PAGE);
    tftDrawSetupPanel();
    return;
  }
  if (code >= 0xA0 && code <= 0xA6) {
    int index = tftSetupPage * TFT_SETUP_PAGE_SIZE + (code - 0xA0);
    if (index >= panel.count) return;
    const TctRow &row = panel.rows[index];
    if (row.kind == TCT_INFO) return;
    if (row.kind == TCT_ACTION) {
      tctAction(index, row);
      tftDrawSetupPanel();
    } else if (row.kind == TCT_B || row.kind == TCT_MEASURE) {
      tctToggle(row);
      tftDrawSetupPanel();
    } else {
      tftKeypadOpenRow(row);
    }
  } else if ((code >= 0xB0 && code <= 0xB6) || (code >= 0xC0 && code <= 0xC6)) {
    int index = tftSetupPage * TFT_SETUP_PAGE_SIZE + (code & 0x0F);
    if (index >= panel.count) return;
    const TctRow &row = panel.rows[index];
    if (row.kind == TCT_INFO || row.kind == TCT_B || row.kind == TCT_MEASURE || row.kind == TCT_ACTION) return;
    tctAdjust(row, code >= 0xC0);
    tftDrawSetupPanel();
  } else if (code == 0xD0) {
    if (tftSetupPage > 0) {
      tftSetupPage--;
      tftDrawSetupPanel();
    }
  } else if (code == 0xD1) {
    int pages = (panel.count + TFT_SETUP_PAGE_SIZE - 1) / TFT_SETUP_PAGE_SIZE;
    if (tftSetupPage + 1 < pages) {
      tftSetupPage++;
      tftDrawSetupPanel();
    }
  } else if (code == 0xD2) {
    toScreen("page " + String(TFT_SETUP_PAGE));
  }
}

void handleTftEvent(uint8_t page, uint8_t code) {
  if (page == TFT_KEYPAD_PAGE) {
    tftKeypadEvent(code);
    return;
  }
  if (page == TFT_KEYBOARD_PAGE) {
    tftKbEvent(code);
    return;
  }
  if (page == TFT_PANEL_PAGE) {
    tftPanelEvent(code);
    return;
  }
  if (page == TFT_MENU_PAGE) {
    tftMenuEvent(code);
    return;
  }
  if (page == TFT_COMANDO_PAGE) {
    tftComandoEvent(code);
    return;
  }
  if (page == TFT_GCODE_PAGE) {
    tftGcodeEvent(code);
    return;
  }
  if (page == TFT_SETUP_PAGE) {
    tftSetupEvent(code);
    return;
  }
  if (page == TFT_WIFI_PAGE) {
    tftWifiEvent(code);
    return;
  }
  if (page == TFT_INFO_PAGE) {
    tftInfoEvent(code);
    return;
  }
  if (page == TFT_WORK_PAGE) {
    tftWorkEvent(code);
    return;
  }
  if (page >= TFT_PAGE_COUNT) return;
  const TftPage &pg = TFT_PAGES[page];
  if (code == 0x10) {
    tftPageLoaded(page);
    // Value boxes first, card backdrop last: the 288x358 card blit is the
    // slowest command and while it runs the boxes would stay empty (the
    // "veil" the user sees over PASSO right after the keypad returns).
    // The whole repaint is deferred (see tftRunDeferredModeRepaint): drawn
    // here it would collide with the background decode and the first box
    // would come out as white blocks.
    tftModeRepaintPage = page;
    tftModeRepaintAtMs = millis() + 300;
    tftModeRepaintPass = 0;
  } else if (code == 0x30) {
    setModeFromTask(pg.mode);
    tftOpenWorkPagePending = true;
  } else if (code == 0x31) {
    toScreen("page 0");
  } else if (code >= 0x40 && code <= 0x45) {
    uint8_t index = code - 0x40;
    // 0x45 on SCANALATURA taps the right half of the shared "MAX / MIN" text
    // (field 4). It must win over the field lookup because the page also has
    // a read-only computed field in slot 5.
    if (code == 0x45 && pg.count >= 5 && pg.f[4].kind == TK_ZSTOPS) {
      tftStopAdjustSide = 1;
      tftKeypadOpenValue(page, TK_ZMIN, tftStopText(&z, false, false));
      return;
    }
    if (index >= pg.count) return;
    const TftField &f = pg.f[index];
    if (f.kind == TK_NONE) return;
    if (f.kind == TK_CONERATIO || tftIsCalcKind(f.kind)) return; // Derived from the measurements: read-only.
    if (f.kind == TK_SIDE) {
      // On TRONCATURA the side is the sign of the pitch, so PASSO changes too.
      tftAdjustField(f, true);
      tftDrawPage(page);
      return;
    }
    if (f.kind == TK_FWD) {
      auxForward = !auxForward;
      tftDrawField(f, page);
      return;
    }
    if (f.kind == TK_SIGN || f.kind == TK_HAND) {
      if (f.kind == TK_HAND && isOn) {
        tftSetStatus("SPEGNI PRIMA", 3000);
        beep();
        return;
      }
      long cur = nextDuprFlag ? nextDupr : dupr;
      if (cur != 0) setDupr(-cur);
      tftDrawField(f, page);
      return;
    }
    if (f.kind == TK_ZSTOPS || f.kind == TK_ZSTOPS_MIN) {
      // Two zones share the "MAX / MIN" text: left half edits MAX, right MIN.
      bool editMax = code == 0x44;
      tftStopAdjustSide = editMax ? 0 : 1;
      tftKeypadOpenValue(page, editMax ? TK_ZMAX : TK_ZMIN, tftStopText(&z, editMax, false));
      return;
    }
    tftKeypadOpen(page, index);
  } else if (code >= 0x20 && code <= 0x29) {
    uint8_t index = (code - 0x20) / 2;
    if (index >= pg.count) return;
    tftAdjustField(pg.f[index], (code & 1) != 0);
    // Every measurement feeds the computed value on the side card and the
    // values quoted on the drawing: redraw both together with the field.
    tftDrawPage(page);
  }
}

int processNextionMessage() {
  lastNextionPageId = 255;
  if (nextionBufferIndex < 6) return 0;
  if (nextionBuffer[0] == 0x68) {
    tftDiagPage = nextionBuffer[1];
    tftDiagCode = nextionBuffer[2];
    tftDiagEvents++;
    handleTftEvent(nextionBuffer[1], nextionBuffer[2]);
    return 0;
  }
  if (nextionBuffer[0] == 0x65) {
    byte pageId = nextionBuffer[1];
    int code = 0;
    if (pageId == 0x00) {
      code = HEX_TO_KEYCODE[nextionBuffer[2]];
    } else if (pageId == 0x01) {
      switch (nextionBuffer[2]) {
        case 12: code = B_MODE_GEARS; break;
        case 13: code = B_MODE_TURN; break;
        case 14: code = B_MODE_FACE; break;
        case 15: code = B_MODE_CONE; break;
        case 16: code = B_MODE_CUT; break;
        case 17: code = B_MODE_THREAD; break;
        case 18: code = B_MODE_ELLIPSE; break;
        case 19: code = B_MODE_GCODE; break;
        case 20: code = B_MODE_ASYNC; break;
        case 21: code = B_MODE_Y; break;
        case 23: code = B_MODE_XGEAR; break;
        case 25: code = B_MODE_JOYSTICK; break;
        case 27: code = B_MODE_SLOT; break;
        case 41: toScreen("page 0"); return 0;
      }
    }
    if (code != 0) {
      lastNextionPageId = pageId;
      if (nextionBuffer[3] == 0) code |= PS2_BREAK;
    }
    return code;
  }
  return 0;
}

void setModeFromUi(int modeToSet, bool eventFromNextion) {
  setModeFromTask(modeToSet);
  if (eventFromNextion && lastNextionPageId == 1) toScreen("page 0");
}

void processKeypadEvent() {
  processWebUiMoveFailsafe();
  tftRunDeferredModeRepaint();
  int event = 0;
  bool eventFromNextion = false;
  bool eventUsesKeyboardMap = false;
  bool eventFromWebUi = false;
  lastNextionPageId = 255;
  WebUiEvent webUiEvent = {};
  if (readWebUiEvent(&webUiEvent)) {
    event = webUiEvent.actionCode;
    eventFromWebUi = true;
    if (!webUiEvent.isPress) event |= PS2_BREAK;
  } else if (wsKeycode != 0) {
    event = wsKeycode;
    wsKeycode = 0;
    eventUsesKeyboardMap = true;
  } else if (keyboard.available()) {
    event = keyboard.read();
    eventUsesKeyboardMap = true;
  } else if (!tftUploadActive && Serial1.available() > 0) {
    byte incomingByte = Serial1.read();
    if (incomingByte == 0x88) tftDiagReboots++;
    if (nextionBufferIndex < NEXTION_BUFFER_LENGTH) {
      nextionBuffer[nextionBufferIndex] = incomingByte;
      nextionBufferIndex++;
    } else {
      nextionBufferIndex = 0;
    }
    if (checkForTerminator()) {
      event = processNextionMessage();
      eventFromNextion = event != 0 && lastNextionPageId != 255;
      nextionBufferIndex = 0;
    }
  }
  if (event == 0) return;
  int physicalKeyCode = event & 0xFF;
  bool isPress = !(event & PS2_BREAK);
  int keyCode = eventUsesKeyboardMap ? keyboardActionForCode(byte(physicalKeyCode)) : physicalKeyCode;
  keypadTimeUs = micros();

  if (eventUsesKeyboardMap) {
    publishKeyboardEvent(byte(physicalKeyCode), byte(keyCode), isPress);
  }

  // Some keyboards send this code and expect an answer to initialize.
  if (physicalKeyCode == 170) {
    keyboard.echo();
    return;
  }

  if (eventUsesKeyboardMap && shouldConsumeKeyboardCapture(byte(physicalKeyCode), isPress)) {
    return;
  }

  if (keyCode == 0) return;

  // Off button always gets handled.
  if (keyCode == B_OFF) {
    buttonOffPressed = isPress;
    isPress ? buttonOnOffPress(false) : buttonOffRelease();
  }

  if (mode == MODE_GCODE && isOn) {
    // Not allowed to interfere other than turn off.
    if (isPress && keyCode != B_OFF) beep();
    return;
  }

  // Releases don't matter in numpad but it has to run before LRUD since it might handle those keys.
  if (isPress && processNumpad(keyCode)) {
    return;
  }

  if (eventFromWebUi) {
    updateWebUiMoveWatchdog(byte(keyCode), isPress);
  }

  // Keyboard may not send release event if another button is pressed before first one is released.
  buttonLeftPressed = false;
  buttonRightPressed = false;
  buttonUpPressed = false;
  buttonDownPressed = false;
  buttonBackPressed = false;
  buttonForwardPressed = false;

  // Setup wizard navigation.
  if (isPress && setupIndex == 2 && (keyCode == B_LEFT || keyCode == B_RIGHT)) {
    auxForward = !auxForward;
  } else if (isPress && mode == MODE_GCODE && setupIndex == 1 && (keyCode == B_UP || keyCode == B_DOWN)) {
    if (gcodeProgramIndex > 0 && keyCode == B_UP) gcodeProgramIndex--;
    else if (gcodeProgramIndex == 0 && gcodeProgramCount > 0 && keyCode == B_UP) gcodeProgramIndex = gcodeProgramCount - 1;
    else if ((gcodeProgramIndex < gcodeProgramCount - 1) && keyCode == B_DOWN) gcodeProgramIndex++;
    else if (keyCode == B_DOWN) gcodeProgramIndex = 0;
  } else if (isPress && mode == MODE_GCODE && setupIndex == 1 && keyCode == B_MINUS) {
    removeGcodeByName(getCurrentGcodeProgramName());
    return;
  } else if (isWebUiMoveAction(byte(keyCode))) { // Make sure isPress=false propagates to motion flags.
    setMoveButtonPressed(byte(keyCode), isPress);
  }

  // For all other keys we have no "release" logic.
  if (!isPress) {
    return;
  }

  // Rest of the buttons.
  if (keyCode == B_PLUS) {
    buttonPlusMinusPress(true);
  } else if (keyCode == B_MINUS) {
    buttonPlusMinusPress(false);
  } else if (keyCode == B_ON) {
    buttonOnOffPress(true);
  } else if (keyCode == B_STOPL) {
    buttonLeftStopPress(&z);
  } else if (keyCode == B_STOPR) {
    buttonRightStopPress(&z);
  } else if (keyCode == B_STOPU) {
    buttonLeftStopPress(&x);
  } else if (keyCode == B_STOPD) {
    buttonRightStopPress(&x);
  } else if (keyCode == B_STOPF && ACTIVE_Y) {
    buttonLeftStopPress(&y);
  } else if (keyCode == B_STOPB && ACTIVE_Y) {
    buttonRightStopPress(&y);
  } else if (keyCode == B_MODE_Y && ACTIVE_Y) {
    setModeFromUi(MODE_Y, eventFromNextion);
  } else if (keyCode == B_MODE_ELLIPSE) {
    setModeFromUi(MODE_ELLIPSE, eventFromNextion);
  } else if (keyCode == B_MODE_GCODE) {
    setModeFromUi(MODE_GCODE, eventFromNextion);
  } else if (keyCode == B_MODE_ASYNC) {
    setModeFromUi(MODE_ASYNC, eventFromNextion);
  } else if (keyCode == B_MULTISTART) {
    buttonMultistartPress();
  } else if (keyCode == B_DISPL) {
    buttonDisplayPress();
  } else if (keyCode == B_X) {
    markAxis0(&x);
  } else if (keyCode == B_Z) {
    markAxis0(&z);
  } else if (keyCode == B_Y && ACTIVE_Y) {
    markAxis0(&y);
  } else if (keyCode == B_X_ENA) {
    x.disabled = !x.disabled;
    updateEnable(&x);
  } else if (keyCode == B_Z_ENA) {
    z.disabled = !z.disabled;
    updateEnable(&z);
  } else if (keyCode == B_Y_ENA && ACTIVE_Y) {
    y.disabled = !y.disabled;
    updateEnable(&y);
  } else if (keyCode == B_STEP) {
    buttonMoveStepPress();
  } else if (keyCode == B_REVERSE) {
    buttonReversePress();
  } else if (keyCode == B_MEASURE) {
    buttonMeasurePress();
  } else if (keyCode == B_MODE_GEARS) {
    setModeFromUi(MODE_NORMAL, eventFromNextion);
  } else if (keyCode == B_MODE_TURN) {
    setModeFromUi(MODE_TURN, eventFromNextion);
  } else if (keyCode == B_MODE) {
    if (eventFromNextion) toScreen("page 1");
    else if (mode == MODE_NORMAL) setModeFromTask(MODE_XGEAR);
    else if (mode == MODE_XGEAR) setModeFromTask(MODE_JOYSTICK);
    else if (mode == MODE_JOYSTICK) setModeFromTask(MODE_TURN);
    else if (mode == MODE_TURN) setModeFromTask(MODE_FACE);
    else if (mode == MODE_FACE) setModeFromTask(MODE_CONE);
    else if (mode == MODE_CONE) setModeFromTask(MODE_CUT);
    else if (mode == MODE_CUT) setModeFromTask(MODE_SLOT);
    else if (mode == MODE_SLOT) setModeFromTask(MODE_THREAD);
    else if (mode == MODE_THREAD) setModeFromTask(MODE_ELLIPSE);
    else if (mode == MODE_ELLIPSE) setModeFromTask(MODE_GCODE);
    else if (mode == MODE_GCODE) setModeFromTask(MODE_ASYNC);
    else if (mode == MODE_ASYNC) setModeFromTask(y.active ? MODE_Y : MODE_NORMAL);
    else if (mode == MODE_Y) setModeFromTask(MODE_NORMAL);
    else setModeFromTask(MODE_NORMAL);
  } else if (keyCode == B_MODE_XGEAR) {
    setModeFromUi(MODE_XGEAR, eventFromNextion);
  } else if (keyCode == B_MODE_JOYSTICK) {
    setModeFromUi(MODE_JOYSTICK, eventFromNextion);
  } else if (keyCode == B_MODE_FACE) {
    setModeFromUi(MODE_FACE, eventFromNextion);
  } else if (keyCode == B_MODE_CONE) {
    setModeFromUi(MODE_CONE, eventFromNextion);
  } else if (keyCode == B_MODE_CUT) {
    setModeFromUi(MODE_CUT, eventFromNextion);
  } else if (keyCode == B_MODE_SLOT) {
    setModeFromUi(MODE_SLOT, eventFromNextion);
  } else if (keyCode == B_MODE_THREAD) {
    setModeFromUi(MODE_THREAD, eventFromNextion);
  }
}

void taskKeypad(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    processKeypadEvent();
    taskYIELD();
  }
  vTaskDelete(NULL);
}

void moveAxis(Axis* a) {
  // Most of the time a step isn't needed.
  if (a->pendingPos == 0) {
    if (a->speed > a->speedStart) {
      a->speed--;
    }
    return;
  }

  unsigned long nowUs = micros();
  float delayUs = 1000000.0 / a->speed;
  if (nowUs - a->stepStartUs < delayUs - 5) {
    // Not enough time has passed to issue this step.
    return;
  }

  if (xSemaphoreTake(a->mutex, 1) == pdTRUE) {
    // Check pendingPos again now that we have the mutex.
    if (a->pendingPos != 0) {
      bool dir = a->pendingPos > 0;
      setDir(a, dir);

      DLOW(a->step);
      int delta = dir ? 1 : -1;
      a->pendingPos -= delta;
      if (dir && a->motorPos >= a->pos) {
        a->pos++;
      } else if (!dir && a->motorPos <= (a->pos - a->backlashSteps)) {
        a->pos--;
      }
      a->motorPos += delta;
      a->posGlobal += delta;

      bool accelerate = a->continuous || a->pendingPos >= a->decelerateSteps || a->pendingPos <= -a->decelerateSteps;
      a->speed += (accelerate ? 1 : -1) * a->acceleration * delayUs / 1000000.0;
      if (a->speed > a->speedMax) {
        a->speed = a->speedMax;
      } else if (a->speed < a->speedStart) {
        a->speed = a->speedStart;
      }
      a->stepStartUs = nowUs;

      DHIGH(a->step);
    }
    xSemaphoreGive(a->mutex);
  }
}

void modeGearbox(Axis* a) {
  if (a->movingManually) {
    return;
  }
  a->speedMax = LONG_MAX;
  stepToContinuous(a, posFromSpindle(a, spindlePosAvg, true));
}

long getJoystickLathePitchAbs() {
  return abs(dupr);
}

bool joystickLatheFeedCommandActive() {
  return isOn && dupr != 0 && !joystickLatheRapid && (joystickLatheDirectionZ != 0 || joystickLatheDirectionX != 0);
}

bool startJoystickLatheFeedSync(Axis* a, long pitch) {
  joystickLatheSyncAxis = a == &x ? 1 : 0;
  joystickLatheSyncPitch = pitch;
  long spindleTarget = spindleFromPosWithModePitch(a, a->pos, pitch);
  spindlePosSync = spindleModulo(spindlePos - spindleTarget);
  if (spindlePosSync == 0) {
    spindlePosAvg = spindlePos = spindleTarget;
    joystickLatheSyncPitch = 0;
    return true;
  }
  return false;
}

bool rebaseJoystickLatheAxis(Axis* a, long pitch) {
  if (pitch == 0) return true;
  if (xSemaphoreTake(a->mutex, 10) != pdTRUE) {
    beepFlag = true;
    return false;
  }

  // Start this JOY feed axis from its current physical position. This avoids
  // a catch-up move when the axis joins a feed that another axis already began.
  long target = posFromSpindleWithModePitch(a, spindlePosAvg, false, pitch);
  long delta = target - a->pos;
  if (a->leftStop != LONG_MAX) {
    a->leftStop += delta;
  }
  if (a->rightStop != LONG_MIN) {
    a->rightStop += delta;
  }
  a->pos += delta;
  a->motorPos += delta;
  a->originPos -= delta;
  a->fractionalPos = 0;
  a->pendingPos = 0;
  a->continuous = false;
  a->speed = a->speedStart;

  xSemaphoreGive(a->mutex);
  return true;
}

bool applyPendingJoystickLatheRebases(long zPitch, long xPitch) {
  if (joystickLatheRebaseZAfterSync) {
    if (zPitch != 0 && !rebaseJoystickLatheAxis(&z, zPitch)) return false;
    joystickLatheRebaseZAfterSync = false;
  }
  if (joystickLatheRebaseXAfterSync) {
    if (xPitch != 0 && !rebaseJoystickLatheAxis(&x, xPitch)) return false;
    joystickLatheRebaseXAfterSync = false;
  }
  return true;
}

Axis* getJoystickLatheSyncAxis(long previousZPitch, long previousXPitch, long zPitch, long xPitch) {
  if (previousZPitch != 0 && zPitch != 0) return &z;
  if (previousXPitch != 0 && xPitch != 0) return &x;
  return zPitch != 0 ? &z : &x;
}

long getJoystickLathePitchForAxis(Axis* a, long zPitch, long xPitch) {
  return a == &z ? zPitch : xPitch;
}

void modeJoystick() {
  int zDirection = z.movingManually ? 0 : joystickLatheDirectionZ;
  int xDirection = x.movingManually ? 0 : joystickLatheDirectionX;
  if (joystickLatheRapid) {
    zDirection = 0;
    xDirection = 0;
  }
  long pitchAbs = getJoystickLathePitchAbs();
  if (pitchAbs == 0) {
    zDirection = 0;
    xDirection = 0;
  }

  long zPitch = zDirection == 0 ? 0 : pitchAbs * zDirection;
  long xPitch = xDirection == 0 ? 0 : pitchAbs * xDirection;
  if (!applyPendingJoystickLatheRebases(zPitch, xPitch)) {
    return;
  }

  long previousZPitch = joystickLathePitchZ;
  long previousXPitch = joystickLathePitchX;
  bool feedChanged = zPitch != joystickLathePitchZ || xPitch != joystickLathePitchX ||
      zDirection != joystickLatheFeedSignZ || xDirection != joystickLatheFeedSignX;
  if (feedChanged && (joystickLathePitchZ != 0 || joystickLathePitchX != 0 || zPitch != 0 || xPitch != 0)) {
    if (zPitch != 0 || xPitch != 0) {
      if (joystickLatheThreadLocked) {
        bool zContinues = previousZPitch != 0 && zPitch == previousZPitch;
        bool xContinues = previousXPitch != 0 && xPitch == previousXPitch;
        if (zContinues || xContinues) {
          // Keep already-feeding axes phase-locked and rebase only changed axes.
          if (zPitch != 0 && !zContinues && !rebaseJoystickLatheAxis(&z, zPitch)) return;
          if (xPitch != 0 && !xContinues && !rebaseJoystickLatheAxis(&x, xPitch)) return;
        } else {
          Axis* syncAxis = getJoystickLatheSyncAxis(previousZPitch, previousXPitch, zPitch, xPitch);
          long syncPitch = getJoystickLathePitchForAxis(syncAxis, zPitch, xPitch);
          joystickLatheRebaseZAfterSync = zPitch != 0 && syncAxis != &z;
          joystickLatheRebaseXAfterSync = xPitch != 0 && syncAxis != &x;
          if (!startJoystickLatheFeedSync(syncAxis, syncPitch)) {
            joystickLatheFeedSignZ = zDirection;
            joystickLatheFeedSignX = xDirection;
            joystickLathePitchZ = zPitch;
            joystickLathePitchX = xPitch;
            return;
          }
          if (!applyPendingJoystickLatheRebases(zPitch, xPitch)) return;
        }
      } else {
        markOrigin();
        joystickLatheThreadLocked = true;
      }
    }
  }
  joystickLatheFeedSignZ = zDirection;
  joystickLatheFeedSignX = xDirection;
  joystickLathePitchZ = zPitch;
  joystickLathePitchX = xPitch;

  if (zPitch == 0 && xPitch == 0) {
    return;
  }
  if (zPitch != 0) {
    z.speedMax = LONG_MAX;
    stepToContinuous(&z, posFromSpindleWithModePitch(&z, spindlePosAvg, true, zPitch));
  }
  if (xPitch != 0) {
    x.speedMax = LONG_MAX;
    stepToContinuous(&x, posFromSpindleWithModePitch(&x, spindlePosAvg, true, xPitch));
  }
}

long auxSafeDistance, startOffset;
void modeTurn(Axis* main, Axis* aux) {
  if (main->movingManually || aux->movingManually || turnPasses <= 0 ||
      main->leftStop == LONG_MAX || main->rightStop == LONG_MIN ||
      aux->leftStop == LONG_MAX || aux->rightStop == LONG_MIN ||
      dupr == 0 || (dupr * opDuprSign < 0) || starts < 1) {
    setIsOnFromLoop(false);
    return;
  }

  // Variables below have to be re-calculated every time because origin can change
  // while TURN is running e.g. due to dupr change.
  long mainStartStop = opDuprSign > 0 ? main->rightStop : main->leftStop;
  long mainEndStop = opDuprSign > 0 ? main->leftStop : main->rightStop;
  long auxStartStop = auxForward ? aux->rightStop : aux->leftStop;
  long auxEndStop = auxForward ? aux->leftStop : aux->rightStop;

  // opIndex 0 is only executed once, do setup calculations here.
  auxSafeDistance = (auxForward ? -1 : 1) * SAFE_DISTANCE_DU * aux->motorSteps / aux->screwPitch;
  if (opIndex == 0) {
    startOffset = starts == 1 ? 0 : round(ENCODER_STEPS_FLOAT / starts);

    // Move to right-bottom limit.
    main->speedMax = main->speedManualMove;
    aux->speedMax = aux->speedManualMove;
    long auxPos = auxStartStop;
    // Overstep by 1 so that "main" backlash is taken out before "opSubIndex == 1".
    long mainPos = mainStartStop + (opDuprSign > 0 ? -1 : 1);
    stepToFinal(main, mainPos);
    stepToFinal(aux, auxPos);
    if (main->pos == mainPos && aux->pos == auxPos) {
      stepToFinal(main, mainStartStop);
      opIndex = 1;
      opSubIndex = 0;
    }
  } else if (opIndex <= turnPasses * starts) {
    if (opIndexAdvanceFlag && (opIndex + starts) < turnPasses * starts) {
      opIndexAdvanceFlag = false;
      opIndex += starts;
    }
    float fraction = (turnPasses - ceil(opIndex / float(starts))) / turnPasses;
    if (mode == MODE_THREAD) fraction = fraction * fraction; // make initial passed larger, final passes smaller
    long auxPos = auxEndStop - (auxEndStop - auxStartStop) * fraction;
    // Bringing X to starting position.
    if (opSubIndex == 0) {
      stepToFinal(aux, auxPos);
      if (aux->pos == auxPos) {
        opSubIndex = 1;
        spindlePosSync = spindleModulo(spindlePosGlobal - spindleFromPos(main, main->posGlobal) + startOffset * (opIndex - 1));
        return; // Instead of jumping to the next step, let spindlePosSync get to 0 first.
      }
    }
    // spindlePosSync counted down to 0, start thread from here.
    if (opSubIndex == 1) {
      markOrigin();
      main->speedMax = LONG_MAX;
      opSubIndex = 2;
      // markOrigin() changed Start/EndStop values, re-calculate them.
      return;
    }
    // Doing the pass cut.
    if (opSubIndex == 2) {
      // In case we were pushed to the next opIndex before finishing the current one.
      long mainTargetPos = posFromSpindle(main, spindlePosAvg, true);
      long auxTargetPos = auxPos;
      if (mode == MODE_THREAD && coneRatio != 0) {
        float coneEffectRatio = -coneRatio / 2 / main->motorSteps * aux->motorSteps / aux->screwPitch * main->screwPitch * (auxForward ? 1 : -1);
        auxTargetPos = auxPos + round(mainTargetPos * coneEffectRatio);
      }

      if (auxTargetPos > aux->leftStop) auxTargetPos = aux->leftStop;
      if (auxTargetPos < aux->rightStop) auxTargetPos = aux->rightStop;

      stepToContinuous(main, mainTargetPos);
      stepToContinuous(aux, auxTargetPos);
      if (main->pos == mainEndStop || (coneRatio != 0 && aux->pos == (opDuprSign > 0 ? auxStartStop : auxEndStop))) {
        opSubIndex = 3;
      }
    }
    // Retracting the tool
    if (opSubIndex == 3) {
      long auxTargetPos = (mode == MODE_THREAD ? auxStartStop : auxPos) + auxSafeDistance;
      stepToFinal(aux, auxTargetPos);
      if (aux->pos == auxTargetPos) {
        opSubIndex = 4;
      }
    }
    // Returning to start of main.
    if (opSubIndex == 4) {
      main->speedMax = main->speedManualMove;
      // Overstep by 1 so that "main" backlash is taken out before "opSubIndex == 2".
      long mainPos = mainStartStop + (opDuprSign > 0 ? -1 : 1);
      stepToFinal(main, mainPos);
      if (main->pos == mainPos) {
        stepToFinal(main, mainStartStop);
        opSubIndex = 0;
        opIndex++;
      }
    }
  } else {
    // Move to right-bottom limit.
    main->speedMax = main->speedManualMove;
    long auxPos = auxStartStop;
    long mainPos = mainStartStop;
    stepToFinal(main, mainPos);
    stepToFinal(aux, auxPos);
    if (main->pos == mainPos && aux->pos == auxPos) {
      setIsOnFromLoop(false);
      beep();
    }
  }
}

void modeCone() {
  if (z.movingManually || x.movingManually || coneRatio == 0) {
    return;
  }

  float zToXRatio = -coneRatio / 2 / z.motorSteps * x.motorSteps / x.screwPitch * z.screwPitch * (auxForward ? 1 : -1);
  if (zToXRatio == 0) {
    return;
  }

  // TODO: calculate maximum speeds and accelerations to avoid potential desync.
  x.speedMax = LONG_MAX;
  z.speedMax = LONG_MAX;

  // Respect limits of both axis by translating them into limits on spindlePos value.
  long spindle = spindlePosAvg;
  long spindleMin = LONG_MIN;
  long spindleMax = LONG_MAX;
  if (z.leftStop != LONG_MAX) {
    (dupr > 0 ? spindleMax : spindleMin) = spindleFromPos(&z, z.leftStop);
  }
  if (z.rightStop != LONG_MIN) {
    (dupr > 0 ? spindleMin: spindleMax) = spindleFromPos(&z, z.rightStop);
  }
  if (x.leftStop != LONG_MAX) {
    long lim = spindleFromPos(&z, round(x.leftStop / zToXRatio));
    if (zToXRatio < 0) {
      (dupr > 0 ? spindleMin: spindleMax) = lim;
    } else {
      (dupr > 0 ? spindleMax : spindleMin) = lim;
    }
  }
  if (x.rightStop != LONG_MIN) {
    long lim = spindleFromPos(&z, round(x.rightStop / zToXRatio));
    if (zToXRatio < 0) {
      (dupr > 0 ? spindleMax : spindleMin) = lim;
    } else {
      (dupr > 0 ? spindleMin: spindleMax) = lim;
    }
  }
  if (spindle > spindleMax) {
    spindle = spindleMax;
  } else if (spindle < spindleMin) {
    spindle = spindleMin;
  }

  stepToContinuous(&z, posFromSpindle(&z, spindle, true));
  stepToContinuous(&x, round(z.pos * zToXRatio));
}

void modeCut() {
  if (x.movingManually || turnPasses <= 0 || x.leftStop == LONG_MAX || x.rightStop == LONG_MIN || dupr == 0 || dupr * opDuprSign < 0) {
    setIsOnFromLoop(false);
    return;
  }

  long startStop = opDuprSign > 0 ? x.rightStop : x.leftStop;
  long endStop = opDuprSign > 0 ? x.leftStop : x.rightStop;

  if (opIndex == 0) {
    // Move to back limit.
    x.speedMax = x.speedManualMove;
    long xPos = startStop;
    stepToFinal(&x, xPos);
    if (x.pos == xPos) {
      opIndex = 1;
      opSubIndex = 0;
    }
  } else if (opIndex <= turnPasses) {
    // Set spindlePos and x.pos in sync.
    if (opSubIndex == 0) {
      spindlePosAvg = spindlePos = spindleFromPos(&x, x.pos);
      opSubIndex = 1;
    }
    // Doing the pass cut.
    if (opSubIndex == 1) {
      x.speedMax = LONG_MAX;
      long endPos = endStop - (endStop - startStop) / turnPasses * (turnPasses - opIndex);
      long xPos = posFromSpindle(&x, spindlePosAvg, true);
      if (dupr > 0 && xPos > endPos) xPos = endPos;
      else if (dupr < 0 && xPos < endPos) xPos = endPos;
      stepToContinuous(&x, xPos);
      if (x.pos == endPos) {
        opSubIndex = 2;
      }
    }
    // Returning to start.
    if (opSubIndex == 2) {
      x.speedMax = x.speedManualMove;
      stepToFinal(&x, startStop);
      if (x.pos == startStop) {
        opSubIndex = 0;
        opIndex++;
      }
    }
  } else {
    setIsOnFromLoop(false);
    beep();
  }
}

long duPerSecondToStepsPerSecond(Axis* a, long duPerSecond) {
  long speed = round(abs(duPerSecond) * a->motorSteps / a->screwPitch);
  return speed < 1 ? 1 : speed;
}

void modeSlot() {
  if (z.movingManually || x.movingManually || turnPasses <= 0 ||
      z.leftStop == LONG_MAX || z.rightStop == LONG_MIN ||
      x.leftStop == LONG_MAX || x.rightStop == LONG_MIN) {
    setIsOnFromLoop(false);
    return;
  }

  long zStartStop = z.rightStop;
  long zEndStop = z.leftStop;
  long xStartStop = auxForward ? x.rightStop : x.leftStop;
  long xEndStop = auxForward ? x.leftStop : x.rightStop;

  if (opIndex == 0) {
    z.speedMax = z.speedManualMove;
    x.speedMax = x.speedManualMove;
    stepToFinal(&z, zStartStop);
    stepToFinal(&x, xStartStop);
    if (z.pos == zStartStop && x.pos == xStartStop) {
      opIndex = 1;
      opSubIndex = 0;
    }
  } else if (opIndex <= turnPasses) {
    long xPos = xEndStop - round((xEndStop - xStartStop) * (turnPasses - opIndex) / float(turnPasses));
    long zReduction = duToSteps(&z, SLOT_LEFT_REDUCTION_DU) * (opIndex - 1);
    long zEndPos = zEndStop - zReduction;
    if (zEndPos < zStartStop) zEndPos = zStartStop;

    if (opSubIndex == 0) {
      x.speedMax = x.speedManualMove;
      stepToFinal(&x, xPos);
      if (x.pos == xPos) {
        opSubIndex = 1;
      }
    } else if (opSubIndex == 1) {
      if (dupr == 0) {
        stepToFinal(&z, z.pos);
        return;
      }
      z.speedMax = duPerSecondToStepsPerSecond(&z, dupr);
      stepToContinuous(&z, zEndPos);
      if (z.pos == zEndPos) {
        opSubIndex = 2;
      }
    } else if (opSubIndex == 2) {
      x.speedMax = x.speedManualMove;
      stepToFinal(&x, xStartStop);
      if (x.pos == xStartStop) {
        opSubIndex = 3;
      }
    } else if (opSubIndex == 3) {
      z.speedMax = z.speedManualMove;
      stepToFinal(&z, zStartStop);
      if (z.pos == zStartStop) {
        opSubIndex = 0;
        opIndex++;
      }
    }
  } else {
    setIsOnFromLoop(false);
    beep();
  }
}

void modeEllipse(Axis* main, Axis* aux) {
  if (main->movingManually || aux->movingManually || turnPasses <= 0 ||
      main->leftStop == LONG_MAX || main->rightStop == LONG_MIN ||
      aux->leftStop == LONG_MAX || aux->rightStop == LONG_MIN ||
      main->leftStop == main->rightStop ||
      aux->leftStop == aux->rightStop ||
      dupr == 0 || dupr != opDupr) {
    setIsOnFromLoop(false);
    return;
  }

  // Start from left or right depending on the pitch.
  long mainStartStop = opDuprSign > 0 ? main->rightStop : main->leftStop;
  long mainEndStop = opDuprSign > 0 ? main->leftStop : main->rightStop;
  long auxStartStop = aux->rightStop;
  long auxEndStop = aux->leftStop;

  main->speedMax = main->speedManualMove;
  aux->speedMax = aux->speedManualMove;

  if (opIndex == 0) {
    opIndex = 1;
    opSubIndex = 0;
    spindlePos = 0;
    spindlePosAvg = 0;
  } else if (opIndex <= turnPasses) {
    float pass0to1 = opIndex / float(turnPasses);
    long mainDelta = round(pass0to1 * (mainEndStop - mainStartStop));
    long auxDelta = round(pass0to1 * (auxEndStop - auxStartStop));
    long spindleDelta = spindleFromPos(main, mainDelta);

    // Move to starting position.
    if (opSubIndex == 0) {
      long auxPos = auxStartStop;
      stepToFinal(aux, auxPos);
      if (aux->pos == auxPos) {
        opSubIndex = 1;
      }
    } else if (opSubIndex == 1) {
      long mainPos = mainEndStop - mainDelta;
      stepToFinal(main, mainPos);
      if (main->pos == mainPos) {
        opSubIndex = 2;
        spindlePos = 0;
        spindlePosAvg = 0;
      }
    } else if (opSubIndex == 2) {
      float progress0to1 = 0;
      if ((spindleDelta > 0 && spindlePosAvg >= spindleDelta) || (spindleDelta < 0 && spindlePosAvg <= spindleDelta)) {
        progress0to1 = 1;
      } else {
        progress0to1 = spindlePosAvg / float(spindleDelta);
      }
      float mainCoeff = auxForward ? cos(HALF_PI * (3 + progress0to1)) : (1 + sin(HALF_PI * (progress0to1 - 1)));
      long mainPos = mainEndStop - mainDelta + round(mainDelta * mainCoeff);
      float auxCoeff = auxForward ? (1 + sin(HALF_PI * (3 + progress0to1))) : sin(HALF_PI * progress0to1);
      long auxPos = auxStartStop + round(auxDelta * auxCoeff);
      stepToContinuous(main, mainPos);
      stepToContinuous(aux, auxPos);
      if (progress0to1 == 1 && main->pos == mainPos && aux->pos == auxPos) {
        opIndex++;
        opSubIndex = 0;
      }
    }
  } else if (opIndex == turnPasses + 1) {
    stepToFinal(aux, auxStartStop);
    if (aux->pos == auxStartStop) {
      setIsOnFromLoop(false);
      beep();
    }
  }
}

void discountFullSpindleTurns() {
  // When standing at the stop, ignore full spindle turns.
  // This allows to avoid waiting when spindle direction reverses
  // and reduces the chance of the skipped stepper steps since
  // after a reverse the spindle starts slow.
  if (dupr != 0 && (isGearboxMode() || mode == MODE_CONE)) {
    Axis* a = getPitchAxis();
    if (stepperIsRunning(a)) return;
    int spindlePosDiff = 0;
    if (a->pos == a->rightStop) {
      long stopSpindlePos = spindleFromPos(a, a->rightStop);
      if (dupr > 0) {
        if (spindlePos < stopSpindlePos - ENCODER_STEPS_INT) {
          spindlePosDiff = ENCODER_STEPS_INT;
        }
      } else {
        if (spindlePos > stopSpindlePos + ENCODER_STEPS_INT) {
          spindlePosDiff = -ENCODER_STEPS_INT;
        }
      }
    } else if (a->pos == a->leftStop) {
      long stopSpindlePos = spindleFromPos(a, a->leftStop);
      if (dupr > 0) {
        if (spindlePos > stopSpindlePos + ENCODER_STEPS_INT) {
          spindlePosDiff = -ENCODER_STEPS_INT;
        }
      } else {
        if (spindlePos < stopSpindlePos - ENCODER_STEPS_INT) {
          spindlePosDiff = ENCODER_STEPS_INT;
        }
      }
    }
    if (spindlePosDiff != 0) {
      spindlePos += spindlePosDiff;
      spindlePosAvg += spindlePosDiff;
    }
  }
}

void processSpindleCounter() {
  pcnt_unit_handle_t unit = pulseUnits[PULSE_COUNTER_SPINDLE];
  if (unit == nullptr) {
    return;
  }
  int count;
  pcnt_unit_get_count(unit, &count);
  int delta = count - spindleCount;
  if (delta == 0) {
    return;
  }
  if (count >= PCNT_CLEAR || count <= -PCNT_CLEAR) {
    pcnt_unit_clear_count(unit);
    spindleCount = 0;
  } else {
    spindleCount = count;
  }

  unsigned long microsNow = micros();
  if (spindleEncTimeIndex >= RPM_BULK) {
    spindleEncTimeDiffBulk = microsNow - spindleEncTimeAtIndex0;
    spindleEncTimeAtIndex0 = microsNow;
    spindleEncTimeIndex = 0;
  }
  spindleEncTimeIndex += abs(delta);

  spindlePos += delta;
  spindlePosGlobal += delta;
  if (spindlePosGlobal > ENCODER_STEPS_INT) {
    spindlePosGlobal -= ENCODER_STEPS_INT;
  } else if (spindlePosGlobal < 0) {
    spindlePosGlobal += ENCODER_STEPS_INT;
  }
  if (spindlePos > spindlePosAvg) {
    spindlePosAvg = spindlePos;
  } else if (spindlePos < spindlePosAvg - ENCODER_BACKLASH) {
    spindlePosAvg = spindlePos + ENCODER_BACKLASH;
  }
  spindleEncTime = microsNow;

  if (spindlePosSync != 0) {
    spindlePosSync += delta;
    if (spindlePosSync % ENCODER_STEPS_INT == 0) {
      spindlePosSync = 0;
      if (mode == MODE_JOYSTICK && joystickLatheSyncPitch != 0) {
        Axis* a = joystickLatheSyncAxis == 1 ? &x : &z;
        spindlePosAvg = spindlePos = spindleFromPosWithModePitch(a, a->pos, joystickLatheSyncPitch);
        joystickLatheSyncPitch = 0;
      } else {
        Axis* a = getPitchAxis();
        spindlePosAvg = spindlePos = spindleFromPos(a, a->pos);
      }
    }
  }
}

// Apply changes requested by the keyboard thread.
void applySettings() {
  if (nextDuprFlag) {
    applyDupr();
    nextDuprFlag = false;
  }
  if (nextStartsFlag) {
    applyStarts();
    nextStartsFlag = false;
  }
  if (z.nextLeftStopFlag) {
    applyLeftStop(&z);
    z.nextLeftStopFlag = false;
  }
  if (z.nextRightStopFlag) {
    applyRightStop(&z);
    z.nextRightStopFlag = false;
  }
  if (x.nextLeftStopFlag) {
    applyLeftStop(&x);
    x.nextLeftStopFlag = false;
  }
  if (x.nextRightStopFlag) {
    applyRightStop(&x);
    x.nextRightStopFlag = false;
  }
  if (y.nextLeftStopFlag) {
    applyLeftStop(&y);
    y.nextLeftStopFlag = false;
  }
  if (y.nextRightStopFlag) {
    applyRightStop(&y);
    y.nextRightStopFlag = false;
  }
  if (nextConeRatioFlag) {
    applyConeRatio();
    nextConeRatioFlag = false;
  }
  if (nextIsOnFlag) {
    setIsOnFromLoop(nextIsOn);
    nextIsOnFlag = false;
  }
  if (nextModeFlag) {
    setModeFromLoop(nextMode);
    nextModeFlag = false;
  }
  if (tftOpenWorkPagePending) {
    tftOpenWorkPagePending = false;
    // INGRANAGGI runs as MODE_NORMAL, so this path cannot use tftIsWorkMode().
    if (mode != MODE_GCODE) tftAutoOpenWorkPage();
  }
}

void setup() {
  loadMachineConfig();
  loadWifiConfig();
  loadKeyboardConfig();
  nextionWriteMutex = xSemaphoreCreateMutex();

  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);

  pinMode(Z_DIR, OUTPUT);
  pinMode(Z_STEP, OUTPUT);
  pinMode(Z_ENA, OUTPUT);
  DHIGH(Z_STEP);

  pinMode(X_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  pinMode(X_ENA, OUTPUT);
  DHIGH(X_STEP);

  if (ACTIVE_Y) {
    pinMode(Y_DIR, OUTPUT);
    pinMode(Y_STEP, OUTPUT);
    pinMode(Y_ENA, OUTPUT);
    DHIGH(Y_STEP);
  }
  initJoystick();

  Preferences pref;
  pref.begin(PREF_NAMESPACE);
  if (pref.getInt(PREF_VERSION) != PREFERENCES_VERSION) {
    pref.clear();
    pref.putInt(PREF_VERSION, PREFERENCES_VERSION);
  }

  initAxis(&z, NAME_Z, true, false, MOTOR_STEPS_Z, SCREW_Z_DU, PULSE_PER_REVOLUTION_Z, SPEED_START_Z, SPEED_MANUAL_MOVE_Z, ACCELERATION_Z, INVERT_Z, INVERT_Z_ENABLE, NEEDS_REST_Z, MAX_TRAVEL_MM_Z, BACKLASH_DU_Z, Z_ENA, Z_DIR, Z_STEP, Z_PULSE_A, Z_PULSE_B, PULSE_COUNTER_Z);
  initAxis(&x, NAME_X, true, false, MOTOR_STEPS_X, SCREW_X_DU, PULSE_PER_REVOLUTION_X, SPEED_START_X, SPEED_MANUAL_MOVE_X, ACCELERATION_X, INVERT_X, INVERT_X_ENABLE, NEEDS_REST_X, MAX_TRAVEL_MM_X, BACKLASH_DU_X, X_ENA, X_DIR, X_STEP, X_PULSE_A, X_PULSE_B, PULSE_COUNTER_X);
  initAxis(&y, NAME_Y, ACTIVE_Y, ROTARY_Y, MOTOR_STEPS_Y, SCREW_Y_DU, PULSE_PER_REVOLUTION_Y, SPEED_START_Y, SPEED_MANUAL_MOVE_Y, ACCELERATION_Y, INVERT_Y, INVERT_Y_ENABLE, NEEDS_REST_Y, MAX_TRAVEL_MM_Y, BACKLASH_DU_Y, Y_ENA, Y_DIR, Y_STEP, Y_PULSE_A, Y_PULSE_B, PULSE_COUNTER_Y);

  isOn = false;
  savedDupr = dupr = pref.getLong(PREF_DUPR);
  motionMutex = xSemaphoreCreateMutex();
  savedStarts = starts = min(STARTS_MAX, max(static_cast<int32_t>(1), pref.getInt(PREF_STARTS)));
  z.savedPos = z.pos = pref.getLong(PREF_POS_Z);
  z.savedPosGlobal = z.posGlobal = pref.getLong(PREF_POS_GLOBAL_Z);
  z.savedOriginPos = z.originPos = pref.getLong(PREF_ORIGIN_POS_Z);
  z.savedMotorPos = z.motorPos = pref.getLong(PREF_MOTOR_POS_Z);
  z.savedLeftStop = z.leftStop = pref.getLong(PREF_LEFT_STOP_Z, LONG_MAX);
  z.savedRightStop = z.rightStop = pref.getLong(PREF_RIGHT_STOP_Z, LONG_MIN);
  z.savedDisabled = z.disabled = pref.getBool(PREF_DISABLED_Z, false);
  x.savedPos = x.pos = pref.getLong(PREF_POS_X);
  x.savedPosGlobal = x.posGlobal = pref.getLong(PREF_POS_GLOBAL_X);
  x.savedOriginPos = x.originPos = pref.getLong(PREF_ORIGIN_POS_X);
  x.savedMotorPos = x.motorPos = pref.getLong(PREF_MOTOR_POS_X);
  x.savedLeftStop = x.leftStop = pref.getLong(PREF_LEFT_STOP_X, LONG_MAX);
  x.savedRightStop = x.rightStop = pref.getLong(PREF_RIGHT_STOP_X, LONG_MIN);
  x.savedDisabled = x.disabled = pref.getBool(PREF_DISABLED_X, false);
  y.savedPos = y.pos = pref.getLong(PREF_POS_Y);
  y.savedPosGlobal = y.posGlobal = pref.getLong(PREF_POS_GLOBAL_Y);
  y.savedOriginPos = y.originPos = pref.getLong(PREF_ORIGIN_POS_Y);
  y.savedMotorPos = y.motorPos = pref.getLong(PREF_MOTOR_POS_Y);
  y.savedLeftStop = y.leftStop = pref.getLong(PREF_LEFT_STOP_Y, LONG_MAX);
  y.savedRightStop = y.rightStop = pref.getLong(PREF_RIGHT_STOP_Y, LONG_MIN);
  y.savedDisabled = y.disabled = pref.getBool(PREF_DISABLED_Y, false);
  savedSpindlePos = spindlePos = pref.getLong(PREF_SPINDLE_POS);
  savedSpindlePosAvg = spindlePosAvg = pref.getLong(PREF_SPINDLE_POS_AVG);
  savedSpindlePosSync = spindlePosSync = pref.getInt(PREF_OUT_OF_SYNC);
  savedSpindlePosGlobal = spindlePosGlobal = pref.getLong(PREF_SPINDLE_POS_GLOBAL);
  savedShowAngle = showAngle = pref.getBool(PREF_SHOW_ANGLE);
  savedShowTacho = showTacho = pref.getBool(PREF_SHOW_TACHO);
  savedMoveStep = moveStep = pref.getLong(PREF_MOVE_STEP, MOVE_STEP_1);
  savedMode = pref.getInt(PREF_MODE);
  if (savedMode < MODE_NORMAL || savedMode > MODE_SLOT || (savedMode == MODE_Y && !ACTIVE_Y)) savedMode = MODE_NORMAL;
  setModeFromLoop(savedMode);
  savedMeasure = measure = pref.getInt(PREF_MEASURE);
  savedConeRatio = coneRatio = pref.getFloat(PREF_CONE_RATIO, coneRatio);
  if (savedMode == MODE_CONE) recomputeConeRatio();
  savedTurnPasses = turnPasses = pref.getInt(PREF_TURN_PASSES, turnPasses);
  savedAuxForward = auxForward = pref.getBool(PREF_AUX_FORWARD, true);
  pref.end();

  if (!z.needsRest && !z.disabled) digitalWrite(z.ena, z.invertEnable ? LOW : HIGH);
  if (!x.needsRest && !x.disabled) digitalWrite(x.ena, x.invertEnable ? LOW : HIGH);
  if (y.active && !y.needsRest && !y.disabled) digitalWrite(y.ena, y.invertEnable ? LOW : HIGH);

  if (LittleFS.begin(true)) {
    gcodeProgramCount = getGcodeProgramCount();
  }

  // Debug.
  Serial.begin(115200);
  if (WIFI_ENABLED) {
    webUiEventQueue = xQueueCreate(WEB_UI_EVENT_QUEUE_LENGTH, sizeof(WebUiEvent));
  }

  // Nextion.
  Serial1.begin(NEXTION_NORMAL_BAUD, SERIAL_8N1, 44, 43);

  // Initialize the keyboard.
  keyboard.begin(KEY_DATA, KEY_CLOCK);
  xTaskCreatePinnedToCore(taskKeypad, "taskKeypad", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  if (joystickUsable()) xTaskCreatePinnedToCore(taskJoystick, "taskJoystick", 4000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);

  // Non-time-sensitive tasks on core 0.
  delay(1300); // Nextion needs time to boot or first display update will be ignored.
  // The display keeps its page across an ESP-only reboot; returning to the
  // menu keeps both sides in sync and re-arms drawing via the page 0x10 event.
  toScreen("page 0");
  if (xTaskCreatePinnedToCore(taskAttachInterrupts, "taskAttachInterrupts", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */) == pdPASS) {
    while (!pulseCountersReady) {
      delay(1);
    }
  }
  xTaskCreatePinnedToCore(taskDisplay, "taskDisplay", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskMoveZ, "taskMoveZ", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskMoveX, "taskMoveX", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  if (ACTIVE_Y) xTaskCreatePinnedToCore(taskMoveY, "taskMoveY", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskGcode, "taskGcode", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  if (WIFI_ENABLED) xTaskCreatePinnedToCore(taskWiFi, "taskWiFi", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
}

void loop() {
  if (emergencyStop != ESTOP_NONE) {
    return;
  }
  if (xSemaphoreTake(motionMutex, 1) != pdTRUE) {
    return;
  }
  applySettings();
  processSpindleCounter();
  discountFullSpindleTurns();
  if (mode == MODE_JOYSTICK && spindlePosSync != 0 && !joystickLatheFeedCommandActive()) {
    cancelJoystickLatheSync();
    resetJoystickLatheFeedPosition();
  }
  if (!isOn || (dupr == 0 && mode != MODE_SLOT) || spindlePosSync != 0) {
    // None of the modes work.
    if (mode == MODE_JOYSTICK && (!isOn || dupr == 0)) {
      resetJoystickLatheFeedPosition();
    }
  } else if (mode == MODE_NORMAL) {
    modeGearbox(&z);
  } else if (mode == MODE_XGEAR) {
    modeGearbox(&x);
  } else if (mode == MODE_JOYSTICK) {
    modeJoystick();
  } else if (mode == MODE_TURN) {
    modeTurn(&z, &x);
  } else if (mode == MODE_FACE) {
    modeTurn(&x, &z);
  } else if (mode == MODE_CUT) {
    modeCut();
  } else if (mode == MODE_SLOT) {
    modeSlot();
  } else if (mode == MODE_CONE) {
    modeCone();
  } else if (mode == MODE_THREAD) {
    modeTurn(&z, &x);
  } else if (mode == MODE_ELLIPSE) {
    modeEllipse(&z, &x);
  }
  moveAxis(&z);
  moveAxis(&x);
  if (ACTIVE_Y) moveAxis(&y);
  xSemaphoreGive(motionMutex);
}
