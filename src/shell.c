#include "prompt.h"

#define MAX_KOMUT_UZUNLUK 1024
#define MAX_ARG 256

int main(){
    char line[MAX_KOMUT_UZUNLUK];
    char *komut[MAX_ARG];

    while(1){
        //Kabuktaki her döngüde ekrana ">" karakterini basar. 
        prompt_yazdir();

        //Kabuğun çalışmaya başladığı dizini statik bir değişkene atar.
        getcwd(currDir, 1024);
        
        //Kabuğa girilenleri char* bir değişkene alır.
        if(fgets(line, MAX_KOMUT_UZUNLUK, stdin) == NULL){
            break;
        }

        size_t uzunluk = strlen(line);
        if(uzunluk > 0 && line[uzunluk-1] == '\n'){
            line[uzunluk-1] = '\0';
        }

        //Kabukta aldığı girilen aragümanlar boşluklar ile ayırarak ayrı ayrı bir dizide saklar. 
        int sayac = 0;
        komut[sayac] = strtok(line, " ");
        while(komut[sayac] != NULL){
            sayac++;
            komut[sayac] = strtok(NULL, " ");
        }

        //Kabuğa girilen komudu gerekli işlemlerden geçirdikten sonra 
        //girilen komudun işini yapması için komut yürütücü fonksiyona atar.
        komut_yurutucu(komut);
    }
}