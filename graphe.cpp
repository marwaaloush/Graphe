//IF5 - Octobre 2005
//Raphaelle Chaine

#include <iostream> 
#include <cstdio>
#include <fstream> //ifstream, ofstream
#include <cstdlib> //exit
#include <vector>

void creeFichierEntiers(const char * nomFichier, int nb)
//preconditions : nomFichier chaine de caracteres designant le nom du fichier a creer
//postcondition : le fichier nomFichier contient nb entiers separes par des espaces
{
  std::ofstream ofs;
  ofs.open(nomFichier);
  if(ofs.bad()) 
    {std::cout<<"Impossible d'ouvrir le fichier "<<nomFichier<<" en ecriture \n"; exit(1);}

  for(int i=0;i<nb;i++)
    {
      int temp;
      std::cout << "Entier suivant : ";
      std::cin >> temp; //Ou utilisez la version robuste de saisie d'un int
      ofs << temp <<' ';//Remarquez que l'on separe les int par des espaces
    }
  ofs.close();
}


void litFichierEntiers(const char * nomFichier)
//preconditions : nomFichier chaine de caracteres designant le nom d'un fichier
//                contenant des entiers separes par des caracteres d'espacement
//postcondition : affichage du contenu du fichier sur la sortie standard
{
  std::ifstream ifs;
  ifs.open(nomFichier);
  if(ifs.bad())
    {std::cout<<"Impossible d'ouvrir le fichier "<<nomFichier<<" en lecture \n"; exit(1);}
  int temp;
  while(ifs >> temp)
    std::cout<<"Entier suivant "<<temp<< std::endl;
  ifs.close();
}

void litFichierPGM(const char* nomFichier) {
    std::ifstream ifs(nomFichier, std::ios::in);
    if (!ifs.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << nomFichier << " en lecture.\n";
        return;
    }

    std::string format;
    ifs >> format; // Lecture du format (P2 ou P5)
    if (format != "P2") {
        std::cerr << "Format non supporté : " << format << ". Seul le format P2 est pris en charge.\n";
        return;
    }

    // Ignorer les commentaires (lignes commençant par #)
    std::string line;
    std::getline(ifs, line); // Lire le reste de la ligne
    while (ifs.peek() == '#') {
        std::getline(ifs, line); // Ignorer les lignes de commentaire
    }

    // Lire la largeur, la hauteur et la valeur maximale
    int largeur, hauteur, valeur_max;
    ifs >> largeur >> hauteur >> valeur_max;

    std::cout << "Dimensions : " << largeur << " x " << hauteur << "\n";
    std::cout << "Valeur maximale : " << valeur_max << "\n";

    // Lire les pixels
    std::vector<std::vector<int>> pixels(hauteur, std::vector<int>(largeur));
    for (int i = 0; i < hauteur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            ifs >> pixels[i][j];
        }
    }

    // Afficher les pixels sous forme de tableau
    std::cout << "Contenu du fichier PGM (pixels) :\n";
    for (const auto& row : pixels) {
        for (int pixel : row) {
            std::cout << pixel << " ";
        }
        std::cout << "\n";
    }

    ifs.close();
}

int main()
{
  char fich[100]; 
  const char* nomFichier = "./img.pgm";

  std::cout << "Lecture du fichier PGM : " << nomFichier << "\n";
  litFichierPGM(nomFichier);
  int n;
  std::cout << "Entrez le nom du fichier d'entiers a creer" << std::endl;
  std::scanf("%99s",nomFichier);
  std::cout << "Combien d'entiers dans ce fichier ?" << std::endl;
  std::cin >> n;
  creeFichierEntiers(fich,n);
  std::cout << "Affichage des entiers contenu dans le fichier" << std::endl;
  litFichierEntiers(fich);
  return 0;
}