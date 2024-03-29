namespace AVL{
  
  struct node{
    int key;
    int val;
    int num;
    unsigned char height;
    node* left;
    node* right;
    node(int k) { key = k; left = right = 0; height = 1; val = 1; num = 1;}
  };
  
  unsigned char height(node* p){
    return p?p->height:0;
  }

  int bfactor(node* p){
    return height(p->right)-height(p->left);
  }
  
  void fixnum(node * p){
    p->num = p->val;
    if(p->left != 0) p->num = p->num+p->left->num;
    if(p->right != 0) p->num = p->num+p->right->num;
  }
  
  void fixheight(node* p){
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
    fixnum(p);
  }
  
  node* rotateright(node* p){
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
  }

  node* rotateleft(node* q){
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
  }

  node* balance(node* p){ // balancing the p node
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // balancing is not required
  }
  
  
  // p = insert(p,k);
  node* insert(node* p, int k){ // insert k key in a tree with p root
    if( !p ) return new node(k);
    if( k<p->key )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    return balance(p);
  }

  node* findmin(node* p){ // find a node with minimal key in a p tree 
    return p->left?findmin(p->left):p;
  }

  node* removemin(node* p){ // deleting a node with minimal key from a p tree
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
  }
  // p = remove(p,k);
  node* remove(node* p, int k){ // deleting k key from p tree
    if( !p ) return 0;
    if( k < p->key )
        p->left = remove(p->left,k);
    else if( k > p->key )
        p->right = remove( p->right,k);  
    else{ //  k == p->key 
        node* q = p->left;
        node* r = p->right;
        delete p;
        if( !r ) return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
  }
  node* find(node*p, int k){
    if(!p) return 0;
    if( k < p->key )
        return find(p->left,k);
    else if( k > p->key )
        return find(p->right,k);  
    else {
        return p;
    }
  }
  
  void bal(node *p, int k){ // restore the balance
    if( k < p->key )
      bal(p->left,k);
    else if( k > p->key )
      bal(p->right,k);
    fixnum(p);
  }
  
  // Num of nodes >= to k
  int query(node* p, int k){
    if( !p ) return 0;
    if( k < p->key ){
      return p->val + (p->right==0?0:p->right->num) + query(p->left,k) ;
    }else if( k > p->key ){
      return query(p->right,k);  
    }else {
      return p->val + (p->right==0?0:p->right->num);
    }
  }
  
}
