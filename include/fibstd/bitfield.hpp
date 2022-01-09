#include <cstddef>
#include <cstdint>

namespace Fib::Std
{
#if __cplusplus
#if (__cplusplus >= (2017'00)) // for constexpr lambda

#define BITFIELD_WIDTH(StructType, bitfieldName)                                                                       \
    []() constexpr->std::size_t                                                                                        \
    {                                                                                                                  \
        StructType structure{};                                                                                        \
        --structure.data.fields.bitfieldName;                                                                          \
        std::size_t bitCount = 0;                                                                                      \
        while (structure.data.fields.bitfieldName != 0)                                                                \
        {                                                                                                              \
            structure.data.fields.bitfieldName >>= 1;                                                                  \
            ++bitCount;                                                                                                \
        }                                                                                                              \
        return bitCount;                                                                                               \
    }                                                                                                                  \
    ()

#define BITFIELD_MAX(StructType, bitfieldName)                                                                         \
    []() constexpr->std::size_t                                                                                        \
    {                                                                                                                  \
        StructType structure{};                                                                                        \
        return --structure.data.fields.bitfieldName;                                                                   \
    }                                                                                                                  \
    ()

#endif
#endif
} // namespace Fib::Std