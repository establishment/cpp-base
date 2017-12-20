#ifndef CPPBASE_MACROS_HPP
#define CPPBASE_MACROS_HPP

#define NONRET __attribute__((noreturn))
#define UNUSED __attribute__((unused))
#define GENERATE_PRINTF_WARNINGS __attribute__((format(printf, 1, 2)))

#endif // CPPBASE_MACROS_HPP
