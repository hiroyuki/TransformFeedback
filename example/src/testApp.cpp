#include "testApp.h"
#include "ofxTransformFeedback.h"
ofMesh mesh;
ofEasyCam cam;
ofVboMesh container;
ofxTransformFeedback tffb;
//--------------------------------------------------------------
void testApp::setup(){
    mesh.setMode(OF_PRIMITIVE_POINTS);
    int counter = 0;
    for ( int i = -ofGetWidth(); i < ofGetWidth(); i+= 10 )
    {
        mesh.addVertex(ofVec3f(i, 0));
        counter++;
    }
    tffb.setupGeometry(GL_POINTS, GL_POINTS, 2);
    tffb.loadShader("shader/sample.vert", "shader/sample.frag", "shader/sample.geom");
    vector< string> varying;
    varying.push_back("position");
    varying.push_back("color");
    tffb.setupVaryingFeedback(varying);

    container.setMode(OF_PRIMITIVE_POINTS);
    container.setUsage(GL_STATIC_DRAW);
    //vbomesh hack to allocate space of buffer
    {
        vector< ofVec3f> verts;
        vector< ofFloatColor> colors;
        verts.resize(2*counter);
        colors.resize(2*counter);
        container.addVertices(verts);
        container.addColors(colors);
        container.draw();
    }
}

//--------------------------------------------------------------
void testApp::update(){
    tffb.getShader().begin();
    tffb.getShader().setUniform1f("time", ofGetElapsedTimef()*1.5);
    tffb.getShader().setUniform1f("width", 5);
    tffb.getShader().setUniform1f("height", 400);
    tffb.bindVarying(0, container.getVbo().getVertId());
    tffb.bindVarying(1, container.getVbo().getColorId());
    tffb.begin(OF_PRIMITIVE_POINTS);
    mesh.draw();
    tffb.end();
    tffb.getShader().end();
    tffb.checkError(0);

}

//--------------------------------------------------------------
void testApp::draw(){
    float *pos = tffb.getValue(container.getVbo().getVertId());
    float *color = tffb.getValue(container.getVbo().getColorId());
    tffb.checkError(1);
    
    ofBackground(0);
    glPointSize(5);
    
    cam.begin();
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    for( int i = 0; i < container.getNumVertices(); i++ )
    {
        mesh.addColor(ofFloatColor(color[i*4], color[i*4+1], color[i*4+2], color[i*4+3]));
        mesh.addVertex(ofVec3f(pos[i*3],pos[i*3+1]+2,pos[i*3+2]));
    }
    mesh.draw();
    cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
