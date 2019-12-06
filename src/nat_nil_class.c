#include "natalie.h"
#include "nat_nil_class.h"

NatObject *NilClass_new(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    printf("FIXME: this method should not be defined\n");
    abort();
}

NatObject *NilClass_to_s(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    assert(self->type == NAT_VALUE_NIL);
    NatObject *out = nat_string(env, "");
    return out;
}

NatObject *NilClass_inspect(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    assert(self->type == NAT_VALUE_NIL);
    NatObject *out = nat_string(env, "nil");
    return out;
}
