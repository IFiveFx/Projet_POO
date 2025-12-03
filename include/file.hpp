#include <string>
#include "Grid.hpp"

using namespace std;

#if !defined(DEF_FILE)
#define DEF_FILE

class Grid;

class File
{
private:
    string name;
    string path;
public:
    File(const string& name,const string& path);
    ~File();
    void setName(string name);
    void setPath(string path);
    string getName();
    string getPath();
    string read() const;
    void write(string ligne) const;
    void write(Grid* grid) const;
    bool rename(string name);
};


#endif // DEF_FILE
