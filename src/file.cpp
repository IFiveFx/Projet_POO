#include "file.hpp"
#include <fstream>
#include <cstdio>
#include <iostream>

File::File(const string& name,const string& path) {
    this->name = name;
    this->path = path.empty() ? name : path ;
}

File::~File() {}

void File::setName(string name) {
    this->name = name;
}
void File::setPath(string path) {
    this->path = path;
}
string File::getName() {
    return this->name;
}
string File::getPath() {
    return this->path;
}

string File::read() const{
    ifstream file(this->path.c_str(), ios::in);
    if(file.fail()) {
        cerr << "Erreur d'ouverture du fichier \"" << this->name << "\"\n";
        return "";
    }

    string output;
    string ligne;

    while (getline(file,ligne)) output += ligne + "\n";
    
    return output;  
    
}

void File::write(string ligne) const{
    
    ofstream file(this->path.c_str(),ios::out | ios::ate);
    if(file.fail()) {
        cerr << "Erreur d'ouverture du fichier \"" << this->name << "\"\n";
        return;
    }

    file << ligne << endl;
    file.close();
}


bool File::rename(string name) {
    File newFile(name,name + ".txt");
    ifstream file(this->path.c_str(), ios::in);
    if(file.fail()) {
        cerr << "Erreur d'ouverture du fichier \"" << this->name << "\"\n";
        return 1;
    }
    string ligne;
    while (getline(file,ligne))newFile.write(ligne);
    remove(this->getPath().c_str());
    return 0;
}