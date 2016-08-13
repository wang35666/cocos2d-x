#include "LSurface.h"

NS_CC_BEGIN

LSurface* LSurface::Create()
{
	LSurface* surface = new LSurface;
	return surface;
}

LSurface::LSurface() : numVerts(0), verts(nullptr), numIndices(0), indices(nullptr)
{

}

void LSurface::DeriveNormals()
{
	int	i;

	if (tangentsCalculated) {
		return;
	}

	for (i = 0; i < numVerts; i++) {
		verts[i].normal.setZero();
		verts[i].tangents[0].setZero();
		verts[i].tangents[1].setZero();
	}

	for (i = 0; i < numIndices; i += 3) {
		// make face tangents
		float		d0[5], d1[5];
		LDrawVert	*a, *b, *c;
		Vec3		temp, normal, tangents[2];

		a = verts + indices[i + 0];
		b = verts + indices[i + 1];
		c = verts + indices[i + 2];

		d0[0] = b->xyz[0] - a->xyz[0];
		d0[1] = b->xyz[1] - a->xyz[1];
		d0[2] = b->xyz[2] - a->xyz[2];
		d0[3] = b->st[0] - a->st[0];
		d0[4] = b->st[1] - a->st[1];

		d1[0] = c->xyz[0] - a->xyz[0];
		d1[1] = c->xyz[1] - a->xyz[1];
		d1[2] = c->xyz[2] - a->xyz[2];
		d1[3] = c->st[0] - a->st[0];
		d1[4] = c->st[1] - a->st[1];

		// normal
		temp[0] = d1[1] * d0[2] - d1[2] * d0[1];
		temp[1] = d1[2] * d0[0] - d1[0] * d0[2];
		temp[2] = d1[0] * d0[1] - d1[1] * d0[0];
		normal.set(temp.getNormalized());

		temp[0] = (d0[0] * d1[4] - d0[4] * d1[0]);
		temp[1] = (d0[1] * d1[4] - d0[4] * d1[1]);
		temp[2] = (d0[2] * d1[4] - d0[4] * d1[2]);
		tangents[0].set(temp.getNormalized());

		temp[0] = (d0[3] * d1[0] - d0[0] * d1[3]);
		temp[1] = (d0[3] * d1[1] - d0[1] * d1[3]);
		temp[2] = (d0[3] * d1[2] - d0[2] * d1[3]);
		tangents[1].set(temp.getNormalized());

		// sum up the tangents and normals for each vertex on this face
		for (int j = 0; j < 3; j++) {
			LDrawVert* vert = &verts[indices[i + j]];
			vert->normal += normal;
			vert->tangents[0] += tangents[0];
			vert->tangents[1] += tangents[1];
		}
	}

	tangentsCalculated = true;
}

void LSurface::BoundTriSurf()
{
	for (int i = 0; i < numVerts; i++)
	{
		//aabb.AddPoint(verts[i].xyz);
	}
}

void LSurface::CreateSilIndice()
{
	int	c_removed, c_unique;
	int	*remap;
	int	i;
	const LDrawVert *v1, *v2;

	remap = (int*)malloc(numVerts * sizeof(remap[0]));

	c_removed = 0;
	c_unique = 0;
	for (i = 0; i < numVerts; i++) {
		v1 = &verts[i];

		// see if there is an earlier vert that it can map to
		int j = 0;
		bool found = false;
		for (j = 0; j < i; ++j)
		{
			int k = remap[j];
			v2 = &verts[k];
			if (v2->xyz[0] == v1->xyz[0]
				&& v2->xyz[1] == v1->xyz[1]
				&& v2->xyz[2] == v1->xyz[2]) {
				c_removed++;
				remap[i] = k;
				found = true;
				break;
			}
		}

		if (!found) {
			c_unique++;
			remap[i] = i;
		}
	}

	silIndices = new glIndex_t[numIndices];
	for (i = 0; i < numIndices; i++) {
		silIndices[i] = remap[indices[i]];
	}

	free(remap);
}

void LSurface::AllocSurfVerts(int num)
{
	if (verts != nullptr)
		delete[] verts;

	numVerts = num;
	verts = new LDrawVert[num];
}

void LSurface::GenVBO()
{
	if (vbo[0] != 0)
		glDeleteBuffers(1, &vbo[0]);

	if (vbo[1] != 0)
		glDeleteBuffers(1, &vbo[0]);

	glGenBuffers(1, &vbo[0]);
	glGenBuffers(1, &vbo[1]);

	// Stick the data for the vertices into its VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LDrawVert) * numVerts, verts, GL_STATIC_DRAW);

	// Stick the data for the indices into its VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glIndex_t) * numIndices, indices, GL_STATIC_DRAW);

	// Clear the VBO state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

NS_CC_END