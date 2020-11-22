
#pragma once
#include "ofMain.h"
#include "ofxBox2dBaseShape.h"
#include "ofxBox2dPolygonUtils.h"

class ofxBox2dPolygon : public ofxBox2dBaseShape, public ofPolyline {

private:
	
	bool	bIsSimplified;
	bool    bIsTriangulated;
	float   area;
	ofVec2f center;
    
	void    calculateCentroid();
	float   calculateArea();
    void    makeConvexPoly();

public:
	
	ofVboMesh				mesh;
	ofRectangle				bounds;
	vector <TriangleShape>	triangles;
	
	//----------------------------------------
	ofxBox2dPolygon();
	~ofxBox2dPolygon();
	void destroy();
	void clear();
    
	//----------------------------------------
	void addTriangle(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c);
	
	//----------------------------------------
	// Polygon helper functions
	//----------------------------------------
	void simplify(float tolerance=0.3);
    void simplifyToMaxVerts();
	void triangulate(float angleConstraint = -1, float sizeConstraint = -1);
    
	//----------------------------------------
	vector <ofDefaultVertexType> &getPoints();
	bool	isGoodShape() { return calculateArea() > 15; }
    bool    isTriangulated() { return bIsTriangulated; }
	//------------------------------------------------
	void addAttractionPoint(ofVec2f pt, float amt=1);
	void addAttractionPoint(float x, float y, float amt=1);
	void addRepulsionForce(float x, float y, float amt);
	void addRepulsionForce(ofVec2f pt, float amt);
    
	//----------------------------------------
	void create(b2World * b2dworld);
	void draw();
	void drawTriangles();
	
};
