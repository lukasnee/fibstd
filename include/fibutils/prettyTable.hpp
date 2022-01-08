#pragma once

#include <algorithm>
#include <array>
#include <cstdint>

namespace Fib::Utils
{

class PrettyTable
{

public:
    using PrintfF = int(const char *, ...);

    struct ColumnDescr
    {
        const char *strName = nullptr;
        const char *strFmt = nullptr;
        const std::size_t width = 0;
    };

    template <std::size_t size> using ColumnsDescr = std::array<ColumnDescr, size>;

    template <std::size_t size>
    PrettyTable(PrintfF printfF, const char *title, const ColumnsDescr<size> &columnsDescr)
        : printfF(printfF), title(title), descriptors(columnsDescr.data(), columnsDescr.size())
    {
    }

    int printHeader();
    int printHeaderWithoutTitle();
    template <typename... Args> int printEntry(Args... args)
    {
        int charsPrinted = 0;
        charsPrinted += this->printfF(this->format.config.verticalBorder.get());
        charsPrinted += this->printEntryRecursively(0, args...);
        return charsPrinted;
    }
    int printEndOfTable();
    struct Format
    {
    public:
#define CONFIG_VARS                                                                                                    \
    CONFIG_VAR(std::size_t, columnSpacing, 1)                                                                          \
    CONFIG_VAR(const char *, corner, "+")                                                                              \
    CONFIG_VAR(const char *, horizontalBorder, "-")                                                                    \
    CONFIG_VAR(const char *, verticalBorder, "|")                                                                      \
    CONFIG_VAR(const char *, newline, "\n")                                                                            \
    CONFIG_VAR(const char *, space, " ")                                                                               \
    CONFIG_VAR(const char *, headerRangedFmt, "%-*.*s")
#include "fibutils/configTemplate.hpp"
#undef CONFIG_VARS
    } format;

#define CONFIG_VARS                                                                                                    \
    CONFIG_VAR(bool, noHorizontalLinesBetweenEntries, false)                                                           \
    CONFIG_VAR(std::size_t, maxLengthForPrintfF, 64 - sizeof('\0'))
#include "fibutils/configTemplate.hpp"
#undef CONFIG_VARS

private:
    class Descriptors
    {
    public:
        Descriptors(const ColumnDescr *pData, std::size_t count) : pData(pData), cnt(count)
        {
        }
        const ColumnDescr &operator[](std::size_t index) const
        {
            return index < this->cnt ? this->pData[index] : this->empty;
        }
        std::size_t count() const
        {
            return this->cnt;
        }

    private:
        const ColumnDescr empty, *pData = nullptr;
        std::size_t cnt = 0;
    };

    template <typename Arg, typename... Args> int printEntryRecursively(std::size_t idx, Arg arg, Args... args)
    {
        int charsPrinted = 0;
        if (idx < this->descriptors.count())
        {
            charsPrinted += this->printSpacing(this->format.config.space.get());
            auto contentPrinted = this->printfF(this->descriptors[idx].strFmt, arg);
            charsPrinted += contentPrinted;
            charsPrinted += printPaddingAndCloseField(idx, contentPrinted);
            charsPrinted += printEntryRecursively(idx + 1, args...);
        }
        return charsPrinted;
    }

    template <typename Arg> int printEntryRecursively(std::size_t idx, Arg arg)
    {
        int charsPrinted = 0;
        if (idx < this->descriptors.count())
        {
            charsPrinted += this->printSpacing(this->format.config.space.get());
            auto contentPrinted = this->printfF(this->descriptors[idx].strFmt, arg);
            charsPrinted += contentPrinted;
            charsPrinted += printPaddingAndCloseField(idx, contentPrinted);
            charsPrinted += this->printfF(this->format.config.newline.get());
            if (this->config.noHorizontalLinesBetweenEntries.get())
            {
            }
            else
            {
                this->printEndOfTable();
            }
        }
        return charsPrinted;
    }

    int printPaddingAndCloseField(std::size_t descrIndex, std::uint16_t charsAlreadyPrinted);
    int printSpacing(const char *strSpacing);
    int printPlainLine();
    int printTitle();
    int printHeaderNames();
    int printHeaderUnderlines();

    PrintfF *printfF = nullptr;
    const char *title = nullptr;
    const Descriptors descriptors;
};

class PrettyTablePrinter
{
public:
    using PrintfF = int(const char *, ...);

    PrettyTablePrinter(PrettyTable &prettyTable) : prettyTable(prettyTable)
    {
        this->prettyTable.printHeader();
    }

    template <std::size_t size>
    PrettyTablePrinter(PrintfF printfF, const char *title,
                       const PrettyTable::ColumnsDescr<size> &prettyTableColumnsDescr)
        : prettyTable(printfF, title, prettyTableColumnsDescr)
    {
        this->prettyTable.printHeader();
    }
    template <typename... Args> int printEntry(Args... args)
    {
        return this->prettyTable.printEntry(args...);
    }

    ~PrettyTablePrinter()
    {
        if (this->prettyTable.config.noHorizontalLinesBetweenEntries.get())
        {
            this->prettyTable.printEndOfTable();
        }
    }

private:
    PrettyTable prettyTable;
};

} // namespace Fib::Utils