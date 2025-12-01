#include <string>

using namespace std;

#if !defined(DEF_FILE)
#define DEF_FILE

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
    bool rename(string name);
};


#endif // DEF_FILE
