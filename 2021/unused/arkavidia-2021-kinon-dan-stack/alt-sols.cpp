#include <bits/stdc++.h>
using namespace std;

/* prinsip kerja program ini adlaah bikin satu stack terurut dari angka2 positif.
program bikin 2 stack, satu baut ngisi angka2 stack, satu buat penanda bottom stack baru yg dibuat stlh program berjalan.
dari angka2 negatif yg dimasukkan berikutnya, jika next elemen yg ketemu di stack adalah 0 atau next dari stack kedua adalah
bottom stack, maka elemen tsb adalah top of stack dan bs lgsg diapus. jika gabisa, maka bikin bottom stack baru dgn stack penanda
dan apus elemen tsb.*/

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int q, i, input, count = 0, j; //inisialisasi var
    bool fill = false;
    cin >> q; //input jumlah masukan
    int x[100], counter[100]; //inisialisasi stack dan counter
    for (i = 0; i < 100; i++){
        x[i] = 0;
        counter[i] = 0;
    }
    counter[0] = 1; //inisialisasi start stack awal
    for (i = 0; i < q; i++){ //iterasi input 
        cin >> input;
        if (input > 0){ //input positif, menambah ke stack
            j = 0;
            while (j < 100 && !fill){ //mencari bot of stack yg kosong biar diisi dulu
                if (counter[j] == 1){
                    if (x[j] == 0){
                        x[j] = input;
                        fill = true;
                    }
                }
                j++;
            }
            j = 0;
            while (j < 100 && !fill){ //jika ga ketemu bot yg kosong, maka isi tempat yg ada aja
                if (x[j] == 0){
                    x[j] = input;
                    fill = true;
                }
                j++;
            }
        }
        else if (input < 0){ //input negatif, membuang top of stack jika nilainya sama
            input = (-1)*input; //jadi positif
            j = 0;
            while (x[j] != input){ //mencari elemen di stack
                j++;
            }
            if (x[j+1] == 0 || counter[j+1] == 1){ //jika next = 0 atau next = bot stack berikutnya, maka dia top of stack, lgsg apus
                x[j] = 0;
            }
            else{ //jika ngga, bikin stack baru
                x[j] = 0;
                counter[j+1] = 1;
                count++;
            }
        }
    }
    cout << count; //print jumlah stack yg terpakai
    return 0;
}