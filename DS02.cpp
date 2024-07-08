#include "SocialNetwork.cpp"

int main() {
    SocialNetwork network;
    network.readFromFile("inputFile.txt");

    while (true) {
        int choice;

        cout<<"\x1b[6m\x1b[37m---------------------------------------\n";
        cout<<"\t Welcome To Linked in Page\n";
        cout<<"-------------   MENU   ----------------\x1b[0m \n\n";

        cout<<"\x1b[32m1.Suggestion\n";
        cout<<"2. Exit\n";
        cout<<"\x1b[33m\n Enter your choice: \x1b[0m";

        cin>>choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            system("cls");
            sug(network);
            break;
        case 2:
            system("cls");
            cout<<"\x1b[31m System closed!\n";
            exit(0);
        default:
           cout<<"\x1b[31m\n| Invalid choice! Please try again.|  \n\n \x1b[0m";
            system("PAUSE>NUL");
            system("cls");
            break;
        }
    }

    return 0;
}
