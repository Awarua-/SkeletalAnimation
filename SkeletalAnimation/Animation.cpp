#include <iostream>
#include <GL/freeglut.h>

using namespace std;

#include <assimp/cimport.h>
#include <assimp/types.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "assimp_extras.h"

const aiScene* scene = NULL;
GLuint scene_list = 0;
aiVector3D scene_min, scene_max, scene_center;
float secsPerTick = NULL;
unsigned int tick = 0;

bool loadModel(const char* fileName)
{
	scene = aiImportFile(fileName, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene == NULL) exit(1);
	secsPerTick = 1.0 / scene->mAnimations[0]->mTicksPerSecond;
	get_bounding_box(scene, &scene_min, &scene_max);
	return true;
}

void render(const aiScene* sc, const aiNode* nd) // 
{
	aiMatrix4x4 m = nd->mTransformation;
	aiMesh* mesh;
	aiFace* face;

	aiTransposeMatrix4(&m); //Convert to column-major order
	glPushMatrix();
	glMultMatrixf((float*)&m); //Multiply by the transformation matrix for this node

	// Draw all meshes assigned to this node
	for (int n = 0; n < nd->mNumMeshes; n++)
	{
		mesh = scene->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		if (mesh->HasNormals())
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);


		if (mesh->HasVertexColors(0))
			glEnable(GL_COLOR_MATERIAL);
		else
			glDisable(GL_COLOR_MATERIAL);

		//Get the polygons from each mesh and draw them
		for (int k = 0; k < mesh->mNumFaces; k++)
		{
			face = &mesh->mFaces[k];
			GLenum face_mode;

			switch (face->mNumIndices)
			{
			case 1: face_mode = GL_POINTS;
				break;
			case 2: face_mode = GL_LINES;
				break;
			case 3: face_mode = GL_TRIANGLES;
				break;
			default: face_mode = GL_POLYGON;
				break;
			}

			glBegin(face_mode);

			for (int i = 0; i < face->mNumIndices; i++)
			{
				int index = face->mIndices[i];
				if (mesh->HasVertexColors(0))
				{
					glEnable(GL_COLOR_MATERIAL);
					glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				}
				else
					glDisable(GL_COLOR_MATERIAL);
				if (mesh->HasNormals())
					glNormal3fv(&mesh->mNormals[index].x);
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}
	}

	// Draw all children
	for (int i = 0; i < nd->mNumChildren; i++)
		render(sc, nd->mChildren[i]);

	glPopMatrix();
}

void initialise()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	loadModel("BVH_Files/Dance.bvh"); //<<<-------------Specify input file name here
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1.0, 1000.0);
}

void update(int value)
{
	auto anim = scene->mAnimations[0];
	for (int i = 0; i < anim->mNumChannels; i++)
	{
		auto chnl = anim->mChannels[i];
		auto posn = chnl->mPositionKeys[tick % chnl->mNumPositionKeys].mValue;
		auto rotn = chnl->mRotationKeys[tick % chnl->mNumRotationKeys].mValue;
		auto matPos = aiMatrix4x4();
		matPos.Translation(posn, matPos);
		auto matRotn3 = rotn.GetMatrix();
		auto matRot = aiMatrix4x4(matRotn3);
		auto matprod = matPos * matRot;
		auto node = scene->mRootNode->FindNode(chnl->mNodeName);
		node->mTransformation = matprod;
	}
	tick = (tick + 1) % static_cast<int>(anim->mDuration);
	glutPostRedisplay();
	glutTimerFunc(secsPerTick * 1000, update, 0);
}

void display()
{
	float pos[4] = {50, 50, 50, 1};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, 0, -5, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	// scale the whole asset to fit into our view frustum 
	float tmp = scene_max.x - scene_min.x;
	tmp = aisgl_max(scene_max.y - scene_min.y, tmp);
	tmp = aisgl_max(scene_max.z - scene_min.z, tmp);
	tmp = 1.f / tmp;
	glScalef(tmp, tmp, tmp);

	// center the model
	glTranslatef(-scene_center.x, -scene_center.y, -scene_center.z);


	scene_list = glGenLists(1);
	glNewList(scene_list, GL_COMPILE);

	render(scene, scene->mRootNode);
	glEndList();

	glCallList(scene_list);

	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Assimp Test");
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	initialise();
	glutDisplayFunc(display);
	glutTimerFunc(secsPerTick * 1000, update, 0);
	glutMainLoop();

	aiReleaseImport(scene);
}
