#include <stdio.h>
#include <stdlib.h>
#include <ctime>

//GLOBAL DEGISKENLER
unsigned __int64 packWeight, packArraySize = 0;
FILE* filePointer;

//Dinamik dizinin rahat ve hizli bir sekilde kullanimi icin tanimladigimiz struct yapisi.
struct dynamicArray {
	unsigned __int64 arraySize;
	unsigned __int64 indis;
	unsigned __int64* arrayName;
};
typedef struct dynamicArray array;

//Kullanilacak olan dinamik array'lerin bildirimi
array valuesArray;
array weightsArray;
array tableArray;

//Dinamik dizi icin bellekten alan tahsisi.
void createArray(array* d, unsigned long long int sizeVal)
{
	d->arrayName = (unsigned __int64*)malloc(sizeVal * sizeof(unsigned __int64));
	d->arraySize = sizeVal;
	d->indis = 0;
}

//Dinamik dizi degerinin ilk tanimdan buyuk olmasi durumunda genisletme ve bellekten ek alan alma.
void expandArray(array* d)
{
	if (d->indis == d->arraySize) //Yine de maksimum indis degeri ile tanimli dizi genisligini karsilastiyoruz.
	{
		unsigned __int64* cntrl;
		d->arraySize++;

		//Bellekten alan alinamamasi durumunda uyari almasi icin duzenliyoruz.
		cntrl = (unsigned __int64*)realloc(d->arrayName, sizeof(unsigned __int64) * d->arraySize);
		if (cntrl == NULL)
		{
			printf("Memory Fault!");
			exit(1);
		}
		d->arrayName = cntrl;
	}
}

//Dinamik diziye bellek ekleme ve indis degerinin arttirilamasi.
void addArray(array* d, unsigned __int64 v)
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
	unsigned __int64 temp = 0, counter = 0;
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
			//Ilk iki degerde cantanin maksimum agirlik degeri, dizi uzunlugu alinmasindan sonra degerlerin ve agirliklarin diziye alinmasi.
			if (counter % 2 == 0)	addArray(&valuesArray, temp);
			else					addArray(&weightsArray, temp);
		}
		counter++;
	}
	fclose(filePointer);
}

//Iki deger arasinda maksimum degerin secimi
unsigned long long max(unsigned __int64 a, unsigned __int64 b) { return (a > b) ? a : b; }

//Knapsack islemlerini gerceklestirdigimiz canta agirligini, cantadaki array uzunluklarini ve var olan deger, agirlik verilerini barindiran dinamik dizilerini parametre olarak alir.
long long int knapsackAlgorithm(unsigned __int64 W, array* wt, array* val, unsigned __int64 n)
{									  
	unsigned __int64 i = 0, w = 0;
	createArray(&tableArray, W + 1);

	for (i = 0; i < W + 1; i++)
		tableArray.arrayName[i] = 0;

	for (i = 1; i < n + 1; i++)
	{
		for (w = W; w > 0; w--)
		{
			if (wt->arrayName[i - 1] <= w)
			{	
				tableArray.arrayName[w] = max(tableArray.arrayName[w], tableArray.arrayName[w - wt->arrayName[i - 1]] + val->arrayName[i - 1]);
			}	
		}
	}

	return tableArray.arrayName[W];
}

//Dinamik olarak almis oldugumuz dizileri iade ediyoruz.
void freeDinamicArrays()
{
	freeArray(&tableArray);
	freeArray(&valuesArray);
	freeArray(&weightsArray);
}

//Gecen islem s?renin ekrana yazdirilmasi(milisaniye)
void timer(clock_t filereadtime, clock_t start, clock_t end)
{
	printf("\nFile Read Time(MiliSecond): %lf", (double)(start - filereadtime));
	printf("\nKnapsack Time(MiliSecond): %lf\n", (double)(end - start));
}

int main(int argc, char* argv[]) {

	//Islem zamanini olcebilmek icin clock_t kutuphanesi kullaniyoruz.
	clock_t filereadtime, start, end;
	
	
	//Islem yapilacak dosyayi sectirme, dosyayi okuma islemleri
	menu();
	filereadtime = clock();
	fileItemGetArray();
	printf("\nPackWeight: %lld, packArraySize: %lld", packWeight, packArraySize);
	
	//Knapsack Algoritmasinin islenmesi
	start = clock();
	printf("\nResult = %lld\n", knapsackAlgorithm(packWeight, &weightsArray, &valuesArray, packArraySize));
	end = clock();

	timer(filereadtime, start, end);
	freeDinamicArrays();
	return 0;
}