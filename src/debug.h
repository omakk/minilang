#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define DBG(x) printf x
#else
#define DBG(x) do {} while (0)
#endif

#endif
