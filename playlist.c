#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "playlist.h"
#define CAMINHOARQUIVO "musicas.txt"

typedef struct Node {
    char artist[100];
    char song[100];
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Playlist {
    Node* head;
    Node* current;
} Playlist;

int main() {
    setlocale(LC_ALL, "Portuguese");
    Playlist* playlist = createPlaylist();
    loadPlaylist(CAMINHOARQUIVO, playlist);

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        if (choice == 1) {
            display(playlist);
        } else if (choice == 2) {
            displaySorted(playlist);
        } else if (choice == 3) {
            char artist[100], song[100];
            printf("Nome do artista: ");
            fgets(artist, sizeof(artist), stdin);
            artist[strcspn(artist, "\n")] = '\0'; // Remove the newline character
            printf("Nome da música: ");
            fgets(song, sizeof(song), stdin);
            song[strcspn(song, "\n")] = '\0'; // Remove the newline character
            append(playlist, artist, song);
            savePlaylist(CAMINHOARQUIVO, playlist);
            printf("Música adicionada com sucesso.\n");
        } else if (choice == 4) {
            char song[100];
            printf("Nome da música a ser removida: ");
            fgets(song, sizeof(song), stdin);
            song[strcspn(song, "\n")] = '\0'; // Remove the newline character
            if (removeSong(playlist, song)) {
                savePlaylist(CAMINHOARQUIVO, playlist);
                printf("Música removida com sucesso.\n");
            } else {
                printf("Música não encontrada.\n");
            }
        } else if (choice == 5) {
            char song[100];
            printf("Nome da música: ");
            fgets(song, sizeof(song), stdin);
            song[strcspn(song, "\n")] = '\0'; // Remove the newline character
            Node* node = find(playlist, song);
            if (node) {
                printf("Encontrado: %s - %s\n", node->artist, node->song);
            } else {
                printf("Música não encontrada.\n");
            }
        } else if (choice == 6) {
            Node* current = advance(playlist);
            if (current) {
                printf("Tocando agora: %s - %s\n", current->artist, current->song);
            } else {
                printf("Playlist vazia.\n");
            }
        } else if (choice == 7) {
            Node* current = retreat(playlist);
            if (current) {
                printf("Tocando agora: %s - %s\n", current->artist, current->song);
            } else {
                printf("Playlist vazia.\n");
            }
        } else if (choice == 8) {
            printf("Saindo...\n");
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 8);

    return 0;
}

Node* createNode(const char* artist, const char* song) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->artist, artist);
    strcpy(newNode->song, song);
    newNode->next = newNode->prev = newNode;
    return newNode;
}

Playlist* createPlaylist() {
    Playlist* playlist = (Playlist*)malloc(sizeof(Playlist));
    playlist->head = NULL;
    playlist->current = NULL;
    return playlist;
}

void append(Playlist* playlist, const char* artist, const char* song) {
    Node* newNode = createNode(artist, song);
    if (!playlist->head) {
        playlist->head = newNode;
        playlist->current = newNode;
    } else {
        Node* tail = playlist->head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = playlist->head;
        playlist->head->prev = newNode;
    }
}

int removeSong(Playlist* playlist, const char* song) {
    if (!playlist->head) return 0;
    Node* current = playlist->head;
    do {
        if (strcmp(current->song, song) == 0) {
            if (current == playlist->head) {
                if (playlist->head->next == playlist->head) {
                    free(playlist->head);
                    playlist->head = NULL;
                    playlist->current = NULL;
                } else {
                    Node* tail = playlist->head->prev;
                    playlist->head = playlist->head->next;
                    playlist->head->prev = tail;
                    tail->next = playlist->head;
                    free(current);
                }
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
            }
            return 1;
        }
        current = current->next;
    } while (current != playlist->head);
    return 0;
}

Node* find(Playlist* playlist, const char* song) {
    if (!playlist->head) return NULL;
    Node* current = playlist->head;
    do {
        if (strcmp(current->song, song) == 0) return current;
        current = current->next;
    } while (current != playlist->head);
    return NULL;
}

void display(Playlist* playlist) {
    if (!playlist->head) return;
    Node* current = playlist->head;
    do {
        printf("%s - %s\n", current->artist, current->song);
        current = current->next;
    } while (current != playlist->head);
}

void displaySorted(Playlist* playlist) {
    if (!playlist->head) return;
    int n = 0;
    Node* current = playlist->head;
    do {
        n++;
        current = current->next;
    } while (current != playlist->head);

    Node* nodes[n];

    current = playlist->head;
    for (int i = 0; i < n; i++) {
        nodes[i] = current;
        current = current->next;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(nodes[i]->song, nodes[j]->song) > 0) {
                Node* temp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s - %s\n", nodes[i]->artist, nodes[i]->song);
    }
}

Node* advance(Playlist* playlist) {
    if (playlist->current) {
        playlist->current = playlist->current->next;
    }
    return playlist->current;
}

Node* retreat(Playlist* playlist) {
    if (playlist->current) {
        playlist->current = playlist->current->prev;
    }
    return playlist->current;
}

void loadPlaylist(const char* filename, Playlist* playlist) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File %s not found.\n", filename);
        return;
    }
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char artist[100], song[100];
        sscanf(line, "%[^;];%[^\n]", artist, song);
        append(playlist, artist, song);
    }
    fclose(file);
}

void savePlaylist(const char* filename, Playlist* playlist) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }
    Node* current = playlist->head;
    if (current) {
        do {
            fprintf(file, "%s;%s\n", current->artist, current->song);
            current = current->next;
        } while (current != playlist->head);
    }
    fclose(file);
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Exibir a playlist pela ordem de cadastro\n");
    printf("2. Exibir a playlist ordenada pelo nome das músicas\n");
    printf("3. Inserir novas músicas\n");
    printf("4. Remover uma música\n");
    printf("5. Buscar por uma música\n");
    printf("6. Avançar para próxima música\n");
    printf("7. Retornar a música anterior\n");
    printf("8. Sair\n");
    printf("Escolha uma opção: ");
}


