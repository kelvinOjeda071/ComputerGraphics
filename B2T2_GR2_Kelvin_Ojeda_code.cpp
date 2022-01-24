#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);//Definen los métodos que se van a utilzar
void processInput(GLFWwindow* window);
const unsigned int SCR_WIDTH = 900;// Configura el tamaño de la ventana, tanto de altura como anchura
const unsigned int SCR_HEIGHT = 900;
float movedFactorX = 0.0f; //Se define el factor con el que se va a mover la figura
float movedFactorY = 0.65f; //Se define el factor con el que se va a mover la figura
int main()
{   glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//Especifica las versiones de openGL a utilizar tanto la menor como la mayor
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Kelvin Ojeda, 1723806392", NULL, NULL);//Crea la pestaña acorde con las dimensiones especificadas
    if (window == NULL)
    {   std::cout << "Falla en la creación de la ventana GLFW window" << std::endl;
        glfwTerminate();
        return -1;}
    glfwMakeContextCurrent(window); //Permite otorgar un conjunto de tareas a la vez a la CPU
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//Se invoca a la función que permite el cambio de perspectiva de la pestaña activa
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//En caso de fallar el GLAD
    {   std::cout << "Fallo en la inicialización del GLAD" << std::endl;
        return -1;}
    Shader ourShader("E:/shaders/B2P2_vertexshader.vs", "E:/shaders/B2P2_fragmentshader.fs");//Se invoca a los shaders correspondientes a la presente práctica
    float vertices[] = {
            // positions                // colors        //Indices  //P(X) -> Son identificadores de las coordenadas utilizadas en el plano cartesiano del archivo .pdf
		 0.00f,   0.00f, 0.0f,      1.00f,0.988f,0.019f,   //   0        1  //Circunferencia del sol
		 0.10f,   0.10f, 0.0f,      1.00f,0.823f,0.058f,   //   1        2
		 0.15f,   0.00f, 0.0f,      1.00f,0.823f,0.058f,   //   2        3
		 0.10f,  -0.10f, 0.0f,      1.00f,0.823f,0.058f,   //   3        4
		 0.00f,  -0.15f, 0.0f,      1.00f,0.823f,0.058f,   //   4        5
		-0.10f,  -0.10f, 0.0f,      1.00f,0.823f,0.058f,   //   5        6
		-0.15f,   0.00f, 0.0f,      1.00f,0.823f,0.058f,   //   6        7
		-0.10f,   0.10f, 0.0f,      1.00f,0.823f,0.058f,   //   7        8
		 0.00f,   0.15f, 0.0f,      1.00f,0.823f,0.058f,   //   8        9
		-0.10f,   0.25f, 0.0f,      1.00f,0.988f,0.019f,   //   9        10 //Puntas del sol
		 0.10f,   0.25f, 0.0f,      1.00f,0.988f,0.019f,   //   10       11
		 0.25f,   0.10f, 0.0f,      1.00f,0.988f,0.019f,   //   11       12
		 0.25f,  -0.10f, 0.0f,      1.00f,0.988f,0.019f,   //   12       13
		 0.10f,  -0.25f, 0.0f,      1.00f,0.988f,0.019f,   //   13       14
		-0.10f,  -0.25f, 0.0f,      1.00f,0.988f,0.019f,   //   14       15
		-0.25f,  -0.10f, 0.0f,      1.00f,0.988f,0.019f,   //   15       16
		-0.25f,   0.10f, 0.0f,      1.00f,0.988f,0.019f,   //   16       17
		-1.00f,   0.05f, 0.0f,      0.580f,0.560f,0.560f,  //   17       18 //Carril del carro
		-1.00f,  -0.30f, 0.0f,      0.580f,0.560f,0.560f,  //   18       19
		 1.00f,   0.05f, 0.0f,      0.580f,0.560f,0.560f,  //   19       20
		 1.00f,  -0.30f, 0.0f,      0.580f,0.560f,0.560f,  //   20       21
	  -0.1000f,   0.0000f, 0.0f,    0.090f,0.086f,0.086f,  //   21       22 //Llanta 1 del carro
	  -0.0625f,   0.0375f, 0.0f,    0.090f,0.086f,0.086f,  //   22       23
	  -0.0500f,   0.0000f, 0.0f,    0.090f,0.086f,0.086f,  //   23       24
	  -0.0625f,  -0.0375f, 0.0f,    0.090f,0.086f,0.086f,  //   24       25
	  -0.1000f,  -0.0500f, 0.0f,    0.090f,0.086f,0.086f,  //   25       26
	  -0.1375f,  -0.0375f, 0.0f,    0.090f,0.086f,0.086f,  //   26       27
	  -0.1500f,   0.0000f, 0.0f,    0.090f,0.086f,0.086f,  //   26       28
	  -0.1375f,   0.0375f, 0.0f,    0.090f,0.086f,0.086f,  //   27       29
	  -0.1000f,   0.0500f, 0.0f,    0.090f,0.086f,0.086f,  //   29       30
	   0.3500f,   0.0000f, 0.0f,    0.090f,0.086f,0.086f,  //   30       31 //Llanta 2 del carro
	   0.3875f,   0.0375f, 0.0f,    0.090f,0.086f,0.086f,  //   31       32
	   0.4000f,   0.0000f, 0.0f,    0.090f,0.086f,0.086f,  //   32       33
	   0.3875f,  -0.0375f, 0.0f,    0.090f,0.086f,0.086f,  //   33       34
	   0.3500f,  -0.0500f, 0.0f,    0.090f,0.086f,0.086f,  //   34       35
	   0.3125f,  -0.0375f, 0.0f,    0.090f,0.086f,0.086f,  //   35       36
	   0.3000f,   0.0000f, 0.0f,    0.090f,0.086f,0.086f,  //   36       37
	   0.3125f,   0.0375f, 0.0f,    0.090f,0.086f,0.086f,  //   37       38
	   0.3500f,   0.0500f, 0.0f,    0.090f,0.086f,0.086f,  //   38       39
		-1.00f,    -1.00f, 0.0f,    0.266f,0.827f,0.211f,  //   39       40 //Pasto
		 1.00f,    -1.00f, 0.0f,    0.266f,0.827f,0.211f,  //   40       41
	   -0.150f,    0.150f,0.0f,    0.988f, 0.721f, 0.392f, //   41       42 //Chasis del carro
	    0.450f,    0.150f,0.0f,    0.988f, 0.721f, 0.392f, //   42       43
	    0.300f,    0.250f,0.0f,    0.168f, 0.776f, 0.870f, //   43       44
	    0.050f,    0.250f,0.0f,    0.168f, 0.776f, 0.870f, //   44       45
	   -0.150f,    0.100f,0.0f,    0.988f, 0.721f, 0.392f, //   45       46
	   -0.300f,    0.025f,0.0f,    0.435f, 0.243f, 0.003f, //   46       47
	    0.450f,    0.100f,0.0f,    0.988f, 0.721f, 0.392f, //   47       48
	    0.600f,    0.025f,0.0f,    0.435f, 0.243f, 0.003f, //   48       49
	   -0.300f,    0.175f,0.0f,    0.960f, 0.176f, 0.019f, //   49       50
	    0.600f,    0.100f,0.0f,    0.996f, 1.000f, 0.219f, //   50       51
	    0.000f,    0.900f,0.0f,    0.996f, 1.000f, 0.219f, //   51       52 //Avion Caza
	   -0.600f,   -0.200f,0.0f,    0.647f, 0.631f, 0.631f, //   52       53
	    0.600f,   -0.200f,0.0f,    0.960f, 0.549f, 0.039f, //   53       54
	    0.000f,   -0.200f,0.0f,    0.960f, 0.549f, 0.039f, //   54       55
	   -0.900f,   -0.700f,0.0f,    0.039f, 0.960f, 0.388f, //   55       56
	    0.900f,   -0.700f,0.0f,    0.039f, 0.960f, 0.388f, //   56       57
	    0.000f,   -0.800f,0.0f,    0.039f, 0.960f, 0.388f  //   57       58
	    
    };
	unsigned int indices[] = {
		0,2,1,//0 //Circulo del Sol
		0,3,2,
		0,4,3,
		0,5,4,
		0,6,5,
		0,7,6,
		0,8,7,
        0,1,8,//7
		10,8,1,//8 //Puntas del Sol
		11,1,2,
		12,2,3,
		13,3,4,
		14,4,5,
		15,5,6,
		16,6,7,
		9,7,8,//15 //Carril
        17,18,19,//16
        19,18,20,//17
        18,39,20,//18 //Pasto
        20,39,40,//19
        44,41,43,//20 //Chasis
        41,42,43,
        41,45,42,
        42,45,47,
        41,49,45,
        50,42,47,
        49,46,50,
        50,46,48,//27
        21,23,22,//28 //Llanta01
        21,24,23,
        21,25,24,
        21,26,25,
        21,27,26,
        21,28,27,
        21,29,28,
        21,22,29,//35
        30,32,31,//36 //Llanta02
        30,33,32,
        30,34,33,
        30,35,34,
        30,36,35,
        30,37,36,
        30,38,37,
        30,31,38,//43
        51,52,53,//44 //Avion Caza
        52,57,53,
        52,55,54,
        53,54,56 //47

	};
    unsigned int VBO, VAO, EBO; //Crea los identificadores tanto para el VAO y VBO
    glGenVertexArrays(1, &VAO); //Se genera el VAO correspondiente
    glGenBuffers(1, &VBO); //Se genera el vertex buffer para el VBO
    glBindVertexArray(VAO); //Se activa el VAO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Se activa el VBO para a posteriori configurar los atributos dentro del VAO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Se configura la matriz de vertices para su posterior lectura de atributos
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);// Se configura que el EBO va hacer un objeto del tipo Element_Array_buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Se configura el EBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //Lectura de atributos de posición
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//Lectura de atributos de color
    glEnableVertexAttribArray(1);
    unsigned int texture1, texture2, texture3, texture4, texture5, texture6; //Se crean variables del tipo enteras tanto para la textura1 como para la textura2
    
    glGenTextures(1, &texture1); //Textura 01 que le corresponde al sol
    glBindTexture(GL_TEXTURE_2D, texture1); // Se activa la coordenada de textura1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Se configura el wrapping tanto en el eje S como T del tipo GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Se configura el texture filtering como GL_LINEAR tanto para magnificación o minificación
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels; //Se guarda la información referente a la textura1
    unsigned char* data = stbi_load("E:/textures/texture1_sol.jpg", &width, &height, &nrChannels, 0); //Se obtienen los datos de la primera textura
    if (data)
    {   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//Se configura los datos asociados a la primera textura
        glGenerateMipmap(GL_TEXTURE_2D);}
    else std::cout << "Falló al cargar la primera textura" << std::endl;//En caso de existir un error se lanza una advertencia por consola
    stbi_image_free(data);//Se liberan los recursos asociados a la textura
    ourShader.use(); //Se activa el programa referenciado en los shader de las clases
    ourShader.setInt("texture1", 0); //Se asigna la textura1 al samplen TEXTURE0
    
    glGenTextures(1, &texture2);//Textura 02 que le corresponde a la carretera
    glBindTexture(GL_TEXTURE_2D, texture2); //Se activa la segunda textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// Se configura el wrapping tanto en el eje S como T del tipo Clamp_to_edge
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Se configura el texture filtering como GL_LINEAR tanto para magnificación o minificación
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("E:/textures/texture2_via.png", &width, &height, &nrChannels, 0);//Se guarda la información referente a la textura2
    if (data)
    {   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);//Se configura los datos asociados a la segunda textura
        glGenerateMipmap(GL_TEXTURE_2D);}
    else std::cout << "Falló al cargar la segunda textura" << std::endl;
    stbi_image_free(data); //Se liberan los datos asociados a la segunda textura
    ourShader.setInt("texture2", 0); //Se configura la segunda textura
    
    glGenTextures(1, &texture3);// Se genera la textura 03 correspondiente al pasto del costado de la carretera
    glBindTexture(GL_TEXTURE_2D, texture3); //Se activa la tercera textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// Se configura el wrapping tanto en el eje S como T del tipo GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Se configura el texture filtering como GL_LINEAR tanto para magnificación o minificación
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("E:/textures/texture3_pasto.jpg", &width, &height, &nrChannels, 0);//Se guarda la información referente a la textura3
    if (data)
    {   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//Se configura los datos asociados a la  textura 3
        glGenerateMipmap(GL_TEXTURE_2D);}
    else std::cout << "Falló al cargar la  textura 03" << std::endl; 
    stbi_image_free(data); //Se liberan los datos asociados a la textura 3
    ourShader.setInt("texture3", 0); //Se asocia la tercera textura al fragment shader

    glGenTextures(1, &texture4);// Se genera la textura 04
    glBindTexture(GL_TEXTURE_2D, texture4); //Se activa la textura 04
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// Se configura el wrapping tanto en el eje S como T del tipo GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Se configura el texture filtering como GL_LINEAR tanto para magnificación o minificación
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("E:/textures/texture4_color_chasis.jpg", &width, &height, &nrChannels, 0);//Se guarda la información referente a la textura4
    if (data)
    {   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//Se configura los datos asociados a la textura4
        glGenerateMipmap(GL_TEXTURE_2D);}
    else  std::cout << "Falló al cargar la  textura 04" << std::endl; 
    stbi_image_free(data); //Se liberan los datos asociados a la  tectura 4
    ourShader.setInt("texture4", 0); //Se configura la textura 4

    glGenTextures(1, &texture5);// Se genera textura 5
    glBindTexture(GL_TEXTURE_2D, texture5); //Se activa la  textura 5
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// Se configura el wrapping tanto en el eje S como T del tipo GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Se configura el texture filtering como GL_LINEAR tanto para magnificación o minificación
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("E:/textures/texture5_llanta.png", &width, &height, &nrChannels, 0);//Se guarda la información referente a la textura 5
    if (data)
    {   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);//Se configura los datos asociados a la  textura 5
        glGenerateMipmap(GL_TEXTURE_2D);}
    else std::cout << "Falló al cargar la textura 05" << std::endl;
    stbi_image_free(data); //Se liberan los datos asociados a la textura 5
    ourShader.setInt("texture5", 0); //Se configura la  textura 5

    glGenTextures(1, &texture6);// Se genera textura 6
    glBindTexture(GL_TEXTURE_2D, texture6); //Se activa la  textura 6
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// Se configura el wrapping tanto en el eje S como T del tipo GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Se configura el texture filtering como GL_LINEAR tanto para magnificación o minificación
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("E:/textures/texture6_camuflaje.jpg", &width, &height, &nrChannels, 0);//Se guarda la información referente a la textura 6
    if (data)
    {   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//Se configura los datos asociados a la  textura 6
        glGenerateMipmap(GL_TEXTURE_2D);}
    else std::cout << "Falló al cargar la textura 06" << std::endl;
    stbi_image_free(data); //Se liberan los datos asociados a la textura 06
    ourShader.setInt("texture6", 0); //Se configura la  textura 06

    while (!glfwWindowShouldClose(window)) //Ingreso dentro del render loop
    {   processInput(window); //Se procesan las entradas a partir del método especificado
        glClearColor(0.525f, 0.8f, 0.996f, 1.0f); //Se configura el color del fondo
        glClear(GL_COLOR_BUFFER_BIT);
        glm::mat4 transform = glm::mat4(1.0f); //Se invoca a la matriz de transformacion
        float timeValue = (sin(glfwGetTime() / 2 + 0.5)) * 2; //Se obtiene el tiempo de la máquina local
        float mezclaColor = timeValue / 2; 
        ourShader.setFloat("variable_mezcla", mezclaColor); //Se invoca al uniform que permite el mostrar el poscentaje de color y de textura en el fragment shader
        ourShader.use();// Se activa el programa
        glBindVertexArray(VAO); //Se activa el VAO para su posterior utilización
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform"); //Se envia al fragment el valor de la matriz de transformación
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glActiveTexture(GL_TEXTURE0); //Se linkean los datos de la textura2 dentro del GL_TEXTURE0
        
        glBindTexture(GL_TEXTURE_2D, texture2);
        glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, (void*)(48 * sizeof(GLuint)));//16
        transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f)); //Se translada ´la figura del sol
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); //Se rota la figura del sol
        transform = glm::scale(transform, glm::vec3(timeValue, timeValue, 0.0f)); 
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);//Se asigna al fragment las coordenadas de sol para que se apliquen los cambios de la matriz de transformancion
        
        glBindTexture(GL_TEXTURE_2D, texture1); //Se linkea la matriz la textura1 dentro del GL_TEXTURE0
        glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0); //16 -> Se envian a dibujar las primeras 16 filas de coordenas de las figuras del EBO
        transform = glm::mat4(1.0f); //Se restaura la matriz de transformación
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]); //Se envia nuevamente la matriz de transformación para que las demas figuras no se muevan
        
        glBindTexture(GL_TEXTURE_2D, texture3);
        glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, (void*)(54 * sizeof(GLuint)));//18 -> Se envian a dibujar desde la fila 18 las coordenas de las figuras del EBO
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(movedFactorX, 0.0f, 0.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
        
        glBindTexture(GL_TEXTURE_2D, texture4);
        glDrawElements(GL_TRIANGLES, 8 * 3, GL_UNSIGNED_INT, (void*)(60 * sizeof(GLuint)));//20-> Se envian a dibujar desde la fila 20 las coordenas de las figuras del EBO
        
        glBindTexture(GL_TEXTURE_2D, texture5);
        glDrawElements(GL_TRIANGLES, 16 * 3, GL_UNSIGNED_INT, (void*)(84 * sizeof(GLuint)));//28-> Se envian a dibujar desde la fila 28 las coordenas de las figuras del EBO
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.65f, movedFactorY, 0.0f)); //Se translada la figura del avion
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 1.0f)); //Se rota la figura del avion
        transform = glm::scale(transform, glm::vec3(0.3f, 0.3f, 0.0f)); //Se reduzca la figura del avion
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
        glBindTexture(GL_TEXTURE_2D, texture6);
        glDrawElements(GL_TRIANGLES, 6 * 3, GL_UNSIGNED_INT, (void*)(132 * sizeof(GLuint)));//44-> Se envian a dibujar desde la fila 44 las coordenas de las figuras del EBO
        glfwSwapBuffers(window); //Se intercambia los buffers de lectura y escritura
        glfwPollEvents(); //Procesan los eventos especificados en el render loop
    }
    glDeleteVertexArrays(1, &VAO); //Se eliminar el VAO y el VBO para liberar recursos
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate(); //Termina la ejecución del GLFW
    return 0;}
void processInput(GLFWwindow* window)
{   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        movedFactorX = movedFactorX + 0.01f; // Permite el movimiento horizontal hacia la derecha del carro
        if (movedFactorX >= 1.0f)  movedFactorX = 1.0f;}
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        movedFactorX = movedFactorX - 0.01f;// Permite el movimiento horizontal hacia la izquierda del carro 
        if (movedFactorX <= -1.0f)  movedFactorX = -1.0f;}
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        movedFactorY = movedFactorY + 0.01f; // Permite el movimiento vertical hacia arriba del avion
        if (movedFactorY >= 1.0f)  movedFactorY = 1.0f;}
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        movedFactorY = movedFactorY - 0.01f; // Permite el movimiento vertical hacia abajo del avion
        if (movedFactorY <= -1.0f)  movedFactorY = -1.0f;}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{   glViewport(0, 0, width, height);//Fucnion que permite especificar las dimensiones de la pantalla para de esta forma cambiar la distribución de la pantalla
}