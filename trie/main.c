#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ALPHABET_SIZE 26

struct node
{
    bool isEOW;
    struct node* next[ALPHABET_SIZE];
};

typedef struct node Node;

Node* createNode()
{
    int i=0;
    // return type of malloc is void* so convert it to node*
    // address is returned right side so node* n on left

    Node* newNode = (Node*)malloc(sizeof(Node));// Allocate a new node
    newNode->isEOW = false;// initialise its members
    for( i=0 ; i < ALPHABET_SIZE ; i++)
        newNode->next[i] = NULL;
    return newNode;// return node

}

int showMenu()
{
    int ch;
    printf("MENU\n");
    printf("====\n");
    printf("1. Insert word\n");
    printf("2. Auto Suggest\n");
    printf("3. Print all words\n");
    printf("4. Exit\n");
    printf("Your Choice: ");
    scanf("%d", &ch);
    return ch;
}

void insertWord(Node* root, char word[])
{
    int i;
    Node* temp = root;
    // repeat for each char in word
    for(i=0 ; i<strlen(word) ; i++){
        int idx = word[i] - 'a';
        if(temp->next[idx] == NULL)
            temp->next[idx] = createNode();
        temp = temp->next[idx];  // going down
    }

    temp->isEOW = true;
    printf("inserted %s\n", word);
}

void printAllWords(Node *root, char *prefix)
{
    int len = strlen(prefix);
    char newPrefix[len+2];
    strcpy(newPrefix, prefix);
    int i;


    if(root == NULL)
        return;

    if(root->isEOW)
        printf("%s\n",newPrefix);

    for(i=0 ; i<ALPHABET_SIZE ; i++)
    {
        if(root->next[i] != NULL)
        {
            newPrefix[len] = (char)('a'+i);
            newPrefix[len+1] = '\0';
            printAllWords(root->next[i], newPrefix);
        }
    }


}

void autoSuggest(Node *root, char *prefix)
{
    int i;
    for(i=0 ; prefix[i]!='\0' ; i++)
    {
        int idx = prefix[i] - 'a';
        if(root->next[idx] != NULL)
            root = root->next[idx];
        else
        {
            printf("No word with %s\n", prefix);
            return;
        }
    }
    printAllWords(root, prefix);
}


int main()
{
    Node* root = createNode();
    int ch;
    char word[100];

    FILE *fp = fopen("dictionary.txt", "r");
    if(fp == NULL)
        printf("file not found!");
    while(!feof(fp))
    {
        fscanf(fp, "%s", word);
        insertWord(root, word);
    }
    fclose(fp);

    while(1)
    {
        ch = showMenu();
        switch(ch)
        {
        case 1:
            printf("\nEnter a word: ");
            scanf("%s", word);
            insertWord(root, word);
            break;
        case 2:
            printf("Enter prefix");
            scanf("%s", word);
            autoSuggest(root, word);
            break;
        case 3:
            printAllWords(root, "");
            break;
        case 4:
            exit(0);
            // return can be done
            // exit here so break is not necessarily required
        default:
            printf("Bad choice!! Try Again...\n");
        }
    }
    return 0;
}
