varying vec3 Normal;
varying vec3 camPos;
uniform vec3 cam;;

void main(void)
{
	camPos = vec3(cam.x-gl_Vertex.x, cam.y-gl_Vertex.y, cam.z-gl_Vertex.z);
    gl_Position = ftransform();
	gl_FrontColor = vec4(0.937254, 0.847058, 0.027450, 1.0);

	Normal = gl_NormalMatrix * gl_Normal;
}