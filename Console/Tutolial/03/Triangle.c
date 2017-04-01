/* Using the standard output for fprintf */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>

/* Using the GLUT library for the base windowing setup */
#include <GL/glut.h>
/* ADD GLOBAL VARIABLES HERE LATER */

#include "shader_utils.h"

GLuint program;
GLint attribute_coord2d;
GLint attribute_v_color;
GLuint vbo_triangle;
GLuint vbo_triangle_colors;
GLint uniform_fade;

/*
Function: init_resources
Receives: void
Returns: int
This function creates all GLSL related stuff
explained in this example.
Returns 1 when all is ok, 0 with a displayed error
*/
int init_resources(void)
{
  GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

  GLuint vs, fs;
  if ((vs = create_shader("triangle.v.glsl", GL_VERTEX_SHADER))   == 0) return 0;
  if ((fs = create_shader("triangle.f.glsl", GL_FRAGMENT_SHADER)) == 0) return 0;

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram:");
    print_log(program);
    return 0;
  }

#if 0
  GLfloat triangle_vertices[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
  };
  glGenBuffers(1, &vbo_triangle);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

  GLfloat triangle_colors[] = {
     0.0, 1.0, 0.0,
     0.0, 0.0, 1.0,
     1.0, 0.0, 0.0,
  };
  glGenBuffers(1, &vbo_triangle_colors);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_colors);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors), triangle_colors, GL_STATIC_DRAW);
#else
  GLfloat triangle_attributes[] = {
     0.0,  0.8,   1.0, 1.0, 0.0,
    -0.8, -0.8,   0.0, 0.0, 1.0,
     0.8, -0.8,   1.0, 0.0, 0.0,
  };
  glGenBuffers(1, &vbo_triangle);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif

  const char* attribute_name = "coord2d";
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if (attribute_coord2d == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return 0;
  }

  attribute_name = "v_color";
  attribute_v_color = glGetAttribLocation(program, attribute_name);
  if (attribute_v_color == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return 0;
  }

  const char* uniform_name;
  uniform_name = "fade";
  uniform_fade = glGetUniformLocation(program, uniform_name);
  if (uniform_fade == -1) {
    fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    return 0;
  }

  return 1;
}

void onDisplay()
{
  /* Clear the background as white */
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(program);

#if 0
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
  glEnableVertexAttribArray(attribute_coord2d);
  /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
  glVertexAttribPointer(
    attribute_coord2d, // attribute
    2,                 // number of elements per vertex, here (x,y)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0                  // offset of first element
  );

  glEnableVertexAttribArray(attribute_v_color);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_colors);
  glVertexAttribPointer(
    attribute_v_color, // attribute
    3,                 // number of elements per vertex, here (r,g,b)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0                  // offset of first element
  );
#else

  glEnableVertexAttribArray(attribute_coord2d);
  glEnableVertexAttribArray(attribute_v_color);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
  glVertexAttribPointer(
    attribute_coord2d,   // attribute
    2,                   // number of elements per vertex, here (x,y)
    GL_FLOAT,            // the type of each element
    GL_FALSE,            // take our values as-is
    5 * sizeof(GLfloat), // next coord2d appears every 5 floats
    0                    // offset of the first element
  );
  glVertexAttribPointer(
    attribute_v_color,   // attribute
    3,                   // number of elements per vertex, here (r,g,b)
    GL_FLOAT,            // the type of each element
    GL_FALSE,            // take our values as-is
    5 * sizeof(GLfloat), // next color appears every 5 floats
    (GLvoid*) (2 * sizeof(GLfloat))  // offset of first element
  );
#endif

  /* Push each element in buffer_vertices to the vertex shader */
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(attribute_coord2d);
  glDisableVertexAttribArray(attribute_v_color);

  /* Display the result */
  glutSwapBuffers();
}

void free_resources()
{
  glDeleteProgram(program);
  glDeleteBuffers(1, &vbo_triangle);
}

void idle()
{
  float cur_fade = sinf(glutGet(GLUT_ELAPSED_TIME) / 1000.0 * (2*M_PI) / 5) / 2 + 0.5; // 0->1->0 every 5 seconds
  glUseProgram(program);
  glUniform1f(uniform_fade, cur_fade);
  glutPostRedisplay();
}

int main(int argc, char* argv[])
{
  /* Glut-related initialising functions */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutCreateWindow("My First Triangle");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /* Extension wrangler initialising */
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK)
  {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
    return EXIT_FAILURE;
  }

  /* When all init functions runs without errors,
  the program can initialise the resources */
  if (1 == init_resources())
  {
    /* We can display it if everything goes OK */
    glutDisplayFunc(onDisplay);
    glutIdleFunc(idle);
    glutMainLoop();
  }

  /* If the program exits in the usual way,
  free resources and exit with a success */
  free_resources();

  return EXIT_SUCCESS;
}
