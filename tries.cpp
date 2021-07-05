//use trie whenever u see prefix
struct node
{
	node* nxt[26];
	int cnt;
	node(){
		cnt=0;
		for(int i=0;i<26;++i)
			nxt[i]=NULL;
	}
};

int find_ans(string const&s,node* head){
	node* temp=head;
	for(char c:s){
		if(temp->nxt[c-'a']){
			temp=temp->nxt[c-'a'];
		}
		else{
			return 0;
		}
	}
	return temp->cnt;
}

void insert_in_trie(string const&s,node* head){
	node* temp=head;
	for(char c:s){
		if(!temp->nxt[c-'a'])
			temp->nxt[c-'a']=new node();
		temp=temp->nxt[c-'a'];
		temp->cnt++;
	}
}


//max xor of two numbers
struct node
{
  node* nxt[2];
  node(){
    for(int i=0;i<2;++i){
      nxt[i]=0;
    }
  }
};
void insert(int x,node* head){
  node* temp=head;
  for(int i=30;i>=0;i--){
    int bit=((x>>i)&1LL);
    if(bit==0){
      if(temp->nxt[0]==NULL)
        temp->nxt[0]=new node();
      temp=temp->nxt[0];
    }
    else{
      if(temp->nxt[1]==NULL)
        temp->nxt[1]=new node();
      temp=temp->nxt[1];
    }
  }

}
int find_ans(std::vector<int>& a){
  node* head=new node();
  int n=a.size();
  for(int i=0;i<n;++i){
    insert(a[i],head);
  }
  int ans=0;
  for(int i=0;i<n;i++){
    int m=(1LL<<30);
    int cur_xor=0;
    node* temp=head;
    for(int j=30;j>=0;--j){
      int bit=((a[i]>>j)&1LL);
      if(bit==0){
        //we want another bit to be 1
        if(temp->nxt[1]){
          cur_xor+=m;
          temp=temp->nxt[1];
        }
        else{
          temp=temp->nxt[0];
        }
      }
      else{
        //we want nxt[0]
        if(temp->nxt[0]){
          cur_xor+=m;
          temp=temp->nxt[0];
        }
        else{
          temp=temp->nxt[1];
        }
      }
      m=(m>>1LL);
    }
    ans=max(ans,cur_xor);
  }
  return ans;
}


//other implementation
class Trie
{
private:
  unordered_map<char,Trie *>nxt={};
  bool isword=false;
  int cnt=0;
public:
  Trie(){}
  
  void insert(string word){
    Trie* temp=this;
    int n=(int)word.length();
    for(int i=0;i<n;++i){
      if(temp->nxt[word[i]-'a']==NULL)
        temp->nxt[word[i]-'a']=new Trie();
      temp=temp->nxt[word[i]-'a'];
      temp->cnt++;
    }
    temp->isword=true;
  }

  bool search(string word){
    Trie* temp=this;
    int n=(int)word.length();
    for(int i=0;i<n;++i){
      if(temp->nxt[word[i]-'a']==NULL)
        return false;
      temp=temp->nxt[word[i]-'a'];
    }
    return temp->isword;
  }

  bool is_prefix(string prefix){
    Trie* temp=this;
    int n=(int)word.length();
    for(int i=0;i<n;++i){
      if(temp->nxt[word[i]-'a']==NULL)
        return false;
      temp=temp->nxt[word[i]-'a'];
    }
    return true;
  }

};