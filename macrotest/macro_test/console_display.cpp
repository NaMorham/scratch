#include "console_display.h"

//#include <sstream>
#include <iostream>

ConsoleDisplay::ConsoleDisplay()
{
    std::cerr << "Created ConsoleDisplay" << std::endl;
#ifdef _MSC_VER
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //ms_isWindowsConsole = (INVALID_HANDLE_VALUE == hConsole);
    if (getEnvVar("SHELL").empty())
    {
        ms_usingANSI = false;
        ms_isWindowsConsole = true;
    }
    else
    {
        ms_usingANSI = true;
        ms_isWindowsConsole = false;
    }
#else
    ms_isWindowsConsole = false;
#endif
    ms_usingColour = true;

    std::cerr << "usingColour [" << std::to_string(ms_usingColour) << "], usingANSI [" << std::to_string(ms_usingANSI) << "], isWindowsConsole [" << std::to_string(ms_isWindowsConsole) << "]" << std::endl;
}


ConsoleDisplay::~ConsoleDisplay()
{
    std::cerr << "Destroyed ConsoleDisplay" << std::endl;
}

/*
PConsoleDisplay ConsoleDisplay::get()
{
    if (ms_pConsole == nullptr)
    {
        ms_pConsole = std::make_shared<ConsoleDisplay*>();
    }
    return ms_pConsole;
}

PConsoleDisplay ConsoleDisplay::ms_pConsole = nullptr;
/*/
ConsoleDisplay& ConsoleDisplay::get()
{
    static ConsoleDisplay theConsole;
    return theConsole;
}
//*/

bool ConsoleDisplay::ms_usingColour = true;
bool ConsoleDisplay::ms_usingANSI = false;
bool ConsoleDisplay::ms_isWindowsConsole = false;

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


void ConsoleDisplay::allColours()
{
    if (ms_usingColour)
    {
        if (ms_isWindowsConsole)
        {
#ifdef _MSC_VER
            size_t i, j;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (GetLastError() == ERROR_INVALID_HANDLE)
            {
                std::cerr << "Could not get stdout handle" << std::endl;
                ms_isWindowsConsole = false;
                return;
            }
            printLastError();
            WORD prevVal = 7;

            std::printf("i\\j|");
            for (i = 0; i < 16; i++)
            {
                std::printf("%3d|", i);
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
                printLastError();
                std::printf("%2d |", i);
                for (j = 0; j < 16; j++)
                {
                    WORD val = static_cast<WORD>((j * 16) + i);
                    SetConsoleTextAttribute(hConsole, val);
                    printLastError();
                    std::printf("%3d", val);
                    SetConsoleTextAttribute(hConsole, 7);
                    printLastError();
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
            printLastError();
#endif
        }
        else
        {
            // not a windows console
            size_t i, j;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (GetLastError() == ERROR_INVALID_HANDLE)
            {
                std::cerr << "Could not get stdout handle" << std::endl;
                ms_isWindowsConsole = false;
                return;
            }
            printLastError();
            WORD prevVal = 7;

            std::printf("i\\j|");
            for (i = 0; i < 16; i++)
            {
                std::printf("%3d|", i);
            }
            std::printf("\n---+");
            for (i = 0; i < 16; i++)
            {
                std::printf("---+");
            }
            std::printf("\n");
            for (i = 0; i < 16; i++)
            {
                std::printf("%2d |", i);
                for (j = 0; j < 16; j++)
                {
                    WORD val = static_cast<WORD>((j * 16) + i);
                    std::printf("%3d", val);
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
        }
    }
}

std::ostream& ConsoleDisplay::winCol(WORD fore, WORD back, std::string text, std::ostream& os, bool restore /*= true*/)
{
#ifdef _MSC_VER
    HANDLE hConsole = INVALID_HANDLE_VALUE;
    if (ms_isWindowsConsole && ms_usingColour)
    {
        fore = fore % 16;
        back = back % 16;
        WORD val = (back * 16) + fore;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, val);
    }
#endif
    os << text;
#ifdef _MSC_VER
    if (restore && ms_isWindowsConsole && ms_usingColour && (hConsole != INVALID_HANDLE_VALUE))
    {
        SetConsoleTextAttribute(hConsole, 7);
    }
#endif

    return os;
}

#include <iostream>
void ConsoleDisplay::printLastError()
{
    uint32_t err = GetLastError();
    if (err != 0)
    {
        std::cerr << GetLastErrorText(err) << std::endl;
    }
}

std::string ConsoleDisplay::GetLastErrorText(uint32_t err)
{
    // use @err,hr in the debugger
#ifdef _MSC_VER
    std::string msg;

    LPVOID lpMsgBuf = nullptr;
    DWORD dw = static_cast<DWORD>(err);

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&lpMsgBuf,
        0, NULL);

    // Display the error message and exit the process
    msg.assign(reinterpret_cast<const char*>(lpMsgBuf));

    LocalFree(lpMsgBuf);
#else
    msg.assign("Error:").append(std::to_string(err));
#endif

    return msg;
}

std::string ConsoleDisplay::getEnvVar(std::string var)
{
    std::string env("");

    char* envVar = nullptr;
    size_t requiredSize = 0;

    if (!var.empty())
    {
        try
        {
            getenv_s(&requiredSize, NULL, 0, var.c_str());
            if (requiredSize == 0)
            {
                std::cerr << "Environmanet var [" << var.c_str() << "] doesn't exist!" << std::endl;
                return env;
            }

            envVar = (char*)malloc(requiredSize * sizeof(char));
            if (!envVar)
            {
                std::cerr << "Failed to allocate memory [" << (requiredSize * sizeof(char)) << "] bytes" << std::endl;
                return env;
            }

            // Get the value of the LIB environment variable.  
            getenv_s(&requiredSize, envVar, requiredSize, var.c_str());

            env.assign(envVar ? envVar : "");

            if (envVar)
            {
                free(envVar);
            }
            envVar = nullptr;
            return env;
        }
        catch (std::exception &e)
        {
            std::cerr << "Recieved exception [" << e.what() << "]" << std::endl;
            if (envVar)
            {
                free(envVar);
            }
            envVar = nullptr;
            return std::string("");
        }
    }
    return envVar;
}
