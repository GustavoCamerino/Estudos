//=============================//
// Fragment Shader (Phong)     //
//=============================//
#version 330 compatibility

// Iluminação: componentes do modelo de Phong (ambiente, difusa, especular).
// Conceito de CG: Phong separa a luz em 3 termos para aproximar o comportamento optico.
uniform vec4 Global_ambient;
uniform vec4 Light_ambient;
uniform vec4 Light_diffuse;
uniform vec4 Light_specular;

// Material: como a superfície responde a luz.
// Conceito de CG: parâmetros do material modulam cada termo de iluminação.
uniform float Material_shininess; // expoente de Phong (controle do tamanho do brilho)
uniform vec4  Material_specular;
uniform vec4  Material_ambient;
uniform vec4  Material_diffuse;

// Interpolados do VS (conceito de CG: interpolação per-fragment = iluminação por pixel).
in vec3 vN;            
in vec3 vPosEye;       
in vec3 vLightPosEye;  

void main() {
    // Normaliza vetores para cálculos angulares corretos.
    // Conceito de CG: dot products assumem vetores unitários.
    vec3 Normal = normalize(vN);

    // Vetor do ponto até a luz e até o olho, todos em EYE space.
    // Conceito de CG: manter CONSISTÊNCIA de espaço é essencial para resultados corretos.
    vec3 Lvec  = vLightPosEye - vPosEye;
    vec3 Light = normalize(Lvec);
    vec3 Eye   = normalize(-vPosEye); // no EYE space, a camera está na origem (0,0,0)

    // Termo ambiente: luz de base que simula iluminação indireta difusa do ambiente.
    // Didático: somamos ambiente global + ambiente da luz e modulamos pelo material.
    vec4 ambient = (Global_ambient + Light_ambient) * Material_ambient;

    // Termo difuso (Lambert): proporcional a cos(theta) = N·L, clampado em [0,1].
    // Conceito de CG: simula energia recebida quando a superfície aponta para a luz.
    float NdotL = max(dot(Normal, Light), 0.0);
    vec4 diffuse = Light_diffuse * NdotL * Material_diffuse;

    // Termo especular (Phong): brilho de destaque (highlight).
    // Conceito de CG: só faz sentido se houver luz direta (N·L > 0).
    vec4 specular = vec4(0.0);
    if (NdotL > 0.0) {
        // reflect(I, N) reflete o VETOR INCIDENTE; por isso usamos -Light.
        vec3 R = reflect(-Light, Normal);
        // Expoente controla concentração do brilho: maior = highlight mais estreito.
        float s = pow(max(dot(Eye, R), 0.0), Material_shininess);
        specular = Light_specular * s * Material_specular;
    }

    // Atenuação pela distância (luz pontual).
    // Conceito de CG: 1 / (k0 + k1*d + k2*d^2). Aqui usamos forma comum e barata.
    // Observação didática: usamos dist e dist^2 para mostrar custo/benefício de dot vs. sqrt.
    float dist2 = dot(Lvec, Lvec);     // mais barato que pow(length(Lvec), 2)
    float dist  = sqrt(dist2);
    float k0 = 1.0;    // constante (piso de intensidade)
    float k1 = 0.0;    // linear   (pode ajustar para cenas grandes)
    float k2 = 0.0001; // quadrática (ajuste para queda realista)
    float attenuation = 1.0 / (k0 + k1*dist + k2*dist2);

    // Composição final.
    // Conceito de CG: ambient é independente; difusa e especular são afetadas pela atenuação.
    vec4 color = ambient + attenuation * (diffuse + specular);

    // Saída. Em pipelines modernos (core), usaríamos 'out vec4 fragColor;'.
    gl_FragColor = color;
}
