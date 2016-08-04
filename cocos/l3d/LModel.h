#ifndef __LMODEL_H__
#define __LMODEL_H__

NS_CC_BEGIN

class LSurface;

class LModel
{
public:
	LModel();
	~LModel();

	LSurface* AllocGeo();

	LSurface* GetGeometries(int idx);

	int GetGeometriesCount();

	void GenerateNormals();

	void CalcBounds();

	void BuildDeformInfo();

	void SetNumFrames(int num);

	int GetNumFrames() { return _numFrames; }

private:

	Vector<LSurface*> _surfaces;

	std::string _name;
	int _numFrames;
};

NS_CC_END

#endif