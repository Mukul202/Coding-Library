
class heap
{
  int capacity;
  vector<int>heap_arr;
  int heap_size;
public:
  heap(int cap);

  void minheapify(int);//

  int parent(int i){
    return (i-1)/2;
  }

  int left(int i){
    return (2*i+1);
  }

  int right(int i){
    return (2*i+2);
  }

  int extractMin();//return the min_val and remove it from the heap

  void decreasekey(int index,int new_val);//decreases the value at index to new_val

  int getmin(){
    return heap_arr[0];
  }

  void deletekey(int index);//deletes the key at index

  void insertkey(int val);//insert new val

};

heap::heap(int cap){
  heap_size=0;
  capacity=cap;
  heap_arr.resize(cap);
}

void heap::minheapify(int i){
  //heapify the tree rooted at i
  int l=left(i);
  int r=right(i);
  int smallest=i;

  if(l<heap_size && heap_arr[l]<heap_arr[smallest])
    smallest=l;

  if(r<heap_size && heap_arr[r]<heap_arr[smallest])
    smallest=r;

  if(smallest!=i){
    swap(heap_arr[i],heap_arr[smallest]);
    minheapify(smallest);
  }

}

void heap::deletekey(int index){
  decreasekey(index,INT_MIN);
  extractMin();
}

void heap::decreasekey(int index,int new_val){
  heap_arr[index]=new_val;
  while(index!=0 && heap_arr[parent(index)]>heap_arr[index]){
    swap(heap_arr[parent(index)],heap_arr[index]);
    index=parent(index);
  }
}

int heap::extractMin(){
  if(heap_size<=0)
    return INT_MAX;
  if(heap_size==1){
    heap_size--;
    return heap_arr[0];
  }
  int root=heap_arr[heap_size-1];
  heap_size--;
  minheapify(0);
  return root;
}
