#include <stdio.h>

#if defined (_MSC_VER)
#define compiler "MSVC"
#endif

#if defined (__GNUC__)
#define compiler "GCC"
#endif

#if defined (__TINYC__)
#define compiler "TCC"
#endif

#if defined (__clang__)
#define compiler "clang"
#endif

#ifdef NDEBUG
#define asserts "disabled"
#else
#define asserts "enabled"
#endif

int main()
{
	printf("Compiler: %s\n", compiler);
	printf("Bitness: %d\n", sizeof(void*) * 8);
	printf("Asserts: %s\n", asserts);
	return 0;
}
