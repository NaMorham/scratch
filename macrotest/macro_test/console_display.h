#pragma once
#include <memory>
#include <string>

#ifdef _MSC_VER
#include <Windows.h>
#endif

//#ifndef HANDLE
//#define HANDLE uint32_t
//#endif

class ConsoleDisplay;

//typedef std::shared_ptr<ConsoleDisplay> PConsoleDisplay;

class ConsoleDisplay
{
public:
    enum eColours
    {
        None = 0,
        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,

        NUM_COLOURS,

        B_Black = NUM_COLOURS,
        B_Red,
        B_Green,
        B_Yellow,
        B_Blue,
        B_Magenta,
        B_Cyan,
        B_White,

        NUM_TOTAL_COLOURS
    };

    struct ColLookup_t
    {
        ColLookup_t(uint32_t a, uint32_t  w) : ansi(a), win(w) {}
        union
        {
            uint32_t vals[2];
            struct { uint32_t ansi, win; };
        };
    };

    static const uint32_t NO_COL = static_cast<uint32_t>(-1);

    inline static bool isBold(eColours val) { return (val >= B_Black); }

    static std::string ColourStr(eColours col);

    static uint32_t GetColValue(eColours col, bool isWin = ms_isWindowsConsole);

    static uint32_t GetBGColValue(eColours col, bool isWin = ms_isWindowsConsole);

    //static std::ostream& colText(std::string text, std::ostream& os,
        //uint32_t fore = None, uint32_t back = None, bool isWin = ms_isWindowsConsole);

    static ConsoleDisplay& get();

    static void allColours();

    static std::ostream& colText(eColours fore, eColours back, std::string text, std::ostream& os,
        bool restore = true, bool isWin = ms_isWindowsConsole);

    static void printLastError();

    static std::string GetLastErrorText(uint32_t err);

    static std::string getEnvVar(std::string var);

    static bool isWindowsConsole() { return ms_isWindowsConsole; }
    static bool usingColour() { return ms_usingColour; }
    static bool usingansi() { return ms_usingANSI; }

    static const char *NRM;
    static const char *BLD;
    static const char *BLK;
    static const char *RED;
    static const char *GRN;
    static const char *YRL;
    static const char *BLU;
    static const char *MAG;
    static const char *CYN;
    static const char *WHT;

    static const char* _on_NRM;
    static const char* _on_BLD;
    static const char* _on_BLK;
    static const char* _on_RED;
    static const char* _on_GRN;
    static const char* _on_YRL;
    static const char* _on_BLU;
    static const char* _on_MAG;
    static const char* _on_CYN;
    static const char* _on_WHT;

    static const char* _off_NRM;
    static const char* _off_BLD;
    static const char* _off_BLK;
    static const char* _off_RED;
    static const char* _off_GRN;
    static const char* _off_YRL;
    static const char* _off_BLU;
    static const char* _off_MAG;
    static const char* _off_CYN;
    static const char* _off_WHT;

    static std::ostream& reset(std::ostream& os, bool isWin = ms_isWindowsConsole);

private:
    ConsoleDisplay();
    virtual ~ConsoleDisplay();

    ConsoleDisplay(ConsoleDisplay& orig) = delete;
    ConsoleDisplay(ConsoleDisplay&& orig) = delete;
    ConsoleDisplay& operator=(ConsoleDisplay& orig) = delete;
    ConsoleDisplay& operator=(ConsoleDisplay&& orig) = delete;

    static bool ms_usingANSI;
    static bool ms_usingColour;
    static bool ms_isWindowsConsole;

    static HANDLE getStdHandle(std::ostream&os);
    static std::ostream& winCol(eColours fore, eColours back, std::string text, std::ostream& os, bool restore = true);
    static std::ostream& ansiCol(eColours fore, eColours back, std::string text, std::ostream& os, bool restore = true);

    static void InitDefaultAttr();

    static WORD ms_defaultAttr;
};

