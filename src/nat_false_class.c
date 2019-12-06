#include "natalie.h"
#include "nat_false_class.h"

NatObject *FalseClass_new(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    printf("FIXME: this method should not be defined\n");
    abort();
}

NatObject *FalseClass_to_s(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block) {
    assert(self->type == NAT_VALUE_FALSE);
    return nat_string(env, "false");
}
