/*
 * app_enet.h
 *
 *  Created on: 3 июн. 2022 г.
 *      Author: tkachev
 */

#ifndef APP_ENET_H_
#define APP_ENET_H_

//Cyclone TCP
#include "Cyclone_TCP/cyclone_tcp/core/net.h"
#include "Cyclone_TCP/cyclone_tcp/drivers/mac/stm32h7xx_eth_driver.h"
#include "Cyclone_TCP/cyclone_tcp/drivers/phy/ksz8081_driver.h"
#include "date_time.h"
#include "debug.h"
#include "path.h"
#include "Cyclone_TCP/cyclone_crypto/rng/yarrow.h"
#include "Cyclone_TCP/cyclone_tcp/http/mime.h"
#include "Cyclone_TCP/cyclone_crypto/hardware/stm32h7xx_crypto.h"
#include "Cyclone_TCP/cyclone_crypto/hardware/stm32h7xx_crypto_trng.h"
#include "Cyclone_TCP/cyclone_tcp/http/http_server.h"
#include "tls.h"

#define APP_HTTP_SERVER_CERT "certs/server_cert.pem"
#define APP_HTTP_SERVER_KEY "certs/server_key.pem"
#define PO_VER               "1.0"

#pragma pack(push, 1)
typedef	struct Enet_Param
{
	uint8_t myPassword[9];
	uint8_t myMAC[18];
	uint8_t myIP[16];
	uint8_t myMASK[16];
	uint8_t myGTW[16];
	uint16_t Http;

} Enet_Param_t;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct app_enet
{

#ifdef INCLUDE_TCP_TERMINAL
	Socket *serverTerminalTCPSocket;
	Socket *clientTerminalTCPSocket;
	IpAddr clientIpAddr;
	uint16_t clientPort;
#endif

	Socket * serverUDPSocket;
	IpAddr *clientIpAddrUDP;
	uint16_t clientPortUDP;

	Enet_Param_t *EnetParam; // Параметры сети

} app_enet_t;
#pragma pack(pop)

void netCyclonTCPInit(void);
void SetNewNetConfig(Enet_Param_t *param);

//Forward declaration of functions
error_t httpServerTlsInitCallback(HttpConnection *connection,
   TlsContext *tlsContext);

HttpAccessStatus httpServerAuthCallback(HttpConnection *connection,
   const char_t *user, const char_t *uri);

error_t httpServerCgiCallback(HttpConnection *connection,
   const char_t *param);

error_t httpServerRequestCallback(HttpConnection *connection,
   const char_t *uri);

error_t httpServerUriNotFoundCallback(HttpConnection *connection,
   const char_t *uri);

error_t httpServerAnswer(HttpConnection *connection, const char_t *filename,  const void *data, size_t length);

uint8_t setNewParam(char_t *data, size_t length);
char_t * getValueByTagName( const char_t *sourse, const char_t *dest, size_t length);
uint8_t comparePasswords(char_t *data, size_t length);

void *tftpServerOpenFileCallback(const char_t *filename,
   const char_t *mode, bool_t writeAccess);

error_t tftpServerWriteFileCallback(void *file,
   size_t offset, const uint8_t *data, size_t length);

error_t tftpServerReadFileCallback(void *file,
   size_t offset, uint8_t *data, size_t size, size_t *length);

void tftpServerCloseFileCallback(void *file);


void vTCPTask( void *pvParametrs );


#endif /* APP_ENET_H_ */
