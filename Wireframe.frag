#version 330 core
out vec4 FragColor;

in vec3 vertexColor; // Receive color from the vertex shader

void main()
{
    FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Set output color to black
}
