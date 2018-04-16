#pragma once
#include <memory>
#include <string>

#ifdef _MSC_VER
#include <Windows.h>
#endif

class ConsoleDisplay;

//typedef std::shared_ptr<ConsoleDisplay> PConsoleDisplay;

class ConsoleDisplay
{
public:
    static ConsoleDisplay& get();

    static void allColours();

    static std::ostream& winCol(WORD fore, WORD back, std::string text, std::ostream& os, bool restore = true);

    static void printLastError();

    static std::string GetLastErrorText(uint32_t err);

    static std::string getEnvVar(std::string var);

    static bool isWindowsConsole() { return ms_isWindowsConsole; }
    static bool usingColour() { return ms_usingColour; }
    static bool usingansi() { return ms_usingANSI; }

    const char *NRM;
    const char *BLD;
    const char *BLK;
    const char *RED;
    const char *GRN;
    const char *YRL;
    const char *BLU;
    const char *MAG;
    const char *CYN;
    const char *WHT;

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
};

