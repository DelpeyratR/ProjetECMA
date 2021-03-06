#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

#include "voisinage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;


carte Ha,Hp,Ca,Cp;
int n,m;
void getData(ifstream& fichier) {
	char char1;
	double tmp;
	if(fichier) {
		//pour n
		fichier >> char1 >> char1 >> n >> char1;
		cout <<"n="<< n<<"\n";
		//pour m
		fichier >> char1 >> char1 >> m >>char1;
		cout <<"m="<< m<<"\n";
		int Ba,Bp;
		//pour Ba, si existe!
		fichier >> char1 ;
		if(char1=='B'){//then Ba est d�finie, et Bp aussi
		  fichier >> char1 >> char1>>Ba >>char1;
		  cout <<"Ba="<< Ba<<"\n";

		  //pour Bp
		  fichier >> char1 >> char1 >>char1 >> Bp >>char1;
		
		  
		// Ha
		fichier >> char1 >> char1 >> char1 >> char1; // lit H a = [       
		}
		else if(char1=='H'){	fichier >> char1 >> char1 >> char1; // le 'H' a �t� lu, on lit " a = ["
		}
		else cout << "Probl�me de lecture de l'instance, donn�es non conforme au mod�le...\n";
		

		
		for(int i=0;i<n;i++) {
			fichier >> char1 ; // lit le [ de la ligne
			vector<float> ligne;; // On initialise la i�me ligne de M
			for(int j=0;j<m;j++) {
				fichier >> tmp >> char1;
				// Chaque ligne du fichier contient n fois le motif suivant :
				// un entier suivi d�un caract�re ("," ou "]" a la fin)
				ligne.push_back(tmp); // On ajoute l�entier lu � la i�me ligne de M
			}
			Ha.push_back(ligne);
			ligne.clear();
			fichier >> char1;//lit ",", Fin de la lecture de la i�me ligne de M
		}
		fichier >> char1; //lit ; a la fin de E
		displayData(Ha,n,m);
		fichier >> char1 >> char1 >> char1 >> char1; // lit C a = [

		for(int i=0;i<n;i++) {
			fichier >> char1 ; // lit le [ de la ligne
			vector<float> ligne; // On initialise la i�me ligne de M
			for(int j=0;j<m;j++) {
				fichier >> tmp >> char1;
				// Chaque ligne du fichier contient n fois le motif suivant :
				// un entier suivi d�un caract�re ("," ou "]" a la fin)
				ligne.push_back(tmp); // On ajoute l�entier lu � la i�me ligne de M
			}
			Ca.push_back(ligne);
			ligne.clear();
			fichier >> char1;//lit ",", Fin de la lecture de la i�me ligne de M
		}
		fichier >> char1; //lit ; a la fin du tableau
		displayData(Ca,n,m);

		// Hp
		
		fichier >> char1 >> char1 >> char1 >> char1; // lit C a = [

		for(int i=0;i<n;i++) {
			fichier >> char1 ; // lit le [ de la ligne
			vector<float> ligne;
			for(int j=0;j<m;j++) {
				fichier >> tmp >> char1;
				// Chaque ligne du fichier contient n fois le motif suivant :
				// un entier suivi d�un caract�re ("," ou "]" a la fin)
				ligne.push_back(tmp); // On ajoute l�entier lu � la i�me ligne de M
			}
			Hp.push_back(ligne);
			ligne.clear();
			fichier >> char1;//lit ",", Fin de la lecture de la i�me ligne de M
		}
		fichier >> char1; //lit ; a la fin du tableau
		displayData(Hp,n,m);

		// Cp
		
		fichier >> char1 >> char1 >> char1 >> char1; // lit C p = [

		for(int i=0;i<n;i++) {
			fichier >> char1 ; // lit le [ de la ligne
			vector<float> ligne; // On initialise la i�me ligne de M
			for(int j=0;j<m;j++) {
				fichier >> tmp >> char1;
				// Chaque ligne du fichier contient n fois le motif suivant :
				// un entier suivi d�un caract�re ("," ou "]" a la fin)
				ligne.push_back(tmp); // On ajoute l�entier lu � la i�me ligne de M
			}
			Cp.push_back(ligne);
			ligne.clear();
			fichier >> char1;//lit ",", Fin de la lecture de la i�me ligne de M
		}
		fichier >> char1; //lit ; a la fin du tableau
		displayData(Ca,n,m);

		fichier.close();
	}
}
solution voisinage(solution s)
{
	bool chgt=false;
	solution svoisin=s;
	int compteur=0;
	while(chgt==false&&compteur<20){
	chgt=false;
	svoisin=voisinage1(s,&chgt,Ha,Hp,Ca,Cp,n,m);
	compteur++;
	}
	return svoisin;
}
solution recuit(solution& init,ofstream& sortie,int r,float Tinit,float phi,int Kmax)
{
	//param�tres
	time_t tic,tac;
	double tps;
	solution max=init;
	solution s=init;
	solution ss=init;
	float T=Tinit;
	int K=0;
	float delta;
	float q;
	float e;
	sortie<<"Param�tres"<<endl;
	sortie<<"Tinit = "<<Tinit<<endl<<"phi ="<<phi<<endl;
	sortie<<"Kmax = "<<Kmax<<endl<<"r = "<<r<<endl;
	while(K<Kmax)
	{
		tic=time(NULL);
		for(int nbIter=0;nbIter<r;nbIter++)
		{
			//on tire au sort une solution s'
			ss=voisinage(s);
			//display(ss.z,n,m);
			delta=ss.taille-s.taille;
			if(delta>=0&&ss.quotient>=2)//la nouvelle solution a une �nergie plus basse
			{
				s=ss;
				if(s.taille>max.taille){
					max=s;}
			}
			else
			{
				//On tire un nombre q pour d�cider si on garde la solution ss ou pas
				q=rand()%1000;
				q=q/1000;
				e=exp(delta/T);
				if(q<=e){
					s=ss;
				}
			}
		}
		tac=time(NULL);
		tps=difftime(tac,tic);
		sortie<<"It�ration = "<<K<<endl;
		sortie<<"Temperature = "<<T<<endl;
		sortie<<"Temps de l'�xecution = "<<tps<<endl;
		sortie<<"Meileure solution trouv�e jusqu'� pr�sent = "<<max.taille<<endl;
		sortie<<"Quotient de la meilleure solution trouvee = "<<max.quotient<<endl;
		K++;
		//Changement de temp�rature
		T=T*phi;
	}
	return max;
}
solution initialisation(int n,int m)
{
	solution sol;
	bool find=false;
	for(int i=0;i<n;i++){
		vector<int> ligne;
		for(int j=0;j<m;j++) 
		{ 
			if((Ha[i][j]+Hp[i][j]>=2)&&find==false)
			{
				ligne.push_back(1);
				pair<int,int> p;
				p.first=i;
				p.second=j;
				sol.interieur.push_back(p);
				sol.exterieur=voisins(i,j,n,m);
				sol.taille=1;
				sol.quotient=Ha[i][j]+Hp[i][j];
				find=true;
			}
			else
				ligne.push_back(0);
		}
		sol.z.push_back(ligne);
	}
	if(find)
		cout<<"solution initiale admissible"<<endl;
	else
		cout<<"erreur"<<endl;
	display(sol.z,n,m);
	return sol;

}
int main ()
{
	time_t deb,fin;
	double tps;
	string s;
	string t;
	string rep;
	srand (time(NULL));
	
	/*cout<< "entrez nom du fichier:"<<endl;
	cin>>s;
	cout<<"entrez nom du fichier resultat:"<<endl;
	cin>>t;*/
	rep="C:/Users/J.pages/Documents/Roxane/ProjetECMA-master/ProjetECMA-master/instances/instances_eleves/";
	t="a";
	s="projet_5_8_1";
	t=rep+t+".txt";
	ofstream sortie;
	sortie.open(t, ios::out); 
	s=rep+s+".dat";
	ifstream fichier(s, ios::in); 
		//lecture du fichier de donn�es
		getData(fichier);
		solution Sinit=initialisation(n,m);
		int r=10; //nombre d'it�rations par palier de temp�rature
		float Tinit=100; //temp�rature
		float phi=0.9;//facteur de d�croissance
		int Kmax=10;//nombre de paliers de temp�rature
/*
		cout<< "Choisissez une temperature initiale Tinit:"<<endl;
		cin>>Tinit;
		cout<< "Choisissez un nombre de paliers de temperature Kmax:"<<endl;
		cin>>Kmax;
		cout<< "Choisissez le nombre d'iterations sur un meme palier r:"<<endl;
		cin>>r;
		cout<< "Choisissez un facteur de decroissance de la temp�rature phi:"<<endl;
		cin>>phi;*/
		//Calcul de la solution initiale
		//zone Sinit=initialisation(n,m);
		//Calcul de la solution par recuit simul�
		//tps=difftime(fin,deb);
		solution  Srecuit;
		deb=time(NULL);
		Srecuit=recuit(Sinit,sortie,r,Tinit,phi,Kmax);
		fin=time(NULL);
		tps=difftime(fin,deb);
		//sortie<<"Valeur finale de la solution par recuit simul� = "<<Srecuit.z<<endl;
		sortie<<"Temps d'�x�cution total = "<<tps;
		
		
	}
			