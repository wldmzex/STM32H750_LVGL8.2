#include "wldtool_str.h"
#include "stdarg.h"

char buffer[WLDSTR_BUFFER_SIZE];
char buffer_current_use = 0;
// int debug_size = 0;
//  ##########################
//  get length of string
//  ##########################
int str_len(char *str) {
  int i = 0;
  while (*str != 0) {
    i++;
    str++;
  }
  return i;
}

// ##########################
// compare string,1 for same
// ##########################
char str_compare(char *str1, char *str2) {
  while (*str1 != 0 && *str2 != 0) {
    if (*str1 != *str2)
      return 0;
    str1++;
    str2++;
  }
  if (*str1 == *str2)
    return 1;
  return 0;
}
// ##########################
// convert string 2 number -- dec part
// ##########################
long str_getnumber(char **str) {
  long i = 0;
  unsigned char p = 0;
  while (**str != 0) {
    if (**str >= '0' && **str < '9')
      break;
    if (**str == '-') {
      (*str)++;
      if (**str >= '0' && **str < '9') {
        p = 1;
        break;
      }
    }
    (*str)++;
  }
  while ((**str >= '0' && **str <= '9')) {
    i *= 10;
    i += **str - '0';
    (*str)++;
  }
  if (p)
    i = -i;
  return i;
}

// ##########################
// read a string line
// move pointer to next line
// ##########################
char *str_readline(char **str) {
  char *p = buffer;
  if (**str == 0) {
    buffer[0] = 0;
    return buffer;
  }
  while (**str != '\n' && **str != ' ' && **str != 0) {
    *p = **str;
    p++;
    (*str)++;
  }
  *p = 0;
  return buffer;
}

// ##########################
// ruturn buffer with result
// ##########################
char *str_getstr_until_arg(char **str, char arg) {
  char *p = buffer;
  if (**str == 0) {
    buffer[0] = 0;
    return buffer;
  }
  while (**str != arg && **str != 0) {
    *p = **str;
    p++;
    (*str)++;
  }
  *p = 0;
  return buffer;
}

// ##########################
// copy string return copy size
// ##########################
int str_copy(char *pstr, char *cstr) {
  int i = 0;
  while (*cstr != 0) {
    *pstr = *cstr;
    pstr++;
    i++;
    cstr++;
  }
  *pstr = 0;
  *cstr = 0;
  return i;
}

// ##########################
// convert string 2 number
// ##########################
int str_prase_int(char *string) {
  int value = 0;
  int sign = 0;
  while (*buffer != 0) {
    if (*buffer == '-') {
      sign = 1;
      string++;
    }
    value *= 10;
    value += (*string - '0');
    string++;
  }
  if (sign) {
    value = -value;
  }
  return value;
}

// ##########################
// convert string 2 number
// ##########################
double str_prase_double(char *string) {
  double value = 0;
  int sign = 0;
  while (*buffer != 0) {
    if (*buffer == '-') {
      sign += 0x8000;
      string++;
    }
    if (*buffer == '.') {
      sign += 0x4000;
      string++;
    }
    if (sign & 0x4000) {
      sign++;
    }
    value *= 10;
    value += (*string - '0');
    string++;
  }
  if (sign & 0x8000) {
    value = -value;
  }
  sign &= 0x3fff;
  while (sign) {
    value /= 10;
    sign--;
  }
  return value;
}

// ##########################
// append hexdata 2 content
// ##########################
int str_format_d8(unsigned char data, char **buffer) {
  **buffer = data;
  (*buffer)++;
  return 0;
}

// ##########################
// format function -- String part
// ##########################
int str_formats(char *formatstr, char **buffer) {
  int format_i = 0;
  while (formatstr[format_i] != '\0') {
    str_format_d8(formatstr[format_i], buffer);
    format_i++;
  }
  return 0;
}

// ##########################
// format function -- Number part
// ##########################
int str_format_num(long f, int base, char **buffer) {
  if (f == 0) {
    return 0;
  }
  str_format_num(f / base, base, buffer);
  str_format_d8("0123456789abcdef"[f % base], buffer);
  return 0;
}

// ##########################
// format function -- signed number part
// ##########################
int str_format_dec(int d, char **buffer) {
  if (d == 0) {
    str_format_d8('0', buffer);
  }
  if (d < 0) {
    str_format_d8('-', buffer);
    str_format_num(-d, 10, buffer);
  } else {
    str_format_num(d, 10, buffer);
  }
  return 0;
}

// ##########################
// format function -- hex number part
// ##########################
int str_format_hex(int d, char **buffer) {
  if (d == 0) {
    str_format_d8('0', buffer);
  }
  if (d < 0) {
    str_format_d8('-', buffer);
    str_format_num(-d, 16, buffer);
  } else {
    str_format_num(d, 16, buffer);
  }
  return 0;
}
// ##########################
// format function -- hex number part
// ##########################
int str_format_num_double(double f, char **buf, char size) {
  int i = (int)f;
  str_format_dec(i, buf);
  str_format_d8('.', buf);
  if (size == 0) {
    size = 6;
    f = f - i;
    while ((f != 0) && (size--)) {
      f *= 10;
      str_format_d8("0123456789abcdef"[(int)f % 10], buf);
      f -= (int)f;
    }
  } else {
    f = f - i;
    while ((size--)) {
      f *= 10;
      str_format_d8("0123456789abcdef"[(int)f % 10], buf);
      f -= (int)f;
    }
  }
  return 0;
}
// ##########################
// format function -- hex number part
// ##########################
int str_format_double(double num, char **buf, char size) {
  if (num == 0) {
    str_format_d8('0', buf);
  }
  if (num < 0) {
    str_format_d8('-', buf);
    str_format_num_double(-num, buf, size);
  } else {
    str_format_num_double(num, buf, size);
  }
  return 0;
}

// ##########################
// get string from charsquence
// ##########################
char *str_getformat(char *charsquence, ...) {
  int format_i = 0, motion = 0;
  char *buf = buffer;
  va_list va_p;
  va_start(va_p, charsquence);
  while (charsquence[format_i] != '\0') {
    if (charsquence[format_i] != '%') {
      if (charsquence[format_i] != '\\') {
        str_format_d8(charsquence[format_i], &buf);
      } else {
        switch (charsquence[++format_i]) {
        case 'n':
          str_format_d8('\n', &buf);
          break;
        case 'r':
          str_format_d8('\r', &buf);
          break;
        }
      }
    } else {
      while (charsquence[format_i + 1] >= '0' &&
             charsquence[format_i + 1] <= '9') {
        motion *= 10;
        if (motion == 0 && *charsquence == '0') {
          motion++;
          continue;
        }
        motion += (charsquence[format_i + 1] - '0');
        format_i++;
      }
      switch (charsquence[++format_i]) {
      case 'd':
        str_format_dec(va_arg(va_p, int), &buf);
        break;
      case 'c':
        str_format_d8(va_arg(va_p, int), &buf);
        break;
      case 's':
        str_formats(va_arg(va_p, char *), &buf);
        break;
      case 'f':
        str_format_double(va_arg(va_p, double), &buf, motion);
        break;
      case 'h':
        str_format_hex(va_arg(va_p, int), &buf);
        break;
      }
    }
    motion = 0;
    format_i++;
  }
  *buf = 0;
  va_end(va_p);
  return buffer;
}
