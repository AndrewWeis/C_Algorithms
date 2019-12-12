#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#pragma pack(push, 1)
typedef struct files {
	char name[21]; // Имя файла, состоящее из латинских букв, цифр и символов точки.
	unsigned long long int S; // Размер 𝑆𝑖 файла в байтах
	char Dirictoria; // Байт равен 1, если файл на самом деле является директорией, и 0 иначе.
	unsigned long long int C; // Момент времени 𝐶𝑖, когда файл был создан
	unsigned long long int M; // Момент времени 𝑀𝑖, когда файл был изменён в последний раз
	char hide; // Байт равен 1, если файл скрытый, и 0 иначе.
} files;
#pragma pack(pop)

files file[1002];

int main() {
	long long int A; // не раньше этого момента времени
	long long int B; //  искомый файл не модифицировался позже этого момента времени 
	FILE* input = fopen("input.bin", "rb");
	FILE* output = fopen("output.bin", "wb");
	int number, sum = 0, N = 0;
	int sorted[1001] = { 0 };

	fread(&N, sizeof(int), 1, input);
	fread(&A, sizeof(long long int), 1, input);
	fread(&B, sizeof(long long int), 1, input);

	for (int i = 0; i < N; i++) 
		fread(&file[i], sizeof(files), 1, input);
	

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {

			if (strcmp(file[i].name, file[j].name) > 0) {
				file[1001] = file[i];
				file[i] = file[j];
				file[j] = file[1001];
			}
		}
	}

	int k = 0;
	for (int i = 0; i < N; i++) {
		int hide = file[i].hide;
		int dirictoria = file[i].Dirictoria;
		if (dirictoria == 0 && hide == 0 && file[i].C >= A && file[i].M <= B) {
			sorted[k] = i;
			k++;
		}
	}

	for (int i = 0; i < k; i++)
		fwrite(&file[sorted[i]], sizeof(files), 1, output);

	fclose(input);
	fclose(output);
	return 0;
}
