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

int main()
{
	TCRDB *rdb;
  	int ecode, pksiz, i, rsiz;

	rdb = tcrdbnew();

	if(!tcrdbopen(rdb, "localhost", 1978))
	{
    	ecode = tcrdbecode(rdb);
    	printf("open error: %s\n", tcrdberrmsg(ecode));
  	}

	
	tcrdbput2(rdb, "key", "value");

	 if(!tcrdbclose(rdb))
	{
    	ecode = tcrdbecode(rdb);
 	    printf("close error: %s\n", tcrdberrmsg(ecode));
  	}

	tcrdbdel(rdb);
	return 0;
}
