#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
using namespace std;
class hesap1{
	private:
		char urunID[4];
		char urunADET[5];
		char urunISMI[30];
		string okunan,eslesme,eslesme2;
		string idokunan,idokunan2;
		string id_donustur;
		string listeoku;
	public:
		//BA�LIKLARI YAZDIRMAK ���N YAPICI FONKS�YON
		hesap1(){
			string baslikoku="";
			int satir=0;
			ofstream baslik_yazdir("urun_bilgi.txt",ios::app);
			baslik_yazdir.setf(ios::left);
			ifstream baslik("urun_bilgi.txt");
			while(!baslik.eof()){
				satir++;
				getline(baslik,baslikoku);
				if(satir==1 && baslikoku==""){
					baslik_yazdir << setw(12) << "URUN ID" << setw(30) << "URUN ISMI" << setw(12) << "URUN ADET" << endl;
					baslik_yazdir.close();
				}
				else{
					break;
				}
			}	
		}
		~hesap1(){
		}
		void setisim(char y_isim[30]){
			for(int i=0;i<30;i++){
				urunISMI[i]=y_isim[i];
			}
		}
		void setadet(char y_adet[5]){
			for(int i=0;i<5;i++){
				urunADET[i]=y_adet[i];
			}
		}
		void ekle(){
			int idsayi;
			int adetSayi;
			ofstream urun_bilgi("urun_bilgi.txt",ios::app);
			int sayac=0,dogruluk=0;
			ifstream id_bak("urun_bilgi.txt");
			int s_sayi=0;
			
			//�R�N ID ATAMAK ���N
			while(!id_bak.eof()){
				s_sayi++;
				sayac++;	
				getline(id_bak,idokunan);
				id_donustur=idokunan.substr(0,4);
				for(int i=0;i<4;i++){
					urunID[i]=id_donustur[i];
				}
				urun_bilgi.setf(ios::left);
				if(sayac==2){
					//DOSYA BO� �SE �LK ID OLARAK 1000 ATANIYOR
					if(strlen(urunID)==0){
						dogruluk=1;
						urun_bilgi << setw(12) << "1000";
					}
				}
			}
			id_bak.close();
			int s_sayi2=0;
			ifstream id_bak2("urun_bilgi.txt");
			while(!id_bak2.eof()){
				s_sayi2++;
				getline(id_bak2,idokunan2);
				//SON SATIR BO� OLDU�U ���N B�R �NCEK� SATIRIN �D DEGER�N� OKUYOR VE B�R ARTTIRARAK YEN� ID OLUSTURUYOR
				if(s_sayi2==(s_sayi-1)){
					id_donustur=idokunan2.substr(0,4);
					for(int i=0;i<4;i++){
						urunID[i]=id_donustur[i];
					}
				idsayi=atoi(urunID);
				adetSayi=atoi(urunADET);
				if(dogruluk==0){
					urun_bilgi << setw(12) << (idsayi-adetSayi)/1000+1;
				}
				}
			}
			//G�NCELLEME ESNASINDA �LK HARF� ALMIYOR
			urun_bilgi<< setw(30) << urunISMI << setw(10) << urunADET << endl;
			cout << "�r�n ba�ar�yla kaydedildi!\n";
			urun_bilgi.close();		
		}
		void listele(){
			//KAYITLI �R�NLER EKRANA YAZDIRILIYOR
			ifstream listele("urun_bilgi.txt");
			while(!listele.eof()){
				getline(listele,listeoku);
				cout << listeoku << endl;
			}
			listele.close();
		}
		
		void ara(int secim2,int isim_kontrol){
			int id_kontrol;
			int hata=0;
			if(secim2==1){
				//ID NO �LE ARAMA YAPILIYOR
				do{
					cout << "�r�n ID: "; cin >> urunID; cin.ignore();
					id_kontrol=strlen(urunID);
					if(id_kontrol!=4) cout << "L�tfen ge�erli ID giriniz!\n";
				}while(id_kontrol!=4);
				//URUN DOSYADAN OKUNUYOR VE KONTROL �SLEM� YAPILIYOR
				ifstream urunid_oku("urun_bilgi.txt");
				while(!urunid_oku.eof()){
					getline(urunid_oku,okunan);
					eslesme=okunan.substr(0,4);
					if (eslesme==urunID){
						hata=1;
						cout.setf(ios::left);
						cout << endl << setw(12) << "URUN ID" << setw(30) << "URUN ISMI" << setw(12) << "URUN ADET" << endl;
						cout << okunan <<endl << endl;
					}
				}
				if(hata==0) cout << "Bu ID numaras�na ait �r�n bulunamad�!" << endl;
				urunid_oku.close();
			}
			if(secim2==2){
				//�R�N �SM� �LE ARAMA YAPILIYOR
				do{
					cout << "�r�n �smi: "; cin.ignore(); gets(urunISMI); strlwr(urunISMI);
					isim_kontrol=strlen(urunISMI);
					if(isim_kontrol>25) cout << "L�tfen ge�erli �r�n ismi giriniz!\n";
				}while(isim_kontrol>25);
				cout.setf(ios::left);
				cout << endl << setw(12) << "URUN ID" << setw(30) << "URUN ISMI" << setw(12) << "URUN ADET" << endl;
				//�R�N DOSYADAN OKUNUYOR VE KONTROL ��LEM� YAPILIYOR
				int onay=0;
				string gonder;
				ifstream urunisim_oku("urun_bilgi.txt");
				while(!urunisim_oku.eof()){
					getline(urunisim_oku,okunan);			
					for(int i=12;i<(12+strlen(urunISMI));i++){
						gonder+=okunan[i];	
					}
					if(urunISMI==gonder){
						cout << okunan << endl << endl;
						onay=1;
						//�NCEK� B�LG�N�N �ST�NE YAZMAMASI ���N DE���KEN TEM�ZLEN�YOR
						gonder="";
					}
					//�NCEK� B�LG�N�N �ST�NE YAZMAMASI ���N DE���KEN TEM�ZLEN�YOR
					else{
						gonder="";
					}
				}
				if(onay==0) cout << "-Arad���n�z �r�ne ait bir kay�t bulunamad�-" << endl;
				urunisim_oku.close();
			}
		}
}urun;

class hesap2{
	private:
		char urunID[4];
		char urunADET[5];
		char urunISMI[30];
		string okunan,eslesme,eslesme2;
		string idokunan,idokunan2;
		string id_donustur;
		string listeoku;
		//S�PAR�� DE���KENLER�
		char s_urunID[4];
		int s_urunADET;
		int s2_urunADET;
		char k_sirketi[10];
		char siparisID[6];
		string s_okunan;
	public:
		string sip_id;
		int id_kontrol;
		//BA�LIKLARI YAZDIRMAK ���N YAPICI FONKS�YON
		hesap2(){
			string baslikoku="";
			int satir=0;
			ofstream baslik_yazdir("siparis_bilgi.txt",ios::app);
			baslik_yazdir.setf(ios::left);
			ifstream baslik("siparis_bilgi.txt");
			while(!baslik.eof()){
				satir++;
				getline(baslik,baslikoku);
				if(satir==1 && baslikoku==""){
					baslik_yazdir << setw(15) << "SIPARIS ID" << setw(12) << "URUN ID" << setw(30) << "URUN ISMI" << setw(12) << "URUN ADET"  << setw(12) << "KARGO S."<< endl;
					baslik_yazdir.close();
				}
				else{
					break;
				}
			}	
		}
		~hesap2(){
		}
	void sil(){
		//�R�N S�LME ��LEM� YAPILIYOR
		//DI�ARIDAN G�R�LEN ID DI�INDAK� B�T�N SATIRLAR BA�KA DOSYAYA YAZDIRILIYOR B�YLECE �STEN�LEN �R�N S�L�NM�� OLUYOR
		do{
				cout << "�r�n ID: "; cin >> urunID; cin.ignore();
				id_kontrol=strlen(urunID);
				if(id_kontrol!=4) cout << "L�tfen ge�erli ID giriniz!\n";
			}while(id_kontrol!=4);
			system("cls");		
			
			ifstream dosyaoku("urun_bilgi.txt");
			while(!dosyaoku.eof()){
				getline(dosyaoku,okunan);
				eslesme=okunan.substr(0,4);
		//ESLESME YOKSA BA�KA DOSYAYA YAZDIR
				if(urunID!=eslesme){
					//B�R SATIR BO�LUK BIRAKMASINI ENGELLEMEK ���N
					if(okunan!=""){
						ofstream yenidosya("yenibilgi.txt",ios::app);
						yenidosya << okunan << endl;
						yenidosya.close();
					}
				}
			}
			dosyaoku.close();
			//�LK DOSYA S�L�N�YOR
			remove("urun_bilgi.txt");
			//perror("hata: "); // HATA KODUNU G�STER�YOR
			//YEN� DOSYANIN ADINI �LK DOSYANIN ADIYLA DE���T�R�YOR B�YLECE MAIN DOSYAMIZ OLARAK DEVAM ED�YOR
			rename("yenibilgi.txt","urun_bilgi.txt");
			cout << "�r�n ba�ar�yla silindi\n";
	}
	void guncelle(){
		//�R�N G�NCELLEME
		do{
				cout << "G�ncellemek �stedi�iniz �r�n�n ID NUMARASINI Giriniz: "; cin >> urunID; cin.ignore();
				id_kontrol=strlen(urunID);
				if(id_kontrol!=4) cout << "L�tfen ge�erli ID giriniz!\n";
			}while(id_kontrol!=4);
			system("cls");		
			ifstream dosyaoku("urun_bilgi.txt");
			while(!dosyaoku.eof()){
				getline(dosyaoku,okunan);
				eslesme=okunan.substr(0,4);
		//ESLESME YOKSA BA�KA DOSYAYA YAZDIR
				if(urunID!=eslesme){
					//B�R SATIR BO�LUK BIRAKMASINI ENGELLEMEK ���N
					if(okunan!=""){
						ofstream yenidosya("yenibilgi.txt",ios::app);
						yenidosya << okunan << endl;
						yenidosya.close();
					}
				}
				
				else if(urunID==eslesme){
					eslesme2=urunID;
				}				
			}
			dosyaoku.close();
			remove("urun_bilgi.txt");
			rename("yenibilgi.txt","urun_bilgi.txt");
			
			//�R�N KAYIT
			ofstream urun_bilgi("urun_bilgi.txt",ios::app);
			urun_bilgi.setf(ios::left);
			do{
				cout << "YEN� �r�n �smi: "; cin.ignore(); gets(urunISMI); strlwr(urunISMI);
				if(urunISMI=="") cout << "Lutfen isim alan�n� bo� b�rakmay�n�z..." << endl;
			}while(urunISMI=="");
			
			do{
				cout << "YEN� �r�n Adet: "; gets(urunADET);
				if(urunADET=="") cout << "L�tfen adet alan�n� bo� b�rakmay�n�z..." << endl;
			}while(urunADET=="");	
			urun_bilgi << setw(12) << eslesme2 <<setw(30) << urunISMI << setw(10) << urunADET << endl;
			cout << "�r�n ba�ar�yla g�ncellendi!\n";	
			urun_bilgi.close();
	}
	void setid2(){
		//�LK S�PAR�� ID ATAMASI YAPILIYOR
		sip_id="813278";
	}
	void sipariskayit(){
			int onaylama=0;
			int sayac=0;
			int dogruluk=0;
			int idsayi2=0;
		//S�PAR�� KAYIT
			ofstream siparis_bilgi("siparis_bilgi.txt",ios::app);
			siparis_bilgi.setf(ios::left);
			do{
				cout << "Sipari� Kayd� ��in �r�n ID Giriniz: "; cin.ignore(); gets(s_urunID);
				ifstream kontrol("urun_bilgi.txt");
				while(!kontrol.eof()){
					getline(kontrol,idokunan);
					eslesme=idokunan.substr(0,4);
					if(s_urunID==eslesme){
						//DOSYADAN OKUNAN STR�NG OLDU�U ���N CHAR T�P�NE D�N���M� BU �EK�LDE SA�LANIYOR
						//URUN_B�LG�.TXT DEN URUN ID VE URUN ISMI ALINIYOR
						for(int i=0;i<34;i++){
							s_okunan+=idokunan[i];
						}
						onaylama=1;
					}
				}
				if(onaylama=0) cout << "GE�ERS�Z �R�N ID, TEKRAR DENEY�N�Z...";
			}while(onaylama=0);
			cout << "Sipari� Edilen �r�n�n Adedini Giriniz: "; cin >> s_urunADET; cin.ignore();
			cout << "Kargo �irketini Giriniz: "; gets(k_sirketi); strupr(k_sirketi);
			//S�PAR�� ID ATAMAK ���N
			ifstream id_bak("siparis_bilgi.txt");
			int s_sayi=0;
			s2_urunADET=s_urunADET;
			while(!id_bak.eof()){
				s_sayi++;
				sayac++;
				getline(id_bak,idokunan);
				id_donustur=idokunan.substr(0,6);
				for(int i=0;i<6;i++){
					s_urunID[i]=id_donustur[i];
				}
				if(sayac==2){
				//DOSYA BO� �SE
					if(strlen(s_urunID)==0){
						dogruluk=1;
						
						siparis_bilgi << setw(15) << sip_id;
					}
				}
			}
			id_bak.close();
			int s_sayi2=0;
			ifstream id_bak2("siparis_bilgi.txt");
			//SIFIRLANDI�I ���N ATAMA YAPARAK KURTARDIM
			while(!id_bak2.eof()){
				s_sayi2++;
				getline(id_bak2,idokunan2);	
				if(s_sayi2==(s_sayi-1)){
					id_donustur=idokunan2.substr(0,6);
					for(int i=0;i<6;i++){
						s_urunID[i]=id_donustur[i];
					}
					idsayi2=atoi(s_urunID);
					if(dogruluk==0){
						siparis_bilgi << setw(15) << idsayi2+1;
					}
				}
			}
			id_bak2.close();
			siparis_bilgi << setw(42) << s_okunan << setw(12) << s2_urunADET << setw(12) << k_sirketi << endl;
			s_okunan="";
			siparis_bilgi.close();
			cout << "Sipari� Ba�ar�yla Kaydedildi!\n";
	}
	void siparissorgu(){
		//S�PAR�� SORGULAMA
		do{
			cout << "Siparis ID: "; cin >> s_urunID; cin.ignore();
			id_kontrol=strlen(s_urunID);
			if(id_kontrol!=6) cout << "L�tfen ge�erli Siparis ID giriniz!\n";
		}while(id_kontrol!=6);
		//URUN DOSYADAN OKUNUYOR VE KONTROL �SLEM� YAPILIYOR
		ifstream sipid_oku("siparis_bilgi.txt");
		while(!sipid_oku.eof()){
			getline(sipid_oku,okunan);
			eslesme=okunan.substr(0,6);
			if (eslesme==s_urunID){
				cout.setf(ios::left);
				cout << endl << setw(15) << "SIPARIS ID" << setw(12) << "URUN ID" << setw(30) << "URUN ISMI" << setw(12) << "URUN ADET"  << setw(12) << "KARGO S."<< endl;
				cout << okunan <<endl <<endl;
			}
		}
		sipid_oku.close();
	}
}urun2;

class islem:public hesap1,public hesap2{
};
int main(){
	char cevap;
	//�R�N DE���KENLER�
	char y_isim[30];
	char y_adet[5];
	int sayi_adet;
	setlocale(LC_ALL,"Turkish");
	int secim,secim2;
	int deger=0;
	int isim_kontrol;
	cout << "---SISTEME HOSGELDINIZ---\n\n";
	do{
	cout << "Hangi i�lemi yapmak istersiniz?\n1-�r�n Kay�t\n2-�r�nleri Listele\n3-�r�n Sorgu\n4-�r�n Silme\n5-�r�n G�ncelleme\n6-Sipari� Kay�t\n7-Sipari� Sorgu\n";
	hesap1 hesap1();
	do{
		cout << "\n�SLEM NO: "; cin >> secim;
		if(secim!=1 && secim!=2 && secim!=3 && secim!=4 && secim!=5 && secim!=6 && secim!=7) cout << "Lutfen dogru islem numarasi giriniz!";
	}while(secim!=1 && secim!=2 && secim!=3 && secim!=4 && secim!=5 && secim!=6 && secim!=7);
	cout << "\n";
	switch(secim){
		case 1:{
			//DI�ARIDAN �R�N �SM� VE ADED� ALINIYOR
			do{
				cout << "�r�n �smi: "; cin.ignore(); gets(y_isim); strlwr(y_isim);
				if(y_isim=="") cout << "Lutfen isim alan�n� bo� b�rakmay�n�z..." << endl;
			}while(y_isim=="");
			
			do{
				do{
				cout << "(EN AZ 100 ADET)\n�r�n Adet: "; gets(y_adet);
				sayi_adet=atoi(y_adet);
				if(sayi_adet<100) cout << "Adet say�n�z en az 100 olmal�!";
				}while(sayi_adet<100);
				if(y_adet=="") cout << "L�tfen adet alan�n� bo� b�rakmay�n�z..." << endl;
			}while(y_adet=="");
			
			urun.setisim(y_isim);
			urun.setadet(y_adet);
			urun.ekle();
			break;
		}
		case 2:{
			urun.listele();
			break;
		}
		case 3:{
			cout << "Arama i�lemini nas�l yapmak istersiniz?\n1-�r�n ID\n2-�r�n �smi\n";
			cout << "��LEM NO:"; cin >> secim2; system("cls");
			
			urun.ara(secim2,isim_kontrol);
			break;
		}
		case 4:{
			urun2.sil();
			break;
		}
		case 5:{
			urun2.guncelle();
			break;
		}
		case 6:{
			urun2.setid2();
			urun2.sipariskayit(); 
			break;
		}
		case 7:{
			urun2.siparissorgu();
			break;
		}
	}
	int kontrol=0;
		do{
			cout << "Ba�ka i�lem yapmak istiyor musunuz?(E/H): "; 
			cin >> cevap;
			if(cevap=='e' || cevap=='E' || cevap=='h' || cevap=='H'){
				kontrol=0;
			}
			else{
				kontrol=1;
				system("cls"); 
				cout << "Ger�erli bir cevap giriniz!\n";	
			}
		}while(kontrol==1);
	system("cls");
	}while(cevap=='E' || cevap=='e');
	cout << "��k�� yap�l�yor"; sleep(1); cout << "."; sleep(1); cout << "."; sleep(1); cout << ".";
	return 0;
	}
