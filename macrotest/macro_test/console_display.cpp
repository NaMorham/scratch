#include "console_display.h"

//#include <sstream>
#include <iostream>



ConsoleDisplay::ColLookup_t lookup[ConsoleDisplay::NUM_TOTAL_COLOURS] = {
    // STD colours
    ConsoleDisplay::ColLookup_t(ConsoleDisplay::NO_COL, ConsoleDisplay::NO_COL),  // None
    ConsoleDisplay::ColLookup_t(30, 0),  // Black
    ConsoleDisplay::ColLookup_t(31, 4),  // Red
    ConsoleDisplay::ColLookup_t(32, 2),  // Green
    ConsoleDisplay::ColLookup_t(33, 6),  // Yellow
    ConsoleDisplay::ColLookup_t(34, 1),  // Blue
    ConsoleDisplay::ColLookup_t(35, 5),  // Magenta
    ConsoleDisplay::ColLookup_t(36, 3),  // Cyan
    ConsoleDisplay::ColLookup_t(37, 7),  // White
    // BOLD colours
    ConsoleDisplay::ColLookup_t(40, 8),  // B_Black
    ConsoleDisplay::ColLookup_t(41, 12), // B_Red
    ConsoleDisplay::ColLookup_t(42, 10), // B_Green
    ConsoleDisplay::ColLookup_t(43, 14), // B_Yellow
    ConsoleDisplay::ColLookup_t(44, 9),  // B_Blue
    ConsoleDisplay::ColLookup_t(45, 13), // B_Magenta
    ConsoleDisplay::ColLookup_t(46, 11), // B_Cyan
    ConsoleDisplay::ColLookup_t(47, 15)  // B_White
};

std::string ConsoleDisplay::ColourStr(eColours col)
{
    static std::string colStr[] = {
        "None",
        "Black",
        "Red",
        "Green",
        "Yellow",
        "Blue",
        "Magenta",
        "Cyan",
        "White",

        "Bold Black",
        "Bold Red",
        "Bold Green",
        "Bold Yellow",
        "Bold Blue",
        "Bold Magenta",
        "Bold Cyan",
        "Bold White"
    };
    
    return std::string((col > B_White) || (col < None) ? "Unk" : colStr[col]);
}

uint32_t ConsoleDisplay::GetColValue(eColours col, bool isWin /*= ms_isWindowsConsole*/)
{
    uint32_t result;
    if ((col == ConsoleDisplay::None) || (col > B_White))
    {
        result = NO_COL;
    }
    else
    {
        result = (isWin ? lookup[col].win : lookup[col].ansi);
    }
    return result;
}

uint32_t ConsoleDisplay::GetBGColValue(eColours col, bool isWin /*= ms_isWindowsConsole*/)
{
    uint32_t result(GetColValue(col, isWin));
    return (result == NO_COL ? result : (isWin ? result * 16 : result + 10));
}

//std::ostream& ConsoleDisplay::colText(std::string text, std::ostream& os,
//    uint32_t fore /*= ConsoleDisplay::None*/, uint32_t back /*= ConsoleDisplay::None*/, bool isWin /*= ms_isWindowsConsole*/)
//{
//    if (isWin)
//    {
//        HANDLE hStd = getStdHandle(os);
//        if (ms_usingColour && (hStd != INVALID_HANDLE_VALUE))
//        {
//        }
//        os << text;
//        if (ms_usingColour && (hStd != INVALID_HANDLE_VALUE))
//        {
//        }
//    }
//    else
//    {
//        os << text;
//    }
//    return os;
//}

ConsoleDisplay::ConsoleDisplay()
{
    std::cerr << "[ConsoleDisplay] Created" << std::endl;
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

    InitDefaultAttr();

    std::cerr << "[ConsoleDisplay] usingColour [" << std::to_string(ms_usingColour) << "], usingANSI [" << std::to_string(ms_usingANSI) << "], isWindowsConsole [" << std::to_string(ms_isWindowsConsole) << "]" << std::endl;
}


ConsoleDisplay::~ConsoleDisplay()
{
    std::cerr << "[ConsoleDisplay] Destroyed ConsoleDisplay" << std::endl;
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

const char* ConsoleDisplay::NRM = "";
const char* ConsoleDisplay::BLD = "";
const char* ConsoleDisplay::BLK = "";
const char* ConsoleDisplay::RED = "";
const char* ConsoleDisplay::GRN = "";
const char* ConsoleDisplay::YRL = "";
const char* ConsoleDisplay::BLU = "";
const char* ConsoleDisplay::MAG = "";
const char* ConsoleDisplay::CYN = "";
const char* ConsoleDisplay::WHT = "";

void ConsoleDisplay::allColours()
{
    std::string fname("[" __FUNCTION__ "]");
    if (ms_usingColour)
    {
        if (ms_isWindowsConsole)
        {
            //std::cerr << fname << " Render as a windows console" << std::endl;
#ifdef _MSC_VER
            int i, j;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (GetLastError() == ERROR_INVALID_HANDLE)
            {
                std::cerr << fname << " Could not get stdout handle" << std::endl;
                ms_isWindowsConsole = false;
                return;
            }
            printLastError();
            WORD prevVal = 7;

            std::printf("\ni\\j|");
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
            std::cerr << fname << " Render as a non-windows console" << std::endl;
            int i, j;

            std::printf("\ni\\j|");
            for (i = 0; i < 16; i++)
            {
                std::printf(" %3d  |", i + (i >= 8 ? 92 : 40));
            }
            std::printf("\n---+");
            for (i = 0; i < 16; i++)
            {
                std::printf("------+");
            }
            std::printf("\n");
            for (i = 0; i < 16; i++)
            {
                std::printf("%2d |", i + (i >= 8 ? 82 : 30));
                for (j = 0; j < 16; j++)
                {
                    int f((i % 8) + 30);
                    int b((j % 8) + 40);
                    if (i >= 8)
                    {
                        f += 60;
                    }
                    if (j >= 8)
                    {
                        b += 60;
                    }
                    //int val = ((j * 16) + i);
                    std::printf("\033[%d;%dm%2d;%-3d\033[0m|", f, b, f, b);
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

std::ostream& ConsoleDisplay::winCol(eColours  fore, eColours  back, std::string text, std::ostream& os, bool restore /*= true*/)
{
    std::string fname("[" __FUNCTION__ "]");
#ifdef _MSC_VER
    HANDLE hConsole = INVALID_HANDLE_VALUE;
    if (ms_isWindowsConsole && ms_usingColour)
    {
        uint32_t f(GetColValue(fore, true));
        uint32_t b(GetBGColValue(back, true));
        //std::cerr << fname << " -> fore [" << f << "], back [" << b << "]" << std::endl;
        WORD val = 0;
        if (f != NO_COL)
        {
            val += static_cast<WORD>(f);
        }
        if (b != NO_COL)
        {
            val += static_cast<WORD>(b);
        }
        //std::cerr << fname << " -> attribVal [" << val << "]" << std::endl;
        hConsole = getStdHandle(os);
        if (hConsole != INVALID_HANDLE_VALUE)
        {
            SetConsoleTextAttribute(hConsole, val);
        }
    }
#endif
    os << text;
#ifdef _MSC_VER
    if (restore)// && ms_isWindowsConsole && ms_usingColour && (hConsole != INVALID_HANDLE_VALUE))
    {
        //SetConsoleTextAttribute(hConsole, ms_defaultAttr);
        reset(os);
    }
#endif

    return os;
}

std::ostream& ConsoleDisplay::ansiCol(eColours fore, eColours back, std::string text, std::ostream& os, bool restore /*= true*/)
{
    std::string fname("[" __FUNCTION__ "]");

    uint32_t f(GetColValue(fore, false));
    uint32_t b(GetBGColValue(back, false));

    //std::cerr << fname << " - f [], b []" << std::endl;
    if (ms_usingColour && ms_usingANSI)
    {
        if (f != NO_COL)
        {
            os << std::string("\033[").append(std::to_string(f)).append("m");
        }
        if (b != NO_COL)
        {
            os << std::string("\033[").append(std::to_string(b)).append("m");
        }
    }
    os << text;
    if (restore && ms_usingColour && ms_usingANSI)
    {
        reset(os);
    }
    return os;
}

std::ostream& ConsoleDisplay::colText(eColours  fore, eColours  back, std::string text, std::ostream& os,
    bool restore /*= true*/, bool isWin /*= ms_isWindowsConsole*/)
{
    //std::cerr << "[" << __FUNCTION__ << "] -> fore [" << fore << ": " << ColourStr(fore) << 
    //    "], back [" << back << ": " << ColourStr(back) << "]" << std::endl;
 
    if (isWin)
    {
        return winCol(fore, back, text, os, restore);
    }
    else
    {
        return ansiCol(fore, back, text, os, restore);
    }

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
                std::cerr << "Environment var [" << var.c_str() << "] doesn't exist!" << std::endl;
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

HANDLE ConsoleDisplay::getStdHandle(std::ostream& os)
{
    HANDLE hStd = INVALID_HANDLE_VALUE;

    if (os.rdbuf() == std::cout.rdbuf())
    {
        hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    else if (os.rdbuf() == std::cerr.rdbuf())
    {
        hStd = GetStdHandle(STD_ERROR_HANDLE);
    }

    return hStd;
}

void ConsoleDisplay::InitDefaultAttr()
{
#ifdef _MSC_VER
    if (ms_isWindowsConsole)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

        if (hStdout == INVALID_HANDLE_VALUE)
        {
            return;
        }

        if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
        {
            return;
        }

        ms_defaultAttr = csbiInfo.wAttributes;
    }
    else
    {
        ms_defaultAttr = 7;
    }
#else
    ms_defaultAttr = 0;
#endif

    if (ms_usingColour)
    {
        ConsoleDisplay::NRM = _on_NRM;
        ConsoleDisplay::BLD = _on_BLD;
        ConsoleDisplay::BLK = _on_BLK;
        ConsoleDisplay::RED = _on_RED;
        ConsoleDisplay::GRN = _on_GRN;
        ConsoleDisplay::YRL = _on_YRL;
        ConsoleDisplay::BLU = _on_BLU;
        ConsoleDisplay::MAG = _on_MAG;
        ConsoleDisplay::CYN = _on_CYN;
        ConsoleDisplay::WHT = _on_WHT;
    }
    else
    {
        ConsoleDisplay::NRM = _off_NRM;
        ConsoleDisplay::BLD = _off_BLD;
        ConsoleDisplay::BLK = _off_BLK;
        ConsoleDisplay::RED = _off_RED;
        ConsoleDisplay::GRN = _off_GRN;
        ConsoleDisplay::YRL = _off_YRL;
        ConsoleDisplay::BLU = _off_BLU;
        ConsoleDisplay::MAG = _off_MAG;
        ConsoleDisplay::CYN = _off_CYN;
        ConsoleDisplay::WHT = _off_WHT;
    }
}

std::ostream& ConsoleDisplay::reset(std::ostream& os, bool isWin /*= ConsoleDisplay::ms_isWindowsConsole*/)
{
    if (isWin)
    {
#ifdef _MSC_VER
        if (ms_isWindowsConsole)
        {
            HANDLE hConsole = getStdHandle(os);

            if (hConsole != INVALID_HANDLE_VALUE)
            {
                SetConsoleTextAttribute(hConsole, ms_defaultAttr);
            }
        }
#endif
    }
    else
    {
        if (ms_usingANSI)
        {
            os << _on_NRM;
        }
    }
    return os;
}

WORD ConsoleDisplay::ms_defaultAttr = 0;
