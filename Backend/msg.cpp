#include "mqueue.h"
#include <stdlib.h>
#include <stdio.h>
mqd_t q1,q2;

/// Operation
#define INIT 	1
#define READ 	2
#define WRITE 	3
#define EXIT 	4

/// Port
#define DATA 	1
#define STAT 	2
#define CTRL	3

struct message
{
	char op;
	char port;
	unsigned char value;
}m1,m2;

int init()
{
	char msg[30];
	struct mq_attr tmp;
	printf("in msg Q init\n");
	q1=mq_open("/my_send_q",O_WRONLY);
	q2=mq_open("/my_rcv_q",O_RDONLY|O_NONBLOCK);
	
	if(q1==-1 || q2==-1)
	{
		//printf("cannot open q\n");
		return -1;
	}
	if(mq_receive(q2,(char *)&m1,sizeof(m1),NULL)==-1)
	{
		//perror("");
		//printf("cannot get init message\n");
		return -2;
	}
	mq_close(q2);
	q2=mq_open("/my_rcv_q",O_RDONLY);
	
	return 0;
}
void msg_write(int ops,char ports,unsigned char val)
{
	m1.op=ops;
	m1.port=ports;
	m1.value=val;
	mq_send(q1,(char*) &m1,sizeof(m1),1);
}

struct message msg_read()
{
	struct message tmp;
	mq_receive(q2,(char*)&tmp,sizeof(tmp),NULL);
	return tmp;
}

void finish()
{
	m1.op=EXIT;
	m1.port=DATA;
	mq_send(q1,(char*)&m1,sizeof(m1),1);
	mq_close(q1);
	mq_close(q2);
}

