#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
int main()
{
  int *a;  // указатель на массив
  int i, n;
  system("chcp 1251");
  system("cls");
  printf("Введите размер массива: ");
  scanf("%d", &n);
  // Выделение памяти
  a = (int*)malloc(n * sizeof(int));
  // Ввод элементов массива
  for (i = 0; i<n; i++)
  {
    printf("a[%d] = ", i);
    scanf("%d", &a[i]);
  }
  // Вывод элементов массива
  for (i = 0; i<n; i++)
    printf("%d ", a[i]);
  free(a);
  return 0;
}
