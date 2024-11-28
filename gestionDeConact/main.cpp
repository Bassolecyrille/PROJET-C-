#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

// Définition de la structure Contact
struct Contact {
    string nom;
    string telephone;
    string email;
    string adresse;
};

// Classe GestionnaireDeContacts pour gérer les contacts
class GestionnaireDeContacts {
private:
    vector<Contact> contacts;

    // Fonction pour trouver un contact par nom
    int trouverIndexParNom(const string& nom) {
        for (size_t i = 0; i < contacts.size(); i++) {
            if (contacts[i].nom == nom) {
                return i;
            }
        }
        return -1; // Retourne -1 si le contact n'est pas trouvé
    }

public:
    // Ajouter un contact
    void ajouterContact(const Contact& contact) {
        contacts.push_back(contact);
        cout << "Contact ajouté avec succès.\n";
    }

    // Modifier un contact existant
    void modifierContact(const string& nom) {
        int index = trouverIndexParNom(nom);
        if (index != -1) {
            cout << "Modifier les informations du contact " << contacts[index].nom << " :\n";
            cout << "Nouveau numéro de téléphone : ";
            cin >> contacts[index].telephone;
            cout << "Nouvel email : ";
            cin >> contacts[index].email;
            cout << "Nouvelle adresse : ";
            cin.ignore();
            getline(cin, contacts[index].adresse);
            cout << "Contact modifié avec succès.\n";
        } else {
            cout << "Contact non trouvé.\n";
        }
    }

    // Supprimer un contact
    void supprimerContact(const string& nom) {
        int index = trouverIndexParNom(nom);
        if (index != -1) {
            contacts.erase(contacts.begin() + index);
            cout << "Contact supprimé avec succès.\n";
        } else {
            cout << "Contact non trouvé.\n";
        }
    }

    // Rechercher un contact par nom
    void rechercherContact(const string& nom) {
        for (const auto& contact : contacts) {
            if (contact.nom == nom) {
                cout << "Nom : " << contact.nom << "\nTéléphone : " << contact.telephone
                     << "\nEmail : " << contact.email << "\nAdresse : " << contact.adresse << "\n";
                return;
            }
        }
        cout << "Contact non trouvé.\n";
    }

    // Trier les contacts par nom
    void trierContacts() {
        sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
            return a.nom < b.nom;
        });
        cout << "Contacts triés par nom.\n";
    }

    // Sauvegarder les contacts dans un fichier
    void sauvegarderDansFichier(const string& nomFichier) {
        ofstream fichier(nomFichier);
        if (fichier.is_open()) {
            for (const auto& contact : contacts) {
                fichier << contact.nom << "," << contact.telephone << "," << contact.email << "," << contact.adresse << "\n";
            }
            fichier.close();
            cout << "Contacts sauvegardés dans le fichier " << nomFichier << ".\n";
        } else {
            cout << "Erreur lors de l'ouverture du fichier.\n";
        }
    }

    // Charger les contacts depuis un fichier
    void chargerDepuisFichier(const string& nomFichier) {
        ifstream fichier(nomFichier);
        if (fichier.is_open()) {
            contacts.clear();
            string ligne;
            while (getline(fichier, ligne)) {
                Contact contact;
                size_t pos = 0;
                // Découper la ligne en parties séparées par des virgules
                pos = ligne.find(",");
                contact.nom = ligne.substr(0, pos);
                ligne.erase(0, pos + 1);

                pos = ligne.find(",");
                contact.telephone = ligne.substr(0, pos);
                ligne.erase(0, pos + 1);

                pos = ligne.find(",");
                contact.email = ligne.substr(0, pos);
                ligne.erase(0, pos + 1);

                contact.adresse = ligne;

                contacts.push_back(contact);
            }
            fichier.close();
            cout << "Contacts chargés depuis le fichier " << nomFichier << ".\n";
        } else {
            cout << "Erreur lors de l'ouverture du fichier.\n";
        }
    }

    // Afficher tous les contacts
    void afficherContacts() {
        if (contacts.empty()) {
            cout << "Aucun contact disponible.\n";
        } else {
            for (const auto& contact : contacts) {
                cout << "Nom : " << contact.nom << "\nTéléphone : " << contact.telephone
                     << "\nEmail : " << contact.email << "\nAdresse : " << contact.adresse << "\n\n";
            }
        }
    }
};

// Fonction principale
int main() {
    GestionnaireDeContacts gestionnaire;
    int choix;
    do {
        cout << "\nMenu de Gestion de Contacts :\n";
        cout << "1. Ajouter un contact\n";
        cout << "2. Modifier un contact\n";
        cout << "3. Supprimer un contact\n";
        cout << "4. Rechercher un contact\n";
        cout << "5. Trier les contacts par nom\n";
        cout << "6. Sauvegarder les contacts\n";
        cout << "7. Charger les contacts\n";
        cout << "8. Afficher tous les contacts\n";
        cout << "0. Quitter\n";
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1: {
                Contact contact;
                cout << "Nom : ";
                cin >> contact.nom;
                cout << "Téléphone : ";
                cin >> contact.telephone;
                cout << "Email : ";
                cin >> contact.email;
                cout << "Adresse : ";
                cin.ignore();
                getline(cin, contact.adresse);
                gestionnaire.ajouterContact(contact);
                break;
            }
            case 2: {
                string nom;
                cout << "Nom du contact à modifier : ";
                cin >> nom;
                gestionnaire.modifierContact(nom);
                break;
            }
            case 3: {
                string nom;
                cout << "Nom du contact à supprimer : ";
                cin >> nom;
                gestionnaire.supprimerContact(nom);
                break;
            }
            case 4: {
                string nom;
                cout << "Nom du contact à rechercher : ";
                cin >> nom;
                gestionnaire.rechercherContact(nom);
                break;
            }
            case 5:
                gestionnaire.trierContacts();
                break;
            case 6: {
                string nomFichier;
                cout << "Nom du fichier pour sauvegarder : ";
                cin >> nomFichier;
                gestionnaire.sauvegarderDansFichier(nomFichier);
                break;
            }
            case 7: {
                string nomFichier;
                cout << "Nom du fichier pour charger : ";
                cin >> nomFichier;
                gestionnaire.chargerDepuisFichier(nomFichier);
                break;
            }
            case 8:
                gestionnaire.afficherContacts();
                break;
            case 0:
                cout << "Au revoir !\n";
                break;
            default:
                cout << "Choix invalide. Réessayez.\n";
        }
    } while (choix != 0);

    return 0;
}
