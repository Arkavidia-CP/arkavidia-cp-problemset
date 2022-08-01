# include<iostream>
using namespace std;

// kita gunakan ADT list linier untuk membuat linked list

// DEKLARASI TIPE BENTUKAN
typedef struct tElmtlist *address;
typedef struct tElmtlist {
    int el[1000000]; //tempat menyimpan tumpukan
    int count; //jumlah piring dalam tumpukan
    int id; //urutan tumpukan
	address next;
} ElmtList;
typedef struct {
	address First;
} List;


// SELEKTOR
#define El(P, i) (P)->el[i]
#define Next(P) (P)->next
#define Count(P) (P)->count
#define ID(P) (P)->id
#define First(L) ((L).First)
#define Nil NULL


//FUNGSI BAWAAN
address Alokasi (int X){
// Alokasi tumpukan piring ke-X
    address P;
    P = (address) malloc(sizeof(tElmtlist));
    if (P == Nil){
        return Nil;
    }
    else{
        Count(P) = 0;
        ID(P) = X;
        Next(P) = Nil;
        return P;
    }
}

address Search (List L, int X){
// Cari tumpukan dengan ID X
    address P = First(L);
    while (P != Nil && ID(P) != X){
        P = Next(P);
    }
    return P;
}

void Insert (List *L, int X){
// Masukin tumpukan ID X ke list
    address P = Alokasi(X);
    address F = First(*L);
    if (First(*L) == Nil){
        First(*L) = P;
    }
    else {
        while (Next(F) != Nil && ID(F) < X){
            F = Next(F);
        }
        if (Next(F) == Nil){
            Next(F) = P;
        }
        else{
            Next(P) = Next(F);
            Next(F) = P;
        }
    }
}

void Enqueue (List *L, int X, int idx){
// Masukin piring idx ke tumpukan ID X
    address P = Search(*L, X);
    if (P == Nil){
        Insert(L, X);
        P = Search(*L, X);
    }
    El(P, Count(P)) = idx;
    Count(P)++;
}


// MAIN PROGRAM
int main(){
    int n, m, q, i, a, idx, perintah, j1, j2, idx2; //inisialisasi variabel
    cin >> n >> m >> q; //scan baris pertama
    List L;
    First(L) = Nil;
    address P, P2;

    // input kondisi piring awal
    for (i = 1; i <= m; i++){ 
        Insert(&L, i); //masukkin tumpukan ke list
        cin >> n; //jumlah piring di tumpukan
        for(idx = 0; idx < n; idx++){ //input index piring2
            cin >> a;
            Enqueue(&L, i, a);
        }
    }

    // input perintah
    for (i = 0; i < q; i++){
        cin >> perintah;
        if (perintah == 1){ //input 1, menambah piring baru ke stack j2
            cin >> j1 >> j2;
            Enqueue(&L, j2, j1);
        }
        else if (perintah == 2){ //input 2, membuang piring teratas stack j1
            cin >> j1;
            P = Search(L, j1);
            El(P, Count(P)) = 0;
            Count(P)--;
        }
        else if (perintah == 3){ //input 3, menumpuk stack j1 ke stack j2
            cin >> j1 >> j2;
            P = Search(L, j1);
            P2 = Search(L, j2);
            for (idx = 0; idx < Count(P); idx++){
                Enqueue(&L, j2, El(P, idx));
                El(P, idx) = 0;
            }
            Count(P) = 0;
        }
    }
    



    //print
    P = First(L);
    while (P != Nil){
        if (Count(P) != 0){
            cout << ID(P) << ":";
            for (i = 0; i < Count(P); i++){
                cout << " " << El(P, i);
            }
            cout << "\n";
        }
        P = Next(P);
    }
    return 0;
}