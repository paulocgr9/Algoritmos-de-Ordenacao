#include <iostream>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::rand;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

// Criando uma estrutura de nó
typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

// Protótipos das funções
Node *createNode(int);
void printArray(long long int*, int);
void displayList(Node*);
void insertEnd(Node**, int);
void swapValues(Node*, Node*);
void bubbleSort(Node**, int);
void optimizedBubbleSort(Node**, int);
void selectionSort(Node**);
void optimizedSelectionSort(Node **);
void freeList(Node **);

int main()
{
    int iNumeroSeeds = 50;
    int iNumeroElementos = 15000;

    long long int temposBubbleSort[iNumeroSeeds] = {};
    long long int temposOptimizedBubbleSort[iNumeroSeeds] = {};
    long long int temposSelectionSort[iNumeroSeeds] = {};
    long long int temposOptimizedSelectionSort[iNumeroSeeds] = {};

    for (int iIndex = 0; iIndex < iNumeroSeeds; iIndex++){
        cout << "FAZENDO PARA A SEED " << iIndex << endl << "==" << endl;
        // Definindo uma lista
        Node *head1 = nullptr;

        // Adicionando os valores aleatórios à lista
        srand(iIndex);
        for (int i = 0; i < iNumeroElementos; i++)
        {
            insertEnd(&head1, rand() % iNumeroElementos);
        }

        //cout << "ANTES DO BUBBLE SORT" << endl;
        //displayList(head1);

        //cout << "DEPOIS DO BUBBLE SORT" << endl;
        cout << "EXECUTANDO BUBBLE SORT" << endl;
        auto timeStart = high_resolution_clock::now();
        bubbleSort(&head1, iNumeroElementos);
        auto timeStop = high_resolution_clock::now();

        //cout << "Array ordenado: ";
        //displayList(head1);

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos." << endl;
        cout << "========================================" << endl;
        temposBubbleSort[iIndex] = timeDuration.count();
        freeList(&head1);
        //displayList(head1);

        Node* head2 = nullptr;

        for (int i = 0; i < iNumeroElementos; i++)
        {
            insertEnd(&head2, rand() % iNumeroElementos);
        }
        //cout << "ANTES DO OPTIMIZED BUBBLE SORT" << endl;
        //displayList(head2);

        //cout << "DEPOIS DO OPTIMIZED BUBBLE SORT" << endl;
        cout << "EXECUTANDO OPTIMIZED BUBBLE SORT" << endl;
        timeStart = high_resolution_clock::now();
        optimizedBubbleSort(&head2, iNumeroElementos);
        timeStop = high_resolution_clock::now();

        //cout << "Array ordenado: ";
        //displayList(head2);

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos." << endl;
        cout << "========================================" << endl;
        temposOptimizedBubbleSort[iIndex] = timeDuration.count();
        freeList(&head2);

        Node* head3 = nullptr;

        for (int i = 0; i < iNumeroElementos; i++)
        {
            insertEnd(&head3, rand() % iNumeroElementos);
        }
        //cout << "ANTES DO SELECTION SORT" << endl;
        //displayList(head3);

        //cout << "DEPOIS DO SELECTION SORT" << endl;
        cout << "DEPOIS DO SELECTION SORT" << endl;
        timeStart = high_resolution_clock::now();
        selectionSort(&head3);
        timeStop = high_resolution_clock::now();

        //cout << "Array ordenado: ";
        //displayList(head3);

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos." << endl;
        cout << "========================================" << endl;
        temposSelectionSort[iIndex] = timeDuration.count();
        freeList(&head3);

        Node* head4 = nullptr;

        for (int i = 0; i < iNumeroElementos; i++)
        {
            insertEnd(&head4, rand() % iNumeroElementos);
        }
        //cout << "ANTES DO OPTIMIZED SELECTION SORT" << endl;
        //displayList(head4);

        //cout << "DEPOIS DO OPTIMIZED SELECTION SORT" << endl;
        cout << "DEPOIS DO OPTIMIZED SELECTION SORT" << endl;
        timeStart = high_resolution_clock::now();
        optimizedSelectionSort(&head4);
        timeStop = high_resolution_clock::now();

        //cout << "Array ordenado: ";
        //displayList(head4);

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos." << endl;
        cout << "========================================" << endl;
        temposOptimizedSelectionSort[iIndex] = timeDuration.count();
        freeList(&head4);

    }

    cout << "TEMPOS BUBBLE SORT:" << endl;
    printArray(temposBubbleSort, iNumeroSeeds);
    cout << "TEMPOS OPTIMIZED BUBBLE SORT:" << endl;
    printArray(temposOptimizedBubbleSort, iNumeroSeeds);
    cout << "TEMPOS SELECTION SORT:" << endl;
    printArray(temposSelectionSort, iNumeroSeeds);
    cout << "TEMPOS OPTIMIZED SELECTION SORT:" << endl;
    printArray(temposOptimizedSelectionSort, iNumeroSeeds);
    return 0;

}

void printArray(long long int arriNumbers[], int iLength)
{
     for (int i = 0; i < iLength; i++) cout << arriNumbers[i] << ", ";
     cout << endl;
}

Node* createNode(int iPayload)
{
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->iPayload = iPayload;
    temp->ptrPrev = nullptr;
    temp->ptrNext = nullptr;

    return temp;
}

void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Impossível mostrar lista: Lista inexistente." << endl;
        return;
    }
    if (node->ptrPrev != nullptr)
    {
        cout << "Impossível mostrar lista: Meio da lista." << endl;
        return;
    }

    Node* current = node;
    cout << "Valores: ";
    while (current != nullptr)
    {
        cout << current->iPayload << " ";
        current = current->ptrNext;
    }
    cout << endl;

    return;
}

void insertEnd(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);
    if (*head == nullptr)
    {
        (*head) = newNode;
        return;
    }

    Node* current = (*head);

    while (current->ptrNext != nullptr) current = current->ptrNext;
    
    newNode->ptrPrev = current;
    current->ptrNext = newNode;

    return;
}

void swapValues(Node* Node1, Node* Node2)
{
    // Trocando somente os Payloads
    int iTemp = Node1->iPayload;
    Node1->iPayload = Node2->iPayload;
    Node2->iPayload = iTemp;
}

void bubbleSort(Node** head, int iLenght)
{
    for (int iOuterLoop = 0; iOuterLoop < iLenght-1; iOuterLoop++)
    {
        Node* current = *head;
        do
        {
            if (current->iPayload > current->ptrNext->iPayload)
            {
                swapValues(current, current->ptrNext);
            }
            current = current->ptrNext;
        }
        while (current->ptrNext != nullptr);
    }
}

void optimizedBubbleSort(Node** head, int iLenght)
{
    bool bUnordered = false;
    for (int iOuterLoop = 0; iOuterLoop < iLenght-1; iOuterLoop++)
    {
        bUnordered = false;

        Node* current = *head;
        //do
        for(int iInnerLoop = 0; iInnerLoop < iLenght - iOuterLoop - 1; iInnerLoop++) {
            if (current->iPayload > current->ptrNext->iPayload)
            {
                swapValues(current, current->ptrNext);
                bUnordered = true;
            }
            current = current->ptrNext;
        }
        //while (current->ptrNext != nullptr);
        if (bUnordered == false) break;
    }
}

void selectionSort(Node** head)
{
    Node* currentOuter = *head;
    while(currentOuter != nullptr)
    {
        Node* currentInner = currentOuter->ptrNext;
        while(currentInner != nullptr)
        {
            if (currentOuter->iPayload > currentInner->iPayload)
            {
                swapValues(currentOuter, currentInner);
            }
        currentInner = currentInner->ptrNext;
        }
    currentOuter = currentOuter->ptrNext;
    }
}

void optimizedSelectionSort(Node** head)
{
    int minValue = 0;
    Node* ptrSwap = 0;

    Node* currentOuter = *head;
    while(currentOuter != nullptr)
    {
        minValue = currentOuter->iPayload;
        ptrSwap = currentOuter;

        Node* currentInner = currentOuter->ptrNext;
        while(currentInner != nullptr)
        {
            if (minValue > currentInner->iPayload)
            {
                minValue = currentInner->iPayload;
                ptrSwap = currentInner;
            }
            currentInner = currentInner->ptrNext;
        }
        swapValues(currentOuter, ptrSwap);
        currentOuter = currentOuter->ptrNext;
    }
}

void freeList(Node** head){
    Node* current = *head;
    current = current->ptrNext;
    while(current->ptrNext != nullptr){
        free(current->ptrPrev);
        current = current->ptrNext;
    }
    free(current);
}
