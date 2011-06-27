import posix_ipc
import struct
fmt='=BBB'
INIT= 	1
READ= 	2
WRITE= 	3
EXIT= 	4


DATA= 	1
STAT= 	2
CTRL=	3
q1=posix_ipc.MessageQueue('/my_send_q',flags=posix_ipc.O_CREAT,max_message_size=3,write=False)
q2=posix_ipc.MessageQueue('/my_rcv_q',flags=posix_ipc.O_CREAT,max_message_size=3,read=False)
m1=struct.pack(fmt,INIT,0,0)
print str(m1)
q2.send(m1)

lst=['','DATA','STATUS','CONTROL']
while(True):
    m1=q1.receive()[0]
    #print m1
    op,port,dat=struct.unpack(fmt,m1)
    if(op==EXIT):
        break
    if op==WRITE:
        print 'write operation',lst[port],dat
    if op==READ:
        print 'read operation',lst[port]
        dat=input('Enter data\n')
        m1=struct.pack(fmt,op,port,dat)
        q2.send(m1)

q1.unlink()
q2.unlink()
