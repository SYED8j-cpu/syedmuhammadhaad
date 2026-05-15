/*
 * Space Invaders - Console Game (Turn-Based)
 * Department of Computer Science, UET Lahore
 *
 * We removed #include <cstdlib> and #include <ctime>
 * and replaced everything they provided with simple
 * functions we write ourselves.
 *
 * Compile: g++ space_game.cpp -o space_game
 * Run:     space_game.exe   (Windows)
 *          ./space_game     (Linux / Mac)
 *
 * Controls (type a key, then press ENTER):
 *   a - Move left
 *   d - Move right
 *   f - Fire
 *   p - Pause / Unpause
 *   q - Quit
 */

// ─────────────────────────────────────────────────────────────
//  ONLY ONE HEADER NEEDED NOW
//  <iostream> gives us cin and cout for input/output.
//  We no longer need <cstdlib> (for rand/srand/system)
//  or <ctime> (for time), because we write our own versions.
// ─────────────────────────────────────────────────────────────
#include <iostream>
using namespace std;


// ═════════════════════════════════════════════════════════════
//  PART 1 — OUR OWN RANDOM NUMBER GENERATOR
//
//  rand() and srand() came from <cstdlib>.
//  We replace them with a simple formula called an LCG
//  (Linear Congruential Generator).
//
//  How it works:
//    - We keep one number called rngState (the "seed").
//    - Every time we want a random number we run:
//        rngState = rngState * BIG_NUMBER + ANOTHER_NUMBER
//      This scrambles rngState into a new value.
//    - We return part of that scrambled value.
//  The two magic numbers below are from a famous maths book
//  ("Numerical Recipes") — they are known to produce a good
//  spread of values.
// ═════════════════════════════════════════════════════════════

unsigned int rngState = 12345;   // Starting value (the "seed").
                                 // Any number works here.

// Call this once at the start to set the seed.
// Different seeds → different enemy behaviour each game.
void seedRng(unsigned int newSeed)
{
    rngState = newSeed;
}

// Returns one non-negative random integer.
// Replaces rand().
int myRand()
{
    // LCG formula — multiplier and increment from Numerical Recipes.
    rngState = rngState * 1664525u + 1013904223u;

    // Keep only the lower 31 bits so the result is always positive.
    // The >> 1 shifts right by 1 bit, which is the same as dividing
    // by 2 and dropping the sign bit.
    return (int)((rngState >> 1) & 0x7FFFFFFF);
}

// Returns a random number from 0 up to (but NOT including) n.
// Example: randUpTo(6) gives 0, 1, 2, 3, 4, or 5.
// Replaces the common pattern  rand() % n
int randUpTo(int n)
{
    return myRand() % n;
}


// ═════════════════════════════════════════════════════════════
//  PART 2 — OUR OWN SCREEN CLEAR
//
//  system("cls || clear") came from <cstdlib>.
//  It ran an external OS command to wipe the screen.
//  That's considered unsafe, and it needs <cstdlib>.
//
//  Our replacement just prints 40 blank lines.
//  That pushes the old output off the top of the terminal,
//  so the board appears fresh each turn.
// ═════════════════════════════════════════════════════════════

void clearScreen()
{
    for (int i = 0; i < 40; i++)
        cout << "\n";
}


// ─────────────────────────────────────────────────────────────
//  BOARD SIZE CONSTANTS
//  const means the value never changes while the program runs.
// ─────────────────────────────────────────────────────────────
const int ROWS         = 25;
const int COLS         = 50;
const int MAX_ENEMIES  = 12;
const int MAX_BULLETS  = 20;
const int MAX_EBULLETS = 20;


// ─────────────────────────────────────────────────────────────
//  CHARACTERS DRAWN ON THE BOARD
// ─────────────────────────────────────────────────────────────
const char EMPTY   = ' ';
const char WALL    = '#';
const char PLAYER  = 'P';
const char BULLET  = '|';   // your shot — travels upward
const char EBULLET = 'v';   // enemy shot — travels downward
const char ENEMY_A = 'A';   // basic drone — moves left/right
const char ENEMY_B = 'B';   // gunship     — moves + fires
const char ENEMY_C = 'C';   // predator    — diagonal + fires often


// ─────────────────────────────────────────────────────────────
//  DATA STRUCTURES
//  A struct groups related variables under one name.
// ─────────────────────────────────────────────────────────────

// Represents one bullet (either yours or an enemy's)
struct Bullet {
    int  row;      // which row it is on
    int  col;      // which column it is on
    bool active;   // true = still flying, false = gone
};

// Represents one enemy ship
struct Enemy {
    int  row;           // position
    int  col;
    char type;          // 'A', 'B', or 'C'
    int  health;        // hits needed to destroy it
    bool active;        // false = destroyed
    int  dir;           // +1 moves right, -1 moves left
    int  diagDirR;      // row direction used by type C
    int  fireCooldown;  // turns until next shot
};


// ─────────────────────────────────────────────────────────────
//  GLOBAL GAME STATE
//  Variables declared here are accessible by every function.
// ─────────────────────────────────────────────────────────────
char board[ROWS][COLS];   // the 2-D grid we draw each turn

int  playerRow;
int  playerCol;
int  playerHealth = 5;
int  playerLives  = 3;
int  score        = 0;
int  level        = 1;
bool gameOver     = false;
bool playerWon    = false;
bool paused       = false;

Enemy  enemies[MAX_ENEMIES];
int    enemyCount = 0;

Bullet bullets[MAX_BULLETS];    // your bullets
Bullet eBullets[MAX_EBULLETS];  // enemy bullets


// ─────────────────────────────────────────────────────────────
//  BOARD HELPER FUNCTIONS
// ─────────────────────────────────────────────────────────────

// Fill every cell with a space (blank).
void clearBoard()
{
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            board[r][c] = EMPTY;
}

// Draw '#' around the edge of the board.
void drawWalls()
{
    // Top and bottom rows
    for (int c = 0; c < COLS; c++) {
        board[0][c]        = WALL;
        board[ROWS - 1][c] = WALL;
    }
    // Left and right columns
    for (int r = 0; r < ROWS; r++) {
        board[r][0]        = WALL;
        board[r][COLS - 1] = WALL;
    }
}

// Put a character on the board, but only inside the walls.
void placeOnBoard(int r, int c, char ch)
{
    if (r > 0 && r < ROWS - 1 && c > 0 && c < COLS - 1)
        board[r][c] = ch;
}


// ─────────────────────────────────────────────────────────────
//  PAUSE
//  Flips paused between true and false.
//  When paused == true, all game functions do nothing.
// ─────────────────────────────────────────────────────────────
void pause()
{
    paused = !paused;   // ! means "flip" — true becomes false, false becomes true

    if (paused)
        cout << "\n  *** GAME PAUSED *** Type p + ENTER to resume\n";
    else
        cout << "\n  *** GAME RESUMED ***\n";
}


// ─────────────────────────────────────────────────────────────
//  PRINT BOARD
//  Rebuilds the grid from scratch, then prints it.
//  Using clearScreen() instead of system("cls || clear").
// ─────────────────────────────────────────────────────────────
void printBoard()
{
    // Step 1 — start with a blank board and draw the walls.
    clearBoard();
    drawWalls();

    // Step 2 — place every active game object onto the grid.
    placeOnBoard(playerRow, playerCol, PLAYER);

    for (int i = 0; i < enemyCount; i++)
        if (enemies[i].active)
            placeOnBoard(enemies[i].row, enemies[i].col, enemies[i].type);

    for (int i = 0; i < MAX_BULLETS; i++)
        if (bullets[i].active)
            placeOnBoard(bullets[i].row, bullets[i].col, BULLET);

    for (int i = 0; i < MAX_EBULLETS; i++)
        if (eBullets[i].active)
            placeOnBoard(eBullets[i].row, eBullets[i].col, EBULLET);

    // Step 3 — clear the terminal so the new frame replaces the old one.
    clearScreen();   // <-- our own function, no <cstdlib> needed

    // Step 4 — print the HUD (heads-up display) above the board.
    cout << "  Level: " << level
         << "  |  Score: " << score
         << "  |  Lives: " << playerLives
         << "  |  Health: ";
    for (int h = 0; h < playerHealth; h++)
        cout << "* ";
    cout << "\n";

    // Step 5 — print the board row by row.
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++)
            cout << board[r][c];
        cout << "\n";
    }

    // Step 6 — show controls (or pause message) below the board.
    if (paused)
        cout << "\n  *** PAUSED *** Type p + ENTER to resume\n";
    else
        cout << "\n  [a] Left  [d] Right  [f] Fire  [p] Pause  [q] Quit\n";

    cout << "  Your move: ";
}


// ─────────────────────────────────────────────────────────────
//  PLAYER MOVEMENT
//  Both functions check paused first and do nothing if paused.
// ─────────────────────────────────────────────────────────────

void movePlayerLeft()
{
    if (paused) {
        cout << "  [PAUSED] Cannot move. Press p to resume.\n";
        return;   // stop here — do not move
    }

    // col - 1 > 0 makes sure we don't walk into the left wall
    if (playerCol - 1 > 0)
        playerCol--;
}

void movePlayerRight()
{
    if (paused) {
        cout << "  [PAUSED] Cannot move. Press p to resume.\n";
        return;
    }

    // COLS - 1 is the right wall, so we stop one step before it
    if (playerCol + 1 < COLS - 1)
        playerCol++;
}


// ─────────────────────────────────────────────────────────────
//  FIRE
//  Finds the first inactive slot in the bullets array and
//  puts a new bullet just above the player.
// ─────────────────────────────────────────────────────────────
void fire()
{
    if (paused) {
        cout << "  [PAUSED] Cannot fire. Press p to resume.\n";
        return;
    }

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {          // found an empty slot
            bullets[i].row    = playerRow - 1;   // one row above player
            bullets[i].col    = playerCol;
            bullets[i].active = true;
            return;   // only fire one bullet per turn
        }
    }
    // If all slots are full, the shot is silently ignored.
}


// ─────────────────────────────────────────────────────────────
//  MOVE ENEMY
//  Moves enemy number 'idx' one step in the given direction.
//  direction can be: "left", "right", "up", "down", or "diag"
// ─────────────────────────────────────────────────────────────
void moveEnemy(int idx, string direction)
{
    if (paused) return;   // enemies freeze when paused

    // '&' means we're editing the actual enemy, not a copy of it.
    Enemy& e = enemies[idx];

    if (!e.active) return;   // skip destroyed enemies

    if (direction == "left"  && e.col - 1 > 0)         e.col--;
    if (direction == "right" && e.col + 1 < COLS - 1)  e.col++;
    if (direction == "up"    && e.row - 1 > 0)          e.row--;
    if (direction == "down"  && e.row + 1 < ROWS - 1)  e.row++;

    if (direction == "diag") {
        // If we're about to hit a wall, reverse direction.
        if (e.col + e.dir      <= 0 || e.col + e.dir      >= COLS - 1) e.dir      = -e.dir;
        if (e.row + e.diagDirR <= 0 || e.row + e.diagDirR >= ROWS - 1) e.diagDirR = -e.diagDirR;
        e.col += e.dir;
        e.row += e.diagDirR;
    }
}


// ─────────────────────────────────────────────────────────────
//  MOVE FIRE
//  Moves ALL active bullets one step each turn.
//  timeStep = how many rows each bullet moves (usually 1).
//  Also checks whether any bullet has hit something.
// ─────────────────────────────────────────────────────────────
void moveFire(int timeStep)
{
    if (paused) return;   // bullets freeze when paused

    // ── Your bullets travel upward (row number decreases) ──
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;   // skip empty slots

        bullets[i].row -= timeStep;         // move up

        // Did it leave the screen?
        if (bullets[i].row <= 0) {
            bullets[i].active = false;
            continue;
        }

        // Did it hit an enemy?
        for (int j = 0; j < enemyCount; j++) {
            if (!enemies[j].active) continue;

            if (bullets[i].row == enemies[j].row &&
                bullets[i].col == enemies[j].col)
            {
                bullets[i].active = false;   // bullet disappears
                enemies[j].health--;         // enemy loses 1 HP

                // Destroy the enemy if health reaches 0.
                if (enemies[j].health <= 0) {
                    enemies[j].active = false;

                    // Award points — harder enemies give more.
                    if      (enemies[j].type == ENEMY_C) score += 30;
                    else if (enemies[j].type == ENEMY_B) score += 20;
                    else                                  score += 10;
                }
            }
        }
    }

    // ── Enemy bullets travel downward (row number increases) ──
    for (int i = 0; i < MAX_EBULLETS; i++) {
        if (!eBullets[i].active) continue;

        eBullets[i].row += timeStep;   // move down

        // Did it leave the screen?
        if (eBullets[i].row >= ROWS - 1) {
            eBullets[i].active = false;
            continue;
        }

        // Did it hit the player?
        if (eBullets[i].row == playerRow &&
            eBullets[i].col == playerCol)
        {
            eBullets[i].active = false;
            playerHealth--;

            // If health hits 0, lose a life and reset health.
            if (playerHealth <= 0) {
                playerLives--;
                playerHealth = 5;
                if (playerLives <= 0)
                    gameOver = true;
            }
        }
    }
}


// ─────────────────────────────────────────────────────────────
//  ENEMY FIRE
//  Fires a bullet from enemy number 'idx'.
// ─────────────────────────────────────────────────────────────
void enemyFire(int idx)
{
    if (paused) return;

    for (int i = 0; i < MAX_EBULLETS; i++) {
        if (!eBullets[i].active) {
            eBullets[i].row    = enemies[idx].row + 1;   // just below the enemy
            eBullets[i].col    = enemies[idx].col;
            eBullets[i].active = true;
            return;
        }
    }
}


// ─────────────────────────────────────────────────────────────
//  SPAWN ENEMIES
//  Creates a fresh wave of enemies for the current level.
//  Higher levels have more enemies.
// ─────────────────────────────────────────────────────────────
void spawnEnemies()
{
    enemyCount = 0;

    // Start with 4 enemies; add 2 more per level, up to the maximum.
    int count = 4 + (level - 1) * 2;
    if (count > MAX_ENEMIES) count = MAX_ENEMIES;

    for (int i = 0; i < count; i++) {
        enemies[i].col          = 3 + (i * 4) % (COLS - 6);   // spread across the board
        enemies[i].row          = 2 + (i / 4) * 2;            // stack in rows of 4
        enemies[i].active       = true;
        enemies[i].dir          = (i % 2 == 0) ? 1 : -1;      // alternate directions
        enemies[i].diagDirR     = 1;
        enemies[i].fireCooldown = randUpTo(5) + 3;  // <-- uses our randUpTo, not rand()

        // Cycle through types: A, B, C, A, B, C ...
        int t = i % 3;
        if      (t == 0) { enemies[i].type = ENEMY_A; enemies[i].health = 1; }
        else if (t == 1) { enemies[i].type = ENEMY_B; enemies[i].health = 2; }
        else             { enemies[i].type = ENEMY_C; enemies[i].health = 3; }

        enemyCount++;
    }
}


// ─────────────────────────────────────────────────────────────
//  INIT LEVEL
//  Resets bullets and player position, then spawns enemies.
//  Called at the start of every level (including level 1).
// ─────────────────────────────────────────────────────────────
void initLevel()
{
    // Clear all bullets from the previous level.
    for (int i = 0; i < MAX_BULLETS;  i++) bullets[i].active  = false;
    for (int i = 0; i < MAX_EBULLETS; i++) eBullets[i].active = false;

    // Place the player near the bottom centre.
    playerRow    = ROWS - 3;
    playerCol    = COLS / 2;
    playerHealth = 5;

    spawnEnemies();
}


// ─────────────────────────────────────────────────────────────
//  GET SEED
//  Asks the player to type a number.
//  This replaces  srand(time(0))  which needed <ctime>.
//
//  Why do we need a seed?
//  Our myRand() always produces the same sequence of numbers
//  if it starts from the same seed.  By letting the player
//  type a different number each game, every game feels
//  different (enemies fire at different times, etc.).
// ─────────────────────────────────────────────────────────────
unsigned int getSeed()
{
    cout << "  Type any whole number to randomise the game: ";
    unsigned int s;
    cin >> s;
    cin.ignore();   // discard the leftover newline so the next cin works correctly
    return s;
}


// ─────────────────────────────────────────────────────────────
//  MAIN — THE GAME LOOP
//  Everything comes together here.
// ─────────────────────────────────────────────────────────────
int main()
{
    // ── Welcome screen ───────────────────────────────────────
    cout << "\n\n  === SPACE INVADERS ===\n\n";
    cout << "  Enemy types:\n";
    cout << "   A - Basic Drone  (1 HP, moves left/right)\n";
    cout << "   B - Gunship      (2 HP, moves left/right + fires)\n";
    cout << "   C - Predator     (3 HP, moves diagonally + fires often)\n\n";
    cout << "  You have 3 lives and 5 HP per life.\n";
    cout << "  Each turn: type a letter and press ENTER.\n\n";

    // ── Seed the random number generator ─────────────────────
    // getSeed() replaces time(0) — no <ctime> needed.
    seedRng(getSeed());

    // ── Set up level 1 ───────────────────────────────────────
    initLevel();

    // ── Main loop — keeps running until the game ends ────────
    while (!gameOver && !playerWon)
    {
        // Show the current state of the board.
        printBoard();

        // Read one character from the player.
        char ch;
        cin >> ch;
        cin.ignore();   // discard the leftover newline

        // ── Handle input ─────────────────────────────────────

        // q always quits, even when paused.
        if (ch == 'q' || ch == 'Q') {
            gameOver = true;
            break;
        }

        // p toggles the pause flag and loops back to printBoard.
        if (ch == 'p' || ch == 'P') {
            pause();
            continue;   // skip the rest of this turn
        }

        // Movement and firing.
        // Each function checks 'paused' internally and does
        // nothing if the game is paused — so these are safe
        // to call without an extra check here.
        if (ch == 'a' || ch == 'A') movePlayerLeft();
        if (ch == 'd' || ch == 'D') movePlayerRight();
        if (ch == 'f' || ch == 'F') fire();

        // Advance all bullets by 1 row (does nothing if paused).
        moveFire(1);

        // ── Move enemies and let them fire ───────────────────
        for (int i = 0; i < enemyCount; i++) {
            if (!enemies[i].active) continue;

            // Types A and B bounce left/right.
            if (enemies[i].type == ENEMY_A || enemies[i].type == ENEMY_B) {
                int nextCol = enemies[i].col + enemies[i].dir;

                // Hit a wall? Reverse direction and step down one row.
                if (nextCol <= 0 || nextCol >= COLS - 1) {
                    enemies[i].dir = -enemies[i].dir;
                    if (enemies[i].row + 1 < ROWS - 3)
                        enemies[i].row++;
                }

                // Move in the current direction.
                moveEnemy(i, enemies[i].dir == 1 ? "right" : "left");
            }
            else {
                // Type C moves diagonally.
                moveEnemy(i, "diag");
            }

            // If an enemy reaches the player's row, it's game over.
            if (!paused && enemies[i].row >= playerRow)
                gameOver = true;

            // Decrement the fire timer and shoot if it hits 0.
            if (!paused) {
                enemies[i].fireCooldown--;
                if (enemies[i].fireCooldown <= 0) {
                    // B fires 1 in 3 times, C fires 1 in 2 times.
                    if (enemies[i].type == ENEMY_B && randUpTo(3) == 0) enemyFire(i);
                    if (enemies[i].type == ENEMY_C && randUpTo(2) == 0) enemyFire(i);

                    // Reset the cooldown to a new random value.
                    enemies[i].fireCooldown = randUpTo(5) + 3;  // <-- randUpTo, not rand()
                }
            }
        }

        // ── Check for level clear ────────────────────────────
        int aliveCount = 0;
        for (int i = 0; i < enemyCount; i++)
            if (enemies[i].active)
                aliveCount++;

        if (aliveCount == 0) {
            level++;
            if (level > 3) {
                playerWon = true;
                break;
            }
            score += 50 * level;   // bonus points for clearing a level
            printBoard();
            cout << "\n  *** Level " << level << " — get ready! Press ENTER...\n";
            cin.get();
            paused = false;   // make sure we aren't still paused
            initLevel();
        }
    }

    // ── End screen ───────────────────────────────────────────
    clearScreen();
    cout << "\n\n  ================================\n";
    if (playerWon)
        cout << "      YOU WIN! Congratulations!\n";
    else
        cout << "            GAME OVER\n";
    cout << "        Final score: " << score << "\n";
    cout << "  ================================\n\n";

    return 0;
}