#ifndef ERROR_H
#define ERROR_H

/**
 * @brief Basic Error Handler
 */
typedef enum {
  ERR_SUCCESS = 0,
  ERR_FAILURE = 1,
  NEEDS_UPDATE = 2,
  ERR_INVALID_POINTER = 3,
  ERR_INVALID_ARGUMENT = 4
} err_t;

#endif // ERROR_H