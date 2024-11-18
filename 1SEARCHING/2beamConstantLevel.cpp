#include<bits/stdc++.h> 
using namespace std; 

void bfs(vector<vector<int>>&adj,vector<int>visited,int start,int width){ 
    queue<int>q; 
    q.push(start); 
    visited[start]=1; 
    while(!q.empty()){ 
        int front=q.front(); 
        q.pop(); 
        cout<<front<<" "; 
        int ct=0; 
        for(int i=0;i<adj[front].size();i++){ 
            if(adj[front][i] && !visited[i]){ 
                ct++; 
                visited[i]=1; 
                q.push(i); 
                if(ct==width) break; 
            } 
        } 
    } 
} 
int main(){ 
    int n; 
    cout<<"Enter the number of nodes : "; 
    cin>>n; 
    vector<vector<int>>adj(n,vector<int>(n)); 
    for(int i=0;i<n;i++){ 
        for(int j=0;j<n;j++){ 
            int edge; 
            cin>>edge; 
            adj[i][j]=edge; 
        } 
    } 
    int start,width; 
    cout<<"Enter the starting node : "; 
    cin>>start; 
    vector<int>visited(n,0); 
   for(int width=1;width<=3;width++){ 
bfs(adj,visited,start,width);   
cout<<endl;  
}  
return 0; 
}