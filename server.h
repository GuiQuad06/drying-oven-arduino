#ifndef SERVER_CORE_H
#define SERVER_CORE_H

#include "error.h"

err_t server_init(void);
void server_setupRest(int &temp, int &hum, int &dht_temp, int &dht_hum, int &bat);
void server_begin(void);
void server_listen(void);

#endif // SERVER_CORE_H