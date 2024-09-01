#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <atomic>
#include "src/getDimensions.h"

using namespace std;

atomic<int> width, height;

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to clear the console screen
void clearScreen() {
    system("cls");
}

// Function to continuously update the window size
DWORD WINAPI updateWindowSize(LPVOID lpParam) {
    int w, h;
    while (true) {
        getDimentions(w, h);
        width.store(w);
        height.store(h);
    }
    return 0;
}

int main() {
    srand(time(NULL));

    HANDLE hThread = CreateThread(NULL, 0, updateWindowSize, NULL, 0, NULL);
    if (hThread == NULL) {
        cerr << "Error creating thread!" << endl;
        return 1;
    }

    while (true){

        clearScreen();

        int currentWidth = width.load();
        int currentHeight = height.load();

        for (int i = 0; i < currentHeight; ++i) {
            for (int j = 0; j < currentWidth; ++j) {
                if (rand() % 100 < 5) { // 5% chance to print a star
                    setCursorPosition(j, i);
                    cout << "*";
                }
            }
        }
        Sleep(50);
    }

    /*
    This line wont be executed since the thing is never ending

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    */
    return 0;
}