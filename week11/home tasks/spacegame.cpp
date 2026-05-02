/*
 * Space Invaders - Console Game (Turn-Based)
 * Department of Computer Science, UET Lahore
 * Task 01 + Task 02 Implementation
 *
 * Compile: g++ space_game.cpp -o space_game
 * Run:     space_game.exe  (Windows)  OR  ./space_game  (Linux)
 *
 * Controls (type key then press ENTER each turn):
 *   a - Move player left
 *   d - Move player right
 *   f - Fire
 *   p - Pause / Unpause
 *   q - Quit
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// ─────────────────────────────────────────────
//  BOARD DIMENSIONS
// ─────────────────────────────────────────────
const int ROWS        = 25;
const int COLS        = 50;
const int MAX_ENEMIES  = 12;
const int MAX_BULLETS  = 20;
const int MAX_EBULLETS = 20;

// ─────────────────────────────────────────────
//  CELL SYMBOLS
// ─────────────────────────────────────────────
const char EMPTY   = ' ';
const char WALL    = '#';
const char PLAYER  = 'P';
const char BULLET  = '|';   // player bullet (goes up)
const char EBULLET = 'v';   // enemy bullet  (goes down)
const char ENEMY_A = 'A';   // moves left/right only
const char ENEMY_B = 'B';   // moves left/right + fires
const char ENEMY_C = 'C';   // moves diagonally + fires often

// ─────────────────────────────────────────────
//  DATA STRUCTURES
// ─────────────────────────────────────────────
struct Bullet {
    int  row, col;
    bool active;
};

struct Enemy {
    int  row, col;
    char type;
    int  health;
    bool active;
    int  dir;        // +1 right, -1 left
    int  diagDirR;   // row direction for type C
    int  fireCooldown;
};

// ─────────────────────────────────────────────
//  GLOBAL GAME STATE
// ─────────────────────────────────────────────
char board[ROWS][COLS];

int  playerRow;
int  playerCol;
int  playerHealth = 5;
int  playerLives  = 3;
int  score        = 0;
int  level        = 1;
bool gameOver     = false;
bool playerWon    = false;
bool paused       = false;   // <-- GLOBAL PAUSE FLAG used by all functions

Enemy  enemies[MAX_ENEMIES];
int    enemyCount = 0;

Bullet bullets[MAX_BULLETS];
Bullet eBullets[MAX_EBULLETS];

// ─────────────────────────────────────────────
//  BOARD UTILITIES
// ─────────────────────────────────────────────
void clearBoard() {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            board[r][c] = EMPTY;
}

void drawWalls() {
    for (int c = 0; c < COLS; c++) {
        board[0][c]      = WALL;
        board[ROWS-1][c] = WALL;
    }
    for (int r = 0; r < ROWS; r++) {
        board[r][0]      = WALL;
        board[r][COLS-1] = WALL;
    }
}

void placeOnBoard(int r, int c, char ch) {
    if (r > 0 && r < ROWS-1 && c > 0 && c < COLS-1)
        board[r][c] = ch;
}

// ─────────────────────────────────────────────
//  PAUSE FUNCTION
//  Toggles the global paused flag.
//  When paused = true, ALL game functions
//  (move, fire, enemy AI) do nothing.
// ─────────────────────────────────────────────
void pause() {
    paused = !paused;

    // Inform the player immediately
    if (paused)
        cout << "\n  *** GAME PAUSED *** Type p + ENTER to resume\n";
    else
        cout << "\n  *** GAME RESUMED ***\n";
}

// ─────────────────────────────────────────────
//  6. printBoard  (no gotoxy / getCharAtXY)
// ─────────────────────────────────────────────
void printBoard() {
    clearBoard();
    drawWalls();

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

    system("cls || clear");

    // HUD
    cout << "  Level: " << level
         << "  |  Score: " << score
         << "  |  Lives: " << playerLives
         << "  |  Health: ";
    for (int h = 0; h < playerHealth; h++) cout << "* ";
    cout << "\n";

    // Draw 2D board row by row
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++)
            cout << board[r][c];
        cout << "\n";
    }

    // Controls / pause status
    if (paused)
        cout << "\n  *** PAUSED *** Type p + ENTER to resume\n";
    else
        cout << "\n  [a] Left  [d] Right  [f] Fire  [p] Pause  [q] Quit\n";

    cout << "  Your move: ";
}

// ─────────────────────────────────────────────
//  TASK 01 - REQUIRED FUNCTIONS
//  Every function checks 'paused' first and
//  does nothing if the game is paused.
// ─────────────────────────────────────────────

// 1. movePlayerLeft
void movePlayerLeft() {
    if (paused) {
        cout << "  [PAUSED] Cannot move. Press p to resume.\n";
        return;
    }
    if (playerCol - 1 > 0)
        playerCol--;
}

// 2. movePlayerRight
void movePlayerRight() {
    if (paused) {
        cout << "  [PAUSED] Cannot move. Press p to resume.\n";
        return;
    }
    if (playerCol + 1 < COLS - 1)
        playerCol++;
}

// 3. fire
void fire() {
    if (paused) {
        cout << "  [PAUSED] Cannot fire. Press p to resume.\n";
        return;
    }
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].row    = playerRow - 1;
            bullets[i].col    = playerCol;
            bullets[i].active = true;
            return;
        }
    }
}

// 4. moveEnemy
void moveEnemy(int idx, string direction) {
    if (paused) return;   // pause: enemies freeze

    Enemy& e = enemies[idx];
    if (!e.active) return;

    if (direction == "left"  && e.col - 1 > 0)         e.col--;
    if (direction == "right" && e.col + 1 < COLS - 1)  e.col++;
    if (direction == "down"  && e.row + 1 < ROWS - 1)  e.row++;
    if (direction == "up"    && e.row - 1 > 0)          e.row--;
    if (direction == "diag") {
        if (e.col + e.dir      <= 0 || e.col + e.dir      >= COLS-1) e.dir      = -e.dir;
        if (e.row + e.diagDirR <= 0 || e.row + e.diagDirR >= ROWS-1) e.diagDirR = -e.diagDirR;
        e.col += e.dir;
        e.row += e.diagDirR;
    }
}

// 5. moveFire
void moveFire(int timeStep) {
    if (paused) return;   // pause: all bullets freeze

    // Player bullets move up
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;

        bullets[i].row -= timeStep;

        if (bullets[i].row <= 0) { bullets[i].active = false; continue; }

        // Check hit on any enemy
        for (int j = 0; j < enemyCount; j++) {
            if (!enemies[j].active) continue;
            if (bullets[i].row == enemies[j].row &&
                bullets[i].col == enemies[j].col) {
                bullets[i].active = false;
                enemies[j].health--;
                if (enemies[j].health <= 0) {
                    enemies[j].active = false;
                    if      (enemies[j].type == ENEMY_C) score += 30;
                    else if (enemies[j].type == ENEMY_B) score += 20;
                    else                                  score += 10;
                }
            }
        }
    }

    // Enemy bullets move down
    for (int i = 0; i < MAX_EBULLETS; i++) {
        if (!eBullets[i].active) continue;

        eBullets[i].row += timeStep;

        if (eBullets[i].row >= ROWS - 1) { eBullets[i].active = false; continue; }

        // Check hit on player
        if (eBullets[i].row == playerRow &&
            eBullets[i].col == playerCol) {
            eBullets[i].active = false;
            playerHealth--;
            if (playerHealth <= 0) {
                playerLives--;
                playerHealth = 5;
                if (playerLives <= 0) gameOver = true;
            }
        }
    }
}

// ─────────────────────────────────────────────
//  ENEMY FIRING
// ─────────────────────────────────────────────
void enemyFire(int idx) {
    if (paused) return;   // pause: enemies cannot fire

    for (int i = 0; i < MAX_EBULLETS; i++) {
        if (!eBullets[i].active) {
            eBullets[i].row    = enemies[idx].row + 1;
            eBullets[i].col    = enemies[idx].col;
            eBullets[i].active = true;
            return;
        }
    }
}

// ─────────────────────────────────────────────
//  LEVEL SETUP
// ─────────────────────────────────────────────
void spawnEnemies() {
    enemyCount = 0;
    int count = 4 + (level - 1) * 2;
    if (count > MAX_ENEMIES) count = MAX_ENEMIES;

    for (int i = 0; i < count; i++) {
        enemies[i].col          = 3 + (i * 4) % (COLS - 6);
        enemies[i].row          = 2 + (i / 4) * 2;
        enemies[i].active       = true;
        enemies[i].dir          = (i % 2 == 0) ? 1 : -1;
        enemies[i].diagDirR     = 1;
        enemies[i].fireCooldown = rand() % 5 + 3;

        int t = i % 3;
        if      (t == 0) { enemies[i].type = ENEMY_A; enemies[i].health = 1; }
        else if (t == 1) { enemies[i].type = ENEMY_B; enemies[i].health = 2; }
        else             { enemies[i].type = ENEMY_C; enemies[i].health = 3; }

        enemyCount++;
    }
}

void initLevel() {
    for (int i = 0; i < MAX_BULLETS;  i++) bullets[i].active  = false;
    for (int i = 0; i < MAX_EBULLETS; i++) eBullets[i].active = false;

    playerRow    = ROWS - 3;
    playerCol    = COLS / 2;
    playerHealth = 5;

    spawnEnemies();
}

// ─────────────────────────────────────────────
//  MAIN GAME LOOP
// ─────────────────────────────────────────────
int main() {
    srand((unsigned)time(0));

    cout << "\n\n  === SPACE INVADERS ===\n\n";
    cout << "  Enemy Types:\n";
    cout << "   A - Basic Drone  (1 HP, moves left/right)\n";
    cout << "   B - Gunship      (2 HP, moves left/right + fires)\n";
    cout << "   C - Predator     (3 HP, moves diagonally + fires often)\n\n";
    cout << "  You have 3 lives and 5 HP per life.\n";
    cout << "  Each turn: type a letter and press ENTER.\n\n";
    cout << "  Press ENTER to start...";
    cin.get();

    initLevel();

    while (!gameOver && !playerWon) {

        // Show current board state
        printBoard();

        // Read player input
        char ch;
        cin >> ch;
        cin.ignore();

        // ── q always quits ──────────────────────
        if (ch == 'q' || ch == 'Q') {
            gameOver = true;
            break;
        }

        // ── p toggles pause (works any time) ───
        if (ch == 'p' || ch == 'P') {
            pause();
            continue;   // go back to printBoard to show updated pause status
        }

        // ── All game functions internally check
        //    the paused flag and do nothing when
        //    paused, so calling them is safe. ───

        // Player actions
        if (ch == 'a' || ch == 'A') movePlayerLeft();
        if (ch == 'd' || ch == 'D') movePlayerRight();
        if (ch == 'f' || ch == 'F') fire();

        // Advance bullets (does nothing if paused)
        moveFire(1);

        // Move all enemies (does nothing if paused)
        for (int i = 0; i < enemyCount; i++) {
            if (!enemies[i].active) continue;

            if (enemies[i].type == ENEMY_A || enemies[i].type == ENEMY_B) {
                int nextCol = enemies[i].col + enemies[i].dir;
                if (nextCol <= 0 || nextCol >= COLS - 1) {
                    enemies[i].dir = -enemies[i].dir;
                    if (enemies[i].row + 1 < ROWS - 3)
                        enemies[i].row++;
                }
                moveEnemy(i, enemies[i].dir == 1 ? "right" : "left");
            } else {
                moveEnemy(i, "diag");
            }

            // Enemy reached player row → game over
            if (!paused && enemies[i].row >= playerRow)
                gameOver = true;

            // Enemy fires (does nothing if paused)
            if (!paused) {
                enemies[i].fireCooldown--;
                if (enemies[i].fireCooldown <= 0) {
                    if (enemies[i].type == ENEMY_B && rand() % 3 == 0) enemyFire(i);
                    if (enemies[i].type == ENEMY_C && rand() % 2 == 0) enemyFire(i);
                    enemies[i].fireCooldown = rand() % 5 + 3;
                }
            }
        }

        // Check if all enemies are defeated
        int alive = 0;
        for (int i = 0; i < enemyCount; i++)
            if (enemies[i].active) alive++;

        if (alive == 0) {
            level++;
            if (level > 3) { playerWon = true; break; }
            score += 50 * level;
            printBoard();
            cout << "\n  *** Level " << level << " starting! Press ENTER...\n";
            cin.get();
            paused = false;   // always unpause at new level
            initLevel();
        }
    }

    // ── End screen ──────────────────────────────
    system("cls || clear");
    cout << "\n\n  ================================\n";
    if (playerWon)
        cout << "      YOU WIN! Congratulations!\n";
    else
        cout << "            GAME OVER\n";
    cout << "        Final Score: " << score << "\n";
    cout << "  ================================\n\n";

    return 0;
}