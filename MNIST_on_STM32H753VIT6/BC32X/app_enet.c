/*
 * app_enet.c
 *
 *  Created on: 3 июн. 2022 г.
 *      Author: tkachev
 */



#include "app_enet.h"
#include "app_interface.h"
#include "app_periph.h"

#include "tftp/tftp_server.h"

#include "stm32h753xx.h"
#include "stm32h7xx_hal.h"

const uint8_t server_cert[] = {"-----BEGIN CERTIFICATE-----"
								 "MIICOTCCAeCgAwIBAgIUeohUShlJC9c8B+pIWol5iHOMfXMwCgYIKoZIzj0EAwIw"
								 "SzELMAkGA1UEBhMCRlIxFjAUBgNVBAoMDU9yeXggRW1iZWRkZWQxJDAiBgNVBAMM"
								 "G09yeXggRW1iZWRkZWQgVGVzdCBFQ0RTQSBDQTAeFw0xOTA2MjkxMjQ3MDNaFw0y"
								 "NDA2MjcxMjQ3MDNaMEExCzAJBgNVBAYTAkZSMRYwFAYDVQQKDA1Pcnl4IEVtYmVk"
								 "ZGVkMRowGAYDVQQDDBFodHRwcy1zZXJ2ZXItZGVtbzBZMBMGByqGSM49AgEGCCqG"
								 "SM49AwEHA0IABLx7aAcNrvC2RP8nkRiOvyE7Ehqke1dmA9bwHReB6WHhUIVFGTgB"
								 "UyqtfMEqzPiKjl1/hR++QvBwsu3tec7RCF+jgaswgagwEQYJYIZIAYb4QgEBBAQD"
								 "AgZAMAwGA1UdEwEB/wQCMAAwDgYDVR0PAQH/BAQDAgWgMB0GA1UdDgQWBBRD7CmX"
								 "Tbl37ks14TsYAj1tvVBb/DAfBgNVHSMEGDAWgBS8YBR2AZbAhjOLwWfA55tIH9PZ"
								 "uzA1BgNVHREELjAsghFodHRwcy1zZXJ2ZXItZGVtb4IXaHR0cHMtc2VydmVyLWRl"
								 "bW8ubG9jYWwwCgYIKoZIzj0EAwIDRwAwRAIgZ4TD0PE4rPHp1qisZw00bPm2pHkE"
								 "a9YPc4z3eVdHLLMCIFlKSuyXTjejqkyEfDSLNQmC7aylz8JrRk3MNGIGSfxw"
								 "-----END CERTIFICATE-----"};

const uint8_t server_key[] = {"-----BEGIN EC PARAMETERS-----"
								"BggqhkjOPQMBBw=="
								"-----END EC PARAMETERS-----"
								"-----BEGIN EC PRIVATE KEY-----"
								"MHcCAQEEIDfnnFlaI0STg8m+aoGrAGcVXioq6S5SCTaMUqG2/RepoAoGCCqGSM49"
								"AwEHoUQDQgAEvHtoBw2u8LZE/yeRGI6/ITsSGqR7V2YD1vAdF4HpYeFQhUUZOAFT"
								"Kq18wSrM+IqOXX+FH75C8HCy7e15ztEIXw=="
								"-----END EC PRIVATE KEY-----"};

const uint8_t str_html[] = {"<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
	"<meta http-equiv=\"Content-Type\" content=\"text/html\">\n"
	"<meta charset=\"windows-1251\">\n"

	"<title>Rele Ethernet Web Server</title>\n"
	  "<script type=\"text/javascript\" src=\"js/ReleEth.js\"></script>\n"
//"		<script src=\"js/ReleEth.js\"></script>\n"

	"<link rel=\"stylesheet\" href=\"css/reset.css\">\n"
	"<link rel=\"stylesheet\" href=\"css/demo.css\">\n"

"</head>\n"
"<body>\n"
	"<noscript>Enable JavaScript in your browser!</noscript>\n"
	"<!--<div id=\"center\"> -->\n"
		"<div class=\"wrapper\">\n"
		"<div class=\"header bkColor3\"><div class=\"headerText\">BC32X web server</div></div>\n"
		"<!--<div class=\"wrapper\">-->\n"
			"<br>\n"

		"<table>\n"
		"<tr><td><form id=\"main_form\" action =\"post_ind.html\" method=\"post\" name=\"main_form\" >\n"
							"<button type=\"submit\" class=\"submit_send\" name=\"submit_send\"> Send </button>\n"
			"<tr><td width=\"320px\">\n"
			"<table class=\"dataTable\" style=\"width: 800px;\">\n"
				"<tr><th class=\"bkColor3\" colspan=3><center>System Information</center></td></tr>\n"
				"<tr><td>Password</td><td class=\"tdparam\"></td>  <td><input id=\"U_PAS\" name=\"U_PAS\" type=\"password\" inputmode = \"verbatim\"\n"
												  "maxlength=\"8\" size=\"20\" placeholder=\"Password\"></td></tr>\n"
				"<tr><td>New password</td><td class=\"tdparam\"></td> <td><input id=\"NEW_PAS\" name=\"NEW_PAS\" type=\"password\" inputmode = \"verbatim\"\n"
												   "maxlength=\"8\" size=\"20\" placeholder=\"New password\"></td></tr> \n"
				"</td></tr>\n"
				"<tr><td>Confirm password</td><td class=\"tdparam\"></td> <td><input id=\"CONF_PAS\" name=\"CONF_PAS\" type=\"password\" inputmode = \"verbatim\"\n"
												   "maxlength=\"8\" size=\"20\" placeholder=\"Confirm password\"></td></tr>\n"
				"</td></tr>\n"
				"<tr><td>MAC Address</td><td id=\"mac_addr\" class=\"tdparam\"></td> <td><input id=\"MAC\" type=\"text\" name=\"MAC\" placeholder=\"hex: xx-xx-xx-xx-xx-xx\"> </td></tr>\n"
				"<tr><td>Protocol</td><td id=\"protocol\" class=\"tdparam\"> </td> <td>"
						"<select name=\"select\" class=\"select-css\">"
    					"<option value=\"s1\">HTTP</option>"
    					"<option value=\"s2\">HTTPS</option>"
						"</select>"
						"</td></tr>\n"
				"<tr><td>Software version</td><td id=\"po_ver\" class=\"tdparam\"> </td></tr>\n"
			"</table>\n"
			"<br>\n"

			"<table class=\"dataTable\" style=\"width: 800px;\">\n"
				"<tr><th class=\"bkColor1\" colspan=3><center>IPv4 Configuration</center></td></tr>\n"
				"<tr><td>IPv4 Address</td><td id=\"ip_addr\" class=\"tdparam\"> </td> <td><input id=\"IP\" type=\"text\" name=\"IP\" placeholder=\"xx.xx.xx.xx\"></td></tr>\n"
				"<tr><td>Subnet Mask</td><td id=\"m_m\" class=\"tdparam\"> </td> <td><input id=\"S_MASK\" type=\"text\" name=\"S_MASK\" placeholder=\"xx.xx.xx.xx\"></td></tr>\n"
				"<tr><td>Default Gateway</td><td id=\"gate\" class=\"tdparam\"> </td> <td><input id=\"D_GTW\" type=\"text\" name=\"D_GTW\" placeholder=\"xx.xx.xx.xx\"></td></tr>\n"
			"</table>\n"
			"<br>\n"
		"</form></td></tr>\n"
		"</table>\n"
		"<script> timerEvent(); </script>\n"
		"</div>\n"
		"<div class=\"footer bkColor3\"><div class=\"footerText\">AO \"Альфа - Прибор\"</div></div>\n"
	"</div>\n"
"</body>\n"
"</html>\n"
};


const uint8_t favicon_ico[] = { 0x89, 0x50, 0x4e, 0x47, 0xd, 0xa, 0x1a, 0xa, 0x0, 0x0, 0x0, 0xd, 0x49, 0x48, 0x44, 0x52, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0,
								0x0, 0x10, 0x8, 0x3, 0x0, 0x0, 0x0, 0x28, 0x2d, 0xf, 0x53, 0x0, 0x0, 0x0, 0x4, 0x67, 0x41, 0x4d, 0x41, 0x0, 0x0, 0xb1, 0x8f,
								0xb, 0xfc, 0x61, 0x5, 0x0, 0x0, 0x0, 0x20, 0x63, 0x48, 0x52, 0x4d, 0x0, 0x0, 0x7a, 0x26, 0x0, 0x0, 0x80, 0x84, 0x0, 0x0, 0xfa,
								0x0, 0x0, 0x0, 0x80, 0xe8, 0x0, 0x0, 0x75, 0x30, 0x0, 0x0, 0xea, 0x60, 0x0, 0x0, 0x3a, 0x98, 0x0, 0x0, 0x17, 0x70, 0x9c, 0xba,
								0x51, 0x3c, 0x0, 0x0, 0x0, 0xdb, 0x50, 0x4c, 0x54, 0x45, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0,
								0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0,
								0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0,
								0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0,
								0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0,
								0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0,
								0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0,
								0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0,
								0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0,
								0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0,
								0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0x16, 0x7e, 0xc0, 0xff, 0xff, 0xff, 0xf0, 0xbf, 0xbf,
								0x4e, 0x0, 0x0, 0x0, 0x47, 0x74, 0x52, 0x4e, 0x53, 0x0, 0x0, 0x0, 0x32, 0xcd, 0xd7, 0xe2, 0x4c, 0x62, 0xe8, 0x1d, 0x77, 0xe7,
								0xed, 0xe3, 0xef, 0xdc, 0xe4, 0xc7, 0x19, 0x3f, 0xe5, 0xd8, 0xda, 0x7, 0x5e, 0xe9, 0xb8, 0xb7, 0x8f, 0x4a, 0x9f, 0x78, 0x55,
								0x25, 0xb5, 0x14, 0x41, 0x9d, 0xfe, 0x20, 0xde, 0x6e, 0x37, 0xfb, 0x46, 0xfa, 0xae, 0xdd, 0x3, 0x27, 0x64, 0x1b, 0xa1, 0xeb,
								0x6d, 0x99, 0xc, 0xd9, 0xb6, 0xf8, 0xc8, 0x7c, 0x9e, 0xd5, 0x38, 0xad, 0xee, 0x42, 0x51, 0x1c, 0x2e, 0x89, 0x32, 0xd7, 0x0,
								0x0, 0x0, 0x1, 0x62, 0x4b, 0x47, 0x44, 0x1, 0xff, 0x2, 0x2d, 0xde, 0x0, 0x0, 0x0, 0x7, 0x74, 0x49, 0x4d, 0x45, 0x7, 0xe5, 0xa,
								0x1d, 0xc, 0x36, 0x25, 0xa9, 0x9c, 0xb, 0x24, 0x0, 0x0, 0x0, 0x1, 0x6f, 0x72, 0x4e, 0x54, 0x1, 0xcf, 0xa2, 0x77, 0x9a, 0x0, 0x0,
								0x0, 0x86, 0x49, 0x44, 0x41, 0x54, 0x18, 0xd3, 0xad, 0xce, 0x59, 0x17, 0x81, 0x50, 0x18, 0x46, 0xe1, 0xcf, 0xab, 0x50, 0x94, 0xd0,
								0x39, 0x64, 0x96, 0xcc, 0x65, 0x8a, 0xcc, 0xf3, 0xf0, 0xfd, 0xff, 0x7f, 0x64, 0xb9, 0xed, 0xd2, 0xb2, 0x2f, 0x9f, 0xab, 0x4d, 0x14,
								0x2f, 0x11, 0xeb, 0x2f, 0x90, 0x54, 0xd4, 0x54, 0x3a, 0xa3, 0xe9, 0xc8, 0x6a, 0x39, 0xc3, 0xcc, 0x5b, 0x54, 0x28, 0x96, 0x6c, 0x21,
								0xcb, 0x15, 0xa7, 0x2a, 0x45, 0x8d, 0xeb, 0xd, 0xe2, 0x26, 0xd0, 0xe2, 0x36, 0x3a, 0x6e, 0xd7, 0xf1, 0x4c, 0x80, 0xb8, 0x7, 0xf4, 0x7,
								0x43, 0x0, 0x23, 0x7b, 0x2c, 0xbe, 0x30, 0x81, 0xee, 0x2b, 0xf0, 0x10, 0x4c, 0xdd, 0xd9, 0x7c, 0xb1, 0x24, 0xe, 0x57, 0x6b, 0x3f, 0xda,
								0x6c, 0x77, 0x72, 0x8f, 0xc3, 0xf1, 0x74, 0xa6, 0x8b, 0x50, 0xaf, 0xb7, 0xfb, 0x23, 0x78, 0x1a, 0x21, 0x5e, 0x91, 0xf5, 0xfe, 0xe1,
								0xf4, 0x3, 0x5e, 0x65, 0xd, 0xe8, 0x6d, 0x45, 0xbe, 0xd, 0x0, 0x0, 0x0, 0x25, 0x74, 0x45, 0x58, 0x74, 0x64, 0x61, 0x74, 0x65,
								0x3a, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x0, 0x32, 0x30, 0x32, 0x31, 0x2d, 0x31, 0x30, 0x2d, 0x32, 0x39, 0x54, 0x31, 0x32, 0x3a, 0x35,
								0x34, 0x3a, 0x33, 0x36, 0x2b, 0x30, 0x30, 0x3a, 0x30, 0x30, 0x1f, 0x24, 0xcd, 0xb1, 0x0, 0x0, 0x0, 0x25, 0x74, 0x45, 0x58, 0x74, 0x64, 0x61,
								0x74, 0x65, 0x3a, 0x6d, 0x6f, 0x64, 0x69, 0x66, 0x79, 0x0, 0x32, 0x30, 0x32, 0x31, 0x2d, 0x31, 0x30, 0x2d, 0x32, 0x39, 0x54, 0x31, 0x32, 0x3a,
								0x35, 0x34, 0x3a, 0x33, 0x36, 0x2b, 0x30, 0x30, 0x3a, 0x30, 0x30, 0x6e, 0x79, 0x75, 0xd, 0x0, 0x0, 0x0, 0x0, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42,
								0x60, 0x82
							};

const uint8_t demo_css[] = { "body {\n"
	"padding: 10px;\n"
	"font-family: Verdana, Arial, sans-serif;\n"
	"font-size: 14px;\n"
"}\n"

"h2 {\n"
	"font-size: 14px;\n"
	"font-weight: bold;\n"
	"text-align: left;\n"
	"margin: 5px 20px 5px 20px;\n"
"}\n"

"p {\n"
	"text-align: left;\n"
	"padding: 10px 30px;\n"
"}\n"

"ul {\n"
	"text-align: left;\n"
	"padding: 5px 60px;\n"
"}\n"

"li {\n"
	"list-style-type: disc;\n"
"}\n"

"span {\n"
	"display: inline-block;\n"
"}\n"

"form {\n"
	"text-align: left;\n"
	"padding: 0px 0px;\n"
"}\n"

"#slider {\n"
	"width: 800px;\n"
	"height: 600px;\n"
"}\n"

".anythingSlider-default.activeSlider .anythingWindow {\n"
	"border-color: #FFFFFF;\n"
"}\n"

"input {\n"
 	"text-align: center;\n"
 	"margin-left: 2%;\n"
"}\n"

"button {\n"
	"height: 50px;\n"
	"width: 100px;\n"
	"font-size: xx-large;\n"
	"position: fixed;\n"
	"top: 97px;\n"
"}\n"

"button.submit_send {\n"

	"background-color: #2159D6;\n"
	"color: white;\n"
	"left: 820px;\n"
"}\n"

"button.start {\n"
	"background-color: #21AA29;\n"
	"color: white;\n"
	"left: 930px;\n"
"}\n"

"button.stop {\n"
	"background-color: #D62408;\n"
	"color: white;\n"
	"left: 1040px;\n"
"}\n"

"#center {\n"
	"width: 800px;\n"
	"margin-left: auto;\n"
	"margin-right: auto;\n"
"}\n"

"div.header {\n"
	"height: 75px;\n"
	"line-height: 90px;\n"
	"width: 100%;\n"
	"text-align: right;\n"
	"border-radius: 30px 30px 0px 0px;\n"
	"-moz-border-radius: 30px 30px 0px 0px;\n"
	"-webkit-border-radius: 30px 30px 0px 0px;\n"
"}\n"

"div.headerText {\n"
	"margin-right: 30px;\n"
	"font-size: 24px;\n"
	"font-weight: bold;\n"
	"color: white;\n"
"}\n"

"div.wrapper {\n"
	"min-height: 100%;\n"
	"height: 92vh;\n"
	"background-color: #e0e0e0;\n"
	"text-align: center;\n"
"}\n"

"div.footer {\n"
	"height: 60px;\n"
	"line-height: 60px;\n"
	"width: 100%;\n"
	"text-align: right;\n"
	"border-radius: 0px 0px 30px 30px;\n"
	"-moz-border-radius: 0px 0px 30px 30px;\n"
	"-webkit-border-radius: 0px 0px 30px 30px;\n"
"}\n"

"div.footerText {\n"
	"margin-right: 30px;\n"
	"font-size: 20px;\n"
	"color: white;\n"
"}\n"

"table.dataTable {\n"
	"background: none;\n"
	"border: 0px;\n"
	"margin-left: auto;\n"
	"margin-right: auto;\n"
"}\n"

".dataTable th {\n"
	"border: 0px;\n"
	"padding: 15px;\n"
	"background-color: #000000;\n"
	"color: #FFFFFF;\n"
	"font-weight: bold;\n"
	"font-size: 22px;\n"
"}\n"

".dataTable td {\n"
	"padding: 6.5px;\n"
	"background-color: #e0e0e0;\n"
	"text-align: left;\n"
	"font-size: 20px;\n"
	"border-bottom: 0.5px solid #000000;\n"
	"width: 200px;\n"
"}\n"


".color1 {\n"
	"color: #D62408;\n"
"}\n"

".color2 {\n"
	"color: #21AA29;\n"
"}\n"

".color3 {\n"
	"color: #2159D6;\n"
"}\n"

".color4 {\n"
	"color: #FCB400;\n"
"}\n"

"td.tdparam {\n"
	"text-align: left;\n"
	"width: 280px;\n"
"}\n"


"div.bkColor1, th.bkColor1, td.bkColor1 {\n"
	"background-color: #D62408;\n"
"}\n"

"div.bkColor2, th.bkColor2 {\n"
	"background-color: #21AA29;\n"
"}\n"

"div.bkColor3, th.bkColor3 {\n"
	"background-color: #2159D6;\n"
"}\n"

"div.bkColor4, th.bkColor4 {\n"
	"background-color: #FCB400;\n"
"}\n"

".select-css {\n"
"display: block;\n"
"font-size: 16px;\n"
"font-family: sans-serif;\n"
"font-weight: 650;\n"
"text-align: center;\n"
"color: #444;\n"
"line-height: 1;\n"
"padding: .6em 1.4em .5em .8em; width: 100%;\n"
"max-width: 100%;\n"
"box-sizing: border-box;\n"
"margin: 0;\n"
"border: 1px solid #aaa;\n"
" box-shadow: 0 1px 0 1px rgba(0,0,0,.04);\n"
"border-radius: .5em;\n"
" -moz-appearance: none;\n"
" -webkit-appearance: none;\n"
" appearance: none;\n"
" background-color: #fff;\n"
"background-repeat: no-repeat, repeat;\n"
"background-position: right .7em top 50%, 0 0;\n"
"background-size: .65em auto, 100%;\n"
"}" };

const uint8_t reset_css[] = { "html, body, div, span, applet, object, iframe, h1, h2, h3, h4, h5, h6, p, blockquote, pre,\n"
		                       "a, abbr, acronym, address, big, cite, code, del, dfn, em, img, ins, kbd, q, s, samp, small,\n"
		                       "strike, strong, sub, sup, tt, var, b, u, i, center, dl, dt, dd, ol, ul, li, fieldset, form,\n"
		                       "label, legend, input, textarea, table, caption, tbody, tfoot, thead, tr, th, td, article,\n"
		                       "aside, canvas, details, embed, figure, figcaption, footer, header, hgroup, menu, nav, output,\n"
		                       "ruby, section, summary,\n"
		                       "time, mark, audio, video {\n"

		                        "margin: 0;\n"
		                        "padding: 0;\n"
		                        "border: 0;\n"
		                        "font-size: 100%;\n"
		                        "font: inherit;\n"
		                        "vertical-align: baseline;\n}\n"
		                        "article, aside, details, figcaption, figure,\n"
		                        "footer, header, hgroup, menu, nav, section {\n"
		                        "display: block;\n}\n"

		                        "body {\n"
		                        "line-height: 1;\n}\n"

		                        "ol, ul {\n"
		                        "list-style: none;\n}\n"

		                        "blockquote, q {\n"
		                        "quotes: none;\n}\n"

		                        "blockquote:before, blockquote:after,\n"
		                        "q:before, q:after {\n"
		                        "content: '';\n"
		                        "content: none;\n}\n"

		                        "table {\n"
		                        "border-collapse: collapse;\n"
		                        "border-spacing: 0;\n}\n"
                            };

const uint8_t script[] = {
		"var mac = \" \";\n"
		"var ip = \" \";\n"
		"var verpo = \" \";\n"
		"var gateway = \" \";\n"
		"var mmask = \" \";\n"
		"var prot = \" \";\n"

		"function timerEvent() {\n"
			//Create XMLHttpRequest object\n"
			"var xhr = new XMLHttpRequest();\n"

			"if(xhr == null) {\n"
				"window.alert('XMLHttpRequest object is not supported!');\n"
				"return;\n"
			"}\n"

			"xhr.onreadystatechange = function() {\n"
				"if(xhr.readyState == 4) {\n"
					"if(xhr.status == 200) {\n"
						"refreshPage(xhr);\n"
						"setTimeout('timerEvent()', 1000);\n"
					"}\n"
				"}\n"
			"};\n"

			"xhr.open('GET', 'data.xml', true);\n"
			"xhr.send(null);\n"
		"}\n"

		"function refreshPage(xhr) {\n"
			"if(xhr != null) {\n"
				"mac = (xhr.responseXML.getElementsByTagName('MAC')[0].childNodes[0].nodeValue);\n"
				"ip = (xhr.responseXML.getElementsByTagName('IP')[0].childNodes[0].nodeValue);\n"
				"verpo = (xhr.responseXML.getElementsByTagName('VER_PO')[0].childNodes[0].nodeValue);\n"
				"gateway = (xhr.responseXML.getElementsByTagName('GTW')[0].childNodes[0].nodeValue);\n"
				"mmask = (xhr.responseXML.getElementsByTagName('MASK')[0].childNodes[0].nodeValue);\n"
				"prot = (xhr.responseXML.getElementsByTagName('PRT')[0].childNodes[0].nodeValue);\n"
				"mac_addr.innerHTML = mac;\n"
				"ip_addr.innerHTML = ip;\n"
				"po_ver.innerHTML = verpo;\n"
				"gate.innerHTML = gateway;\n"
				"m_m.innerHTML = mmask;\n"
				"protocol.innerHTML = prot;\n"
			"}\n"
		"}\n"
};

extern app_os_resources_t app_os_res;

app_enet_t *apEnParam;
/*
HttpServerSettings httpServerSettings;
HttpServerContext httpServerContext;
HttpConnection httpConnections[APP_HTTP_MAX_CONNECTIONS];
TftpServerSettings tftpServerSettings;
TftpServerContext tftpServerContext;
TlsCache *tlsCache;*/
YarrowContext yarrowContext;
uint8_t seed[32];


void netCyclonTCPInit(void)
{
	NetInterface *interface;
	apEnParam = (app_enet_t *) osAllocMem(sizeof(app_enet_t));
	apEnParam->EnetParam = (Enet_Param_t *) osAllocMem(sizeof(Enet_Param_t));
	apEnParam->clientTerminalTCPSocket = (Socket *) osAllocMem(sizeof(Socket));
	apEnParam->serverTerminalTCPSocket = (Socket *) osAllocMem(sizeof(Socket));
	apEnParam->serverUDPSocket = (Socket *) osAllocMem(sizeof(Socket));
	apEnParam->clientIpAddrUDP = (IpAddr *) osAllocMem(sizeof(IpAddr));

	ReadEnet(apEnParam->EnetParam);

    error_t error;
	MacAddr macAddr;
	Ipv4Addr ipv4Addr;
/*
	 //Initialize hardware cryptographic accelerator
	error = stm32h7xxCryptoInit();
	//Any error to report?
	if(error)
	   TRACE_ERROR("Failed to initialize hardware crypto accelerator!\r\n");
	//Generate a random seed
	error = trngGetRandomData(seed, sizeof(seed));
	//Any error to report?
	if(error)
	   TRACE_ERROR("Failed to generate random data!\r\n");
	//PRNG initialization
	error = yarrowInit(&yarrowContext);
	//Any error to report?
	if(error)
	   TRACE_ERROR("Failed to initialize PRNG!\r\n");
	//Properly seed the PRNG
	error = yarrowSeed(&yarrowContext, seed, sizeof(seed));
	//Any error to report?
	if(error)
	   TRACE_ERROR("Failed to seed PRNG!\r\n");*/
	//Initialize TCP/IP stack
	error = netInit();
	//Any error to report?
	if(error)
		TRACE_INFO("Error init TCP/IP stack!\r\n");

	//Configure the first Ethernet interface
	interface = &netInterface[0];
	//Set interface name
	netSetInterfaceName(interface, APP_IF_NAME);
    //Set host name
	netSetHostname(interface, APP_HOST_NAME);
	//Select the relevant network adapter
	netSetDriver(interface, &stm32h7xxEthDriver);
	netSetPhyDriver(interface, &ksz8081PhyDriver);
    //Set host MAC address
	macStringToAddr(apEnParam->EnetParam->myMAC, &macAddr);
	netSetMacAddr(interface, &macAddr);

	//Initialize network interface
	error = netConfigInterface(interface);
	//Failed to configure the interface?
	if(error)
		TRACE_INFO("Error config Interface!\r\n");

    //Set IPv4 host address
    ipv4StringToAddr(apEnParam->EnetParam->myIP, &ipv4Addr);
    ipv4SetHostAddr(interface, ipv4Addr);
    //Set subnet mask
    ipv4StringToAddr(apEnParam->EnetParam->myMASK, &ipv4Addr);
    ipv4SetSubnetMask(interface, ipv4Addr);
    //Set default gateway
    ipv4StringToAddr(apEnParam->EnetParam->myGTW, &ipv4Addr);
    ipv4SetDefaultGateway(interface, ipv4Addr);
    while(!interface->configured);
    //TLS session cache initialization
  /*  tlsCache = tlsInitCache(8);
    //Any error to report?
    //if(tlsCache == NULL)
    //   TRACE_ERROR("Failed to initialize TLS session cache!\r\n");

    //Get default settings
    httpServerGetDefaultSettings(&httpServerSettings);
    //Bind HTTP server to the desired interface
    httpServerSettings.interface = &netInterface[0];
    //Listen to port 443
    httpServerSettings.port = apEnParam->EnetParam->Http;

    //Maximum length of the pending connection queue
    httpServerSettings.backlog = 2;
    //Client connections
    httpServerSettings.maxConnections = APP_HTTP_MAX_CONNECTIONS;
    httpServerSettings.connections = httpConnections;
    //Specify the server's root directory
    strcpy(httpServerSettings.rootDirectory, "/www/");
    //Set default home page
    strcpy(httpServerSettings.defaultDocument, "index.shtm");
    //Callback functions
   // httpServerSettings.tlsInitCallback = httpServerTlsInitCallback;
    //httpServerSettings.authCallback = httpServerAuthCallback;
    httpServerSettings.cgiCallback = httpServerCgiCallback;
    httpServerSettings.requestCallback = httpServerRequestCallback;
    httpServerSettings.uriNotFoundCallback = httpServerUriNotFoundCallback;

    //HTTP server initialization
    error = httpServerInit(&httpServerContext, &httpServerSettings);
    //Failed to initialize HTTP server?
    if(error)
          TRACE_ERROR("Failed to initialize HTTP server!\r\n");

    //Start HTTP server
    error = httpServerStart(&httpServerContext);
    //Failed to start HTTP server?
    if(error)
          TRACE_ERROR("Failed to start HTTP server!\r\n");*/

    //Get default settings
    /* tftpServerGetDefaultSettings(&tftpServerSettings);
     //Bind TFTP server to the desired interface
     tftpServerSettings.interface = &netInterface[0];
     //Listen to port 69
     tftpServerSettings.port = TFTP_PORT;
     //Open file callback function
     tftpServerSettings.openFileCallback = tftpServerOpenFileCallback;
     //Write file callback function
     tftpServerSettings.writeFileCallback = tftpServerWriteFileCallback;
     //Read file callback function
     tftpServerSettings.readFileCallback = tftpServerReadFileCallback;
     //Close file callback function
     tftpServerSettings.closeFileCallback = tftpServerCloseFileCallback;

     //TFTP server initialization
     error = tftpServerInit(&tftpServerContext, &tftpServerSettings);
     //Failed to initialize TFTP server?
     if(error)
     {
        //Debug message
        TRACE_ERROR("Failed to initialize TFTP server!\r\n");
     }

     //Start TFTP server
     error = tftpServerStart(&tftpServerContext);
     //Failed to start TFTP server?
     if(error)
     {
        //Debug message
        TRACE_ERROR("Failed to start TFTP server!\r\n");
     }*/
}

void SetNewNetConfig(Enet_Param_t *param)
{
	NetInterface *interface = &netInterface[0];
	error_t error = netStopInterface(interface);

	MacAddr macAddr;
	Ipv4Addr ipv4Addr;

	macStringToAddr(apEnParam->EnetParam->myMAC, &macAddr);
	netSetMacAddr(interface, &macAddr);
	//Set IPv4 host address
	ipv4StringToAddr(apEnParam->EnetParam->myIP, &ipv4Addr);
	ipv4SetHostAddr(interface, ipv4Addr);
	//Set subnet mask
	ipv4StringToAddr(apEnParam->EnetParam->myMASK, &ipv4Addr);
	ipv4SetSubnetMask(interface, ipv4Addr);
	//Set default gateway
	ipv4StringToAddr(apEnParam->EnetParam->myGTW, &ipv4Addr);
	ipv4SetDefaultGateway(interface, ipv4Addr);
	netStartInterface(interface);
}


void stm32h7xxEthInitGpio(NetInterface *interface)
{
   GPIO_InitTypeDef GPIO_InitStruct;
   // Клок включается в функциях HAL_Init() и MX_GPIO_Init()
   //Enable SYSCFG clock
   __HAL_RCC_SYSCFG_CLK_ENABLE();

   //Enable GPIO clocks
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();
   __HAL_RCC_GPIOC_CLK_ENABLE();
   /* Peripheral clock enable */

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // ETH_RESET_PHY (PE3)

    /*Configure GPIO pin : PE3 */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);

    //Select RMII interface mode
    HAL_SYSCFG_ETHInterfaceSelect(SYSCFG_ETH_RMII);

   //Configure RMII pins
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_ETH;

   //Configure ETH_RMII_REF_CLK (PA1), ETH_MDIO (PA2) and ETH_RMII_CRS_DV (PA7)
    GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   //Configure ETH_RMII_TXD1 (PB13), RMII_TX_EN (PB11) and ETH_RMII_TXD0 (PB12)
   GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_11 | GPIO_PIN_12;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   //Configure ETH_MDC (PC1), ETH_RMII_RXD0 (PC4) and ETH_RMII_RXD1 (PC5)
   GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5;
   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}


/**
 * @brief TLS initialization callback
 * @param[in] connection Handle referencing a client connection
 * @param[in] tlsContext Pointer to the TLS context
 * @return Error code
 **/
/*
error_t httpServerTlsInitCallback(HttpConnection *connection,
   TlsContext *tlsContext)
{
   error_t error;
   const char_t *serverCert = server_cert;
   size_t serverCertLen = sizeof(server_cert) - 1; // Вычтем нулевой символ
   const char_t *serverKey = server_key;
   size_t serverKeyLen = sizeof(server_key) - 1; // Вычтем нулевой символ

   //Set TX and RX buffer size
   error = tlsSetBufferSize(tlsContext, 2048, 2048);
   //Any error to report?
   if(error)
      return error;

   //Set the PRNG algorithm to be used
   error = tlsSetPrng(tlsContext, YARROW_PRNG_ALGO, &yarrowContext);
   //Any error to report?
   if(error)
      return error;

   //Session cache that will be used to save/resume TLS sessions
   error = tlsSetCache(tlsContext, tlsCache);
   //Any error to report?
   if(error)
      return error;

   //Client authentication is not required
   error = tlsSetClientAuthMode(tlsContext, TLS_CLIENT_AUTH_NONE);
   //Any error to report?
   if(error)
      return error;

   //Get server's certificate
   //error = resGetData(APP_HTTP_SERVER_CERT, (const uint8_t **) &serverCert,
   //   &serverCertLen);
   //Any error to report?
   //if(error)
   //   return error;

   //Get server's private key
   //error = resGetData(APP_HTTP_SERVER_KEY, (const uint8_t **) &serverKey,
   //   &serverKeyLen);
   //Any error to report?
   //if(error)
   //   return error;

   //Import server's certificate
   error = tlsAddCertificate(tlsContext, serverCert, serverCertLen, serverKey,
      serverKeyLen);
   //Any error to report?
   if(error)
      return error;

   //Successful processing
   return NO_ERROR;
}*/


/**
 * @brief HTTP authentication callback
 * @param[in] connection Handle referencing a client connection
 * @param[in] user NULL-terminated string specifying the user name
 * @param[in] uri NULL-terminated string containing the path to the requested resource
 * @return Access status (HTTP_ACCESS_ALLOWED, HTTP_ACCESS_DENIED,
 *   HTTP_BASIC_AUTH_REQUIRED or HTTP_DIGEST_AUTH_REQUIRED)
 **/

HttpAccessStatus httpServerAuthCallback(HttpConnection *connection,
   const char_t *user, const char_t *uri)
{
   HttpAccessStatus status;

   //Manage access rights
   if(pathMatch(uri, "/passwords.txt"))
   {
      //This file is not visible
      status = HTTP_ACCESS_DENIED;
   }
   else if(pathMatch(uri, "/config/*"))
   {
      //This directory is not visible
      status = HTTP_ACCESS_DENIED;
   }
   else if(pathMatch(uri, "/admin/*"))
   {
      //Only the administrator can access this directory
      if(!strcmp(user, "administrator"))
      {
         //Check the administrator password
         if(httpCheckPassword(connection, "password", HTTP_AUTH_MODE_BASIC))
            status = HTTP_ACCESS_ALLOWED;
         else
            status = HTTP_ACCESS_BASIC_AUTH_REQUIRED;
      }
      else
      {
         //Users other than administrator cannot access this directory
         status = HTTP_ACCESS_BASIC_AUTH_REQUIRED;
      }
   }
   else
   {
      //No restriction for other directories
      status = HTTP_ACCESS_ALLOWED;
   }

   //Return access status
   return status;
}


/**
 * @brief CGI callback function
 * @param[in] connection Handle referencing a client connection
 * @param[in] param NULL-terminated string that contains the CGI parameter
 * @return Error code
 **/

error_t httpServerCgiCallback(HttpConnection *connection,
   const char_t *param)
{
   static uint_t pageCounter = 0;
   uint_t length;
   MacAddr macAddr;
#if (IPV4_SUPPORT == ENABLED)
   Ipv4Addr ipv4Addr;
#endif
#if (IPV6_SUPPORT == ENABLED)
   uint_t n;
   Ipv6Addr ipv6Addr;
#endif

   //Underlying network interface
   NetInterface *interface = connection->socket->interface;

   //Check parameter name
   if(!strcasecmp(param, "PAGE_COUNTER"))
   {
      pageCounter++;
      sprintf(connection->buffer, "%u time%s", pageCounter, (pageCounter >= 2) ? "s" : "");
   }
   else if(!strcasecmp(param, "BOARD_NAME"))
   {
      strcpy(connection->buffer, "STM32H753I-EVAL");
   }
   else if(!strcasecmp(param, "SYSTEM_TIME"))
   {
      systime_t time = osGetSystemTime();
      formatSystemTime(time, connection->buffer);
   }
   else if(!strcasecmp(param, "MAC_ADDR"))
   {
      netGetMacAddr(interface, &macAddr);
      macAddrToString(&macAddr, connection->buffer);
   }
   else if(!strcasecmp(param, "IPV4_ADDR"))
   {
      ipv4GetHostAddr(interface, &ipv4Addr);
      ipv4AddrToString(ipv4Addr, connection->buffer);
   }
   else if(!strcasecmp(param, "SUBNET_MASK"))
   {
      ipv4GetSubnetMask(interface, &ipv4Addr);
      ipv4AddrToString(ipv4Addr, connection->buffer);
   }
   else if(!strcasecmp(param, "DEFAULT_GATEWAY"))
   {
      ipv4GetDefaultGateway(interface, &ipv4Addr);
      ipv4AddrToString(ipv4Addr, connection->buffer);
   }
#if (IPV6_SUPPORT == ENABLED)
   else if(!strcasecmp(param, "LINK_LOCAL_ADDR"))
   {
      ipv6GetLinkLocalAddr(interface, &ipv6Addr);
      ipv6AddrToString(&ipv6Addr, connection->buffer);
   }
   else if(!strcasecmp(param, "GLOBAL_ADDR"))
   {
      ipv6GetGlobalAddr(interface, 0, &ipv6Addr);
      ipv6AddrToString(&ipv6Addr, connection->buffer);
   }
   else if(!strcasecmp(param, "IPV6_PREFIX"))
   {
      ipv6GetPrefix(interface, 0, &ipv6Addr, &n);
      ipv6AddrToString(&ipv6Addr, connection->buffer);
      length = strlen(connection->buffer);
      sprintf(connection->buffer + length, "/%u", n);
   }
   else if(!strcasecmp(param, "ROUTER"))
   {
      ipv6GetDefaultRouter(interface, 0, &ipv6Addr);
      ipv6AddrToString(&ipv6Addr, connection->buffer);
   }
   else if(!strcasecmp(param, "IPV6_PRIMARY_DNS"))
   {
      ipv6GetDnsServer(interface, 0, &ipv6Addr);
      ipv6AddrToString(&ipv6Addr, connection->buffer);
   }
   else if(!strcasecmp(param, "IPV6_SECONDARY_DNS"))
   {
      ipv6GetDnsServer(interface, 1, &ipv6Addr);
      ipv6AddrToString(&ipv6Addr, connection->buffer);
   }
#endif
   else
   {
      return ERROR_INVALID_TAG;
   }

   //Get the length of the resulting string
   length = strlen(connection->buffer);

   //Send the contents of the specified environment variable
   return httpWriteStream(connection, connection->buffer, length);
}


/**
 * @brief HTTP request callback
 * @param[in] connection Handle referencing a client connection
 * @param[in] uri NULL-terminated string containing the path to the requested resource
 * @return Error code
 **/

error_t httpServerRequestCallback(HttpConnection *connection,
   const char_t *uri)
{
   error_t error;
   size_t n;
   char_t buffer[256];
   if(!strcmp(uri, "index.shtm"))
   {
	   return httpServerAnswer(connection, ".shtm", str_html, sizeof(str_html));
   }
   else if (!strcmp(uri, "/css/demo.css"))
   {
	   return httpServerAnswer(connection, ".css", demo_css, sizeof(demo_css));
   }
   else if (!strcmp(uri, "/css/reset.css"))
   {
		return httpServerAnswer(connection, ".css", reset_css, sizeof(reset_css));
   }
   else if (!strcmp(uri, "/favicon.ico"))
   {
		return httpServerAnswer(connection, ".png", favicon_ico, sizeof(favicon_ico));
   }
   else if (!strcmp(uri, "/js/ReleEth.js"))
   {
	   return httpServerAnswer(connection, ".js", script, sizeof(script) - 1);
   }
   //Process data.xml file?
   else if(!strcasecmp(uri, "/data.xml"))
   {
      //Format XML data
      n = sprintf(buffer, "<data>\r\n");
      n += sprintf(buffer + n, "  <IP>%s</IP>\r\n", apEnParam->EnetParam->myIP);
      n += sprintf(buffer + n, "  <MAC>%s</MAC>\r\n", apEnParam->EnetParam->myMAC);
      n += sprintf(buffer + n, "  <MASK>%s</MASK>\r\n", apEnParam->EnetParam->myMASK);
      n += sprintf(buffer + n, "  <GTW>%s</GTW>\r\n", apEnParam->EnetParam->myGTW);
      n += sprintf(buffer + n, "  <PRT>%s</PRT>\r\n", apEnParam->EnetParam->Http == HTTPS_PORT ? "HTTPS" :
    		  	  	  	  	  	  	  	  	  	  	  (apEnParam->EnetParam->Http == HTTP_PORT ? "HTTP" : "Error"));
      n += sprintf(buffer + n, "  <VER_PO>%s</VER_PO>\r\n", PO_VER);
      n += sprintf(buffer + n, "</data>\r\n");

      return httpServerAnswer(connection, ".xml", buffer, n);
   }
   else if (!strcmp(uri, "/post_ind.html"))
   {
	   size_t len_recieved;
	   char_t *buffer = osAllocMem(512);

	   error = httpReadStream(connection, buffer, 512, &len_recieved, HTTP_FLAG_BREAK_CRLF);

	   setNewParam(buffer, len_recieved);

	   osFreeMem(buffer);

	   char_t URI[23] = { "http://" };

	   strcpy(&URI[7], apEnParam->EnetParam->myIP);

	   error = httpSendRedirectResponse(connection, 303, URI);

	   return error; //Return status code
   }
   else
   {
      //The requested resource cannot be found
      return ERROR_NOT_FOUND;
   }
}


/**
 * @brief URI not found callback
 * @param[in] connection Handle referencing a client connection
 * @param[in] uri NULL-terminated string containing the path to the requested resource
 * @return Error code
 **/

error_t httpServerUriNotFoundCallback(HttpConnection *connection,
   const char_t *uri)
{
   //Not implemented
   return ERROR_NOT_FOUND;
}


error_t httpServerAnswer(HttpConnection *connection, const char_t *filename,  const void *data, size_t length)
{
	  error_t error;
	  //Format HTTP response header
	  connection->response.version = connection->request.version;
	  connection->response.statusCode = 200;
	  connection->response.keepAlive = connection->request.keepAlive;
	  connection->response.noCache = TRUE;
	  connection->response.contentType = mimeGetType(filename);
	  connection->response.chunkedEncoding = FALSE;
	  connection->response.contentLength = length;

	  //Send the header to the client
	  error = httpWriteHeader(connection);
	  //Any error to report?
	  if(error)
		 return error;

	  //Send response body
	  error = httpWriteStream(connection, data, length);
	  //Any error to report?
	  if(error)
		 return error;

	  //Properly close output stream
	  error = httpCloseStream(connection);
	  //Return status code
	  return error;
}

uint8_t setNewParam(char_t *data, size_t length)
{
	char_t *temp;

	if(comparePasswords(data, length))  // если пароли совпали, то можно проверять остальные параметры
	{
		uint8_t flagforsave = 0;
		char_t *temp2;

		temp = getValueByTagName( data, "&MAC=", length);
		if(temp)
		{
			temp2 = strnstr(temp, "&", sizeof(apEnParam->EnetParam->myMAC));
			uint8_t forMAC[18] = {[17] = '\0'};
			memcpy(forMAC, temp, temp2 - temp);
			MacAddr macAddrNew;
			error_t error = macStringToAddr(forMAC, &macAddrNew);
			if (!error)
			{
				memcpy(apEnParam->EnetParam->myMAC, forMAC, 18);
				flagforsave = 1;
			}
		}

		temp = getValueByTagName( data, "&IP=", length);
		if(temp)
		{
			temp2 = strnstr(temp, "&", sizeof(apEnParam->EnetParam->myIP));
			uint8_t forIP[16] = {[15] = '\0'};
			memcpy(forIP, temp, temp2 - temp);
			Ipv4Addr ipv4Addrnew;
			error_t error = ipv4StringToAddr(forIP, &ipv4Addrnew);
			if (!error)
			{
				memcpy(apEnParam->EnetParam->myIP, forIP, 16);
				flagforsave = 1;
			}
		}

		temp = getValueByTagName( data, "&S_MASK=", length);
		if(temp)
		{
			temp2 = strnstr(temp, "&", sizeof(apEnParam->EnetParam->myMASK));
			uint8_t forIP[16] = {[15] = '\0'};
			memcpy(forIP, temp, temp2 - temp);
			Ipv4Addr ipv4Addrnew;
			error_t error = ipv4StringToAddr(forIP, &ipv4Addrnew);
			if (!error)
			{
				memcpy(apEnParam->EnetParam->myMASK, forIP, 16);
				flagforsave = 1;
			}
		}

		temp = getValueByTagName( data, "&D_GTW=", length);
		if(temp)
		{
			temp2 = strnstr(temp, "&", sizeof(apEnParam->EnetParam->myGTW));
			uint8_t forIP[16] = {[15] = '\0'};
			memcpy(forIP, temp, temp2 - temp);
			Ipv4Addr ipv4Addrnew;
			error_t error = ipv4StringToAddr(forIP, &ipv4Addrnew);
			if (!error)
			{
				memcpy(apEnParam->EnetParam->myGTW, forIP, 16);
				flagforsave = 1;
			}
		}

		temp = getValueByTagName( data, "&NEW_PAS=", length);
		if(temp)
		{
			temp2 = getValueByTagName( data, "&CONF_PAS=", length);
			if (temp2)
			{
				char_t *temp3 = strnstr(temp, "&", 9);
				if(!strncmp(temp, temp2, temp3 - temp))    // Если пароли совпадают, то копируем пароль
				{
					memcpy(apEnParam->EnetParam->myPassword, temp, temp3 - temp);
					flagforsave = 1;
				}
			}
		}
		if(flagforsave)
		{
			char const * tkn_arr [1] = {"save"};
			execute (1, tkn_arr);
			SetNewNetConfig(apEnParam->EnetParam);
			return 1;
		}
	}
	return 0;
}

char_t * getValueByTagName( const char_t *sourse, const char_t *dest, size_t length)
{
	char_t *temp = strnstr(sourse, dest, length);

	if(temp)
	{
		uint32_t len = strlen(dest);
		temp += len;
		if(*temp == '&') return NULL;
		if( temp - sourse >= length) return NULL; // на случай достижения конца данных
	}
	return temp;
}

uint8_t comparePasswords(char_t *data, size_t length)
{
	char_t *temp = getValueByTagName( data, "&U_PAS=", length);

	if(temp)
		if( !strncmp(temp, apEnParam->EnetParam->myPassword, strlen(apEnParam->EnetParam->myPassword)) )
			return 1;

	return 0;
}

void vTCPTask( void *pvParametrs )
{
	error_t error;
	size_t length;

	//Create a connectionless socket
	apEnParam->serverTerminalTCPSocket = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);
	//Failed to create socket?
	if(!apEnParam->serverTerminalTCPSocket)
		//TRACE_INFO("Error to open TCP socket! Error: %u\n", apEnParam->serverTerminalTCPSocket);
	//Define a 15s timeout for all blocking operations
	error = socketSetTimeout(apEnParam->serverTerminalTCPSocket, INFINITE_DELAY);
	//Any error to report?
	if( error)
		//TRACE_INFO("Error to set timeout for TCP socket! Error: %u\n", error);
	//Use a large buffer for transmitting data
	error = socketSetTxBufferSize(apEnParam->serverTerminalTCPSocket, 1024);
	//Any error to report?
	if(error)
		//TRACE_INFO("Error to set Tx Buffer for TCP socket! Error: %u\n", error);
	error = socketSetRxBufferSize(apEnParam->serverTerminalTCPSocket, 536);
	//Any error to report?
	if(error)
		//TRACE_INFO("Error to set Tx Buffer for TCP socket! Error: %u\n", error);
	error = socketBindToInterface(apEnParam->serverTerminalTCPSocket, &netInterface[0]);
	if(error)
		//TRACE_INFO("Error to bind to interface TCP socket! Error: %u\n", error);
	//Bind the newly created socket to port 23
	error = socketBind(apEnParam->serverTerminalTCPSocket, &IP_ADDR_ANY, 23);
	if(error)
		//TRACE_INFO("Error to bind TCP socket! Error: %u\n", error);
	//Place socket in listening state
	error = socketListen(apEnParam->serverTerminalTCPSocket, 0);
	//Any error to report?
	if(error)
		//TRACE_INFO("Error to listen TCP socket! Error: %u\n", error);

	for( ;; )
	{
		//Accept an incoming connection
		apEnParam->clientTerminalTCPSocket = socketAccept(apEnParam->serverTerminalTCPSocket,
														  &apEnParam->clientIpAddr,
														  &apEnParam->clientPort);
		if(apEnParam->clientTerminalTCPSocket != NULL)
		{
			uint8_t *bufferTCP = osAllocMem(100);
			while(apEnParam->clientTerminalTCPSocket->state != TCP_STATE_CLOSED &&
				  apEnParam->clientTerminalTCPSocket->state != TCP_STATE_CLOSE_WAIT)
			{
				  error = socketReceive(apEnParam->clientTerminalTCPSocket, bufferTCP, 100,
							  &length, SOCKET_FLAG_PEEK );
				  if (error == NO_ERROR)
				  {
					  for(uint32_t i = 0; i < length; i++)
						xQueueSend( app_os_res.xQueueRX_TCP_MRL, &bufferTCP[i], 0 );
				  }
			}
			socketClose(apEnParam->clientTerminalTCPSocket);
		    osFreeMem(bufferTCP);
		}
	}
	vTaskDelay( 20 );
}
