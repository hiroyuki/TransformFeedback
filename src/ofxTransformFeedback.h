//
//  ofxTransformFeedback.h
//
//  Created by 堀 宏行 on 2013/11/16.
//
//

#ifndef example_ofxTransformFeedback_h
#define example_ofxTransformFeedback_h

class ofxTransformFeedback
{
public:
    
    void setupGeometry( GLenum output, GLenum input, int outputCount)
    {
        setGeometryInputType(output);
        setGeometryOutputType(input);
        setGeometryOutputCount(outputCount);
    }
    
    void setGeometryInputType(GLenum type) {
        shader.setGeometryInputType( type );
    }
    
    //--------------------------------------------------------------
    void setGeometryOutputType(GLenum type) {
        shader.setGeometryOutputType( type );
    }
    
    //--------------------------------------------------------------
    void setGeometryOutputCount(int count) {
        shader.setGeometryOutputCount(count);
    }
    
    bool loadShader(string vertName, string fragName, string geomName="")
    {
        if(vertName.empty() == false) shader.setupShaderFromFile(GL_VERTEX_SHADER, vertName);
        if(fragName.empty() == false) shader.setupShaderFromFile(GL_FRAGMENT_SHADER, fragName);
        if(geomName.empty() == false) shader.setupShaderFromFile(GL_GEOMETRY_SHADER_EXT, geomName);
        if ( ofIsGLProgrammableRenderer())
        {
            shader.bindDefaults();
        }
    }
    
    void setupVaryingFeedback( vector< string>& varyings)
    {
        const GLchar* _varyings[varyings.size()];
        for ( int i = 0; i < varyings.size();i++)
        {
            _varyings[i] = varyings.at(i).c_str();
        }
        if ( varyings.size() > 1)
        {
            glTransformFeedbackVaryings(shader.getProgram(), varyings.size(), _varyings, GL_SEPARATE_ATTRIBS);
        }
        else
        {
            glTransformFeedbackVaryings(shader.getProgram(), varyings.size(), _varyings, GL_INTERLEAVED_ATTRIBS);
        }
        linkShader();
    }
    
    void linkShader()
    {
        shader.linkProgram();
    }
    
    void bindVarying( int varyingIndex, int bufferId )
    {
        glBindBufferBaseEXT(GL_TRANSFORM_FEEDBACK_BUFFER, varyingIndex, bufferId);
    }
    
    void begin(ofPrimitiveMode mode)
    {
        int primitive = ofGetGLPrimitiveMode(mode);
        if ( primitive != GL_POINTS && primitive != GL_LINES && primitive != GL_TRIANGLES)
        {
            ofLogWarning() << "primitive mode must be OF_PRIMITIVE_TRIANGLES, OF_PRIMITIVE_LINES, or OF_PRIMITIVE_POINTS";
        }
        glBeginTransformFeedbackEXT(primitive);
    }
    
    void end()
    {
        glEndTransformFeedbackEXT();
    }
    
    float* getValue( int bufferId )
    {
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        float *result = (float *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return result;
    }
    
    
    ofShader& getShader()
    {
        return shader;
    }
    
    void checkError(int no) {
        GLenum err = glGetError();
        
        
        if ( err != GL_NO_ERROR ) {
            printf( "%d OpenGL ERROR code %d: %s\n", no, err, (const char *)gluErrorString( err ) );
        }
    }
    
private:
    ofShader shader;
};

#endif
