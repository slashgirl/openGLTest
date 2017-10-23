#version 120

uniform sampler2D diffuse;

varying vec2 texCoord0;
varying vec3 normal0;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0) * clamp(dot(-vec3(0,1,1),normal0), 0.1, 1.0);	//法线向量与光照信息的点乘再结合纹理信息得到最后的颜色信息，y和z的45度角光照
}