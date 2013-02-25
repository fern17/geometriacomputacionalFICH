#include <iostream>
#include <vector>
#include <cstdio>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	unsigned int horizontal = 10;
	unsigned int vertical = 10;
	unsigned int maximo = horizontal*vertical;
	unsigned int start = 100;
	unsigned int step = 15;
	float mult = 2.5;
	ofstream file1 ("points5.txt", ios::trunc);
	if (file1.is_open()) {
		file1<<maximo+3<<'\n';
		//Agrega el triangulo envolvente
		file1<<10<<' '<<10<<'\n'; //punto 0
		file1<<start+horizontal*step*mult<<' '<<start+vertical*step*mult*0.2<<'\n';
		file1<<10<<' '<<start+vertical*step*mult<<'\n';
		for (unsigned int i = 0; i < vertical; i++) {
			for (unsigned int j = 0; j < horizontal; j++) {
				file1<<start+(j+1)*step<<' '<<start+(i+1)*step<<'\n';
			}
		}
	}
	file1.close();
	
	ofstream file2 ("neighbors5.txt", ios::trunc);
	if (file2.is_open()) {
		//punto 0
		file2<<1<<' ';
		for (int i = horizontal+3-1; i > 3; i--) {
			file2<<i<<' ';
		}
		for (unsigned int i = 0; i < vertical; i++) {
			file2<<i*horizontal+3<<' ';
		}
		file2<<2<<'\n';
		
		//punto 1
		file2<<2<<' ';
		for (int i = maximo+3-1; i > 0; i-=10){
			file2<<i<<' ';
		}
		file2<<0<<' ';
		file2<<'\n';
		
		//punto 2
		file2<<0<<' ';
		for (unsigned int i = maximo-horizontal+3; i < maximo+3; i++) {
			file2<<i<<' ';
		}
		file2<<1<<'\n';
		
		unsigned int idx = 3;
		for (unsigned int i = 0; i < vertical; i++) {
			for (unsigned int j = 0; j < horizontal; j++) {
				std::vector<unsigned int> vecinos;
				if ((idx+1) % (horizontal+3) != 0) 
					vecinos.push_back(idx+1); //derecha
				
				if (((idx+1) % (horizontal+3) != 0) and idx+1+horizontal < maximo)
					vecinos.push_back(idx+1+horizontal); //arriba derecha
				if (idx+horizontal < maximo)
					vecinos.push_back(idx+horizontal); //arriba
				if (((idx % (horizontal+3)) != 0) and idx > 0)
					vecinos.push_back(idx-1); //izquierda
				if (idx >= horizontal+3) {
					if (((idx-1) % (horizontal+3) != 0) and idx > horizontal+1)
						vecinos.push_back(idx-1-horizontal); //abajo izquierda
					
					vecinos.push_back(idx-horizontal); //abajo
				}
					
				
				//std::cout<<"Vecinos de "<<idx<<": ";
				for (unsigned int k = 0; k < vecinos.size(); k++) {
					file2<<vecinos[k]<<' ';
				}
				file2<<"\n";
				idx++;
			}
		}
	}
	
	ofstream file3 ("triangles5.txt", ios::trunc);
	if (file3.is_open()) {
		file3<<0<<' '<<1<<' '<<2<<'\n';//triangulo envolvente
		for (unsigned int i = 3; i < maximo-horizontal; i++) {
			if ((i+1) % (horizontal+3) != 0) {
				file3<<i<<' '<<i+1<<' '<<i+1+horizontal;
				file3<<"\n";
			}
		}
		for (unsigned int i = horizontal+3; i < maximo; i++) {
			if ((i+1) % (horizontal+3) != 0) {
				file3<<i<<' '<<i-horizontal<<' '<<i+1;
				file3<<"\n";
			}
		}
	}
	return 0;
}

