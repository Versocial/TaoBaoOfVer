//#include "Server.h"
//#define ReadByInput(key)  ;cin>>key;cin.clear();cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
//#define DO(todo)	{usingLocker.lock();todo;usingLocker.unlock();}
//#define _EXIT ("@exit")
//#define _SHOW ("@show")
//#define _LOGOUT ("@logout")
//
//enum LoginFlag {
//	logout,seller,consumer
//};
//
//
//int Server::Main1() {
//	LoginFlag loginFlag = logout;
//	Seller* userS=new Seller();
//	Consumer* userC=new Consumer();
//	string CMD="";
//	cout << "Welcome!" << endl;
//	while (1) {
//		ReadByInput(CMD);
//		if (CMD == _LOGOUT) {
//			switch (loginFlag)
//			{
//			case logout:cout << "Already Logout.\n";
//				break;
//			case seller:DO(sellers->releaseIntoFile(userS->id())); cout << "Seller [ " << userS->id() << " ] logout.\n"; delete userS;
//				break;
//			case consumer:DO(consumers->releaseIntoFile(userC->id())); cout << "Consumer [ " << userC->id() << " ] logout.\n"; delete userC;
//				break;
//			default:
//				break;
//			}
//		}
//		else if (CMD == _SHOW) {
//			goods->toShowGoods(cout);
//		}
//		else if (CMD == _EXIT) {
//			cout << "Exit now.\n"; continue;
//		}
//		switch (loginFlag)
//		{
//		case logout:char mod;
//			cout << "Type 's' to sign up or 'l' to login.\n";
//			ReadByInput(mod);;
//			switch (mod)
//			{
//			case 's':cout << "Type in 's' to reach Seller MOD, or 'c' to reach Consumer MOD.\n ";
//				ReadByInput(mod);
//				if (mod == 's')DO(sellers->addCountByCin())
//				else if (mod == 'c')DO(consumers->addCountByCin())
//				else cout << "Unavialiable input.\n";
//				break;
//			case 'l':cout << "Type in 's' to reach Seller MOD, or 'c' to reach Consumer MOD.\n ";
//				ReadByInput(mod);
//				cout << "Please type in id.\n";
//				idType id; ReadByInput(id);
//				if (mod == 's') {
//					sellers->readFromFile(id);
//					sellers->getObjectById(id, (Object*&)userS);
//				}
//				else if (mod == 'c') {
//					consumers->readFromFile(id);
//					consumers->getObjectById(id, (Object*&)userC);
//					cout << "Give me your password.\n";
//					string passwd; cin >> passwd;// ReadByInput(passwd);
//					while (!userC->passWordMatch(passwd)) {
//						cout << "Wrong ! Please retype in !\n"
//							ReadByInput(passwd);
//					}
//					cout << "Welcome " << userC->Name();
//				}
//				
//				break;
//			default:
//				mod = 'e';
//				break;
//			}
//			if (mod == 's')loginFlag = seller;
//			else if (mod == 'c')loginFlag = consumer;
//			break;
//		case seller:
//			break;
//		case consumer:
//			break;
//		default:
//			break;
//		}
//
//		//char mod;
//		//do {
//		//	cout << "Type in 's' to reach Seller MOD, or 'c' to reach Consumer MOD.\n ";
//		//	ReadByInput(mod);
//		//} while (mod != 's' && mod != 'c');
//		//if (mod == 's') {
//		//	while (1) {
//		//		//consumerMain1
//
//
//		//		//!consumerMain1
//		//	}
//		//}
//		//else {
//		//	while (1) {
//		//		//SellerMain1
//
//		//		//!SellerMain1
//		//	}
//		//}
//	}
//}