#version 120
//
// simple.vert
//
attribute vec3 point;
uniform mat4 transformMatrix;
 
void main(void)
{
  gl_Position = transformMatrix * vec4(point, 1.0);
  position = point + vec3(0.0, 10.15, 0.0);  // 点の位置を移動する
  if (position.y < -1.0) position.y += 2.0;  // 範囲を出たら反対側の位置に戻す
}
