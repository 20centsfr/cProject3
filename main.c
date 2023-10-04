#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void clearInputBuffer();
int verifIp(char *ip);
void addIp();
void listIp(char **ipArray, int count);
char** readIp(int* count);
void freeIpArray(char** ipArray, int ipCount);
int main(int argc, char** argv);

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int decimalToBinary(int n) {
    if (n == 0)
        return 0;

    int binary[32];
    int reverse;
    int i = 0;

    while (n > 0) {
        binary[i] = n % 2;
        n = n / 2;
        i++;
    }

    for (int j = i - 3; j >= 0; j--) {
        reverse *= 10;
        reverse += binary[j];
    }
    return reverse;
}

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
    clearInputBuffer();

    if (!verifIp(ip)) {
        printf("Adresse IP non valide : %s\n", ip);
        return;
    }

    FILE *file = fopen("ipList.txt", "a+");
    if (file == NULL) {
        printf("Impossible d'ouvrir/creer le fichier ipList.txt");
        return;
    }

    fprintf(file, "%s\n", ip);

    printf("\nL'ip a ete ajoute avec succes\n");

    fclose(file);
}

void ipToBinary(int n) {
    if (n == 0) {
        printf("00000000");
        return;
    }

    int binary[8] = {0};
    int i = 7;

    while (n > 0 && i >= 0) {
        binary[i] = n % 2;
        n = n / 2;
        i--;
    }

    for (int j = 0; j < 8; j++) {
        printf("%d", binary[j]);
    }
}


void listIp(char **ipArray, int count){

    int choice;
    unsigned int a, b, c, d;

    for(int i = 0; i < count; i++)
        printf("%d : %s\n",i + 1, ipArray[i]);

    do{
    printf("Selectionne une ip a consulter\n");
    scanf("%d", &choice);
    }while(choice > count || choice < 0);
    clearInputBuffer();

    sscanf(ipArray[choice - 1], "%d.%d.%d.%d", &a, &b, &c, &d);

    printf("Ip : %s\n", ipArray[choice - 1]);
    printf("Binaire : ");
    ipToBinary(a);
    printf(".");
    ipToBinary(b);
    printf(".");
    ipToBinary(c);
    printf(".");
    ipToBinary(d);
    printf("\nHexa : %02x.%02x.%02x.%02x\n", a, b, c, d);

}

char** readIp(int *count) {
    FILE* file = fopen("ipList.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier ipList.txt\n");
        return NULL;
    }

    char line[20];
    int ipCount = 0;

    char** ipArray = NULL;

    while (fgets(line, sizeof(line), file) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        if (verifIp(line)) {
            ipArray = (char**)realloc(ipArray, (ipCount + 1) * sizeof(char*));
            if (ipArray == NULL) {
                printf("Erreur lors de l'allocation mémoire");
                exit(1);
            }

            ipArray[ipCount] = (char*)malloc(strlen(line) + 1);
            if (ipArray[ipCount] == NULL) {
                printf("Erreur lors de l'allocation mémoire");
                exit(1);
            }

            strcpy(ipArray[ipCount], line);
            ipCount++;
        }
    }

    fclose(file);

    *count = ipCount;
    return ipArray;
}


void freeIpArray(char** ipArray, int ipCount) {
    for (int i = 0; i < ipCount; i++) {
        free(ipArray[i]);
    }
    free(ipArray);
}

int main(int argc, char** argv){
    char choice;
    char** ipArray = NULL;
    int ipCount = 0;

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
        clearInputBuffer();

        switch (choice)
        {
            case 'a':
                addIp();
                break;

            case 'l':
                freeIpArray(ipArray, ipCount);
                ipArray = readIp(&ipCount);
                listIp(ipArray, ipCount);
                break;

            case 's':
                //searchByMask();
                break;

            case 'd':
                //deleteIp();
                break;
        }


    }while (choice != 'q');

    freeIpArray(ipArray, ipCount);

    return 0;
}
