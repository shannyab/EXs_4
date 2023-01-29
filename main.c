#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
typedef struct GRAPH_NODE_ *pnode;;
typedef struct edge_{
int weight;
pnode endpoint;
struct edge_ *next;
}edge,*pedge;
typedef struct queueNode{
pnode nodedata;
int priority;
struct queueNode* next;
}queuenode;
typedef struct GRAPH_NODE_{
int node_num;
pedge edges;
struct GRAPH_NODE_ *next;
int seq;
}node,*pnode;
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);
void dij(int *nodes,pnode here);
void pe(int* cit,int strt,int enndd,int nodddess,int* ans,pnode head);
void sweap(int* a,int* b);
pnode gen(int k);
pnode nnod(int k,pnode next);
pnode find_node(int data,pnode head);
void rouedg(pnode here);
void regto(int data,pnode here);
pnode innode(int data,pnode *head);
queuenode* nq(pnode data,int p);
pnode pp(queuenode** head);
void ps(queuenode** head,pnode d,int p);
int mpy(queuenode** head);
pedge nwedge(int weight,pedge next,pnode d);
pedge nwedge(int weight,pedge next,pnode d){
pedge p=(pedge) malloc(sizeof(edge));
p->endpoint=d;
p->next=next;
p->weight=weight;
return p;
}
pnode nnod(int k,pnode next){
pnode p=(pnode) malloc(sizeof(node));
p->node_num=k;
p->next=next;
p->edges=NULL;
return p;
}
pnode find_node(int data,pnode head){
while (head){
if (head->node_num == data){
return head;
}
head=head->next;
}
return NULL;
}
pnode gen(int k){
pnode head=NULL;
for (int i=k-1;i>=0;i--){
head=nnod(i,head);
}
return head;
}
void rouedg(pnode here){
pedge next=here->edges;
while(next){
pedge prev=next;
next=next->next;
free(prev);
}
}
void regto(int data,pnode here){
pedge check_edge=here->edges;
if(check_edge){
if (check_edge->endpoint->node_num == data){
pedge del=check_edge;
here->edges=check_edge->next;
free(del);
return;
}
while(check_edge->next != NULL){
if (check_edge->next->endpoint->node_num == data){
pedge del=check_edge->next;
check_edge->next=del->next;
free(del);
return;
}
check_edge=check_edge->next;
}
}
}
pnode innode(int data,pnode *head){
pnode *p=head;
while ((*p)->next)
   {
if((*p)->node_num< data && (*p)->next->node_num> data){
pnode new=nnod(data,(*p)->next);
(*p)->next=new;
return new;
}
p=&((*p)->next);
}
pnode new=nnod(data,(*p)->next);
(*p)->next=new;
return new;
}
void build_graph_cmd(pnode *head){
int i;
scanf("%d",&i);
pnode here=find_node(i,*head);
pedge prev=NULL;
while(scanf("%d",&i)==1){
pnode d=find_node(i,*head);
scanf("%d",&i);
prev=nwedge(i,prev,d);
}
here->edges=prev;
}
void insert_node_cmd(pnode *head){
int i;
scanf("%d",&i);
pnode here=find_node(i,*head);
if (*head == NULL){
*head=nnod(i,NULL);
here=*head;
}
else if(here != NULL){
rouedg(here);
}
else{
here=innode(i,head);
}
pedge prev=NULL;
while(scanf("%d",&i)==1){
pnode d=find_node(i,*head);
scanf("%d",&i);
prev=nwedge(i,prev,d);
}
here->edges=prev;
}
void delete_node_cmd(pnode *head){
int i;
scanf("%d",&i);
pnode chk=*head;
pnode del=NULL;
if (chk->node_num == i){
*head=chk->next;
del=chk;
}
else{
while(chk->next){
if (chk->next->node_num == i){
del=chk->next;
chk->next=del->next;
break;
}
chk= chk->next;
}
}
chk=*head;
while(chk){
regto(i,chk);
chk=chk->next;
}
rouedg(del);
free(del);
}
queuenode* nq(pnode data,int p){
queuenode* temp=(queuenode*)malloc(sizeof(queuenode));
temp->nodedata=data;
temp->priority=p;
temp->next=NULL;
return temp;
}
pnode pp(queuenode** head){
pnode temp=(*head)->nodedata;
queuenode* temptofree=*head;
(*head)=(*head)->next;
free(temptofree);
return temp;
}
void ps(queuenode** head,pnode d,int p){
queuenode* strt=(*head);
queuenode* temp=nq(d,p);
if (mpy(head)){
(*head)=temp;
return;
}
if ((*head)->priority > p){
temp->next=*head;
(*head)=temp;}
else{
while (strt->next != NULL&&strt->next->priority < p){
strt=strt->next;
}
temp->next=strt->next;
strt->next=temp;
}
}
int mpy(queuenode** head){
	return (*head) == NULL;
}
void printGraph_cmd(pnode head){
while(head){
printf("node id: %d\n",head->node_num);
pedge here=head->edges;
while(here){
printf("%d -> %d   w: %d\n",head->node_num,here->endpoint->node_num,here->weight);
here= here->next;
}
head=head->next;
}
}
void deleteGraph_cmd(pnode* head){
pnode here=*head;
while(here){
rouedg(here);
pnode del=here;
here=here->next;
free(del);
}
}
void shortsPath_cmd(pnode head){
int src;
int d;
while(scanf("%d",&src)==0);
while(scanf("%d",&d)==0);
//int max=0;
pnode here;
pnode curr=head;
int j=0;
int idxdest;
int idxsrc;
while (curr){
curr->seq=j;
if (curr->node_num == src){
here=curr;
idxsrc=j;
}
if (curr->node_num == d){
idxdest=j;
}
j++;
curr= curr->next;
}
int *nodes=(int*)malloc(sizeof(int)*j);
for (int i=0;i<j;i++){
nodes[i]=INT_MAX;
}
nodes[idxsrc]=0;
dij(nodes,here);
if (nodes[idxdest]<INT_MAX){
printf("Dijsktra shortest path: %d \n",nodes[idxdest]);
}
else{
printf("Dijsktra shortest path: -1 \n");
}
free(nodes);
}
void dij(int *nodes,pnode here){
queuenode* here_queue=nq(here,0);
while (!mpy(&here_queue)){
here=pp(&here_queue);
pedge curr_edge=here->edges;
while(curr_edge){
if (nodes[here->seq] + curr_edge->weight < nodes[curr_edge->endpoint->seq]){
nodes[curr_edge->endpoint->seq]=nodes[here->seq] + curr_edge->weight;
ps(&here_queue,curr_edge->endpoint,nodes[curr_edge->endpoint->seq]);
}
curr_edge= curr_edge->next;
}
}
}
void TSP_cmd(pnode head){
int j;
scanf("%d",&j);
int *cit=(int*)malloc(sizeof(int)*j);
for(int i=0; i<j; i++){
scanf("%d",&cit[i]);
}
int max=0;
pnode here=head;
while (here){
here->seq=max;
max++;
here= here->next;
}
int ans=INT_MAX;
pe(cit,0,j-1,max,&ans,head);
if (ans != INT_MAX){
printf("TSP shortest path: %d \n",ans);
}
else{
printf("TSP shortest path: -1 \n");
}
free(cit);
}
void pe(int* cit,int strt,int enndd,int nodddess,int* ans,pnode head){
if (strt == enndd){
int check =0;
int *dxtra=(int*)malloc(sizeof(int)*nodddess);
for (int i=0;i<nodddess;i++){
dxtra[i]= INT_MAX;
}
pnode here=find_node(cit[0],head);
dxtra[here->seq]=0;
for (int i=1;i<=enndd;i++){
dij(dxtra,here);
if (dxtra[find_node(cit[i],head)->seq] == INT_MAX){
free (dxtra);
return;
}
here=find_node(cit[i],head);
check=check + dxtra[here->seq];
for (int j=0;j<nodddess;j++){
dxtra[j]= INT_MAX;
}
dxtra[here->seq]=0;  
}
free (dxtra);
if (check < *ans && check !=0){
*ans=check;
}
return;
}
for (int k=strt;k<=enndd;k++){
sweap(cit+k,cit+strt);
pe(cit,strt+1,enndd,nodddess,ans,head);
sweap(cit+k,cit+strt);
}
}
void sweap(int* a,int* b){
int temp=*a;
*a=*b;
*b=temp;
}
int main(){
char s;
int k;
pnode head=NULL;
int end_of_file=0;
while(end_of_file!=EOF){
end_of_file=scanf("%c",&s);
if (s == 'A'){
deleteGraph_cmd(&head);
scanf("%d",&k);
head=gen(k);
}
if (s == 'n'){
build_graph_cmd(&head);
}
if (s == 'B'){
insert_node_cmd(&head);
}
if (s=='p'){
printGraph_cmd(head);
}
if (s=='S'){
shortsPath_cmd(head);
}
if (s=='D'){
delete_node_cmd(&head);
}
if (s=='T'){
TSP_cmd(head);
}
}
deleteGraph_cmd(&head);
return 0;
}