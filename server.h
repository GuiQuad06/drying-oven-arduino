#ifndef SERVER_CORE_H
#define SERVER_CORE_H

/**
 * @brief Basic Error Handler
 */
typedef enum {
  ERR_SUCCESS = 0,
  ERR_FAILURE = 1,
  NEEDS_UPDATE = 2
} err_t;

err_t server_init(void);
void server_setupRest(int &temp, int &hum, int &bat);
void server_begin(void);
void server_listen(void);

#endif // SERVER_CORE_H