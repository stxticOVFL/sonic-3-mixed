#ifndef IINI_H
#define IINI_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Utils/Standard.h>
#include <Engine/IApp.h>

class IINI {
public:
    struct ConfigItems {
    char section[60];
    bool hasSection;
    char key[60];
    char value[60];
    }; 
    ConfigItems item[80];
    int count;

    IINI(const char* filename);
    std::string GetString(const char* section, const char* key);
    int GetString(const char* section, const char* key, char* dest);
    int GetInteger(const char* section, const char* key, int* dest);
    int GetBool(const char* section, const char* key, bool* dest);
    int SetString(const char* section, const char* key, char* value);
    int SetInteger(const char* section, const char* key, int value);
    int SetBool(const char* section, const char* key, bool value);
    void Write(const char* filename);
    void Cleanup();
};

#endif /* IINI_H */
