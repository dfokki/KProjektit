#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATE_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <iostream>

//luodaan  taulukko jonne voidaan lis‰t‰ liittyneet asiakkaat
SOCKET Connections[100];
//ConnectionCounter pit‰‰ sis‰ll‰‰n seuraavan yhteyden jota tullaan k‰ytt‰m‰‰n
int ConnectionCounter = 0;

//luodaan funktio joka k‰sittelee asiakkaiden yhteydet erikseen
//void ClientsThread(int index)
//{
//	int bufferlength; //puskurin pituudelle
//	//k‰sittelee asiakkaan l‰hett‰m‰t viestit
//	while (true)
//	{
//		//haetaan viestin pituus
//		recv(Connections[index],(char*) &bufferlength, sizeof(int), NULL);
//		//luodaan puskuri joka pystyy vastaanottamaan l‰hetetyn viestin
//		char *buffer = new char[bufferlength];
//		//vastaanotetaan viesti 
//		recv(Connections[index], buffer, bufferlength, NULL);
//		//mahdollistaa l‰hett‰misen kaikille asiakkaille 
//		for (size_t i = 0; i < ConnectionCounter; i++)
//		{
//			if (i == index)
//				continue;
//			//ensin l‰hetet‰‰n asiakkaalle viestin pituus
//			send(Connections[i],(char*) &bufferlength, sizeof(bufferlength), NULL);
//			//seuraavaksi viesti
//			send(Connections[i], buffer, bufferlength, NULL);
//			
//		}
//		delete[] buffer;
//	}
//}

//luodaan funktio joka k‰sittelee asiakkaiden yhteydet erikseen
void ClientsOrderThread(int index)
{
	int bufferlength; //puskurin pituudelle
					  //k‰sittelee asiakkaan l‰hett‰m‰t viestit
	while (true)
	{
		
		std::string check;
		//haetaan viestin pituus
		recv(Connections[index], (char*)&bufferlength, sizeof(int), NULL);
		//luodaan puskuri joka pystyy vastaanottamaan l‰hetetyn viestin
		char *buffer = new char[bufferlength + 1];

		buffer[bufferlength] = '\0';
		//vastaanotetaan viesti 
		recv(Connections[index], buffer, bufferlength, NULL);
		check.append(buffer);
		if (check.find("Makkarakeitto") == 0)
		{
			std::cout << "Makkarakeittoa tilattu" << "asiakkaalle numero:" << index << std::endl;
			
			std::cout << "Asiakkaan " << index << "ruoka valmistumassa \n" << std::endl;
			std::string Buffer = "Tilaamanne ruoka on valmistumassa.\nRuoan hinta on 9.50e,\nlis\x84ksi kaikki juomat sis\x84ltyv\x84t hintaan ja on noudettavissa Juomap\x94yd\x84st\x84: \n\n";
			int HBlength = Buffer.size();//viestin pituus
			send(Connections[index], (char*)&HBlength, sizeof(int), NULL); //l‰hetet‰‰n tervehdystekstin pituus
			send(Connections[index], Buffer.c_str(), HBlength, NULL); //l‰hetet‰‰n tervehdysteksti asiakkaalle 
		}
		if ((check.find("Kalakeitto") == 0 )| (check.find("kalakeitto") == 0))
		{
			std::cout << "Kalakeittoa tilattu" << "asiakkaalle numero: " << index << std::endl;

			std::cout << "Asiakkaan " << index << " ruoka valmistumassa \n" << std::endl;
			std::string Buffer = "Tilaamanne ruoka on valmistumassa.\nRuoan hinta on 10.50e,\nlis\x84ksi kaikki juomat sis\x84ltyv\x84t hintaan ja on noudettavissa Juomap\x94yd\x84st\x84: \n\n";
			int HBlength = Buffer.size();//viestin pituus
			send(Connections[index], (char*)&HBlength, sizeof(int), NULL); //l‰hetet‰‰n tervehdystekstin pituus
			send(Connections[index], Buffer.c_str(), HBlength, NULL); //l‰hetet‰‰n tervehdysteksti asiakkaalle 
		}
		//tulostetaan asiaakkaan viesti
		std::cout << buffer << std::endl;


		delete[] buffer;
	}
}


int main()
{
	//Winsockin k‰ynnisty
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) // tarkastetaan mik‰li wsa startup palauttaa jotain muuta kuin nollaan niin se on ep‰onnistunut
	{
		MessageBoxA(NULL, "winsocketin luonti ep\x84onnistui", "Virhe", MB_OK | MB_ICONERROR);
		exit(1);
	}
	SOCKADDR_IN addr; //Osoite jota kuunteleva Socketti tulee k‰ytt‰m‰‰n
	int addrlen = sizeof(addr); //osoitteen pituus (tarvitaan yhteyden hyv‰ksymiseen
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");// sis‰inen verkko
	addr.sin_port = htons(8888); //portti
	addr.sin_family = AF_INET; //IPv4 Socket;

	//luodaan kuuntelija socketuusien yhteyksien kuuntelemiseen.
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	//kiinnitet‰‰n osoite kuuntelijaan
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); 
	//asettaa kuuntelijan tilan kuuntelemaan tulevia l‰hetyksi‰.
	listen(sListen, SOMAXCONN); 

	SOCKET newConnection; //Socket asiakkaan yhteytt‰ varten
	const int connectionsAvailable = (int)sizeof(Connections) / sizeof(Connections)[0];
	std::cout << "\n Max Connections: " << connectionsAvailable << "\n" << std::endl;

	for (size_t i = 0; i < connectionsAvailable; i++)
	{


		newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); // hyv‰ksyt‰‰n uusi yhteys

		//Clientin hyv‰ksynn‰n tarkistus
		if (newConnection == 0)
		{
			std::cout << "Asiakkaan yhteyden hyvaksynta epaonnistunut \n" << std::endl;
		}
		else
		{
			std::cout << "Asiakkaan "<< i << " yhteys onnistunut \n" << std::endl;
			std::string HelloBuffer = "TERVETULOA RAFLAAN!\n\nKuinka voin palvella? \nT\x84n\x84\x84n tarjolla on: \n\n     Kalakeittoa hintaan 10.50e \n tai \n     Makkarakeittoa hintaa 9.50 \n"; //Luodaan tervehdysteksti
			int HBlength = HelloBuffer.size();//viestin pituus
			send(newConnection, (char*)&HBlength, sizeof(int), NULL); //l‰hetet‰‰n tervehdystekstin pituus
			send(newConnection, HelloBuffer.c_str(), HBlength, NULL); //l‰hetet‰‰n tervehdysteksti asiakkaalle 
			Connections[i] = newConnection;
			ConnectionCounter++;
			//Luodaan sˆie joka hoitaa t‰m‰n kierroksen asiakkaan
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientsOrderThread, (LPVOID)(i), NULL, NULL);
		}

	}
	system("Pause");
    return 0;
}

