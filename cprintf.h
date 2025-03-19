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
#include <stdlib.h>
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

int cprintf_cfmt_snprintf (char *buf, size_t buf_n, const char * restrict format) {
  int rc = 0;
  int index = 0;
  const char * pointer = format;

  char *buf_iter = buf;
  size_t remaining_n = buf_n;

  while (*pointer != '\0') {
    if (pointer[0] == '%' && (pointer[1] == 'F' || pointer[1] == 'B' || pointer[1] == 'A')) {
      pointer++;

      switch (pointer[0]) {
        case 'F':
        case 'B':
          pointer++;

          switch (pointer[0]) {
            case 'k': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_BLACK]   : CPRINTF_BG_COLOURS[CPRINTF_BLACK]);    break;
            case 'r': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_RED]     : CPRINTF_BG_COLOURS[CPRINTF_RED]);      break;
            case 'g': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_GREEN]   : CPRINTF_BG_COLOURS[CPRINTF_GREEN]);    break;
            case 'y': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_YELLOW]  : CPRINTF_BG_COLOURS[CPRINTF_YELLOW]);   break;
            case 'b': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_BLUE]    : CPRINTF_BG_COLOURS[CPRINTF_BLUE]);     break;
            case 'm': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_MAGENTA] : CPRINTF_BG_COLOURS[CPRINTF_MAGENTA]);  break;
            case 'c': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_CYAN]    : CPRINTF_BG_COLOURS[CPRINTF_CYAN]);     break;
            case 'w': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : (pointer[-1] == 'F') ? CPRINTF_FG_COLOURS[CPRINTF_WHITE]   : CPRINTF_BG_COLOURS[CPRINTF_WHITE]);    break;
          }
          break;
        case 'A':
            pointer++;

            switch (pointer[0]) {
              case 'r': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_RESET]); break;
              case 'b': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_BOLD]); break;
              case 'f': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_DIM]); break;
              case 'i': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_ITALIC]); break;
              case 'u': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_UNDERLINE]); break;
              case 'l': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_BLINK_SLOW]); break;
              case 'k': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_BLINK_RAPID]); break;
              case 'v': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_INVERTED]); break;
              case 'h': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_HIDDEN]); break;
              case 's': rc = snprintf(buf_iter, remaining_n, "%s", (!cprintf_enable_flag) ? "" : CPRINTF_ATTRIBUTES[CPRINTF_STRIKETHOUGH]); break;
            }
            break;
        default:
          rc = snprintf(buf_iter, remaining_n, "%%%c", pointer[0]);
          break;
      }
    }
    else {
      if (buf != NULL)
      {
        *buf_iter = pointer[0];
      }
      rc = 1;
    }

    /* handle snprintf failure */
    if (rc == -1)
    {
      return -1;
    }

    /* increment the total bytes written */
    index += rc;

    /* move along the buffer if in write mode */
    if (buf_iter != NULL) { 
      buf_iter    += rc;
      remaining_n -= rc;

      if (index > buf_n) {
        break;
      }
    }

    /* move the read pointer */ 
    pointer++;
  }

  index++;
  if (buf_iter != NULL) {
    *buf_iter = '\0';
    buf_iter++;
    remaining_n--;
  }
  return index;
}

char *cprintf_get_cfmt (const char * restrict format) {
  int rc = 0;
  char  *cfmt = NULL;
  size_t cfmt_size = 0;

  rc = cprintf_cfmt_snprintf (NULL, 0, format);
  if (rc <= -1) { 
    return NULL; 
  }
  cfmt_size = (size_t)rc;
  cfmt = malloc (cfmt_size + 1);
  if (cfmt == NULL) {
    return NULL;
  }
  (void)cprintf_cfmt_snprintf (cfmt, cfmt_size, format);
  cfmt[cfmt_size] = '\0';

  return cfmt;
}

int cvsnprintf(char *buf, size_t buf_n, const char * restrict format, va_list args)
{
  int rc = 0;
  char *cfmt = NULL;

  cfmt = cprintf_get_cfmt(format);
  if (cfmt == NULL) {
    return -1;
  }

  rc = vsnprintf(buf, buf_n, cfmt, args);

  free (cfmt);
  cfmt = NULL;
  return rc;
}


int csnprintf(char *buf, size_t buf_n, const char * restrict format, ...) {
  va_list args;
  int rc = 0;

  va_start(args, format);
  
  rc = cvsnprintf(buf, buf_n, format, args);

  va_end(args);
  return rc;
}


int cvfprintf(FILE *stream, const char * restrict format, va_list args) {
  int rc = 0;
  char *cfmt = NULL;

  cfmt = cprintf_get_cfmt(format);
  if (cfmt == NULL) {
    return -1;
  }

  rc = vfprintf(stream, cfmt, args);

  free (cfmt);
  cfmt = NULL;
  return rc;
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
