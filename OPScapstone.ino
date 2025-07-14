//row and column pin definitions
const uint8_t rowPins[8] = {22, 20, 3, 21, 8, 4, 9, 6};
const uint8_t colPins[8] = {17, 14, 15, 2, 5, 16, 18, 19};

//joystick, led, button definitions
#define jstickX 28
#define jstickY 27
#define jstickButton 26
#define REDLED 10
#define YELLOWLED 11
#define GREENLED 12
#define startButton 13

//game variables
int playerX = 1;
int playerY = 1;
bool gameStarted = false;
bool gameWon = false;
bool joystickEngaged = false;
bool jstickButtonPressed = false;
int currentMaze = 0;

//player blink variables
bool blinkState = true;
unsigned long lastBlink = 0;
const unsigned long blinkInterval = 377;

//led blink variables
bool greenLedState = false;
bool redLedState = false;
unsigned long lastGreenBlink = 0;
unsigned long lastRedBlink = 0;
const unsigned long ledBlinkInterval = 700;

//win variables
unsigned long winDisplayTimer = 0;
bool showingWinScreen = true;
bool winner = false;

//variables for the displays and mazes
bool display[8][8];
bool maze[8][8];

//win coordinate variables
int winX, winY;
int winX1 = 7, winY1 = 6;
int winX2 = 0, winY2 = 1;
int winX3 = 7, winY3 = 1;

//maze layouts
bool maze1[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,1},
    {1,0,1,0,1,0,1,1},
    {1,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,0,0,0,1,0,1},
    {1,1,1,1,0,1,0,0},
    {1,1,1,1,1,1,1,1}
};

bool maze2[8][8] = {
    {1,1,1,1,1,1,1,1},
    {0,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,0,0,0,1,0,1},
    {1,1,1,1,0,1,0,1},
    {1,0,0,1,0,0,0,1},
    {1,0,1,1,1,1,0,1},
    {1,1,1,1,1,1,1,1}
};

bool maze3[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,0},
    {1,1,0,1,0,1,0,1},
    {1,0,0,0,0,1,0,1},
    {1,0,1,1,0,1,0,1},
    {1,0,0,1,0,0,0,1},
    {1,1,0,1,1,1,0,1},
    {1,1,1,1,1,1,1,1}
};

//number screens
bool num1[8][8] = {
    {0,0,0,1,1,0,0,0},
    {0,0,1,1,1,0,0,0},
    {0,1,1,1,1,0,0,0},
    {0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1}
};

bool num2[8][8] = {
    {0,0,1,1,1,1,0,0},
    {1,1,1,1,1,1,1,1},
    {1,1,0,0,0,1,1,1},
    {0,0,0,0,1,1,1,0},
    {0,0,0,1,1,1,0,0},
    {0,0,1,1,1,0,0,0},
    {0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1}
};

bool num3[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1}
};

//arrow, win, loss screens
bool arrow[8][8] = {
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,1,0,0},
    {0,0,0,0,1,1,1,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,1,1,1,0},
    {0,0,0,0,1,1,0,0},
    {0,0,0,0,1,0,0,0}
};

bool winScreen[8][8] = {
    {1,0,0,0,1,0,0,0},
    {1,0,1,0,1,0,0,0},
    {1,1,0,1,1,0,1,0},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,1,0},
    {1,1,0,0,1,0,1,0},
    {1,0,1,0,1,0,0,0},
    {1,0,0,1,1,0,0,0}
};

bool lossScreen[8][8] = {
    {1,1,1,0,0,0,0,0},
    {1,1,1,0,0,0,0,0},
    {1,1,1,0,0,0,0,0},
    {1,1,1,0,0,0,0,0},
    {1,1,1,0,0,0,0,0},
    {1,1,1,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1}
};

void setup() {
     //set all row and column pins to be outputs
     //set all rows and columns to be in the opposite state required for LEDs to be on (all LEDs off)
    for (int i = 0; i < 8; i++) {
        pinMode(rowPins[i], OUTPUT);
        pinMode(colPins[i], OUTPUT);
        digitalWrite(rowPins[i], LOW);
        digitalWrite(colPins[i], HIGH);
    }

    //set joystick movements (x and y direction) and joystick button to inputs
    pinMode(jstickX, INPUT);
    pinMode(jstickY, INPUT);
    pinMode(jstickButton, INPUT_PULLUP);

    //set leds to output
    pinMode(REDLED, OUTPUT);
    pinMode(YELLOWLED, OUTPUT);
    pinMode(GREENLED, OUTPUT);

    //set start button to input
    pinMode(startButton, INPUT_PULLUP);

    //initialize serial and UART communication
    Serial.begin(9600);
    Serial1.setTX(0);
    Serial1.setRX(1);
    Serial1.begin(115200);
}

void loop() {
    // Wait for both players to start
    if (!gameStarted) {
        waitForStart();
        return;
    }

    // Main game loop
    if (!gameWon) {
        handleJstick();
        playerBlink();
        updateDisplay();
        drawDisplay();

        // Check if player reached the winning coordinate
        if (playerX == winX && playerY == winY) {
            gameWon = true;

            // Send WIN signal to the other Pico
            Serial1.println("WIN");

            bool otherWon = false;
            unsigned long startTime = millis();

            // Wait briefly to see if the other Pico also sends a WIN
            while (millis() - startTime < 250) {
                if (Serial1.available()) {
                    String msg = Serial1.readStringUntil('\n');
                    msg.trim();
                    if (msg == "WIN") {
                        otherWon = true;
                        break;
                    }
                }
            }

            // Determine winner based on whether the other Pico also claimed a win
            winner = !otherWon;

            // Show the correct end screen
            patternToDisplay(winner ? winScreen : lossScreen);
            digitalWrite(GREENLED, LOW);
            digitalWrite(REDLED, LOW);
            winDisplayTimer = millis();
        }
    } else {
        // After game is over
        if (winner) {
            greenBlink();
        } else {
            redBlink();
        }

        // Alternate between win/loss screen and arrow animation
        if (millis() - winDisplayTimer >= 1500) {
            showingWinScreen = !showingWinScreen;
            winDisplayTimer = millis();
        }

        patternToDisplay(showingWinScreen ? (winner ? winScreen : lossScreen) : arrow);
        drawDisplay();

        // Reset game when start button is pressed again
        if (digitalRead(startButton) == LOW) {
            delay(150);
            while (digitalRead(startButton) == LOW) delay(10);
            gameStarted = false;
            gameWon = false;
            winner = false;
            digitalWrite(GREENLED, LOW);
            digitalWrite(REDLED, LOW);
            greenLedState = false;
            redLedState = false;
        }
    }

    delay(1);
}

//start state
void waitForStart() {
    //initializing led colors
    digitalWrite(REDLED, HIGH);
    digitalWrite(YELLOWLED, LOW);
    digitalWrite(GREENLED, LOW);

    Serial.println("Waiting for start button...");

    while (digitalRead(startButton) == HIGH) {
        if (digitalRead(jstickButton) == LOW && !jstickButtonPressed) {
            jstickButtonPressed = true;
            currentMaze = (currentMaze + 1) % 3;

            if (currentMaze == 0) patternToDisplay(num1);
            else if (currentMaze == 1) patternToDisplay(num2);
            else patternToDisplay(num3);

            for (int i = 0; i < 600; i += 10) {
                drawDisplay();
                delay(10);
            }
        }

        if (digitalRead(jstickButton) == HIGH) {
            jstickButtonPressed = false;
        }

        patternToDisplay(arrow);
        drawDisplay();
        delay(1);
    }

    delay(150);
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, HIGH);

    Serial.println("Start button pressed. Sending READY...");
    bool sentReady = false;
    bool receivedReady = false;
    bool goReceived = false;

    unsigned long startTime = millis();
    while (!gameStarted && millis() - startTime < 5000) {
        if (!sentReady) {
            Serial1.println("READY");
            Serial.println("READY sent.");
            sentReady = true;
        }

        if (Serial1.available()) {
            String msg = Serial1.readStringUntil('\n');
            msg.trim(); // Clean newline/whitespace

            Serial.print("Serial1 received: ");
            Serial.println(msg);

            if (msg == "READY" && !receivedReady) {
                Serial.println("Received READY from other device.");
                receivedReady = true;
                delay(100); // Give both time to acknowledge
                Serial1.println("GO");
                Serial.println("Sent GO.");
                gameStarted = true;
            } else if (msg == "GO") {
                Serial.println("Received GO.");
                goReceived = true;
                gameStarted = true;
            }
        }

        delay(10);
    }

    digitalWrite(GREENLED, LOW);

    if (!gameStarted) {
        Serial.println("Timeout: other device did not respond.");
        digitalWrite(REDLED, HIGH);
        return;
    }

    Serial.println("Both players ready. Starting countdown...");

    // Countdown
    digitalWrite(REDLED, HIGH);
    patternToDisplay(num3); for (int i = 0; i < 1000; i += 10) { drawDisplay(); delay(10); }

    digitalWrite(REDLED, LOW);
    digitalWrite(YELLOWLED, HIGH);
    patternToDisplay(num2); for (int i = 0; i < 1000; i += 10) { drawDisplay(); delay(10); }

    digitalWrite(YELLOWLED, LOW);
    digitalWrite(GREENLED, HIGH);
    patternToDisplay(num1); for (int i = 0; i < 1000; i += 10) { drawDisplay(); delay(10); }

    digitalWrite(GREENLED, LOW);

    // Maze and player setup
    if (currentMaze == 0) {
        memcpy(maze, maze1, sizeof(maze));
        winX = winX1; winY = winY1;
        playerX = 1; playerY = 1;
    } else if (currentMaze == 1) {
        memcpy(maze, maze2, sizeof(maze));
        winX = winX2; winY = winY2;
        playerX = 6; playerY = 6;
    } else {
        memcpy(maze, maze3, sizeof(maze));
        winX = winX3; winY = winY3;
        playerX = 1; playerY = 6;
    }
}

//handles joysick movements
void handleJstick() {
    int horiz = analogRead(jstickX);
    int vert = analogRead(jstickY);
    int dx = 0, dy = 0;

    //jstick deadzones (basically joystick sensitivity)
    if (horiz < 500) dx = 1;
    else if (horiz > 950) dx = -1;
    if (vert > 950) dy = -1;
    else if (vert < 500) dy = 1;

    //player moves, but player cannot move past edges or into maze barriers
    if ((dx != 0 || dy != 0) && !joystickEngaged) {
        int newX = constrain(playerX + dx, 0, 7);
        int newY = constrain(playerY + dy, 0, 7);
        if (maze[newY][newX] == 0) {
            playerX = newX;
            playerY = newY;
        }
        joystickEngaged = true;
    }

    if (dx == 0 && dy == 0) joystickEngaged = false;
}

//update player blinking
void playerBlink() {
    if (millis() - lastBlink > blinkInterval) {
        blinkState = !blinkState;
        lastBlink = millis();
    }
}

//update green light blinking after win
void greenBlink() {
    if (millis() - lastGreenBlink >= ledBlinkInterval) {
        greenLedState = !greenLedState;
        digitalWrite(GREENLED, greenLedState ? HIGH : LOW);
        lastGreenBlink = millis();
    }
}

//update red light blinking after loss
void redBlink() {
    if (millis() - lastRedBlink >= ledBlinkInterval) {
        redLedState = !redLedState;
        digitalWrite(REDLED, redLedState ? HIGH : LOW);
        lastRedBlink = millis();
    }
}

//updates display as player moves
void updateDisplay() {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            display[y][x] = maze[y][x];
        }
    }
    display[playerY][playerX] = blinkState ? 1 : 0;
}

//initialize matrix display
void drawDisplay() {
    for (int col = 0; col < 8; col++) {
        digitalWrite(colPins[col], LOW);
        for (int row = 0; row < 8; row++) {
            digitalWrite(rowPins[row], display[row][col] ? HIGH : LOW);
        }
        delay(1);
        digitalWrite(colPins[col], HIGH);
        for (int row = 0; row < 8; row++) {
            digitalWrite(rowPins[row], LOW);
        }
    }
}

//copy different pattern arrays to display
void patternToDisplay(bool pattern[8][8]) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            display[y][x] = pattern[y][x];
        }
    }
}