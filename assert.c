#include <__cross_studio_io.h>

void __assert(const char *__expression, const char *__filename, int __line)
{
	debug_printf( "Assertion failed : %s %s %d\n", __expression, __filename, __line );
}