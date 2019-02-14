/******************************************************************************************************************************
*   Program: Bilgisayar hakk�nda netbios ad�n�,kullan�c� ad�n�,CPU core say�s�n� ve mimarisini g�steren win32 api uygulamas�  *
*   Yazan ��rencinin Numaras�: 151220051                                                                                      *
*   Yazan ��rencinin Ad� Soyad�: Zekeriya Furkan INCE                                                                         *
*   Yaz�lma Tarihi: 01/12/2018 12:54																						  *
*   Degistirme Nedeni: MessageBox() fonksiyonunda tam olarak ��kt� verildi.                                                   *  
*******************************************************************************************************************************/


#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <Windows.h>

// karakter dizelerinin uzunlugu
#define INFO_BUFFER_SIZE 32767

// DLL'i yuklemek icin gerekli
typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);

// Bilgisayarin gerekli bilgilerin alinmasi
LPCWSTR DisplayTextSistemBilgileri()
{
	// bilgisayar kullanici adinin alinmasi
	TCHAR  pszUserNameBilgi[INFO_BUFFER_SIZE];
	DWORD  dwbufUserNameCount = INFO_BUFFER_SIZE;
	
	if (!GetUserName(pszUserNameBilgi, &dwbufUserNameCount))
	{
		printf("HATA VAR");
	}

	// bilgisayarin NETBIOS adinin alinmasi
	TCHAR  pszComputerNameBilgi[INFO_BUFFER_SIZE];
	DWORD  dwbufComputerNameCount = INFO_BUFFER_SIZE;
	
	if (!GetComputerName(pszComputerNameBilgi, &dwbufComputerNameCount))
	{
		printf("HATA VAR");
	}

	//TCHAR t�r�nden dizi olusturma cikti icin
	TCHAR pszValueTextCikti[INFO_BUFFER_SIZE]; 
	
	// bilgisayar sistemin mimari bilgilerin alinmasi
	PGNSI pGNSI;
	SYSTEM_INFO SistemBilgi;
	pGNSI = (PGNSI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");

	// Sayet DLL mevcutsa okuyacak yoksa kutuphaneden okuyacak
	if (pGNSI != NULL)
		pGNSI(&SistemBilgi);
	else
		GetNativeSystemInfo(&SistemBilgi);

	// Bilgisayar mimari icin karsilastirma
	if (SistemBilgi.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
		_sntprintf_s(pszValueTextCikti, INFO_BUFFER_SIZE, _T("Bilgisayar : %s\nKullan�c� : %s\nI�lem�i : %d\nMimari: 64 - bit\n"), 
															pszComputerNameBilgi, pszUserNameBilgi, SistemBilgi.dwNumberOfProcessors);
	}
	else if (SistemBilgi.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
		_sntprintf_s(pszValueTextCikti, INFO_BUFFER_SIZE, _T("Bilgisayar : %s\nKullan�c� : %s\nI�lem�i : %d\nMimari: 32 - bit\n"), 
														    pszComputerNameBilgi, pszUserNameBilgi, SistemBilgi.dwNumberOfProcessors);
	}

	return pszValueTextCikti;
}


int main()
{
	// Ekrana mesaj kutusu ile bilgi vermek icin
	int iReturnMessageBox = MessageBox(NULL,DisplayTextSistemBilgileri(),L"Sistem Bilgisi",MB_ICONINFORMATION | MB_DEFBUTTON2);

	if(iReturnMessageBox != 1)
		printf("HATA VAR");

	return 0;
}