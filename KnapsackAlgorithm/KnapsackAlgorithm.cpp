#include <stdio.h>
#include <stdlib.h>
#include <vcruntime_string.h>


//GLOBAL DEGISKENLER
unsigned long long int packWeight = 0;	//Var olan problemimiz icin (cantanin) maksimum alabilecegi agirlik ve verilerin dizi uzunluk degerini tuttugumuz global degiskenler.
long long int packArraySize = 0;    
FILE* filePointer;

//Dinamik dizinin rahat ve hizli bir sekilde kullanimi icin tanimladigimiz struct yapisi.
struct dynamicArray {
	unsigned long long int arraySize;
	unsigned long long int indis;
	unsigned long long int* arrayName;
};
typedef struct dynamicArray array;

//Kullanilacak olan dinamik array'lerin bildirimi
array valuesArray;
array weightsArray;

//Dinamik dizi icin bellekten alan tahsisi.
void createArray(array* d, unsigned long long int sizeVal)
{
	d->arrayName = (unsigned long long int*)malloc(sizeVal * sizeof(unsigned long long int));
	d->arraySize = sizeVal;
	d->indis = 0;
}

//Dinamik dizi degerinin ilk tanimdan buyuk olmasi durumunda genisletme ve bellekten ek alan alma.
void expandArray(array* d)
{
	if (d->indis == d->arraySize) //Yine de maksimum indis degeri ile tanimli dizi genisligini karsilastiyoruz.
	{
		unsigned long long int *cntrl;
		d->arraySize++;
		cntrl = (unsigned long long int*)realloc(d->arrayName, sizeof(unsigned long long int) * d->arraySize);
		//Bellekten alan alinamamasi durumunda uyari almasi icin duzenliyoruz.
		if (cntrl != NULL)	
			d->arrayName = cntrl;
		else				
			printf("Memory Fault!");

	}
}

//Dinamik diziye bellek ekleme ve indis degerinin arttirilamasi.
void addArray(array* d, unsigned long long int v)
{
	expandArray(d);
	d->arrayName[d->indis++] = v;
}

//Dinamik dizi alanini tamimiyla silinerek bellege iadesi.
void freeArray(array* d)
{
	free(d->arrayName);
	d->arraySize = 0;
	d->indis = 0;
}

//Dizi degerlerini yazdirilmasi icin kullandigimiz fonksiyon.
void writeArray(array* d)
{
	unsigned long long int i;
	for (i = 0; i < d->indis; i++)
		printf("%lld\n", d->arrayName[i]);
}



/* 	Menu Fonksiyonu
	Bu fonksiyonun amaci kullaniciya islem yapmak istedigi dosyayi sectirmek. Ve dosya ismini proje geneline hazir hale getirerek, islemleri hazirlamak.
	Ornegin 1 girildigin ks_4_0.txt adli 4 adet degere sahip liste isleme alinacaktir.
*/
void menu()
{
	int choise = 0;
	printf("*****************************************  MENU  *****************************************\n\n");
	printf("Backpack Algorithm Select the file to be applied. (Enter Line Number: -> Simple; 1)\n");
	printf("1-ks_4_0.txt\n2-ks_100_0.txt\n3-ks_10000_0.txt\nSelect:");
	scanf_s("%d", &choise);

	switch (choise)
	{
		case 1:		filePointer = fopen("ks_4_0.txt", "r");		break;
		case 2:		filePointer = fopen("ks_100_0.txt", "r");	break;
		case 3:		filePointer = fopen("ks_10000_0.txt", "r");	break;
		default:
			system("cls"); //Console Ekrani Temizleme
			printf("***************************  Incorrect Entry! Please Try Again.  ***************************\n\n");
			menu();
	}
}

//Txt dosyasi icerisinde tanimli degerleri dosyadan okuyarak dinamik olarak bildirdigimiz dizi icerisinde tanimliyoruz.
void fileItemGetArray()
{
	unsigned long long int temp = 0;
	long long int counter = 0;
	while (fscanf(filePointer, "%lld", &temp) != EOF)
	{
		if (counter == 0)
		{
			//Dosyadan alinan eleman sayisi metrigine gore dinamik dizi tanimi
			packArraySize = temp;
			createArray(&valuesArray, packArraySize);
			createArray(&weightsArray, packArraySize);
		}
		else if (counter == 1)	packWeight = temp;
		else
		{
			if (counter % 2 == 0)	addArray(&valuesArray, temp);
			else					addArray(&weightsArray, temp);
		}
		counter++;
	}
	//writeArray(&valuesArray);
	//writeArray(&weightsArray);

	fclose(filePointer);
}

//Iki deger arasinda maksimum degerin secimi
unsigned long long max(unsigned long long int a, unsigned long long int b) { return (a > b) ? a : b; }

//Knapsack islemlerini gerceklestirdigimiz canta agirligini, cantadaki array uzunluklarini ve var olan agirlik deger, agirlik dinamik dizilerini parametre olarak alir.
long long int knapsackAlgorithm(unsigned long long int W, array* wt, array* val, unsigned long long int n)
{
	long long int i=0;
	unsigned long long int w=0, dp[100001]={};
	memset(dp, 0, sizeof(dp));

	for(i = 1; i < n + 1; i++)
	{
		for(w = W; w > 0; w--)
		{
			if (wt->arrayName[i - 1] <= w)
			{
				dp[w] = max(dp[w], dp[w - wt->arrayName[i - 1]] + val->arrayName[i - 1]);
				//printf("\ndp[w] Degeri: %lld \t dp[w - wt->arrayName[i - 1]] + val->arrayName[i - 1] Degeri:%lld", dp[w], dp[w - wt->arrayName[i - 1]] + val->arrayName[i - 1]);
			}
		}
	}

	return dp[W];
}

int main(int argc, char* argv[]) {
	menu();
	fileItemGetArray();
	printf("\nPackWeight: %lld, packArraySize: %lld", packWeight, packArraySize);
	printf("\nResult = %lld", knapsackAlgorithm(packWeight, &weightsArray, &valuesArray, packArraySize));


	//Dinamik olarak almis oldugumuz dizileri iade ediyoruz.
	freeArray(&valuesArray);
	freeArray(&weightsArray);
	return 0;
}