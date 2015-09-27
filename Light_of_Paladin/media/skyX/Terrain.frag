// --------------------- Terrain material ------------------------

// Uniform
uniform float     uLightY;
uniform sampler2D uAmbientMap;
uniform sampler2D uTex0;
uniform sampler2D uTex1;

void main()
{
    float AmbientLight = texture2D(uAmbientMap,gl_TexCoord[0].xy).x * (0.8 - 0.8*clamp( -(uLightY-0.15)*4.0, 0.0, 1.0) + 0.115);
    
    vec3 Tex0 = texture2D(uTex0,gl_TexCoord[0].xy*200.0).xyz;
    vec3 Tex1 = texture2D(uTex1,gl_TexCoord[0].xy*200.0).xyz;
    
    gl_FragColor = vec4(AmbientLight * mix(Tex1, Tex0, clamp(7.5*(gl_TexCoord[0].z/1000.0-0.5), 0.0, 1.0)), 1.0);
}
