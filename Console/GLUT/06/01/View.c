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

void resize(int w, int h/* arguments */) {
  /*  ウィンドウ全体をビューポートに設定 */
  glViewport(0, 0, w, h);

  /*  変換行列の初期化  */
  glLoadIdentity();

  /*  スクリーン上の表示領域をビューポートの大きさに比例させる  */
  glOrtho(-w/200.0, w/200.0, -h/200.0, h/200.0, -1.0, 1.0);
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
  glutReshapeFunc(resize);
  init();
  glutMainLoop();
  return 0;
}
