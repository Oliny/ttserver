#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <tcrdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <tcrdb.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <tcutil.h>
#include <tchdb.h>
#include <fcntl.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
void error(const char *msg) //функция для ошибок
{
    perror(msg);
    exit(0);
}

char message[] = "set "; //Запрос, который отправится 
char buf[64];

int main(int argc, char *argv[])
{
	 if ( argc < 3 ) //Если количество аргументов меньше 3
    {
       
        printf( "usage: %s <key> <value>\n", argv[0] );
        exit(1);
    }
    int sockfd, portno; //Сокет и номер порта
    struct sockaddr_in addr; //Адрес сервера
    struct hostent *server;//
    sockfd = socket(AF_INET, SOCK_STREAM, 0);//инициализация сокета
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    addr.sin_family = AF_INET; //Указываем тип адреса
    addr.sin_port = htons(1978); //Указываем порт
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // INADDR_LOOPBACK = 127.0.0.1
    if(connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    error("ERROR connecting");
    else printf("Connected to server\n");

    strcat(message, argv[1]); // Добавляем ключ
    strcat(message, " 0 0 ");
	// flags = 0 — произвольное 16-битное целое число, которое сервер хранит вместе с данными и возвращает его, когда клиент извлекает значение ключа

	// exptime = 0 — время жизни ключа. Указывается в секундах. Если задан 0, ключ будет жить до тех пор, пока система не удалит его, освобождая место для новых ключей. 

    char str[100];
    
    sprintf(str,"%i",strlen(argv[2])); // Записываем длину значения value
    strcat(message, str); // Добавляем количество байт значения

    strcat(message, "\r\n");
    strcat(message, argv[2]); // Добавляем значение value
   strcat(message, "\r\n");

	printf("%s\n",message); // Выводим сообщение

    send(sockfd, message, strlen(message), 0);//Отправляем  сообщение в сокет
    recv(sockfd, buf, 12, 0);//Получаем ответ (12 байт) от сокета и сохраняем в buf
    

    printf(("%s"),buf);

    close(sockfd);//Закрываем сокет

	return 0;
}
