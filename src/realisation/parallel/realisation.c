//
// Created by gallaann on 01.04.2022.
//

#include "../realisation.h"
#include "sys/msg.h"
#include "unistd.h"
#include "sys/wait.h"

#define mtype_const 512U

typedef struct{
    long mtype;
    double length;
}msgbuf;

void send_message(int qid, msgbuf *qbuf, long type) {
    qbuf->mtype = type;
    if (msgsnd(qid, qbuf, sizeof(qbuf->length), 0) == -1) {
        exit(EXIT_FAILURE);
    }
}
void read_message(int qid, msgbuf *qbuf, long type) {
    qbuf->mtype = type;
    if (msgrcv(qid, qbuf, sizeof(qbuf->length), qbuf->mtype, 0) == -1){
        exit(EXIT_FAILURE);
    }
}

int work(size_t amount){
    scanf ("%li",&amount);

    FILE* file = fopen("../input_file.txt", "r");
    if (!file){
        return -1;
    }

    Storage storage = storage_constructor(amount);
    fill_storage(&storage,file);

    int msgqid;
    if ((msgqid = msgget(IPC_PRIVATE, IPC_CREAT|0660)) == -1) { // queue creation error
        return -1;
    }

    int pid[amount];
    msgbuf qbuf;
    int qtype = 1;
    size_t number_of_processors = sysconf(_SC_NPROCESSORS_ONLN); // gives number of cores online

    for (int i = 1; i < number_of_processors; ++i) {
        pid[i] = fork();

        if (-1 == pid[i]) { // error
            return -1;
        }

        if (0 == pid[i]) {
            qbuf.mtype = mtype_const;
            qbuf.length = length(storage.points[i]);
            send_message(msgqid, &qbuf, qtype);
            exit(EXIT_SUCCESS);
        }
    }

    int status;
    int stat;

    for (int i = 1; i < number_of_processors; ++i) {
        status = waitpid(pid[i], &stat, 0);
        if (pid[i] != status) { // Child process pid[i] didn't exited
            free_storage(&storage);
            return -1;
        }
    }

    for (int i = 1; i < number_of_processors; ++i) {
        read_message(msgqid, &qbuf, qtype);
        storage.length[i-1] = qbuf.length;
    }

    if (msgctl(msgqid, IPC_RMID, NULL) < 0) { //queue removal error
        return -1;
    }

    print_storage(&storage);

    free_storage(&storage);
    fclose(file);

    return 1;
}