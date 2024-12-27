#include "prompt.h"
#include "girisyonlendirme.h"

//Kabuktaki her döngüde ekrana ">" karakterini basar. 
//Aynı zamanda buffer boşaltırlarak ">" karakterinin hemen yazılması sağlanır.
void prompt_yazdir(){
    printf("> ");
    fflush(stdout);
}

//Kabukta bulunan bir built-in komuttur.
//Kabuktan çıkış işini yapar.
void quit(){
    exit(0);
}

//Kabukta bulunan bir diğer built-in komuttur.
//Kabuğun dizin değiştirmesini sağlar.
void cd(char **komut){
    if(komut[1] == NULL){
        fprintf(stderr, "Gerekli arguman yok!\n");
    }
    else{
        if(chdir(komut[1]) != 0){
            perror("Dizin degisikligi basarisiz");
        }
    }
}

//Kabukta tekli komutları çalıştırır.
//Alt proses üretir ve onun bitmesini bekler.
//Aynı zamanda prosesin sonucunu ekrana yazar.
int tekli_komut(char **komut){
    pid_t child_pid = fork();
    if(child_pid == 0){
        if(execvp(komut[0], komut) == -1){
            perror("Komut bulunamadi");
            kill(getpid(), SIGTERM);
        }
    }
    else if(child_pid < 0){
        perror("Fork islemi basarisiz!");
        return 0;
    }
    else{
        waitpid(child_pid, NULL, 0);
        return 1;
    }
}

//Kabukta istenilen farklı işlevlerin yerine getirmesini sağlar.
//Girilen komutun istenilen hangi işlevi gerçekleştireceğine 
//karar vererek gerekli fonksiyon çağrımlarını yapar.
int komut_yurutucu(char **komut){
    int i = 0;
    int j = 0;

    if(komut[0] == NULL){
        return 0;
    }
    if(strcmp(komut[0], "quit") == 0){
        quit();
    }
    if(strcmp(komut[0], "cd") == 0){
        cd(komut);
        return 1;
    }
    while(komut[j] != NULL){
        if(strcmp(komut[j],"&") == 0){
            //ARKAPLANDA CALISMA
            return 1;
        }
        else if(strcmp(komut[j],"<") == 0){
            if(komut[i+1] == NULL){
                printf("Yeteri kadar arguman yok!\n");
            }
            giris_yonlendirme(komut);
            return 1;
        }
        else if(strcmp(komut[j],">") == 0){
            if(komut[j+1] == NULL){
                printf("Yeteri kadar arguman yok!\n");
            }
            //CIKIS YONLENDIRME
            return 1;
        }
        else if(strcmp(komut[j], "|" == 0)){
            char* komut1[j + 1];
            for(int x = 0 ; x < j ; x ++)
                komut1[x] = komut[x];
            
            komut1[j] = NULL;

            int k = 0;
            int komut2_size = 0;
            while(komut[j + 1 + komut2_size] != NULL)
                komut2_size++;
            
            char* komut2[komut2_size + 1];
            for(int x = j + 1; komut[x] != NULL ; x ++){
                komut2[k] = komut[x];
                k++
            }
            komut2[k] = NULL;

            pid_t child_fork = fork();
            if(child_pid == 0){
                komut_yurutucu(komut1);
            }
            else if(child_pid < 0){
                perror("Fork islemi basarisiz!");
                return 0;
            }
            else{
                waitpid(child_pid, NULL, 0);
                komut_yurutucu(komut2);
                return 1;
            }
        }
        j++;
    }
    if(komut[j] == NULL){
        return tekli_komut(komut);
    }
}
