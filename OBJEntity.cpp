#include "OBJEntity.h"
#include "Globals.h"
#include "math.h"

#include <sstream>
#include <fstream>

#define deleteVector(__type__, __vect__) do {\
    std::vector<__type__>::iterator iter; \
    std::vector<__type__>::iterator end; \
    iter = __vect__->begin();\
    end = __vect__->end();\
    while(iter != end) delete (*(iter++));\
    delete __vect__;\
    } while(false)

OBJEntity::OBJEntity(std::string filename) : Drawable() {
    this->vertices = new std::vector<Vector3*>();
    this->colors = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
    this->faces = new std::vector<Face*>();
    parse(filename.c_str());
}

OBJEntity::~OBJEntity() {
    deleteVector(Vector3*, vertices);
    deleteVector(Vector3*, colors);
    deleteVector(Vector3*, normals);
    deleteVector(Face*, faces);
}

void OBJEntity::parse(const char *filename) {
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens;
    std::string token;
    std::string ftok;
    
    std::cout << "Starting parse of: " << filename << std::endl;
    
    while( std::getline(infile, line) ) {
        if(line.empty()) continue;
        tokens.clear();
        tokens = split(line, ' ', tokens);
        ftok = tokens.at(0);
        
        if( ftok.compare("v") == 0 ) {			//Parse the vertex line
            vertices->push_back(new Vector3(
                                        std::stof(tokens.at(1)),
                                        std::stof(tokens.at(2)),
                                        std::stof(tokens.at(3))
                                        ));
            bool hasColor = (tokens.size() == 6);
            colors->push_back(new Vector3(
                                      hasColor ? std::stof(tokens.at(4)) : 0.5,
                                      hasColor ? std::stof(tokens.at(5)) : 0.5,
                                      hasColor ? std::stof(tokens.at(6)) : 0.5
                                      ));
            
        } else if( ftok.compare("vn") == 0 ) {	//Parse the normal line
            Vector3 *newVN = new Vector3(
                                    std::stof(tokens.at(1)),
                                    std::stof(tokens.at(2)),
                                    std::stof(tokens.at(3))
                                    );
            newVN->normalize();
            normals->push_back(newVN);
            
        } else if( tokens.at(0).compare("f") == 0 ) {
            Face *face = new Face();
            int splitPstn = (GLint)tokens[1].find("/");
            int v0 = atoi(tokens[1].substr(0, splitPstn).c_str());
            int n0 = atoi(tokens[1].substr(splitPstn+2).c_str());
            splitPstn = (GLint)tokens[2].find("/");
            int v1 = atoi(tokens[2].substr(0, splitPstn).c_str());
            int n1 = atoi(tokens[2].substr(splitPstn+2).c_str());
            splitPstn = (GLint)tokens[3].find("/");
            int v2 = atoi(tokens[3].substr(0, splitPstn).c_str());
            int n2 = atoi(tokens[3].substr(splitPstn+2).c_str());
            face->set( v0, v1, v2, n0, n1, n2);
            faces->push_back(face);
            
        }
        
    }
    std::cout << "Done parsing." << std::endl;
}

std::vector<std::string>& OBJEntity::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJEntity::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void OBJEntity::draw() {
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf( Matrix4::transpose(m2w).getPointer() );
    
    glBegin(GL_TRIANGLES);

    std::vector<Face*>::iterator it = faces->begin();
    while(faces->end() != it) {
        GLint n1 = (*it)->normalIndices[0] - 1;
        GLint n2 = (*it)->normalIndices[1] - 1;
        GLint n3 = (*it)->normalIndices[2] - 1;
        GLint v1 = (*it)->vertexIndices[0] - 1;
        GLint v2 = (*it)->vertexIndices[1] - 1;
        GLint v3 = (*it)->vertexIndices[2] - 1;
        glNormal3f( (*normals).at(n1)->x,(*normals).at(n1)->y,(*normals).at(n1)->z );
        glColor3f( (*colors).at(v1)->x, (*colors).at(v1)->y,(*colors).at(v1)->z );
        glVertex3f((*vertices).at(v1)->x, (*vertices).at(v1)->y,(*vertices).at(v1)->z );
        
        glNormal3f( (*normals).at(n2)->x,(*normals).at(n2)->y,(*normals).at(n2)->z );
        glColor3f( (*colors).at(v2)->x, (*colors).at(v2)->y,(*colors).at(v2)->z );
        glVertex3f((*vertices).at(v2)->x, (*vertices).at(v2)->y,(*vertices).at(v2)->z );
        
        glNormal3f( (*normals).at(n3)->x,(*normals).at(n3)->y,(*normals).at(n3)->z );
        glColor3f( (*colors).at(v3)->x, (*colors).at(v3)->y,(*colors).at(v3)->z );
        glVertex3f((*vertices).at(v3)->x, (*vertices).at(v3)->y,(*vertices).at(v3)->z );
        ++it;
    }
    glEnd();
    
    glPopMatrix();
}

void OBJEntity::update() {
    
}