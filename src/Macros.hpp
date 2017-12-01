#ifndef CPP_BASE_MACROS
#define CPP_BASE_MACROS

#define NONRET __attribute__((noreturn))
#define UNUSED __attribute__((unused))
#define GENERATE_PRINTF_WARNINGS __attribute__((format(printf, 1, 2)))

#endif
