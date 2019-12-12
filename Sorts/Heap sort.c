#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void Adjust(int Heap_of_Numbers[], int i) {
    int j, copy, num, reference = 1;
    
    num = Heap_of_Numbers[0];

    while (2 * i <= num && reference == 1) {
        j = 2 * i;
        if (j + 1 <= num && Heap_of_Numbers[j + 1] > Heap_of_Numbers[j])
            j = j + 1;

        if (Heap_of_Numbers[j] < Heap_of_Numbers[i])
            reference = 0;
        else
        {
            copy = Heap_of_Numbers[i];
            Heap_of_Numbers[i] = Heap_of_Numbers[j];
            Heap_of_Numbers[j] = copy;
            i = j;
        }
    }
}

void Make_Heap(int heap[]) {
    int i, Number_of_Elements;
    Number_of_Elements = heap[0];

    for (int i = Number_of_Elements / 2; i >= 1; i--)
        Adjust(heap, i);
}

int heap[500001];

int main() {
    FILE* input = fopen("input.bin", "rb");
    FILE* output = fopen("output.bin", "wb");
   
    int NumberofElements, LastElement, CopyVariable;

    fread(&NumberofElements, sizeof(int), 1, input);

    for (int i = 1; i <= NumberofElements; i++)
        fread(&heap[i], sizeof(int), 1, input);

    heap[0] = NumberofElements;
    Make_Heap(heap);

    while (heap[0] > 1) {
        LastElement = heap[0];
        CopyVariable = heap[1];
        heap[1] = heap[LastElement];
        heap[LastElement] = CopyVariable;
        heap[0]--;
        Adjust(heap, 1);
    }

    for (int i = 1; i <= NumberofElements; i++)
        fwrite(&heap[i], sizeof(int), 1, output);

    fclose(input);
    fclose(output);
    return 0;
}
