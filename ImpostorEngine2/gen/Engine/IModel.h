#ifndef IMODEL_H
#define IMODEL_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class IGraphics;

#include <Utils/Standard.h>
#include <Engine/I3D.hh>
#include <Engine/IGraphics.h>

class IModel {
public:
    vector<uint32_t>        Colors;
    vector<IFace>           Faces;
    vector<vector<IVertex>> Vertices;
    vector<vector<IVertex>> Normals;
    vector<vector<IVertex>> UVs;
    int                     FaceCount;
    unsigned int            BufferID_V;
    unsigned int            BufferID_N;
    IGraphics* G = NULL;

    IModel();
    IModel(const char* filename, IGraphics* G);
    bool HasColors();
    void Cleanup();
};

#endif /* IMODEL_H */
