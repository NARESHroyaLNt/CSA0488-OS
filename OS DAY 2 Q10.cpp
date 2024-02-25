#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message.h"
int main() {
    int msgid;
    message msgToSend;
    msgid = msgget(MSG_KEY, 0644 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }
    msgToSend.msgType = 1; 
    strcpy(msgToSend.msgText, "Hello, world!");
    if (msgsnd(msgid, &msgToSend, sizeof(msgToSend.msgText), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("Sender: Message sent\n");
    return 0;
}

