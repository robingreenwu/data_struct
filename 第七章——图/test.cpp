#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3;
bool visited[maxn];
typedef struct ArcNode 
{
    int  adjvex;                // 该弧所指向的顶点的位置
    struct ArcNode* nextarc;
    // 指向下一条弧的指针
    int* info;       // 该弧相关信息的指针
} ArcNode;
typedef struct VNode 
{
    int  data;   // 顶点信息
    ArcNode* firstarc;
    // 指向第一条依附该顶点的弧
} VNode, AdjList[maxn];
typedef struct {
    AdjList  vertices;   // 表头结点向量
    int      vexnum, arcnum;
    // 图的当前顶点数和弧数
    int      kind;          // 图的种类标志
} ALGraph;
void createGraph(ALGraph &G){
    cout<<"请输入顶点数和边数：";
    cin>>G.vexnum>>G.arcnum;
    for(int i=0;i<G.vexnum;i++){
        G.vertices[i].data=i;
        G.vertices[i].firstarc=NULL;    
    }
    cout<<"请输入边的信息："<<endl;
    for(int i=0;i<G.arcnum;i++){
        int u,v;
        cin>>u>>v;
        ArcNode *p=new ArcNode;
        p->adjvex=v;
        p->nextarc=G.vertices[u].firstarc;
        G.vertices[u].firstarc=p;
        ArcNode *q=new ArcNode;
        q->adjvex=u;
        q->nextarc=G.vertices[v].firstarc;
        G.vertices[v].firstarc=q;   
    }
}
void DFS(ALGraph &G,int v){
    visited[v]=true;
    cout<<v<<" ";
    for(ArcNode*p=G.vertices[v].firstarc;p!=NULL;p=p->nextarc){
        if(!visited[p->adjvex]){
            DFS(G,p->adjvex);
        }
    }
}
void BFS(ALGraph&G,int v){
    queue<int>q;
    q.push(v);
    visited[v]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cout<<u<<" ";
        for(ArcNode*p=G.vertices[u].firstarc;p!=NULL;p=p->nextarc){
            if(!visited[p->adjvex]){
                q.push(p->adjvex);
                visited[p->adjvex]=true;
            }
        }
    }
}
bool ispath(ALGraph &G,int be,int en){
    memset(visited,false,sizeof(visited));
    stack<int>s;
    s.push(be);
    visited[be]=true;
    while(!s.empty()){
        int u=s.top();
        s.pop();
        for(ArcNode *p=G.vertices[u].firstarc;p!=NULL;p=p->nextarc){
            if(p->adjvex==en){
                return true;
            }
            if(!visited[p->adjvex]){
                s.push(p->adjvex);
                visited[p->adjvex]=true;
            }
        }
    }
    return false;
}
bool ispathoflenk(ALGraph &G,int u,int v,int k){
    if(k==0)return u==v;
    visited[u]=true;
    for(ArcNode*p=G.vertices[u].firstarc;p!=NULL;p=p->nextarc){
        if(!visited[p->adjvex]){
            if(ispathoflenk(G,p->adjvex,v,k-1)){
                return true;
            }
        }
    }
    visited[u]=false;
    return false;
}
bool chack(ALGraph &G,int u,int v,int k){
    memset(visited,false,sizeof(visited));
    return ispathoflenk(G,u,v,k);}
int main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    ALGraph G;
    createGraph(G);
    cout << "DFS遍历: ";
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            DFS(G, i);
        }
    }
    cout << endl;
    cout << "BFS遍历: ";
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            BFS(G, i);
        }
    }
    int vi,vj;
    cout << "请输入要判别路径的起点和终点：";
    cin >> vi >> vj;
    if (ispath(G, vi, vj)) {
        cout << "存在从顶点 " << vi << " 到顶点 " << vj << " 的路径。" << endl;
    } else {
        cout << "不存在从顶点 " << vi << " 到顶点 " << vj << " 的路径。" << endl;
    }
    int u,v,k;
    cout << "请输入要判别长度为k的路径的起点、终点和长度：";
    cin >> u >> v >> k;
    if (chack(G, u, v, k)) {
        cout << "存在从顶点 " << u << " 到顶点 " << v << " 长度为 " << k << " 的路径。" << endl;
    } else {
        cout << "不存在从顶点 " << u << " 到顶点 " << v << " 长度为 " << k << " 的路径。" << endl;
    }
    cout << endl;
	return 0;
}