varying vec3 Normal;
varying vec3 camPos;

void main(void)
{
	vec4 color = gl_Color;
	float Intensity = dot( normalize(camPos) , normalize(Normal) );
	float factor = 1.0;
	if ( Intensity > -0.01 && Intensity < 0.01)
		factor = 0.2;
	color *= vec4 ( factor, factor, factor, 1.0 );
    gl_FragColor =  color;

}