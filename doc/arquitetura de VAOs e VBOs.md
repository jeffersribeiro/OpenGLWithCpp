![arquitetura de VAOs e VBOs](./imgs/arquitetura%20de%20VAOs%20e%20VBOs.png)

Essa imagem mostra a arquitetura de VAOs e VBOs no OpenGL moderno — algo fundamental para desenhar objetos na tela com eficiência. Vamos por partes:

# 🧱 Componentes da imagem

## 🔴 VAO (Vertex Array Object)

* É um objeto que armazena os ponteiros de atributos (vertex attribute pointers).
* Cada VAO configura como ler os dados dos VBOs.
* Pode ter até 16 atributos (0 a 15).
* Exemplo: posição, cor, normal, coordenada de textura, etc.

## 🟩 VBO (Vertex Buffer Object)

* Contém os dados brutos dos vértices.
* Cada VBO é só um bloco de memória na GPU.
* Você pode ter 1 ou vários VBOs por VAO.
* Cada VBO pode conter:
  * Somente posição (VBO 1)
  * Somente cor (VBO 2)
  * Ou intercalado (posição + cor + normal + ...)

## 🔁 Relação entre VAO e VBO

A imagem mostra que:

* VAO 1 tem os atributos:
  * attribute pointer 0 → posição em VBO 1
  * attribute pointer 1 → cor em VBO 2

* VAO 2 pode usar o mesmo VBO mas com um layout diferente
  * Por exemplo, ele usa só as posições do VBO 2 e ignora as cores

## 🧠 Conceito-chave: os ponteiros de atributos

Quando você escreve no OpenGL:

```cpp
GL.VertexAttribPointer(0, 3, Float, false, stride, offset);
GL.EnableVertexAttribArray(0);
```

Você está dizendo:

>"O atributo 0 (por exemplo, a posição) deve ser lido do VBO atualmente ligado, com </br> esse tamanho, espaçamento e deslocamento."


E o VAO guarda essa instrução.

## 🛠️ Por que isso importa?

- Com VAO, você configura os atributos uma única vez no Load() e depois só faz:

```cpp
GL.BindVertexArray(vao);
GL.DrawArrays(...);
```

- Isso é muito mais eficiente do que reconfigurar os atributos a cada frame.
- Permite múltipos objetos com layouts diferentes (cada um com seu VAO).

## 🔁 Reutilização e modularidade

| VAO   | Função                                                    |
| ----- | --------------------------------------------------------- |
| VAO 1 | Desenha modelo A com posição + cor em buffers separados   |
| VAO 2 | Desenha modelo B com atributos diferentes ou intercalados |

```cpp
float vertices[] = {
    0.0f, -0.5f, 0.0f,  // V0₂ — centro inferior
    1.0f, -0.5f, 0.0f,  // V1₂ — canto inferior direito
    0.5f, 0.5f, 0.0f    // V2₂ — topo direito
}
```

## 🧠 Como a GPU enxerga isso no VBO:

A GPU vê isso como um bloco contínuo de bytes na memória. Cada grupo de 3 floats representa um vértice:

| Vértice | Componente | Mapeamento no VBO | Valor |
| ------- | ---------- | ----------------- | ----- |
| V0      | x          | pos\[0]           | -0.5f |
| V0      | y          | pos\[1]           | -0.5f |
| V0      | z          | pos\[2]           | 0.0f  |
| V1      | x          | pos\[3]           | 0.5f  |
| V1      | y          | pos\[4]           | -0.5f |
| V1      | z          | pos\[5]           | 0.0f  |
| V2      | x          | pos\[6]           | 0.0f  |
| V2      | y          | pos\[7]           | 0.5f  |
| V2      | z          | pos\[8]           | 0.0f  |
