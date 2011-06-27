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
};

int init();
void msg_write(int ops,char ports,unsigned char val);
struct message msg_read();
void finish();
