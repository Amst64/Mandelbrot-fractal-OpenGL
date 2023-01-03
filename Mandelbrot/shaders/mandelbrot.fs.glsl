#version 330

in vec2 vFragPos;

out vec3 fFragColor;

vec2 complexSqr(vec2 z) 
{
    float x = pow(z.x, 2) - pow(z.y, 2);
    float y = 2 * z.x * z.y;

    return vec2(x, y);
}

void main()
{
    int N      = 1000;
    bool outsideOfCircle = false;
    vec2 Z = vFragPos;
    int iteration = 0;
    vec3 color;
    for (int i = 0; i < N; i++) {
        iteration = i;
        if (length(Z) > 2) {
            outsideOfCircle = true;
            break;
        }
        Z = complexSqr(Z) + vFragPos;
    }

    if (outsideOfCircle) {
        fFragColor = vec3(float(iteration)  / N, float(iteration) / N, float(iteration) * float(iteration) / N);
    }
    else {
        fFragColor = vec3(0.0, 0.0, 0.0);
    }
}