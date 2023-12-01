#include "Bezier.hpp"


extern GLint winWidth, winHeight;

Bezier::Bezier() {
	reset();
}

void Bezier::reset() {
	nCtrlPts = 0;
	nPts = 26;
}

/*  Compute binomial coefficients C[n] for given value of n, output in GLint C[] */
void Bezier::binomialCoeffs(GLint n, GLint C[]) {
	// your code, using O(n) algorithm for C_{n, i), i = 0, 1, ..., n
	//C(n,0) = 1
	C[0] = 1;
	//C(n,i) = C(n-1,i-1) + C(n-1,i)
	for (int i = 1; i <= n; i++) {
		C[i] = C[i - 1] * (n - i + 1) / i ;
	}
	
}

/*  Compute Bezier point at u, and output in Point *bezPt */
void Bezier::computeBezPt(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt)
{
	double x = 0, y = 0, z = 0;
	
	for (int i = 0; i < nCtrlPts; i++) {
		x += C[i] * pow(u, i) * pow(1 - u, nCtrlPts - i - 1) * ctrlPts[i].x;
		y += C[i] * pow(u, i) * pow(1 - u, nCtrlPts - i - 1) * ctrlPts[i].y;
		z += C[i] * pow(u, i) * pow(1 - u, nCtrlPts - i - 1) * ctrlPts[i].z;
	}

	// double b[nCtrlPts], x=0, y=0, z=0, r;
	// int n = nCtrlPts - 1;
	// r = u/(1. - u);
	// b[0] = pow( 1.0-u, n);

	// for (int i=1; i<=n; ++i) {
	// 	b[i] = b[i-1] * (n-i+1) / i * r;
	// }

	// for (int i=0; i<=n; ++i) {
	// 	x = x + b[i]*ctrlPts[i].x;
	// 	y = y + b[i]*ctrlPts[i].y;
	// 	z = z + b[i]*ctrlPts[i].z;
	// }

	bezPt->set(x, y, z);
	
}

/*  Compute both Bezier point and tangent at u, and output in Point bezPt and Vector bezTan respectively*/
void Bezier::computeBezPtTan(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt, Vector *bezTan)
{
	int n = nCtrlPts - 1;
    double x = 0, y = 0, z = 0;

    for (int i = 0; i < nCtrlPts; ++i) {
        x += C[i] * pow(u, i) * pow(1 - u, nCtrlPts - i - 1) * ctrlPts[i].x;
        y += C[i] * pow(u, i) * pow(1 - u, nCtrlPts - i - 1) * ctrlPts[i].y;
        z += C[i] * pow(u, i) * pow(1 - u, nCtrlPts - i - 1) * ctrlPts[i].z;
    }
    bezPt->set(x, y, z);

    x = 0, y = 0, z = 0;
    for (int i = 0; i < n; ++i) {
        x += C[i] * (i - n * u) * pow(u, i - 1) * pow(1 - u, nCtrlPts - i - 1) * ctrlPts[i].x;
        y += C[i] * (i - n * u) * pow(u, i - 1) * pow(1 - u, nCtrlPts - i - 1) * ctrlPts[i].y;
        z += C[i] * (i - n * u) * pow(u, i - 1) * pow(1 - u, nCtrlPts - i - 1) * ctrlPts[i].z;
    }

    bezTan->set(x, y, z);

}


/* call to compute the sequence of points on Bezier curve for drawing Bezier curve */
void Bezier::computeBezCurvePts() {
	GLfloat u = 0.5;
	GLint C[nCtrlPts];
	binomialCoeffs(nCtrlPts-1, C);
	for (int k = 0; k < nPts; k++) {
		u = GLfloat(k) / GLfloat(nPts-1);
		computeBezPt(u, nCtrlPts, ctrlPts, C, &Pts[k]);
	}
}


/* call to compute the sequence of points and tangents on Bezier curve for mesh of rotating Bezier curve */
void Bezier::computeBezPtsTan(GLint npts, Point pts[], Vector tangents[]) {
	GLfloat u = 0.5;
	GLint C[nCtrlPts];
	binomialCoeffs(nCtrlPts-1, C);
	for (int k = 0; k < npts; k++) {
		u = GLfloat(k) / GLfloat(npts-1);
		computeBezPtTan(u, nCtrlPts, ctrlPts, C, &pts[k],  &tangents[k]);
	}
}


void Bezier::drawCPts() {
	glPointSize(3.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < nCtrlPts; i++) {
		glVertex2f(ctrlPts[i].x, ctrlPts[i].y);
	}
	glEnd();
}

/* display Control points in 2D view */
void Bezier::displayCPts() {
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
}

/* display Control points and curve in 2D view */
void Bezier::display() {
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
	drawCurve();
}

