#include <stdio.h>
#include <stdlib.h>
#include <vcruntime_string.h>


//GLOBAL DEGISKENLER
long long int packWeight = 0, packArraySize = 0;    //Var olan problemimiz icin (cantanin) maksimum alabilecegi agirlik ve verilerin dizi uzunluk degerini tuttugumuz global degiskenler.
FILE* filePointer;

//Dinamik dizinin rahat ve hizli bir sekilde kullanimi icin tanimladigimiz struct yapisi.
struct dynamicArray {
	long long int arraySize;
	long long int indis;
	long long int* arrayName;
};
typedef struct dynamicArray array;

//Kullanilacak olan dinamik array'lerin bildirimi
array valuesArray;
array weightsArray;

//Dinamik dizi icin bellekten alan tahsisi.
void createArray(array* d, long long int sizeVal)
{
	d->arrayName = (long long int*)malloc(sizeVal * sizeof(long long int));
	d->arraySize = sizeVal;
	d->indis = 0;
}

//Dinamik dizi degerinin ilk tanimdan buyuk olmasi durumunda genisletme ve bellekten ek alan alma.
void expandArray(array* d)
{
	if (d->indis == d->arraySize) //Yine de maksimum indis degeri ile tanimli dizi genisligini karsilastiyoruz.
	{
		d->arraySize++;
		d->arrayName = (long long int*)realloc(d->arrayName, sizeof(long long int) * d->arraySize);
	}
}

//Dinamik diziye bellek ekleme ve indis degerinin arttirilamasi.
void addArray(array* d, long long int v)
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
	long long int i;
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
	long long temp = 0, counter = 0;
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
long long max(long long int a, long long int b) { return (a > b) ? a : b; }

// Returns the maximum value that
// can be put in a knapsack of capacity W
long long int knapSack(long long int W, array* wt, array* val, long long int n)
{
	long long int i=0;
	long long w=0, dp[100001]={};
	memset(dp, 0, sizeof(dp));

	for (i = 1; i < n + 1; i++)
	{
		for (w = W; w >= 0; w--)
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
	printf("\nResult = %lld", knapSack(packWeight, &weightsArray, &valuesArray, packArraySize));


	//Dinamik olarak almis oldugumuz dizileri iade ediyoruz.
	freeArray(&valuesArray);
	freeArray(&weightsArray);
	return 0;
}