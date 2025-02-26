#include<stdio.h>
#include<malloc.h>

struct node{
    int data;
    struct node*left;
    struct node*right;
};

struct node* constructnode(int data){
     struct node*n;
    n = (struct node*)malloc(sizeof(struct node));
    n -> data = data;
    n -> left = NULL;
    n -> right = NULL;
    return n;}
    
     
    //       5
    //      /  \
    //     3    6
    //    / \
    //   1   4
    // binary tree
   
  int isBST(struct node*root){
   static struct node *prev = NULL;
    if( root != NULL){
        if(!isBST(root->left)){
            return 0;
        }
       if(prev !=NULL && root->data <= prev->data){
        return 0;
       }
       prev = root;
       isBST(root->right);
    }
       else{
        return 1;
       }
   }


   // this is a recurssive code
   struct node* search(struct node* root,int key){
    if(root==NULL){
        return NULL;
    }
    if(root->data==key){
        return root;
    }
    else if(root->data > key){
        return search(root->left,key);
    }
    else{
        return search(root->right,key);
    }
   }

   //this is an iterative code
   struct node* searchIter(struct node* root,int key){
    while(root!=NULL){
        {
            if(key== root->data){
                return root;
            }
            else if(key< root->data){
                root = root ->left;
            }
            else{
                root = root->right;
            }
        }
    }
     return NULL;
   }

   //to insert a number in the tree
   void insert(struct node*root,int key){
    //here the root is the number that is to be inserted
    struct node*prev = NULL;
    while(root != NULL){
        prev = root;
        if(key == root->data){
            printf("sorry but you can not insert the data %d already exists in the tree");
            return;
        }
        else if(key < root->data){
            root = root->left;
        }
        else{
            root = root->right;
        }
    }
    struct node* new = constructnode(key);
    if(key< prev->data){
        prev->left = new;
    }
    else{
        prev->right = new;
    }
}
int main(){
    // struct node*p;
    // // p = (struct node*)malloc(sizeof(struct node));
    // // p -> data = 2;
    // // p -> left = NULL;
    // // p -> right = NULL;

    struct node*p = constructnode(5);
    struct node*p1 = constructnode(3);
    struct node*p2 = constructnode(6);
    struct node*p3 = constructnode(1);
    struct node*p4 = constructnode(4);


    p -> left = p1;
    p -> right = p2;
    p1-> left = p3;
    p1 -> right = p4;
    
    insert(p,6);
    printf("%d", p->right->right->data);
    return 0;
}