/* J. David's webserver */
/* This is a simple webserver.
 * Created November 1999 by J. David Blackstone.
 * CSE 4344 (Network concepts), Prof. Zeigler
 * University of Texas at Arlington
 */
/* This program compiles for Sparc Solaris 2.6.
 * To compile for Linux:
 *  1) Comment out the #include <pthread.h> line.
 *  2) Comment out the line that defines the variable newthread.
 *  3) Comment out the two lines that run pthread_create().
 *  4) Uncomment the line that runs accept_request().
 *  5) Remove -lsocket from the Makefile.
 */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <cstdlib>
#include <pthread.h>
#include "common.h"

void error_die(const char *sc)
{
    perror(sc);
    exit(1);
}

/**********************************************************************/
/* This function starts the process of listening for web connections
 * on a specified port.  If the port is 0, then dynamically allocate a
 * port and modify the original port variable to reflect the actual
 * port.
 * Parameters: pointer to variable containing the port to connect on
 * Returns: the socket */
/**********************************************************************/
int startup(u_short *port)
{
    int httpd = 0;
    int on = 1;
    struct sockaddr_in name;

    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        error_die("socket");
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
    {
        error_die("setsockopt failed");
    }
    if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
        error_die("bind");
    if (*port == 0)  /* if dynamically allocating a port */
    {
        socklen_t namelen = sizeof(name);
        if (getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1)
            error_die("getsockname");
        *port = ntohs(name.sin_port);
    }
    if (listen(httpd, 5) < 0)
        error_die("listen");
    return(httpd);
}

void * accept_request(void * args){

    int client_sock = (intptr_t) args;

    char buf[1024];
    recv(client_sock, buf, sizeof(buf), 0);
    char * ptr = buf;
    while(*ptr && *ptr!='\n'){if(*ptr==' ')*ptr=0;ptr++;}
    if( strlen(buf + 6) != 64 ){
        close(client_sock);
        return nullptr;
    }
    char * ret = httpd_callback(buf + 6);
    if( ret == nullptr) return nullptr;
    strcpy(buf, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nAccess-Control-Allow-Origin: *\r\n\r\n");
    strcat(buf, ret);
    delete[] ret;
    send(client_sock, buf, strlen(buf), 0);
    printf("ok\n");
    close(client_sock);
    return nullptr;

}

int httpd_main(void) {

    int server_sock = -1;
    u_short port = 4000;
    int client_sock = -1;
    struct sockaddr_in client_name;
    socklen_t  client_name_len = sizeof(client_name);
    pthread_t newthread;

    server_sock = startup(&port);
    printf("httpd running on port %d\n", port);

    while (1)
    {
        client_sock = accept(server_sock,
                             (struct sockaddr *)&client_name,
                             &client_name_len);
        if (client_sock == -1)
            error_die("accept");
        /* accept_request(&client_sock); */

        pthread_create(&newthread , NULL, accept_request, (void *)(intptr_t)client_sock);
    }
    close(server_sock);
    return(0);
}