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
    
    //preorder traversal for 
    //       5
    //      /  \
    //     3    6
    //    / \
    //   1   4
    // binary tree
    void preOrder(struct node*root){
        if (root != NULL)
        { 
            printf("%d ",root->data);
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    //similarly postorder traversal
    void postOrder(struct node*root){
        if (root != NULL)
        { 
            postOrder(root->left);
            postOrder(root->right);
            printf("%d ",root->data);
        }
    }
   
   //and inorder traversal
   void inOrder(struct node*root){
        if (root != NULL)
        { 
            inOrder(root->left);
            printf("%d ",root->data);
            inOrder(root->right);
        }
    }

int main(){
    // struct node*p;q
    // // p = (struct node*)malloc(sizeof(struct node));
    // // p -> data = 2;
    // // p -> left = NULL;
    // // p -> right = NULL;

    // struct node*p1;
    // // p1 = (struct node*)malloc(sizeof(struct node));
    // // p1 -> data = 1;
    // // p1 -> left = NULL;
    // // p1 -> right = NULL;

    // struct node*p2;
    // // p2 = (struct node*)malloc(sizeof(struct node));
    // // p2 -> data = 4;
    // // p2 -> left = NULL;
    // // p2 -> right = NULL;
    struct node*p = constructnode(5);
    struct node*p1 = constructnode(3);
    struct node*p2 = constructnode(6);
    struct node*p3 = constructnode(1);
    struct node*p4 = constructnode(4);


    p -> left = p1;
    p -> right = p2;
    p1-> left = p3;
    p1 -> right = p4;
    
    preOrder(p);
    printf("\n");
    postOrder(p);
    printf("\n");
    inOrder(p);
    printf("\n");
    return 0;
}