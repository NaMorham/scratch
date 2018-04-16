#pragma once
#include <memory>
#include <string>

class ConsoleDisplay
{
public:
    static std::shared_ptr<ConsoleDisplay> get() { }

    static bool usingColour;
    static bool usingansi;

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

    bool m_isAnsi;

    static std::shared_ptr<ConsoleDisplay> ms_console;
};

#ifdef _MSC_VER
#include <Windows.h>
#endif

void allColours();

std::ostream& winCol(WORD fore, WORD back, std::string text, std::ostream& os, bool restore = true);
