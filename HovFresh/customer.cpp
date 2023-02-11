#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct custNode{
    char name[50];
    int id;
    int typeMembership;
    char orderId[50];
    custNode* next;
};

struct Customer{
    char name[50];
    int id;
    int typeMembership;
};

struct Menu{
    int id;
    char name[50];
    int price;
};

struct Queue{
    custNode* front = NULL;
    custNode* rear = NULL;
};

void printMenu(){
    printf("Hov's Fresh\n");
    printf("===================\n");
    printf("1. Add New Order\n");
    printf("2. View Order Queue\n");
    printf("3. Serve Order\n");
    printf("4. Exit\n");
    printf(">> ");
}

custNode* createNode(char name[], int id, int typeMembership, char orderId[]){
    custNode* temp = (custNode*)malloc(sizeof(custNode));
    strcpy(temp->name, name);
    temp->id = id;
    temp->typeMembership = typeMembership;
    strcpy(temp->orderId, orderId);
    temp->next = NULL;

    return temp;
}

Queue* createQueue(){
    Queue* temp = (Queue*)malloc(sizeof(Queue));
    temp->front = temp->rear = NULL;
    return temp;
}

struct Menu menuArr[105];
int size = 0;

void readMenu(){
    FILE *f = fopen("menus.txt", "r");
    if(f == NULL){
        printf("File not found\n");
        return;
    }

    while(!feof(f)){
        fscanf(f, "%d#%[^#]#%d\n", &menuArr[size].id, menuArr[size].name, &menuArr[size].price);
        size++;
    }

    fclose(f);
}

struct Customer custArr[105];
int sizes = 0;

void readCustomer(){
    FILE *f = fopen("customers.txt", "r");
    if(f == NULL){
        printf("File not found\n");
        return;
    }

    while(!feof(f)){
        fscanf(f, "%d#%[^#]#%d\n", &custArr[sizes].id, custArr[sizes].name, &custArr[sizes].typeMembership);
        sizes++;
    }

    fclose(f);
}

void viewMenu(){
    for(int i = 0; i < size; i++){
        printf("%d. %s - %d\n", menuArr[i].id, menuArr[i].name, menuArr[i].price);
    }
}

void viewCustomer(){
    for(int i = 0; i < sizes; i++){
        printf("%d. %s - %d\n", custArr[i].id, custArr[i].name, custArr[i].typeMembership);
    }
}

int findIdByCustName(char name[]){
    for(int i = 0; i < sizes; i++){
        if(strcmp(custArr[i].name, name) == 0){
            return custArr[i].id;
        }
    }
    return -1;
}

void addOrderToQueue(Queue* q, char name[], int id, int typeMembership, char orderId[]){
    custNode* temp = createNode(name, id, typeMembership, orderId);

    if(q->rear == NULL && q->front == NULL){
        q->front = q->rear = temp;
        return;
    }else if(temp->typeMembership > q->front->typeMembership){
        temp->next = q->front;
        q->front = temp;
        return;
    }else {
        custNode* iter = q->front;
        while(iter->next && temp->typeMembership <= iter->next->typeMembership){
            iter = iter->next;
        }

        temp->next = iter->next;
        iter->next = temp;

        // if(iter == q->rear){
        //     q->rear = temp;
        // }

        return;
    }
}

void printOrder(Queue* q){
    custNode* iter = q->front;
    if(q == NULL){
        printf("There is No Data!!");
        return;
    }

    while(iter){
        printf("\nOrder id: %s\n", iter->orderId);
        printf("Name: %s\n", iter->name);
        printf("ID: %d\n", iter->id);
        printf("Type of Membership: %d\n", iter->typeMembership);
        
        iter = iter->next;
    }

    puts("");
}


void serveOrder(Queue* q){
    if(q->front == NULL){
        printf("There is No Data!!");
        return;
    }

    custNode* temp = q->front;
    q->front = q->front->next;

    if(q->front == NULL){
        q->rear = NULL;
    }

    free(temp);
}

int checkName(char name[]){
    for(int i = 0; i < sizes; i++){
        if(strcmp(custArr[i].name, name) == 0){
            return 1;
        }
    }

    return -1;
}

void removeAll(Queue* q){
    custNode* temp = q->front;
    while(temp){
        serveOrder(q);
        temp = temp->next;
    }
}

int main(){
    Queue* q = createQueue();
    srand(time(0));
    int menuInput = 0;
    readMenu();
    readCustomer();
    do{

        printMenu();
        scanf("%d", &menuInput); getchar();

        switch(menuInput){
            case 1:{
                char nameCust[100];
    
                do{
                    printf("Input your name: ");
                    scanf("%[^\n]", nameCust); getchar();
                }while(checkName(nameCust) == -1);

                printf("\n");
                printf("Menu\n");
                printf("===========\n");
                viewMenu();
                printf("\n");

                int menuOrder = 0;
                do{
                    printf("Input your menuOrder: ");
                    scanf("%d", &menuOrder); getchar();
                }while(menuOrder > size);

                printf("Summary of your order\n");
                printf("=========================\n");
                printf("Item: %s\n", menuArr[menuOrder - 1].name);
                printf("Total Price: %d\n", menuArr[menuOrder - 1].price);
                printf("=========================\n");

                char orderId[7];
                sprintf(orderId, "%d%c%c%d%d%d%d", findIdByCustName(nameCust), rand() % 26 + 'A', rand() % 26 + 'A', rand() % 10, rand() % 10, rand() % 10, rand() % 10); getchar();

                printf("Your Order ID: %s\n", orderId);

                addOrderToQueue(q, nameCust, findIdByCustName(nameCust), custArr[findIdByCustName(nameCust) - 1].typeMembership, orderId);
                break;
            }

            case 2:{
                printOrder(q);
                break;
            }

            case 3:{
                serveOrder(q);
                break;
            }

            case 4:{
                removeAll(q);
                break;
            }

            default:{
                break;
            }
        }
    }while(menuInput != 4);
    return 0;
}