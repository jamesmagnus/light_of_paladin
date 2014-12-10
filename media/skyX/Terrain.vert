// --------------------- Terrain material ------------------------

// Uniform
uniform mat4 uWorldViewProj;		// Don't needed, only for hlsl compatibility

void main()
{
    // Clip space position
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[0].z = gl_Vertex.y;
}

