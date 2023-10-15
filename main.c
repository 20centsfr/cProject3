#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void inputString(char *string, int size);
void clearInputBuffer();
int verifIp(char *ip);
void addIp();
void ipToBinary(int n);
void listIp(char **ipArray, int count);
char** readIp(int* count);
void freeIpArray(char** ipArray, int ipCount);
void deleteIp();
void searchByMask(char **ipArray, int ipCount);

int main(int argc, char** argv){
    char choice[5];
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

        printf("\n a - Add a new IP address\n");
        printf(" l - List all IP addresses\n");
        printf(" s - Search IP addresses by mask\n");
        printf(" d - Delete an IP address\n");
        printf(" q - Quit\n");
        printf ("Choix : ");
        inputString(choice, sizeof(choice));
        printf ("\n");

        while (strlen(choice) != 1 || choice[0] != 'a' && choice[0] != 'l' && choice[0] != 's' && choice[0] != 'd' && choice[0] != 'q') {
            printf("\nChoix invalide, veuillez recommencer : ");
            inputString(choice, sizeof(choice));
        }

        switch (choice[0])
        {
            case 'a':
                freeIpArray(ipArray, ipCount);
                addIp();
                break;

            case 'l':
                freeIpArray(ipArray, ipCount);
                ipArray = readIp(&ipCount);
                listIp(ipArray, ipCount);
                break;

            case 's':
                freeIpArray(ipArray, ipCount);
                searchByMask(ipArray, ipCount);
                break;

            case 'd':
                deleteIp();
                break;
        }


    }while (choice[0] != 'q');

    freeIpArray(ipArray, ipCount);

    return 0;
}

void searchByMask(char **ipArray, int ipCount) {
    char networkIP[20];
    char **ipArrayByMask = NULL;
    int mask;
    int compteur = 0;

    printf("Entrez l'adresse IP : ");
    inputString(networkIP, sizeof(networkIP));

    // Vérification de la validité de l'adresse IP
    if (!verifIp(networkIP)) {
        printf("Adresse IP du réseau non valide : %s\n", networkIP);
        return;
    }

    printf("Entrez le masque : ");
    scanf("%d", &mask);
    clearInputBuffer();

    // Vérification de la validité du masque
    if (mask < 8 || mask > 32) {
        printf("Masque invalide. Entrez une valeur entre 8 et 32.\n");
        return;
    }

    // Calcul du nombre d'adresses possibles
    int numAddresses = 1 << (32 - mask); // Équivalent à 2^(32 - mask)

    for (int i = 0; i < numAddresses; i++) {
        char *ip = (char *)malloc(20);
        int a, b, c, d;
        sscanf(networkIP, "%d.%d.%d.%d", &a, &b, &c, &d);
        d += i;
        c += d / 256;
        d %= 256;
        b += c / 256;
        c %= 256;
        a += b / 256;
        b %= 256;

        snprintf(ip, 20, "%d.%d.%d.%d", a, b, c, d);

        ipArrayByMask = (char **)realloc(ipArrayByMask, (compteur + 1) * sizeof(char *));
        ipArrayByMask[compteur] = ip;
        ++compteur;
    }

    // Récupération des IP dans le fichier
    ipArray = readIp(&ipCount);

    int trouve = 0;
    for (int i = 0; i < compteur; i++) {
        for (int j = 0; j < ipCount; j++) {
            if (strcmp(ipArrayByMask[i], ipArray[j]) == 0) {
                printf("Adresse IP trouvée : %s\n", ipArrayByMask[i]);
                trouve = 1;
            }
        }
    }
    printf ("\n\n");

    if (!trouve) {
        printf("\nAucune adresse IP n'a été trouvée pour le réseau %s/%d\n\n", networkIP, mask);
    }

    // Libérez la mémoire allouée pour ipArrayByMask
    for (int i = 0; i < numAddresses; i++) {
        free(ipArrayByMask[i]);
    }

    // Libérer la mémoire allouée pour le tableau d'adresses IP
    freeIpArray(ipArray, ipCount);
}

void inputString(char *string, int size) {
    if (fgets(string, size, stdin) != NULL) {
        if (string[strlen(string) - 1] == '\n') 
            string[strlen(string) - 1] = '\0'; 
        else 
            clearInputBuffer(); // Nettoie le reste du tampon d'entrée
    } else {
        clearInputBuffer(); // Nettoie le tampon d'entrée en cas d'erreur
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
    char userInput[20];

    printf("\nEntrez une ip valide : ");
    scanf("%19s", userInput);
    clearInputBuffer();

    if (!verifIp(userInput)) {
        printf("\nAdresse IP non valide : %s\n", userInput);
        return;
    }

    FILE *file = fopen("ipList.txt", "a+");
    if (file == NULL) {
        printf("\nImpossible d'ouvrir/creer le fichier ipList.txt\n\n");
        return;
    }

    if (fscanf(file, "%s", ip) != EOF) {
        while (fscanf(file, "%s", ip) != EOF) {
            if (strcmp(userInput, ip) == 0) {
                printf("\n\nL'ADRESSE IP EXISTE DÉJÀ !\n\n\n");
                fclose(file);
                return;
            }
        }
    }

    fprintf(file, "%s\n", userInput);

    printf("\nL'ip a été ajoutée avec succès !\n\n");

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

    printf("\n0 - Cancel\n");

    do{
    printf("\nSelectionnez une ip à consulter : ");
    scanf("%d", &choice);
    }while(choice > count || choice < 0);
    clearInputBuffer();

    if(choice == 0)
        return;

    sscanf(ipArray[choice - 1], "%d.%d.%d.%d", &a, &b, &c, &d);

    printf("IP : %s\n", ipArray[choice - 1]);
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

void deleteIp() {
    char ipToDelete[20];
    char **ipArray = NULL;
    int ipCount = 0;
    int found = 0;

    printf("Entrez l'adresse IP à supprimer : ");
    inputString(ipToDelete, sizeof(ipToDelete));
    

    // Lire les adresses IP à partir du fichier
    ipArray = readIp(&ipCount);

    if (ipCount == 0) {
        printf("\nLa liste des adresses IP est vide.\n\n");
        freeIpArray(ipArray, ipCount);
        return;
    }


    // Rechercher l'adresse IP à supprimer
    for (int i = 0; i < ipCount; i++) {
        if (strcmp(ipToDelete, ipArray[i]) == 0) {
            found = 1;
            // Libérer la mémoire de l'adresse IP à supprimer
            free(ipArray[i]);
            // Réduire le compteur des adresses IP
            ipCount--;
            // Décaler les adresses IP restantes
            for (int j = i; j < ipCount; j++) {
                ipArray[j] = ipArray[j + 1];
            }
            break;
        }
    }

    if (found) {
        // Écrire les adresses IP restantes dans le fichier
        FILE *file = fopen("ipList.txt", "w");
        if (file == NULL) {
            printf("\nImpossible d'ouvrir le fichier ipList.txt pour la mise à jour.\n\n");
            freeIpArray(ipArray, ipCount);
            return;
        }

        for (int i = 0; i < ipCount; i++) {
            fprintf(file, "%s\n", ipArray[i]);
        }

        fclose(file);
        printf("\nL'adresse IP a été supprimée avec succès.\n\n");
    } else {
        printf("\nL'adresse IP spécifiée n'a pas été trouvée dans la liste.\n\n");
    }

    // Libérer la mémoire allouée pour le tableau d'adresses IP
    freeIpArray(ipArray, ipCount);
}
