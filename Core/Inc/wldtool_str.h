#ifndef __WLDTOOL_STR_H_
#define __WLDTOOL_STR_H_
// ========================== Confiture ================================

#define WLDSTR_BUFFER_SIZE 100
#define WLDSTR_BUFFER_COUNT 3

// ========================== Confiture ================================
char *str_getline(char **str);
char *str_getstr_until_arg(char **str, char arg);

float str_prase_float(char *buffer);
int str_prase_int(char *buffer);
int str_copy(char *pstr, char *cstr);

char str_compare(char *str, char *str2);
char *str_getformat(char *charsquence, ...);
long str_getnumber(char **str);
int str_len(char *str);

#endif
