#ifndef DEBUG_H
#define DEBUG_H

#ifdef IDEBUG
#define AssertRaw(expression) if(!(expression)) { *(int *)0 = 0; }
#else
#define AssertRaw(expression)
#endif

#endif // !DEBUG_H

