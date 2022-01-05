#include "include/fibutils/prettyTable.hpp"

#include <cstring>

namespace Fib::Utils
{
int PrettyTable::printPaddingAndCloseField(std::size_t descrIndex, std::uint16_t charsAlreadyPrinted)
{
    int charsPrinted = 0;
    for (std::size_t i = charsAlreadyPrinted; i < this->descriptors[descrIndex].width; i++)
    {
        charsPrinted += this->printfF(Config::Format::space);
    }
    charsPrinted += this->printSpacing(Config::Format::space);
    charsPrinted += this->printfF(Config::Format::verticalBorder);
    return charsPrinted;
}

int PrettyTable::printSpacing(const char *strSpacing)
{
    int charsPrinted = 0;
    for (std::size_t i = Config::Format::columnSpacing; i; i--)
    {
        if (std::strlen(strSpacing) == 0)
        {
            charsPrinted += 1;
        }
        else
        {
            charsPrinted += this->printfF(strSpacing);
        }
    }
    return charsPrinted;
}

int PrettyTable::printHeader()
{
    int charsPrinted = 0;
    charsPrinted += this->printPlainLine();
    charsPrinted += this->printTitle();
    charsPrinted += this->printHeaderWithoutTitle();
    return charsPrinted;
}

int PrettyTable::printHeaderWithoutTitle()
{
    int charsPrinted = 0;
    charsPrinted += this->printHeaderUnderlines();
    charsPrinted += this->printHeaderNames();
    charsPrinted += this->printHeaderUnderlines();
    return charsPrinted;
}
int PrettyTable::printEndOfTable()
{
    int charsPrinted = 0;
    charsPrinted += this->printHeaderUnderlines();
    return charsPrinted;
}

int PrettyTable::printPlainLine()
{
    int charsPrinted = 0;
    charsPrinted += this->printfF(Config::Format::corner);
    for (std::size_t i = 0; i < this->descriptors.count(); i++)
    {
        charsPrinted += this->printSpacing(Config::Format::horizontalBorder);
        for (std::size_t underlineLeft = this->descriptors[i].width; underlineLeft > 0; underlineLeft--)
        {
            charsPrinted += this->printfF(Config::Format::horizontalBorder);
        }
        charsPrinted += this->printSpacing(Config::Format::horizontalBorder);
        if (this->descriptors.count() - i > 1)
        {
            charsPrinted += this->printfF(Config::Format::horizontalBorder);
        }
        else
        {
            charsPrinted += this->printfF(Config::Format::corner);
        }
    }
    charsPrinted += this->printfF(Config::Format::newline);
    return charsPrinted;
}

int PrettyTable::printTitle()
{
    int charsPrinted = 0;
    charsPrinted += this->printfF(Config::Format::verticalBorder);
    std::uint16_t totalTableWidth = std::strlen(Config::Format::verticalBorder);
    for (std::size_t i = 0; i < this->descriptors.count(); i++)
    {
        totalTableWidth += Config::Format::columnSpacing;
        totalTableWidth += this->descriptors[i].width;
        totalTableWidth += Config::Format::columnSpacing;
        totalTableWidth += std::strlen(Config::Format::verticalBorder);
    }
    charsPrinted += this->printSpacing(Config::Format::space);
    const int minWidth = static_cast<int>(std::strlen(this->title));
    const int maxWidth = totalTableWidth - std::strlen(Config::Format::verticalBorder) - Config::Format::columnSpacing -
                         Config::Format::columnSpacing - std::strlen(Config::Format::verticalBorder);
    const int charsPrintedContent =
        this->printfF(Config::Format::headerRangedFmt, minWidth, Config::maxLengthForPrintfF, this->title);
    charsPrinted += charsPrintedContent;
    for (int i = 0; i < (maxWidth - charsPrintedContent); i++)
    {
        charsPrinted += this->printSpacing(Config::Format::space);
    }
    charsPrinted += this->printSpacing(Config::Format::space);
    charsPrinted += this->printfF(Config::Format::verticalBorder);
    charsPrinted += this->printfF(Config::Format::newline);
    return charsPrinted;
}

int PrettyTable::printHeaderUnderlines()
{
    int charsPrinted = 0;
    charsPrinted += this->printfF(Config::Format::corner);
    for (std::size_t i = 0; i < this->descriptors.count(); i++)
    {
        charsPrinted += this->printSpacing(Config::Format::horizontalBorder);
        for (std::size_t underlineLeft = this->descriptors[i].width; underlineLeft > 0; underlineLeft--)
        {
            charsPrinted += this->printfF(Config::Format::horizontalBorder);
        }
        charsPrinted += this->printSpacing(Config::Format::horizontalBorder);
        charsPrinted += this->printfF(Config::Format::corner);
    }
    charsPrinted += this->printfF(Config::Format::newline);
    return charsPrinted;
}

int PrettyTable::printHeaderNames()
{
    int charsPrinted = 0;
    charsPrinted += this->printfF(Config::Format::verticalBorder);
    for (std::size_t i = 0; i < this->descriptors.count(); i++)
    {
        charsPrinted += this->printSpacing(Config::Format::space);
        const int minWidth = static_cast<int>(std::strlen(this->descriptors[i].strName));
        const int maxWidth = static_cast<int>(this->descriptors[i].width);
        const int charsPrintedContent = this->printfF(Config::Format::headerRangedFmt, minWidth,
                                                      Config::maxLengthForPrintfF, this->descriptors[i].strName);
        charsPrinted += charsPrintedContent;
        for (int i = 0; i < (maxWidth - charsPrintedContent); i++)
        {
            charsPrinted += this->printSpacing(Config::Format::space);
        }
        charsPrinted += this->printSpacing(Config::Format::space);
        charsPrinted += this->printfF(Config::Format::verticalBorder);
    }
    charsPrinted += this->printfF(Config::Format::newline);
    return charsPrinted;
}

} // namespace Fib::Utils