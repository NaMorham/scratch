#include "console_display.h"


ConsoleDisplay::ConsoleDisplay()
{
}


ConsoleDisplay::~ConsoleDisplay()
{
}

std::shared_ptr<ConsoleDisplay> ConsoleDisplay::ms_console = nullptr;

bool ConsoleDisplay::usingColour = true;
bool ConsoleDisplay::usingansi = false;

const char* ConsoleDisplay::_on_NRM = "\033[0m";
const char* ConsoleDisplay::_on_BLD = "\033[1m";
const char* ConsoleDisplay::_on_BLK = "\033[30m";
const char* ConsoleDisplay::_on_RED = "\033[31m";
const char* ConsoleDisplay::_on_GRN = "\033[32m";
const char* ConsoleDisplay::_on_YRL = "\033[33m";
const char* ConsoleDisplay::_on_BLU = "\033[34m";
const char* ConsoleDisplay::_on_MAG = "\033[35m";
const char* ConsoleDisplay::_on_CYN = "\033[36m";
const char* ConsoleDisplay::_on_WHT = "\033[37m";

const char* ConsoleDisplay::_off_NRM = "";
const char* ConsoleDisplay::_off_BLD = "";
const char* ConsoleDisplay::_off_BLK = "";
const char* ConsoleDisplay::_off_RED = "";
const char* ConsoleDisplay::_off_GRN = "";
const char* ConsoleDisplay::_off_YRL = "";
const char* ConsoleDisplay::_off_BLU = "";
const char* ConsoleDisplay::_off_MAG = "";
const char* ConsoleDisplay::_off_CYN = "";
const char* ConsoleDisplay::_off_WHT = "";


void allColours()
{
#ifdef _MSC_VER
    size_t i, j;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD prevVal = 7;

    std::printf("i\\j|");
    for (i = 0; i < 16; i++)
    {
        std::printf("%3d|",i);
    }
    std::printf("\n---+");
    for (i = 0; i < 16; i++)
    {
        std::printf("---+");
    }
    std::printf("\n");
    for (i = 0; i < 16; i++)
    {
        SetConsoleTextAttribute(hConsole, 7);
        std::printf("%2d |", i);
        for (j = 0; j < 16; j++)
        {
            WORD val = static_cast<WORD>((j * 16) + i);
            SetConsoleTextAttribute(hConsole, val);
            std::printf("%3d", val);
            SetConsoleTextAttribute(hConsole, 7);
            std::printf("|");
        }
        std::printf("\n");
    }
    std::printf("---+");
    for (i = 0; i < 16; i++)
    {
        std::printf("---+");
    }
    std::printf("\n");

    SetConsoleTextAttribute(hConsole, prevVal); // back to default
#endif
}

std::ostream& winCol(WORD fore, WORD back, std::string text, std::ostream& os, bool restore /*= true*/)
{
    fore = fore % 16;
    back = back % 16;
    WORD val = (back * 16) + fore;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, val);
    os << text;
    if (restore)
        SetConsoleTextAttribute(hConsole, 7);

    return os;
}
