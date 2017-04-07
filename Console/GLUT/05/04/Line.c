#include <GL/glut.h>

void display(void) {
  /* code */
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
  glColor3d(1.0, 0.0, 0.0 );  /*  赤 */
  glVertex2d(-0.9, -0.9);
  glColor3d(0.0, 1.0, 0.0 );  /*  緑 */
  glVertex2d( 0.9, -0.9);
  glColor3d(0.0, 0.0, 1.0 );  /*  青 */
  glVertex2d( 0.9,  0.9);
  glColor3d(1.0, 1.0, 0.0 );  /*  黄 */
  glVertex2d(-0.9,  0.9);
  glEnd();
  glFlush();
}

void init(void/* arguments */) {
  /* code */
  glClearColor(1.0,1.0,1.0,1.0);
}
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}
