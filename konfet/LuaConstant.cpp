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
        return os << "(nil)";
    case ConstantType::LUA_TBOOLEAN:
        return os << std::get<bool>(constant.m_value);
    case ConstantType::LUA_TNUMBER:
        return os << std::get<double>(constant.m_value);
    case ConstantType::LUA_TSTRING:
        return os << std::get<std::string>(constant.m_value);
    default:
        throw std::exception("trying to stream uninitialized constant");
    }
}

void LuaConstant::setValue(const ValueType newValue)
{
    m_value = newValue;
    m_hasValue = true;
}

bool LuaConstant::isNil()
{
    return !empty() && std::holds_alternative<std::monostate>(m_value);
}

ConstantType LuaConstant::type()
{
    if (empty()) {
        throw std::exception("cannot get type of uninitialized constant");
    }

    switch (m_value.index()) {
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
    return !m_hasValue;
}

} // namespace Konfet