#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATE_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <iostream>

SOCKET Connection;

//viestinn�n hallinta
void ClientThread() 
{
	int bufferlength; //puskurin pituudelle
	while (true)
	{
		recv(Connection, (char*) &bufferlength, sizeof(int), NULL);
		//luodaan puskuri joka pystyy vastaanottamaan l�hetetyn viestin
		char *buffer = new char[bufferlength+1];

		buffer[bufferlength] = '\0';
		//vastaanotetaan viesti 
		recv(Connection, buffer, bufferlength, NULL);

		std::cout << buffer << std::endl;
		delete[] buffer; //vapautetaan varattu muisti
	}
}
 
//ensin l�hetet��n kokonaisluku joka kertoo stringin pituuden jonka j�lkeen vasta l�hetet��n string


int main()
{
	//Winsockin k�ynnisty
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) // tarkastetaan mik�li wsa startup palauttaa jotain muuta kuin nollaan niin se on ep�onnistunut
	{
		MessageBoxA(NULL, "winsocketin luonti ep�onnistui", "Virhe", MB_OK | MB_ICONERROR);
		exit(1);
	}

	//luodaan osoite joka kiinnitet��n yhteys sockettiimme
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr); // tarvitaan yhteydenmuoidostamis funktioon
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8888); //Portti asetetaan 8888:i
	addr.sin_family = AF_INET;//IPv4 Socketti
	//luodaan yhteydelle Socket
	Connection = socket(AF_INET, SOCK_STREAM, NULL); 
	//tarkistetaan ett� pystyt��nk� yhteys luomaan
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0)
	{
		MessageBoxA(NULL, "yhteyden muodostaminen epaonnistui", "VIRHE!", MB_OK | MB_ICONERROR);
		return 0;
	}

	std::cout << "Yhteys Muodostettu" << std::endl;
	//Luodaan asiakkaan s�ie
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL);
	
	int SVpituus;
	recv(Connection, (char*)&SVpituus, sizeof(SVpituus), NULL);
	char* SaapuvaViesti = new char[SVpituus + 1];
	SaapuvaViesti[SVpituus] = '\0';

	//seuraavaksi vastaanotetaan viesti k�ytt�m�ll� recv() funktiota taulukkoon SaapuvatViestit
	recv(Connection, SaapuvaViesti, SVpituus, NULL);
	//printataan saapunut viesti
	std::cout << SaapuvaViesti << std::endl;

	delete[] SaapuvaViesti;

	// luodaan while loop sy�tteelle
	std::string buffer; //puskuri viestien l�hett�miselle
	while (true)
	{
		std::getline(std::cin,buffer);
		int bufferlength = buffer.size();
		//l�hetet��n puskurin pituus
		send(Connection, (char*)&bufferlength, sizeof(int), NULL);
		//l�hetet��n puskuri
		send(Connection, buffer.c_str(), bufferlength, NULL);

	}

	system("Pause");

	return 0;
}
