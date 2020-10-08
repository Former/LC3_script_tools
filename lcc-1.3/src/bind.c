#include "c.h"
#undef yy
#define yy \
xx(lc3,          lc3IR) \
xx(lc3_32bit,    lc3_32bitIR) \
xx(lc3dtu,       lc3dtuIR) \
xx(lc3dtu_32bit, lc3dtu_32bitIR) \
xx(symbolic/osf, symbolic64IR) \
xx(symbolic/irix,symbolicIR) \
xx(symbolic,     symbolicIR) \
xx(bytecode,     bytecodeIR) \
xx(null,         nullIR)

#undef xx
#define xx(a,b) extern Interface b;
yy

Binding bindings[] = {
#undef xx
#define xx(a,b) #a, &b,
yy
	NULL, NULL
};
#undef yy
#undef xx
