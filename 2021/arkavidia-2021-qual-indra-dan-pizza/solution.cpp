/**
*   Author  : Muhammad Hasan (mhasan01)
*   Problem : Tumpukan Piring Pizza
**/
#include <bits/stdc++.h>

using namespace std;

const int MAX_PIRING = 1e5 + 5;
const int MAX_TUMPUKAN = 1e5 + 5;

int N, M, Q;

struct Piring {
    int bawah, atas;
} piring[MAX_PIRING];

struct Tumpukan {
    int piring_terbawah;
    int piring_teratas;
} tumpukan[MAX_TUMPUKAN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> Q;

    // Lakukan inisialiasi
    auto inisialisasi = [&]() -> void {
        for (int i = 1; i < MAX_PIRING; i++) {
            piring[i] = {-1, -1};
        }
        for (int i = 1; i < MAX_TUMPUKAN; i++) {
            tumpukan[i] = {-1, -1};
        }
    };

    inisialisasi();

    auto letakkan_piring_baru = [&](int idx_piring, int idx_tumpukan) -> void {
        // Harus merupakan piring terbaru
        assert(piring[idx_piring].bawah == -1);
        if (tumpukan[idx_tumpukan].piring_terbawah == -1) { // Belum ada piring apapun
            tumpukan[idx_tumpukan].piring_terbawah = idx_piring;
            piring[idx_piring].bawah = idx_tumpukan;
        } else {
            int idx_piring_teratas = tumpukan[idx_tumpukan].piring_teratas;
            piring[idx_piring_teratas].atas = idx_piring;
            piring[idx_piring].bawah = idx_piring_teratas;
        }
        tumpukan[idx_tumpukan].piring_teratas = idx_piring;
    };

    auto ambil_piring_teratas = [&](int idx_tumpukan) -> void {
        // Harus ada piring terlebih dahulu
        assert(tumpukan[idx_tumpukan].piring_terbawah != -1);
        if (tumpukan[idx_tumpukan].piring_terbawah == tumpukan[idx_tumpukan].piring_teratas) { // Jika hanya ada satu tumpukan
            // Inisialisasi ulang
            int piring_teratas = tumpukan[idx_tumpukan].piring_teratas;
            piring[piring_teratas] = {-1, -1};
            tumpukan[idx_tumpukan] = {-1, -1};
            return;
        }
        int piring_teratas = tumpukan[idx_tumpukan].piring_teratas;
        int piring_teratas_terbaru = piring[piring_teratas].bawah;
        assert(piring_teratas_terbaru != -1);
        assert(piring[piring_teratas_terbaru].atas == piring_teratas);
        piring[piring_teratas] = {-1, -1};
        piring[piring_teratas_terbaru].atas = -1;
        tumpukan[idx_tumpukan].piring_teratas = piring_teratas_terbaru;
    };

    auto pindah_piring_pada_tumpukan = [&](int idx_tumpukan_1, int idx_tumpukan_2) -> void {
        if (tumpukan[idx_tumpukan_1].piring_terbawah == -1) {
            // Tumpukan kosong, tidak perlu melakukan apapun
            return;
        }
        if (tumpukan[idx_tumpukan_2].piring_terbawah == -1) {
            int terbawah = tumpukan[idx_tumpukan_1].piring_terbawah;
            piring[terbawah].bawah = idx_tumpukan_2;
            tumpukan[idx_tumpukan_2] = tumpukan[idx_tumpukan_1];
        } else {
            int teratas_1 = tumpukan[idx_tumpukan_1].piring_teratas;
            int terbawah_1 = tumpukan[idx_tumpukan_1].piring_terbawah;
            int teratas_2 = tumpukan[idx_tumpukan_2].piring_teratas;
            piring[teratas_2].atas = terbawah_1;
            piring[terbawah_1].bawah = teratas_2;
            tumpukan[idx_tumpukan_2].piring_teratas = teratas_1;
        }
        tumpukan[idx_tumpukan_1] = {-1, -1};
    };

    for (int i = 1; i <= M; i++) {
        int jumlah_piring;
        cin >> jumlah_piring;
        for (int j = 0; j < jumlah_piring; j++) {
            int nomor_piring;
            cin >> nomor_piring;
            letakkan_piring_baru(nomor_piring, i);
        }
    }
    
    auto output = [&](int idx_tumpukan) -> void {
        if (tumpukan[idx_tumpukan].piring_terbawah == -1) return;
        cout << idx_tumpukan << ": ";
        int no_piring = tumpukan[idx_tumpukan].piring_terbawah;
        while (no_piring != -1) {
            cout << no_piring;
            no_piring = piring[no_piring].atas;
            cout << (no_piring == -1 ? '\n' : ' ');
        }
    };

    for (int q = 1; q <= Q; q++) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int i, j;
            cin >> i >> j;
            letakkan_piring_baru(i, j);
        } else if (tp == 2) {
            int j;
            cin >> j;
            ambil_piring_teratas(j);
        } else if (tp == 3) {
            int j1, j2;
            cin >> j1 >> j2;
            pindah_piring_pada_tumpukan(j1, j2);
        }
    }

    for (int i = 1; i <= M; i++) {
        output(i);
    }

    return 0;
}