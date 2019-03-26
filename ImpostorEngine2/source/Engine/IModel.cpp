#if INTERFACE
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
};
#endif

#include <Engine/IModel.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>

PUBLIC IModel::IModel() {

}

PUBLIC IModel::IModel(const char* filename, IGraphics* G) {
    IResource* ModelResource = IResources::Load(filename);
    IStreamer modelReader(ModelResource);
    if (modelReader.ReadUInt32BE() != 0x4D444C00) { // MDL0
        // toss error
        // incorrect magic
        return;
    }
    int HasVertColors = modelReader.ReadByte();
    int PolyType = modelReader.ReadByte();
    int VertexCount = modelReader.ReadUInt16();
    int FrameCount = modelReader.ReadUInt16();

    if (HasVertColors == 5) {
        for (int i = 0; i < VertexCount; i++) {
            Colors.push_back(modelReader.ReadByte() << 16 | modelReader.ReadByte() << 8 | modelReader.ReadByte());
            modelReader.ReadByte(); // read A (alpha), we don't it, but we need to read it
        }
    }

    FaceCount = modelReader.ReadUInt16() / PolyType;
    int f1, f2, f3, f4;
    for (int i = 0; i < FaceCount; i++) {
        f1 = modelReader.ReadUInt16();
        f2 = modelReader.ReadUInt16();
        f3 = modelReader.ReadUInt16();
        if (PolyType == 4)
            f4 = modelReader.ReadUInt16();

        if (PolyType == 3)
            Faces.push_back(IFace(f1, f2, f3));
        else
            Faces.push_back(IFace(f1, f2, f3, f4));
    }

    for (int f = 0; f < FrameCount; f++) {
        Vertices.push_back(vector<IVertex>());
        Normals.push_back(vector<IVertex>());
        for (int i = 0; i < VertexCount; i++) {
            Vertices[f].push_back(IVertex(modelReader.ReadFloat(), modelReader.ReadFloat(), modelReader.ReadFloat()));
            Normals[f].push_back(IVertex(modelReader.ReadFloat(), modelReader.ReadFloat(), modelReader.ReadFloat()));
        }
    }

    IResources::Close(ModelResource);

    if (FrameCount == 0) return;

    BufferID_V = G->MakeVertexBuffer(this, true);
    BufferID_N = G->MakeVertexBuffer(this, false);

    this->G = G;
}

PUBLIC bool IModel::HasColors() {
    return Colors.size() > 0;
}

PUBLIC void IModel::Cleanup() {
    // Does nothing
    if (G) G->DeleteBufferID(BufferID_V);
    if (G) G->DeleteBufferID(BufferID_N);
}
