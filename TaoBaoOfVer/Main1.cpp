#include "Server.h"
#define ReadByInput(key)  ;cin>>key;cin.clear();cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
int Server::Main1() {
	while (1) {
		char mod;
		do {
			cout << "Type in 's' to reach Seller MOD, or 'c' to reach Consumer MOD.\n ";
			ReadByInput(mod);
			cin.clear();cin
		} while (mod != 's' && mod != 'c');
		if (mod == 's') {
			while (1) {
				//consumerMain1
				
				
				//!consumerMain1
			}
		}
		else {
			while (1) {
				//SellerMain1
				
				//!SellerMain1
			}
		}

	}
}