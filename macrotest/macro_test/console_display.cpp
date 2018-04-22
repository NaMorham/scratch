#include "mcs_logger.h"
#include "console_display.h"

#include <iostream>


ConsoleDisplay::ColLookup_t lookup[ConsoleDisplay::NUM_TOTAL_COLOURS] = {
    // STD colours
    ConsoleDisplay::ColLookup_t(ConsoleDisplay::NO_COL, ConsoleDisplay::NO_COL),  // None
    ConsoleDisplay::ColLookup_t(30, 0),  // eBlack
    ConsoleDisplay::ColLookup_t(31, 4),  // eRed
    ConsoleDisplay::ColLookup_t(32, 2),  // eGreen
    ConsoleDisplay::ColLookup_t(33, 6),  // eYellow
    ConsoleDisplay::ColLookup_t(34, 1),  // eBlue
    ConsoleDisplay::ColLookup_t(35, 5),  // eMagenta
    ConsoleDisplay::ColLookup_t(36, 3),  // eCyan
    ConsoleDisplay::ColLookup_t(37, 7),  // eWhite
    // BOLD colours
    ConsoleDisplay::ColLookup_t(90, 8),  // eB_Black
    ConsoleDisplay::ColLookup_t(91, 12), // eB_Red
    ConsoleDisplay::ColLookup_t(92, 10), // eB_Green
    ConsoleDisplay::ColLookup_t(93, 14), // eB_Yellow
    ConsoleDisplay::ColLookup_t(94, 9),  // eB_Blue
    ConsoleDisplay::ColLookup_t(95, 13), // eB_Magenta
    ConsoleDisplay::ColLookup_t(96, 11), // eB_Cyan
    ConsoleDisplay::ColLookup_t(97, 15)  // eB_White
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
    
    return std::string((col > eB_White) || (col < eNone) ? "Unk" : colStr[col]);
}

uint32_t ConsoleDisplay::GetColValue(eColours col, bool isWin /*= ms_isWindowsConsole*/)
{
    uint32_t result;
    if ((col == ConsoleDisplay::eNone) || (col > eB_White))
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
//    uint32_t fore /*= ConsoleDisplay::eNone*/, uint32_t back /*= ConsoleDisplay::eNone*/, bool isWin /*= ms_isWindowsConsole*/)
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
    ms_usingANSI = true;
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

const char* ConsoleDisplay::AnsiVals::_on_NRM = "\033[0m";
const char* ConsoleDisplay::AnsiVals::_on_BLD = "\033[1m";
const char* ConsoleDisplay::AnsiVals::_on_BLK = "\033[30m";
const char* ConsoleDisplay::AnsiVals::_on_RED = "\033[31m";
const char* ConsoleDisplay::AnsiVals::_on_GRN = "\033[32m";
const char* ConsoleDisplay::AnsiVals::_on_YRL = "\033[33m";
const char* ConsoleDisplay::AnsiVals::_on_BLU = "\033[34m";
const char* ConsoleDisplay::AnsiVals::_on_MAG = "\033[35m";
const char* ConsoleDisplay::AnsiVals::_on_CYN = "\033[36m";
const char* ConsoleDisplay::AnsiVals::_on_WHT = "\033[37m";

const char* ConsoleDisplay::AnsiVals::_off_NRM = "";
const char* ConsoleDisplay::AnsiVals::_off_BLD = "";
const char* ConsoleDisplay::AnsiVals::_off_BLK = "";
const char* ConsoleDisplay::AnsiVals::_off_RED = "";
const char* ConsoleDisplay::AnsiVals::_off_GRN = "";
const char* ConsoleDisplay::AnsiVals::_off_YRL = "";
const char* ConsoleDisplay::AnsiVals::_off_BLU = "";
const char* ConsoleDisplay::AnsiVals::_off_MAG = "";
const char* ConsoleDisplay::AnsiVals::_off_CYN = "";
const char* ConsoleDisplay::AnsiVals::_off_WHT = "";

const char* ConsoleDisplay::AnsiVals::NRM = "";
const char* ConsoleDisplay::AnsiVals::BLD = "";
const char* ConsoleDisplay::AnsiVals::BLK = "";
const char* ConsoleDisplay::AnsiVals::RED = "";
const char* ConsoleDisplay::AnsiVals::GRN = "";
const char* ConsoleDisplay::AnsiVals::YRL = "";
const char* ConsoleDisplay::AnsiVals::BLU = "";
const char* ConsoleDisplay::AnsiVals::MAG = "";
const char* ConsoleDisplay::AnsiVals::CYN = "";
const char* ConsoleDisplay::AnsiVals::WHT = "";

std::ostream& ConsoleDisplay::allColours(std::ostream& os)
{
#ifdef _WIN32
    std::string fname(std::string("[").append(__FUNCTION__).append("]"));
#else
    std::string fname(std::string("[").append(__func__).append("]"));
#endif
    if (ms_usingColour)
    {
        if (ms_isWindowsConsole)
        {
#ifdef _MSC_VER
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (GetLastError() != ERROR_SUCCESS)
            {
                std::cerr << fname << " Could not get stdout handle" << std::endl;
                ms_isWindowsConsole = false;
                printLastError();
            }
            else
            {
                allColoursWin(hConsole, os);
            }
#endif
        }
        else
        {
            // not a windows console
            allColoursAnsi(os);
        }
    }
    return os;
}

std::ostream& ConsoleDisplay::allColoursWin(HANDLE hCurConsole, std::ostream& os)
{
    if (hCurConsole != INVALID_HANDLE_VALUE)
    {
        int i, j;
        WORD prevVal = 7;

        os << std::endl << "i\\j|";
        for (i = 0; i < 16; i++)
        {
            os << std::setw(3) << i << "|";
        }
        os << std::endl << "---+";
        for (i = 0; i < 16; i++)
        {
            os << "---+";
        }
        os << std::endl;
        for (i = 0; i < 16; i++)
        {
#ifdef _MSC_VER
            SetConsoleTextAttribute(hCurConsole, 7);
            printLastError();
#endif
            os << std::setw(2) << i << "|";
            for (j = 0; j < 16; j++)
            {
                WORD val = static_cast<WORD>((j * 16) + i);
#ifdef _MSC_VER
                SetConsoleTextAttribute(hCurConsole, val);
                printLastError();
#endif
                os << std::setw(3) << val;
#ifdef _MSC_VER
                SetConsoleTextAttribute(hCurConsole, 7);
                printLastError();
#endif
                os << "|";
            }
            os << std::endl;
        }
        os << "---+";
        for (i = 0; i < 16; i++)
        {
            os << "---+";
        }
        os << std::endl;

#ifdef _MSC_VER
        SetConsoleTextAttribute(hCurConsole, prevVal); // back to default
        printLastError();
#endif
    }
    return os;
}

std::ostream& ConsoleDisplay::allColoursAnsi(std::ostream& os)
{
    int i, j;

    if (os.good())
    {
        os << std::endl << "i\\j|";
        for (i = 0; i < 16; i++)
        {
            os << " " << std::setw(3) << i + (i >= 8 ? 92 : 40);
        }
        os << std::endl;

        os << "---+";
        for (i = 0; i < 16; i++)  // for each column
        {
            os << "------+";
        }
        os << std::endl;

        for (i = 0; i < 16; i++)
        {
            os << std::setw(2) << i + (i >= 8 ? 82 : 30) << " |";
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

                os << "\033[" << f << "m\033[" << b << "m" << std::setw(2) << f << ";" <<
                    std::left << std::setw(3) << b << "\033[0m|";
            }
            os << std::endl;
        }

        os << "---+";
        for (i = 0; i < 16; i++)  // for each column
        {
            os << "------+";
        }
        os << std::endl;
    }
    return os;
}

// Draw coloured text on a Windows CMD console
std::ostream& ConsoleDisplay::winCol(eColours  fore, eColours  back, std::string text, std::ostream& os,
    HANDLE hCurConsole, bool restore /*= true*/)
{
#ifdef _MSC_VER
    std::string fname("[" __FUNCTION__ "]");
    if (ms_isWindowsConsole && ms_usingColour && (hCurConsole != INVALID_HANDLE_VALUE))
    {
        WORD curAttr = getCurAttribs(hCurConsole);
        uint32_t b(GetBGColValue(back, true));
        uint32_t f(GetColValue(fore, true));
        WORD val = 0;
        if (f != NO_COL)
        {
            val += static_cast<WORD>(f);
        }
        else
        {
            val += (curAttr % 16);
        }
        if (b != NO_COL)
        {
            val += static_cast<WORD>(b);
        }
        else
        {
            val += curAttr - (curAttr % 16);
        }
        SetConsoleTextAttribute(hCurConsole, val);
    }
#endif
    os << text;
#ifdef _MSC_VER
    if (restore)
    {
        resetWin(os, hCurConsole);
    }
#endif

    return os;
}

// Draw coloured text on a console supporting ANSI colours
std::ostream& ConsoleDisplay::ansiCol(eColours fore, eColours back, std::string text, std::ostream& os, bool restore /*= true*/)
{
#ifdef _MSC_VER
    std::string fname("[" __FUNCTION__ "]");
#else
    std::string fname(std::string("[").append(__func__).append("]"));
#endif

    uint32_t f(GetColValue(fore, false));
    uint32_t b(GetBGColValue(back, false));

    if (ms_usingColour && ms_usingANSI)
    {
        if (f != NO_COL)
        {
            os << "\033[" << f << "m";
        }
        if (b != NO_COL)
        {
            os << "\033[" << b << "m";
        }
    }
    os << text;
    if (restore && ms_usingColour && ms_usingANSI)
    {
        reset(os);
    }
    return os;
}

std::ostream& ConsoleDisplay::colText(eColours  fore, std::string text, std::ostream& os,
    bool restore /*= true*/, bool isWin /*= ms_isWindowsConsole*/)
{
    return colText(fore, eNone, text, os, restore, isWin);
}

std::ostream& ConsoleDisplay::colText(eColours  fore, eColours  back, std::string text, std::ostream& os,
    bool restore /*= true*/, bool isWin /*= ms_isWindowsConsole*/)
{
    //std::cerr << "[" << __FUNCTION__ << "] -> fore [" << fore << ": " << ColourStr(fore) << 
    //    "], back [" << back << ": " << ColourStr(back) << "]" << std::endl;
 
    if (isWin)
    {
        return winCol(fore, back, text, os, getStdHandle(os), restore);
    }
    else
    {
        return ansiCol(fore, back, text, os, restore);
    }

}

template<typename T>
std::ostream& ConsoleDisplay::colText(eColours fore, const T& val, std::ostream& os,
    bool restore /*= true*/, bool isWin /*= ms_isWindowsConsole*/)
{
    std::stringstream ss;
    ss << val;
    return colText(fore, ss.str(), os, restore, isWin);
}

template<typename T>
std::ostream& ConsoleDisplay::colText(eColours fore, eColours back, const T& val, std::ostream& os,
    bool restore /*= true*/, bool isWin /*= ms_isWindowsConsole*/)
{
    std::stringstream ss;
    ss << val;
    return colText(fore, back, ss.str(), os, restore, isWin);
}

std::ostream& ConsoleDisplay::setFore(eColours fore, std::ostream& os, bool isWin /*= ms_isWindowsConsole*/)
{
    if (isWin)
    {
        winSetFore(fore, os);
    }
    else
    {
        ansiSetFore(fore, os);
    }
    return os;
}

std::ostream& ConsoleDisplay::setBack(eColours back, std::ostream& os, bool isWin /*= ms_isWindowsConsole*/)
{
    if (isWin)
    {
        winSetBack(back, os);
    }
    else
    {
        ansiSetBack(back, os);
    }
    return os;
}

std::ostream& ConsoleDisplay::reset(std::ostream& os, bool isWin /*= ConsoleDisplay::ms_isWindowsConsole*/)
{
    if (isWin)
    {
#ifdef _MSC_VER
        HANDLE hConsole = getStdHandle(os);

        if (hConsole != INVALID_HANDLE_VALUE)
        {
            SetConsoleTextAttribute(hConsole, ms_defaultAttr);
        }
#endif
    }
    else
    {
        if (ms_usingANSI)
        {
            os << AnsiVals::_on_NRM;
        }
    }
    return os;
}

void ConsoleDisplay::printLastError(uint32_t err)
{
    if (err != ERROR_SUCCESS)
    {
        std::cerr << GetLastErrorText(err) << std::endl;
    }
}

std::string ConsoleDisplay::GetLastErrorText(uint32_t err)
{
    // use @err,hr in the debugger
    std::string msg;
#ifdef _MSC_VER

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
    //msg.assign("Error:").append(std::to_string(err)); 
#else
    msg.assign("Error:").append(std::to_string(err));
#endif

    return msg;
}

std::string ConsoleDisplay::getEnvVar(std::string var)
{
    std::string env("");

#ifdef _MSC_VER
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
#else
    env = std::string(getenv(var.c_str()));
#endif

    return env;
}

HANDLE ConsoleDisplay::getStdHandle(std::ostream& os)
{
    HANDLE hStd = INVALID_HANDLE_VALUE;
#ifdef _MSC_VER
    if (os.rdbuf() == std::cout.rdbuf())
    {
        hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    else if (os.rdbuf() == std::cerr.rdbuf())
    {
        hStd = GetStdHandle(STD_ERROR_HANDLE);
    }

    if (GetLastError() != ERROR_SUCCESS)
    {
        printLastError();
        hStd = INVALID_HANDLE_VALUE;
    }
#endif
    return hStd;
}

WORD ConsoleDisplay::getCurAttribs(HANDLE hConsole)
{
#ifdef _MSC_VER
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    if ((hConsole != INVALID_HANDLE_VALUE) && GetConsoleScreenBufferInfo(hConsole, &csbiInfo))
    {
        return csbiInfo.wAttributes;
    }
    else
    {
        return 7;  // black background with light grey text
    }
#else
    return 0;
#endif
}

void ConsoleDisplay::InitDefaultAttr()
{
#ifdef _MSC_VER
    if (ms_isWindowsConsole)
    {
        ms_defaultAttr = getCurAttribs(GetStdHandle(STD_OUTPUT_HANDLE));
        printLastError();
    }
    else
    {
        ms_defaultAttr = 7;  // black background with lt grey text
    }
#else
    ms_defaultAttr = 0;  // black on black, but not used
#endif

    if (ms_usingColour)
    {
        AnsiVals::NRM = AnsiVals::_on_NRM;
        AnsiVals::BLD = AnsiVals::_on_BLD;
        AnsiVals::BLK = AnsiVals::_on_BLK;
        AnsiVals::RED = AnsiVals::_on_RED;
        AnsiVals::GRN = AnsiVals::_on_GRN;
        AnsiVals::YRL = AnsiVals::_on_YRL;
        AnsiVals::BLU = AnsiVals::_on_BLU;
        AnsiVals::MAG = AnsiVals::_on_MAG;
        AnsiVals::CYN = AnsiVals::_on_CYN;
        AnsiVals::WHT = AnsiVals::_on_WHT;
    }
    else
    {
        AnsiVals::NRM = AnsiVals::_off_NRM;
        AnsiVals::BLD = AnsiVals::_off_BLD;
        AnsiVals::BLK = AnsiVals::_off_BLK;
        AnsiVals::RED = AnsiVals::_off_RED;
        AnsiVals::GRN = AnsiVals::_off_GRN;
        AnsiVals::YRL = AnsiVals::_off_YRL;
        AnsiVals::BLU = AnsiVals::_off_BLU;
        AnsiVals::MAG = AnsiVals::_off_MAG;
        AnsiVals::CYN = AnsiVals::_off_CYN;
        AnsiVals::WHT = AnsiVals::_off_WHT;
    }
}

std::ostream& ConsoleDisplay::resetWin(std::ostream& os, HANDLE hCurConsole)
{
    if (ms_usingColour)
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
        else
        {
            reset(os, false); // try ansi
        }
#endif
    }
    return os;
}

std::ostream& ConsoleDisplay::ansiSetFore(eColours fore, std::ostream& os)
{
    if (ms_usingColour && ms_usingANSI && (fore != eNone))
    {
        uint32_t f(GetColValue(fore, false));

        if (f != NO_COL)
        {
            os << "\033[" << f << "m";
        }
    }
    return os;
}
std::ostream& ConsoleDisplay::ansiSetBack(eColours back, std::ostream& os)
{
    if (ms_usingColour && ms_usingANSI && (back != eNone))
    {
        uint32_t b(GetBGColValue(back, false));

        if (b != NO_COL)
        {
            os << "\033[" << b << "m";
        }
    }
    return os;
}

std::ostream& ConsoleDisplay::winSetFore(eColours fore, std::ostream& os)
{
#ifdef _MSC_VER
    return winSetFore(fore, os, getStdHandle(os));
#else
    return os;
#endif
}
std::ostream& ConsoleDisplay::winSetBack(eColours back, std::ostream& os)
{
#ifdef _MSC_VER
    return winSetBack(back, os, getStdHandle(os));
#else
    return os;
#endif
}

#ifdef _MSC_VER
std::ostream& ConsoleDisplay::winSetFore(eColours fore, std::ostream& os, HANDLE hCurConsole)
{
    if (ms_isWindowsConsole && ms_usingColour && (hCurConsole != INVALID_HANDLE_VALUE))
    {
        WORD curAttr = getCurAttribs(hCurConsole);
        uint32_t f(GetColValue(fore, true));
        WORD val = 0;
        if (f != NO_COL)
        {
            val += static_cast<WORD>(f);
            val += curAttr - (curAttr % 16);
            SetConsoleTextAttribute(hCurConsole, val);
        }
    }
    return os;
}
std::ostream& ConsoleDisplay::winSetBack(eColours back, std::ostream& os, HANDLE hCurConsole)
{
    if (ms_isWindowsConsole && ms_usingColour && (hCurConsole != INVALID_HANDLE_VALUE))
    {
        WORD curAttr = getCurAttribs(hCurConsole);
        uint32_t b(GetBGColValue(back, true));
        WORD val = 0;
        if (b != NO_COL)
        {
            val += (curAttr % 16);
            val += static_cast<WORD>(b);
            SetConsoleTextAttribute(hCurConsole, val);
        }
    }
    return os;
}
#endif

WORD ConsoleDisplay::ms_defaultAttr = 0;

std::ostream& operator<<(std::ostream& os, const ConsoleDisplay::ColObjBase& obj)
{
    ConsoleDisplay::colText(obj.col(), obj.text(), os, true);
    return os;
}
