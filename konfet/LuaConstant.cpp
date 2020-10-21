#include "LuaConstant.h"

namespace Konfet {

LuaConstant& LuaConstant::operator=(const ValueType& other)
{
    setValue(other);
    return *this;
}

std::ostream& operator<<(std::ostream& os, LuaConstant constant)
{
    switch (constant.type()) {
    case ConstantType::LUA_TNIL:
        os << "(nil)";
        break;
    case ConstantType::LUA_TBOOLEAN:
        os << std::get<bool>(constant.value);
        break;
    case ConstantType::LUA_TNUMBER:
        os << std::get<double>(constant.value);
        break;
    case ConstantType::LUA_TSTRING:
        os << std::get<std::string>(constant.value);
        break;
    default:
        throw std::exception("trying to stream uninitialized constant");
    }
}

void LuaConstant::setValue(const ValueType newValue)
{
    value = newValue;
    hasValue = true;
}

bool LuaConstant::isNil()
{
    return !empty() && std::holds_alternative<std::monostate>(value);
}

ConstantType LuaConstant::type()
{
    if (empty()) {
        throw std::exception("cannot get type of uninitialized constant");
    }

    switch (value.index()) {
    case 0:
        return ConstantType::LUA_TNIL;
    case 1:
        return ConstantType::LUA_TBOOLEAN;
    case 2:
        return ConstantType::LUA_TNUMBER;
    case 3:
        return ConstantType::LUA_TSTRING;
    default:
        throw std::exception("invalid constant type");
    }
}

bool LuaConstant::empty()
{
    return !hasValue;
}

} // namespace Konfet