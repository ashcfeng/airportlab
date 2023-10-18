#include <cstring>

class Airport
{
public:
    char    code[10];
    char    type[16];
    char    name[64];
    float   longitude;
    float   latitude;
    float   distance;
    bool equals(Airport a) {
      return strcmp(code, a.code) == 0 && strcmp(type, a.type) == 0 && strcmp(name, a.name) == 0 && longitude == a.longitude && latitude == a.latitude;
    }
};