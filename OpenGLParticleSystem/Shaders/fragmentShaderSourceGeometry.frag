#version 330 core
out vec4 FragColor;
uniform sampler2D texture1;

in Outputs{
 vec2 TexCoords;
}GeoOut;

void main()
{
FragColor = texture(texture1, GeoOut.TexCoords);
};