/*
    PAC-MAN GAME - Simple 2D Array Implementation
    Department of Computer Science, UET Lahore
    
    Controls: W = Up, S = Down, A = Left, D = Right, Q = Quit
*/

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

// ============================================================
//  CONSTANTS
// ============================================================
const int ROWS = 20;
const int COLS = 40;

// What each cell means in the maze array
const char WALL      = '#';
const char DOT       = '.';
const char ENERGIZER = 'O';
const char EMPTY     = ' ';

// ============================================================
//  GLOBAL VARIABLES
// ============================================================

// The 2D maze array - this is the main data structure
char maze[ROWS][COLS];

// Pac-Man position and direction
int pacRow, pacCol;
int pacDirRow, pacDirCol;  // direction of movement

// 4 Ghosts - each has a row, col, and direction
int ghostRow[4], ghostCol[4];
int ghostDirRow[4], ghostDirCol[4];

// Ghost starting positions
int ghostStartRow[4] = {9, 9, 10, 10};
int ghostStartCol[4] = {18, 19, 18, 19};

// Game state
int score;
int lives;
int energizerTimer;  // counts down from 30

// ============================================================
//  THE MAZE (stored in a file, loaded into 2D array)
// ============================================================

void saveMazeToFile()
{
    ofstream file("maze.txt");

    file << "########################################" << endl;
    file << "#..................O...................#" << endl;
    file << "#.####.####.#########.####.####.####.#" << endl;
    file << "#.####.####.#########.####.####.####.#" << endl;
    file << "#......................................#" << endl;
    file << "#.####.##.###########.##.####.######.#" << endl;
    file << "#......##.....###.....##......######.#" << endl;
    file << "#######.##### ### #####.#############" << endl;
    file << "#######.#           #.#############" << endl;
    file << "#######.# ######### #.#############" << endl;
    file << "       .  #       #  .             " << endl;
    file << "#######.# ######### #.#############" << endl;
    file << "#######.#           #.#############" << endl;
    file << "#######.### ####### ###.###########" << endl;
    file << "#......##...........##.............#" << endl;
    file << "#.####.##.#########.##.####.#####.#" << endl;
    file << "#O......................O...........#" << endl;
    file << "#.####.##.#########.##.####.#####.#" << endl;
    file << "#......................................#" << endl;
    file << "########################################" << endl;

    file.close();
}

void loadMazeFromFile()
{
    // First create the file if it doesn't exist
    saveMazeToFile();

    ifstream file("maze.txt");

    for (int r = 0; r < ROWS; r++)
    {
        string line;
        getline(file, line);
        for (int c = 0; c < COLS; c++)
        {
            if (c < (int)line.size())
                maze[r][c] = line[c];
            else
                maze[r][c] = EMPTY;
        }
    }

    file.close();
}

// ============================================================
//  GOTOXY - Move cursor to position (no flicker)
// ============================================================
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ============================================================
//  DRAW EVERYTHING
// ============================================================
void drawAll()
{
    // Draw HUD (score, lives)
    gotoxy(0, 0);
    cout << "Score: " << score << "   Lives: ";
    for (int i = 0; i < lives; i++) cout << "C ";
    cout << "   ";
    if (energizerTimer > 0)
        cout << "[POWER MODE: " << energizerTimer << "]  ";
    else
        cout << "                    ";

    // Draw the 2D maze array
    for (int r = 0; r < ROWS; r++)
    {
        gotoxy(0, r + 2);
        for (int c = 0; c < COLS; c++)
        {
            cout << maze[r][c];
        }
    }

    // Draw Pac-Man on top of maze
    gotoxy(pacCol, pacRow + 2);
    cout << 'C';

    // Draw 4 ghosts on top of maze
    for (int i = 0; i < 4; i++)
    {
        gotoxy(ghostCol[i], ghostRow[i] + 2);
        if (energizerTimer > 0)
            cout << 'B';   // blue/scared ghost
        else
            cout << 'G';
    }
}

// ============================================================
//  INITIALIZE GAME
// ============================================================
void initGame()
{
    loadMazeFromFile();

    // Pac-Man starts at row 16, col 1
    pacRow = 16;
    pacCol = 1;
    pacDirRow = 0;
    pacDirCol = 1;  // start moving right

    // Set ghost starting positions and directions
    for (int i = 0; i < 4; i++)
    {
        ghostRow[i] = ghostStartRow[i];
        ghostCol[i] = ghostStartCol[i];
    }

    // Ghost 0: moves horizontally (right)
    ghostDirRow[0] = 0;  ghostDirCol[0] = 1;

    // Ghost 1: moves vertically (down)
    ghostDirRow[1] = 1;  ghostDirCol[1] = 0;

    // Ghost 2: random - start moving right
    ghostDirRow[2] = 0;  ghostDirCol[2] = 1;

    // Ghost 3: chaser - starts moving left
    ghostDirRow[3] = 0;  ghostDirCol[3] = -1;

    score = 0;
    lives = 3;
    energizerTimer = 0;
}

// ============================================================
//  MOVE PAC-MAN
// ============================================================
void movePacMan()
{
    int newRow = pacRow + pacDirRow;
    int newCol = pacCol + pacDirCol;

    // Check boundary
    if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS)
        return;

    // Check wall
    if (maze[newRow][newCol] == WALL)
        return;

    // Erase old position in maze display
    // (we leave the maze cell as is, just move pac position)
    pacRow = newRow;
    pacCol = newCol;

    // Eat dot
    if (maze[pacRow][pacCol] == DOT)
    {
        score += 10;
        maze[pacRow][pacCol] = EMPTY;
    }
    // Eat energizer
    else if (maze[pacRow][pacCol] == ENERGIZER)
    {
        score += 50;
        maze[pacRow][pacCol] = EMPTY;
        energizerTimer = 30;  // power mode for 30 iterations
    }
}

// ============================================================
//  MOVE GHOST 0 - Horizontal Only (bounces off walls)
// ============================================================
void moveGhost0()
{
    int newCol = ghostCol[0] + ghostDirCol[0];

    // If wall ahead, reverse direction
    if (newCol < 0 || newCol >= COLS || maze[ghostRow[0]][newCol] == WALL)
    {
        ghostDirCol[0] = -ghostDirCol[0];
        newCol = ghostCol[0] + ghostDirCol[0];
    }

    if (newCol >= 0 && newCol < COLS && maze[ghostRow[0]][newCol] != WALL)
        ghostCol[0] = newCol;
}

// ============================================================
//  MOVE GHOST 1 - Vertical Only (bounces off walls)
// ============================================================
void moveGhost1()
{
    int newRow = ghostRow[1] + ghostDirRow[1];

    // If wall ahead, reverse direction
    if (newRow < 0 || newRow >= ROWS || maze[newRow][ghostCol[1]] == WALL)
    {
        ghostDirRow[1] = -ghostDirRow[1];
        newRow = ghostRow[1] + ghostDirRow[1];
    }

    if (newRow >= 0 && newRow < ROWS && maze[newRow][ghostCol[1]] != WALL)
        ghostRow[1] = newRow;
}

// ============================================================
//  MOVE GHOST 2 - Random Movement
// ============================================================
void moveGhost2()
{
    // 4 possible directions: up, down, left, right
    int dirR[4] = {-1, 1,  0, 0};
    int dirC[4] = { 0, 0, -1, 1};

    // Try current direction first
    int newRow = ghostRow[2] + ghostDirRow[2];
    int newCol = ghostCol[2] + ghostDirCol[2];

    // If current direction is blocked, pick a random new direction
    if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS
        || maze[newRow][newCol] == WALL)
    {
        // Try random directions until one works
        int tries = 0;
        while (tries < 10)
        {
            int d = rand() % 4;
            newRow = ghostRow[2] + dirR[d];
            newCol = ghostCol[2] + dirC[d];
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS
                && maze[newRow][newCol] != WALL)
            {
                ghostDirRow[2] = dirR[d];
                ghostDirCol[2] = dirC[d];
                break;
            }
            tries++;
        }
    }

    // Move
    newRow = ghostRow[2] + ghostDirRow[2];
    newCol = ghostCol[2] + ghostDirCol[2];
    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS
        && maze[newRow][newCol] != WALL)
    {
        ghostRow[2] = newRow;
        ghostCol[2] = newCol;
    }
}

// ============================================================
//  MOVE GHOST 3 - Chases Pac-Man (simple step toward him)
// ============================================================
void moveGhost3()
{
    // Find which direction gets us closer to Pac-Man
    int bestRow = ghostRow[3];
    int bestCol = ghostCol[3];
    int bestDist = 99999;

    int dirR[4] = {-1, 1,  0, 0};
    int dirC[4] = { 0, 0, -1, 1};

    for (int d = 0; d < 4; d++)
    {
        int newRow = ghostRow[3] + dirR[d];
        int newCol = ghostCol[3] + dirC[d];

        // Skip walls and out of bounds
        if (newRow < 0 || newRow >= ROWS) continue;
        if (newCol < 0 || newCol >= COLS) continue;
        if (maze[newRow][newCol] == WALL) continue;

        // Calculate Manhattan distance to Pac-Man
        int dist = abs(newRow - pacRow) + abs(newCol - pacCol);

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
//  CHECK COLLISION (Pac-Man vs Ghosts)
// ============================================================
bool checkCollision()
{
    for (int i = 0; i < 4; i++)
    {
        if (ghostRow[i] == pacRow && ghostCol[i] == pacCol)
        {
            if (energizerTimer > 0)
            {
                // Pac-Man eats the ghost!
                score += 200;
                // Reset ghost to start
                ghostRow[i] = ghostStartRow[i];
                ghostCol[i] = ghostStartCol[i];
            }
            else
            {
                // Ghost eats Pac-Man
                return true;
            }
        }
    }
    return false;
}

// ============================================================
//  COUNT REMAINING DOTS (win condition)
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
//  MAIN FUNCTION
// ============================================================
int main()
{
    srand(time(0));

    // Hide blinking cursor
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 1;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);

    system("cls");

    // Show simple start screen
    gotoxy(10, 5);  cout << "=== PAC-MAN GAME ===";
    gotoxy(10, 7);  cout << "Controls:";
    gotoxy(10, 8);  cout << "  W = Up    S = Down";
    gotoxy(10, 9);  cout << "  A = Left  D = Right";
    gotoxy(10, 10); cout << "  Q = Quit";
    gotoxy(10, 12); cout << "Symbols:";
    gotoxy(10, 13); cout << "  C = Pac-Man  G = Ghost  B = Scared Ghost";
    gotoxy(10, 14); cout << "  . = Dot (10 pts)  O = Energizer (50 pts)";
    gotoxy(10, 15); cout << "  Eat ghost while powered = 200 pts";
    gotoxy(10, 17); cout << "Press any key to start...";

    getch();  // wait for key press
    system("cls");

    initGame();

    // ---- MAIN GAME LOOP ----
    while (true)
    {
        // Draw everything
        drawAll();

        // Read player input (non-blocking)
        if (_kbhit())
        {
            char key = getch();

            if (key == 'q' || key == 'Q')
                break;

            // Change Pac-Man direction
            if (key == 'w' || key == 'W') { pacDirRow = -1; pacDirCol = 0; }
            if (key == 's' || key == 'S') { pacDirRow =  1; pacDirCol = 0; }
            if (key == 'a' || key == 'A') { pacDirRow =  0; pacDirCol = -1; }
            if (key == 'd' || key == 'D') { pacDirRow =  0; pacDirCol =  1; }

            // Arrow keys (send 2 bytes: 224 then the key)
            if (key == (char)224)
            {
                char arrow = getch();
                if (arrow == 72) { pacDirRow = -1; pacDirCol = 0; }  // up
                if (arrow == 80) { pacDirRow =  1; pacDirCol = 0; }  // down
                if (arrow == 75) { pacDirRow =  0; pacDirCol = -1; } // left
                if (arrow == 77) { pacDirRow =  0; pacDirCol =  1; } // right
            }
        }

        // Move Pac-Man
        movePacMan();

        // Move all 4 ghosts
        moveGhost0();
        moveGhost1();
        moveGhost2();
        moveGhost3();

        // Decrease energizer timer
        if (energizerTimer > 0)
            energizerTimer--;

        // Check if ghost caught Pac-Man
        if (checkCollision())
        {
            lives--;

            gotoxy(5, ROWS + 3);
            cout << "  *** CAUGHT! Lives left: " << lives << " ***  ";

            if (lives <= 0)
            {
                gotoxy(5, ROWS + 4);
                cout << "  GAME OVER! Final Score: " << score;
                gotoxy(5, ROWS + 5);
                cout << "  Press any key...";
                getch();
                break;
            }

            // Reset Pac-Man and ghosts to start
            pacRow = 16;
            pacCol = 1;
            pacDirRow = 0;
            pacDirCol = 1;

            for (int i = 0; i < 4; i++)
            {
                ghostRow[i] = ghostStartRow[i];
                ghostCol[i] = ghostStartCol[i];
            }

            energizerTimer = 0;

            Sleep(1500);  // pause so player sees message
            gotoxy(5, ROWS + 3);
            cout << "                              ";
        }

        // Check win condition (all dots eaten)
        if (countDots() == 0)
        {
            gotoxy(5, ROWS + 3);
            cout << "  *** YOU WIN! Score: " << score << " ***";
            gotoxy(5, ROWS + 4);
            cout << "  Press any key...";
            getch();
            break;
        }

        Sleep(150);  // controls game speed
    }

    // Save final maze state to file
    ofstream save("maze_save.txt");
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
            save << maze[r][c];
        save << endl;
    }
    save.close();

    return 0;
}