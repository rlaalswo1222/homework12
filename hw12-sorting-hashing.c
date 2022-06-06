/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;
	printf("[----- [김민재] [2021041070] -----]\n");
	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a); // 동적할당 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); // 인덱스 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); // 배열 출력
	printf("\n");
}


int selectionSort(int *a) //선택정렬
{
	int min; //최소값
	int minindex; // 최소값 위치
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 출력 

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // 최솟값 인덱스 = i
		min = a[i]; // 최소값을 a[i]에 담음
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) 
			{
				min = a[j]; // 최소값 업데이트
				minindex = j; // 최솟값 인덱스 업데이트
			}
		}
		a[minindex] = a[i]; //최솟값과 i번째 배열 값 바꿔줌
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 출력 
	return 0;
}

int insertionSort(int *a) //삽입정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; // 삽입될 숫자인 i번째 정수를 t에 담음
		j = i; // i의 값을 j에 담음
		while (a[j-1] > t && j > 0) //j - 1번째 원소보다 t가 클때, j가 음수가 아닐때 까지 반복
		{
			a[j] = a[j-1]; // 배열의 왼쪽으로 이동
			j--; // j값 감소
		}
		a[j] = t; // j번쨰에 t 담음
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 출력

	return 0;
}

int bubbleSort(int *a) // 버블정렬
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++) //배열 사이즈만큼 반복
	{
		for (j =MAX_ARRAY_SIZE-1;j>i;j--) //배열의 각각의 요소에 접근하기 위해 반복
		{
			if (a[j-1] > a[j]) // j - 1번째 요소가 j번째 요소보다 크면 
			{
				t = a[j-1]; // 서로의 위치 변경
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 출력

	return 0;
}

int shellSort(int *a) //쉘정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //h 값을 반으로 줄이다가, h가 1보다 작으면 종료
	{
		for (i = 0; i < h; i++) // 부분 리스트의 개수는 h와 같음
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // i+h 요소에 대한 삽입 정렬
			{
				v = a[j];//v는 j번째 값
				k = j;//k를 이용해 j 이전 인덱스 앞부분 조사
				
				while (k > h-1 && a[k-h] > v) ////k-h번 값이 현재 조사하는 값보다 크면
				{
					a[k] = a[k-h]; //한칸 뒤로 밀기
					k -= h;
				}
				a[k] = v; //k의 자리에 값 대입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 출력

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];//피봇은 맨 오른쪽
		i = -1;//left는 배열의 맨 왼쪽 -1
		j = n - 1;//right는 배열의 맨 오른쪽

		while(1)
		{
			while(a[++i] < v);//i번째 값이 피봇보다 작으면 i++
			while(a[--j] > v);//j번째 값이 피봇보다 크면 j++

			if (i >= j) break;//i와 j가 교차되면 while문 종료
			t = a[i];
			a[i] = a[j];
			a[j] = t;
			//i번째 값과 j번째 값을 바꿔줌
		}
		t = a[i]; 
		a[i] = a[n-1];
		a[n-1] = t;
		// 피봇과 교차된 부분에서의 값을 바꿔줌
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
		//교차된 부분을 기준으로 두개로 나누어 재귀 호출
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) //해시 테이블 값 모두 -1로 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; // a[i]를 키로 설정
		hashcode = hashCode(key); //해시 함수를 통해 키에 따른 해시코드 부여
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //해시코드에 대한 테이블에 값이 없으면
		{
			hashtable[hashcode] = key; //해시코드에 대한 테이블에 키값을 대입
		} else 	{

			index = hashcode;//index는 해시코드

			while(hashtable[index] != -1) //index에 대한 해시 테이블 값이 존재한다면, 즉 빈 버킷이 없으면
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // index를 증가시켜 다른 버킷을 찾음
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //index에 대한 테이블값에 키를 대입
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); //키값에 따른 해시코드를 구해 인덱스를 정함

	if(ht[index] == key) //키값과 인덱스에 대한 해시테이블 값이 일치하면
		return index; // 인덱스 반환

	while(ht[++index] != key) //index값을 증가시키면서
	{
		index = index % MAX_HASH_TABLE_SIZE; // 해시코드 새로 생성
	}
	return index; // 인덱스 반환
}



