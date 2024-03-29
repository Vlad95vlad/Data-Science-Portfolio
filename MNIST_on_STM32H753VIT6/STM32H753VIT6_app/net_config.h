/**
 * @file net_config.h
 * @brief CycloneTCP configuration file
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2010-2021 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneTCP Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.1.0
 **/

#ifndef _NET_CONFIG_H
#define _NET_CONFIG_H


//Sets TCP/IP tick interval (in milliseconds). A value of 100ms is recommended.
#define NET_TICK_INTERVAL        100


//Trace level for TCP/IP stack debugging
//Trace level for TCP/IP stack debugging
#define MEM_TRACE_LEVEL          4
#define NIC_TRACE_LEVEL          4
#define ETH_TRACE_LEVEL          2
#define ARP_TRACE_LEVEL          2
#define IP_TRACE_LEVEL           2
#define IPV4_TRACE_LEVEL         2
#define IPV6_TRACE_LEVEL         2
#define ICMP_TRACE_LEVEL         2
#define IGMP_TRACE_LEVEL         2
#define ICMPV6_TRACE_LEVEL       2
#define MLD_TRACE_LEVEL          2
#define NDP_TRACE_LEVEL          2
#define UDP_TRACE_LEVEL          2
#define TCP_TRACE_LEVEL          2
#define SOCKET_TRACE_LEVEL       2
#define RAW_SOCKET_TRACE_LEVEL   2
#define BSD_SOCKET_TRACE_LEVEL   2
#define WEB_SOCKET_TRACE_LEVEL   2
#define AUTO_IP_TRACE_LEVEL      4
#define SLAAC_TRACE_LEVEL        4
#define DHCP_TRACE_LEVEL         4
#define DHCPV6_TRACE_LEVEL       4
#define DNS_TRACE_LEVEL          4
#define MDNS_TRACE_LEVEL         2
#define NBNS_TRACE_LEVEL         2
#define LLMNR_TRACE_LEVEL        2
#define COAP_TRACE_LEVEL         4
#define FTP_TRACE_LEVEL          5
#define HTTP_TRACE_LEVEL         4
#define MQTT_TRACE_LEVEL         4
#define MQTT_SN_TRACE_LEVEL      4
#define SMTP_TRACE_LEVEL         5
#define SNMP_TRACE_LEVEL         4
#define SNTP_TRACE_LEVEL         4
#define TFTP_TRACE_LEVEL         4
#define MODBUS_TRACE_LEVEL       4

//Number of network adapters
//Sets the number of network interfaces. If the application
//makes use of multiple network adapters, the default value can be
//changed to reflect the actual number of interfaces.
#define NET_INTERFACE_COUNT 1
#define NET_TASK_STACK_SIZE 255
#define NET_TASK_PRIORITY   5

//Size of the MAC address filter
#define MAC_ADDR_FILTER_SIZE 12

//IPv4 support
//This switch adds or removes support for IPv4.
#define IPV4_SUPPORT ENABLED
//Size of the IPv4 multicast filter
#define IPV4_MULTICAST_FILTER_SIZE 4

//IPv4 support
#define IPV4_SUPPORT ENABLED
//Size of the IPv4 multicast filter
#define IPV4_MULTICAST_FILTER_SIZE 4

//IPv4 fragmentation support
#define IPV4_FRAG_SUPPORT ENABLED
//Maximum number of fragmented packets the host will accept
//and hold in the reassembly queue simultaneously
#define IPV4_MAX_FRAG_DATAGRAMS 4
//Maximum datagram size the host will accept when reassembling fragments
#define IPV4_MAX_FRAG_DATAGRAM_SIZE 8192

//Size of ARP cache
#define ARP_CACHE_SIZE 10
//Maximum number of packets waiting for address resolution to complete
#define ARP_MAX_PENDING_PACKETS 2

//IGMP host support
#define IGMP_HOST_SUPPORT DISABLED
//This switch adds or removes support for Auto-IP (dynamic configuration of IPv4 link-local addresses).
#define AUTO_IP_SUPPORT ENABLED

//IPv6 support
#define IPV6_SUPPORT DISABLED
//Size of the IPv6 multicast filter
#define IPV6_MULTICAST_FILTER_SIZE 8

//IPv6 fragmentation support
#define IPV6_FRAG_SUPPORT DISABLED
//Maximum number of fragmented packets the host will accept
//and hold in the reassembly queue simultaneously
#define IPV6_MAX_FRAG_DATAGRAMS 4
//Maximum datagram size the host will accept when reassembling fragments
#define IPV6_MAX_FRAG_DATAGRAM_SIZE 8192

//MLD support
#define MLD_SUPPORT DISABLED

//Neighbor cache size
#define NDP_NEIGHBOR_CACHE_SIZE 8
//Destination cache size
#define NDP_DEST_CACHE_SIZE 8
//Maximum number of packets waiting for address resolution to complete
#define NDP_MAX_PENDING_PACKETS 2

//TCP support
#define TCP_SUPPORT ENABLED
//Sets the TCP tick interval (in milliseconds). A value of 100ms or 200ms is recommended.
#define TCP_TICK_INTERVAL 100
//Maximum segment size, in bytes. A value of 1430 bytes is recommended to accommodate both IPv4 and IPv6.
#define TCP_MAX_MSS       1430
//Default buffer size for transmission
#define TCP_DEFAULT_TX_BUFFER_SIZE (1024)
//Default buffer size for reception
#define TCP_DEFAULT_RX_BUFFER_SIZE (1024)

#define TCP_MAX_TX_BUFFER_SIZE 6144
#define TCP_MAX_RX_BUFFER_SIZE 6144
//Default SYN queue size for listening sockets
#define TCP_DEFAULT_SYN_QUEUE_SIZE 4
//Maximum SYN queue size for listening sockets.
#define TCP_MAX_SYN_QUEUE_SIZE    6
//Maximum number of retransmissions
#define TCP_MAX_RETRIES           5
//nitial retransmission timeout (in milliseconds). This value can be increased up to 3s to
//accommodate high latency networks.
#define TCP_INITIAL_RTO           1000
//Selective acknowledgment support
#define TCP_SACK_SUPPORT ENABLED

//UDP support
#define UDP_SUPPORT ENABLED
//Receive queue depth for connectionless sockets
#define UDP_RX_QUEUE_SIZE 4

//Raw socket support
#define RAW_SOCKET_SUPPORT DISABLED
//Receive queue depth for raw sockets
#define RAW_SOCKET_RX_QUEUE_SIZE 4

//Number of sockets that can be opened simultaneously
#define SOCKET_MAX_COUNT 7

//LLMNR responder support
#define LLMNR_RESPONDER_SUPPORT DISABLED

//HTTP server support
#define HTTP_SERVER_SUPPORT DISABLED
//HTTP over TLS
#define HTTP_SERVER_TLS_SUPPORT DISABLED
//Server Side Includes support
#define HTTP_SERVER_SSI_SUPPORT DISABLED
//Basic access authentication support
#define HTTP_SERVER_BASIC_AUTH_SUPPORT DISABLED
//Support for persistent connections
#define HTTP_SERVER_PERSISTENT_CONN_SUPPORT DISABLED
//HTTP Strict Transport Security support
#define HTTP_SERVER_HSTS_SUPPORT DISABLED

#define HTTP_SERVER_STACK_SIZE  615
#define HTTP_SERVER_PRIORITY    4
#define HTTP_SERVER_BUFFER_SIZE 512

// Unknown defines
#define SNMP_MD5_SUPPORT DISABLED
#define SNMP_SHA1_SUPPORT DISABLED
#define SNMP_AES_SUPPORT DISABLED
#define SNMP_DES_SUPPORT DISABLED
#define SMTP_CLIENT_LOGIN_AUTH_SUPPORT DISABLED
#define SMTP_CLIENT_PLAIN_AUTH_SUPPORT DISABLED
#define BSD_SOCKET_SUPPORT DISABLED


#define APP_IF_NAME "eth0"
#define APP_HOST_NAME "https-server-BC32X"
#define APP_PASSWORD "12345678"
#define APP_MAC_ADDR "00-C0-CA-6B-86-E3"
//#define APP_MAC_ADDR "00-C0-CA-A8-03-12"
#define APP_IPV4_HOST_ADDR "192.168.3.18"
#define APP_IPV4_SUBNET_MASK "255.255.255.0"
#define APP_IPV4_DEFAULT_GATEWAY "192.168.0.1"
#define APP_UDP_PORT    4515
#define MAX_UDPBUF_SIZE  1200

//Application configuration
#define APP_HTTP_MAX_CONNECTIONS 4
//FTP server support
#define FTP_SERVER_SUPPORT DISABLED

//TFTP server support
#define TFTP_SERVER_SUPPORT DISABLED
//Priority at which the TFTP server should run
#define TFTP_SERVER_PRIORITY OS_TASK_PRIORITY_HIGH

#endif
