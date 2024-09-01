#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

void getDimentions(int &columns, int &rows) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        std::cerr << "Error retrieving console screen buffer info\n";
        columns = rows = -1;
        return;
    }
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}