#include <iostream>
#include <GLFW/glfw3.h>
#include <math.h>
#include <windows.h>

float angle1 = 3.1415926;
static GLint rack1, rack2, rack3;

static GLfloat view_rotx = 20.f, view_roty = 30.f, view_rotz = 0.f;
static GLint gear1, gear2, gear3;
static GLfloat angle = 0.f;

/* draw the rack function */
void rack(GLfloat x, GLfloat y, GLfloat insideRadius, GLfloat outsideRadius,
	GLint tooth, GLfloat toothLength, float r, float g, float b)
{
	GLfloat r0, r1, r2, tooth_width, generated_angle;
	GLfloat u, v, len;
	r0 = insideRadius;
	r1 = outsideRadius - toothLength / 2.f;
	r2 = outsideRadius + toothLength / 2.f;
	/* configure width of tooth */
	tooth_width = 0.5f * angle1 / tooth;

	glShadeModel(GL_FLAT);

	glNormal3f(0.f, 0.f, 1.f);

	/* drawing the circle */
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= tooth; i++)
	{
		/* set the color to the given parameters */
		glColor3f(r, g, b);
		generated_angle = i * 2.f * 3.1415926 / tooth;
		/* creating the circle */
		glVertex3f(x + r0 * (float)cos(generated_angle), y + r0 * (float)sin(generated_angle), tooth_width * 0.5f);
		glVertex3f(x + r1 * (float)cos(generated_angle), y + r1 * (float)sin(generated_angle), tooth_width * 0.5f);
		if (i < tooth)
		{
			/* filling the space between the edge of the wheel and the teeth */
			glVertex3f(x + r0 * (float)cos(generated_angle), y + r0 * (float)sin(generated_angle), tooth_width * 0.5f);
			glVertex3f(x + r1 * (float)cos(generated_angle + 3 * tooth_width), y + r1 * (float)sin(generated_angle + 3 * tooth_width), tooth_width * 0.5f);
		}
	}
	glEnd();

	/* drawing teeth */
	glBegin(GL_QUADS);
	for (int i = 0; i < tooth; i++)
	{
		generated_angle = i * 2.f * 3.1415926 / tooth;
		/* creating teeth */
		glVertex3f(x + r1 * (float)cos(generated_angle), y + r1 * (float)sin(generated_angle), tooth_width * 0.5f);
		glVertex3f(x + r2 * (float)cos(generated_angle + tooth_width), y + r2 * (float)sin(generated_angle + tooth_width), tooth_width * 0.5f);
		glVertex3f(x + r2 * (float)cos(generated_angle + 2 * tooth_width), y + r2 * (float)sin(generated_angle + 2 * tooth_width), tooth_width * 0.5f);
		glVertex3f(x + r1 * (float)cos(generated_angle + 3 * tooth_width), y + r1 * (float)sin(generated_angle + 3 * tooth_width), tooth_width * 0.5f);
	}
	glEnd();

	glNormal3f(0.0, 0.0, -1.0);

	/* draw back face */
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= tooth; i++) {
		generated_angle = i * 2.f * 3.1415926 / tooth;
		glVertex3f(x + r1 * (float)cos(generated_angle), y + r1 * (float)sin(generated_angle), -tooth_width * 0.5f);
		glVertex3f(x + r0 * (float)cos(generated_angle), y + r0 * (float)sin(generated_angle), -tooth_width * 0.5f);
		if (i < tooth) {
			glVertex3f(x + r1 * (float)cos(generated_angle + 3 * tooth_width), y + r1 * (float)sin(generated_angle + 3 * tooth_width), -tooth_width * 0.5f);
			glVertex3f(x + r0 * (float)cos(generated_angle), y + r0 * (float)sin(generated_angle), -tooth_width * 0.5f);
		}
	}
	glEnd();

	glBegin(GL_QUADS);

	for (int i = 0; i < tooth; i++) {
		generated_angle = i * 2.f * 3.1415926 / tooth;

		glVertex3f(x + r1 * (float)cos(generated_angle + 3 * tooth_width), y + r1 * (float)sin(generated_angle + 3 * tooth_width), -tooth_width * 0.5f);
		glVertex3f(x + r2 * (float)cos(generated_angle + 2 * tooth_width), y + r2 * (float)sin(generated_angle + 2 * tooth_width), -tooth_width * 0.5f);
		glVertex3f(x + r2 * (float)cos(generated_angle + tooth_width), y + r2 * (float)sin(generated_angle + tooth_width), -tooth_width * 0.5f);
		glVertex3f(x + r1 * (float)cos(generated_angle), y + r1 * (float)sin(generated_angle), -tooth_width * 0.5f);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < tooth; i++) {
		generated_angle = i * 2.f * 3.1415926 / tooth;

		glVertex3f(x + r1 * (float)cos(generated_angle), y + r1 * (float)sin(generated_angle), tooth_width * 0.5f);
		glVertex3f(x + r1 * (float)cos(generated_angle), y + r1 * (float)sin(generated_angle), -tooth_width * 0.5f);
		u = x + (r2 * (float)cos(generated_angle + tooth_width) - r1 * (float)cos(generated_angle));
		v = y + (r2 * (float)sin(generated_angle + tooth_width) - r1 * (float)sin(generated_angle));
		len = (float)sqrt(u * u + v * v);
		u /= len;
		v /= len;
		glNormal3f(v, -u, 0.0);
		glVertex3f(x + r2 * (float)cos(generated_angle + tooth_width), y + r2 * (float)sin(generated_angle + tooth_width), tooth_width * 0.5f);
		glVertex3f(x + r2 * (float)cos(generated_angle + tooth_width), y + r2 * (float)sin(generated_angle + tooth_width), -tooth_width * 0.5f);
		glNormal3f(x + (float)cos(generated_angle), y + (float)sin(generated_angle), 0.f);
		glVertex3f(x + r2 * (float)cos(generated_angle + 2 * tooth_width), y + r2 * (float)sin(generated_angle + 2 * tooth_width), tooth_width * 0.5f);
		glVertex3f(x + r2 * (float)cos(generated_angle + 2 * tooth_width), y + r2 * (float)sin(generated_angle + 2 * tooth_width), -tooth_width * 0.5f);
		u = x + (r1 * (float)cos(generated_angle + 3 * tooth_width) - r2 * (float)cos(generated_angle + 2 * tooth_width));
		v = y + (r1 * (float)sin(generated_angle + 3 * tooth_width) - r2 * (float)sin(generated_angle + 2 * tooth_width));
		glNormal3f(v, -u, 0.f);
		glVertex3f(x + r1 * (float)cos(generated_angle + 3 * tooth_width), y + r1 * (float)sin(generated_angle + 3 * tooth_width), tooth_width * 0.5f);
		glVertex3f(x + r1 * (float)cos(generated_angle + 3 * tooth_width), y + r1 * (float)sin(generated_angle + 3 * tooth_width), -tooth_width * 0.5f);
		glNormal3f(x + (float)cos(generated_angle), y + (float)sin(generated_angle), 0.f);
	}

	glVertex3f(x + r1 * (float)cos(0), y + r1 * (float)sin(0), tooth_width * 0.5f);
	glVertex3f(x + r1 * (float)cos(0), y + r1 * (float)sin(0), -tooth_width * 0.5f);

	glEnd();

	glShadeModel(GL_SMOOTH);

	/* draw inside radius cylinder */
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= tooth; i++) {

		generated_angle = i * 2.f * 3.1415926 / tooth;

		glNormal3f(x - (float)cos(generated_angle), y + -1 * (float)sin(generated_angle), 0.f);
		glVertex3f(x + r0 * (float)cos(generated_angle), y + r0 * (float)sin(generated_angle), -tooth_width * 0.5f);
		glVertex3f(x + r0 * (float)cos(generated_angle), y + r0 * (float)sin(generated_angle), tooth_width * 0.5f);
	}
	glEnd();

}


void key(GLFWwindow* window, int k, int s, int action, int mods)
{
	if (action != GLFW_PRESS) return;

	switch (k) {
	case GLFW_KEY_Z:
		if (mods & GLFW_MOD_SHIFT)
			view_rotz -= 5.0;
		else
			view_rotz += 5.0;
		break;
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	case GLFW_KEY_UP:
		view_rotx += 5.0;
		break;
	case GLFW_KEY_DOWN:
		view_rotx -= 5.0;
		break;
	case GLFW_KEY_LEFT:
		view_roty += 5.0;
		break;
	case GLFW_KEY_RIGHT:
		view_roty -= 5.0;
		break;
	default:
		return;
	}
}


void reshape(GLFWwindow* window, int width, int height)
{
	GLfloat h = (GLfloat)height / (GLfloat)width;
	GLfloat xmax, znear, zfar;

	znear = 5.0f;
	zfar = 30.0f;
	xmax = znear * 0.13f;

	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-xmax, xmax, -xmax * h, xmax * h, znear, zfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -9.0);
}

void init()
{
	static GLfloat pos[4] = { 5.f, 5.f, 10.f, 0.f };
	static GLfloat red[4] = { 1.f, 0.f, 0.f, 1.f };
	static GLfloat green[4] = { 0.f, 1.f, 0.f, 1.f };
	static GLfloat blue[4] = { 0.f, 0.f, 1.f, 1.f };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	/* declaring the racks and sending arguments to the function */
	rack1 = glGenLists(1);
	glNewList(rack1, GL_COMPILE);
	rack(-0.4f, -0.3f, 0.15f, 0.55f, 24, 0.08f, 1.0f, 0.f, 0.f);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glEndList();

	rack2 = glGenLists(1);
	glNewList(rack2, GL_COMPILE);
	rack(-0.4f, 0.58f, 0.2f, 0.3f, 15, 0.08f, 0.f, 1.f, 0.f);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
	glEndList();

	rack3 = glGenLists(1);
	glNewList(rack3, GL_COMPILE);
	rack(0.48f, -0.33f, 0.05f, 0.3f, 15, 0.08f, 0.f, 0.f, 1.f);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glEndList();

	glEnable(GL_NORMALIZE);
}

int main()
{
	/* handling errors and creating the window */
	GLFWwindow* window;
	if (!glfwInit()) {
		std::cout << "Blad Init!";
		return -1;
	}

	glfwWindowHint(GLFW_DEPTH_BITS, 16);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	window = glfwCreateWindow(800, 800, "Gears", 0, 0);
	if (!window) {
		std::cout << "Error creating the window!";
		glfwTerminate();
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, reshape);
	glfwSetKeyCallback(window, key);
	glfwMakeContextCurrent(window);
	//gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	/* initializing creation of racks */
	init();
	reshape(window, 800, 800);
	while (!glfwWindowShouldClose(window))
	{
		/* setting the background */
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* saving data of the transformation into the matrix, exacuting and removing the matrix*/
		glPushMatrix();

		glRotatef(view_rotx, 1.0, 0.0, 0.0);
		glRotatef(view_roty, 0.0, 1.0, 0.0);
		glRotatef(view_rotz, 0.0, 0.0, 1.0);

		glPushMatrix();
		glTranslatef(0.48f, -0.33f, 0.0f);
		glRotatef(angle1 * 1.6, 0.0f, 0.0f, 1.0f);
		glTranslatef(-0.48f, 0.33f, 0.0f);
		glCallList(rack3);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.4f, 0.58f, 0.0f);
		glRotatef(angle1 * 1.6, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.4f, -0.58f, 0.0f);
		glCallList(rack2);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-0.4f, -0.3f, 0.0f);
		glRotatef(-angle1 , 0.0f, 0.0f, 1.0f);
		glTranslatef(0.4f, 0.3f, 0.0f);
		glCallList(rack1);
		glPopMatrix();

		glPopMatrix();

		/* modify the angle depending on the passing time */
		angle1 = 45.f * (float)glfwGetTime();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}