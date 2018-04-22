#ifndef __MCS__MACRO_TEST__CONSOLE_DISPLAY_H__
#define __MCS__MACRO_TEST__CONSOLE_DISPLAY_H__ 

#pragma once

#include <memory>
#include <string>
#include <cstdint>

#ifdef _MSC_VER
#include <Windows.h>
#endif

#ifndef _WIN32
#include <errno.h>

inline uint32_t GetLastError() { return errno; }

typedef uint32_t HANDLE;
typedef unsigned short WORD;

const HANDLE INVALID_HANDLE_VALUE = static_cast<HANDLE>(-1);
const uint32_t ERROR_SUCCESS = 0;
#endif

class ConsoleDisplay
{
public:
    enum eColours
    {
        eNone = 0,
        eBlack,
        eRed,
        eGreen,
        eYellow,
        eBlue,
        eMagenta,
        eCyan,
        eWhite,

        NUM_COLOURS,

        eB_Black = NUM_COLOURS,
        eB_Red,
        eB_Green,
        eB_Yellow,
        eB_Blue,
        eB_Magenta,
        eB_Cyan,
        eB_White,

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

    inline static bool isBold(eColours val) { return (val >= eB_Black); }

    static std::string ColourStr(eColours col);

    static uint32_t GetColValue(eColours col, bool isWin = ms_isWindowsConsole);
    static uint32_t GetBGColValue(eColours col, bool isWin = ms_isWindowsConsole);

    //static std::ostream& colText(std::string text, std::ostream& os,
        //uint32_t fore = None, uint32_t back = None, bool isWin = ms_isWindowsConsole);

    static ConsoleDisplay& get();

    static std::ostream& allColours(std::ostream& os);

    static std::ostream& colText(eColours fore, std::string text, std::ostream& os,
        bool restore = true, bool isWin = ms_isWindowsConsole);

    static inline std::ostream& colText(eColours fore, const char* text, std::ostream& os,
        bool restore = true, bool isWin = ms_isWindowsConsole) { return colText(fore, std::string(text), os, restore, isWin); }

    static std::ostream& colText(eColours fore, eColours back, std::string text, std::ostream& os,
        bool restore = true, bool isWin = ms_isWindowsConsole);

    static inline std::ostream& colText(eColours fore, eColours back, const char* text, std::ostream& os,
        bool restore = true, bool isWin = ms_isWindowsConsole) { return colText(fore, back, std::string(text), os, restore, isWin); }

    template<typename T>
    static std::ostream& colText(eColours fore, const T& val, std::ostream& os,
        bool restore = true, bool isWin = ms_isWindowsConsole);

    template<typename T>
    static std::ostream& colText(eColours fore, eColours back, const T& val, std::ostream& os,
        bool restore = true, bool isWin = ms_isWindowsConsole);

    static std::ostream& setFore(eColours fore, std::ostream& os, bool isWin = ms_isWindowsConsole);
    static std::ostream& setBack(eColours fore, std::ostream& os, bool isWin = ms_isWindowsConsole);

    static std::ostream& reset(std::ostream& os, bool isWin = ms_isWindowsConsole);

    inline static void printLastError() { printLastError(GetLastError()); }

    static void printLastError(uint32_t err);

    static std::string GetLastErrorText(uint32_t err);

    static std::string getEnvVar(std::string var);

    static bool isWindowsConsole() { return ms_isWindowsConsole; }
    static bool usingColour() { return ms_usingColour; }
    static bool usingansi() { return ms_usingANSI; }

    class ColObjBase
    {
    public:
        ColObjBase(eColours col, std::string text) : m_col(col), m_text(text) {}
        virtual ~ColObjBase() {}

        friend std::ostream& operator<<(std::ostream& os, const ColObjBase& obj);

        eColours col() const { return m_col; }
        std::string text() const { return m_text; }

    private:
        eColours m_col;
        std::string m_text;
    };

    template<eColours c>
    class ColObj : public ColObjBase
    {
    public:
        ColObj(std::string text) : ColObjBase(c, text) {}
        virtual ~ColObj() {}
    };

    // convienience functors
    typedef ColObj<eBlack>      Black;
    typedef ColObj<eRed>        Red;
    typedef ColObj<eGreen>      Green;
    typedef ColObj<eYellow>     Yellow;
    typedef ColObj<eBlue>       Blue;
    typedef ColObj<eMagenta>    Magenta;
    typedef ColObj<eCyan>       Cyan;
    typedef ColObj<eWhite>      White;
    typedef ColObj<eB_Black>    B_Black;
    typedef ColObj<eB_Red>      B_Red;
    typedef ColObj<eB_Green>    B_Green;
    typedef ColObj<eB_Yellow>   B_Yellow;
    typedef ColObj<eB_Blue>     B_Blue;
    typedef ColObj<eB_Magenta>  B_Magenta;
    typedef ColObj<eB_Cyan>     B_Cyan;
    typedef ColObj<eB_White>    B_White;

private:
    struct AnsiVals
    {
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
    };

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

    static WORD getCurAttribs(HANDLE hConsole);
    static void InitDefaultAttr();

    static WORD ms_defaultAttr;

    static std::ostream& ansiCol(eColours fore, eColours back, std::string text, std::ostream& os, bool restore = true);
    static std::ostream& ansiSetFore(eColours fore, std::ostream& os);
    static std::ostream& ansiSetBack(eColours back, std::ostream& os);

    static std::ostream& winCol(eColours fore, eColours back, std::string text, std::ostream& os, HANDLE hCurConsole, bool restore = true);
    static std::ostream& winSetFore(eColours fore, std::ostream& os);
    static std::ostream& winSetBack(eColours back, std::ostream& os);

//#ifdef _MSC_VER
    static std::ostream& winSetFore(eColours fore, std::ostream& os, HANDLE hCurConsole);
    static std::ostream& winSetBack(eColours back, std::ostream& os, HANDLE hCurConsole);

    static std::string ColourStr(eColours col, HANDLE hCurConsole);
    static std::ostream& allColoursWin(HANDLE hCurConsole, std::ostream& os);
    static std::ostream& resetWin(std::ostream& os, HANDLE hCurConsole);
    static std::ostream& colTextWin(eColours fore, eColours back, std::string text, std::ostream& os, bool restore, HANDLE hCurConsole);
//#endif
    static std::ostream& allColoursAnsi(std::ostream& os);
};

std::ostream& operator<<(std::ostream& os, const ConsoleDisplay::ColObjBase& obj);

#endif //__MCS__MACRO_TEST__CONSOLE_DISPLAY_H__ 

