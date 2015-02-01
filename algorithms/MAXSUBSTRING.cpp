#include<iostream>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cstring>

using namespace std;

string words[35];
int len[35], N;
bool esta[35];

#define MAXN 1000005
int n,t,n1,n2; //n es el tamao de la cadena
int p[MAXN],r[MAXN],h[MAXN];
//p es el inverso del suffix array, no usa indices del suffix array ordenado
//h el el tamao del lcp entre el i-esimo y el i+1-esimo elemento de suffix array ordenado
string s, s1;
void fix_index(int *b, int *e) {
    int pkm1, pk, np, i, d, m;
    pkm1 = p[*b + t];
    m = e - b; d = 0;
    np = b - r;
    for(i = 0; i < m; i++) {
        if (((pk = p[*b+t]) != pkm1) && !(np <= pkm1 && pk < np+m)) {
            pkm1 = pk;
            d = i;
        }
        p[*(b++)] = np + d;
    }
}
bool comp(int i, int j) {
    return p[i + t] < p[j + t];
}
void suff_arr() {
    int i, j, bc[256];
    t = 1;
    for(i = 0; i < 256; i++) bc[i] = 0; //alfabeto
    for(i = 0; i < n; i++) ++bc[int(s[i])]; //counting sort inicial del alfabeto
    for(i = 1; i < 256; i++) bc[i] += bc[i - 1];
    for(i = 0; i < n; i++) r[--bc[int(s[i])]] = i;
    for(i = n - 1; i >= 0; i--) p[i] = bc[int(s[i])];
    for(t = 1; t < n; t *= 2) {
        for(i = 0, j = 1; i < n; i = j++) {
            while(j < n && p[r[j]] == p[r[i]]) ++j;
            if (j - i > 1) {
                sort(r + i, r + j, comp);
                fix_index(r + i, r + j);
            }
        }
    }
}
void lcp() {
    int tam = 0, i, j;
    for(i = 0; i < n; i++)if (p[i] > 0) {
        j = r[p[i] - 1];
        while(s[i + tam] == s[j + tam]) ++tam;
        h[p[i] - 1] = tam;
        if (tam > 0) --tam;
    }
    h[n - 1] = 0;
}

int indexToWord(int n) {
    int i = 0;
    while (n+1 > len[i]) i++;
    //cout << "Tengo " << n+1 << " y len " << len[i] << " con i " << i << endl;
    if (n+1 == len[i]) return -1;
    return i;
}

int calcularMin(int ini, int fin) {
    if (ini == fin) return n - (r[ini]+1);
    int r = h[ini];
    for (int i = ini+1; i < fin; i++) {
        r = min(r, h[i]);
    }
    return r;
}

int main(){
    //s="atatat$";
    //n=s.size();
    
    while (true) {
        cin >> N;
        
        if (feof(stdin)) break;
        
        cin >> words[0];
        len[0] = words[0].size() + 1;
        s = words[0];
        s += "$";
        for (int w = 1; w < N; w++) {
            cin >> words[w];
            len[w] = len[w-1] + words[w].size() + 1;
            s += words[w];
            s += "$";
        }
        
        n=s.size();
    
        suff_arr();
        lcp();
        
        memset(esta, 0, sizeof(esta));
        int start = 0, end = 1, b = 0;
        
        while (indexToWord(r[start]) == -1) start++;
        end = start+1;
        
        esta[indexToWord(r[start])] = true;
        while (start < end && end < n) {
            int ind = indexToWord(r[end]);
            //cout << r[end] << " -> " << ind << endl;
            while (esta[ind]) {
                //cout << "Recorte " << start << endl;
                esta[indexToWord(r[start])] = false;
                start++;
            }
            esta[ind] = true;
            if (end - start + 1 == N) b = max(b, calcularMin(start, end)); 
            //cout << "Agregue "<< end << " con size " << end-start+1 << endl;
            end++;
        } 
        
        cout << b << endl;
    }
    
        
    /*for(int i=0;i<n;i++) {
        for (int j = r[i]; j < n; j++) {
            cout << s[j];
        }
        cout << endl;
    }
    for(int i=0;i<n;i++)cout<<h[i]<<" ";cout<<endl;*/
        
    return 0;
}
