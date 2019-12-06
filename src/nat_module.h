#ifndef __NAT_MODULE__
#define __NAT_MODULE__

NatObject *Module_new(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block);
NatObject *Module_inspect(NatEnv *env, NatObject *self, size_t argc, NatObject **args, struct hashmap *kwargs, NatBlock *block);

#endif
