#include <stdio.h>
int main(){
    while (1)
    {
        int odev,lab,proje,vize,final;
        float ortalama;

        printf("odev notu giriniz: ");scanf("%d",&odev);
        if (odev == 101){break;}
        printf("lab notu giriniz: ");scanf("%d",&lab);
        printf("proje notu giriniz: ");scanf("%d",&proje);
        printf("vize notu giriniz: ");scanf("%d",&vize);
        printf("final notu giriniz: ");scanf("%d",&final);

        ortalama = odev*0.1 + lab*0.1 + proje*0.2 + vize*0.2 + final*0.4;

        printf("mba ortalama: %.2f \n", ortalama);
    }
    printf("cikis yapildi");
    return 0;
}
