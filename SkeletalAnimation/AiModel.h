#pragma once
#include <vector>
#include <assimp/scene.h>

class AiModel
{
	const aiScene* model;
	std::vector<aiVector3D> vertices = std::vector<aiVector3D>();
	std::vector<aiVector3D> normals = std::vector<aiVector3D>();
	bool isAnimation;
	bool useBones;
public:
	explicit AiModel(const char* filename, bool isAnimation = true, bool useBones = false);
	void setSecsPerTick(float secsPerTick);
	void updateAnimation(unsigned int tick);
	void render() const;
	void releaseResources() const;
	aiVector3D getRootPos();

	double animDuration;
	float secsPerTick = NULL;
	aiVector3D scene_min, scene_max;
private:
	const aiScene* loadModel(const char* fileName);
	void updateVerts();
	void render(const aiScene* sc, const aiNode* nd) const;
};
