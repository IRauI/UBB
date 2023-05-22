#include "UI.h"

using std::cout;
using std::cin;



void run() {
	int option = 0;
	ActivityRepo rep;
	ActivityValidator val;
	ActivityList list;
	ActivityStore ctr(rep, val,list);
	do {
		cout << "1.Adaugare activitate\n2.Stergere activitate\n3.Modificare activitate\n4.Afisare Activitati\n5.Filtrare Activitati\n6.Sortare Activitati\n7.Stergeti Lista\n8.Salvati Lista\n9.Undo\n10.Generati Lista\n11.Adaugati in Lista\n12.Afisati Lista\n0.Exit\n";
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
			for (auto activity : ctr.getAll2()) {
				cout << activity << '\n';
			}
		}
		if (option == 2) {
			int i = 1;
			for (auto activity : ctr.getAll2()) {
				cout << i << "." << activity << '\n';
				++i;
			}
			int aux;
			cout << "Numarul activitatii sterse:\n";
			do {
				cin >> aux;
			} while (aux <= 0 || aux > ctr.getAll2().size());
			try {
				ctr.removeActivity(ctr.getAll2().at(aux - 1));
			}
			catch (ValidateException e) {
				cout << e << '\n';
			}
			catch (ActivityRepoException ae)
			{
				cout << ae << '\n';
			}
			for (auto activity : ctr.getAll2()) {
				cout << activity << '\n';
			}
		}
		if (option == 3) {
			int i = 1;
			for (auto activity : ctr.getAll2()) {
				cout << i << "." << activity << '\n';
				++i;
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
				ctr.modifyActivity(ctr.getAll2().at(aux - 1), descriere, type, durata);
			}
			catch (ValidateException e) {
				cout << e << '\n';
			}
			catch (ActivityRepoException ae)
			{
				cout << ae << '\n';
			}
			for (auto activity : ctr.getAll2()) {
				cout << activity << '\n';
			}
		}
		if (option == 4) {
			for (auto activity : ctr.getAll2()) {
				cout << activity << '\n';
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
				for (auto activity : ctr.filterByDescription(description)) {
					cout << activity << '\n';
				}
			}
			if (aux == 2) {
				cout << "Tipul:\n";
				string type;
				cin >> type;
				for (auto activity : ctr.filterByType(type) ) {
					cout << activity << '\n';
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
				for (auto activity : ctr.sortByTitle()) {
					cout << activity << '\n';
				}
			}
			if (aux == 2) {
				for (auto activity : ctr.sortByDescription()) {
					cout << activity << '\n';
				}
			}
			if (aux == 3) {
				for (auto activity : ctr.sortByTypeDuration()) {
					cout << activity << '\n';
				}
			}
		}
		if (option == 7) {
			ctr.emptyList();
			cout << "Lista a fost golita \n";
		}
		if (option == 8) {
			string file;
			cout << "Fisierul in care doriti sa salvati:\n";
			cin >> file;
			ctr.saveList(file);
		}
		if (option == 9) {
			cout << "1.Adaugare\n2.Modificare\n3.Stergere\n";
			int aux;
			cin >> aux;
			if (aux == 1) {
				ctr.undoAdd();
			}
			if (aux == 2) {
				ctr.undoModify();
			}
			if (aux == 3) {
				ctr.undoDelete();
			}
			for (auto activity : ctr.getAll2()) {
				cout << activity << '\n';
			}
		}
		if (option == 10) {
			cout << "Numarul de elemente:\n";
			int n = 0;
			cin >> n;
			ctr.generateList(n);
			for (auto activity : ctr.getList()) {
				cout << activity << '\n';
			}
		}

		if (option == 11) {
			for (auto activity : ctr.getAll2()) {
				cout << activity << '\n';
			}
			cout << "Titlu:\n";
			string title;
			cin >> title;
			ctr.addToList2(title);
		}
		if (option == 12) {
			for (auto activity : ctr.getList()) {
				cout << activity << '\n';
			}
		}
		if (option == 13) {
			ctr.undo();
		}
	} while (option != 0);
}