#include "natalie.hpp"

namespace Natalie {
const BigInt BignumValue::MAX_BIGINT { NAT_INT_MAX };
const BigInt BignumValue::MIN_BIGINT { NAT_INT_MIN };

ValuePtr BignumValue::to_s(Env *env, ValuePtr base_value) {
    if (base_value) {
        // NATFIXME
        NAT_UNREACHABLE();
    }
    return new StringValue { m_bignum->to_string().c_str() };
}

ValuePtr BignumValue::add(Env *env, ValuePtr arg) {
    if (arg->is_float()) {
        double current = strtod(m_bignum->to_string().c_str(), NULL);
        auto result = current + arg->as_float()->to_double();
        return new FloatValue { result };
    }

    if (!arg.is_integer()) {
        arg = Natalie::coerce(env, arg, this).second;
    }

    arg.assert_type(env, Value::Type::Integer, "Integer");

    auto other = arg->as_integer();
    return new BignumValue { to_bignum() + other->to_bignum() };
}

bool BignumValue::eq(Env *env, ValuePtr other) {
    if (other.is_integer()) {
        return to_bignum() == other->as_integer()->to_bignum();
    } else if (other->is_float()) {
        return to_bignum() == other->as_float()->to_double();
    }
    return false;
}

bool BignumValue::lt(Env *env, ValuePtr other) {
    if (other->is_float()) {
        return to_bignum() < other->as_float()->to_double();
    }

    if (!other.is_integer()) {
        other = Natalie::coerce(env, other, this).second;
    }

    if (other.is_integer()) {
        return to_bignum() < other->as_integer()->to_bignum();
    }
    env->raise("ArgumentError", "comparison of Integer with {} failed", other->inspect_str(env));
}

bool BignumValue::lte(Env *env, ValuePtr other) {
    if (other->is_float()) {
        return to_bignum() <= other->as_float()->to_double();
    }

    if (!other.is_integer()) {
        other = Natalie::coerce(env, other, this).second;
    }

    if (other.is_integer()) {
        return to_bignum() <= other->as_integer()->to_bignum();
    }
    env->raise("ArgumentError", "comparison of Integer with {} failed", other->inspect_str(env));
}

bool BignumValue::gt(Env *env, ValuePtr other) {
    if (other->is_float()) {
        return to_bignum() > other->as_float()->to_double();
    }

    if (!other.is_integer()) {
        other = Natalie::coerce(env, other, this).second;
    }

    if (other.is_integer()) {
        return to_bignum() > other->as_integer()->to_bignum();
    }
    env->raise("ArgumentError", "comparison of Integer with {} failed", other->inspect_str(env));
}

bool BignumValue::gte(Env *env, ValuePtr other) {
    if (other.is_float()) {
        return to_bignum() >= other->as_float()->to_double();
    }

    if (!other.is_integer()) {
        other = Natalie::coerce(env, other, this).second;
    }

    if (other.is_integer()) {
        return to_bignum() >= other->as_integer()->to_bignum();
    }
    env->raise("ArgumentError", "comparison of Integer with {} failed", other->inspect_str(env));
}
}
