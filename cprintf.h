#ifndef CPRINTF_H
#define CPRINTF_H

#ifdef CPRINTF_IMPLEMENTATION

#define CPRINTF_BLACK                               0
#define CPRINTF_RED                                 1
#define CPRINTF_GREEN                               2
#define CPRINTF_YELLOW                              3
#define CPRINTF_BLUE                                4
#define CPRINTF_MAGENTA                             5
#define CPRINTF_CYAN                                6
#define CPRINTF_WHITE                               7
#define CPRINTF_DEFAULT                             9

#define CPRINTF_RESET                               0
#define CPRINTF_BOLD                                1
#define CPRINTF_DIM                                 2
#define CPRINTF_ITALIC                              3
#define CPRINTF_UNDERLINE                           4
#define CPRINTF_BLINK_SLOW                          5
#define CPRINTF_BLINK_RAPID                         6
#define CPRINTF_INVERTED                            7
#define CPRINTF_HIDDEN                              8
#define CPRINTF_STRIKETHOUGH                        9

#define CPRINTF_BUFFER_SIZE                         2048

static const char * CPRINTF_FG_COLOURS[] = {
  "\033[30m",
  "\033[31m",
  "\033[32m",
  "\033[33m",
  "\033[34m", 
  "\033[35m",
  "\033[36m",
  "\033[37m"
};

static const char * CPRINTF_BG_COLOURS[] = {
  "\033[40m",
  "\033[41m",
  "\033[42m",
  "\033[43m",
  "\033[44m", 
  "\033[45m",
  "\033[46m",
  "\033[47m"
};

static const char * CPRINTF_ATTRIBUTES[] = {
  "\033[0m",
  "\033[1m",
  "\033[2m",
  "\033[3m",
  "\033[4m",
  "\033[5m", 
  "\033[6m",
  "\033[7m",
  "\033[8m",
  "\033[9m"
};

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifndef CPRINTF_ENABLE_FLAG_DEFAULT
#define CPRINTF_ENABLE_FLAG_DEFAULT 1
#endif
static int cprintf_enable_flag = CPRINTF_ENABLE_FLAG_DEFAULT;

void cprintf_enable(void) {
  cprintf_enable_flag = 1; 
}

void cprintf_disable(void) {
  cprintf_enable_flag = 0; 
}

void cprintf_toggle(void) {
  cprintf_enable_flag ^= 1;
}

int cprintf_get_status(void) {
  return cprintf_enable_flag;
}

int cvfprintf(FILE *stream, const char * restrict format, va_list args) {
  char buffer[CPRINTF_BUFFER_SIZE];
  int index = 0;
  const char * pointer = format;

  while (pointer[0]) {
    if (pointer[0] == '%' && (pointer[1] == 'F' || pointer[1] == 'B' || pointer[1] == 'A')) {
      pointer++;

      switch (pointer[0]) {
        case 'F':
        case 'B':
          pointer++;

          switch (pointer[0]) {
            case 'k': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_BLACK]   : CPRINTF_BG_COLOURS[CPRINTF_BLACK]);    break;
            case 'r': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_RED]     : CPRINTF_BG_COLOURS[CPRINTF_RED]);      break;
            case 'g': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_GREEN]   : CPRINTF_BG_COLOURS[CPRINTF_GREEN]);    break;
            case 'y': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_YELLOW]  : CPRINTF_BG_COLOURS[CPRINTF_YELLOW]);   break;
            case 'b': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_BLUE]    : CPRINTF_BG_COLOURS[CPRINTF_BLUE]);     break;
            case 'm': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_MAGENTA] : CPRINTF_BG_COLOURS[CPRINTF_MAGENTA]);  break;
            case 'c': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_CYAN]    : CPRINTF_BG_COLOURS[CPRINTF_CYAN]);     break;
            case 'w': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_WHITE]   : CPRINTF_BG_COLOURS[CPRINTF_WHITE]);    break;
          }

          index += strlen(&buffer[index]);
          break;
        case 'A':
            pointer++;

            switch (pointer[0]) {
              case 'r': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_RESET]); break;
              case 'b': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_BOLD]); break;
              case 'f': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_DIM]); break;
              case 'i': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_ITALIC]); break;
              case 'u': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_UNDERLINE]); break;
              case 'l': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_BLINK_SLOW]); break;
              case 'k': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_BLINK_RAPID]); break;
              case 'v': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_INVERTED]); break;
              case 'h': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_HIDDEN]); break;
              case 's': snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_STRIKETHOUGH]); break;
            }

            index += strlen(&buffer[index]);
            break;
        default:
          snprintf(&buffer[index], CPRINTF_BUFFER_SIZE - index, "%%%c", pointer[0]);
          index += strlen(&buffer[index]);
          break;
      }
    }
    
    else {
      buffer[index++] = pointer[0];
    }

    if (index >= CPRINTF_BUFFER_SIZE) {
      break;
    }
      
    pointer++;
  }

  buffer[index] = '\0';
  return vfprintf(stream, buffer, args);
}


int cfprintf(FILE *stream, const char * restrict format, ...) {
  int rc;
  va_list args;
  va_start(args, format);

  rc = cvfprintf(stream, format, args);

  va_end(args);
  return rc;
}

int cprintf(const char * restrict format, ...) {
  int rc;
  va_list args;
  va_start(args, format);

  rc = cvfprintf(stdout, format, args);

  va_end(args);
  return rc;
}

#endif // CPRINTF_IMPLEMENTATION

#endif // CPRINTF_H
