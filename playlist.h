typedef struct Node Node;
typedef struct Playlist Playlist;

void displayMenu();
void savePlaylist(const char* filename, Playlist* playlist);
void loadPlaylist(const char* filename, Playlist* playlist);
Node* retreat(Playlist* playlist);
Node* advance(Playlist* playlist);
void displaySorted(Playlist* playlist);
void display(Playlist* playlist);
Node* find(Playlist* playlist, const char* song);
int removeSong(Playlist* playlist, const char* song);
void append(Playlist* playlist, const char* artist, const char* song);
Playlist* createPlaylist();
Node* createNode(const char* artist, const char* song);