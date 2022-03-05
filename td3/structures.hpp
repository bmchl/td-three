#pragma once
// Structures mémoires pour une collection de films.

#include <string>
#include <cassert>
#include "gsl/span"
#include <memory>
using gsl::span;
using namespace std;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

class ListeFilms {
public:
	ListeFilms() = default;
	ListeFilms(const std::string& nomFichier);
	ListeFilms(const ListeFilms& l) { assert(l.elements == nullptr); } // Pas demandé dans l'énoncé, mais on veut s'assurer qu'on ne fait jamais de copie de liste, car la copie par défaut ne fait pas ce qu'on veut.  Donc on ne permet pas de copier une liste non vide (la copie de liste vide est utilisée dans la création d'un acteur).
	~ListeFilms();
	void ajouterFilm(Film* film);
	void enleverFilm(const Film* film);
	shared_ptr<Acteur> trouverActeur(const string& nomActeur) const;
	span<Film*> enSpan() const;
	int size() const { return nElements; }

private:
	void changeDimension(int nouvelleCapacite);

	int capacite = 0, nElements = 0;
	Film** elements = nullptr; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
	bool possedeLesFilms_ = false; // Les films seront détruits avec la liste si elle les possède.
};

struct ListeActeurs {
public:
	ListeActeurs() {};
	ListeActeurs(int capacite, int nElements):capacite_(capacite),nElements_(nElements)
	{
		elements_ = make_unique<shared_ptr<Acteur>[]>(capacite);
	}
	ListeActeurs(ListeActeurs const& ancListe)
	{
		assert(ancListe.elements_ == nullptr);
	}
	ListeActeurs operator=(ListeActeurs const& ancListe)
	{
		capacite_ = ancListe.capacite_;
		nElements_ = ancListe.nElements_;
		elements_ = move(ancListe.elements_);
		return *this;
	}

	int lireCapacite()
	{
		return capacite_;
	}
	int lireNElements()
	{
		return nElements_;
	}
	span<shared_ptr<Acteur>> lireElements() const
	{
		return span(elements_.get(), nElements_);
	}
	Acteur lireElement(int index) const
	{
		return *elements_.get()[index]
	};

	void detruireElements()
	{
		delete[] elements_.get();
	}
	//	span<Acteur*> spanListeActeurs(const ListeActeurs& liste) { return span(liste.elements, liste.nElements); }

private:
	int capacite_ = 0;
	int nElements_ = 0;
	unique_ptr<shared_ptr<Acteur>[]> elements_; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
};

class Film
{
public:
	Film() = default;
	Film(const Film& ancFilm):
		titre_(ancFilm.titre_),
		realisateur_(ancFilm.realisateur_),
		anneeSortie_(ancFilm.anneeSortie_),
		recette_(ancFilm.recette_),
		acteurs_(ancFilm.acteurs_)
	{
	}
	~Film()
	{
	}
	friend ostream& operator<< (ostream& o, const Film& film);
	void modifierTitre(string nouvTitre)
	{
		titre_ = nouvTitre;
	}
	ListeActeurs lireActeurs()
	{
		return acteurs_;
	}
private:
	std::string titre_ = "", realisateur_ = ""; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie_ = 0, recette_ = 0; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs_;
};

class Acteur
{
public:
	std::string nom; int anneeNaissance; char sexe;
	//ListeFilms joueDans;c
};
