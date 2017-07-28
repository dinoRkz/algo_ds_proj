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

// This method creates a new node of type 'Node'
Node* createNode()
{
    int i=0;

    // return type of malloc is void* so convert it to node*
    // address is returned right side so node* n on left
    // allocate this memory to a new node
    Node* newNode = (Node*)malloc(sizeof(Node));

    // initialise its members
    newNode->isEOW = false;
    for( i=0 ; i < ALPHABET_SIZE ; i++)
        newNode->next[i] = NULL;

    // return node
    return newNode;

}

// This method inserts a node into trie
void insertWord(Node* root, char word[])
{
    int i;
    // create a copy of root
    Node* temp = root;

    // repeat for each char in word
    for(i=0 ; i<strlen(word) ; i++)
    {
        // ASCII value of current character
        int idx = word[i] - 'a';

        // if the current character (character to be added to the part of word traversed)
        // is not present, create a new node and assign it to 'ASCII value of character' of next pointer
        if(temp->next[idx] == NULL)
            temp->next[idx] = createNode();
        
        // if the current character is already present, go to next node
        temp = temp->next[idx];
    }

    // After the word is complete, set isEOW as true
    temp->isEOW = true;
    printf("inserted %s\n", word);
}

// This is a recursive(DFS type recursion) function to print all words
void printAllWords(Node *root, char *prefix)
{
    int i, len = strlen(prefix);

    // len + 2 = length of prefix accessed + current character + '\0'
    char newPrefix[len+2];
    strcpy(newPrefix, prefix);

    // if no words are present in trie, return
    if(root == NULL)
        return;

    // if recursion reaches EOW, print
    if(root->isEOW)
        printf("%s\n",newPrefix);

    // DFS type recursion
    for(i=0 ; i<ALPHABET_SIZE ; i++)
    {
        if(root->next[i] != NULL)
        {
            // typecast and append current character
            newPrefix[len] = (char)('a'+i);
            
            // append null terminator
            newPrefix[len+1] = '\0';
            
            // recurse
            printAllWords(root->next[i], newPrefix);
        }
    }
}

// prints all words starting with the given prefix
void autoSuggest(Node *root, char *prefix)
{
    int i;

    // going down the trie until the prefix is traversed completely
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

    // print all words from here
    printAllWords(root, prefix);
}

// This method, shows menu and returns integer
int showMenu()
{
    int ch;
    char junkChars[256];
    printf("MENU\n");
    printf("====\n");
    printf("1. Insert word\n");
    printf("2. Auto Suggest\n");
    printf("3. Print all words\n");
    printf("4. Exit\n");
    printf("Your Choice: ");

    // Input validation - goo.gl/XnjH6A
    if(scanf("%d", &ch) == 0)
    {
        printf("Please type an integer...\n");
        scanf("%s", junkChars);
        return -1;
    }
    return ch;
}

int main()
{
    Node* root = createNode();
    int ch;
    char word[100];

    FILE *fp = fopen("dictionary.txt", "r");
    if(fp == NULL)
    {
        printf("file not found!");
        exit(0);
    }
    else
    {
        while(!feof(fp))
        {
            fscanf(fp, "%s", word);
            insertWord(root, word);
        }
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
            // return(instead of exit(0)) can be done
            // exit(0) is here, so break is not necessarily required
        default:
            printf("Bad choice!! Try Again...\n");
        }
    }
    return 0;
}
