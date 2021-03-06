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

char message[] = "set "; //Запрос, который отправится 
char buf[64];

int main(int argc, char *argv[])
{
	 if ( argc != 3 ) //Если количество аргументов не равно 3
    {
        //Написать подсказку для пользователя
        printf( "usage: %s <key> <value>\n", argv[0] );
        exit(1);
    }
    int sock; //Сокет
    struct sockaddr_in addr; //Адрес сервера

    sock = socket(AF_INET, SOCK_STREAM, 0);//инициализация сокета
    if(sock < 0)//Если ошибка
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET; //Указываем тип адреса
    addr.sin_port = htons(1978); //Указываем порт
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // INADDR_LOOPBACK = 127.0.0.1


    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }
    else printf("Connected to server\n");

    strcat(message, argv[1]); // Добавляем ключ
    strcat(message, " 0 0 ");
	// flags = 0 — произвольное 16-битное целое число, которое сервер хранит вместе с данными и возвращает его, когда клиент извлекает значение ключа

	// exptime = 0 — время жизни ключа. Указывается в секундах. Если задан 0, ключ будет жить до тех пор, пока система не удалит его, освобождая место для новых ключей. 

    char str[100];
    sprintf(str,"%d",strlen(argv[2])); // Записываем длину значения value
    strcat(message, str); // Добавляем количество байt значения

    strcat(message, "\r\n");
    strcat(message, argv[2]); // Добавляем значение value
    strcat(message, "\r\n");

	printf("%s\n",message); // Выводим сообщение

    send(sock, message, strlen(message), 0);//Отправляем  сообщение в сокет
    recv(sock, buf, 12, 0);//Получаем ответ (12 байт) от сокета и сохраняем в buf
    

    printf(buf);

    close(sock);//Закрываем сокет

	return 0;
}
