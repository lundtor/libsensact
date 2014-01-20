#include <stdio.h>
#include <unistd.h>
#include "ble_update.h"
#include <sys/shm.h>

#define SHM_KEY 1234

// Usage: ./ble_demo <ble_address>

int main(int argc, const char* argv[]) {

    float *ble_temp;

    //update_loop("BC:6A:29:AB:41:36", &ble_temp);
    //update_loop("BC:6A:29:C3:3C:79", &ble_temp);

    // Write temperature to shared memory
    int shmid = shmget((key_t) SHM_KEY, sizeof(float),
                       0666 | IPC_CREAT);
    if (shmid == -1) {
        printf("shmget failed\n");
    }

    ble_temp = shmat(shmid, (void *) 0, 0);

    *ble_temp = 0;

    update_loop((char *) argv[1], ble_temp);

    // never reached

    return 0;
}