#include <bits/stdc++.h>
using namespace std;
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
BiTNode* SearchBST(BiTNode* T,int key,BiTree f,BiTree &p){
    if(!T){
        p=f;
        return NULL;
    }
    else if(key==T->data){
        p=T;
        return T;
    }
    else if(key<T->data){
        return SearchBST(T->lchild,key,T,p);
    }
    else{
        return SearchBST(T->rchild,key,T,p);
    }
}
bool insertBST(BiTree &T,int key){
    BiTNode *p,*s;
    if(!(p=SearchBST(T,key,NULL,s))){
        BiTNode *r=new BiTNode;
        r->data=key;
        r->lchild=r->rchild=NULL;
        if(!s){
            T=r;
        }
        else if(key<s->data){
            s->lchild=r;
        }
        else{
            s->rchild=r;
        }
        return true;
    }
    else{
        return false;
    }
}
void Delete(BiTree &p)
{
    BiTree q;
    if(!p->rchild){
        q=p;
        p=p->lchild;
        free(q);
    }
    else if(!p->lchild){
        q=p;
        p=p->rchild;
        free(q);
    }
    else{
        q=p;
        BiTree s=p->lchild;
        while(s->rchild){
            q=s;
            s=s->rchild;
        }
        p->data=s->data;
        if(q!=p){
            q->rchild=s->lchild;
        }
        else{
            q->lchild=s->lchild;
        }
        free(s);
    }
}
bool DeleteBST(BiTree&T,int key)
{
    if(!T)return false;
    else{
        if(key==T->data){
            Delete(T);
            return true;
        }
        else if(key<T->data){
            return DeleteBST(T->lchild,key);
        }
        else{
            return DeleteBST(T->rchild,key);
        }
    }
}
void InOrderTraverse(BiTree T){
    if(T){
        InOrderTraverse(T->lchild);
        cout<<T->data<<" ";
        InOrderTraverse(T->rchild);
    }
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    BiTree T=NULL;
    insertBST(T,20);
    insertBST(T,32);
    insertBST(T,30);
    insertBST(T,35);
    insertBST(T,20);
    insertBST(T,50);
    insertBST(T,80);
    insertBST(T,90);
    insertBST(T,85);
    insertBST(T,88);
    cout << "中序遍历结果: ";
    InOrderTraverse(T);
    cout << endl;
    int searchKey = 40;
    BiTree p;
    if (SearchBST(T, searchKey, NULL, p)) {
        cout << "找到元素 " << searchKey << endl;
    } else {
        cout << "未找到元素 " << searchKey << endl;
    }
    cout << "删除元素 20" << endl;
    DeleteBST(T, 20);
    cout << "中序遍历结果: ";
    InOrderTraverse(T);
    cout << endl;
    return 0;
}