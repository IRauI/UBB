#include "UI.h"

using std::cout;
using std::cin;



void run() {
	int option = 0;
	ActivityRepo rep;
	ActivityValidator val;
	ActivityStore ctr(rep, val);
	do {
		cout << "1.Adaugare activitate\n2.Stergere activitate\n3.Modificare activitate\n4.Afisare activitati\n5.Filtrare Activitati\n6.Sortare Activitati\n0.Exit\n";
		cin >> option;
		if (option == 1) {
			string title;
			string description;
			string type;
			int duration;
			cout << "Titlu:\n";
			cin >> title;
			cout << "Descriere:\n";
			cin >> description;
			cout << "Tip:\n";
			cin >> type;
			cout << "Durata:\n";
			cin >> duration;
			try
			{
				ctr.addActivity(title, description, type, duration);

			}
			catch (ValidateException e)
			{
				cout << e;
			}
			catch (ActivityRepoException ae)
			{
				cout << ae << '\n';
			}
			for (int i = 0; i < ctr.getAll2().size(); ++i) {
				cout << ctr.getAll2().get(i) << '\n';
			}
		}
		if (option == 2) {
			for (int i = 0; i < ctr.getAll2().size(); ++i) {
				cout << i << "." << ctr.getAll2().get(i) << '\n';
			}
			int aux;
			cout << "Numarul activitatii sterse:\n";
			do {
				cin >> aux;
			} while (aux <= 0 || aux > ctr.getAll2().size());
			try {
				ctr.removeActivity(ctr.getAll2().get(aux - 1));
			}
			catch (ValidateException e) {
				cout << e << '\n';
			}
			catch (ActivityRepoException ae)
			{
				cout << ae << '\n';
			}
			for (int i = 0; i < ctr.getAll2().size(); ++i) {
				cout << ctr.getAll2().get(i) << '\n';
			}
		}
		if (option == 3) {
			for (int i = 0; i < ctr.getAll2().size(); ++i) {
				cout << i << "." << ctr.getAll2().get(i) << '\n';
			}
			int aux;
			cout << "Numarul activitatii modificate:\n";
			do {
				cin >> aux;
			} while (aux <= 0 || aux > ctr.getAll2().size());
			string descriere;
			string type;
			int durata;
			cout << "Descriere:\n";
			cin >> descriere;
			cout << "Tip:\n";
			cin >> type;
			cout << "Durata:\n";
			cin >> durata;
			try {
				ctr.modifyActivity(ctr.getAll2().get(aux - 1), descriere, type, durata);
			}
			catch (ValidateException e) {
				cout << e << '\n';
			}
			catch (ActivityRepoException ae)
			{
				cout << ae << '\n';
			}
			for (int i = 0; i < ctr.getAll2().size(); ++i) {
				cout << ctr.getAll2().get(i) << '\n';
			}
		}
		if (option == 4) {
			for (int i = 0; i < ctr.getAll2().size(); ++i) {
				cout << ctr.getAll2().get(i) << '\n';
			}
		}
		if (option == 5) {
			int aux = 0;
			cout << "1.Descriere\n2.Tip\n";
			do {
				cin >> aux;
			} while (aux < 1 && aux > 2);
			if (aux == 1) {
				cout << "Descrierea:\n";
				string description;
				cin >> description;
				for (int i = 0; i < ctr.filterByDescription(description).size(); ++i) {
					cout << ctr.filterByDescription(description).get(i) << '\n';
				}
			}
			if (aux == 2) {
				cout << "Tipul:\n";
				string type;
				cin >> type;
				for (int i = 0; i < ctr.filterByType(type).size(); ++i) {
					cout << ctr.filterByType(type).get(i) << '\n';
				}
			}
		}
		if (option == 6) {
			int aux = 0;
			cout << "1.Titlu\n2.Descriere\n3.Tip+Durata\n";
			do {
				cin >> aux;
			} while (aux < 1 && aux > 3);
			if (aux == 1) {
				for (int i = 0; i < ctr.sortByTitle().size(); ++i) {
					cout << ctr.sortByTitle().get(i) << '\n';
				}
			}
			if (aux == 2) {
				for (int i = 0; i < ctr.sortByDescription().size(); ++i) {
					cout << ctr.sortByDescription().get(i) << '\n';
				}
			}
			if (aux == 3) {
				for (int i = 0; i < ctr.sortByTypeDuration().size(); ++i) {
					cout << ctr.sortByTypeDuration().get(i) << '\n';
				}
			}
		}
	} while (option != 0);
}