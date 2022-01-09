#include <cstddef>
#include <cstdint>

namespace Fib::Std
{
#if __cplusplus
#if (__cplusplus >= (2017'00)) // for constexpr lambda

#define FIBSTD_BITFIELD_WIDTH(bitfieldContainerType, bitfieldName)                                                            \
    []() constexpr->std::size_t                                                                                        \
    {                                                                                                                  \
        bitfieldContainerType container{};                                                                             \
        --container.bitfieldName;                                                                                      \
        std::size_t bitCount = 0;                                                                                      \
        while (container.bitfieldName != 0)                                                                            \
        {                                                                                                              \
            container.bitfieldName >>= 1;                                                                              \
            ++bitCount;                                                                                                \
        }                                                                                                              \
        return bitCount;                                                                                               \
    }                                                                                                                  \
    ()

#define FIBSTD_BITFIELD_MAX(bitfieldContainerType, bitfieldName)                                                                      \
    []() constexpr->std::size_t                                                                                        \
    {                                                                                                                  \
        bitfieldContainerType container{};                                                                                     \
        return --container.bitfieldName;                                                                               \
    }                                                                                                                  \
    ()

#endif
#endif
} // namespace Fib::Std