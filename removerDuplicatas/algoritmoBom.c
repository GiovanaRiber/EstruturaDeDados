#include <stdio.h>

int removeDuplicatasEficiente(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int j = 1; // índice para armazenar o próximo número único
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[i - 1]) {
            nums[j] = nums[i];
            j++;
        }
    }
    return j; // retorna o novo tamanho do vetor
}

int main() {
    int nums[] = {1, 1, 2, 2, 3, 4, 4, 5};
    int tamanho = sizeof(nums) / sizeof(nums[0]);

    int novoTamanho = removeDuplicatasEficiente(nums, tamanho);

    printf("Novo tamanho: %d\n", novoTamanho);
    printf("Vetor sem duplicatas: ");
    for (int i = 0; i < novoTamanho; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}