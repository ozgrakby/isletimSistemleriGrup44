#include "girisyonlendirme.h"


// bu fonksiyon "<" sembolünü algılar, dosyayı açar ve okur
void giris_yonlendirme(char **komut)
{
    int i=0;
    int dosya_betimleyici;

    while (komut[i] != NULL) // buradaki while, komut dizisini Null okuyana kadar tarar
    {
        if(strcmp(komut[i], "<") == 0) // Komut dizisinde "<" sembolünü arayan if yapısı
        {
            if(komut[i+1] == NULL) // "<" sembolünden sonra karakter yoksa hata yazdıran if yapısı
            {
                fprintf(stderr, "Gerekli argüman yok!\n");
                return;
            }
        

            dosya_betimleyici = open(komut[i+1], O_RDONLY); // dosyayı okuma modunda açtığımız kısım
            if(dosya_betimleyici < 0)// dosyanın açılıp açılmadığını kontrol eder
            {
                perror  ("Giriş dosyası açılamadı");
                return;
            }

            dup2(dosya_betimleyici, STDIN_FILENO);//Dosyayı okuduğumuz kısım
            close(dosya_betimleyici);// dosyayı kapatıyoruz

            komut[i] = NULL; // "<" sembolünü Null yaparak komut dizisinden kaldırıyoruz, böylece yönlendirme işleminden sonra dikkate alınmaz
            break;
        }
        i++;
    }
    
    if(tekli_komut(komut)==0)//Eğer komut çalıştırılmadıysa hata verir
    {
        fprintf(stderr,"Komut yürütülemiyor!n");
    }
}