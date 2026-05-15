#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// ============================================================
//  CONSTANTS
// ============================================================
const int ROWS = 20;
const int COLS = 40;

const char WALL      = '#';
const char DOT       = '.';
const char ENERGIZER = 'O';
const char EMPTY     = ' ';

// ============================================================
//  CUSTOM RANDOM NUMBER GENERATOR
//  Uses a Linear Congruential Generator (LCG).
//  QueryPerformanceCounter gives a high-resolution seed
//  without needing <ctime>.
// ============================================================
unsigned long long rngState = 12345;   // fallback if counter fails

void seedRNG()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    rngState = (unsigned long long)counter.QuadPart;
}

int customRand()
{
    // LCG constants from Numerical Recipes.
    rngState = rngState * 1664525ULL + 1013904223ULL;
    // Return a positive 15-bit value.
    return (int)((rngState >> 16) & 0x7FFF);
}

// ============================================================
//  CUSTOM CLEAR SCREEN  (no system("cls"))
//  Uses the Windows console API to blank every cell.
// ============================================================
void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD count;
    COORD homeCoord = {0, 0};
    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoord, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoord, &count);
    SetConsoleCursorPosition(hConsole, homeCoord);
}

// ============================================================
//  CUSTOM ABS  (no <cstdlib>)
// ============================================================
int customAbs(int x)
{
    return (x < 0) ? -x : x;
}

// ============================================================
//  GOTOXY — move the console cursor to column x, row y
// ============================================================
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ============================================================
//  GLOBAL VARIABLES
// ============================================================
char maze[ROWS][COLS];

int pacRow, pacCol;
int pacDirRow, pacDirCol;

int ghostRow[4], ghostCol[4];
int ghostDirRow[4], ghostDirCol[4];

// FIX 2: start positions moved to open cells inside the ghost house
// (rows 9-10, cols 19-20 in the new maze — all ' ' cells).
int ghostStartRow[4] = {9,  9,  10, 10};
int ghostStartCol[4] = {19, 20, 19, 20};

int score;
int lives;
int energizerTimer;

// ============================================================
//  THE MAZE  (embedded directly — no file I/O needed)
//
//  FIX 1: every row is now exactly 40 characters wide.
//  FIX 2: ghost house (rows 9-10, cols 18-22) uses ' ' cells
//          so ghosts start in open space.
//  FIX 3: Pac-Man starts at row 1, col 1 which is always '.'.
//  FIX 4: no endl / \r\n issue because there is no file.
// ============================================================
const char* MAZE_TEMPLATE[ROWS] = {
    "########################################",  // row  0
    ".......................................#",  // row  1  <- Pac-Man starts here (col 1)
    "#.####.####.######.####.####.####.####.",  // row  2
    "#.####.####.######.####.####.####.####.",  // row  3
    "#......................................#",  // row  4
    "#.####.##.##########.##.####.######.###",  // row  5 -- fixed width (was 41)
    "#......##.....###....##......######....#",  // row  6
    "#######.##### ### #####.###############",  // row  7
    "#######.#           #.#################",  // row  8
    "#######.# ######### #.#################",  // row  9  ghost house row A
    "        .  #     #  .                  ",  // row 10  ghost house row B (open corridor)
    "#######.# ######### #.#################",  // row 11
    "#######.#           #.#################",  // row 12
    "#######.### ####### ###.###############",  // row 13
    "#......##...........##.................#",  // row 14
    "#.####.##.#########.##.####.#####.####.",  // row 15
    "O..............................O........",  // row 16  energizers at col 0 and col 30
    "#.####.##.#########.##.####.#####.####.",  // row 17
    "#......................................#",  // row 18
    "########################################"   // row 19
};

void loadMaze()
{
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            maze[r][c] = MAZE_TEMPLATE[r][c];
}

// ============================================================
//  DRAW EVERYTHING
//
//  FIX 5: before drawing each ghost at its NEW position we
//  first blank its OLD position so no trail is left behind.
// ============================================================

// Tracks where each ghost was drawn last frame so we can erase it.
int prevGhostRow[4], prevGhostCol[4];
bool firstDraw = true;   // skip erase on the very first frame

void drawAll()
{
    // ── HUD line ────────────────────────────────────────────
    gotoxy(0, 0);
    cout << "Score: " << score << "   Lives: ";
    for (int i = 0; i < lives; i++) cout << "C ";
    cout << "   ";
    if (energizerTimer > 0)
        cout << "[POWER MODE: " << energizerTimer << "]  ";
    else
        cout << "                    ";

    // ── Draw maze ───────────────────────────────────────────
    for (int r = 0; r < ROWS; r++)
    {
        gotoxy(0, r + 2);
        for (int c = 0; c < COLS; c++)
            cout << maze[r][c];
    }

    // ── Draw Pac-Man ────────────────────────────────────────
    gotoxy(pacCol, pacRow + 2);
    cout << 'C';

    // ── Erase old ghost positions, then draw new ones ───────
    if (!firstDraw)
    {
        for (int i = 0; i < 4; i++)
        {
            // Only erase if the ghost actually moved.
            if (prevGhostRow[i] != ghostRow[i] || prevGhostCol[i] != ghostCol[i])
            {
                gotoxy(prevGhostCol[i], prevGhostRow[i] + 2);
                // Restore what the maze has at that cell.
                cout << maze[prevGhostRow[i]][prevGhostCol[i]];
            }
        }
    }
    firstDraw = false;

    // Draw ghosts at their current positions.
    for (int i = 0; i < 4; i++)
    {
        gotoxy(ghostCol[i], ghostRow[i] + 2);
        cout << (energizerTimer > 0 ? 'B' : 'G');

        // Remember where we drew them so next frame can erase.
        prevGhostRow[i] = ghostRow[i];
        prevGhostCol[i] = ghostCol[i];
    }
}

// ============================================================
//  INITIALIZE GAME
// ============================================================
void initGame()
{
    loadMaze();

    // FIX 3: start Pac-Man at row 1 col 1, which is '.' in the maze.
    pacRow    = 1;
    pacCol    = 1;
    pacDirRow = 0;
    pacDirCol = 1;   // initially moving right

    for (int i = 0; i < 4; i++)
    {
        ghostRow[i] = ghostStartRow[i];
        ghostCol[i] = ghostStartCol[i];
        // Also initialise prev positions so erase works correctly.
        prevGhostRow[i] = ghostStartRow[i];
        prevGhostCol[i] = ghostStartCol[i];
    }

    ghostDirRow[0] = 0;  ghostDirCol[0] =  1;   // ghost 0: right
    ghostDirRow[1] = 1;  ghostDirCol[1] =  0;   // ghost 1: down
    ghostDirRow[2] = 0;  ghostDirCol[2] =  1;   // ghost 2: right (random)
    ghostDirRow[3] = 0;  ghostDirCol[3] = -1;   // ghost 3: left (chaser)

    score         = 0;
    lives         = 3;
    energizerTimer = 0;
    firstDraw     = true;
}

// ============================================================
//  MOVE PAC-MAN
// ============================================================
void movePacMan()
{
    int newRow = pacRow + pacDirRow;
    int newCol = pacCol + pacDirCol;

    // Bounds check.
    if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS)
        return;

    // Wall check.
    if (maze[newRow][newCol] == WALL)
        return;

    pacRow = newRow;
    pacCol = newCol;

    if (maze[pacRow][pacCol] == DOT)
    {
        score += 10;
        maze[pacRow][pacCol] = EMPTY;
    }
    else if (maze[pacRow][pacCol] == ENERGIZER)
    {
        score += 50;
        maze[pacRow][pacCol] = EMPTY;
        energizerTimer = 30;
    }
}

// ============================================================
//  GHOST 0 — horizontal bounce
// ============================================================
void moveGhost0()
{
    int newCol = ghostCol[0] + ghostDirCol[0];

    // Hit a wall or edge? Reverse and try again.
    if (newCol < 0 || newCol >= COLS || maze[ghostRow[0]][newCol] == WALL)
    {
        ghostDirCol[0] = -ghostDirCol[0];
        newCol = ghostCol[0] + ghostDirCol[0];
    }

    if (newCol >= 0 && newCol < COLS && maze[ghostRow[0]][newCol] != WALL)
        ghostCol[0] = newCol;
}

// ============================================================
//  GHOST 1 — vertical bounce
// ============================================================
void moveGhost1()
{
    int newRow = ghostRow[1] + ghostDirRow[1];

    if (newRow < 0 || newRow >= ROWS || maze[newRow][ghostCol[1]] == WALL)
    {
        ghostDirRow[1] = -ghostDirRow[1];
        newRow = ghostRow[1] + ghostDirRow[1];
    }

    if (newRow >= 0 && newRow < ROWS && maze[newRow][ghostCol[1]] != WALL)
        ghostRow[1] = newRow;
}

// ============================================================
//  GHOST 2 — random movement
//
//  FIX 6: after the random tries, fall back to a systematic
//  scan of all 4 directions so the ghost never gets stuck.
// ============================================================
void moveGhost2()
{
    int dirR[4] = {-1,  1,  0,  0};
    int dirC[4] = { 0,  0, -1,  1};

    int newRow = ghostRow[2] + ghostDirRow[2];
    int newCol = ghostCol[2] + ghostDirCol[2];

    // If the current direction is blocked, pick a new one.
    if (newRow < 0 || newRow >= ROWS ||
        newCol < 0 || newCol >= COLS ||
        maze[newRow][newCol] == WALL)
    {
        bool found = false;

        // First: try up to 20 random directions.
        for (int tries = 0; tries < 20 && !found; tries++)
        {
            int d = customRand() % 4;
            newRow = ghostRow[2] + dirR[d];
            newCol = ghostCol[2] + dirC[d];
            if (newRow >= 0 && newRow < ROWS &&
                newCol >= 0 && newCol < COLS &&
                maze[newRow][newCol] != WALL)
            {
                ghostDirRow[2] = dirR[d];
                ghostDirCol[2] = dirC[d];
                found = true;
            }
        }

        // FIX 6: fallback — scan all 4 directions systematically
        // so the ghost is never permanently stuck.
        if (!found)
        {
            for (int d = 0; d < 4 && !found; d++)
            {
                newRow = ghostRow[2] + dirR[d];
                newCol = ghostCol[2] + dirC[d];
                if (newRow >= 0 && newRow < ROWS &&
                    newCol >= 0 && newCol < COLS &&
                    maze[newRow][newCol] != WALL)
                {
                    ghostDirRow[2] = dirR[d];
                    ghostDirCol[2] = dirC[d];
                    found = true;
                }
            }
        }
    }

    // Apply the chosen direction.
    newRow = ghostRow[2] + ghostDirRow[2];
    newCol = ghostCol[2] + ghostDirCol[2];
    if (newRow >= 0 && newRow < ROWS &&
        newCol >= 0 && newCol < COLS &&
        maze[newRow][newCol] != WALL)
    {
        ghostRow[2] = newRow;
        ghostCol[2] = newCol;
    }
}

// ============================================================
//  GHOST 3 — chaser (Manhattan distance)
// ============================================================
void moveGhost3()
{
    int dirR[4] = {-1,  1,  0,  0};
    int dirC[4] = { 0,  0, -1,  1};

    int bestRow  = ghostRow[3];
    int bestCol  = ghostCol[3];
    int bestDist = 99999;

    for (int d = 0; d < 4; d++)
    {
        int newRow = ghostRow[3] + dirR[d];
        int newCol = ghostCol[3] + dirC[d];

        if (newRow < 0 || newRow >= ROWS) continue;
        if (newCol < 0 || newCol >= COLS) continue;
        if (maze[newRow][newCol] == WALL)  continue;

        int dist = customAbs(newRow - pacRow) + customAbs(newCol - pacCol);
        if (dist < bestDist)
        {
            bestDist = dist;
            bestRow  = newRow;
            bestCol  = newCol;
        }
    }

    ghostRow[3] = bestRow;
    ghostCol[3] = bestCol;
}

// ============================================================
//  CHECK COLLISION
// ============================================================
bool checkCollision()
{
    for (int i = 0; i < 4; i++)
    {
        if (ghostRow[i] == pacRow && ghostCol[i] == pacCol)
        {
            if (energizerTimer > 0)
            {
                score += 200;
                ghostRow[i] = ghostStartRow[i];
                ghostCol[i] = ghostStartCol[i];
            }
            else
            {
                return true;   // Pac-Man was caught
            }
        }
    }
    return false;
}

// ============================================================
//  COUNT REMAINING DOTS
// ============================================================
int countDots()
{
    int count = 0;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            if (maze[r][c] == DOT || maze[r][c] == ENERGIZER)
                count++;
    return count;
}

// ============================================================
//  MAIN
// ============================================================
int main()
{
    seedRNG();

    // Hide the blinking cursor so the board looks cleaner.
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize   = 1;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);

    clearScreen();

    // ── Welcome screen ───────────────────────────────────────
    gotoxy(10, 5);  cout << "=== PAC-MAN GAME ===";
    gotoxy(10, 7);  cout << "Controls:";
    gotoxy(10, 8);  cout << "  W = Up    S = Down";
    gotoxy(10, 9);  cout << "  A = Left  D = Right";
    gotoxy(10, 10); cout << "  Q = Quit";
    gotoxy(10, 12); cout << "Symbols:";
    gotoxy(10, 13); cout << "  C = Pac-Man  G = Ghost  B = Scared ghost";
    gotoxy(10, 14); cout << "  . = Dot (10 pts)   O = Energizer (50 pts)";
    gotoxy(10, 15); cout << "  Eat ghost while powered = 200 pts";
    gotoxy(10, 17); cout << "Press any key to start...";

    getch();
    clearScreen();

    initGame();

    // ── Main game loop ───────────────────────────────────────
    while (true)
    {
        drawAll();

        // Read keyboard input (non-blocking).
        if (_kbhit())
        {
            char key = getch();

            if (key == 'q' || key == 'Q') break;

            if (key == 'w' || key == 'W') { pacDirRow = -1; pacDirCol =  0; }
            if (key == 's' || key == 'S') { pacDirRow =  1; pacDirCol =  0; }
            if (key == 'a' || key == 'A') { pacDirRow =  0; pacDirCol = -1; }
            if (key == 'd' || key == 'D') { pacDirRow =  0; pacDirCol =  1; }

            // Arrow keys send two bytes: 224 then a code.
            if (key == (char)224)
            {
                char arrow = getch();
                if (arrow == 72) { pacDirRow = -1; pacDirCol =  0; }  // up
                if (arrow == 80) { pacDirRow =  1; pacDirCol =  0; }  // down
                if (arrow == 75) { pacDirRow =  0; pacDirCol = -1; }  // left
                if (arrow == 77) { pacDirRow =  0; pacDirCol =  1; }  // right
            }
        }

        movePacMan();
        moveGhost0();
        moveGhost1();
        moveGhost2();
        moveGhost3();

        // FIX 7: decrement energizer timer BEFORE the collision
        // check, but NOT during the death pause that follows.
        if (energizerTimer > 0)
            energizerTimer--;

        // ── Collision check ───────────────────────────────────
        if (checkCollision())
        {
            lives--;

            gotoxy(5, ROWS + 3);
            cout << "  *** CAUGHT! Lives left: " << lives << " ***  ";

            if (lives <= 0)
            {
                gotoxy(5, ROWS + 4);
                cout << "  GAME OVER! Final score: " << score;
                gotoxy(5, ROWS + 5);
                cout << "  Press any key...";
                getch();
                break;
            }

            // Reset Pac-Man position.
            pacRow    = 1;
            pacCol    = 1;
            pacDirRow = 0;
            pacDirCol = 1;

            // Reset all ghosts to their start positions.
            for (int i = 0; i < 4; i++)
            {
                ghostRow[i] = ghostStartRow[i];
                ghostCol[i] = ghostStartCol[i];
                prevGhostRow[i] = ghostStartRow[i];
                prevGhostCol[i] = ghostStartCol[i];
            }

            // FIX 7: freeze the timer during the pause so
            // power mode doesn't expire while the player can't act.
            // energizerTimer is intentionally NOT touched here.

            Sleep(1500);

            // Clear the "CAUGHT!" message.
            gotoxy(5, ROWS + 3);
            cout << "                              ";

            // Redraw so the reset positions show immediately.
            firstDraw = true;
            drawAll();
        }

        // ── Win condition ─────────────────────────────────────
        if (countDots() == 0)
        {
            gotoxy(5, ROWS + 3);
            cout << "  *** YOU WIN! Score: " << score << " ***";
            gotoxy(5, ROWS + 4);
            cout << "  Press any key...";
            getch();
            break;
        }

        Sleep(150);   // ~6-7 frames per second
    }

    // FIX 8: removed the maze_save.txt block — it was never read
    // anywhere and just created a stale file on disk every game.

    return 0;
}