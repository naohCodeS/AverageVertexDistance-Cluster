#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
// #include <numeric>
using namespace std;

int N; //頂点数
vector<vector<int>> G; //グラフ
vector<vector<int>> L; //頂点間距離
vector<double> cluster;//クラスタ係数

/*
N頂点の無向グラフ
頂点iの次数はM(i)
頂点iは頂点E(i,j)への無向辺をもつ(0<=j<M(i))

1<=N
0<=M(i)<=N-1
0<=E(i)<=N-1

// 入力例1
3
2 1 2 //頂点0：次数 辺を張る頂点番号列
2 2 0
2 0 1

// 入力例2
// 頂点数8の2重サイクル
8
4 6 7 1 2
4 7 0 2 3
4 0 1 3 4
4 1 2 4 5
4 2 3 5 6 
4 3 4 6 7
4 4 5 7 0
4 5 6 0 1
*/

void setVertexDistance(){ //頂点間距離を求める
    for(int start=0; start<N; start++){
        int dist = 0;
        int res = 0;
        queue<int> q;
        q.push(start);
        L[start][start] = 0;
        while(!q.empty()){
            int now = q.front(); q.pop();
            for(int v : G[now]) {
                if(L[start][v]!=-1) continue;
                q.push(v);
                L[start][v] = L[start][now] + 1;
            }
        }
    }
}

double averageVertexDistance(){
    int tmp = 0;
    // for(int i=0; i<N; i++) tmp += accumulate(L[i].begin(), L[i].end(), 0);
    for(int i=0; i<N; i++) for(int l : L[i]) tmp += l;
    return (double)tmp/N/(N-1);
}

void setCluster(){ //クラスター係数を求める
    for(int a=0; a<N; a++){
        for(int b : G[a]){
            for(int c : G[b]){
                for(int aa : G[c]){
                    if(aa==a) {
                        cluster[a]++;
                    }
                }
            }
        }
    }
    for(int i=0; i<N; i++) cluster[i] /=2.0; //頂点を含む三角形の数が求まった
    for(int i=0; i<N; i++) cluster[i] /= G[i].size()*(G[i].size()-1)/2.0; //潜在的に可能な頂点vを含む三角形の数で割る
}

double averageCluster(){
    double tmp = 0;
    for(double c : cluster) tmp += c;
    return tmp / N;
}


int main(){
    cin>>N;
    G.resize(N);
    cluster.resize(N);
    for(int i=0; i<N; i++){
        int M; //頂点mの次数
        cin>>M;
        for(int j=0; j<M; j++){
            int v; cin>>v;
            G[i].push_back(v);
        }
    }
    L.resize(N);
    for(int i=0; i<N; i++) L[i].resize(N,-1);

    setVertexDistance();
    setCluster();

    cout<<"-----vertex distance-----"<<endl;
    for(int i=0; i<N; i++){
        for(int d : L[i]) cout<<d<<" ";
        cout<<endl;
    }
    cout<<"averageVertexDistance : "<<averageVertexDistance()<<endl;
    
    cout<<"-----cluster-----"<<endl;
    for(int i=0; i<N; i++) cout<<"頂点"<<i<<" : "<<cluster[i]<<endl;
    cout<<"average cluster : " << averageCluster()<<endl;
}