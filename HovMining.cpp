#include <stdio.h>
#include <stdlib.h>

struct Node{
    int cave;
    int gold;
    int depth;
    Node* left;
    Node* right;
};

Node* root = NULL;

Node* createNode(int cave, int gold, int depth){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->depth = depth;
    temp->cave = cave;
    temp->gold = gold;
    temp->left = temp->right = NULL;

    return temp;
}

Node* insertMining(Node* curr, int index, int production, int depth){
    if(curr == NULL){
        curr = createNode(index, production, depth);
        printf("New cave index detected\n");
    }else if(index < curr->cave){
        curr->left = insertMining(curr->left, index, production, depth + 1);
    }else if(index > curr->cave){
        curr->right = insertMining(curr->right, index, production, depth + 1);
    }else if(index == curr->cave){
        curr->gold += production;
        printf("Case is Already\n");
    }

    return curr;
}

void displayAll(Node* curr){
    //  inOrder
    if(curr == NULL){
        return;
    }

    displayAll(curr->left);
    printf(">> Cave %d (Depth %d), total gold production: %d\n", curr->cave, curr->depth, curr->gold);
    displayAll(curr->right);
}

void countProduction(Node* curr, int count[]){
    if(curr == NULL){
        return;
    }

    countProduction(curr->left, count);
    count[curr->depth] += curr->gold;
    countProduction(curr->right, count);
}

void displayReport(){
    // set ulang counter
    // memset(count, 0 , sizeof(count)); //memori set

    // for(int i = 0; i < 1001; i++){
    //     counter[i] = 0;
    // }

    int count[1001] = {};
    countProduction(root, count);

    for(int i = 1; i < 1000; i++){
        if(count[i] != 0){
            // printf("%d ", count[i]);
            printf(">> Total gold production for depth %d is %d.\n", i, count[i]);
        }
    }

    puts("");
}

void printMenu(){
    printf("Hov Mining Simulator\n");
    printf("=====================\n");
    printf("[1] Insert Mining Data\n");
    printf("[2] Display All Cave Data\n");
    printf("[3] Display Mining Reports\n");
    printf("[4] Exit\n");
    printf(">> ");
}

int main(){
    int menu = 0;
    do{
        printMenu();
        scanf("%d", &menu); getchar();

        switch(menu){
            case 1:{
                int index;
                do{
                    printf("Input cave index [1-999]: ");
                    scanf("%d", &index); getchar();
                }while(index < 1 || index > 999);

                int gold;
                do{
                    printf("Input gold production [1-100]: ");
                    scanf("%d", &gold); getchar();
                }while(gold < 1 || gold > 100);

                printf("Total Gold Production for Cave %d is %d.\n", index, gold);
                root = insertMining(root, index, gold, 1);
                break;
            }

            case 2:{
                displayAll(root);
                break;
            }

            case 3:{
                displayReport();
                break;
            }

            case 4:{

                break;
            }

            default:{
                break;
            }
        }
        printf("Press to continue ... "); getchar();
    }while(menu != 4);
    return 0;
}