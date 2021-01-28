#include "Control.hpp"

Control::Control()
{
	text = new List * ();
	lineCount = 0;
}

void Control::ListCount() //Text dosyasini acarak her satirdaki eleman sayisini ve toplam satir sayisini
{                         //sayan metot.
	ifstream read;
	read.open("Sayilar.txt");

	if (read.is_open())
	{
		int counter = 0;
		string line = "";

		while (!read.eof())
		{
			getline(read, line);                //Okunan her satir icin bir List nesnesi olusturulur.
			text[counter] = new List();         //Satir okunur.
			text[counter]->nodeCount = count(line.begin(), line.end(), ' ') + 1;
			counter++;                         //Satirdaki elemanlari satirdaki ' ' sayisina gore saymaktadir.
		}                            //Bu yuzden Sayilar.txt dosyasinin formatinda duzensizlik olursa metot dogru calismaz.
		lineCount = counter;
	}
	read.close();
}

void Control::ReadLines()           //Text dosyasini okuyarak elemanlari dinamik yapiya alan metot.
{
	ifstream read;
	read.open("Sayilar.txt");

	if (read.is_open())
	{
		int number = 0;

		for (int j = 0; j < lineCount; j++) //Toplam satir sayisi kadar donecek olan metot.
		{
			read >> number;

			if (text[j]->mid == NULL) //Satirdaki list yapisinin ilk elemanina Node atamasi yapilir
			{                        // ve ilk okunan deger bu Node nesnesine deger olarak verilir.
				text[j]->mid = new Node(number, NULL, NULL); //Ayrica dokumanda belirtildigi uzere orta(mid) olarak atanir.
			}

			for (int i = 0; i < text[j]->nodeCount / 2; i++) //Satirdaki elemanlarin yarisini prev tarafina sirayla atar.
			{
				read >> number;
				text[j]->AddPrev(number, i + 1);

			}

			for (int i = 0; i < text[j]->nodeCount / 2; i++)//Satirdaki elemanlarin yarisini next tarafina sirayla atar.
			{
				read >> number;
				text[j]->AddNext(number, i + 1);

			}

			Node* temp1 = NULL, * temp2 = NULL;

			temp1 = text[j]->mid;
			temp2 = text[j]->mid;

			for (int i = 0; i < text[j]->nodeCount / 2; i++)
			{
				temp1 = temp1->next;
			}
			for (int i = 0; i < text[j]->nodeCount / 2; i++)
			{
				temp2 = temp2->prev;
			}

			temp2->prev = temp1;              //Prev tarafinin sonundaki eleman Next tarafinin sonundaki eleman ile
			temp1->next = temp2;              //karsilikli baglanir ve dairesel yapi olusmus olur.
		}
	}
	read.close();
}

void Control::FindMinMax()   //Listelerin en kucuk ve en buyuklerini bulan metot.
{
	int minIndex = 0, maxIndex = 0;   //En kucuk orta(mid) degerine sahip listelerin TEXT[] yapisindeki indexleri tutulur.
	int minValue, maxValue;

	minValue = maxValue = text[0]->mid->value; // Baslangic olarak en kucuk ve en buyuk degerleri tutacak olan degiskenlere
                                               // Sayilar.txt dosyasi disinda baslangic degeri atamamak icin baslangic degerleri
	for (int i = 0; i < lineCount; i++)        // ilk satirin orta degeri olarak atanir.
	{

		if (text[i]->mid->value < minValue)
		{
			minIndex = i;
			minValue = text[i]->mid->value;
		}

		if (text[i]->mid->value > maxValue)   //Karsilastirmalar sonunda degerler ve bulunduklari listelerin indexleri bulunur.
		{
			maxIndex = i;
			maxValue = text[i]->mid->value;
		}
	}

	SwapWings(minIndex, maxIndex);   // Listelerin sag ve sol kollarinin caprazlamasi icin cagirilan metot.

}

void Control::SwapWings(int minIndex, int maxIndex)  //Caprazlama metotu.
{
	List *listTemp1,*listTemp2;
	List* min = new List(); //Asil yapiyi yapilan islemlerden etkilememek ve orjinal yapiyi korumak adina olusturulan
	List* max = new List(); //en kucuk ve en buyuk listeleri tutacak olan List nesneleri.
	listTemp1=min;
	listTemp2=max;

	min = text[minIndex];  //Parametre olarak alinan indexler sayesinde en kucuk ve en buyuk listeler min ve max isimli
	max = text[maxIndex];  //nesnelere ataniyor.

	int relinkCount = 0; //Eleman sayisi fazla olan listenin fazlalik sayisini tutacak olan degisken.
	int swapCount = 0;  // 2 liste arasinda yapilacak direk yer degistirme sayisi icin degisken.
	bool equalNodes = false; // 2 listenin eleman sayilarinin esit olup olmadigini tutan boolean degisken.

	if (min->nodeCount < max->nodeCount) //Listelerin dugum sayilari kontrol edilip kucuk olanlar bulunuyor ve bu sayede
	{                                   // direk yerdegistirme islemi sayisi bulunuyor.
		swapCount = min->nodeCount / 2;
		equalNodes = false;
	}
	else if (max->nodeCount < min->nodeCount)
	{
		swapCount = max->nodeCount / 2;
		equalNodes = false;
	}
	else
	{
		swapCount = min->nodeCount / 2;
		equalNodes = true;
	}

	Node* minTemp = NULL, * maxTemp = NULL;

//***************************************// maxSol ve minSag kanatlarinin caprazlamasi.


	for (int i = 0; i < swapCount; i++)  // Direk yer degistirme sayisi kadar yer degisimi yapiliyor.
	{
		minTemp = min->mid;
		maxTemp = max->mid;

		for (int j = 0; j <= i; j++) //Temp pointerlari yer degisecek olan dugumlere ilerletiliyor.
		{
			maxTemp = maxTemp->prev;
		}

		for (int j = 0; j <= i; j++)
		{
			minTemp = minTemp->next;
		}

		SwapNodes(minTemp, maxTemp); // Direk yer degisim metotu.
	}

	

	if (!equalNodes) //Eleman sayilari esit ise direk yer degistirmeden sonra fazlalik isleme
	{                // gerek kalmayacagindan boolen degeri kontrol eden kosul yapisi.

		if (min->nodeCount > max->nodeCount) // Buyuk olan listeyi bulmak icin kosul yapisi.
		{
			relinkCount = (min->nodeCount - max->nodeCount) / 2; // Fazlalik islem sayisi.

			for (int i = 0; i < relinkCount; i++)
			{
				minTemp = min->mid; //Her adimda tekrar mid nesnesine sabitleme.
				maxTemp = max->mid;

				for (int j = 0; j < swapCount + 1; j++) //Ilerletme islemleri
				{
					minTemp = minTemp->next;
				}

				for (int j = 0; j < swapCount + i; j++)
				{
					maxTemp = maxTemp->prev;
				}

				RelinkPrev(maxTemp, minTemp); // Fazlalik olan metotun mevcut listesinden koparilip
				max->nodeCount++;            // yeni listenin soluna baglanmasini saglayan metot.
				min->nodeCount--;

				minTemp = min->mid;
				maxTemp = max->mid;
			}
		}
		else // Yukaridaki islemlerin kosul yapisinin diger degeri icin gecerli olan islemleri
		{
			relinkCount = (max->nodeCount - min->nodeCount) / 2;

			for (int i = 0; i < relinkCount; i++)
			{
				minTemp = min->mid;
				maxTemp = max->mid;

				for (int j = 0; j < swapCount + 1; j++)
				{
					maxTemp = maxTemp->prev;
				}

				for (int j = 0; j < swapCount + i; j++)
				{
					minTemp = minTemp->next;
				}

				RelinkNext(minTemp, maxTemp);
				max->nodeCount--;
				min->nodeCount++;
			}
		}

	}




	//**************************************** maxSag ve minSol caprazlamasi




	for (int i = 0; i < swapCount; i++)
	{
		minTemp = min->mid;
		maxTemp = max->mid;

		for (int j = 0; j <= i; j++)
		{
			maxTemp = maxTemp->next;
		}

		for (int j = 0; j <= i; j++)
		{
			minTemp = minTemp->prev;
		}

		SwapNodes(minTemp, maxTemp);
		minTemp = min->mid;
		maxTemp = max->mid;
	}

	if (!equalNodes)
	{
		if (min->nodeCount > max->nodeCount)
		{

			for (int i = 0; i < relinkCount; i++)
			{
				minTemp = min->mid;
				maxTemp = max->mid;

				for (int j = 0; j < swapCount + i; j++)
				{
					maxTemp = maxTemp->next;
				}

				for (int j = 0; j < swapCount + 1; j++)
				{
					minTemp = minTemp->prev;
				}

				RelinkNext(maxTemp, minTemp);
				max->nodeCount++;
				min->nodeCount--;
			}
		}
		else
		{

			for (int i = 0; i < relinkCount; i++)
			{
				minTemp = min->mid;
				maxTemp = max->mid;

				for (int j = 0; j < swapCount + i; j++)
				{
					maxTemp = maxTemp->next;
				}

				for (int j = 0; j < swapCount + 1; j++)
				{
					minTemp = minTemp->prev;
				}

				RelinkNext(maxTemp, minTemp);
				max->nodeCount++;
				min->nodeCount--;
			}
		}
	}

	Print(minIndex, maxIndex); // Islemler gerceklestirildikten sonra ekrana yazma metotu.
	delete listTemp2;
	delete listTemp1;

}


void Control::SwapNodes(Node* min, Node* max) // Direk yer degistirme metotu. 2 dugumun listedeki next ve prev
{                                            // isaretcilerinin digerlerine baglanmasiyla yer degisimi saglanir.
	Node* minPrev, * minNext, * maxPrev, * maxNext;

	minPrev = min->prev;
	minNext = min->next;
	maxPrev = max->prev;
	maxNext = max->next;

	max->next = minNext;
	max->prev = minPrev;
	minNext->prev = max;
	minPrev->next = max;

	min->next = maxNext;
	min->prev = maxPrev;
	maxNext->prev = min;
	maxPrev->next = min;

}


void Control::RelinkPrev(Node* root, Node* newNode) // Koparip prev baglama metotu.
{
	newNode->next->prev = newNode->prev;  //Once nesne eski baglarindan koparilir ve sagindaki ve solundaki 
	newNode->prev->next = newNode->next;  // nesneler birbirine baglanarak yapi butunlugu korunur

	newNode->next = newNode->prev = NULL; //nesnenin next ve prev baglari sifirlanir.

	root->prev->next = newNode;  // yeni nesne , diger listedeki belirli olan listenin soluna baglanir.
	newNode->next = root;
	newNode->prev = root->prev;
	root->prev = newNode;
}

void Control::RelinkNext(Node* root, Node* newNode) // Koparip next baglama metotu.
{
	newNode->next->prev = newNode->prev;
	newNode->prev->next = newNode->next;

	newNode->next = newNode->prev = NULL;

	root->next->prev = newNode;
	newNode->prev = root;
	newNode->next = root->next;
	root->next = newNode;
}

void Control::Print(int minIndex,int maxIndex) //yazdirma metotu
{
	cout << "En Buyuk Liste Orta Dugum Adres : " << text[maxIndex]->mid << endl;
	cout << "En Buyuk Liste Degerler : " << endl;

	Node* temp = text[maxIndex]->mid;
	for (int i = 0; i < (text[maxIndex]->nodeCount) / 2 ; i++)
	{
		temp = temp->prev;
	}

	for (int i = 0; i < text[maxIndex]->nodeCount; i++)
	{
		cout << temp->value << " ";
		temp = temp->next;
	}
	cout << endl << endl;


	cout << "En Kucuk Liste Orta Dugum Adres : " << text[minIndex]->mid << endl;
	cout << "En Kucuk Liste Degerler : " << endl;

	temp = text[minIndex]->mid;
	for (int i = 0; i < (text[minIndex]->nodeCount) / 2; i++)
	{
		temp = temp->prev;
	}

	for (int i = 0; i < text[minIndex]->nodeCount; i++)
	{
		cout << temp->value << " ";
		temp = temp->next;
	}
	cout << endl << endl;

}

Control::~Control()
{
	Node *temp;

	for(int i = 0; i< lineCount; i++)
	{
		temp = text[i]->mid;

		for (int j = 0; j < text[i]->nodeCount ; j++)
		{
			for(int k = text[i]->nodeCount - j; k > 1 ; k--)
			{
				temp=temp->prev;
			}

			temp->next = temp->prev = NULL;
			delete temp;
			if(text[i]->mid)
				temp = text[i]->mid;
		}
		
	}
}
