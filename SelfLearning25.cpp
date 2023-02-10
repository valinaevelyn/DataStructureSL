#include <stdio.h>
#include <stdlib.h>

struct Node{
    int value;
    Node* left;
    Node* right;
};

Node* root = NULL;

Node* createNode(int value){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->value = value;
    temp->left = temp->right = NULL;

    return temp;
}

Node* insertNode(Node* curr, Node* node){
    if(curr == NULL){
        return node;
    }else if(node->value < curr->value){
        curr->left = insertNode(curr->left, node);
    }else if(node->value > curr->value){
        curr->right = insertNode(curr->right, node);
    }

    return curr;
}

void inOrder(int lev, Node* curr){
    if(curr == NULL){
        return;
    }

    inOrder(lev+1, curr->left);
    printf("%d - Level %d\n", curr->value, lev);
    inOrder(lev+1, curr->right);
}

void preOrder(int lev, Node* curr){
    if(curr == NULL){
        return;
    }

    printf("%d - Level %d\n", curr->value, lev);
    preOrder(lev+1, curr->left);
    preOrder(lev+1, curr->right);
}

void postOrder(int lev, Node* curr){
    if(curr == NULL){
        return;
    }

    postOrder(lev+1, curr->left);
    postOrder(lev+1, curr->right);
    printf("%d - Level %d\n", curr->value, lev);
}

Node* deleteNode(Node* curr, int value){
    if(curr == NULL){
        return curr;
    }else if(value < curr->value){
        curr->left = deleteNode(curr->left, value);
    }else if(value > curr->value){
        curr->right = deleteNode(curr->right, value);
    }else{
        if(!curr->left && !curr->right){
            free(curr);
            curr = NULL;
        }else if(!curr->left){
            Node* temp = curr;
            curr = curr->right;
            free(temp);
            curr = NULL;
        }else if(!curr->right){
            Node* temp = curr;
            curr = curr->left;
            free(temp);
            curr = NULL;
        }else{
            Node* iter = curr->left;
            while(iter->right){
                iter = iter->right;
            }

            curr->value = iter->value;
            curr->left = deleteNode(curr->left, value);
        }
    }

    return curr;
}

int main(){
    root = insertNode(root, createNode(5));
    root = insertNode(root, createNode(5));
    root = insertNode(root, createNode(2));
    root = insertNode(root, createNode(5));
    root = insertNode(root, createNode(4));
    root = insertNode(root, createNode(8));
    root = insertNode(root, createNode(1));
    root = insertNode(root, createNode(2));
    root = insertNode(root, createNode(6));
    root = insertNode(root, createNode(4));
    root = insertNode(root, createNode(8));
    root = insertNode(root, createNode(9));
    root = insertNode(root, createNode(5));

    // root = insertNode(root, createNode(2));
    // root = insertNode(root, createNode(5));
    // root = insertNode(root, createNode(0));
    // root = insertNode(root, createNode(9));
    // root = insertNode(root, createNode(0));
    // root = insertNode(root, createNode(9));
    // root = insertNode(root, createNode(8));
    // root = insertNode(root, createNode(3));
    // root = insertNode(root, createNode(4));
    // root = insertNode(root, createNode(7));
    // root = insertNode(root, createNode(2));
    // root = insertNode(root, createNode(8));
    // root = insertNode(root, createNode(1));
    // root = insertNode(root, createNode(0));
    // root = insertNode(root, createNode(4));

    inOrder(0, root);
    postOrder(0, root);
    preOrder(0, root);

    puts("");

    root = deleteNode(root, 5);
    inOrder(0, root);
    puts("");
    root = deleteNode(root, 6);
    inOrder(0, root);
    puts("");
    root = deleteNode(root, 8);
    inOrder(0, root);
    puts("");
    
    return 0;
}