#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int verifIp(char *ip){

    int a, b, c, d;
    if (sscanf(ip, "%d.%d.%d.%d", &a, &b, &c, &d) == 4) {
        if (a >= 0 && a <= 255 &&
            b >= 0 && b <= 255 &&
            c >= 0 && c <= 255 &&
            d >= 0 && d <= 255) {
            return 1;
        }
    }
    return 0;
}

void addIp(){

    char ip[20];

    printf("Entrez un ip valide :\n");
    scanf("%19s", ip);

    if (!verifIp(ip)) {
        printf("Adresse IP non valide : %s\n", ip);
        return;
    }

    FILE *file = fopen("ipList.txt", "a+");
    if (file == NULL) {
        perror("Impossible d'ouvrir/creer le fichier ipList.txt");
        return;
    }

    fprintf(file, "%s\n", ip);

    printf("\nL'ip a ete ajoute avec succes\n");

    fclose(file);
}

int main(int argc, char** argv){
    char choice;

    do{

    printf(" ::::::::                   ::: ::::::::::: :::     :::        ::::::::   ::::::::  :::    ::: ::::::::::\n");
    printf(":+:    :+:                :+: :+:   :+:   :+: :+:   :+:       :+:    :+: :+:    :+: :+:    :+: :+:\n");
    printf("+:+                      +:+   +:+  +:+  +:+   +:+  +:+       +:+    +:+ +:+        +:+    +:+ +:+\n");
    printf("+#+       +#++:++#++:++ +#++:++#++: +#+ +#++:++#++: +#+       +#+    +:+ :#:        +#+    +:+ +#++:++#\n");
    printf("+#+                     +#+     +#+ +#+ +#+     +#+ +#+       +#+    +#+ +#+   +#+# +#+    +#+ +#+\n");
    printf("#+#    #+#              #+#     #+# #+# #+#     #+# #+#       #+#    #+# #+#    #+# #+#    #+# #+#\n");
    printf(" ########               ###     ### ### ###     ### ########## ########   ########   ########  ##########\n");

    printf("\n a - Add a new IP address\n l - List IP addresses\n s - Search similar by mask\n d - Delete an IP\n q - quit\n");
    choice = getchar();

    switch (choice)
    {
    case 'a':
        addIp();
        break;
    
    case 'l':
        //listIp();
        break;

    case 's':
        //searchByMask();
        break;

    case 'd':
        //deleteIp();
        break;
    }

    }while (choice != 'q');
    
}