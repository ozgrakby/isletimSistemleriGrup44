#include "cikisyonlendirme.h"

// Bu fonksiyon ">" sembolünü algılar ve çıkışı belirtilen dosyaya yönlendirir
void cikis_yonlendirme(char **komut) {
    int i = 0;
    int dosya_betimleyici;

    while (komut[i] != NULL) { // Komut dizisini tarar
        if (strcmp(komut[i], ">") == 0) { // ">" sembolünü kontrol eder
            if (komut[i + 1] == NULL) { // ">" sembolünden sonra dosya adı yoksa hata verir
                fprintf(stderr, "Gerekli argüman yok!\n");
                return;
            }

            // Dosyayı yazma modunda açar (varsa üzerine yazar, yoksa oluşturur)
            dosya_betimleyici = open(komut[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (dosya_betimleyici < 0) { // Dosya açılamadıysa hata verir
                perror("Çıkış dosyası açılamadı");
                return;
            }

            // Standart çıktıyı dosyaya yönlendirir
            dup2(dosya_betimleyici, STDOUT_FILENO);
            close(dosya_betimleyici); // Dosya betimleyicisini kapatır

            komut[i] = NULL; // ">" sembolünü ve dosya adını komut dizisinden kaldırır
            break;
        }
        i++;
    }

    if (tekli_komut(komut) == 0) { // Komut çalıştırılamadıysa hata verir
        fprintf(stderr, "Komut yürütülemiyor!\n");
    }
}
