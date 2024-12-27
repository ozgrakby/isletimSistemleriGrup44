/*
44 Nolu Grup
B231210384 Hamide Yortanlı 
B201210077 Muhammed Emin Çetin 
B221210402 Samet Ayan 
G221210005 Özgür Akbay 
G221210055 Yavuz Selim Ateş
*/

#include "arkaplancalisma.h"

#define MAX_BACKGROUND_PROCESSES 1024

typedef struct {
    pid_t pid;
    int active;
} BackgroundProcess;

BackgroundProcess bg_processes[MAX_BACKGROUND_PROCESSES];
int bg_process_count = 0;
volatile sig_atomic_t quit_requested = 0;

void handle_signal(int sig) {
    if (sig == SIGCHLD) {
        int status;
        pid_t pid = waitpid(-1, &status, WNOHANG);  // Bekleyen herhangi bir çocuk
        if (pid > 0) {
            // Çocuk süreç sona erdiğinde çıktı bilgisi
            printf("[%d] retval: %d\n", pid, WEXITSTATUS(status));
        }
    }
}
void arkaplan_calisma(char **komut) {
    pid_t pid = fork();  // Çocuk süreç oluşturuluyor

    if (pid == -1) {
        perror("Fork işlemi başarısız");
        exit(1);
    }

    if (pid == 0) {
        // Çocuk süreçte komut çalıştırılacak
        if (execvp(komut[0], komut) == -1) {
            perror("Execvp hatası");
            exit(1);  // Komut bulunamazsa veya hata oluşursa süreç sonlanır
        }
    }
    // Ana süreç burada çalışmaya devam eder, çocuk süreç arka planda çalışır
}