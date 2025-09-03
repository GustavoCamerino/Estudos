//=============================//
// Vertex Shader (Phong)       //
//=============================//
#version 330 compatibility

// Posição da luz no espaço do objeto/mundo.
// Nota de CG: vamos transformá-la para EYE SPACE no shader,
// pois todo o cálculo de iluminação aqui será feito nesse espaço.
uniform vec3 Light_location;

// Variáveis "varying" modernas (out no VS, in no FS):
// Nota de CG: valores por-vértice que o rasterizador INTERPOLA por fragmento.
// Isso é central no pipeline gráfico programável.
out vec3 vN;            // normal em eye space
out vec3 vPosEye;       // posição do ponto (vertice) em eye space
out vec3 vLightPosEye;  // posição da luz em eye space

void main() {
    // Transforma a posição do vértice de OBJECT -> EYE space.
    // Conceito de CG: trabalhar num mesmo espaço de coordenadas evita erros.
    vec4 ECPosition = gl_ModelViewMatrix * gl_Vertex;
    vPosEye = ECPosition.xyz;

    // Transforma a normal com a Normal Matrix (inverse-transpose da ModelView).
    // Conceito de CG: normais não devem ser transformadas como posições;
    // a Normal Matrix corrige escalas não uniformes e garante direção correta.
    vN = normalize(gl_NormalMatrix * gl_Normal);

    // Transforma a luz para EYE space.
    vLightPosEye = vec3(gl_ModelViewMatrix * vec4(Light_location, 0.0));

    // Posição final em CLIP space (OBJECT -> CLIP), para o pipeline de rasterização.
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
