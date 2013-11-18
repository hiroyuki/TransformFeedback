#version 120
#extension GL_EXT_geometry_shader4 : enable

uniform float time;
uniform float width;
uniform float height;
uniform float radius;
varying out vec3 position;
varying out vec4 color;


void main() {
	vec3 center = gl_PositionIn[0].xyz;
    float changedHeight = (smoothstep(-1, 1, sin(time+center.x))*2.0-1.0) * height;
    
    vec3 leftTop = vec3(center.x - width/2, center.y - changedHeight/2, center.z);
    vec3 leftBtm = vec3(center.x - width/2, center.y + changedHeight/2, center.z);
    vec3 rightBtm = vec3(center.x + width/2, center.y + changedHeight/2, center.z);
    vec3 rightTop = vec3(center.x + width/2, center.y - changedHeight/2, center.z);
    vec4 colorLT = vec4(sin(center.x+time), cos(center.y), sin(time), 1);
    vec4 colorLB = vec4(sin(center.x+time), cos(center.y), sin(time), 1);
    vec4 colorRB = vec4(sin(center.x+time), cos(center.y), sin(time), 1);
    vec4 colorRT = vec4(sin(center.x+time), cos(center.y), sin(time), 1);
    
    gl_Position = gl_ModelViewProjectionMatrix*vec4(leftBtm,1);
    position = leftBtm;
    gl_FrontColor = colorLB;
    color = colorLB;
    EmitVertex();
    gl_Position = gl_ModelViewProjectionMatrix*vec4(leftTop,1);
    position = leftTop;
    gl_FrontColor = colorLT;
    color = colorLT;
    EmitVertex();
//    gl_Position = gl_ModelViewProjectionMatrix*vec4(rightBtm,1);
//    gl_FrontColor = colorRB;
//    EmitVertex();
//    gl_Position = gl_ModelViewProjectionMatrix*vec4(rightTop,1);
//    gl_FrontColor = colorRT;
//    EmitVertex();
    EndPrimitive();
    
}