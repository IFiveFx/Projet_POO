#include "Folder.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

Folder::Folder(string name) : name(name) {}

Folder::~Folder() {}

bool Folder::exist() const {
    struct stat info;
    return stat(this->name.c_str(),&info) == 0;
}

bool Folder::create() const {
    if(this->exist())this->del();
    mkdir(this->name.c_str() ,0775);
    return 0;
}

bool Folder::del() const {
    DIR* dir = opendir(this->name.c_str());

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;

        if (name == "." || name == "..") continue;

        string fullPath = this->name + "/" + name;

        remove(fullPath.c_str());
    }

    closedir(dir);

    return rmdir(this->name.c_str()) != 0;
}

string Folder::getName() const {
    return name;
}