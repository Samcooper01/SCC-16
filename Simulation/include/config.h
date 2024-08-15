#ifndef CONFIG_H
#define CONFIG_H

//Debug is the same as interactive mode
#define DEBUG_LEVEL_0           0
#define DEBUG_LEVEL_1           1
#define DEBUG_LEVEL_2           2

void debug_printf(int debug_level, const char *format, ...);

extern int current_debug_level;

#endif /* CONIFG_H */
