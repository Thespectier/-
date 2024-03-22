//血的教训，读取大规模输入时用sf比io快好多好多 


#include<iostream>
#include<cstdio>
#include<malloc.h>
using namespace std;
#define MAX_NUM 1000010
#define lson pos<<1
#define rson pos<<1|1

unsigned int tree[4*MAX_NUM]={};  //权值线段树 
unsigned int arr[MAX_NUM]={};
unsigned int pos[MAX_NUM]={};


//find_kth出现了问题需要解决； 



//更新叶节点 
void update(unsigned int pos,unsigned int l,unsigned int r,unsigned int k,unsigned int cnt)
{
	unsigned long long int mid;
	while(1)
	{
		mid = (l+r)>>1;
		tree[pos]+=cnt;
		if(l==r){
			break;
		}
		if(k<=mid){
			r = mid;
			pos=lson;
		}
		else{
			l = mid+1;
			pos=rson;
		}
	}
	return ;
}

//查询k排名 
unsigned int find_rk(unsigned int pos,unsigned int l,unsigned int r,unsigned int k)
{
	unsigned int ans=0;
	unsigned int mid;
	while(l!=r)
	{
		mid=(l+r)>>1;
		tree[pos]+=1;
		if(k<=mid){
			ans+=tree[rson];
			r=mid;
			pos=lson;
		}
		else{
			l=mid+1;
			pos=rson;
		}
	}
	tree[pos]+=1;
	return ans+1;
} 

//查询第k大值 
unsigned int find_kth(unsigned int pos,unsigned int l,unsigned int r,unsigned int k)
{
	unsigned int mid;
	while(l!=r)
	{
		mid=(l+r)>>1;
		if(k<=tree[rson]){
			l=mid+1;
			pos=rson;
		}
		else{
			k-=tree[rson];
			r=mid;
			pos=lson;
		}
	}
	return l;
} 

struct Query{
	struct Tnode* next;
	struct Tnode* tail;
};
struct Tnode{
	unsigned int num;
	unsigned int rk;
	struct Tnode* next;
};

struct Query qq[MAX_NUM]={{NULL,NULL},};



void insertQ(unsigned int qi,unsigned int ki,unsigned int rk_i)
{
	if(qq[qi].next==NULL){
		qq[qi].next = (struct Tnode*)malloc(sizeof(struct Tnode));
		qq[qi].next->num = ki;
		qq[qi].next->rk = rk_i;
		qq[qi].tail = qq[qi].next;
	}
	else{
		qq[qi].tail->next = (struct Tnode*)malloc(sizeof(struct Tnode));
		qq[qi].tail = qq[qi].tail->next;
		qq[qi].tail->num = ki;
		qq[qi].tail->rk = rk_i;
	}
	qq[qi].tail->next=NULL;
	return ;
} 

int main()
{
	unsigned int n,q,qi,ki,rk_i;
	struct Tnode* pp;
    int ans[MAX_NUM]={};
    cin>>n>>q;
	for(unsigned int i=1;i<=n;i++){
		scanf("%u",arr+i);
		pos[arr[i]]=i;
	} 
		
	for(unsigned int i=1;i<=q;i++){
		scanf("%u%u",&qi,&ki);
		insertQ(qi,ki,i);
	}
	
	for(unsigned int i=n;i>=1;i--){
		rk_i = find_rk(1,1,n,pos[i]);
		pp = qq[pos[i]].next;
		while(pp!=NULL){
			if(rk_i>pp->num){
				ans[pp->rk] = find_kth(1,1,n,rk_i-pp->num);
			}
			else{
				ans[pp->rk] = -1;
			}
			pp = pp->next;
		}
	}
	
	
	for(unsigned int i=1;i<q;i++){
		printf("%d\n",ans[i]);
	}
	printf("%d",ans[q]);
	
	return 0;
}
