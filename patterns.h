
#ifndef __PATTERNS_H
#define __PATTERNS_H

#include <vram.h>

extern const pattern_t white_pattern;
extern const pattern_t white_small_pattern;
extern const pattern_t black_pattern;
extern const pattern_t bird_pattern;


#define white_pattern_pmfa ((uint8_t)0)
#define white_small_pattern_pmfa ((uint8_t)1)
#define bird_pattern_pmfa ((uint8_t)2)

#define white_pattern_pmba ((uint8_t)0)
#define black_pattern_pmba ((uint8_t)1)

void load_background_pattern(const pattern_t pattern, const uint8_t pmba);
void load_foreground_pattern(const pattern_t pattern, const uint8_t pmfa);

void load_patterns(void);

#endif
