#pragma once

#include <any>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <variant>

namespace Konfet {

enum class ConstantType : uint8_t {
    LUA_TNIL = 0,
    LUA_TBOOLEAN = 1,
    LUA_TNUMBER = 3,
    LUA_TSTRING = 4
};

class LuaConstant {
    typedef std::variant<std::monostate, bool, double, std::string> ValueType;

public:
    LuaConstant& operator=(const ValueType& other);
    friend std::ostream& operator<<(std::ostream& os, LuaConstant constant);

    void setValue(const ValueType newValue);
    bool empty();
    bool isNil();
    ConstantType type();

private:
    bool m_hasValue = false;
    ValueType m_value;
};

} // namespace Konfet