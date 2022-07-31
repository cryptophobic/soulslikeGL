#version 330 core

out vec4 FragColor;
in vec3 ourColor; // input variable from vs (same name and type)
in vec3 ourPosition;

void main()
{
    FragColor = vec4(
    ourPosition.r < 0 ? -ourPosition.r : ourPosition.r,
    ourPosition.g < 0 ? -ourPosition.g : ourPosition.g,
    ourPosition.b < 0 ? -ourPosition.b : ourPosition.b,
    1.0
    );
}
