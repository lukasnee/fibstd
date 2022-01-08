#include "configVariable.hpp"

struct Config
{
    struct Default
    {
#define CONFIG_VAR(type, name, defaultValue) static constexpr type name = defaultValue;
        CONFIG_VARS
#undef CONFIG_VAR
    };

#define CONFIG_VAR(type, name, defaultValue)                                                                           \
    ConfigVariable<type> name = ConfigVariable<type>(Default::name);
    CONFIG_VARS
#undef CONFIG_VAR
} config;