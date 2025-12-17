#define _GNU_SOURCE

#include <arpa/inet.h>
#include <dlfcn.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#define BUFFER_LEN 1024

char* current_time() {
	time_t rawtime;
	char* cur_time = malloc(9);
	if (!cur_time) return NULL;
	struct tm* info;
	time(&rawtime);
	info = localtime(&rawtime);
	sprintf(cur_time, "%02d:%02d:%02d", info->tm_hour, info->tm_min, info->tm_sec);
	return cur_time;
}

int filterhost(char* host) {
	if (strstr(host, "akamai")) return 1;
	if (strstr(host, "amazon")) return 1;
	if (strstr(host, "cloudfront")) return 1;
	if (strstr(host, "googleusercontent")) return 1;
	if (strstr(host, "doubleclick")) return 1;
	if (strstr(host, "doubleverify")) return 1;
	if (strstr(host, "outbrain")) return 1;
	if (strstr(host, "gigya")) return 1;
	if (strstr(host, "pnbomb")) return 1;
	if (strstr(host, "100.net")) return 1;
	return 0;
}

typedef int (*orig_connect_t)(int, const struct sockaddr*, socklen_t);

int connect(int socket, const struct sockaddr* address, socklen_t address_len) {
	orig_connect_t orig_connect = NULL;
	orig_connect = dlsym(RTLD_NEXT, "connect");
	if (address->sa_family == AF_UNIX) {
		return orig_connect(socket, address, address_len);
	}

	struct sockaddr_in* myaddr = (struct sockaddr_in*)address;
	struct sockaddr_in6* myaddr6 = (struct sockaddr_in6*)address;

	char* fam = "OTHER";
	if (address->sa_family == AF_INET)
		fam = "AF_INET";
	else if (address->sa_family == AF_INET6)
		fam = "AF_INET6";

	char address_str[BUFFER_LEN] = {0};
	if (address->sa_family == AF_INET)
		inet_ntop(address->sa_family, &(myaddr->sin_addr.s_addr), address_str, BUFFER_LEN);
	else if (address->sa_family == AF_INET6)
		inet_ntop(address->sa_family, &(myaddr6->sin6_addr.s6_addr), address_str, BUFFER_LEN);

	char host[BUFFER_LEN] = {0};
	char server[BUFFER_LEN] = {0};
	getnameinfo(address, address_len, host, BUFFER_LEN, server, BUFFER_LEN, 0);

	if (filterhost(host)) {
		errno = ECONNREFUSED;
		return -1;
	}

	printf("\e[0;36m(%s)\e[1;31m[SHIMS]\e[0;33m %s (%s) %s\e[0m\n", current_time(), host, fam, address_str);
	return orig_connect(socket, address, address_len);
}
