#if !defined(DEF_FOLDER)
#define DEF_FOLDER

#include "file.hpp"

class Folder
{
private:
    string name;
public:
    Folder(string name);
    ~Folder();
    bool exist() const;
    bool create() const;
    bool del() const;
    string getName() const;
};


#endif // DEF_FOLDER
