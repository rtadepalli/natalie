#include "natalie.h"
#include "nat_string.h"

NatObject *String_to_s(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    assert(self->type == NAT_VALUE_STRING);
    NAT_ASSERT_ARGC(0);
    return self;
}

NatObject *String_ltlt(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    assert(self->type == NAT_VALUE_STRING);
    NAT_ASSERT_ARGC(1);
    NatObject *arg = args[0];
    char *str;
    if (arg->type == NAT_VALUE_STRING) {
        str = arg->str;
    } else {
        NatObject *str_obj = nat_send(env, arg, "to_s", 0, NULL, NULL);
        assert(str_obj->type == NAT_VALUE_STRING);
        str = str_obj->str;
    }
    nat_string_append(self, str);
    return self;
}

NatObject *String_inspect(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    assert(self->type == NAT_VALUE_STRING);
    NAT_ASSERT_ARGC(0);
    NatObject *out = nat_string(env, "\"");
    for (size_t i=0; i<self->str_len; i++) {
        // FIXME: iterate over multibyte chars
        char c = self->str[i];
        if (c == '"' || c == '\\') {
            nat_string_append_char(out, '\\');
            nat_string_append_char(out, c);
        } else if (c == '\n') {
            nat_string_append(out, "\\n");
        } else {
            nat_string_append_char(out, c);
        }
    }
    nat_string_append_char(out, '"');
    return out;
}

NatObject *String_add(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    assert(self->type == NAT_VALUE_STRING);
    NAT_ASSERT_ARGC(1);
    NatObject *arg = args[0];
    char *str;
    if (arg->type == NAT_VALUE_STRING) {
        str = arg->str;
    } else {
        NatObject *str_obj = nat_send(env, arg, "to_s", 0, NULL, NULL);
        assert(str_obj->type == NAT_VALUE_STRING);
        str = str_obj->str;
    }
    NatObject *new_str = nat_string(env, self->str);
    nat_string_append(new_str, str);
    return new_str;
}

NatObject *String_mul(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    assert(self->type == NAT_VALUE_STRING);
    NAT_ASSERT_ARGC(1);
    NatObject *arg = args[0];
    assert(arg->type == NAT_VALUE_INTEGER);
    NatObject *new_str = nat_string(env, "");
    for (size_t i=0; i<arg->integer; i++) {
        nat_string_append_nat_string(new_str, self);
    }
    return new_str;
}

NatObject *String_eqeq(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    assert(self->type == NAT_VALUE_STRING);
    NAT_ASSERT_ARGC(1);
    NatObject *arg = args[0];
    if (arg->type == NAT_VALUE_STRING && strcmp(self->str, arg->str) == 0) {
        return nat_var_get(env, "true");
    } else {
        return nat_var_get(env, "false");
    }
}

NatObject *String_cmp(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    assert(self->type == NAT_VALUE_STRING);
    NAT_ASSERT_ARGC(1);
    NatObject* arg = args[0];
    if (arg->type != NAT_VALUE_STRING) return nat_var_get(env, "nil");
    return nat_integer(env, strcmp(self->str, arg->str));
}

