#include "fibutils/prettyTable.hpp"

#include <cstring>

namespace Fib::Utils
{
int PrettyTable::printPaddingAndCloseField(std::size_t descrIndex, std::uint16_t charsAlreadyPrinted)
{
    int charsPrinted = 0;
    for (std::size_t i = charsAlreadyPrinted; i < this->descriptors[descrIndex].width; i++)
    {
        charsPrinted += this->printfF(this->format.config.space.get());
    }
    charsPrinted += this->printSpacing(this->format.config.space.get());
    charsPrinted += this->printfF(this->format.config.verticalBorder.get());
    return charsPrinted;
}

int PrettyTable::printSpacing(const char *strSpacing)
{
    int charsPrinted = 0;
    for (std::size_t i = this->format.config.columnSpacing.get(); i; i--)
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
    charsPrinted += this->printfF(this->format.config.corner.get());
    for (std::size_t i = 0; i < this->descriptors.count(); i++)
    {
        charsPrinted += this->printSpacing(this->format.config.horizontalBorder.get());
        for (std::size_t underlineLeft = this->descriptors[i].width; underlineLeft > 0; underlineLeft--)
        {
            charsPrinted += this->printfF(this->format.config.horizontalBorder.get());
        }
        charsPrinted += this->printSpacing(this->format.config.horizontalBorder.get());
        if (this->descriptors.count() - i > 1)
        {
            charsPrinted += this->printfF(this->format.config.horizontalBorder.get());
        }
        else
        {
            charsPrinted += this->printfF(this->format.config.corner.get());
        }
    }
    charsPrinted += this->printfF(this->format.config.newline.get());
    return charsPrinted;
}

int PrettyTable::printTitle()
{
    int charsPrinted = 0;
    charsPrinted += this->printfF(this->format.config.verticalBorder.get());
    std::uint16_t totalTableWidth = std::strlen(this->format.config.verticalBorder.get());
    for (std::size_t i = 0; i < this->descriptors.count(); i++)
    {
        totalTableWidth += this->format.config.columnSpacing.get();
        totalTableWidth += this->descriptors[i].width;
        totalTableWidth += this->format.config.columnSpacing.get();
        totalTableWidth += std::strlen(this->format.config.verticalBorder.get());
    }
    charsPrinted += this->printSpacing(this->format.config.space.get());
    const int minWidth = static_cast<int>(std::strlen(this->title));
    const int maxWidth = totalTableWidth - std::strlen(this->format.config.verticalBorder.get()) -
                         this->format.config.columnSpacing.get() - this->format.config.columnSpacing.get() -
                         std::strlen(this->format.config.verticalBorder.get());
    const int charsPrintedContent = this->printfF(this->format.config.headerRangedFmt.get(), minWidth,
                                                  this->config.maxLengthForPrintfF.get(), this->title);
    charsPrinted += charsPrintedContent;
    for (int i = 0; i < (maxWidth - charsPrintedContent); i++)
    {
        charsPrinted += this->printSpacing(this->format.config.space.get());
    }
    charsPrinted += this->printSpacing(this->format.config.space.get());
    charsPrinted += this->printfF(this->format.config.verticalBorder.get());
    charsPrinted += this->printfF(this->format.config.newline.get());
    return charsPrinted;
}

int PrettyTable::printHeaderUnderlines()
{
    int charsPrinted = 0;
    charsPrinted += this->printfF(this->format.config.corner.get());
    for (std::size_t i = 0; i < this->descriptors.count(); i++)
    {
        charsPrinted += this->printSpacing(this->format.config.horizontalBorder.get());
        for (std::size_t underlineLeft = this->descriptors[i].width; underlineLeft > 0; underlineLeft--)
        {
            charsPrinted += this->printfF(this->format.config.horizontalBorder.get());
        }
        charsPrinted += this->printSpacing(this->format.config.horizontalBorder.get());
        charsPrinted += this->printfF(this->format.config.corner.get());
    }
    charsPrinted += this->printfF(this->format.config.newline.get());
    return charsPrinted;
}

int PrettyTable::printHeaderNames()
{
    int charsPrinted = 0;
    charsPrinted += this->printfF(this->format.config.verticalBorder.get());
    for (std::size_t i = 0; i < this->descriptors.count(); i++)
    {
        charsPrinted += this->printSpacing(this->format.config.space.get());
        const int minWidth = static_cast<int>(std::strlen(this->descriptors[i].strName));
        const int maxWidth = static_cast<int>(this->descriptors[i].width);
        const int charsPrintedContent =
            this->printfF(this->format.config.headerRangedFmt.get(), minWidth, this->config.maxLengthForPrintfF.get(),
                          this->descriptors[i].strName);
        charsPrinted += charsPrintedContent;
        for (int i = 0; i < (maxWidth - charsPrintedContent); i++)
        {
            charsPrinted += this->printSpacing(this->format.config.space.get());
        }
        charsPrinted += this->printSpacing(this->format.config.space.get());
        charsPrinted += this->printfF(this->format.config.verticalBorder.get());
    }
    charsPrinted += this->printfF(this->format.config.newline.get());
    return charsPrinted;
}

} // namespace Fib::Utils